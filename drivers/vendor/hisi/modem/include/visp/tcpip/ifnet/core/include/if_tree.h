/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                         IF_TREE.H
 *
 *  Project Code: VISP1.5
 *   Module Name: IFNET
 *  Date Created: 2000/02/28
 *        Author: YuXiaoHan
 *   Description: Ifnet名字解析树头文件
 *               
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2000/02/28      YuXiaoHan       Create
 *  2006/03/30      liai            Adjust for D00654
 *  2006/04/21      liai            Adjust for D00878
 *
 ************************************************************************/

#ifdef  __cplusplus
extern "C"{
#endif

#ifndef _IF_TREE_H_
#define _IF_TREE_H_

/*------------------------------------------------------
   用于进行接口分析的向量结构, 名称解析树的构成单位。
-------------------------------------------------------*/
ULONG GetTopNumber( ULONG usBegin,ULONG usVal );

ULONG MallocVectorItem(VOID ** pData,ULONG ulSize,ULONG ulID);
ULONG FreeVectorItem(VOID * pData,ULONG ulSize);

ULONG IF_NameTreeInit(VOID);

ULONG IF_InitVector ( PIF_ANAL_VECTOR_S * pVector,
                                         ULONG ulMaxAlloc,
                                         ULONG ulFlag,
                                         ULONG ulHelpIndex,
                                         ULONG ulIndex,
                                         ULONG ulNumber
                                        );

ULONG IF_AddIf(IFNAME_S * pstIfName,IFNET_S * pIf);
ULONG IF_AddIfToTree(IFNAME_S * pstIfName,IFNET_S * pIf);

ULONG IF_DelIfFromTree(IFNAME_S * pstIfName);
ULONG IF_DeleteTreeEntry(IFNAME_S * pstIfName,  USHORT usStep, PIF_ANAL_VECTOR_S pstVector);
IFNET_S* IF_GetIfByTypeNum(ULONG ulIfType, ULONG ulFirstDim, ULONG ulSecondDim, ULONG ulThirdDim);

IFNET_S * IF_GetIfFromTree(IFNAME_S * pstIfName);

ULONG IF_GetTypeName(CHAR ** pName,CHAR * pTemp,ULONG ulMaxLen,ULONG * pulLen);
ULONG IF_JudgeIfType(CHAR * szTemp,ULONG * pIndex);
ULONG IF_AnalyseIfName(IFNAME_S * pstIfName,CHAR * szName);

ULONG IF_GetDimension(IFNAME_S * pstIfName); /*支持接口名动态维数。 pengjimei 2002/11/8*/

IFNET_S* IF_GetMainIf(IFNET_S* pIf);
IFNET_S* IF_GetIfByTypeNumSub(ULONG ulIfType, ULONG ulFirstDim, ULONG ulSecondDim, ULONG ulThirdDim,ULONG ulSubPort);

#endif /* _IF_TREE_H_ */

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

