


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "nvim_internalfunc.h"
#include "mdrv.h"
#include "NvIdList.h"

#if (VOS_OS_VER == VOS_LINUX)
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/kallsyms.h>
#include <linux/semaphore.h>
#include <asm/uaccess.h>
#endif

#if (VOS_RTOSCK == VOS_OS_VER)
#include "sre_task.h"
#endif
/* Macro of log */
/*lint -e767 修改人:蒋开波 00105005;检视人:徐铖 51137;原因:Log打印 */
#define    THIS_FILE_ID        PS_FILE_ID_NVIM_COMMFUNC_C
/*lint +e767 修改人:蒋开波 00105005;检视人:徐铖 51137; */

VOS_UINT32                g_ulCFDNvFileId  = 0xFFFFFFFF;

VOS_UINT32                g_ulRecordNvFlag = 0;

#if(VOS_WIN32 == VOS_OS_VER)
VOS_CHAR                  g_acNvAcpuWriteSlicePath[] = ".\\yaffs0\\A_NvWriteSlice.bin";
VOS_CHAR                  g_acNvCcpuWriteSlicePath[] = ".\\yaffs0\\C_NvWriteSlice.bin";

#else

VOS_CHAR                  g_acNvAcpuWriteSlicePath[] = "/mnvm2:0/A_NvWriteSlice.bin";
VOS_CHAR                  g_acNvCcpuWriteSlicePath[] = "/mnvm2:0/C_NvWriteSlice.bin";

#endif

/*****************************************************************************
 函 数 名  : NV_RecordNvWriteSlice
 功能描述  : 记录Nv id 写 Slice值
 输入参数  : usNvId         : Nv id
             ulNvWriteSlice : 写入Nv id 的slice值

 输出参数  : 无
 返 回 值  : VOS_UINT32

 修改历史      :
  1.日    期   : 2013年7月11日
    作    者   : d00212987
    修改内容   : 新增
*****************************************************************************/
VOS_VOID NV_RecordNvWriteSlice(VOS_UINT16 usNvId, VOS_UINT32 ulNvWriteSlice)
{
    FILE                               *pFIle;
    NV_ID_OPERATE_Slice_STRU            stNvIdWriteSlice;
    VOS_UINT32                          ulLength;

    /* 写标记开关尚未开启，不用写入 */
    if (NV_ID_WRITE_SLICE_RECORD != g_ulRecordNvFlag)
    {
        return ;
    }

#if( VOS_LINUX == VOS_OS_VER )
    pFIle = NV_File_Open(g_acNvAcpuWriteSlicePath, NV_FILE_OPEN_MODE_APEND);

#else
    pFIle = NV_File_Open(g_acNvCcpuWriteSlicePath, NV_FILE_OPEN_MODE_APEND);

#endif

    if (VOS_NULL_PTR == pFIle)
    {
        return ;
    }

    /* 获取文件大小 */
    NV_File_Seek(pFIle, 0, NV_FILE_SEEK_END);

    ulLength = (VOS_UINT32)NV_File_Tell(pFIle);

    /* 超过 100k,不再记录 */
    if ((ulLength + sizeof(stNvIdWriteSlice)) > NV_WRITE_SLICE_RECORD_SIZE)
    {
        NV_File_Close(pFIle);

        return ;
    }

    NV_File_Seek(pFIle, 0, NV_FILE_SEEK_SET);

    stNvIdWriteSlice.ulFlag           = NV_ID_WRITE_SLICE_RECORD;
    stNvIdWriteSlice.usNvId           = usNvId;
    stNvIdWriteSlice.ulNvOperateSlice = ulNvWriteSlice;

    NV_File_Write((VOS_VOID *)&stNvIdWriteSlice, sizeof(stNvIdWriteSlice), 1, pFIle);

    NV_File_Close(pFIle);

    return ;
 }

