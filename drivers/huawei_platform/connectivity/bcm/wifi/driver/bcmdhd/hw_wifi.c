#include <linux/module.h>
#include <linux/init.h>
#include <wlioctl.h>
#include <linux/string.h>
#include <linux/errno.h>
#include <hw_wifi.h>
#include "dhd_dbg.h"
#include <wl_cfg80211.h>
#ifdef HW_WIFI_WAKEUP_SRC_PARSE
#include <linux/ip.h>
#include <net/tcp.h>
#include <net/udp.h>
#include <net/icmp.h>
#include <linux/ieee80211.h>
#include <wl_android.h>
#include <proto/bcmevent.h>
#include <bcmendian.h>
#include <linux/types.h>
#include <linux/skbuff.h>
#include <linux/ipv6.h>
#endif

#include "LLT_wifi.h"
#include <log/log_usertype/log-usertype.h>


#define HW_BCN_TIMEOUT 10

#if defined(CONFIG_BCM4343)
    #include <hw_country_code_4343.h>
#elif defined(CONFIG_BCM4339)
    #include <hw_country_code_4339.h>
#elif defined(CONFIG_BCM43455)
    #include <hw_country_code_43455.h>
#elif defined(CONFIG_BCM4359)
    #include <hw_country_code_4359.h>
#else
    #include <hw_country_code.h>
#endif //end CONFIG_BCM4343

#ifdef HW_WIFI_WAKEUP_SRC_PARSE
#define MAX_MSG_LENGTH 30
volatile bool g_wifi_firstwake = FALSE;
#define IPADDR(addr) \
        ((unsigned char*)&addr)[0], \
        ((unsigned char*)&addr)[1], \
        ((unsigned char*)&addr)[2], \
        ((unsigned char*)&addr)[3]

#define IPV6_ADDRESS_SIZEINBYTES 0x10
#define IPV6_DESTOPTS_HDR_OPTIONSIZE 0x8

struct ieee8021x_hdr {
	u8 version;
	u8 type;
	__be16 length;
};

typedef struct IPV6RoutingHeaderFormatTag
{
	uint8_t ucNextHeader;
	uint8_t ucRoutingType;
	uint8_t ucNumAddresses;
	uint8_t ucNextAddress;
	uint32_t ulReserved;
	//uint8_t aucAddressList[0];

}IPV6RoutingHeader;

typedef struct IPV6FragmentHeaderFormatTag
{
	uint8_t ucNextHeader;
	uint8_t ucReserved;
	uint16_t usFragmentOffset;
	uint32_t  ulIdentification;
}IPV6FragmentHeader;

typedef struct IPV6DestOptionsHeaderFormatTag
{
	uint8_t ucNextHeader;
	uint8_t ucHdrExtLen;
	uint8_t ucDestOptions[6];
	//uint8_t udExtDestOptions[0];
}IPV6DestOptionsHeader;

typedef struct IPV6HopByHopOptionsHeaderFormatTag
{
	uint8_t ucNextHeader;
	uint8_t ucMisc[3];
	uint32_t ulJumboPayloadLen;
}IPV6HopByHopOptionsHeader;

typedef struct IPV6AuthenticationHeaderFormatTag
{
	uint8_t ucNextHeader;
	uint8_t ucLength;
	uint16_t usReserved;
	uint32_t  ulSecurityParametersIndex;
	//uint8_t  ucAuthenticationData[0];

}IPV6AuthenticationHeader;
#endif

/* Customized Locale convertor
*  input : ISO 3166-1 country abbreviation
*  output: customized cspec
*/
void get_customized_country_code_for_hw(char *country_iso_code, wl_country_t *cspec)
{
	int size, i;

	HW_PRINT_HI("enter : %s.\n", __FUNCTION__);
	size = ARRAYSIZE(hw_translate_custom_table);

	if (cspec == 0)
		 return;

	if (size == 0)
		 return;

	HW_PRINT_HI("input country code: %s.\n", country_iso_code);
	for (i = 0; i < size; i++) {
		if (strcmp(country_iso_code, hw_translate_custom_table[i].iso_abbrev) == 0) {
			memcpy(cspec->ccode, hw_translate_custom_table[i].custom_locale, WLC_CNTRY_BUF_SZ);
			memcpy(cspec->country_abbrev, hw_translate_custom_table[i].custom_locale, WLC_CNTRY_BUF_SZ);
			cspec->rev = hw_translate_custom_table[i].custom_locale_rev;
			HW_PRINT_HI("output country code: %s, ver: %d.\n", cspec->ccode, cspec->rev);
			return;
		}
	}
	
	return;
}


