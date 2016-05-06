#ifndef _WIFI_TCP_STATISTICS_
#define _WIFI_TCP_STATISTICS_

void wifi_update_rtt(unsigned int rtt, struct sock *sk);
void wifi_IncrSendSegs( struct sock *sk, int count) ;
void wifi_IncrRecvSegs( struct sock *sk, int count);
void wifi_IncrReSendSegs( struct sock *sk, int count);
void wifi_IncrErrSegs( struct sock *sk, int count);
int wifi_tcp_init_proc(struct net *net);
void wifi_IncrRstSegs( struct sock *sk, int count);
void wifi_IncrEstabliseRstSegs( struct sock *sk, int count) ;
void wifi_IncrRcvDupAcksSegs( struct sock *sk, int count);
int wifi_is_on (void);
#endif

