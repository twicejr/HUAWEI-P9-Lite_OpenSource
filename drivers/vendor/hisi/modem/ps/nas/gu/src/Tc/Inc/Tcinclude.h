/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : TcInclude.h
  Description  : TC TASK使用的全部include头文件
  History:
      1.  张志勇      2004.05.13   新规作成
      2.  L47619      2005.11.26   问题单: A32D00767
      3.  L47619      2006.04.12   问题单: A32D08523
*******************************************************************************/
#ifndef _TC_INCLUDE_H_
#define _TC_INCLUDE_H_

#include "PsTypeDef.h"
#include "product_config.h"
#include "Nasrrcinterface.h"

#include "pscfg.h"

#include "TcNasinterface.h"
#include "Tcext.h"
#include "Tcresourceinfo.h"

#include "GtmTcInterface.h"

#include "TcRfaInterface.h"


#include "tracelevel.h"

#include "NasRlcInterface.h"

/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
#include "MsccMmcInterface.h"
/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

#include "NasNvInterface.h"


#endif