uint hw_get_bcn_timeout(void)
{
	return HW_BCN_TIMEOUT;
}

static struct dsm_dev dsm_wifi = {
    .name = "dsm_wifi",
	.device_name = NULL,
	.ic_name = NULL,
	.module_name = NULL,
    .fops = NULL,
    .buff_size = 1024,
};

struct dsm_client *wifi_dsm_client = NULL;

void hw_register_wifi_dsm_client(void) {
    if(NULL == wifi_dsm_client) {
        wifi_dsm_client = dsm_register_client(&dsm_wifi);
    }
}

#define LOG_BUF_SIZE 512
void hw_wifi_dsm_client_notify(int dsm_id, const char *fmt, ...) {
    char buf[LOG_BUF_SIZE] = {0};
    va_list ap;

    va_start(ap, fmt);
    if(wifi_dsm_client && !dsm_client_ocuppy(wifi_dsm_client)) {
        if(fmt) {
            vsnprintf(buf, LOG_BUF_SIZE, fmt, ap);
            dsm_client_record(wifi_dsm_client, buf);
        }
        dsm_client_notify(wifi_dsm_client, dsm_id);
        HW_PRINT_HI("wifi dsm_client_notify success\n");
    } else {
        HW_PRINT_HI("wifi dsm_client_notify failed\n");
    }
    va_end(ap);
}

extern volatile bool hw_cfg80211_suspend;
static volatile int g_need_enable_intr = 0;
extern dhd_pub_t *hw_get_dhd_pub(struct net_device *dev);

static int wait_for_cfg80211_resume(void) {
	int wait_count = 10;
	while(wait_count > 0) {
		msleep(20);
		if(!hw_cfg80211_suspend) {
			HW_PRINT((WIFI_TAG"%s %d\n", __func__, wait_count));
			return wait_count;
		}
		wait_count--;
	}
	return 0;
}

/**
 * This function used in dhd_dpc_thread(dhd_linux.c)
 * when sdio host is in suspend state, skip this action in dpc thread
 * @return: 1 skip, 0 dont skip
 */
int hw_skip_dpc_in_suspend(void) {
	if((!hw_cfg80211_suspend) || (wait_for_cfg80211_resume() > 0)) {
		g_need_enable_intr = 0;
		return 0;
	} else {
		g_need_enable_intr = 1;
		HW_PRINT((WIFI_TAG"%s skip, cfg80211 is in suspend state\n", __func__));
		return 1;
	}
}

/**
 * This function used in wl_cfg80211_resume(wl_cfg80211.c)
 * when dpc thread is interrupted by suspend(see hw_skip_dpc_in_suspend), resched dpc again
 */
void hw_resched_dpc_ifneed(struct net_device *ndev) {
	dhd_pub_t *pub = NULL;
	if(g_need_enable_intr) {
		g_need_enable_intr = 0;
		pub = hw_get_dhd_pub(ndev);
		if(pub && pub->up) {
			HW_PRINT((WIFI_TAG"%s, resched dpc\n", __func__));
			dhd_sched_dpc(pub);
		}
	}
}

#ifdef HW_PATCH_DISABLE_TCP_TIMESTAMPS
/*  sysctl_tcp_timestamps is defined in net/ipv4/tcp_input.c
 *  here to check wlan0 network interface and
 *  when wlan0 is connected, try to disable tcp_timestamps by set it to 0.
 *  and when wlan0 is disconnected, restore to enable tcp_timestamps.
 */
