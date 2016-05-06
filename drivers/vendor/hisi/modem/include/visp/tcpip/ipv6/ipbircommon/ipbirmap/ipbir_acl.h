#ifndef _IPBIR_ACL_H_
#define _IPBIR_ACL_H_

/*Modified to re-arrange IPB IR common headfile
   for VISP and IPOS, w39621, 2006-12-02*/

#if (VRP_YES == TCPIP_IN_VRP)
#include "ipbircommon/ipbirmap/ipos/ipbir_ipos_acl_map.h"    /* for IPOS map*/
#else
#include "ipbircommon/ipbirmap/visp/ipbir_visp_acl_map.h"    /* for VISP map*/
#endif

#endif  /* end of _IPBIR_ACL_H_ */

