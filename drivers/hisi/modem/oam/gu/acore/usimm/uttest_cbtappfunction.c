/* 头文件包含 */

#include "omnvinterface.h"
#include "CbtPpm.h"
#include "AtAppVcomInterface.h"

VOS_UINT32 USIMM_APP_FID_Init(enum VOS_INIT_PHASE_DEFINE ip);

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
VOS_VOID uttest_CBTAPPFUN_USIMM_APP_FID_Init_case1(VOS_VOID)
{
	USIMM_APP_FID_Init(VOS_IP_LOAD_CONFIG);
}

/*******************************************************************
*测试项:
*被测函数功能描述:
*预期结果：
************************* 修改记录 *********************************
#  1.日    期:
#    作    者: j00168360
#    修改内容: 新建CASE
*******************************************************************/
VOS_VOID uttest_CBTAPPFUN_USIMM_APP_FID_Init_case2(VOS_VOID)
{
	USIMM_APP_FID_Init(VOS_IP_FARMALLOC);
}