/*************************************************
Function   : NV_SetAreaAccessable
Description: 对内存区域进行写保护
Input      :
Return     : Ok or Err.
Other      :
Auther     : H59254
*************************************************/
VOS_VOID NV_SetAreaAccessable(NV_AREA_ACCESS_CTRL_ENUM_UINT32 ulCtrlFlag)
{
#if 0  /* DSP 上移后 NV读写保护需要关闭中断近1ms，而DSP响应中断需640μs，所以把NV保护先屏蔽 */
    VOS_INT lLock = 0;

    lLock = VOS_SplIMP();

    DRV_VM_ENABLE(0);

    /*lint -e40 -e655 修改人:甘兰;检视人:徐铖 51137;原因:使用VxWorks操作系统定义影响PCLINT */
    if(NV_AREA_WRITABLE == ulCtrlFlag)
    {
        DRV_VM_STATESET(0, NV_MAGICNUM_ADDR, NV_BUFFER_SIZE, MMU_ATTR_PROT_MSK, VM_STATE_WRITABLE);
    }
    else
    {
        DRV_VM_STATESET(0, NV_MAGICNUM_ADDR, NV_BUFFER_SIZE, MMU_ATTR_PROT_MSK, VM_STATE_WRITABLE_NOT);
    }
    /*lint +e40 -e655 修改人:甘兰;检视人:徐铖 51137;原因:使用VxWorks操作系统定义影响PCLINT */

    DRV_VM_ENABLE(1);

    VOS_Splx(lLock);
#endif
    return;
}

/*****************************************************************************
Function   : NVIM_MemCpy
Description: Copy the NV Data from share memory, but no check the input parameter
Input      : Dest: dest memory
             Src : src memory
             ulnbytes : data length
Return     : NULL
Other      :
*****************************************************************************/
VOS_VOID NVIM_MemCpy( VOS_VOID * Dest, const VOS_VOID * Src,  VOS_UINT32 ulnbytes )
{
    VOS_UINT8 *tmp = (VOS_UINT8 *)Dest;
    volatile VOS_UINT8 *s = (volatile VOS_UINT8 *)Src;

    while (ulnbytes--)
    {
        *tmp++ = *s++;
    }

    return;
}

/*****************************************************************************
Function   : NV_MemDump
Description: Copy the NV Data from share memory to EXC memory
Input      : ulErrorNO: The EXC reason
             ulFileID: file id
             usLineNo: Line NO.
             pData: Save the EXC data
             ulDataLen: Save the EXC data length
Return     : NULL
Other      :
*****************************************************************************/

VOS_VOID NV_MemDump(VOS_UINT32 ulErrorNO, VOS_UINT32 ulFileID,VOS_INT32 ulLineNo,VOS_VOID *pData, VOS_UINT32 ulDataLen)
{
    VOS_UINT32          ulTotalSize = VOS_DUMP_MEM_TOTAL_SIZE;
    VOS_UINT32          *pulDumpBuffer;

    /*lint -e534*/
    VOS_TaskLock();
    /*lint +e534*/

    pulDumpBuffer = (VOS_UINT32*)mdrv_om_register_field(0, NULL, NULL,NULL, VOS_DUMP_MEM_TOTAL_SIZE, 0);

    if (VOS_NULL_PTR == pulDumpBuffer)
    {
        mdrv_om_system_error((VOS_INT)ulErrorNO, (VOS_INT)ulFileID,
                             (VOS_INT)ulLineNo, (VOS_CHAR *)pData, (VOS_INT)ulDataLen);

        return;
    }

    /*lint -e534*/
    VOS_MemSet(pulDumpBuffer, 0, VOS_DUMP_MEM_TOTAL_SIZE);
    /*lint +e534*/

    *pulDumpBuffer++ = mdrv_timer_get_normal_timestamp();
    *pulDumpBuffer++ = g_ulNVInitStartSlice;
    *pulDumpBuffer++ = g_ulNVInitEndSlice;

    ulTotalSize -= sizeof(VOS_UINT32)*3;    /*偏移3 个位置用于保存时间等信息*/

    NVIM_MemCpy(pulDumpBuffer, (VOS_VOID*)NV_MAGICNUM_ADDR, ulTotalSize);

    mdrv_om_system_error(NV_MEMCPY_PARA_ERROR, (VOS_INT)ulFileID,
                         (VOS_INT)ulLineNo, (VOS_CHAR *)pData, (VOS_INT)ulDataLen);

    return;
}