static int hw_dhd_wan0_connected = 0; /* 1: wlan0 connected*/
extern int sysctl_tcp_timestamps;
void hw_set_connect_status(struct net_device *ndev, int status)
{
    struct wireless_dev *wdev = NULL;

    if (NULL == ndev) {
        HW_PRINT_HI("interface is null, skip set status.\n");
        return;
    }

    wdev = ndev_to_wdev(ndev);
    if (NL80211_IFTYPE_STATION != wdev->iftype) {
        HW_PRINT_HI("interface type is %d, skip set sta status.\n", wdev->iftype);
        return;
    }

    hw_dhd_wan0_connected = status;
    /* if wlan0 disconnect, and tcp_ts is 0, restore it to 1 */
    if (0 == hw_dhd_wan0_connected && 0 == sysctl_tcp_timestamps) {
        sysctl_tcp_timestamps = 1;
        HW_PRINT_HI("wlan0 disconnected, restore tcp_timestamps.\n");
    }
}
#endif

/* this function should only be called when tcp_timestamps err in ipv4/tcp_input.c */
void hw_dhd_check_and_disable_timestamps(void)
{
#ifdef HW_PATCH_DISABLE_TCP_TIMESTAMPS
    /* disable tcp_timestamps to 0 only when wlan0 connected.*/
    HW_PRINT_HI("check wlan0 connect status = %d.\n", hw_dhd_wan0_connected);
    if (hw_dhd_wan0_connected) {
        sysctl_tcp_timestamps = 0;
        HW_PRINT_HI("wlan0 connected, disable tcp_timestamps.\n");
    }
#endif
}

#ifdef HW_WIFI_WAKEUP_SRC_PARSE
/***************************************************************************
*Function: 	wlan_send_nl_event
*Description: 	send the port number to the userspace use uevent.
*Input: 		struct net_device *net_dev: dhd net device.
			u16 port: port number.
*Output: 	null
*Return:		null
***************************************************************************/
static void wlan_send_nl_event(struct net_device *net_dev,  u16 port)
{
	struct device* dev = NULL;
	char *uevent[2];
	char msg[MAX_MSG_LENGTH];

	dev = &(net_dev->dev);
	memset(msg, 0, sizeof(msg));
	snprintf(msg, sizeof(msg), "WIFI_WAKE_PORT=%d",port);
	HW_PRINT_HI("%s: send msg: %s\n", __FUNCTION__, msg);
	uevent[0] = msg;
	uevent[1] = NULL;
	kobject_uevent_env(&(dev->kobj), KOBJ_CHANGE, (char**)&uevent);

	return;
}

/***************************************************************************
*Function: 	parse_ipv4_packet
*Description: 	if the packet is tcp/ip type, print ip type, ip address, ip port.
*Input: 		struct sk_buff *skb
*Output: 	null
*Return:		null
***************************************************************************/
static void parse_ipv4_packet(struct sk_buff *skb)
{
	const struct iphdr *iph;
	int iphdr_len = 0;
	struct tcphdr *th;
	struct udphdr *uh;
	struct icmphdr *icmph;

	HW_PRINT_HI("receive ipv4 packet.\n");
	iph = (struct iphdr *)skb->data;
	iphdr_len = iph->ihl*4;

	HW_PRINT_HI("src ip:%d.%d.%d.%d, dst ip:%d.%d.%d.%d\n", IPADDR(iph->saddr), IPADDR(iph->daddr));
	if (iph->protocol == IPPROTO_UDP){
		uh = (struct udphdr *)(skb->data + iphdr_len);
		HW_PRINT_HI("receive UDP packet, src port:%d, dst port:%d.\n", ntohs(uh->source), ntohs(uh->dest));
		wlan_send_nl_event(skb->dev, ntohs(uh->dest));
	}else if(iph->protocol == IPPROTO_TCP){
		th = (struct tcphdr *)(skb->data + iphdr_len);
		HW_PRINT_HI("receive TCP packet, src port:%d, dst port:%d.\n", ntohs(th->source), ntohs(th->dest));
		wlan_send_nl_event(skb->dev, ntohs(th->dest));
	}else if(iph->protocol == IPPROTO_ICMP){
		icmph = (struct icmphdr *)(skb->data + iphdr_len);
		HW_PRINT_HI("receive ICMP packet, type(%d):%s, code:%d.\n", icmph->type,
			((icmph->type == 0)?"ping reply":((icmph->type == 8)?"ping request":"other icmp pkt")), icmph->code);
	}else if(iph->protocol == IPPROTO_IGMP){
		HW_PRINT_HI("receive IGMP packet.\n");
	}else{
		HW_PRINT_HI("receive other IPv4 packet.\n");
	}

	return;
}

