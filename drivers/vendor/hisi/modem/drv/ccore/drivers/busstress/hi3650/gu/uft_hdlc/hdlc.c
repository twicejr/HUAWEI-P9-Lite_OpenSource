#include "hdlcv200_def_test0.h"
#include "hdlcv200_frm_test0.h"
#include <stdio.h>
#include "baseaddr.h"
#include "BasicFunc.h"
#include "hdlc.h"


void hdlcv200_test_all()
{
	
hdlcv200_def_test0();
hdlcv200_frm_test0();
#if 0
hdlcv200_def_test1();
hdlcv200_frm_test1();
hdlcv200_def_test2();
hdlcv200_frm_test2();
#endif

}