/*****************************************************************************
Function   : NV_MemCpy
Description: Copy the NV Data from share memory, Check the input parameter
Input      : Dest: dest memory
             Src : src memory
             ulnbytes : data length
             ulFileID: file id
             usLineNo: Line NO.
Return     : NULL
Other      :
*****************************************************************************/
VOS_VOID NV_MemCpy( VOS_VOID * Dest, const VOS_VOID * Src,  VOS_UINT32 ulnbytes, VOS_UINT32 ulFileID, VOS_INT32 usLineNo )
{
    VOS_UINT_PTR aulExcInfo[2];

    if ( ((VOS_UINT_PTR)Src < NV_MAGICNUM_ADDR)                                  /*小于NV共享缓冲区的起始地址*/
        ||((VOS_UINT_PTR)Src > (NV_MAGICNUM_ADDR+NV_BUFFER_SIZE))                   /*大于于NV共享缓冲区的终结地址*/
        ||(((VOS_UINT_PTR)Src+ulnbytes) > (VOS_UINT_PTR)(NV_MAGICNUM_ADDR+NV_BUFFER_SIZE)) )      /*数据内容大于于NV共享缓冲区的终结地址*/
    {
        /*lint -e534*/
        LogPrint4("ERROR:NV_MemCpy big:file %d, l %d, Src is %p, Len is %d.\r\n",
                    (VOS_INT)ulFileID, (VOS_INT)usLineNo,  Src, (VOS_INT)ulnbytes);
        /*lint +e534*/

        aulExcInfo[0] = (VOS_UINT_PTR)Src;
        aulExcInfo[1] = (VOS_UINT_PTR)ulnbytes;

        NV_MemDump(NV_MEMCPY_PARA_ERROR, ulFileID, usLineNo, aulExcInfo, sizeof(aulExcInfo));

        return;
    }

    NVIM_MemCpy(Dest, Src, ulnbytes);

    return;
}

/*****************************************************************************
Function   : NV_Ctrl_File_Search_InMemory
Description: Find NV ID info. from the NV Control File
Input      : VOS_UINT16 usID -> NV ID
             NV_FILE_LIST_INFO_STRU *pstFileListInfo -> File List info struct
             NV_REFERENCE_DATA_INFO_STRU *pstNvIdInfo -> NV Id info struct
Return     : Ok or Err.
Other      :
*****************************************************************************/
VOS_UINT32 NV_Ctrl_File_Search_InMemory(VOS_UINT16                  usID,
                                                NV_CONTROL_FILE_INFO_STRU   *pstNVCtrlInfo,
                                                NV_FILE_LIST_INFO_STRU      *pstFileListInfo,
                                                NV_REFERENCE_DATA_INFO_STRU *pstNvIdInfo)
{
    VOS_UINT32 ulLow;
    VOS_UINT32 ulHigh;
    VOS_UINT32 ulMid;
    VOS_UINT32 ulOffset;
    VOS_CHAR   *pfileContent;

    if(VOS_NULL_PTR == pstNVCtrlInfo)
    {
        /*lint -e534*/
        LogPrint("Acpu NV_Ctrl_File_Search_InMemory: g_pstAcpuNVCtrlInfo is NULL");
        /*lint +e534*/

        NV_MemDump(NV_ACPU_GOBAL_ERROR, VOS_FILE_ID, __LINE__ , &usID, sizeof(VOS_UINT16));

        return VOS_ERR;
    }

    pfileContent = (VOS_CHAR *)pstNVCtrlInfo;

    /* Get total ID Num */
    ulHigh = pstNVCtrlInfo->ulNvRefCount;
    ulLow  = 1;

    /* Binary Search */
    while(ulLow <= ulHigh)
    {
        ulMid = (ulLow + ulHigh)/2;

        /* Seek the fp to the beginning of ulMid ID */
        ulOffset = sizeof(NV_CONTROL_FILE_INFO_STRU) +
                        (sizeof(NV_FILE_LIST_INFO_STRU)*(pstNVCtrlInfo->ulFileListNum))
                        +(sizeof(NV_REFERENCE_DATA_INFO_STRU)*(ulMid-1));

        /* Get the Id info of the ulMid ID */
        NVIM_MemCpy(pstNvIdInfo, pfileContent + ulOffset, sizeof(NV_REFERENCE_DATA_INFO_STRU));

        if(usID < pstNvIdInfo->usNvId)
        {
            ulHigh = ulMid - 1;
        }
        else if(usID > pstNvIdInfo->usNvId)
        {
            ulLow = ulMid + 1;
        }
        else
        {
            /* Get the file info of this ID */
            ulOffset = sizeof(NV_CONTROL_FILE_INFO_STRU) +
                                (sizeof(NV_FILE_LIST_INFO_STRU)* (pstNvIdInfo->usFileId-1));

            NVIM_MemCpy(pstFileListInfo, pfileContent + ulOffset, sizeof(NV_FILE_LIST_INFO_STRU));

            return VOS_OK;
         }
    }

    /* ID not exist */
    return VOS_ERR;
}

