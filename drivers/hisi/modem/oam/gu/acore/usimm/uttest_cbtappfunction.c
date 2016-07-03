/* 头文件包含 */

#include "omnvinterface.h"
#include "CbtPpm.h"
#include "AtAppVcomInterface.h"

VOS_UINT32 USIMM_APP_FID_Init(enum VOS_INIT_PHASE_DEFINE ip);


VOS_VOID uttest_CBTAPPFUN_USIMM_APP_FID_Init_case1(VOS_VOID)
{
	USIMM_APP_FID_Init(VOS_IP_LOAD_CONFIG);
}


VOS_VOID uttest_CBTAPPFUN_USIMM_APP_FID_Init_case2(VOS_VOID)
{
	USIMM_APP_FID_Init(VOS_IP_FARMALLOC);
}
