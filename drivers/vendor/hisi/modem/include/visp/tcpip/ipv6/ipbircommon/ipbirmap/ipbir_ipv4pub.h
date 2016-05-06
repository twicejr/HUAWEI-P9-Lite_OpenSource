
#ifndef _IPBIR_IPV4PUB_H_
#define _IPBIR_IPV4PUB_H_

/*Modified to re-arrange IPB IR common headfile
    for VISP and IPOS, w39621, 2006-12-02*/

#if (VRP_YES == TCPIP_IN_VRP)
#include "common/ipos/adp/ip_pub.h"           /* for IPOS */
#else
#include "common/visp/VISP_IR_IP4PUB.h"   /* for VISP */
#endif

#endif  /* end of _IPBIR_IPV4PUB_H_ */

