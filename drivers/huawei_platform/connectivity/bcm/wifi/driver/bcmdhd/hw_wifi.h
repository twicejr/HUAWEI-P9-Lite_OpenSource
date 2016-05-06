#ifndef __HW_WIFI_H__
#define __HW_WIFI_H__

/************修改记录************************
版本:				日期:		解决问题:
HUAWEI-2014.001:  	0529		solve wifi panic
HUAWEI-2014.002:       0609		solve scan_done panic.
HUAWEI-2014.003:       0613             throughput optimize.
HUAWEI-2014.004:       0626             solve wdev_cleanup_work panic.
HUAWEI-2014.005:       0702             solve country code problem.
HUAWEI-2014.006:       0725             use huawei customize country code.
HUAWEI-2014.007:       0728             set bcn_timeout for beacon loss and roaming problem.
**********************************************/
#include <typedefs.h>
#include <linuxver.h>
#include <osl.h>
#include <bcmutils.h>
#include <dngl_stats.h>
#include <dhd.h>
#include <wlioctl.h>
#include <wl_iw.h>
#include <dsm/dsm_pub.h>

#define        HUAWEI_VERSION_STR ", HUAWEI-2014.007"

#ifdef HW_WIFI_WAKEUP_SRC_PARSE
#define WIFI_WAKESRC_TAG "WIFI wake src: "
extern volatile bool g_wifi_firstwake;
#endif

#define   HW_5G_CUSTOM_ROAM_TRIGGER_SETTING  -70  /* dBm default roam trigger 5 band , used by dhd_preinit_ioctls func*/

#ifdef HW_DNS_DHCP_PARSE

#define MAX_DOMAIN_LEN (100)

#define DHCP_SERVER_PORT    (67)
#define DHCP_CLIENT_PORT    (68)
#define DNS_SERVER_PORT     (53)

#define HWMACSTR "%02x:%02x:%02x:%02x:%02x:%02x"
#define HWMAC2STR(a) (a)[0], (a)[1], (a)[2], (a)[3], (a)[4], (a)[5]

#define DHCP_CHADDR_LEN         16
#define SERVERNAME_LEN          64
#define BOOTFILE_LEN            128

/* DHCP message type */
#define DHCP_DISCOVER       1
#define DHCP_OFFER          2
#define DHCP_REQUEST        3
#define DHCP_ACK            5
#define DHCP_NAK            6

#define DHO_PAD             0
#define DHO_IPADDRESS       50
#define DHO_MESSAGETYPE     53
#define DHO_SERVERID        54
#define DHO_END             255

struct dhcp_message {
    uint8_t op;             /* message type */
    uint8_t hwtype;         /* hardware address type */
    uint8_t hwlen;          /* hardware address length */
    uint8_t hwopcount;      /* should be zero in client message */
    uint32_t xid;           /* transaction id */
    uint16_t secs;          /* elapsed time in sec. from boot */
    uint16_t flags;
    uint32_t ciaddr;        /* (previously allocated) client IP */
    uint32_t yiaddr;        /* 'your' client IP address */
    uint32_t siaddr;        /* should be zero in client's messages */
    uint32_t giaddr;        /* should be zero in client's messages */
    uint8_t chaddr[DHCP_CHADDR_LEN];    /* client's hardware address */
    uint8_t servername[SERVERNAME_LEN]; /* server host name */
    uint8_t bootfile[BOOTFILE_LEN];     /* boot file name */
    uint32_t cookie;
    uint8_t options[0]; /* message options - cookie */
};

struct dns_message_hdr {
    uint16_t id;    /* transaction id */
    uint16_t flags; /* message future*/
    uint16_t qdcount;   /* question record count */
    uint16_t ancount;   /* answer record count */
    uint16_t nscount;   /* authority record count */
    uint16_t arcount;   /* additional record count*/
};

typedef enum __ns_qrcode {
    ns_q_request = 0, /* request */
    ns_q_response = 1, /* response */
} ns_qrcode;

typedef enum __ns_opcode {
    ns_o_query = 0,     /* Standard query. */
    ns_o_iquery = 1,    /* Inverse query (deprecated/unsupported). */
} ns_opcode;

/*
 * Currently defined response codes.
 */
typedef enum __ns_rcode {
    ns_r_noerror = 0,   /* No error occurred. */
} ns_rcode;

typedef enum __ns_type {
    ns_t_invalid = 0,   /* Cookie. */
    ns_t_a = 1,         /* Host address. */
} ns_type;

extern void hw_parse_special_ipv4_packet(uint8_t *pktdata, uint datalen);

#endif /* HW_DNS_DHCP_PARSE */

extern void get_customized_country_code_for_hw(char *country_iso_code, wl_country_t *cspec);
extern uint hw_get_bcn_timeout(void);
extern void hw_register_wifi_dsm_client(void);
extern void hw_wifi_dsm_client_notify(int dsm_id, const char *fmt, ...);
extern int hw_skip_dpc_in_suspend(void);
extern void hw_resched_dpc_ifneed(struct net_device *ndev);
#ifdef HW_PATCH_DISABLE_TCP_TIMESTAMPS
extern void hw_set_connect_status(struct net_device *ndev, int status);
#endif
extern void hw_dhd_check_and_disable_timestamps(void); /* called in ipv4/tcp_input.c */
#ifdef HW_WIFI_WAKEUP_SRC_PARSE
extern void parse_packet(struct sk_buff *skb);
#endif
#ifdef HW_LINK_COUNTERS
extern void hw_counters_hex_dump(wl_cnt_t *counters);
#endif
extern uint is_beta_user(void);
#endif
