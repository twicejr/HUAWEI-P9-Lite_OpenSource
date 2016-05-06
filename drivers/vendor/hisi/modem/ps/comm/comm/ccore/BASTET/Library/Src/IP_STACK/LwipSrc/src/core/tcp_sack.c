#include "lwip/tcp_sack.h"

#if LWIP_SACK

/* The maximum number of sack segments included in tcp header is 4 */
#define MAX_NUM_SACKS   4

struct tcp_sack_block {
    u32_t   start_seq;
    u32_t   end_seq;
};

struct tcp_sack_block sp_wire[MAX_NUM_SACKS];

int
tcp_sack_parse_option(u8_t *opts, u8_t c)
{
    u8_t l, i;
    u32_t left_wnd_edge, right_wnd_edge;

    for (l = opts[c + 1] - 2, c += 2, i = 0; l > 0; l -= 8, i++) {
        memcpy(&left_wnd_edge, opts + c, sizeof(u32_t));
        left_wnd_edge = ntohl(left_wnd_edge);
        c += 4;

        memcpy(&right_wnd_edge, opts + c, sizeof(u32_t));
        right_wnd_edge = ntohl(right_wnd_edge);
        c += 4;

        sp_wire[i].start_seq = left_wnd_edge;
        sp_wire[i].end_seq = right_wnd_edge;
    }
    return i;
}

static int
tcp_sack_check_dsack(struct tcp_pcb *pcb, struct tcp_sack_block *sp,
             int num_sacks, u32_t ackno)
{
    int dsack = 0;
    u32_t start_seq_0 = sp[0].start_seq;
    u32_t end_seq_0 = sp[0].end_seq;

    if (TCP_SEQ_LT(start_seq_0, ackno)) {
        dsack = 1;
    }
    else if (num_sacks > 1) {
        u32_t start_seq_1 = sp[1].start_seq;
        u32_t end_seq_1 = sp[1].end_seq;
        if (TCP_SEQ_LEQ(end_seq_0, end_seq_1) &&
            TCP_SEQ_GEQ(start_seq_0, start_seq_1)) {
            dsack = 1;
        }
    }

    return dsack;
}

static int
tcp_sack_is_sackblock_valid(struct tcp_pcb *pcb, int is_dsack, u32_t start_seq,
            u32_t end_seq, u32_t ackno)
{
    /* Too far in future, or reversed (interpretation is ambiguous) */
    if (TCP_SEQ_GT(end_seq, pcb->snd_nxt) || TCP_SEQ_GEQ(start_seq, end_seq))
        return 0;

    /* Nasty start_seq wrap-around check (see comments above) */
    if (TCP_SEQ_GEQ(start_seq, pcb->snd_nxt))
        return 0;

    /* In outstanding window? ...This is valid exit for D-SACKs too.
     * start_seq == snd_una is non-sensical (see comments above)
     */
    if (TCP_SEQ_GT(start_seq, ackno))
                return 1;

    if (!is_dsack)
                return 0;

    /* ...Then it's D-SACK, and must reside below snd_una completely */
    if (TCP_SEQ_GT(end_seq, ackno))
                return 0;

        return 1;
}

