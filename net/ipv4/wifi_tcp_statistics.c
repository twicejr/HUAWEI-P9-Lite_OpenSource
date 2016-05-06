#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/workqueue.h>
#include <linux/delay.h>
#include <linux/compiler.h>
#include <net/sock.h>
#include <net/netlink.h>
#include <linux/skbuff.h>
#include <linux/types.h>
#include <linux/netlink.h>
#include <uapi/linux/netlink.h>
#include <linux/kthread.h>
#include <linux/string.h>
#include <net/tcp.h>

#include "wifi_tcp_statistics.h"

MODULE_LICENSE("GPL");

#define WIFI_STAT_ON    1
#define WIFI_STAT_OFF  0

#define NETLINK_MSG_WIFI_TCP_START 1
#define NETLINK_MSG_WIFI_TCP_STOP  0

typedef enum  {
	INDEX_SENDSEGS = 0,  /*LAN SEND SEGS*/
	INDEX_RESENDSEGS,    /*LAN RESEND SEGS*/
	INDEX_RECVSEGS,       /*LAN RECV SEGS*/
	INDEX_ERRSEGS,         /*LAN ERR SEGS*/
	INDEX_OUTRSTS,         /*LAN OUTRST SEGS*/
	INDEX_ESTABLISRST,  /*LAN ESTABLISH RST SEGS*/
	INDEX_RTTDURATION,       /*LAN RTT DURAION*/
	INDEX_RTTSEGS,          /*LAN RTT SEGS*/
	INDEX_SNDDUPACKS,         /*RECV DUPACKS*/
	INDEX_WEBSENDSEGS,        /*WEB SEND SEGS*/
	INDEX_WEBRESENDSEGS,    /*WEB RESEND SEGS*/
	INDEX_WEBRECVSEGS,        /*WEB RECV SEGS*/
	INDEX_WEBERRSEGS,          /*WEB ERR SEGS*/
	INDEX_WEBOUTRSTS,          /*WEB OUTRST SEGS*/
	INDEX_WEBESTABLISRST,    /*WEB ESTABLISH RST SEGS*/
	INDEX_WEBRTTDURATION,  /*WEB RTT DURAION*/
	INDEX_WEBRTTSEGS,    /*WEB RTT SEGS*/
	INDEX_WEBSNDDUPACKS,    /*WEB RECV DUPACKS*/
	INDEX_WEB_SRTT,  /*WIFIPRO SRTT VALUE*/
	MAX_ARR_TITLE_COUNT
	} COUNTER_TYPE;

static char* s_arrTitle[MAX_ARR_TITLE_COUNT] = {
	"SENDSEGS",
	"RESENDSEGS",
	"RECVSEGS",
	"ERRSEGS",
	"OUTRSTS",
	"ESTABLISRST",
	"RTTDURATION",
	"RTTSEGS",
	"SNDDUPACKS",
	"WEBSENDSEGS",
	"WEBRESENDSEGS",
	"WEBRECVSEGS",
	"WEBERRSEGS",
	"WEBOUTRSTS",
	"WEBESTABLISRST",
	"WEBRTTDURATION",
	"WEBRTTSEGS",
	"WEBSNDDUPACKS",
	"WEBSRTT"
};

/* Address to accept any incoming messages. */
#define	INADDR_ANY		((unsigned long int) 0x00000000)

/* Address to send to all hosts. */
#define	INADDR_BROADCAST	((unsigned long int) 0xffffffff)

/* Address indicating an error return. */
#define	INADDR_NONE		((unsigned long int) 0xffffffff)

#define WIFI_LAN1_HEADER           0xC0A80000     //192.168.x.x
#define WIFI_LAN1_MSK                 0xFFFF0000
#define WIFI_LAN2_HEADER           0x0A000000     //10.x.x.x
#define WIFI_LAN2_MSK                 0xFF000000
#define WIFI_LAN3_HEADER           0xAC100000     //172.16.x.x ~ 172.31.x.x
#define WIFI_LAN3_MSK                 0xFFF00000

#define WIFI_MAX_UID_CNT   8

#define WIFI_INVALID_VALUE 0xFFFFFFFF

typedef struct {
	kuid_t uid;
	unsigned int counter[MAX_ARR_TITLE_COUNT];
} UIDTCPStat;

static unsigned int s_WifiStatics[MAX_ARR_TITLE_COUNT] = {0};
static unsigned int s_ON = WIFI_STAT_OFF;
static struct sock *g_wifi_tcp_nlfd = NULL;
static UIDTCPStat s_uidTcpStat[WIFI_MAX_UID_CNT] = {{0}};
static int s_tcpstat_index = 0;
static unsigned char s_cVALIDATESTATE[] = { TCP_ESTABLISHED,  TCP_SYN_SENT, TCP_SYN_RECV, TCP_LISTEN};


int wifipro_get_srtt(void);