/*****************************************************************************
Function   : NV_GetLength
Description: Get NV length from the file without Auth.
Input      : VOS_UINT16 usID -> NV ID
             VOS_UINT32 *pulLength -> buffer to save NV len.
Return     : Ok or Err.
Other      :
*****************************************************************************/
VOS_UINT32 NV_GetLength(VOS_UINT16 usID, VOS_UINT32 *pulLength)
{
    NV_FILE_LIST_INFO_STRU      stFileListInfo;
    NV_REFERENCE_DATA_INFO_STRU stNvIdInfo;

    if( VOS_NULL_PTR == pulLength)
    {
        /* Buffer is Null */
        PS_LOG(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,
                "NV_GetLength:The Buffer is Null.\n");
        return NV_BUFFER_NOT_EXIST;
    }

    if(VOS_OK != NV_Ctrl_File_Search_InMemory(usID,g_pstNVDataBuf,&stFileListInfo,&stNvIdInfo))
    {
        /* ID not exist */
        PS_LOG1(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,
                "NV_GetLength:NV ID not exist.\n",usID);
        return NV_ID_NOT_EXIST;
    }

    *pulLength = (VOS_UINT32)(stNvIdInfo.usNvLength);

    return NV_OK;
}

/*****************************************************************************
Function   : NV_Get16BitLength
Description: Get NV length from the file without Auth for BeiJing.
Input      : VOS_UINT16 usID -> NV ID
             VOS_UINT16 *pusLength -> buffer to save NV len.
Return     : Ok or Err.
Other      :
*****************************************************************************/
VOS_UINT32 NV_Get16BitLength(VOS_UINT16 usID, VOS_UINT16 *pusLength)
{
    VOS_UINT32                          ulLength;
    VOS_UINT32                          ulResult;

    ulResult = NV_GetLength(usID, &ulLength);
    if (NV_OK != ulResult)
    {
        return ulResult;
    }

    *pusLength = (VOS_UINT16)ulLength;

    return NV_OK;
}

/*****************************************************************************
 函 数 名  : NV_NvIdCheck
 功能描述  : NV ID 合法性检查
 输入参数  : usID:     NV ID
             ulOffset: 相对正常NV偏移位置,如需要读取正常NV,偏移量为0
             pItem:    存放NV buffer
             ulLength: 操作 NV 长度

 输出参数  : pstNvIdReturnInfo
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年03月13日
    作    者   : d00212987
    修改内容   : 代码优化

*****************************************************************************/
VOS_UINT32 NV_NvIdCheck(MODEM_ID_ENUM_UINT16               enModemID,
                        VOS_UINT16                              usID,
                        VOS_UINT32                              ulOffset,
                        VOS_VOID                               *pItem,
                        VOS_UINT32                              ulLength,
                        NV_ID_RETUEN_INFO_STRU                 *pstNvIdReturnInfo)
{
    NV_FILE_LIST_INFO_STRU              stFileListInfo;
    NV_REFERENCE_DATA_INFO_STRU         stNvIdInfo;

    if(MODEM_ID_BUTT <= enModemID)
    {
        PS_LOG2(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,
                "NV_NvIdCheck:The Modem ID is too Large. Modem ID is, NV id is:\n", enModemID, usID);
        return NV_MODEM_ID_ERR;
    }

    if ((VOS_NULL_PTR == pItem)||(0 == ulLength))
    {
        /* Buffer is Null */
        PS_LOG1(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,
                "NV_NvIdCheck:The Buffer is Null. nv is:\n", usID);
        return NV_BUFFER_NOT_EXIST;
    }

    /* Not Init  */
    if (0 == g_astNvFileHandle[0].ulSize)
    {
        /* Not Init */
        PS_LOG1(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,
                "NV_NvIdCheck:NV not init.\n", usID);

        return NV_NOT_INIT;
    }

    if (VOS_OK != NV_Ctrl_File_Search_InMemory(usID, g_pstNVDataBuf, &stFileListInfo, &stNvIdInfo))
    {
        /* ID not exist */
        PS_LOG1(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,
                "NV_NvIdCheck:NV ID not exist. nv id is:\n", usID);
        return NV_ID_NOT_EXIST;
    }

    if ((stNvIdInfo.usNvLength < ulOffset)||
            (ulLength > (VOS_UINT32)(stNvIdInfo.usNvLength- ulOffset)))
    {
        /* Offset large than NV data len. or buffer len. large than remain NV data */
        PS_LOG1(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,
                "NV_NvIdCheck:The Buffer is Err. nv id is:\n", usID);
        return NV_PART_DATA_ERR;
    }

    NVIM_MemCpy(pstNvIdReturnInfo->aucFileName, stFileListInfo.aucFileName,sizeof(stFileListInfo.aucFileName));

    pstNvIdReturnInfo->usFileId     = (VOS_UINT16)stFileListInfo.ulFileId;
    pstNvIdReturnInfo->ucModemNum   = stNvIdInfo.ucModemNum;
    pstNvIdReturnInfo->usProperty   = stNvIdInfo.usProperty;

    /* 可以按照输入参数读取多份中的指定数据 */
    if((enModemID + 1) <= stNvIdInfo.ucModemNum)
    {
        /* 文件中NV数据写入的偏移量 */
        pstNvIdReturnInfo->ulNvOffset = stNvIdInfo.ulNvOffset
                                        + (enModemID * stNvIdInfo.usNvLength)
                                        + ulOffset;

        /* 缓存中的偏移量 = XXNV.bin在缓存中的偏移量 + NVID在XXNV.bin中的偏移量 */
        /*ulFileId是从1起始累加 */
        pstNvIdReturnInfo->ulTotalOffset = (g_astNvFileHandle[stNvIdInfo.usFileId].ulOffset
                                            + stNvIdInfo.ulNvOffset)
                                            + (enModemID * stNvIdInfo.usNvLength)
                                            + ulOffset;
    }
    else    /* 只能读取第一份数据 */
    {
        pstNvIdReturnInfo->ulNvOffset = stNvIdInfo.ulNvOffset + ulOffset;

        /* 缓存中的偏移量 = XXNV.bin在缓存中的偏移量 + NVID在XXNV.bin中的偏移量 + ulOffset */
        pstNvIdReturnInfo->ulTotalOffset = g_astNvFileHandle[stNvIdInfo.usFileId].ulOffset
                                            + stNvIdInfo.ulNvOffset
                                            + ulOffset;   /*ulFileId是从1起始累加 */
    }


    return NV_OK;
}

