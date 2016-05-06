#ifndef __LWIP_TCP_SACK_CA__
#define __LWIP_TCP_SACK_CA__

#include "lwip/tcp.h"
#include "lwip/tcp_impl.h"

#ifdef __cplusplus
extern "C" {
#endif

extern int
tcp_sack_parse_option(u8_t *opts, u8_t c);

extern int
tcp_sack_update(struct tcp_pcb *pcb, int num_sacks, u32_t ackno);

extern void
tcp_sack_initialize_fast_rexmit(struct tcp_pcb *pcb);

extern u32_t
tcp_sack_estimate_rexmit_nums(struct tcp_pcb *pcb);

#ifdef __cplusplus
}
#endif

#endif