void dump_ipv6_addr(unsigned short *addr)
{
	int i =0;

	for (i = 0; i < (IPV6_ADDRESS_SIZEINBYTES/2); i++) {
		HW_PRINT_HI(":%lx", ntohs(addr[i]));
	}
	HW_PRINT_HI("\n");
}

static uint8_t *get_next_ipv6_chain_header(uint8_t **headerscan, uint8_t *headtype, int8_t *done, uint16_t *payload_len)
{
	uint16_t next_header_offset = 0;
	uint8_t * payload_ptr = *headerscan;
	uint8_t * return_header_ptr = *headerscan;

	if(headerscan == NULL || (*payload_len == 0) || (*done)){
		return NULL;
	}
	*done = 0;

	switch(*headtype){
	case NEXTHDR_HOP:
		{
			HW_PRINT_HI("IPv6 HopByHop Header.\n");
			next_header_offset += sizeof(IPV6HopByHopOptionsHeader);
		}
		break;
	case NEXTHDR_ROUTING:
		{
			IPV6RoutingHeader *pstIpv6RoutingHeader;
			HW_PRINT_HI("IPv6 Routing Header\n");
			pstIpv6RoutingHeader = (IPV6RoutingHeader *)payload_ptr;
			next_header_offset += sizeof(IPV6RoutingHeader);
			next_header_offset += pstIpv6RoutingHeader->ucNumAddresses * IPV6_ADDRESS_SIZEINBYTES;
		}
		break;
	case NEXTHDR_FRAGMENT:
		{
			HW_PRINT_HI("IPv6 Fragmentation Header\n");
			next_header_offset += sizeof(IPV6FragmentHeader);
		}
		break;
	case NEXTHDR_DEST:
		{
			IPV6DestOptionsHeader *pstIpv6DestOptsHdr = (IPV6DestOptionsHeader *)payload_ptr;
			int nTotalOptions = pstIpv6DestOptsHdr->ucHdrExtLen;
			HW_PRINT_HI("IPv6 DestOpts Header Header\n");
			next_header_offset += sizeof(IPV6DestOptionsHeader);
			next_header_offset += nTotalOptions * IPV6_DESTOPTS_HDR_OPTIONSIZE ;
		}
		break;
	case NEXTHDR_AUTH:
		{
			IPV6AuthenticationHeader *pstIpv6AuthHdr = (IPV6AuthenticationHeader *)payload_ptr;
			int nHdrLen = pstIpv6AuthHdr->ucLength;
			HW_PRINT_HI("IPv6 Authentication Header\n");
			next_header_offset += nHdrLen * 4;
		}
		break;
	case NEXTHDR_TCP:
	case NEXTHDR_UDP:
		{
			HW_PRINT_HI("tcp/udp/icmp Header: %d.\n", *headtype);
			*done = 1;
		}
		break;
	case NEXTHDR_ICMP:
		{
			HW_PRINT_HI("icmp Header: %d.\n", *headtype);
			*done = 1;
		}
		break;
	default:
		*done = 1;
		break;
	}

	if (next_header_offset == 0) {
		HW_PRINT_HI("Receive wrong package, do not parse continuously\n");
		*done = 1;
	}

	if (*done == 0) {
		if (*payload_len <= next_header_offset) {
			*done = TRUE;
		} else {
			*headtype = *payload_ptr;
			payload_ptr += next_header_offset;
			(*payload_len) -= next_header_offset;
		}
	}

	*headerscan = payload_ptr;
	return return_header_ptr;
}

