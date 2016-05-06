#include <intLib.h>
#include <logLib.h>
#include "armGenIntCtlr.h"

extern int armGicSetType(int irq, enum tri_mode triMode);
int armGicBase = 0x8000000;
void for_test() 
{
	logMsg("for test!\n",1,2,3,4,5,6);
}

int gic_test_case01()
{
    
    intConnect ((VOIDFUNCPTR *)100, for_test, 0);
    intEnable(100);
    *GIC_SetPend(100) = 0x10;
    return OK;
}

int gic_test_case02()
{
    int val;
    val =  *GIC_Config(80) ;
    logMsg("value = 0x%x\n",val,2,3,4,5,6);
    armGicSetType((UINT32)80, 0);
    val =  *GIC_Config(80) ;
    logMsg("value = 0x%x\n",val,2,3,4,5,6);
    armGicSetType(80, 1);
    val =  *GIC_Config(80) ;
    logMsg("value = 0x%x\n",val,2,3,4,5,6);
	return OK;
}

int gic_test_case03()
{
    int val;
    val =  *GIC_Config(10) ;
    logMsg("value = 0x%x\n",val,2,3,4,5,6);
    armGicSetType((UINT32)10, 0);
    val =  *GIC_Config(10) ;
    logMsg("value = 0x%x\n",val,2,3,4,5,6);
    armGicSetType(10, 1);
    val =  *GIC_Config(10) ;
    logMsg("value = 0x%x\n",val,2,3,4,5,6);
	return OK;
}
