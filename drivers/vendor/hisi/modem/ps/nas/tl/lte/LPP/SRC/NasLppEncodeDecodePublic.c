


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "vos.h"
#include  "NasLppEncodeDecodePublic.h"
#include  "NasLppOm.h"
#include  "PsLogdef.h"

#define    THIS_FILE_ID            PS_FILE_ID_NASLPPENCODEDECODEPUBLIC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLPPENCODEDECODEPUBLIC_C

/*lint -e701*/
#if (FEATURE_LPP == FEATURE_ON)

/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
VOS_UINT8  g_aucLppEncodeMask[8][8] =
                        {{0x00, 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01},
                        {0x80, 0x00, 0xbf, 0x9f, 0x8f, 0x87, 0x83, 0x81},
                        {0xc0, 0x00, 0x00, 0xdf, 0xcf, 0xc7, 0xc3, 0xc1},
                        {0xe0, 0x00, 0x00, 0x00, 0xef, 0xe7, 0xe3, 0xe1},
                        {0xf0, 0x00, 0x00, 0x00, 0x00, 0xf7, 0xf3, 0xf1},
                        {0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfb, 0xf9},
                        {0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd},
                        {0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
VOS_UINT8  g_aucMask[8][8] =
                        {{0x00, 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01},
                        {0x80, 0x00, 0xbf, 0x9f, 0x8f, 0x87, 0x83, 0x81},
                        {0xc0, 0x00, 0x00, 0xdf, 0xcf, 0xc7, 0xc3, 0xc1},
                        {0xe0, 0x00, 0x00, 0x00, 0xef, 0xe7, 0xe3, 0xe1},
                        {0xf0, 0x00, 0x00, 0x00, 0x00, 0xf7, 0xf3, 0xf1},
                        {0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfb, 0xf9},
                        {0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd},
                        {0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
Function Name   : LTE_MsgHook
Description     : 可维可测函数
Input           : None
Output          : None
Return          : None
History         :
  1.lifuxin 00253982           2014-05-29  Draft Enact
*****************************************************************************/



//#ifndef PS_ITT_PC_TEST_NAS
//VOS_UINT32 LTE_MsgHook(VOS_VOID * pMsg);
/*{
    return 0;
}*/
//#endif
/*****************************************************************************
Function Name   : NAS_Lpp_AsnInit
Description     : ASN初始化函数
Input           : None
Output          : None
Return          : None
History         :
  1.lifuxin 00253982           2014-05-29  Draft Enact
*****************************************************************************/
VOS_VOID NAS_Lpp_AsnInit(VOS_VOID)
{
    NAS_LPP_MEM_CPY_S(g_aucLppEncodeMask, sizeof(g_aucLppEncodeMask),g_aucMask, 64);
}

/*****************************************************************************
Function Name   : NAS_LPP_DebugInfo
Description     : LPP debug勾消息使用
Input           : None
Output          : None
Return          : None
History         :
  1.lifuxin 00253982           2014-05-29  Draft Enact
*****************************************************************************/
/*VOS_VOID NAS_LPP_SaveDebugInfo(LPP_DEBUG_INFO_STRU *pstLppDebug)
{
    return;
}

****************************************************************************
Function Name   : NAS_Lpp_PrintfMsg
Description     : 打印LPP消息
Input           : None
Output          : None
Return          : None
History         :
  1.lifuxin 00253982           2015-05-29  Draft Enact
*****************************************************************************/

VOS_VOID NAS_Lpp_PrintfMsg(VOS_UINT8 *pucEncodeBuff, char * EncodeIe, VOS_UINT32 ulMsgLength)
{
    VOS_UINT32 i;
    VOS_UINT32 ulMsgSize;
    vos_printf("Encode %s bit = %d Msg:\n", EncodeIe, ulMsgLength);
    vos_printf("Msg %s\n", pucEncodeBuff);
    vos_printf("========================================================1\n");

    if((ulMsgLength % 8 != 0) || (ulMsgLength == 0))
    {
        ulMsgSize = ulMsgLength + (8 - ulMsgLength % 8);
    }
    else
    {
        ulMsgSize = ulMsgLength;
    }

    for(i = 0; i < ulMsgSize/8; i++)
    {
        vos_printf("%-4x", pucEncodeBuff[i]);
        if((i%16 == 0) && (i != 0))
        {
            vos_printf("\n");
        }
    }
    vos_printf("\n");
    vos_printf("========================================================2\n\n");
}

/*****************************************************************************
 Function Name   : NAS_LPP_GetParaToOctet
 Description     : 将要编码的uslen长的数据存储到usTar中去，而且保持右对齐
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lifuxin 00253982  2015-05-02    Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LPP_GetParaToOctet(
                                VOS_UINT16      *pusTar,
                                VOS_UINT8       *pArr,
                                VOS_UINT16      usPos,
                                VOS_UINT16      usLen)
{
    VOS_UINT32  ulVTemp1 = 0;
    VOS_UINT32  ulVTemp2 = 0;
    VOS_UINT32  ulVTemp3 = 0;

    ulVTemp1 = usPos >> 3;
    ulVTemp2 = usPos & 0x07;
    ulVTemp3 = usPos + usLen - 1;
    ulVTemp3 = ulVTemp3 >> 3;

    /*本函数的目的是将即将要编码的数据取出来放到usTar中去，并且保证右对齐*/
    /*等于0表示需要编码的数据小于一个byte*/


    if(0 == ulVTemp3 - ulVTemp1)
    {
        *pusTar = (VOS_UINT16)((pArr[ulVTemp1] >> (8 - ulVTemp2 - usLen)) & (0xff >> (8 - usLen)));
    }

    else
    {
        /*需要编码的数据大于一个byte*/
        *pusTar = (VOS_UINT16)(((((VOS_UINT32)(pArr[ulVTemp1] & (0xff >> ulVTemp2))) << 8)
                + ((VOS_UINT32)(pArr[ulVTemp1+1]))) >> (16 - ulVTemp2 - usLen));
    }


    return;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeExtBit
 Description     : 编码有扩展项且不选中扩展项的场景
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lifuxin 00253982  2015-05-02    Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeExtBit(
                        VOS_UINT16      *pBitPos,
                        VOS_UINT8       *pEncodeOutMsg)

{
    VOS_UINT8   ucExtIe = 1;

    /*编码扩展位*/
    NAS_LPP_EncodeBitSteam(pEncodeOutMsg, pBitPos, 1, &ucExtIe);

    return NAS_LPP_ENCODE_SUCC;
}


/*****************************************************************************
 Function Name   : NAS_LPP_Encode_EncodeLongData
 Description     : lpp编码bit位大于0位小于32位的码流函数
 Input           : pEncodeOutMsg 表示编码完成后存储码流的buffer
                   pBitPos  表示当前编码的第一个位置
                   usLen   表示实际要编码的长度
                   ulSource 表示实际要编码的码流
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lifuxin  2015-6-2    Draft Enact
*****************************************************************************/
VOS_VOID NAS_LPP_EncodeEncodeLongData(
                                    VOS_UINT8       *pEncodeOutMsg,
                                    VOS_UINT16      *pBitPos,
                                    VOS_UINT16      usLen,
                                    VOS_UINT32      ulSource)
{
    VOS_UINT8       ucTemp = 0;
    VOS_UINT16      usTemp = 0;

    if((usLen > 0) && (usLen <= 8))
    {
        NAS_LPP_EncodeBitsLess8(pEncodeOutMsg, pBitPos, usLen, (VOS_UINT8)ulSource);
    }
    else if((usLen > 8) && (usLen <= 16))
    {
        usTemp = (VOS_UINT16)ulSource;
        /*高8bit*/
        ucTemp = (VOS_UINT8)(usTemp >> 8);
        if(usLen == 16)
        {
            NAS_LPP_EncodeBitsLess8(pEncodeOutMsg, pBitPos, 8, ucTemp);
        }
        else
        {
            NAS_LPP_EncodeBitsLess8(pEncodeOutMsg, pBitPos, usLen%8, ucTemp);
        }
        /*低8bit*/
        ucTemp = (VOS_UINT8)usTemp;
        NAS_LPP_EncodeBitsLess8(pEncodeOutMsg, pBitPos, 8, ucTemp);
    }
    else if((usLen > 16) && (usLen <= 24))
    {
        /*高8bit*/
        ucTemp = (VOS_UINT8)(ulSource >> 16);
        NAS_LPP_EncodeBitsLess8(pEncodeOutMsg, pBitPos, usLen%16, ucTemp);
        /*中bit*/
        ucTemp = (VOS_UINT8)(ulSource >> 8);
        NAS_LPP_EncodeBitsLess8(pEncodeOutMsg, pBitPos, 8, ucTemp);
        /*低8bit*/
        ucTemp = (VOS_UINT8)ulSource;
        NAS_LPP_EncodeBitsLess8(pEncodeOutMsg, pBitPos, 8, ucTemp);
    }
    else
    {
        /*最高的8bit*/
        ucTemp = (VOS_UINT8)(ulSource >> 24);
        NAS_LPP_EncodeBitsLess8(pEncodeOutMsg, pBitPos, usLen%24, ucTemp);
        /*次高8bit*/
        ucTemp = (VOS_UINT8)(ulSource >> 16);
        NAS_LPP_EncodeBitsLess8(pEncodeOutMsg, pBitPos, 8, ucTemp);
        /*低16bit的高8bit*/
        ucTemp = (VOS_UINT8)(ulSource >> 8);
        NAS_LPP_EncodeBitsLess8(pEncodeOutMsg, pBitPos, 8, ucTemp);
        /*低8bit*/
        ucTemp = (VOS_UINT8)ulSource;
        NAS_LPP_EncodeBitsLess8(pEncodeOutMsg, pBitPos, 8, ucTemp);
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeBitsLess8
 Description     : LPP将需要编码的数据左移到最高位，然后编码
 Input           : pTarget 表示编码完成后存储码流的buffer
                   pulPos  表示当前编码的第一个位置
                   usLen   表示实际要编码的长度
                   pSource 表示实际要编码的码流
 Output          : None
 Return          : VOS_VOID

 History         :
    1.WANGENSHENG  2015-05-15    Draft Enact
*****************************************************************************/
VOS_VOID NAS_LPP_EncodeBitsLess8(
                                    VOS_UINT8       *pucEncodeOutMsg,
                                    VOS_UINT16      *pusBitPos,
                                    VOS_UINT16      usLen,
                                    VOS_UINT8       ucSource)
{
    VOS_UINT8 aucTmp[1];

    aucTmp[0] = ucSource;

    if((usLen == 0) ||(usLen > 8))
    {

        return;
    }
    if(usLen != 8)
    {
        aucTmp[0] = (VOS_UINT8)(aucTmp[0] << (8 - usLen));
    }
    NAS_LPP_SetBitStreamFromStream(pucEncodeOutMsg, *pusBitPos, usLen, aucTmp);
    *pusBitPos += usLen;

    return;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeBitSteam
 Description     : LPP编码最基础的函数
 Input           : pTarget 表示编码完成后存储码流的buffer
                   pulPos  表示当前编码的第一个位置
                   usLen   表示实际要编码的长度
                   pSource 表示实际要编码的码流
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lifuxin 00253982  2015-05-02    Draft Enact
*****************************************************************************/
VOS_VOID NAS_LPP_EncodeBitSteam(
                                    VOS_UINT8       *pTarget,
                                    VOS_UINT16      *pulPos,
                                    VOS_UINT16      usLen,
                                    VOS_UINT8       *pSource)
{
    NAS_LPP_SetBitStreamFromStream(pTarget, *pulPos, usLen, pSource);
    *pulPos += usLen;

    return;
}

/*****************************************************************************
 Function Name   : NAS_LPP_SetBitStreamFromStream
 Description     : LPP编码最基础的函数
 Input           : pTarget 表示编码完成后存储码流的buffer
                   ulPos   表示当前编码的第一个位置
                   usLen   表示实际要编码的长度
                   pSource 表示实际要编码的码流
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lifuxin 00253982  2015-05-02    Draft Enact
*****************************************************************************/
VOS_VOID NAS_LPP_SetBitStreamFromStream(
                                    VOS_UINT8       *pTarget,
                                    VOS_UINT16      ulPos,
                                    VOS_UINT16      usLen,
                                    VOS_UINT8       *pucSource)
{
    VOS_UINT32      ulTargetOctetPos = 0;
    VOS_UINT16      usTargetBitLen = 0;
    VOS_UINT16      usVdata = 0;
    VOS_UINT16      usSourceBitLen = 0;
    VOS_UINT8       ucVlen = 0;
    VOS_UINT8       ucVMoveLen = 0;

    /*得到当前将要存储的字节数的位置*/
    ulTargetOctetPos = ulPos >> 3;

    /*得到当前需要存储的字节处，看还剩多少个bit可以存储*/
    usTargetBitLen = 8 - (ulPos & 0x07);

    /*意思是需要存储的数据长度小于等于还剩余的bit长度，
      则将剩余的长度置为需要编码的长度*/
    if(usTargetBitLen >= usLen)
    {
        usTargetBitLen = usLen;
    }

    /*设置编码位置的初值bit位置*/
    usSourceBitLen = 0;

    /*将存储编码之后数据的buffer指针移到可以编码的字节的首地址*/
    pTarget += ulTargetOctetPos;

    while (usLen != 0)
    {
        /*将要编码的targetBitlen 存储到usVdata中，而且保持右对齐*/
        NAS_LPP_GetParaToOctet(&usVdata, pucSource, usSourceBitLen, usTargetBitLen);

        /*表示当前字节，存储完v_targetBitLen个长度的bit之后占用该byte的总的bit数，
          比如，当前bit从2开始存储3个bit的数据，那么当前byte总共用了5个bit*/
        ucVlen = ((ulPos + usTargetBitLen) & 0x07);

        /*ucVlen等于0的条件一定是当前存储的POS+需要存储的bit数相加等于8，也就是当前位置刚好存满*/
        if(ucVlen != 0)
        {
            /*如果当前当前位置没有存满8个bit，假设从pos2开始存储3个bit，那么总共占用该byte 5个bit，
              那个将vdata左移 8-5个bit， 也就是高五位的bit，前两位是上一个信元占用的bit，紧接着
              的3个bit是我们即将要编码的3个bit，后面3个bit是无效位， bit开始编码了2个bit， 10，
              即将要编码的bit是101，当前byte有效使用5个bit，所以将5个bit移到最左端便于编码，也即
              是vdata从0000 0101 变成了00101 000*/
              ucVMoveLen = 8 - ucVlen;
            usVdata = (VOS_UINT16)(usVdata << ucVMoveLen);
        }

        /*这里重点介绍一下这里的逻辑，首先取出当前byte的值，targetP，如上面的例子，假设当前已经
          存储了2个，那个对应当前byte假设为 10 000000, 实际上前面两位是有效的编码位，值是确定的，
          后面6位还是不确定的值， 后面g_astLppEncodeMask这个全局变量的作用是什么呢? 作用如下:
          实际上就是将当前byte需要编码的实际位清零的作用，横坐标依次增加标识了当前实际已经编码了
          的长度，纵坐标中连续为0的bit即为即将要编码的bit，将两个相与的目的是将即将要编码的数据清零，
          最后让清完零的数据跟上面移完位的bit vdata相或得到编码之后的数据
        */
        *pTarget = ((*pTarget) & g_aucLppEncodeMask[(ulPos&0x07)][ucVlen]) | ((VOS_UINT8)usVdata);

        usSourceBitLen = usSourceBitLen + usTargetBitLen;
        /*将当前编码位置加上targetBitLen，就是总的编码计数的位置增加了len这么长*/
        ulPos = ulPos + usTargetBitLen;
        /*计算剩余的未编码的bits*/
        usLen = usLen - usTargetBitLen;
        /*如果len等于0则说明已经编码完成了*/
        if(usLen != 0)
        {
            /*指向下一个byte的位置，如果还没有编码完成，则将指针下移到下一个位置，继续编码剩余的码流*/
            pTarget++;

            /*根据剩余的bit数设置下一步编码bit的实际长度，这里的逻辑是如果当前的剩余的bit数大于bit，
              则继续按照8bit编码，如果剩余的bit数小于8bit，则将剩余的bit编码完即可，继续循环，
              只要编码完成*/
            if(usLen >= 8)
            {
                usTargetBitLen = 8;
            }
            else
            {
                usTargetBitLen = usLen;
            }
        }
    }
}

/*****************************************************************************
 Function Name   : NAS_LPP_GetParamFromBitStream
 Description     : LPP解码最基础的函数
 Input           : aArr  表示待解码的码流
                   ulPos 表示即将解码的初始位置
                   usLen 表示解码的实际长度
 Output          : None
 Return          : VOS_UINT32
                   返回解码之后的码流
 History         :
    1.lifuxin 00253982  2015-05-02    Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LPP_GetParamFromBitStream(
                                            VOS_UINT8       aArr[],
                                            VOS_UINT32      ulPos,
                                            VOS_UINT8       usLen)
{
    VOS_UINT32      uLVtemp1 = 0;
    VOS_UINT8       ucVtemp2 = 0;
    VOS_UINT32      ulVtemp3 = 0;
    VOS_UINT32      ulReturnvalue = 0;
    VOS_UINT8       ucMaskvalue = 0xFF;
    VOS_UINT32      ulVexpend1 = 0;/*used to expend u8 to u32 high part*/
    VOS_UINT32      ulVexpend2 = 0;/*used to expend u8 to u32 mid-high part*/
    VOS_UINT32      ulVexpend3 = 0;/*used to expend u8 to u32 mid-low part*/
    VOS_UINT32      ulVexpend4 = 0;/*used to expend u8 to u32 low part*/

    /*表示开始解码的第一个byte相对于待译码数据起始地址的字节数*/
    uLVtemp1 = ulPos >> 3;
    /*表示开始解码的第一个byte开始解码的位置*/
    ucVtemp2 = (VOS_UINT8)(ulPos & 0x07);
    /*因为可能存在需要解码的码流跨多个字节，本次计算可以得出需要解码的数据的结束的byte位置*/
    ulVtemp3 = (ulPos + usLen - 1) >> 3;

    switch(ulVtemp3 - uLVtemp1)
    {
        /*表示需要解码的数据在一个byte内部*/
        case 0:
          /*码流不超过一个byte的译码规则，首先取出当前需要译码的第一个byte，然后将其右移8减去该byte已经译码完的码流长度
            再减去实际要译码的长度，实际上的作用是保证即将译码的数据最低位有效，右靠齐，比如当前需要译码的byte已经译了6
            个bit，也即是pos是6，需要译码1个bit，也即是len是1，那么需要将该byte右移 8-6-1=1个bit，也就是将即将需要译码的数据
            放到最低位， 另外 将0xFF右移8-1=7个bit的意义在于取出需要译码的长度，将对应长度置成1，然后将两个相与，即可以取出
            对应的bit位，也就是译码完成
          */
          ulReturnvalue
            =(VOS_UINT32)((aArr[uLVtemp1] >> (8 - ucVtemp2 - usLen)) & (ucMaskvalue >> (8 - usLen)));
          break;

        /*表示需要解码的数据跨越两个byte*/
        case 1:
          /*把当前byte的数据取出来与上，该byte中需要译码的掩码，假设该byte中占有2个bit，那个就是xxxx xx10跟
           0000 0011相与求出当前byt中的bit数，最后再左移8个bit，也即是10 0000 0000，将译码出的两个bit放到了最高
           位*/
          ulVexpend1 = ((VOS_UINT32)(aArr[uLVtemp1] & (ucMaskvalue >> ucVtemp2))) << 8;
          /*取出下一当前byte的下一字节*/
          ulVexpend2 = (VOS_UINT32)(aArr[uLVtemp1+1]);
          /*这里处理相当于先拼接然后再裁减， 拼接先将第一个byte译码出的数据加上第二个byte中的所有数据，
          然后再将第二个byte中实际没有用到的bit移除，就是我们真是需要解码的数据， 比如， 第一个byte占用6个bit，
          需要译码的总长度是len 4，那个说明第二个byte中无效长度bit就是 16-6-4，也就是需要右移6个bit，得到的数据
          就是真实的码流*/
          ulReturnvalue = (VOS_UINT32)((ulVexpend1 + ulVexpend2) >> (16 - ucVtemp2 - usLen));
          break;

        case 2:
          /*当前需要译码的数据的长度跨越了两个byte，实际上这里跟上面case1类似，基本原则是依次取出最高位
          次高byte，以及最低的byte剩余的bit数，同样采用的是最终需要将无用的bit数右移，得到真实的码流，
          不再详细描述*/
          ulVexpend1 = ((VOS_UINT32)(aArr[uLVtemp1] & (ucMaskvalue >> ucVtemp2))) << 16;
          ulVexpend2 = ((VOS_UINT32)(aArr[uLVtemp1+1])) << 8;
          ulVexpend3 = (VOS_UINT32)(aArr[uLVtemp1+2]);
          ulReturnvalue = (ulVexpend1 + ulVexpend2 + ulVexpend3) >> (24 - ucVtemp2 - usLen);
          break;

        case 3:
          ulVexpend1 = ((VOS_UINT32)(aArr[uLVtemp1] & (ucMaskvalue >> ucVtemp2))) << 24;
          ulVexpend2 = ((VOS_UINT32)(aArr[uLVtemp1+1])) << 16;
          ulVexpend3 = ((VOS_UINT32)(aArr[uLVtemp1+2])) << 8;
          ulVexpend4 = (VOS_UINT32)(aArr[uLVtemp1+3]);
          ulReturnvalue
            = (ulVexpend1 + ulVexpend2 + ulVexpend3 + ulVexpend4) >> (32 - ucVtemp2 - usLen);
          break;

        case 4:
          ulVexpend1 = ((VOS_UINT32)(aArr[uLVtemp1+1])) << 24;
          ulVexpend2 = ((VOS_UINT32)(aArr[uLVtemp1+2])) << 16;
          ulVexpend3 = ((VOS_UINT32)(aArr[uLVtemp1+3])) << 8;
          ulVexpend4 = (VOS_UINT32)(aArr[uLVtemp1+4]);
          ulVexpend2
            = (ulVexpend1 + ulVexpend2 + ulVexpend3 + ulVexpend4) >> (40 - ucVtemp2 - usLen);
          ulVexpend1
            =((VOS_UINT32)(aArr[uLVtemp1] & (ucMaskvalue >> ucVtemp2))) << (ucVtemp2 + usLen - 8);
          ulReturnvalue = ulVexpend1 + ulVexpend2;
          break;

        default:
          ;
      }
  return ulReturnvalue;
}
/*****************************************************************************
 Function Name   : NAS_LPP_GetDataFromBitStream
 Description     : LPP解码最基础的函数,
 Input           : aArr  表示待解码的码流
                   ulPos 表示即将解码的初始位置
                   usLen 表示解码的实际长度
 Output          : None
 Return          : VOS_UINT32
                   返回解码之后的码流
 History         :
    1.wangensheng 00324863  2015-05-04    Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LPP_GetDataFromBitStream(
                                            VOS_UINT8                       *pDecodeBitStream,
                                            VOS_UINT32                      *pCurrentBitPos,
                                            VOS_UINT8       usLen)
{
    VOS_UINT32      ulReturnValue;

    ulReturnValue = NAS_LPP_GetParamFromBitStream(pDecodeBitStream,*pCurrentBitPos,usLen);
    *pCurrentBitPos = *pCurrentBitPos + usLen;

    return  ulReturnValue;
}

/*****************************************************************************
 Function Name   : NAS_LPP_GetLongDataFromBitStream
 Description     : LPP解码获取超过32bit数据的函数
 Input           : aArr  表示待解码的码流
                   ulPos 表示即将解码的初始位置
                   usLen 表示解码的实际长度
                   pllDestData 表示存储数据的变量
 Output          : None
 Return          : VOS_UINT32
                   成功返回 NAS_LPP_DECODE_SUCC 失败 返回 NAS_LPP_DECODE_FAIL
 History         :
    1.wangensheng 00324863  2015-05-04    Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LPP_GetLongDataFromBitStream(
                                                VOS_UINT8       aArr[],
                                                VOS_UINT32      *ulPos,
                                                VOS_UINT8       usLen,
                                                VOS_UINT64      *pllDestData)
{
    /*获取大于32bit小于等于64bit的值，并拼接成64bit。大于64bit的值需要在外部去循环处理*/
    VOS_UINT64      ullTargetValue;
    VOS_UINT64      ullTempData1 = 0;
    VOS_UINT8       ucTempLen = 0;
    /*参数检查*/

    if(usLen <= 32 )
    {
        ullTargetValue = (VOS_UINT64)NAS_LPP_GetDataFromBitStream(aArr,ulPos,usLen);
        *pllDestData = ullTargetValue;
        return NAS_LPP_DECODE_SUCC;
    }
    ucTempLen = usLen % 32;
    /*如果是64bit的情况*/
    if(ucTempLen == 0)
    {
        ucTempLen = 32;
    }
    ullTempData1 = (VOS_UINT64)NAS_LPP_GetDataFromBitStream(aArr,ulPos,ucTempLen);
    ullTargetValue = NAS_LPP_GetDataFromBitStream(aArr,ulPos,32);
    ullTargetValue += (ullTempData1) << 32;
    *pllDestData = ullTargetValue;
    return NAS_LPP_DECODE_SUCC;
}
/*****************************************************************************
 Function Name   : NAS_LPP_GetLongBitFromBitStream
 Description     : LPP解码获取超过32bit数据的函数
 Input           : aArr  表示待解码的码流
                   ulPos 表示即将解码的初始位置
                   usLen 表示解码的实际长度
                   pllDestData 表示存储数据的变量
 Output          : None
 Return          : VOS_UINT32
                   成功返回 NAS_LPP_DECODE_SUCC 失败 返回 NAS_LPP_DECODE_FAIL
 History         :
    1.wangensheng 00324863  2015-05-04    Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LPP_GetLongBitFromBitStream(
                                                VOS_UINT8       aArr[],
                                                VOS_UINT32      *ulPos,
                                                VOS_UINT16       usLen,
                                                VOS_UINT8      *pllDestData)
{
    VOS_UINT8   ucTempLen = 0;
    VOS_UINT8   ucTempValue = 0;
    if(usLen == 0)
        return NAS_LPP_DECODE_SUCC;
    ucTempLen = usLen % 8;
    if(ucTempLen == 0)
    {
        ucTempLen = 8;
    }
    while(usLen != 0)
    {
        usLen -=ucTempLen;
        ucTempValue = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(aArr,ulPos,ucTempLen);
        *pllDestData = ucTempValue;
        pllDestData++;
        ucTempLen = 8;
    }
    return NAS_LPP_DECODE_SUCC;
}
/*****************************************************************************
 Function Name   : NAS_LPP_ASN_FAIL_Message
 Description     : LPP编解码可维可测消息
 Input           :可维可测消息头
 Output          : None
 Return          : VOS_UINT32
                   成功返回
 History         :
    1.wangensheng 00324863  2015-05-04    Draft Enact
****************************************************************************
VOS_VOID NAS_LPP_Hook(VOS_VOID* pstMsg)
{
    return  ;
}*/

/*lint +e701*/
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

