#ifndef _CHR_NETLINK_H
#define _CHR_NETLINK_H



#define CHR_SPEED_SLOW_EVENT 8
#define CHR_NETLINK_INIT 1
#define CHR_NETLINK_EXIT 0
#define DIFF_SRC_IP_ADDR_MAX 2

#define DIFF_DST_IP_ADDR_MAX 3
#define TIMER_3_MINUTES (180*HZ)
#define TIMER_60_MINUTES (180*20*HZ)

#define CHR_TIMER_3 1
#define CHR_TIMER_60 2

typedef enum Chr_KnlMsgType {
    NETLINK_CHR_REG = 0,    /* send from apk to register the PID for netlink kernel socket */
    NETLINK_CHR_KER_MSG,    /* send from kernel to apk */
    NETLINK_CHR_UNREG       /* when apk exit send this type message to unregister */
} CHR_MSG_TYPE_EN;

struct chr_nl_packet_msg {
       int chr_event;
       unsigned int src_addr;
};

struct chr_netinterface_info_struct {
       unsigned int dstAddrArrayIndex;
       unsigned int dst_addr[DIFF_DST_IP_ADDR_MAX];
       unsigned int src_addr;
};

void notify_chr_thread_to_send_msg(unsigned int dstAddr,unsigned int srcAddr);

#endif /*_CHR_NETLINK_H*/
