

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