static inline bool wifi_is_validate_state(  struct sock *sk ) {
	int i = 0;
	if( NULL == sk ) {
		return false;
	}

	for( i = 0; i <  sizeof(s_cVALIDATESTATE)/sizeof(unsigned char); i++ ) {
		if( sk->sk_state == s_cVALIDATESTATE[i])
			return true;
	}

	return false;
}

static inline bool wifi_is_local_sock(unsigned int ip_addr)
{
    if(ip_addr != INADDR_LOOPBACK && ip_addr != INADDR_ANY && ip_addr != INADDR_BROADCAST){
        return false;
    }else{
        return true;
    }
}

static inline bool wifi_is_lan_sock(unsigned int ip_addr)
{
    if( (ip_addr & WIFI_LAN1_MSK) != WIFI_LAN1_HEADER
        && (ip_addr & WIFI_LAN2_MSK) != WIFI_LAN2_HEADER
        && (ip_addr & WIFI_LAN3_MSK) != WIFI_LAN3_HEADER){
        return false;
    }else{
        return true;
    }
}

static  kuid_t get_socket_uid(struct sock *sk)  {
	kuid_t uid = WIFI_INVALID_VALUE;
	if( sk == NULL ) {
		return WIFI_INVALID_VALUE;
	}

	uid = sock_i_uid(sk);
	return   uid ;
}

static int wifi_getTcpStatIndex(kuid_t uid) {
	int index =  WIFI_INVALID_VALUE;
	int i = 0;
	if( WIFI_INVALID_VALUE == uid )
		return WIFI_INVALID_VALUE;

	if(0 == uid || 1000 == uid)
		return WIFI_INVALID_VALUE;

	for( i = 0; i < s_tcpstat_index && i < WIFI_MAX_UID_CNT ; i++  ) {
		if( s_uidTcpStat[i].uid == uid ) {
			index = i;
			goto out;
		}
	}

	if(s_tcpstat_index  < WIFI_MAX_UID_CNT) {
		index = s_tcpstat_index;
		s_tcpstat_index++;
		s_uidTcpStat[index].uid = uid;
	}

out:
	return index;
}

static void updateTcpStatByUID (kuid_t uid, int index, int count) {
	int result = 0;

	if( s_ON == WIFI_STAT_OFF ) {
		return ;
	}

	result = wifi_getTcpStatIndex(uid);

	if( WIFI_INVALID_VALUE == result )
		return ;

	if(  uid != s_uidTcpStat[result].uid )
		return;

	s_uidTcpStat[result].counter[index] += count;
}

static void wifi_updateCounter( struct sock *sk, int count, int lan, int web) {
	struct inet_sock *inet = NULL;
	unsigned int dest_addr = 0;
	int index = 0;

	if( s_ON == WIFI_STAT_OFF ) {
		return ;
	}

	if(  NULL == sk ) {
		return ;
	}

	inet = inet_sk(sk);
	if( NULL == inet ) {
		return;
	}

	dest_addr = htonl(inet->inet_daddr);

	if( wifi_is_local_sock(dest_addr) == true  )
		return ;

	if(  wifi_is_lan_sock(dest_addr) == true ) {
		index = lan;
	} else {
		index = web;
	}

	s_WifiStatics[index] += count;

	if( wifi_is_validate_state(sk) ) {
		updateTcpStatByUID( get_socket_uid(sk), index, count );
	}
}

static int wifi_network_stat_show(struct seq_file *seq, void *v)
{
	int i = 0, j = 0;
	int bIndex = INDEX_SENDSEGS, eIndex = INDEX_WEBSNDDUPACKS;
	int index = s_tcpstat_index;
	if( s_ON == WIFI_STAT_OFF )
		return 0;

#ifdef CONFIG_HW_WIFIPRO
	s_WifiStatics[INDEX_WEB_SRTT] = wifipro_get_srtt();
#endif

	for( i = 0; i < MAX_ARR_TITLE_COUNT; i++ ) {
		seq_printf(seq, "%s=%u\n",   s_arrTitle[i],  s_WifiStatics[i]);
	}

	seq_puts(seq, "\nUID\t");
	for( i = bIndex; i <= eIndex; i++  ) {
		seq_printf(seq, "%s\t", s_arrTitle[i]);
	}
	seq_puts(seq, "\n");

	for( i = 0; i <  index && i < WIFI_MAX_UID_CNT ; i++) {
		seq_printf(seq, "%u\t", s_uidTcpStat[i].uid);
		for( j = bIndex; j <= eIndex; j++  ) {
			seq_printf(seq, "%u\t", s_uidTcpStat[i].counter[j]);
		}

		seq_puts(seq, "\n");
	}

	memset(s_uidTcpStat, 0, sizeof(s_uidTcpStat));
	s_tcpstat_index = 0;
	memset(s_WifiStatics, 0, sizeof(s_WifiStatics));
	return 0;
}

