

#ifndef _VOS_STM_H
#define _VOS_STM_H

#ifdef	__cplusplus
extern "C"{
#endif

#if (VRP_PRODUCT_GSR == VRP_YES)
typedef struct Sys_Time
{
    USHORT usYear;
    UCHAR ucMonth;  /* scope is 1 - 12 */
    UCHAR ucDate;   /* scope is 1 - 31 */
    UCHAR ucHour;   /* socpe is 0 - 23 */
    UCHAR ucMinute; /* socpe is 0 - 59 */
    UCHAR ucSecond; /* scope is 0 - 59 */
    UCHAR ucWeek;   /* scope is 1 - 7  */
    /*UCHAR ulMircoSecond;*/
}SYSTIME_S;
#endif



#define isleap(y) ( ((((y)%4)==0)&&(((y)%100)!=0)) || (((y)%400)==0) )

/*ULONG,ULONG,ULONG,ULONG*/
#define ULONG_ADD(Num1High,Num1Low,Num2High,Num2Low) \
{ \
	Num1Low   += Num2Low; \
	Num1High  += Num2High; \
	if ( Num1Low < Num2Low ) \
	{ \
		Num1High += 1; \
	} \
}

/*ULONG,ULONG,ULONG,ULONG*/
#define ULONG_SUB(Num1High,Num1Low,Num2High,Num2Low) \
{ \
	Num1High -= Num2High; \
	if ( Num1Low < Num2Low ) \
	{ \
		Num1High -= 1; \
	} \
	Num1Low -= Num2Low; \
}

/*ULONG,ULONG,ULONG,ULONG,LONG*/
#define ULONG_CMP(Num1High,Num1Low,Num2High,Num2Low,Result) \
{ \
	if ( Num1High > Num2High ) \
		Result = 1; \
	else if ( Num1High < Num2High ) \
		Result = -1; \
	else \
	{ \
		if ( Num1Low > Num2Low ) \
			Result = 1; \
		else if ( Num1Low < Num2Low ) \
			Result = -1; \
		else \
			Result = 0; \
	} \
}



#ifdef	__cplusplus
}
#endif	/* end of __cplusplus */

#endif	/* end of _VOS_STM_H_ */

