/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:kOyQZYzjDpyGdBAEC2GaWinjiDDUykL9e8pckESWBbMVmSWkBuyJO01cTiy3TdzKxGk0oBQa
mSMf7J4FkTpfv/JzwTgKEHe/9N4yU5rqhEDGFnkG4/S4FxOOB/C/wNlmJJL1crdwYm/aqTyh
1nLqNKQ4Z++chSb8cKYj9R/hKwfIb5PaXZgg5zJO/Iq9GH5/ZLPZypqSdXm/ydycwB589950
Ei7CBKw+oauhxBKYkxf2mTywgSwT8KIeA4vH56QTqO8uihq4boCeeG7CILf02Q==*/
/*--------------------------------------------------------------------------------------------------------------------------*/

/******************************************************************************

  ???? (C), 2001-2011, ????????

******************************************************************************
    ? ? ?   : vdmv300plus_hal.h
    ? ? ?   : ??
    ?    ?   : 
    ????   : 
    ????   :
    ????   : VDMV300plus????
     

 ????   :
    1.?    ? : 2009-03-04
    ?    ?   : 
    ????   : 

******************************************************************************/

#ifndef _VDM_HAL_HEADER_
#define _VDM_HAL_HEADER_

#ifdef __cplusplus
extern "C" {
#endif

#include "decparam.h"
#include "vdm_drv.h"

/************************************************************************/
/*   vdm hal macro define                                               */
/************************************************************************/

#define   VDMHAL_OK                    (0)
#define   VDMHAL_ERR                   (-1)
#define   VDMHAL_NOT_ARRANGE           (2)
#define   VDMHAL_FUN_FALSE             (0)
#define   VDMHAL_FUN_TRUE              (1)
#define   MAX_IMG_WIDTH_IN_MB          (512)
#define   MAX_IMG_HALF_HEIGHT_IN_MB    (256)
#define   MAX_IMG_HEIGHT_IN_MB         (MAX_IMG_HALF_HEIGHT_IN_MB*2)
#define   MAX_HOR_SIZE                 (MAX_IMG_WIDTH_IN_MB*16)
#define   MAX_VER_SIZE                 (MAX_IMG_HEIGHT_IN_MB*16)
#define   MAX_MB_NUM_IN_PIC            (MAX_IMG_WIDTH_IN_MB*MAX_IMG_HEIGHT_IN_MB)
#define   MAX_FS_NUM                   (64)

// VDM MAKE REPORT
#define   VDM_RET_RIGHT                (0)
#define   VDM_RET_ERROR                (1)

#define   MAX_SLICE_SLOT_NUM           (200)

#define   FIRST_REPAIR                 (0)
#define   SECOND_REPAIR                (1)
#define   ALIGN_LEN                    (128)

#define   ONEMB_PMV_COLMB_ADDR_LEN     (20*4)   //nearly 16words/mb, now give a little more

#define   DEFAULT_EMAR_ID_VALUE        (0x161f7) 

//AXI PRPESS
#define   VDM_REG_READ_PRESS_0         (0x9f00)
#define   VDM_REG_READ_PRESS_1         (0x9f04)
#define   VDM_REG_WRITE_PRESS_0        (0x9f08)
#define   VDM_REG_WRITE_PRESS_1        (0x9f0c)
#define   VDM_REG_GLOBAL_PRESS         (0x9f10)
#define   VDM_REG_PRESS_START          (0x9f20)


/************************************************************************/
/*  Register read/write interface                                       */
/************************************************************************/
/* mfde register read/write */
#define RD_VREG( reg, dat, VdhId )               \
do {                    \
    if (VdhId < MAX_VDH_NUM)                \
    {                    \
        dat = *((volatile SINT32*)((SINT8*)g_HwMem[VdhId].pVdmRegVirAddr + reg)); \
    }                    \
    else                 \
    {                    \
        dprint(PRN_ALWS,"%s: RD_VREG but VdhId(%d) > MAX_VDH_NUM(%d)\n", __func__, VdhId, MAX_VDH_NUM); \
    }                    \
} while(0)

#define WR_VREG( reg, dat, VdhId )               \
do {                     \
    if (VdhId < MAX_VDH_NUM)                \
    {                    \
        *((volatile SINT32*)((SINT8*)g_HwMem[VdhId].pVdmRegVirAddr + reg)) = dat; \
    }                    \
    else                 \
    {                    \
        dprint(PRN_ALWS,"%s: WR_VREG but VdhId(%d) > MAX_VDH_NUM(%d)\n", __func__, VdhId, MAX_VDH_NUM); \
    }                    \
} while(0)

/* bpd register read/write */
#define RD_BPD_VREG( reg, dat )               \
do {                    \
        dat = *((volatile SINT32*)((SINT8*)g_HwMem[0].pBpdRegVirAddr + reg)); \
} while(0)

#define WR_BPD_VREG( reg, dat )               \
do {                    \
        *((volatile SINT32*)((SINT8*)g_HwMem[0].pBpdRegVirAddr + reg)) = dat; \
} while(0)

/* message pool read/write */
#define RD_MSGWORD( vir_addr, dat )          \
do {                 \
        dat = *((volatile SINT32*)((SINT8*)vir_addr));                      \
} while(0)

#define WR_MSGWORD( vir_addr, dat )          \
do {                 \
        *((volatile SINT32*)((SINT8*)(vir_addr))) = dat;                      \
} while(0)

/* condition check */
#define VDMHAL_ASSERT_RET( cond, else_print )     \
do {               \
 if( !(cond) )            \
 {               \
  dprint(PRN_FATAL,"%s d: %s\n", __func__, __LINE__,  else_print ); \
  return VDMHAL_ERR;          \
 }               \
}while(0)

#define VDMHAL_ASSERT( cond, else_print )      \
do {               \
 if( !(cond) )            \
 {               \
  dprint(PRN_FATAL,"%s: %s\n", __func__, else_print ); \
  return;             \
 }               \
}while(0)

/*#########################################################################################
       structures
 ##########################################################################################*/
typedef enum
 {
     VDM_VERSION_VDHV100 = 1,
     VDM_VERSION_VDHV200_R001,
     VDM_VERSION_VDHV200_R002,
     VDM_VERSION_VDHV200_R003,
     VDM_VERSION_VDHV400_R004,
     VDM_VERSION_BUTT
 } VDM_VERSION_E;
 
typedef enum
{
    FREQ_MODE_0 = 0,    // 148MHz
    FREQ_MODE_1,        // 118.8MHz
    FREQ_MODE_2,        // 198MHz
    FREQ_MODE_3,        // 214.2MHz
    FREQ_MODE_KEEP      // Keep Last Freq
} VDM_FREQMODE_E;
/* syntax?????? */
typedef struct
{
    SINT32    VahbStride;
    SINT32    TotalMemUsed;
    // frame buffer
    UADDR     FrameAddr[MAX_FRAME_NUM];
#ifdef VFMW_MODULE_LOWDLY_SUPPORT
    UADDR     LineNumAddr[MAX_FRAME_NUM];
#endif
    SINT32    ChromOffset;
    SINT32    ValidFrameNum;
    
    // PMV buffer
    UADDR     PMVAddr[30];//这里实际上应该为MAX_FRAME_NUM才合理，但是如果改为MAX_FRAME_NUM，编译器会报错，所以暂时改为30,等待后续更好的方案
    SINT32    HafPmvOffset;
    SINT32    ValidPMVNum;
} VDMHAL_MEM_ARRANGE_S;

typedef struct hi_FS_S
{
    SINT8    *pu8VirAddr;
    SINT8     s32RefFlag;    /* 0: ??????,1: ??????, 2: ??????, 3: ??????  */
    SINT8     s32DispFlag;   /* 0: ??????,1: ??????, 2: ??????, 3: ??????  */
    /* ??????? */
    IMAGE     stImage;

    /* ???? */
    SINT32    s32FsID;
    SINT32    s32ErrLevel;

    /* ?? */
    UADDR     s32PhyAddr;

} FS_S;


/* ??? */
typedef struct hiFS_POOL_S
{
    FS_S      stFrameStore[MAX_FS_NUM];
    SINT32    s32ValidFsNum;
    /* ??? */
    SINT32    s32FrameWidth;
    SINT32    s32FrameHeight;
    SINT32    s32FrameStride;
} FS_POOL_S;


#define    MPEG2_DUMMY_BITS              24     // 40

#define    SHORT_HEADER_ID       1
#define    NON_SHORT_HEADER_ID   2
#define RSHIFT(a,b) ( (a)>0 ? (((a) + ((1<<(b))>>1))>>(b)) : (((a) + ((1<<(b))>>1)-1)>>(b)))

/* Filter strength tables */
/* default strength specified by RV_Default_Deblocking_Strength (0) */
#define RV8_Default_Deblocking_Strength     0

/* Filter strength tables */
/* default strength specified by RV_Default_Deblocking_Strength (0) */
#define RV9_Default_Deblocking_Strength     0



typedef struct hiVDMHAL_FUN_PTR_S
{
    /*VDM_DRV*/
    VOID   (*pfun_VDMDRV_OpenHardware)(SINT32 VdhId);
	VOID   (*pfun_VDMDRV_CloseHardware)(SINT32 VdhId);
    VOID   (*pfun_VDMDRV_ResetClock)(VOID);	
    VOID   (*pfun_SCDDRV_OpenHardware)(VOID);	
    VOID   (*pfun_SCDDRV_CloseHardware)(VOID);	
    VOID   (*pfun_BPDDRV_OpenHardware)(VOID);	
    VOID   (*pfun_BPDDRV_CloseHardware)(VOID);	
	/*VDM_HAL*/
    VOID   (*pfun_VDMHAL_GetCharacter)(VOID);	
    SINT32 (*pfun_VDMHAL_GetHalMemSize)(VOID);
    SINT32 (*pfun_VDMHAL_OpenHAL)(VDMHAL_OPENPARAM_S *pOpenParam);
    VOID   (*pfun_VDMHAL_CloseHAL)(SINT32 VdhId);
    SINT32 (*pfun_VDMHAL_ArrangeMem)( UADDR  MemAddr, SINT32 MemSize, SINT32 Width, SINT32 Height, SINT32 PmvNum, SINT32 FrameNum, SINT32 ChanID, VDMHAL_MEM_ARRANGE_S *pVdmMemArrange );
	VOID   (*pfun_VDMHAL_ResetVdm)( SINT32 VdhId );
	VOID   (*pfun_VDMHAL_GlbReset)( VOID );
    VOID   (*pfun_VDMHAL_ClearIntState)( SINT32 VdhId );
    VOID   (*pfun_VDMHAL_MaskInt)( SINT32 VdhId );
    VOID   (*pfun_VDMHAL_EnableInt)( SINT32 VdhId );	
    SINT32 (*pfun_VDMHAL_CheckReg)(REG_ID_E reg_id, SINT32 VdhId);	
    VOID   (*pfun_VDMHAL_StartHwRepair)(SINT32 VdhId);
    VOID   (*pfun_VDMHAL_StartHwDecode)(SINT32 VdhId);
    SINT32 (*pfun_VDMHAL_PrepareDec)( VID_STD_E VidStd, VOID *pDecParam, SINT32 VdhId );
    SINT32 (*pfun_VDMHAL_IsVdmReady)(SINT32 VdhId);
    SINT32 (*pfun_VDMHAL_IsVdmRun)(SINT32 VdhId);
    SINT32 (*pfun_VDMHAL_PrepareRepair)( VID_STD_E VidStd, VOID *pDecParam, SINT32 RepairTime, SINT32 VdhId );
    SINT32 (*pfun_VDMHAL_MakeDecReport)(MAKE_DEC_REPORT_S *pMakeDecReport);
    SINT32 (*pfun_VDMHAL_BackupInfo)(BACKUP_INFO_S *pBackUpInfo);
    VOID   (*pfun_VDMHAL_WriteScdEMARID)(VOID);
}VDMHAL_FUN_PTR_S;

extern VDMHAL_FUN_PTR_S g_vdm_hal_fun_ptr;

#define VDMDRV_OpenHardware(VdhId) \
        g_vdm_hal_fun_ptr.pfun_VDMDRV_OpenHardware(VdhId)

#define VDMDRV_CloseHardware(VdhId) \
        g_vdm_hal_fun_ptr.pfun_VDMDRV_CloseHardware(VdhId)
    
#define VDMDRV_ResetClock() \
        g_vdm_hal_fun_ptr.pfun_VDMDRV_ResetClock()
            
#define BPDDRV_OpenHardware() \
		g_vdm_hal_fun_ptr.pfun_BPDDRV_OpenHardware()

#define BPDDRV_CloseHardware() \
		g_vdm_hal_fun_ptr.pfun_BPDDRV_CloseHardware()

#define SCDDRV_OpenHardware() \
        g_vdm_hal_fun_ptr.pfun_SCDDRV_OpenHardware()

#define SCDDRV_CloseHardware() \
        g_vdm_hal_fun_ptr.pfun_SCDDRV_CloseHardware()
  
#define VDMHAL_CloseHAL(VdhId) \
        g_vdm_hal_fun_ptr.pfun_VDMHAL_CloseHAL(VdhId)

#define VDMHAL_ResetVdm(VdhId) \
        g_vdm_hal_fun_ptr.pfun_VDMHAL_ResetVdm(VdhId)

#define VDMHAL_GlbReset() \
        g_vdm_hal_fun_ptr.pfun_VDMHAL_GlbReset()
    
#define VDMHAL_ClearIntState(VdhId) \
        g_vdm_hal_fun_ptr.pfun_VDMHAL_ClearIntState(VdhId)
    
#define VDMHAL_MaskInt(VdhId) \
        g_vdm_hal_fun_ptr.pfun_VDMHAL_MaskInt(VdhId)
    
#define VDMHAL_EnableInt(VdhId) \
        g_vdm_hal_fun_ptr.pfun_VDMHAL_EnableInt(VdhId)

#define VDMHAL_StartHwRepair(VdhId) \
        g_vdm_hal_fun_ptr.pfun_VDMHAL_StartHwRepair(VdhId)

#define VDMHAL_StartHwDecode(VdhId) \
        g_vdm_hal_fun_ptr.pfun_VDMHAL_StartHwDecode(VdhId)

#define VDMHAL_MakeDecReport(pMakeDecReport) \
        g_vdm_hal_fun_ptr.pfun_VDMHAL_MakeDecReport(pMakeDecReport)
            
#define VDMHAL_BackupInfo(pBackUpInfo) \
        g_vdm_hal_fun_ptr.pfun_VDMHAL_BackupInfo(pBackUpInfo)
     
#define VDMHAL_WriteScdEMARID() \
        g_vdm_hal_fun_ptr.pfun_VDMHAL_WriteScdEMARID()

#define VDMHAL_GetCharacter() \
		g_vdm_hal_fun_ptr.pfun_VDMHAL_GetCharacter()

#define VDMHAL_GetHalMemSize() \
		g_vdm_hal_fun_ptr.pfun_VDMHAL_GetHalMemSize()

#define VDMHAL_OpenHAL(pOpenParam) \
		g_vdm_hal_fun_ptr.pfun_VDMHAL_OpenHAL(pOpenParam)

#define VDMHAL_ArrangeMem( MemAddr, MemSize, Width, Height, PmvNum, FrameNum, eFlag, pVdmMemArrange ) \
		g_vdm_hal_fun_ptr.pfun_VDMHAL_ArrangeMem(MemAddr, MemSize, Width, Height, PmvNum, FrameNum, eFlag, pVdmMemArrange)

#define VDMHAL_CheckReg(reg_id, VdhId) \
		g_vdm_hal_fun_ptr.pfun_VDMHAL_CheckReg(reg_id, VdhId)

#define VDMHAL_PrepareDec(VidStd, pDecParam, VdhId) \
		g_vdm_hal_fun_ptr.pfun_VDMHAL_PrepareDec(VidStd, pDecParam, VdhId)

#define VDMHAL_IsVdmReady(VdhId) \
		g_vdm_hal_fun_ptr.pfun_VDMHAL_IsVdmReady(VdhId)

#define VDMHAL_IsVdmRun(VdhId) \
		g_vdm_hal_fun_ptr.pfun_VDMHAL_IsVdmRun(VdhId)

#define VDMHAL_PrepareRepair(VidStd, pDecParam, RepairTime, VdhId) \
		g_vdm_hal_fun_ptr.pfun_VDMHAL_PrepareRepair(VidStd, pDecParam, RepairTime, VdhId)

#ifdef __cplusplus
}
#endif


#endif