static void wifi_tcp_nl_receive(struct sk_buff *__skb)
{
	struct nlmsghdr *nlh;
	struct sk_buff *skb;
	skb = skb_get(__skb);

	if (skb->len >= NLMSG_HDRLEN) {
	    nlh = nlmsg_hdr(skb);

	    if ((nlh->nlmsg_len >= sizeof(struct nlmsghdr))&&
	        (skb->len >= nlh->nlmsg_len)) {
	        printk(KERN_ERR "#### %s:  netlink receive a packet, nlmsg_type=%d\n",  __func__, nlh->nlmsg_type);
	        if (NETLINK_MSG_WIFI_TCP_START == nlh->nlmsg_type) {
			s_ON = WIFI_STAT_ON;
	        } else if (NETLINK_MSG_WIFI_TCP_STOP == nlh->nlmsg_type) {
			s_ON = WIFI_STAT_OFF;
			memset(s_WifiStatics, 0, sizeof(s_WifiStatics));
			memset(s_uidTcpStat, 0, sizeof(s_uidTcpStat));
			s_tcpstat_index = 0;
	        } else {
		printk(KERN_ERR "#### %s:  wrong msg_type(%d)####\n",  __func__, nlh->nlmsg_type);
	        }
	     }
	}

	 kfree_skb(skb);
}

static int __init wifi_tcp_module_init(void) {
	 struct netlink_kernel_cfg wifi_tcp_stat_nl_cfg = {
          .input = wifi_tcp_nl_receive,
	};

	printk(KERN_ERR "#### %s:  wifi_tcp_module_init begin init!####\n", __func__);
	g_wifi_tcp_nlfd = netlink_kernel_create(&init_net ,NETLINK_WIFI_EVENT_NL, &wifi_tcp_stat_nl_cfg);

	if(!g_wifi_tcp_nlfd){
		printk(KERN_ERR "#### %s:  wifi_tcp_module_init create sokcet failed!####\n",  __func__);
		return -1;
	}

	return 0;
}
static void __exit wifi_tcp_module_exit(void) {
	if(g_wifi_tcp_nlfd && g_wifi_tcp_nlfd->sk_socket)
	{
		sock_release(g_wifi_tcp_nlfd->sk_socket);
		g_wifi_tcp_nlfd = NULL;
	}
}

module_init(wifi_tcp_module_init);
module_exit(wifi_tcp_module_exit);

static int wifi_network_seq_open(struct inode *inode, struct file *file)
{
    return single_open_net(inode, file, wifi_network_stat_show);
}

static const struct file_operations wifi_networktest = {
    .owner	 = THIS_MODULE,
    .open	 = wifi_network_seq_open,
    .read	 = seq_read,
    .llseek	 = seq_lseek,
    .release = single_release_net,
};

void wifi_update_rtt(unsigned int rtt, struct sock *sk)
{
	wifi_updateCounter(sk, rtt, INDEX_RTTDURATION, INDEX_WEBRTTDURATION);
	wifi_updateCounter(sk, 1,   INDEX_RTTSEGS,   INDEX_WEBRTTSEGS);
	//print_socket_info(sk);
}

void wifi_IncrSendSegs( struct sock *sk, int count) {
    wifi_updateCounter( sk, count, INDEX_SENDSEGS,  INDEX_WEBSENDSEGS);
}

void wifi_IncrRecvSegs( struct sock *sk, int count) {
      wifi_updateCounter( sk, count, INDEX_RECVSEGS,  INDEX_WEBRECVSEGS);
}

void wifi_IncrReSendSegs( struct sock *sk, int count) {
    wifi_updateCounter( sk, count, INDEX_RESENDSEGS,  INDEX_WEBRESENDSEGS);
}

void wifi_IncrErrSegs( struct sock *sk, int count) {
    wifi_updateCounter( sk, count, INDEX_ERRSEGS,  INDEX_WEBERRSEGS);
}

void wifi_IncrRstSegs( struct sock *sk, int count) {
    wifi_updateCounter( sk, count, INDEX_OUTRSTS,  INDEX_WEBOUTRSTS);
}

void wifi_IncrEstabliseRstSegs( struct sock *sk, int count) {
    wifi_updateCounter( sk, count, INDEX_ESTABLISRST,  INDEX_WEBESTABLISRST);
}

void wifi_IncrRcvDupAcksSegs( struct sock *sk, int count) {
	wifi_updateCounter( sk, count, INDEX_SNDDUPACKS,  INDEX_WEBSNDDUPACKS);
}

int wifi_is_on (void) {
	return s_ON;
}

int wifi_tcp_init_proc(struct net *net) {
	if (!proc_create("wifi_network_stat", S_IRUGO, net->proc_net, &wifi_networktest)) {
		return -ENOMEM;
	}

	return 0;
}



