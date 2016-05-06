#ifndef _IPBIR_BN_H_
#define _IPBIR_BN_H_


#if (VRP_YES == TCPIP_IN_VRP)
#include "util/vosutil/md5.h"    /* for IPOS map*/
#else
#include "tcpip/public/dopra/md5.h"    /* for VISP map*/
#endif

#endif  /* end of _IPBIR_BN_H_ */