/************************************************************************
Copyright   : 2005-2008, Huawei Tech. Co., Ltd.
File name   : SiAppSim.h
Author      : H59254
Version     : V200R001
Date        : 2008-10-13
Description : vSIM authenticaion 头文件
History     :
History     :
1.日    期  : 2008年10月13日
  作    者  : zhuli
  修改内容  : Create
************************************************************************/

#ifndef __usimmvsimauth_H__
#define __usimmvsimauth_H__

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define AUTH_OK         0
#define AUTH_ERR        1


extern unsigned char	Rand[16];

extern unsigned char	Autn[16];


extern void RUNA3A8_V1(unsigned char key[16], unsigned char rand[16], unsigned char simoutput[12]);

extern void RUNA3A8_V2(unsigned char key[16],unsigned char randNumber[16], unsigned char output[12]);

extern void RUNA3A8_V3(unsigned char ki_key[16],unsigned char randNumber[16], unsigned char output[12]);

extern unsigned char Milenage(unsigned char *pKI, unsigned char *pOPc, unsigned char *pxRes,unsigned char *pCK, unsigned char *pIK, unsigned char *pKc);

extern void Milenage2G(unsigned char *pKI, unsigned char *pOPc,unsigned char * pRes, unsigned char *pKc);

extern unsigned long Base16Decode(char *data, unsigned long dataLen, unsigned char* dst);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* end of usimmvsimauth.h */


