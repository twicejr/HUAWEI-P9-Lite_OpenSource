#ifndef __ED_USER_H
#define __ED_USER_H


#if 1

#ifdef __cplusplus
    extern "C" {
#endif

#ifndef ED_WARNING_REMOVER
#define ED_WARNING_REMOVER(text)
#ifndef ED_WARNING_REMOVER_NODEFINE
#define ED_WARNING_REMOVER_NODEFINE
#endif
#endif

/* x00309227,2015/06/06,编解码方修改文件Ed_lib.c里面函数定义，将其中long更新为ED_EXLONG,
   并且从version 1.0.144之后，在Ed_data.h中ED_EXLONG被定义为int，
   但Ed_lib.c中的函数同时应用于CDMA和GSM，所以没有更新Ed_lib.c、Ed_lib.h编解码方的修改，
   同时,ED_EXLONG除common以外，只应用于CDMA，现重新定义其值为long */
#ifndef ED_EXLONG
#define ED_EXLONG long
#endif

#ifndef ED_LOCATOR
#define ED_LOCATOR unsigned int
#endif

#define CSN1C_DECLARE_CONTEXT \
	unsigned int* decodedBitsCount = NULL;\
    int localCtxNumber=pCSN1CContextSet->csn1ContextInUse;\
    assert(pCSN1CContextSet->csn1ContextInUse < pCSN1CContextSet->csn1ContextMax);\
    pCSN1CContextSet->csn1ContextInUse++; /* printf ("USING %d CONTEXTS\n", (int)pCSN1CContextSet->csn1ContextInUse); */

#define CSN1C_UNDECLARE_CONTEXT \
	if (decodedBitsCount != NULL) {(*decodedBitsCount) = (unsigned int)(CSN1C_CONTEXT_PTR->CurrOfs - BitOffset);}\
    assert(pCSN1CContextSet->csn1ContextInUse>0); \
    pCSN1CContextSet->csn1ContextInUse--; \
    assert (localCtxNumber==pCSN1CContextSet->csn1ContextInUse);

#define CSN1C_CONTEXT_PTR (pCSN1CContextSet->csn1Contexts+localCtxNumber)


#if !defined ENCODIX_CS0004 && !defined ENCODIX_CS0005
#define ED_EXTRAPARAMS_DECL , struct SCSN1CContextSet* pCSN1CContextSet
#define ED_EXTRAPARAMS_CALL , pCSN1CContextSet
#define ED_EXTRAPARAMS_CODE ED_WARNING_REMOVER(pCSN1CContextSet);
#endif

#if 0
#define ED_EXTRAPARAMS_DECL , struct SCSN1CContextSet* pCSN1CContextSet
#define ED_EXTRAPARAMS_CALL , pCSN1CContextSet
#define ED_EXTRAPARAMS_CODE ED_WARNING_REMOVER(pCSN1CContextSet);
#endif

struct SCSN1CContext;
struct SCSN1CContextSet {
    struct SCSN1CContext* csn1Contexts;
    int csn1ContextInUse;
    int csn1ContextMax;
};

/* Dummy encryption function */
extern int EDBitsToInt (const void* Source, long Offset, int Count);
extern void EDIntToBits (void* Destination, long Offset, int Source, int Count);
extern void SS0053_ENCRYPTION_FUNC_dummy (int encrypt, void* buffer, unsigned offsetInBits, unsigned lengthInOctets, int ENCRYPT_MODE, int DATA_TYPE, int SYNC0, int SYNC1);
#define SS0053_ENCRYPTION_FUNC SS0053_ENCRYPTION_FUNC_dummy

#ifdef __cplusplus
    };
#endif

#endif

#include "C.S0005.h"
#undef CSN1C_USER_CONTEXT_DATA
#include "C.S0004.h"
#undef CSN1C_USER_CONTEXT_DATA


#define CSN1C_USER_CONTEXT_DATA CS0004E_Details p_CS0004E_Details; CS0005E_Details p_CS0005E_Details; CS0005_RuntimeData CS0005_runtime;

#define CSN1C_USERTAGS      256
#define CSN1C_FIELDS        1024
#define CSN1C_STACK_SIZE    512
#define ED_LOCATOR_SET(a,b,c)

#endif