int
tcp_sack_update(struct tcp_pcb *pcb, int num_sacks, u32_t ackno)
{
    int used_sacks = 0;
    int found_dup_sack = 0;
    int i;
    int first_sack_index = 0;
    int new_sacked = 0;
    struct tcp_sack_block sp[MAX_NUM_SACKS];
    struct tcp_seg *next;

    found_dup_sack = tcp_sack_check_dsack(pcb, sp_wire, num_sacks, ackno);

    for (i = 0; i < num_sacks; i++) {
        int dup_sack = !i && found_dup_sack;

        sp[used_sacks].start_seq = sp_wire[i].start_seq;
        sp[used_sacks].end_seq = sp_wire[i].end_seq;

        if (!tcp_sack_is_sackblock_valid(pcb, dup_sack,
                                         sp[used_sacks].start_seq,
                                         sp[used_sacks].end_seq, ackno)) {
            if (i == 0)
                first_sack_index = -1;
            continue;
        }

        /* Ignore very old stuff early */
        if (TCP_SEQ_LEQ(sp[used_sacks].end_seq, ackno))
                continue;

        used_sacks++;
    }
#if 0
    for (i = used_sacks - 1; i > 0; i--) {
        for (j = 0; j < i; j++) {
            if (after(sp[j].start_seq, sp[j+1].start_seq)) {
                swap(sp[j], sp[j+1]);

                /* Track where the first SACK block goes to */
                if (j == first_sack_index)
                    first_sack_index = j + 1;
            }
        }
    }
#endif
    i = 0;
    while (i < used_sacks) {
        u32_t start_seq = sp[i].start_seq;
        u32_t end_seq = sp[i].end_seq;
        if (found_dup_sack && (i == first_sack_index)) {
            i++;
            continue;
        }
        for (next = pcb->unacked; next != NULL; next = next->next) {
            if (!(next->sacked & TF_SACKED) &&
                TCP_SEQ_GEQ(ntohl(next->tcphdr->seqno), start_seq) &&
                TCP_SEQ_LEQ(ntohl(next->tcphdr->seqno) + TCP_TCPLEN(next), end_seq))
            {
                /* Flag sacked */
                next->sacked |= TF_SACKED;
                new_sacked += TCP_TCPLEN(next);
            }
        }
        i++;
    }

    return new_sacked;
}

void
tcp_sack_initialize_fast_rexmit(struct tcp_pcb *pcb)
{
    u32_t high_sacked, seqno;
    struct tcp_seg *next;

    if (pcb->unacked != NULL && !(pcb->flags & TF_INFR)) {
        pcb->recovery_point = pcb->snd_nxt;
        pcb->pipe = 0;
        pcb->high_rxt = 0;

        /* Initialize pipe */
        high_sacked = ntohl(pcb->unacked->tcphdr->seqno);
        for (next = pcb->unacked; next != NULL; next = next->next) {
            if (next->sacked & TF_SACKED) {
                pcb->pipe += TCP_TCPLEN(next);
                seqno = ntohl(next->tcphdr->seqno) + TCP_TCPLEN(next);
                if (TCP_SEQ_GT(seqno, high_sacked))
                    high_sacked = seqno;
            }
        }
        pcb->pipe = pcb->high_data - high_sacked;
        /* This is fast retransmit. Retransmit the first unacked segment. */
        LWIP_DEBUGF(TCP_FR_DEBUG,
            ("tcp_receive: dupacks %"U16_F" (%"U32_F
             "), fast retransmit %"U32_F"\n",
             (u16_t)pcb->dupacks, pcb->lastack,
             ntohl(pcb->unacked->tcphdr->seqno)));

        /* Set ssthresh to half of the minimum of the current
         * cwnd and the advertised window */
        if (pcb->cwnd > pcb->snd_wnd) {
            pcb->ssthresh = pcb->snd_wnd / 2;
        } else {
            pcb->ssthresh = pcb->cwnd / 2;
        }

        /* The minimum value for ssthresh should be 2 MSS */
        if (pcb->ssthresh < 2*pcb->mss) {
            LWIP_DEBUGF(TCP_FR_DEBUG,
                ("tcp_receive: The minimum value for ssthresh %"U16_F
                 " should be min 2 mss %"U16_F"...\n",
                 pcb->ssthresh, 2*pcb->mss));
            pcb->ssthresh = 2*pcb->mss;
        }

        pcb->cwnd = pcb->ssthresh;
        tcp_rexmit(pcb);

        pcb->flags |= TF_INFR;
    }
}