/*****************************************************************************
 函 数 名  : NV_WriteDataToFile
 功能描述  : NV 文件写入
 输入参数  : pItem:          写内容
             ulLength:       内容长度
             ulWriteOffset:  写指针偏移量
 输出参数  :
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年05月24日
    作    者   : d00212987
    修改内容   : V7R1C50 Flashless PhaseII项目新增函数
  2.日    期   : 2013年03月13日
    作    者   : d00212987
    修改内容   : 代码优化
*****************************************************************************/
VOS_UINT32 NV_WriteDataToFile(
    FILE                               *fp,
    VOS_VOID                           *pItem,
    VOS_UINT32                          ulLength,
    VOS_INT32                           lWriteOffset
)
{
    if (VOS_NULL_PTR == fp)
    {
        PS_LOG(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,
            "NV_WriteDataToFile:fp is null.\n");
        return NV_OPEN_FILE_FAIL;
    }

    /* 置写指针位置 */
    if(VOS_OK != NV_File_Seek(fp, lWriteOffset, NV_FILE_SEEK_SET))
    {
        PS_LOG(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,
            "NV_WriteDataToFile:file seek fail.\n");
        return NV_SEEK_FILE_FAIL;
    }

    /* 把 内容写入 写入NV ID */
    if (VOS_ERROR == NV_File_Write(pItem, ulLength, 1, fp))
    {
        PS_LOG(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,
            "NV_WriteDataToFile:write file fail.\n");
        return NV_WRITE_FLASH_FAIL;
    }

    return NV_OK;
}

/*****************************************************************************
Function   : NV_ReadPart
Description: Read Part of NV from the file without Auth.
Input      : VOS_UINT16 usID -> NV ID
             VOS_UINT32 ulOffset -> Offset from the NV data start
             VOS_VOID *pItem -> Save NV data buffer
             VOS_UINT32 ulLength -> buffer length
Return     : Ok or Err.
Other      :
*****************************************************************************/
VOS_UINT32 NV_ReadPartEx(MODEM_ID_ENUM_UINT16              enModemID,
                                VOS_UINT16                      usID,
                                VOS_UINT32                      ulOffset,
                                VOS_VOID                        *pItem,
                                VOS_UINT32                      ulLength)
{
    NV_ID_RETUEN_INFO_STRU              stNvIdReturnInfo;
    VOS_UINT32                          ulResult;

    ulResult = NV_NvIdCheck(enModemID, usID, ulOffset, pItem, ulLength, &stNvIdReturnInfo);

    if(NV_OK != ulResult)
    {
        PS_LOG(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,
                "NV_ReadPartEx:NV ID check fail.\n");
        return ulResult;
    }

    /*从缓存中读取NV数据*/
    NV_MEMCPY((VOS_CHAR*)pItem, ((VOS_CHAR*)g_pstNVDataBuf + stNvIdReturnInfo.ulTotalOffset), ulLength);

    return NV_OK;
}

