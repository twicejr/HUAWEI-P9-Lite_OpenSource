#ifndef _IPBIR_GADS_H_
#define _IPBIR_GADS_H_

/*Modified to re-arrange IPB IR common headfile
   for VISP and IPOS, w39621, 2006-12-02*/

#if (VRP_YES == TCPIP_IN_VRP)
/* not required */                                                               /* for IPOS map*/
#else
#include "tcpip/public/vrpvos/gads_api.h"  /* for VISP map*/
#endif

#endif  /* end of _IPBIR_STANDBY_H_ */

