
#ifndef _TWAMP_BASE_INC_H_
#define _TWAMP_BASE_INC_H_

#ifdef __cplusplus
extern "C" {
#endif



//#include "vos/vospubh/basetype.h"
//#include "tcpip/public/tcpip_debug.h"

/**********************************************************************/
/* TWAMP Extern Header Files in Non-DataCom Enviroment (VISP)           */
/**********************************************************************/
/* VOS Basic Header Files */
#include "tcpip/public/tcpip_config.h"
#include "vos/vospubh/basetype.h"
#include "vos/vospubh/vos_task.h"
#include "vos/vospubh/vos_que.h"
#include "vos/vospubh/vos_ev.h"
#include "vos/vospubh/vos_tmr.h"
#include "vos/vospubh/vos_time.h"
#include "vos/vospubh/vos_def.h"
#include "vos/vospubh/vos_util.h"
#include "v_queue.h"
#include "vos_queue.h"


/*Need to include this file as tcpip_entry.h has dependency on it*/
#include "vos/vospubh/mbuf.h"



#include "tcpip/public/entry/tcpip_entry.h"
#include "tcpip/public/tcpip_id.h"
#include "tcpip/public/tcpip_debug.h"
#include "tcpip/public/tcpip_basefun.h"

#include "tcpip/socket4/include/sock_inc.h"
#include "tcpip/public/tcpip_pub_api.h"
#include "tcpip/public/tcpip_ppi.h"
#include "tcpip/public/tcpip_ha.h"



/* Waitlist header file. */
#include "tcpip/public/dopra/waitlist.h"





extern ULONG g_ulSemForTightMods;

extern CHAR * VOS_IpAddrToStr(ULONG ulAddr, CHAR *szStr);

#ifdef __cplusplus
}
#endif

#endif