/*****************************************************************************
Function   : NV_ReadEx
Description: Read NV from the file without Auth.
Input      : VOS_UINT16 usID -> NV ID
             VOS_VOID *pItem -> Save NV data buffer
             VOS_UINT32 ulLength -> buffer length
Return     : Ok or Err.
Other      :
*****************************************************************************/
VOS_UINT32 NV_ReadEx(MODEM_ID_ENUM_UINT16           enModemID,
                            VOS_UINT16                  usID,
                            VOS_VOID                   *pItem,
                            VOS_UINT32                  ulLength)
{
    /* 直接调用 NV_ReadPart，offset 设置为0 */
    return NV_ReadPartEx(enModemID, usID, 0, pItem, ulLength);
}

/*****************************************************************************
Function   : NV_WriteExMemory
Description: Write NV just to the memory.
Input      : VOS_UINT16 usID -> NV ID
             VOS_UINT32 ulOffset -> offset from NV data start
             VOS_VOID *pItem -> NV data buffer
             VOS_UINT32 ulLength -> buffer length
Return     : Ok or Err.
Other      :
*****************************************************************************/
VOS_UINT32 NV_WriteExMemory(MODEM_ID_ENUM_UINT16           enModemID,
                            VOS_UINT16                  usID,
                            VOS_VOID                   *pItem,
                            VOS_UINT32                  ulLength)
{
    VOS_UINT32                          ulResult;
    NV_ID_RETUEN_INFO_STRU              stNvIdReturnInfo;

    ulResult = NV_NvIdCheck(enModemID, usID, 0, pItem, ulLength, &stNvIdReturnInfo);
    if(NV_OK != ulResult)
    {
        PS_LOG(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,
                "NV_WriteExMemory:NV ID check fail.\n");
        return ulResult;
    }

    /* 判断是否属于安全NV */
    if((VOS_YES == mdrv_crypto_check_sec()) && (g_ulCFDNvFileId == stNvIdReturnInfo.usFileId))
    {
        /* Forbid write seure NV file when seure version */
        PS_LOG1(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,
                "NV_WritePartEx:NV ID is secured:", usID);
        return NV_WRITE_SECURE_FAIL;
    }

    /* 更新缓存中的NV数据 */
    NV_SetAreaAccessable(NV_AREA_WRITABLE);
    NVIM_MemCpy(((VOS_CHAR*)g_pstNVDataBuf + stNvIdReturnInfo.ulTotalOffset), (VOS_CHAR*)pItem, ulLength);
    /* 从buf刷到ddr中 */
#if (VOS_WIN32 != VOS_OS_VER)

#if (VOS_LINUX == VOS_OS_VER)
        __asm(" DSB sy ");
        __asm(" ISB sy ");
#else
        __asm(" DSB ");
        __asm(" ISB ");
#endif

#endif
    NV_SetAreaAccessable(NV_AREA_NO_WRITABLE);

    return NV_OK;
}