void
tcp_sack_set_pipe(struct tcp_pcb *pcb, s32_t var)
{
    /* Note that var maybe a negative number */
    /* The mean of pipe is an estimate of the number of bytes that are currently in transit */
    if ((s32_t)((s32_t)pcb->pipe + var) < 0) {
        pcb->pipe = 0;
    }
    else {
        pcb->pipe = pcb->pipe + var;
    }
}

u32_t
tcp_sack_estimate_rexmit_nums(struct tcp_pcb *pcb)
{
    u32_t wnd;
    s32_t ret;

    wnd = LWIP_MIN(pcb->snd_wnd, pcb->cwnd);
    ret = (s32_t)(wnd - pcb->pipe - pcb->mss);

    if (ret < 0) {
        return 0;
    }
    else {
        return ((wnd - pcb->pipe - pcb->mss) / pcb->mss + 1);
    }
}

void
tcp_sack_loss_rexmit(struct tcp_pcb *pcb)
{
    struct tcp_seg *seg;
    struct tcp_seg *prev, *first = NULL, *last, *holes;
    u32_t max_rexmit_nums = tcp_sack_estimate_rexmit_nums(pcb);
    u32_t cnt = 0;

    if (pcb->unacked == NULL) {
        return;
    }

    /* Adding for SACK */

    /* if no SACKed segments are found, process only one segment */
    last = pcb->unacked->next;

    /* find the last SACKed segment, if any, in the unacked list */
    for (seg = pcb->unacked; seg != NULL; seg = seg->next) {
        if (ntohl(seg->tcphdr->seqno) == pcb->high_rxt) {
            first = seg;
        }
        if (seg->sacked & TF_SACKED) {
            last = seg;
        }
    }
    if (first == NULL)
        first = pcb->unacked;

    /*
     * remove all unSACKed segment (holes) before the last SACKed
     * segment from the unacked list and put them in a temporary list
     */
    for (prev = NULL, seg = pcb->unacked, holes = NULL; seg != last && cnt < max_rexmit_nums;)
    {
        /* seg is unSACKed */
        if (!(seg->sacked & TF_SACKED) && TCP_SEQ_GEQ(ntohl(seg->tcphdr->seqno), ntohl(first->tcphdr->seqno))) {
            if (seg == pcb->unacked) {
                pcb->unacked = pcb->unacked->next;
                seg->next = holes;
                holes = seg;
                seg = pcb->unacked;
            }
            else {
                prev->next = seg->next;
                seg->next = holes;
                holes = seg;
                seg = prev->next;
            }
            cnt ++;
        }
        else {
            prev = seg;
            seg = seg->next;
        }
    }
    /* move the holes segments into the unsent queue */
    while (holes != NULL) {
        seg = holes;
        holes = holes->next;

        if (pcb->unsent == NULL) {
            seg->next = NULL;
            pcb->unsent = seg;
#if TCP_OVERSIZE
            pcb->unsent_oversize = 0;
#if TCP_OVERSIZE_DBGCHECK
            seg->oversize_left = 0;
#endif /* TCP_OVERSIZE_DBGCHECK */
            seg->rexmit = 1;
#endif /* TCP_OVERSIZE */
        }
        else {
            for (last = pcb->unsent, prev = NULL; last != NULL; prev = last, last = last->next) {
                if (TCP_SEQ_LEQ(ntohl(seg->tcphdr->seqno), ntohl(last->tcphdr->seqno))) {
                    if (last == pcb->unsent) {
                        seg->next = pcb->unsent;
                        pcb->unsent = seg;
                    }
                    else {
                        seg->next = prev->next;
                        prev->next = seg;
                    }
                    break;
                }
            }
            if (last == NULL) {
                seg->next = NULL;
                prev->next = seg;
#if TCP_OVERSIZE
                pcb->unsent_oversize = 0;
#if TCP_OVERSIZE_DBGCHECK
                seg->oversize_left = 0;
#endif /* TCP_OVERSIZE_DBGCHECK */
                seg->rexmit = 1;
#endif /* TCP_OVERSIZE */
            }
        }
    }
}
#endif
