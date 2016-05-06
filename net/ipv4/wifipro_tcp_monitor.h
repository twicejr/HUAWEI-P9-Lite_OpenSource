#ifndef _WIFIPRO_TCP_MONITOR_H
#define _WIFIPRO_TCP_MONITOR_H

#define WIFIPRO_LAN1_HEADER          0xC0A80000     //192.168.x.x
#define WIFIPRO_LAN1_MSK             0xFFFF0000
#define WIFIPRO_LAN2_HEADER          0x0A000000     //10.x.x.x
#define WIFIPRO_LAN2_MSK             0xFF000000
#define WIFIPRO_LAN3_HEADER          0xAC100000     //172.16.x.x ~ 172.31.x.x
#define WIFIPRO_LAN3_MSK             0xFFF00000

#define WIFIPRO_GROUP_HEADER         0xE0000000     //224.x.x.x ~ 239.x.x.x
#define WIFIPRO_GROUP_MSK            0xF0000000

#define WIFIPRO_MONITOR_DELAY               (8*HZ)
#define WIFIPRO_TICK_TO_MS                  (1000/HZ)
#define WIFIPRO_RTT_RECORD_SECONDS          8
#define WIFIPRO_MAX_CA_NAME                 12
#define WIFIPRO_MAX_PROC_NAME               80
#define WIFIPRO_CONG_ARRAY                  5
#define WIFIPRO_RTT_THRESHOLD               3000
#define WIFIPRO_RTO_THRESHOLD               300
#define WIFIPRO_PRINT_BUF_SIZE                1500
#define MCC_CHINA                           460
#define BETA_USER                           1
#define WIFIPRO_WLAN_BQE_RTT                    1
#define WIFIPRO_MOBILE_BQE_RTT                  2
#define WIFIPRO_WLAN_SAMPLE_RTT                  3


enum {
    WIFIPRO_ERR = 0,
    WIFIPRO_WARNING,
    WIFIPRO_INFO,
    WIFIPRO_DEBUG,
    WIFIPRO_VERBOSE,
    WIFIPRO_LOG_ALL
};

extern unsigned int wifipro_log_level;

#define WIFIPRO_ERROR(msg, ...)    \
    do {                          \
        if (wifipro_log_level >= WIFIPRO_ERR)  \
            printk(KERN_ERR "#### %s: "msg" ####\n", __func__, ## __VA_ARGS__); \
    } while (0)

#define WIFIPRO_WARNING(msg, ...)    \
    do {                          \
        if (wifipro_log_level >= WIFIPRO_WARNING)  \
            printk(KERN_WARNING "#### %s: "msg" ####\n", __func__, ## __VA_ARGS__); \
    } while (0)

#define WIFIPRO_INFO(msg, ...)    \
    do {                          \
        if (wifipro_log_level >= WIFIPRO_INFO)  \
            printk(KERN_INFO "==== %s: "msg" ====\n", __func__, ## __VA_ARGS__); \
    } while (0)

#define WIFIPRO_DEBUG(msg, ...)    \
    do {                          \
        if (wifipro_log_level >= WIFIPRO_DEBUG)  \
            printk(KERN_INFO "**** %s: "msg" ****\n", __func__, ## __VA_ARGS__); \
    } while (0)

#define WIFIPRO_VERBOSE(msg, ...)    \
    do {                          \
        if (wifipro_log_level >= WIFIPRO_VERBOSE)  \
            printk(KERN_INFO "++++ %s: "msg" ++++\n", __func__, ## __VA_ARGS__); \
    } while (0)


struct wifipro_tcp_monitor_inf {
    unsigned int dst_addr;
    unsigned int dst_port;
    unsigned int src_addr;
    unsigned int src_port;

    unsigned int retransmits;
    unsigned int sock_state;
    unsigned long CurrEstab;
    unsigned long InSegs;
    unsigned long OutSegs;
    unsigned long RetransSegs;
    unsigned long InErrs;
};

typedef struct wifipro_trigger_socket {
    unsigned int dst_addr;
    unsigned int dst_port;
    unsigned int src_addr;
    unsigned int src_port;

    unsigned int retransmits;
    unsigned int other_sock_retrans;
    unsigned int sock_state;
    unsigned long InSegs;
    unsigned long OutSegs;
    unsigned long RetransSegs;
    unsigned long InErrs;
} wifipro_trigger_sock_t;

typedef struct wifipro_rtt_stat {
    unsigned int rtt;
    unsigned int packets;
    unsigned long last_update;
} wifipro_rtt_stat_t;

typedef struct wifipro_rtt_second_stat {
    unsigned int second_num;
    unsigned int total_rtt;
    unsigned int amount;
    unsigned long expire;
    struct wifipro_rtt_second_stat *next;
} wifipro_rtt_second_stat_t;

typedef struct wifipro_congestion_socket{
    char state_name[WIFIPRO_MAX_CA_NAME];
    unsigned int dst_addr;
    unsigned int dst_port;
    unsigned int amount;
    unsigned long when;
}wifipro_cong_sock_t;

typedef struct wifipro_retrans_socket {
    unsigned int dst_addr;
    unsigned int dst_port;
    unsigned int src_addr;
    unsigned int src_port;
    unsigned int retrans;
    unsigned int icsk_rto;
    unsigned char sock_state;
    struct net *net;
} wifipro_retrans_sock_t;

extern bool is_wifipro_on;
extern bool is_mcc_china;

char *wifipro_ntoa(int addr);
int wifipro_handle_retrans(struct sock *sk, struct inet_connection_sock *icsk);
void wifipro_handle_congestion(struct sock *sk, u8 ca_state);
bool wifipro_is_google_sock(struct task_struct *task, unsigned int dest_addr);
bool wifipro_is_trigger_sock(unsigned int dest_addr, unsigned int dest_port);
int wifipro_init_proc(struct net *net);
void wifipro_update_rtt(unsigned int rtt, struct sock *sk);
void wifipro_update_tcp_statistics(int mib_type, struct sk_buff *skb);

static inline bool wifipro_is_not_local_or_lan_sock(unsigned int ip_addr)
{
    if(ip_addr != INADDR_LOOPBACK && ip_addr != INADDR_ANY && ip_addr != INADDR_BROADCAST
        && (ip_addr & WIFIPRO_LAN1_MSK) != WIFIPRO_LAN1_HEADER
        && (ip_addr & WIFIPRO_LAN2_MSK) != WIFIPRO_LAN2_HEADER
        && (ip_addr & WIFIPRO_LAN3_MSK) != WIFIPRO_LAN3_HEADER){
        return true;
    }else{
        return false;
    }
}




void wifi_update_rtt(unsigned int rtt, struct sock *sk);

#endif