/*****************************************************************************
Function   : NV_WritePart
Description: Write NV to the file without Auth.
Input      : VOS_UINT16 usID -> NV ID
             VOS_UINT32 ulOffset -> offset from NV data start
             VOS_VOID *pItem -> NV data buffer
             VOS_UINT32 ulLength -> buffer length
Return     : Ok or Err.
Other      :
*****************************************************************************/
VOS_UINT32 NV_WritePartEx(MODEM_ID_ENUM_UINT16      enModemID,
                                VOS_UINT16              usID,
                                VOS_UINT32              ulOffset,
                                VOS_VOID                *pItem,
                                VOS_UINT32              ulLength)
{
    FILE                               *fp;
    VOS_CHAR                            aucFilePath[NV_ABSLT_PATH_LEN] = {0};
    NV_ID_RETUEN_INFO_STRU              stNvIdReturnInfo;
    VOS_UINT32                          ulResult = NV_OK;
    VOS_UINT16                          usNVProperty;
    VOS_UINT32                          ulTempOffset;

    ulResult = NV_NvIdCheck(enModemID, usID, ulOffset, pItem, ulLength, &stNvIdReturnInfo);
    if(NV_OK != ulResult)
    {
        PS_LOG(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,
                "NV_WritePartEx:NV ID check fail.\n");
        return ulResult;
    }

    /* 判断是否属于安全NV */
    if((VOS_YES == mdrv_crypto_check_sec()) && (g_ulCFDNvFileId == stNvIdReturnInfo.usFileId))
    {
        /* Forbid write seure NV file when seure version */
        PS_LOG1(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,
                "NV_WritePartEx:NV ID is secured:", usID);
        return NV_WRITE_SECURE_FAIL;
    }

    /* 获取低三位有效的权限 */
    usNVProperty = NV_GET_AVAILABE_RIGHT_BITS(stNvIdReturnInfo.usProperty);

    /* 如果上次NV写操作没有完成，则等到其完成 */
    if ( VOS_OK != VOS_SmP(g_ulNVWriteSem, 0))
    {
        PS_LOG(WUEPS_PID_USIM, 0, PS_PRINT_ERROR, "NV_WritePartEx:VOS_SmP failed.");
        return NV_SMP_ERR;
    }

    /* 获取IPC硬件锁 */
    if(MDRV_OK != mdrv_ipc_sem_take(IPC_SEM_NVIM, NV_IPC_TIME_FOREVER))
    {
        /*lint -e534*/
        VOS_SmV(g_ulNVWriteSem);
        /*lint +e534*/
        return NV_SMP_ERR;
    }


    if (BSP_MODULE_SUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_LOCALFLASH))
    {
        /* 本地写文件 */
        /* Use absolute path to operate */
        NV_GetFileAbsltPath(g_aucNvFolderPath,(VOS_CHAR*)(stNvIdReturnInfo.aucFileName),aucFilePath, NV_ABSLT_PATH_LEN);

        ulTempOffset = stNvIdReturnInfo.ulNvOffset + ulOffset;
    }
    else
    {
        VOS_StrNCpy(aucFilePath, g_aucNvFilePath, sizeof(aucFilePath));
        /* 保护操作，防止越界 */
        aucFilePath[NV_ABSLT_PATH_LEN - 1] = '\0';

        ulTempOffset = stNvIdReturnInfo.ulTotalOffset;
    }

    if (NV_PRIORITY_HIGH == usNVProperty)
    {
        /* 高优先级别 立即写 */
        fp = NV_File_Open((VOS_CHAR*)aucFilePath, NV_FILE_OPEN_MODE_RW);

        if (VOS_NULL_PTR == fp)
        {
            /* 释放IPC硬件锁 */
            mdrv_ipc_sem_give(IPC_SEM_NVIM);

            /*lint -e534*/
            VOS_SmV(g_ulNVWriteSem);
            /*lint +e534*/

            return NV_OPEN_FILE_FAIL;
        }

        ulResult = NV_WriteDataToFile(fp, pItem, ulLength, (VOS_INT32)ulTempOffset);

        NV_File_Close(fp);
    }
    else  if (NV_PRIORITY_LOW == usNVProperty)
    {
        /* 低优先级别 关机写 */
    }
    else
    {
         /* NV模块下移，不再支持发消息写 */
 #if 0
         /* 中优先级别 */
         g_stNvPriThresholdCur.ausNvMiddle[stNvAclTblInfo.usNvRight - NV_PRIORITY_MIDDLE1] += 1;

         /* 当前阈值达上限,清空阈值计数器，发送消息给 NV_Fluh 任务*/
         if (g_stNvPriThreshold.ausNvMiddle[stNvAclTblInfo.usNvRight - NV_PRIORITY_MIDDLE1] <=
             g_stNvPriThresholdCur.ausNvMiddle[stNvAclTblInfo.usNvRight - NV_PRIORITY_MIDDLE1])
         {
             /*  给 NV_Flush 任务 发送消息 */
             ulRslt = NV_SendMsgToNvFlush();

             /* 清空阈值计数器 */
             /*lint -e534*/
             VOS_MemSet(&g_stNvPriThresholdCur, 0, sizeof(NV_PRIORITY_THRESHOLD_STRU));
             /*lint +e534*/
         }
 #endif
    }

    if (NV_OK != ulResult)
    {
        /* 释放IPC硬件锁 */
        mdrv_ipc_sem_give(IPC_SEM_NVIM);

        /*lint -e534*/
        VOS_SmV(g_ulNVWriteSem);
        /*lint +e534*/

        PS_LOG1(WUEPS_PID_USIM, 0, PS_PRINT_ERROR,
                "NV_WritePartEx:NV write is filed:", ulResult);

        return ulResult;
    }

    /* 更新缓存中的NV数据 */
    NV_SetAreaAccessable(NV_AREA_WRITABLE);
    NVIM_MemCpy(((VOS_CHAR*)g_pstNVDataBuf + stNvIdReturnInfo.ulTotalOffset), (VOS_CHAR*)pItem, ulLength);
    NV_SetAreaAccessable(NV_AREA_NO_WRITABLE);

    /* 释放IPC硬件锁 */
    mdrv_ipc_sem_give(IPC_SEM_NVIM);

    /*lint -e534*/
    VOS_SmV(g_ulNVWriteSem);
    /*lint +e534*/

    /* 记录Slice */
    NV_RecordNvWriteSlice(usID, mdrv_timer_get_normal_timestamp());

    return NV_OK;
}