static void get_ipv6_protocal_ports(uint8_t *payload, uint16_t payload_len, uint8_t next_header, uint16_t *src_port, uint16_t *des_port)
{
	int8_t done = 0;
	uint8_t *headerscan = payload;
	uint8_t *payload_header = NULL;
	uint8_t headtype;

	if(!payload || payload_len == 0)
		return;

	headtype = next_header;
	while(!done){
		payload_header = get_next_ipv6_chain_header(&headerscan, &headtype, &done, &payload_len);
		if(done){
			if((payload_header != NULL) &&
				(headtype == NEXTHDR_TCP || headtype == NEXTHDR_UDP)){
				*src_port = *((uint16_t *)payload_header);
				*des_port = *((uint16_t *)(payload_header+2));
				HW_PRINT_HI("src_port:0x%x, des_port:0x%x.\n", ntohs(*src_port), ntohs(*des_port));
			}
			break;
		}
	}
}

static void parse_ipv6_packet(struct sk_buff *skb)
{
	struct ipv6hdr *nh;
	uint16_t src_port;
	uint16_t des_port;
	uint8_t *payload;

	nh = (struct ipv6hdr *)skb->data;
	HW_PRINT_HI("version: %d, payload length: %d, nh->nexthdr: %d. \n", nh->version, ntohs(nh->payload_len), nh->nexthdr);
	HW_PRINT_HI("ipv6 src addr: ");
	dump_ipv6_addr((unsigned short *)&(nh->saddr));
	HW_PRINT_HI("ipv6 dst addr: ");
	dump_ipv6_addr((unsigned short *)&(nh->daddr));
	payload = nh + sizeof(struct ipv6hdr);

	get_ipv6_protocal_ports(payload, nh->payload_len, nh->nexthdr, &src_port, &des_port);

	return;
}

/***************************************************************************
*Function: 	parse_arp_packet
*Description: 	if the packet if 802.11 type, print the type name and sub type name.
*Input: 		struct sk_buff *skb
*Output: 	null
*Return:		null
***************************************************************************/
static void parse_arp_packet(struct sk_buff *skb)
{
	const struct iphdr *iph;
	int iphdr_len = 0;
	struct arphdr *arp;

	iph = (struct iphdr *)skb->data;
	iphdr_len = iph->ihl*4;
	arp = (struct arphdr *)(skb->data + iphdr_len);
	HW_PRINT_HI("receive ARP packet, hardware type:%d, protocol type:%d, opcode:%d.\n", ntohs(arp->ar_hrd), ntohs(arp->ar_pro), ntohs(arp->ar_op));

	return;
}

/***************************************************************************
*Function: 	parse_8021x_packet
*Description:	if the packet if 802.1x type, print the type name and sub type name.
*Input:		struct sk_buff *skb
*Output: 	null
*Return:		null
***************************************************************************/
static void parse_8021x_packet(struct sk_buff *skb)
{
	struct ieee8021x_hdr *hdr = (struct ieee8021x_hdr *)(skb->data);

	HW_PRINT_HI("receive 802.1x frame: version:%d, type:%d, length:%d\n", hdr->version, hdr->type, ntohs(hdr->length));

	return;
}


/***************************************************************************
*Function: 	parse_packet
*Description: 	parse the packet from sdio when system waked up by wifi. identify the packet type.
*Input: 		struct sk_buff *skb
*Output: 	null
*Return:		null
***************************************************************************/
void parse_packet(struct sk_buff *skb)
{
	__be16 type;

	type = skb->protocol;
	HW_PRINT_HI(WIFI_WAKESRC_TAG"protocol type:0x%04x\n", ntohs(type));

	if(type == cpu_to_be16(ETH_P_IP)){
		parse_ipv4_packet(skb);
	}else if (type == cpu_to_be16(ETH_P_IPV6)){
		HW_PRINT_HI("receive ipv6 packet.\n");
		parse_ipv6_packet(skb);
	}else if(type == cpu_to_be16(ETH_P_ARP)){
		parse_arp_packet(skb);
	}else if(type == cpu_to_be16(ETHER_TYPE_BRCM)){ //same as ETH_P_LINK_CTL
		HW_PRINT_HI("receive bcm cust packet."); //bcm cust packet is bcm event.
	}else if(type == cpu_to_be16(ETH_P_PAE)){
		parse_8021x_packet(skb);
	}else{
		HW_PRINT_HI("receive other packet.\n");
	}

	return;
}
#endif