/*****************************************************************************
Function   : NV_WriteEx
Description: Write NV to the file without Auth.
Input      : VOS_UINT16 usID -> NV ID
             VOS_VOID *pItem -> NV data buffer
             VOS_UINT32 ulLength -> buffer length
Return     : Ok or Err.
Other      :
*****************************************************************************/
VOS_UINT32 NV_WriteEx(MODEM_ID_ENUM_UINT16          enModemID,
                            VOS_UINT16                  usID,
                            VOS_VOID                    *pItem,
                            VOS_UINT32                  ulLength)
{
    /* 直接调用 NV_WritePart，offset 设置为0 */
    return NV_WritePartEx(enModemID, usID, 0, pItem, ulLength);
}

/*****************************************************************************
Function   : NV_BuildGlobal
Description: build global variable.it is used for A core after C NV init and after C core reboot alone.
Input      : none
Return     : Ok or Err.
Other      :
*****************************************************************************/
VOS_VOID NV_BuildGlobalVar(VOS_VOID)
{
    VOS_UINT32                          ulOffset = 0;
    VOS_UINT32                          i;
    NV_FILE_LIST_INFO_STRU              *pstFileListInfo;

    g_pstNVDataBuf = (NV_CONTROL_FILE_INFO_STRU *)NV_DATA_BASE_ADDR;

    g_astNvFileHandle[0].ulOffset = ulOffset;
    g_astNvFileHandle[0].ulSize = g_pstNVDataBuf->ulCtrlFileSize;

    ulOffset += g_astNvFileHandle[0].ulSize;

    pstFileListInfo = (NV_FILE_LIST_INFO_STRU *)((VOS_CHAR *)g_pstNVDataBuf + sizeof(NV_CONTROL_FILE_INFO_STRU));

    for(i = 1; i <= g_pstNVDataBuf->ulFileListNum; i++)
    {
        g_astNvFileHandle[i].ulOffset = ulOffset;
        g_astNvFileHandle[i].ulSize = pstFileListInfo[i-1].ulFileSize;

        ulOffset += pstFileListInfo[i-1].ulFileSize;
    }

    return;
}

/*****************************************************************************
Function   : Nvim_GetNvBuffSize
Description: Get NV buffer size.
Input      : none
Return     : Ok or Err.
Other      :
*****************************************************************************/
VOS_UINT32 Nvim_GetNvBuffSize(VOS_VOID)
{
    VOS_UINT32                          ulSize;

    ulSize = NV_BUFFER_SIZE;

    return ulSize;
}

/*****************************************************************************
Function   : NV_GetNVIdListNum
Description: Get NV ID num
Input      : VOS_VOID
Return     : NV ID num.
Other      :
*****************************************************************************/
VOS_UINT32 NV_GetNVIdListNum(VOS_VOID)
{
    return g_pstNVDataBuf->ulNvRefCount;
}

/*****************************************************************************
Function   : NV_GetNVIdList
Description: Get NV ID list
Input      : VOS_VOID
Return     : NV ID list.
Other      :
*****************************************************************************/
VOS_UINT32 NV_GetNVIdList(NV_LIST_INFO_STRU *pstNvIdList)
{
    NV_REFERENCE_DATA_INFO_STRU     *pstSrc;
    VOS_UINT32                      i;
    VOS_UINT32                      ulOffset;

    ulOffset = sizeof(NV_CONTROL_FILE_INFO_STRU)
                + (sizeof(NV_FILE_LIST_INFO_STRU) * (g_pstNVDataBuf->ulFileListNum));

    pstSrc   = (NV_REFERENCE_DATA_INFO_STRU *)((VOS_CHAR *)g_pstNVDataBuf + ulOffset);

    for (i=0; i < g_pstNVDataBuf->ulNvRefCount; i++)
    {
        pstNvIdList[i].usNvId         = pstSrc[i].usNvId;
        pstNvIdList[i].ucNvModemNum   = pstSrc[i].ucModemNum;
    }

    return NV_OK;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