#ifdef HW_DNS_DHCP_PARSE
static const uint8_t *hw_dhcp_get_option(const uint8_t *opt_buff, uint32_t opt_len, uint8_t opt, int *len, int expect_len) {
    const uint8_t *p = opt_buff;
    const uint8_t *e = p + opt_len;
    uint8_t l, ol = 0;
    uint8_t o = 0;
    const uint8_t *op = NULL;
    int bl = 0;

    /* DHCP Options are in TLV format with T and L each being a single
     * byte.  In general, here we have p -> T, ol=p+1 -> L, op -> V.
     * We must make sure there is enough room to read both T and L.
     */
    while (p + 1 < e) {
        o = *p++;
        if (o == opt) {
            ol = (p + *p < e) ? *p : e - (p + 1);
            op = p + 1;
            bl += ol;
        }
        switch (o) {
        case DHO_PAD:
            continue;
        case DHO_END:
            goto exit;
        }
        l = *p++;
        p += l;
    }

exit:
    if (expect_len > 0 && bl != expect_len) {
        return NULL;    //unexpect length of value
    }
    if (len)
        *len = bl;
    if (op)
        return op;

    return NULL;
}

static int hw_dhcp_get_option_uint32(uint32_t *i, const uint8_t *opt_buff, uint32_t opt_len, uint8_t option) {
    const uint8_t *p = hw_dhcp_get_option(opt_buff, opt_len, option, NULL, sizeof(uint32_t));
    uint32_t d;

    if (!p)
        return -1;
    memcpy(&d, p, sizeof(d));
    *i = ntohl(d);
    return 0;
}

static int hw_dhcp_get_option_uint8(uint8_t *i, const uint8_t *opt_buff, uint32_t opt_len, uint8_t option) {
    const uint8_t *p = hw_dhcp_get_option(opt_buff, opt_len, option, NULL, sizeof(uint8_t));

    if (!p)
        return -1;
    if (i)
        *i = *(p);
    return 0;
}

static uint8_t get_qr_from_flag(uint16_t flag) {
    return (uint8_t)(((flag & 0x8000U) > 0)? 1 : 0);
}

static uint8_t get_opcode_from_flag(uint16_t flag) {
    return (uint8_t)((flag & 0x7400U) >> 11);
}

static uint8_t get_rcode_from_flag(uint16_t flag) {
    return (uint8_t)(flag & 0x000fU);
}

static void hw_parse_dns_query(uint8_t *msg, uint32_t msg_len) {
    uint8_t *pc = msg;
    uint8_t *pe = msg + msg_len;
    uint8_t qlen = 0;
    char domain[MAX_DOMAIN_LEN + 2] = {0};
    char *pn = domain;
    char *pne = domain + MAX_DOMAIN_LEN;

    while(pc < pe) {
        qlen = *pc++;
        if (qlen > 0) {
            if ((pc + qlen < pe) && (pn + qlen <= pne)) {
                memcpy(pn, pc, qlen);
                pn += qlen;
                *pn = '.';
                *(pn + 1) = '\0';
                pn += 1;
            }
            pc += qlen;
        } else {
            //only printf one record of query item
            break;
        }
    }
    HW_PRINT_HI("%s: domain name: %s \n", __func__, domain);
}

static void hw_parse_dns_answer(uint8_t *msg, uint16_t msg_len, uint16_t qdcount) {
    uint8_t *pc = msg;
    uint8_t *pe = msg + msg_len;
    uint8_t qlen = 0;
    uint16_t type = 0;
    uint16_t rdlen = 0;
    uint32_t ipv4 = 0;
    char domain[MAX_DOMAIN_LEN + 2] = {0};
    char domain_s[MAX_DOMAIN_LEN + 2] = {0};
    char *pn = domain;
    char *pne = domain + MAX_DOMAIN_LEN;
    //skip Questions
    while(qdcount > 0 && pc < pe) {
        qlen = *pc++;
        if (qlen > 0) {
            if ((pc + qlen < pe) && (pn + qlen <= pne)) {
                memcpy(pn, pc, qlen);
                pn += qlen;
                *pn = '.';
                *(pn + 1) = '\0';
                pn += 1;
            }
            pc += qlen;
        } else {
            pc += 4;    //class: 2 bytes, type: 2 bytes
            qdcount--;
            memcpy(domain_s, domain, MAX_DOMAIN_LEN + 2);
            pn = domain;
            pne = domain + MAX_DOMAIN_LEN;
            memset(domain, 0 , sizeof(domain));
        }
    }
    //parse Answers
    while(pc + 12 < pe) {
        pc += 2;    //name: 2 bytes;
        memcpy(&type, pc, sizeof(type));
        pc += 8;    //type, class: 2bytes, ttl: 4bytes;
        memcpy(&rdlen, pc, sizeof(rdlen));
        pc += 2;
        type = ntohs(type);
        rdlen = ntohs(rdlen);
        if (type == ns_t_a && rdlen == 4) {
            memcpy(&ipv4, pc, rdlen);
            HW_PRINT_HI("%s: domain name: %s %d.%d.%d.%d\n", __func__, domain_s, IPADDR(ipv4));
            return;
        }
        pc += rdlen;
    }
    HW_PRINT_HI("%s: domain name: %s\n", __func__, domain_s);
}

static void hw_parse_special_dns_packet(uint8_t *msg, uint32_t msg_len) {
    uint8_t qr, opcode, rcode;
    uint16_t hflag, hqdcount;
    uint32_t dns_hdr_len = sizeof(struct dns_message_hdr);
    struct dns_message_hdr *dns_hdr = NULL;

    if (dns_hdr_len >= msg_len) {
        HW_PRINT_HI("%s: invalid dns packet\n", __func__);
        return;
    }

    dns_hdr = (struct dns_message_hdr *)msg;
    hflag = ntohs(dns_hdr->flags);
    hqdcount = ntohs(dns_hdr->qdcount);
    qr = get_qr_from_flag(hflag);
    opcode = get_opcode_from_flag(hflag);
    rcode = get_rcode_from_flag(hflag);

    if (qr == ns_q_request) {
        if (opcode == ns_o_query && hqdcount > 0) {
            hw_parse_dns_query(msg + dns_hdr_len, msg_len - dns_hdr_len);
        } else {
            HW_PRINT_HI("%s: dont parse dns request pkt, opcode: %u, qd: %u\n", __func__, opcode, hqdcount);
        }
    } else if (qr == ns_q_response) {
        if (opcode == ns_o_query && opcode == ns_r_noerror) {
            hw_parse_dns_answer(msg + dns_hdr_len, msg_len - dns_hdr_len, hqdcount);
        } else {
            HW_PRINT_HI("%s: dont parse dns response pkt, opcode: %u, rcode: %u\n", __func__, opcode, rcode);
        }
    }
}

static void hw_parse_special_dhcp_packet(uint8_t *buff, uint32_t buflen, uint8_t *dst) {
    uint8_t  type = 0;
    uint32_t req_ip = 0;
    uint32_t req_srv = 0;
    uint32_t len = 0;
    struct dhcp_message *msg;
    if (buflen <= sizeof(struct dhcp_message)) {
        HW_PRINT_HI("%s: invalid dhcp packet\n", __func__);
        return;
    }
    msg = (struct dhcp_message *)buff;
    len = buflen - sizeof(struct dhcp_message);

    if (hw_dhcp_get_option_uint8(&type, msg->options, len, DHO_MESSAGETYPE) == -1) {
        HW_PRINT_HI("%s: get message type failed\n", __func__);
        return;
    }

    if (type == DHCP_DISCOVER) {
        HW_PRINT_HI("%s: type: DHCP_DISCOVER\n", __func__);
    } else if (type == DHCP_OFFER) {
        HW_PRINT_HI("%s: type: DHCP_OFFER, ip:%d.%d.%d.%d srvip:%d.%d.%d.%d MAC:" HWMACSTR "\n",
                __func__, IPADDR(msg->yiaddr), IPADDR(msg->siaddr), HWMAC2STR(dst));
    } else if (type == DHCP_REQUEST) {
        hw_dhcp_get_option_uint32(&req_ip, msg->options, len, DHO_IPADDRESS);
        hw_dhcp_get_option_uint32(&req_srv, msg->options, len, DHO_SERVERID);
        req_ip = ntoh32(req_ip);
        req_srv = ntoh32(req_srv);
        HW_PRINT_HI("%s: type: DHCP_REQUEST, ip:%d.%d.%d.%d srvip:%d.%d.%d.%d\n",
                __func__, IPADDR(req_ip), IPADDR(req_srv));
    } else if (type == DHCP_ACK) {
        HW_PRINT_HI("%s: type: DHCP_ACK MAC:" HWMACSTR "\n", __func__, HWMAC2STR(dst));
    } else if (type == DHCP_NAK) {
        HW_PRINT_HI("%s: type: DHCP_NAK MAC:" HWMACSTR "\n", __func__, HWMAC2STR(dst));
    }
}

void hw_parse_special_ipv4_packet(uint8_t *pktdata, uint datalen) {
    int iphdr_len = 0;
    const struct iphdr *iph;
    struct udphdr *uh;
    __be16 src_port;
    __be16 dst_port;
    __be16 udp_len;
    __be16 tot_len;
    uint16_t udphdr_len;
    uint8_t *uplayer_data;

    if (!is_beta_user()) {
        return;
    }
    if ((NULL == pktdata) || (datalen <= ETH_HLEN + 20)) { //invalid ipv4 packet
        return;
    }
    iph = (struct iphdr *)(pktdata + ETH_HLEN);
    iphdr_len = iph->ihl*4;
    tot_len = ntohs(iph->tot_len);

    if (datalen < (tot_len + ETH_HLEN)) {   //invalid ipv4 packet
        return;
    }

    if (iph->protocol == IPPROTO_UDP){
        uh = (struct udphdr *)(pktdata + ETH_HLEN + iphdr_len);
        src_port = ntohs(uh->source);
        dst_port = ntohs(uh->dest);
        udp_len = ntohs(uh->len);
        udphdr_len = (uint16_t)sizeof(struct udphdr);
        if (udp_len <= udphdr_len) {    //invalid udp packet
            return;
        }
        udp_len -= udphdr_len;  //skip udp header
        uplayer_data = (uint8_t *)(pktdata + ETH_HLEN + iphdr_len + udphdr_len);//skip udp header
        if (DNS_SERVER_PORT == src_port || DNS_SERVER_PORT == dst_port) {
            hw_parse_special_dns_packet(uplayer_data, udp_len);
        } else if ((DHCP_SERVER_PORT == src_port && DHCP_CLIENT_PORT == dst_port)
                || (DHCP_SERVER_PORT == dst_port && DHCP_CLIENT_PORT == src_port)) {
            hw_parse_special_dhcp_packet(uplayer_data, udp_len, pktdata + ETH_ALEN);
        }
    }
}
#endif /* HW_DNS_DHCP_PARSE */

#ifdef CONFIG_LLT_TEST

struct UT_TEST_WL  UT_hw_wifi= {
	.wait_for_cfg80211_resume = wait_for_cfg80211_resume,
};

#endif

#ifdef HW_LINK_COUNTERS
#define COUNTER_SIZE_ONE_LINE (16)
#define COUNTER_ITEM_CNT (sizeof(wl_cnt_t) / sizeof(uint32_t))
#define COUNTER_BUF_SIZE (COUNTER_SIZE_ONE_LINE * 9 + 4)

void hw_counters_hex_dump(wl_cnt_t *counters) {
    size_t i = 0;
    char strbuf[COUNTER_BUF_SIZE] = {0};
    uint32_t srcidx = 0;
    uint32_t dstidx = 0;
    uint32_t *buf = (uint32_t *)counters;

    if (!is_beta_user()) {
        return;
    }
    HW_PRINT_HI("%s:\n", __func__);
    for (srcidx = 0; srcidx < COUNTER_ITEM_CNT; srcidx++) {
        snprintf(strbuf + dstidx*9, 10, "%08x ", buf[srcidx]);
        dstidx++;
        if (dstidx >= COUNTER_SIZE_ONE_LINE) {
            HW_PRINT_HI("%s\n", strbuf);
            dstidx = 0;
            memset(strbuf, 0, COUNTER_BUF_SIZE);
        }
    }
    HW_PRINT_HI("%s\n", strbuf);
}
#endif

uint is_beta_user(void) {
    unsigned int type = get_logusertype_flag();
    if (type == BETA_USER) {
        return 1;
    }
    return 0;
}

