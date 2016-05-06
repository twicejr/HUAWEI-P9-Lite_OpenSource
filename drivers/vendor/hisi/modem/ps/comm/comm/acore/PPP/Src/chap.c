/*
 * PPP CHAP Module
 *
 * Written by Toshiharu OHNO (tony-o@iij.ad.jp)
 *
 *   Copyright (C) 1993, Internet Initiative Japan, Inc. All rights reserverd.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the Internet Initiative Japan, Inc.  The name of the
 * IIJ may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $FreeBSD: src/usr.sbin/ppp/chap.c,v 1.65 2000/08/18 00:01:43 brian Exp $
 *
 *    TODO:
 */

#include "PPP/Inc/link.h"
#include "PPP/Inc/ppp_fsm.h"

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_CHAP_C

#if(FEATURE_ON == FEATURE_PPP)

static const VOS_CHAR * const chapcodes[] = {
  "\?\?\?", "CHALLENGE", "RESPONSE", "SUCCESS", "FAILURE"
};
#define MAXCHAPCODE ((sizeof chapcodes / sizeof chapcodes[0]) - 1)

/*****************************************************************************
 函 数 名  : ChapOutput
 功能描述  : 构造CHAP帧并发送
 输入参数  : l - PPP链接
             code - 待填写到头部的Code值
             id - 待填写到头部的Identifier值
             ptr - 待填写的CHAP数据
             count - 待填写的CHAP数据的长度, 单位: 字节
             text - 字符串, 用于日志
 输出参数  : 无
 返 回 值  : NULL
 调用函数  :
 被调函数  :
 说    明  : 不对ptr与code进行组合检查, 如code为某值时, ptr不应为空等等,
             因为此函数为一通用函数, 支持生成所有的CHAP帧, 并能扩展为支持
             MS-CHAP帧等, 各种code, ptr组合情况众多, 一切相关检查交由外部
             调用者来完成

 修改历史      :
  1.日    期   : 2008年10月24日
    作    者   : liukai
    修改内容   : porting from BSD

*****************************************************************************/
VOS_VOID ChapOutput(struct link *l, VOS_INT32 code, VOS_CHAR id,
       const VOS_UCHAR *ptr, VOS_UINT32 count, const VOS_CHAR *text)
{
  VOS_UINT32 len;    /* length of a CHAP frame */
  struct fsmheader lh;
  struct ppp_mbuf *bp;

  len = sizeof(struct fsmheader) + count;
  lh.code = (VOS_CHAR)code;
  lh.id = id;
  lh.length = (VOS_UINT16)VOS_HTONS(len);
  bp = ppp_m_get((VOS_INT32)len);

  if (VOS_NULL_PTR == bp)
  {
      PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING, "no mbuf\r\n");
      return;
  }

  PS_MEM_CPY(PPP_MBUF_CTOP(bp), &lh, sizeof(struct fsmheader));
  if ((count > 0) && (VOS_NULL_PTR != ptr))
  {
    PS_MEM_CPY(PPP_MBUF_CTOP(bp) + sizeof(struct fsmheader), ptr, count);
  }

  if (VOS_NULL_PTR == text)
  {
    PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "Chap Output: code %d\r\n", code);
  }
  else
  {
    PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL,"Chap Output: code %d with text\r\n", code);
  }

  /* now a CHAP frame is ready */
  link_PushPacket(l, bp, LINK_QUEUES(l) - 1, PROTO_CHAP);

  return;
}    /* ChapOutput */

/*****************************************************************************
 函 数 名  : chap_Cleanup
 功能描述  : 清除掉PPP链接两端的Challenge
 输入参数  : chap - 链路中的CHAP记录信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年10月24日
    作    者   : liukai
    修改内容   : porting from BSD

*****************************************************************************/
static VOS_VOID chap_Cleanup(struct chap *chap)
{
    *chap->challenge.local = 0x0;
    *chap->challenge.peer = 0x0;

    chap->auth.retry = 0;
}    /* chap_Cleanup */

/*****************************************************************************
 函 数 名  : chap_Respond
 功能描述  : 构造Response帧并发送
 输入参数  : l - PPP链接
             name - 待填写的Name值
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年10月24日
    作    者   : liukai
    修改内容   : porting from BSD

*****************************************************************************/
static VOS_VOID chap_Respond(struct link *l, const VOS_CHAR *name)
{
  VOS_UCHAR  aucResponseBody[1+MD5DIGESTSIZE+AUTHLEN];
  VOS_UINT32    len;    /* length of Response body */
  VOS_UINT32 ulHashValueLoop;

  /* Response body: */
  /*
   *  ------------------- --------------------- ----------
   * |   HASH-Size(1B)   |   HASH-Value(16B)   |   Name   |
   *  ------------------- --------------------- ----------
   */
  len = 1 + MD5DIGESTSIZE + VOS_StrLen((VOS_CHAR *)name);    /* BSD always thinks user name is not beyong AUTHLEN octets */

  aucResponseBody[0] = MD5DIGESTSIZE;    /* as CHAP only support MD5, MD5 hash value is 16 octets */
  /* in our product, when rx-ed Challenge from PC, just response hash value with zero */
  for (ulHashValueLoop = 1; ulHashValueLoop <= MD5DIGESTSIZE; ulHashValueLoop ++)
  {
      aucResponseBody[ulHashValueLoop] = 0x00;
  }

  if ((VOS_NULL_PTR != name) && ('\0' != *name))
  {
      PS_MEM_CPY(&aucResponseBody[1+MD5DIGESTSIZE], name, VOS_StrLen((VOS_CHAR*)name));
  }
  ChapOutput(l, CHAP_RESPONSE, (l->chap.auth.id), aucResponseBody, len, name);

  return;
}    /* chap_Respond */

/*
   if support mutil-thread, use child thread to read and write challenge/response to file,
   we do NOT need it, masked by liukai
*/

/*****************************************************************************
 函 数 名  : ChapBufferChallengePacket
 功能描述  : 备份CHAP challenge packet
 输入参数  : chap - 链路中的CHAP记录信息
             id - 待填写到头部的Identifier值
             ptr - 待备份的CHAP challenge body数据
             count - 待备份的CHAP challenge body数据的长度, 单位: 字节
 输出参数  : 无
 返 回 值  : NULL
 调用函数  :
 被调函数  :
 说    明  : 备份challenge packet, 为了在IPCP阶段提供给NAS在PDP激活中使用

 修改历史      :
  1.日    期   : 2008年11月4日
    作    者   : liukai
    修改内容   : created

*****************************************************************************/
VOS_VOID ChapBufferChallengePacket(struct chap *chap, VOS_CHAR id,
             const VOS_UCHAR *ptr, VOS_UINT32 count)
{
    VOS_UINT32 len;    /* length of a CHAP frame */
    struct fsmheader lh;
    VOS_UINT8 *pucChallengeBuf;

    len = sizeof(struct fsmheader) + count;
    lh.code = CHAP_CHALLENGE;
    lh.id = id;
    lh.length = (VOS_UINT16)VOS_HTONS(len);

    pucChallengeBuf = chap->RecordData.BufChallenge;
    PS_MEM_CPY(pucChallengeBuf, &lh, sizeof(struct fsmheader));
    if (count > 0)
    {
        PS_MEM_CPY(pucChallengeBuf + sizeof(struct fsmheader), ptr, count);
    }
    chap->RecordData.LenOfChallenge = (VOS_UINT16)len;

    return;
}    /* ChapBufferChallengePacket */

/*****************************************************************************
 函 数 名  : chap_Challenge
 功能描述  : 构造Challenge帧并发送
 输入参数  : l - PPP链接
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年10月25日
    作    者   : liukai
    修改内容   : porting from BSD

*****************************************************************************/
VOS_VOID chap_Challenge(struct link *l)
{
  struct chap *chap = &(l->chap);
  VOS_UINT32 len, i;
  VOS_UINT8 *cp;
  VOS_UINT32 ulTick;
  const VOS_CHAR acLocalChallenge[] = "HUAWEI_CHAP_SRVR";   /* we always use "HUAWEI_CHAP_SRVR" as Name of Challenge */

  /* Challenge body: */
  /*
   *  ------------------------ --------------------- ----------
   * |   Challenge-Size(1B)   |   Challenge-Value   |   Name   |
   *  ------------------------ --------------------- ----------
   */
  len = VOS_StrLen((VOS_CHAR *)acLocalChallenge);

  if (0x0 == *(chap->challenge.local)) {    /* as each time local[0] is 0x0, here is always true */
    ulTick = VOS_GetTick();
    VOS_SetSeed(ulTick);    /* use current tick as seed of random algorithm */

    cp = chap->challenge.local;
    /*AT2D19295 测试组建议challenge中随机字符串长度固定为16，和标杆一致 */
    *cp++ = (VOS_UINT8)(MD5DIGESTSIZE);

    /*
      *cp++ = (VOS_UINT8)(PS_RAND(CHAPCHALLENGELEN-MD5DIGESTSIZE) + MD5DIGESTSIZE);
      随机字串长度本为任意长度, 存放在local的第一个字节,为了防止对端只支持MD5而要求长度为16, 特意保证长度至少16字节
    */
    for (i = 0; i < *(chap->challenge.local); i++)
    {
      *cp++ = (VOS_UINT8)PS_RAND(PS_NULL_UINT8+1);    /* 随机字串 */
    }

    /* use memcpy instead of strcpy, as "The Name should not be NUL or CR/LF terminated." in RFC1994 */
    PS_MEM_CPY(cp, acLocalChallenge, len);
  }

  /* each time send challenge, record its packet */
  ChapBufferChallengePacket(chap, chap->auth.id, chap->challenge.local,
      1 + *(chap->challenge.local) + len);

  ChapOutput(l, CHAP_CHALLENGE, chap->auth.id, chap->challenge.local,
         1 + *(chap->challenge.local) + len, VOS_NULL_PTR);    /* 1: challenge length, *local: 随机字串长度, len: Name length */

  return;
}    /* chap_Challenge */

/*****************************************************************************
 函 数 名  : chap_Success
 功能描述  : 构造Success帧并发送
 输入参数  : l - PPP链接
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年10月25日
    作    者   : liukai
    修改内容   : porting from BSD

*****************************************************************************/
static VOS_VOID chap_Success(struct link *l)
{
  struct authinfo *authp = &(l->chap.auth);
  const VOS_CHAR *pcMsg = "Welcome!!";    /* follow BSD use "Welcome!!" as message */

  /* Success body: */
  /*
   *  -------------
   * |   Message   |
   *  -------------
   */

  ChapOutput(l, CHAP_SUCCESS, authp->id, (VOS_UCHAR *)pcMsg, VOS_StrLen((VOS_CHAR *)pcMsg), VOS_NULL_PTR);

  l->lcp.auth_ineed = 0;    /* after Authentication, clear flag to authenticate peer */

  if (0 == l->lcp.auth_iwait)    /* auth_iwait: 0, authentication to peer is not complete or no need to authentication,
                                               !0, authentication to peer is complete */
  {
    /*
     * Either I didn't need to authenticate, or I've already been
     * told that I got the answer right.
     */
    chap_ReInit(&(l->chap));
    if (PHASE_AUTHENTICATE == l->phase)
    {
        l->phase = PHASE_NETWORK;
        l->ipcp.fsm.state = ST_CLOSED;
        fsm_Open(&(l->ipcp.fsm));
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "goto ipcp stage!\r\n");
    }
  }

  return;
}    /* chap_Success */


/*****************************************************************************
 函 数 名  : chap_Init
 功能描述  : 初始化CHAP模块
 输入参数  : chap - CHAP配置
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年10月25日
    作    者   : liukai
    修改内容   : porting from BSD

*****************************************************************************/
VOS_VOID chap_Init(struct chap *chap)
{
  auth_Init(&(chap->auth), chap_Challenge, chap_Success, VOS_NULL_PTR);
  chap_Cleanup(chap);
  PS_MEM_SET(&(chap->RecordData), '\0', sizeof(chap->RecordData));

  return;
}    /* chap_Init */

/*****************************************************************************
 函 数 名  : chap_ReInit
 功能描述  : 重新初始化CHAP模块
 输入参数  : chap - CHAP配置
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年10月25日
    作    者   : liukai
    修改内容   : porting from BSD

*****************************************************************************/
VOS_VOID chap_ReInit(struct chap *chap)
{
  chap_Cleanup(chap);

  return;
}    /* chap_ReInit */

/*****************************************************************************
 函 数 名  : ChapBufferResponsePacket
 功能描述  : 备份收到的CHAP response packet
 输入参数  : chap - 链路中的CHAP记录信息
             ucHashSize - response中hash-size
             aucHashValue - response中hash-value
             lNameLen - response中name字段的长度, 单位: 字节
 输出参数  : 无
 返 回 值  : NULL
 调用函数  :
 被调函数  :
 说    明  : 备份response packet, 为了在IPCP阶段提供给NAS在PDP激活中使用

 修改历史      :
  1.日    期   : 2008年11月4日
    作    者   : liukai
    修改内容   : created

*****************************************************************************/
VOS_VOID ChapBufferResponsePacket(struct chap *chap, VOS_UCHAR ucHashSize,
             VOS_UCHAR aucHashValue[], VOS_INT32 lNameLen)
{
    VOS_UINT8 *pucResponseNextPos;    /* the start address to store response in buffer for next time */

    pucResponseNextPos = chap->RecordData.BufResponse;

    PS_MEM_CPY(pucResponseNextPos, &(chap->auth.in.hdr), sizeof(struct fsmheader));    /* record packet header */
    pucResponseNextPos += sizeof(struct fsmheader);

    *pucResponseNextPos = ucHashSize;
    pucResponseNextPos++;    /* hash-size always use one octet */

    if (ucHashSize != 0)    /* with hash-value */
    {
        PS_MEM_CPY(pucResponseNextPos, aucHashValue, ucHashSize);
        pucResponseNextPos += ucHashSize;
    }
    if (('\0' != *chap->auth.in.name) && (lNameLen > 0))    /* with name */
    {
        /*
            why do NOT use strcpy, as "The Name should not be NUL or CR/LF terminated."
            in RFC1994. However, rx-ed response packets of peer may use NUL as terminate,
            so use @lNameLen, not to use strlen to calculate itself.
        */
        PS_MEM_CPY(pucResponseNextPos, chap->auth.in.name, (VOS_UINT32)lNameLen);
    }
    else
    {
        *pucResponseNextPos = '\0';
    }

    chap->RecordData.LenOfResponse = VOS_NTOHS(chap->auth.in.hdr.length);

    return ;
}    /* ChapBufferResponsePacket */

/*****************************************************************************
 函 数 名  : chap_Input
 功能描述  : 收到CHAP帧的处理入口函数
 输入参数  : l - PPP链接
             pstMem - 收到的CHAP帧
 输出参数  : 无
 返 回 值  : NULL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年10月24日
    作    者   : liukai
    修改内容   : porting from BSD

*****************************************************************************/
PPP_ZC_STRU *chap_Input(struct link *l, PPP_ZC_STRU *pstMem)
{
  struct chap *chap;
  VOS_INT32 len;
  VOS_UCHAR alen;    /* answer length: challenge or response body length */
  struct ppp_mbuf *bp;
  VOS_UCHAR aucHashValue[MD5DIGESTSIZE];

  bp = ppp_m_get_from_ttfmem(pstMem);
  PPP_MemFree(pstMem);

  if (VOS_NULL_PTR == bp)
  {
    return VOS_NULL_PTR;
  }

  if (VOS_NULL_PTR == l) {
    PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING, "Chap Input: Not a physical link - dropped\r\n");
    ppp_m_freem(bp);
    return VOS_NULL_PTR;
  }

  if ((PHASE_NETWORK != l->phase) &&
      (PHASE_AUTHENTICATE != l->phase)) {
    PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "Unexpected Chap input - dropped\r\n");
    ppp_m_freem(bp);
    return VOS_NULL_PTR;
  }

  chap = &(l->chap);
  if ((VOS_NULL_PTR == (bp = auth_ReadHeader(&chap->auth, bp))) &&
      (0 == VOS_NTOHS(chap->auth.in.hdr.length)))
  {
    PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING, "Chap Input: Truncated header\r\n");
  }
  else if ((0 == chap->auth.in.hdr.code) || ((VOS_UINT8)(chap->auth.in.hdr.code) > MAXCHAPCODE))
  {
    PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, LOG_LEVEL_WARNING,
                  "Chap Input: Bad CHAP code %d !\r\n", chap->auth.in.hdr.code);
  }
  else {
    len = ppp_m_length(bp);

    /* Identifier of rx-ed Response, Success, Fail should match Challenge tx-ed */
    if ((CHAP_CHALLENGE != chap->auth.in.hdr.code) &&
        (chap->auth.id != chap->auth.in.hdr.id)) {
      /* Wrong conversation dude ! */
      PPP_MNTN_LOG3(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL,
              "Chap Input: code <1> dropped (got id <2> not equal to previous id <3>)\r\n",
              chap->auth.in.hdr.code, chap->auth.in.hdr.id, chap->auth.id);
      ppp_m_freem(bp);
      return VOS_NULL_PTR;
    }
    chap->auth.id = chap->auth.in.hdr.id;    /* We respond with this id */

    if (CHAP_CHALLENGE == chap->auth.in.hdr.code)    /* rx-ed challenge */
    {
        bp = ppp_mbuf_Read(bp, &alen, 1);    /* fetch length of peer's challenge */
        len -= (alen + 1);    /* after this step, len is length of peer's name */
        if (len < 0) {
          PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, LOG_LEVEL_WARNING,
                        "Chap Input: Truncated challenge (len %d, alen %d)!\r\n", len, alen);
          ppp_m_freem(bp);
          return VOS_NULL_PTR;
        }
        if (AUTHLEN < len)
        {
          PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, LOG_LEVEL_WARNING,
                        "Chap Input: name of challenge too long (len %d, alen %d)!\r\n", len, alen);
          ppp_m_freem(bp);
          return VOS_NULL_PTR;
        }
        if (CHAPCHALLENGELEN < alen)
        {
          PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, LOG_LEVEL_WARNING,
                        "Chap Input: challenge too long (len %d)!\r\n", alen);
          ppp_m_freem(bp);
          return VOS_NULL_PTR;
        }

        *chap->challenge.peer = alen;
        bp = ppp_mbuf_Read(bp, chap->challenge.peer + 1, alen);    /* record peer's challenge */
        bp = auth_ReadName(&chap->auth, bp, len);    /* record peer's name */

        if (*chap->auth.in.name)    /* challenge with name */
        {
          PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, LOG_LEVEL_WARNING,
                        "Chap Input: challenge (len %d, alen %d) with name\r\n",
                  len, alen);
        }
        else    /* without name */
        {
          PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, LOG_LEVEL_WARNING,
                        "Chap Input: challenge (len %d, alen %d) without name\r\n",
                        len, alen);
        }

        chap_Respond(l, "HUAWEI_CHAP_CLNT");    /* we always use "HUAWEI_CHAP_CLNT" as Name of Response */
    }    /* end of rx-ed challenge */
    else if (CHAP_RESPONSE == chap->auth.in.hdr.code)    /* rx-ed response */
    {
        bp = ppp_mbuf_Read(bp, &alen, 1);    /* read HASH-Size */
        if (MD5DIGESTSIZE != alen)    /* as just support MD5, must be 16 octets */
        {
          PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, LOG_LEVEL_WARNING,
                        "Chap Input: Hash-Size %f is not correct !\r\n", alen);
          ppp_m_freem(bp);
          return VOS_NULL_PTR;
        }
        len -= (alen + 1);    /* after this step, len is length of Name Field */
        if (len < 0) {
          PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, LOG_LEVEL_WARNING,
                        "Chap Input: Truncated response (len %d, alen %d)!\r\n", len, alen);
          ppp_m_freem(bp);
          return VOS_NULL_PTR;
        }
        if (AUTHLEN < len)
        {
          PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, LOG_LEVEL_WARNING,
                        "Chap Input: name of response too long (len %d, alen %d)!\r\n", len, alen);
          ppp_m_freem(bp);
          return VOS_NULL_PTR;
        }

        bp = ppp_mbuf_Read(bp, aucHashValue, MD5DIGESTSIZE);    /* cut HASH value */
        bp = auth_ReadName(&chap->auth, bp, len);

        if (*chap->auth.in.name)
        {
          PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL,"Chap Input: response (len <1>, alen <2>) with name\r\n",
                  len, alen);
        }
        else
        {
          PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL,"Chap Input: response (len <1>, alen <2>) without name\r\n",
                  len, alen);
        }

        if (PHASE_AUTHENTICATE == l->phase)    /* 需要注意只备份在认证阶段中与challenge id匹配的response */
        {
            ChapBufferResponsePacket(chap, MD5DIGESTSIZE, aucHashValue, len);
        }

        chap_Success(l);

        /*
           Moves code to here as the last step of dealing with response by liukai,
           it should stop authentication timer after authentication pass or fail.
           Stops timer at first, a response frame format is not correct and discards it(way of BSD),
           UE has no chance to send challenge again
        */
        auth_StopTimer(&(chap->auth));
    }    /* end of rx-ed response */
    else if (CHAP_SUCCESS == chap->auth.in.hdr.code)    /* rx-ed success */
    {
        /* chap->auth.in.name is already set up at CHALLENGE time, need NOT to print again */
        if (0 < len)
        {
          PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "Chap Input: success with message\r\n");
        }
        else
        {
          PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "Chap Input: success without message\r\n");
        }

        if (PROTO_CHAP == l->lcp.auth_iwait) {
          l->lcp.auth_iwait = 0;
          if (0 == l->lcp.auth_ineed)    /* auth_ineed: 0, authentication by peer is not complete or no need to authentication,
                                                       !0, authentication by peer is complete */
          {
            /*
             * We've succeeded in our ``login''
             * If we're not expecting  the peer to authenticate (or he already
             * has), proceed to network phase.
             */
            chap_ReInit(&(l->chap));
            if (PHASE_AUTHENTICATE == l->phase)
            {
                l->phase = PHASE_NETWORK;
                l->ipcp.fsm.state = ST_CLOSED;
                fsm_Open(&(l->ipcp.fsm));
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "goto ipcp stage!\r\n");
            }
          }
        }
    }    /* end of rx-ed success */
    else    /* rx-ed fail */
    {
        /* chap->auth.in.name is already set up at CHALLENGE time, need NOT to print again */
        if (0 < len)
        {
          PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "Chap Input: fail with message\r\n");
        }
        else
        {
          PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "Chap Input: fail without message\r\n");
        }

        chap_Cleanup(&(l->chap));
        l->phase = PHASE_TERMINATE;
        fsm_Close(&(l->lcp.fsm));
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "goto lcp stage!\r\n");
    }    /* end of rx-ed fail */
  }

  ppp_m_freem(bp);
  return VOS_NULL_PTR;
}    /* chap_Input */


/*
   all the codes below, masked by liukai, are original codes in BSD,
   left them here to make diffences if needs to fix bugs
*/
#if 0
/*****************************************************************************
 函 数 名  : SavePppChallengeFrame
 功能描述  : 在DART工程中将消息码流中CHAP数据写回到CHAP全局变量中
 输入参数  : ucPppId - PPP链接ID
             pucData - 消息码流, 首字节指向PPP帧数据的首字节
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年12月10日
    作    者   : liukai
    修改内容   : Created

*****************************************************************************/
VOS_VOID SavePppChallengeFrame(VOS_UINT8 ucPppId, VOS_UINT8 *pucData)
{
    VOS_UINT16 usLen;
    const VOS_UINT8 ucLenghFieldPos = 5;
    const VOS_UINT8 ucLenghCodePos = 3;
    VOS_UINT8 *pucCurrData;
    VOS_UINT8  ucHigh;
    VOS_UINT8  ucLow;
    struct chap *pstChap;
    VOS_UINT8 *pucChallengeBuf;

    pucCurrData = pucData + ucLenghFieldPos;    /* point to Length Field */

    /* get the length of CHAP Challenge Frame */
    ucHigh = *pucCurrData;
    pucCurrData++;
    ucLow = *pucCurrData;
    usLen = (VOS_UINT16)((ucLow) | (((VOS_UINT16)(ucHigh))<<8));

    pucCurrData = pucData + ucLenghCodePos;    /* point to Code Field */
    pstChap = (&(PPP_LINK(ucPppId)->chap));
    pucChallengeBuf = pstChap->RecordData.BufChallenge;
    PS_MEM_CPY(pucChallengeBuf, pucCurrData, usLen);    /* save data */
    pstChap->RecordData.LenOfChallenge = usLen;
}
#endif

/*
   all the codes below, masked by liukai, are original codes in BSD,
   left them here to make diffences if needs to fix bugs
*/
#if 0
static void
ChapOutput_old(struct physical *physical, u_int code, u_int id,
	   const u_char *ptr, int count, const char *text)
{
  int plen;
  struct fsmheader lh;
  struct mbuf *bp;

  plen = sizeof(struct fsmheader) + count;
  lh.code = code;
  lh.id = id;
  lh.length = htons(plen);
  bp = m_get(plen, MB_CHAPOUT);
  memcpy(MBUF_CTOP(bp), &lh, sizeof(struct fsmheader));
  if (count)
    memcpy(MBUF_CTOP(bp) + sizeof(struct fsmheader), ptr, count);
  log_DumpBp(LogDEBUG, "ChapOutput", bp);
  if (text == NULL)
    log_Printf(LogPHASE, "Chap Output: %s\n", chapcodes[code]);
  else
    log_Printf(LogPHASE, "Chap Output: %s (%s)\n", chapcodes[code], text);
  link_PushPacket(&physical->link, bp, physical->dl->bundle,
                  LINK_QUEUES(&physical->link) - 1, PROTO_CHAP);
}

static char *
chap_BuildAnswer_old(char *name, char *key, u_char id, char *challenge, u_char type
#ifdef HAVE_DES
                 , int lanman
#endif
                )
{
  char *result;
#ifndef __GNU__
	char *digest;
#endif /* __GNU__ */
  size_t nlen, klen;

  nlen = strlen(name);
  klen = strlen(key);

#ifdef HAVE_DES
  if (type == 0x80) {
    char expkey[AUTHLEN << 2];
    MD4_CTX MD4context;
    int f;

    if ((result = malloc(1 + nlen + MS_CHAP_RESPONSE_LEN)) == NULL)
      return result;

    digest = result;					/* the response */
    *digest++ = MS_CHAP_RESPONSE_LEN;			/* 49 */
    memcpy(digest + MS_CHAP_RESPONSE_LEN, name, nlen);
    if (lanman) {
      memset(digest + 24, '\0', 25);
      mschap_LANMan(digest, challenge + 1, key);	/* LANMan response */
    } else {
      memset(digest, '\0', 25);
      digest += 24;

      for (f = 0; f < klen; f++) {
        expkey[2*f] = key[f];
        expkey[2*f+1] = '\0';
      }
      /*
       *           -----------
       * expkey = | k\0e\0y\0 |
       *           -----------
       */
      MD4Init(&MD4context);
      MD4Update(&MD4context, expkey, klen << 1);
      MD4Final(digest, &MD4context);

      /*
       *           ---- -------- ---------------- ------- ------
       * result = | 49 | LANMan | 16 byte digest | 9 * ? | name |
       *           ---- -------- ---------------- ------- ------
       */
      mschap_NT(digest, challenge + 1);
    }
    /*
     *           ---- -------- ------------- ----- ------
     *          |    |  struct MS_ChapResponse24  |      |
     * result = | 49 | LANMan  |  NT digest | 0/1 | name |
     *           ---- -------- ------------- ----- ------
     * where only one of LANMan & NT digest are set.
     */
  } else
#endif
  if ((result = malloc(nlen + 17)) != NULL) {
    /* Normal MD5 stuff */
#ifdef __GNU__
    _exit (240); /* Critical */
#else
    MD5_CTX MD5context;

    digest = result;
    *digest++ = 16;				/* value size */

    MD5Init(&MD5context);
    MD5Update(&MD5context, &id, 1);
    MD5Update(&MD5context, key, klen);
    MD5Update(&MD5context, challenge + 1, *challenge);
    MD5Final(digest, &MD5context);

    memcpy(digest + 16, name, nlen);
    /*
     *           ---- -------- ------
     * result = | 16 | digest | name |
     *           ---- -------- ------
     */
#endif
  }

  return result;
}

static void
chap_StartChild_old(struct chap *chap, char *prog, const char *name)
{
  char *argv[MAXARGS], *nargv[MAXARGS];
  int argc, fd;
  int in[2], out[2];
  pid_t pid;

  if (chap->child.fd != -1) {
    log_Printf(LogWARN, "Chap: %s: Program already running\n", prog);
    return;
  }

  if (pipe(in) == -1) {
    log_Printf(LogERROR, "Chap: pipe: %s\n", strerror(errno));
    return;
  }

  if (pipe(out) == -1) {
    log_Printf(LogERROR, "Chap: pipe: %s\n", strerror(errno));
    close(in[0]);
    close(in[1]);
    return;
  }

  pid = getpid();
  switch ((chap->child.pid = fork())) {
    case -1:
      log_Printf(LogERROR, "Chap: fork: %s\n", strerror(errno));
      close(in[0]);
      close(in[1]);
      close(out[0]);
      close(out[1]);
      chap->child.pid = 0;
      return;

    case 0:
      timer_TermService();

      if ((argc = command_Interpret(prog, strlen(prog), argv)) <= 0) {
        if (argc < 0) {
          log_Printf(LogWARN, "CHAP: Invalid command syntax\n");
          _exit(255);
        }
        _exit(0);
      }

      close(in[1]);
      close(out[0]);
      if (out[1] == STDIN_FILENO)
        out[1] = dup(out[1]);
      dup2(in[0], STDIN_FILENO);
      dup2(out[1], STDOUT_FILENO);
      close(STDERR_FILENO);
      if (open(_PATH_DEVNULL, O_RDWR) != STDERR_FILENO) {
        log_Printf(LogALERT, "Chap: Failed to open %s: %s\n",
                  _PATH_DEVNULL, strerror(errno));
        exit(1);
      }
      for (fd = getdtablesize(); fd > STDERR_FILENO; fd--)
        fcntl(fd, F_SETFD, 1);
#ifndef NOSUID
      setuid(ID0realuid());
#endif
      command_Expand(nargv, argc, (char const *const *)argv,
                     chap->auth.physical->dl->bundle, 0, pid);
      execvp(nargv[0], nargv);
      printf("exec() of %s failed: %s\n", nargv[0], strerror(errno));
      _exit(255);

    default:
      close(in[0]);
      close(out[1]);
      chap->child.fd = out[0];
      chap->child.buf.len = 0;
      write(in[1], chap->auth.in.name, strlen(chap->auth.in.name));
      write(in[1], "\n", 1);
      write(in[1], chap->challenge.peer + 1, *chap->challenge.peer);
      write(in[1], "\n", 1);
      write(in[1], name, strlen(name));
      write(in[1], "\n", 1);
      close(in[1]);
      break;
  }
}

static void
chap_Cleanup_old(struct chap *chap, int sig)
{
  if (chap->child.pid) {
    int status;

    close(chap->child.fd);
    chap->child.fd = -1;
    if (sig)
      kill(chap->child.pid, SIGTERM);
    chap->child.pid = 0;
    chap->child.buf.len = 0;

    if (wait(&status) == -1)
      log_Printf(LogERROR, "Chap: wait: %s\n", strerror(errno));
    else if (WIFSIGNALED(status))
      log_Printf(LogWARN, "Chap: Child received signal %d\n", WTERMSIG(status));
    else if (WIFEXITED(status) && WEXITSTATUS(status))
      log_Printf(LogERROR, "Chap: Child exited %d\n", WEXITSTATUS(status));
  }
  *chap->challenge.local = *chap->challenge.peer = '\0';
#ifdef HAVE_DES
  chap->peertries = 0;
#endif
}

static void
chap_Respond_old(struct chap *chap, char *name, char *key, u_char type
#ifdef HAVE_DES
             , int lm
#endif
            )
{
  u_char *ans;

  ans = chap_BuildAnswer(name, key, chap->auth.id, chap->challenge.peer, type
#ifdef HAVE_DES
                         , lm
#endif
                        );

  if (ans) {
    ChapOutput(chap->auth.physical, CHAP_RESPONSE, chap->auth.id,
               ans, *ans + 1 + strlen(name), name);
#ifdef HAVE_DES
    chap->NTRespSent = !lm;
#endif
    free(ans);
  } else
    ChapOutput(chap->auth.physical, CHAP_FAILURE, chap->auth.id,
               "Out of memory!", 14, NULL);
}

static int
chap_UpdateSet_old(struct fdescriptor *d, fd_set *r, fd_set *w, fd_set *e, int *n)
{
  struct chap *chap = descriptor2chap(d);

  if (r && chap && chap->child.fd != -1) {
    FD_SET(chap->child.fd, r);
    if (*n < chap->child.fd + 1)
      *n = chap->child.fd + 1;
    log_Printf(LogTIMER, "Chap: fdset(r) %d\n", chap->child.fd);
    return 1;
  }

  return 0;
}

static int
chap_IsSet_old(struct fdescriptor *d, const fd_set *fdset)
{
  struct chap *chap = descriptor2chap(d);

  return chap && chap->child.fd != -1 && FD_ISSET(chap->child.fd, fdset);
}

static void
chap_Read_old(struct fdescriptor *d, struct bundle *bundle, const fd_set *fdset)
{
  struct chap *chap = descriptor2chap(d);
  int got;

  got = read(chap->child.fd, chap->child.buf.ptr + chap->child.buf.len,
             sizeof chap->child.buf.ptr - chap->child.buf.len - 1);
  if (got == -1) {
    log_Printf(LogERROR, "Chap: Read: %s\n", strerror(errno));
    chap_Cleanup(chap, SIGTERM);
  } else if (got == 0) {
    log_Printf(LogWARN, "Chap: Read: Child terminated connection\n");
    chap_Cleanup(chap, SIGTERM);
  } else {
    char *name, *key, *end;

    chap->child.buf.len += got;
    chap->child.buf.ptr[chap->child.buf.len] = '\0';
    name = chap->child.buf.ptr;
    name += strspn(name, " \t");
    if ((key = strchr(name, '\n')) == NULL)
      end = NULL;
    else
      end = strchr(++key, '\n');

    if (end == NULL) {
      if (chap->child.buf.len == sizeof chap->child.buf.ptr - 1) {
        log_Printf(LogWARN, "Chap: Read: Input buffer overflow\n");
        chap_Cleanup(chap, SIGTERM);
      }
    } else {
#ifdef HAVE_DES
      int lanman = chap->auth.physical->link.lcp.his_authtype == 0x80 &&
                   ((chap->NTRespSent &&
                     IsAccepted(chap->auth.physical->link.lcp.cfg.chap80lm)) ||
                    !IsAccepted(chap->auth.physical->link.lcp.cfg.chap80nt));
#endif

      while (end >= name && strchr(" \t\r\n", *end))
        *end-- = '\0';
      end = key - 1;
      while (end >= name && strchr(" \t\r\n", *end))
        *end-- = '\0';
      key += strspn(key, " \t");

      chap_Respond(chap, name, key, chap->auth.physical->link.lcp.his_authtype
#ifdef HAVE_DES
                   , lanman
#endif
                  );
      chap_Cleanup(chap, 0);
    }
  }
}

static int
chap_Write_old(struct fdescriptor *d, struct bundle *bundle, const fd_set *fdset)
{
  /* We never want to write here ! */
  log_Printf(LogALERT, "chap_Write: Internal error: Bad call !\n");
  return 0;
}

static void
chap_Challenge_old(struct authinfo *authp)
{
  struct chap *chap = auth2chap(authp);
  int len, i;
  char *cp;

  len = strlen(authp->physical->dl->bundle->cfg.auth.name);

  if (!*chap->challenge.local) {    /* as each time, local is NULL, here is always true */
    randinit();
    cp = chap->challenge.local;

#ifndef NORADIUS
    if (*authp->physical->dl->bundle->radius.cfg.file) {
      /* For radius, our challenge is 16 readable NUL terminated bytes :*/
      *cp++ = 16;
      for (i = 0; i < 16; i++)
        *cp++ = (random() % 10) + '0';
    } else
#endif
    {
#ifdef HAVE_DES
      if (authp->physical->link.lcp.want_authtype == 0x80)
        *cp++ = 8;	/* MS does 8 byte callenges :-/ */
      else
#endif
        *cp++ = random() % (CHAPCHALLENGELEN-16) + 16;    /* 随机字串长度本身设为随机值, 放在local的第一个字节 */
      for (i = 0; i < *chap->challenge.local; i++)
        *cp++ = random() & 0xff;    /* 随机字串 */
    }
    memcpy(cp, authp->physical->dl->bundle->cfg.auth.name, len);
  }
  ChapOutput(authp->physical, CHAP_CHALLENGE, authp->id, chap->challenge.local,
	     1 + *chap->challenge.local + len, NULL);    /* 1: Value-Size, *local: 随机字串长度, len: Name length */
}

static void
chap_Success_old(struct authinfo *authp)
{
  datalink_GotAuthname(authp->physical->dl, authp->in.name);
  ChapOutput(authp->physical, CHAP_SUCCESS, authp->id, "Welcome!!", 10, NULL);
  authp->physical->link.lcp.auth_ineed = 0;
  if (Enabled(authp->physical->dl->bundle, OPT_UTMP))
    physical_Login(authp->physical, authp->in.name);

  if (authp->physical->link.lcp.auth_iwait == 0)
    /*
     * Either I didn't need to authenticate, or I've already been
     * told that I got the answer right.
     */
    datalink_AuthOk(authp->physical->dl);
}

static void
chap_Failure_old(struct authinfo *authp)
{
  ChapOutput(authp->physical, CHAP_FAILURE, authp->id, "Invalid!!", 9, NULL);
  datalink_AuthNotOk(authp->physical->dl);
}

static int
chap_Cmp_old(u_char type, char *myans, int mylen, char *hisans, int hislen
#ifdef HAVE_DES
         , int lm
#endif
        )
{
  if (mylen != hislen)
    return 0;
#ifdef HAVE_DES
  else if (type == 0x80) {
    int off = lm ? 0 : 24;

    if (memcmp(myans + off, hisans + off, 24))
      return 0;
  }
#endif
  else if (memcmp(myans, hisans, mylen))
    return 0;

  return 1;
}

#ifdef HAVE_DES
static int
chap_HaveAnotherGo_old(struct chap *chap)
{
  if (++chap->peertries < 3) {
    /* Give the peer another shot */
    *chap->challenge.local = '\0';
    chap_Challenge(&chap->auth);
    return 1;
  }

  return 0;
}
#endif

void
chap_Init_old(struct chap *chap, struct physical *p)
{
  chap->desc.type = CHAP_DESCRIPTOR;
  chap->desc.UpdateSet = chap_UpdateSet;
  chap->desc.IsSet = chap_IsSet;
  chap->desc.Read = chap_Read;
  chap->desc.Write = chap_Write;
  chap->child.pid = 0;
  chap->child.fd = -1;
  auth_Init(&chap->auth, p, chap_Challenge, chap_Success, chap_Failure);
  *chap->challenge.local = *chap->challenge.peer = '\0';
#ifdef HAVE_DES
  chap->NTRespSent = 0;
  chap->peertries = 0;
#endif
}

void
chap_ReInit_old(struct chap *chap)
{
  chap_Cleanup(chap, SIGTERM);
}

struct mbuf *
chap_Input_old(struct bundle *bundle, struct link *l, struct mbuf *bp)
{
  struct physical *p = link2physical(l);
  struct chap *chap = &p->dl->chap;
  char *name, *key, *ans;
  int len, nlen;
  u_char alen;
#ifdef HAVE_DES
  int lanman;
#endif

  if (p == NULL) {
    log_Printf(LogERROR, "chap_Input: Not a physical link - dropped\n");
    m_freem(bp);
    return NULL;
  }

  if (bundle_Phase(bundle) != PHASE_NETWORK &&
      bundle_Phase(bundle) != PHASE_AUTHENTICATE) {
    log_Printf(LogPHASE, "Unexpected chap input - dropped !\n");
    m_freem(bp);
    return NULL;
  }

  m_settype(bp, MB_CHAPIN);
  if ((bp = auth_ReadHeader(&chap->auth, bp)) == NULL &&
      ntohs(chap->auth.in.hdr.length) == 0)
    log_Printf(LogWARN, "Chap Input: Truncated header !\n");
  else if (chap->auth.in.hdr.code == 0 || chap->auth.in.hdr.code > MAXCHAPCODE)
    log_Printf(LogPHASE, "Chap Input: %d: Bad CHAP code !\n",
               chap->auth.in.hdr.code);
  else {
    len = m_length(bp);
    ans = NULL;

    if (chap->auth.in.hdr.code != CHAP_CHALLENGE &&
        chap->auth.id != chap->auth.in.hdr.id &&
        Enabled(bundle, OPT_IDCHECK)) {
      /* Wrong conversation dude ! */
      log_Printf(LogPHASE, "Chap Input: %s dropped (got id %d, not %d)\n",
                 chapcodes[chap->auth.in.hdr.code], chap->auth.in.hdr.id,
                 chap->auth.id);
      m_freem(bp);
      return NULL;
    }
    chap->auth.id = chap->auth.in.hdr.id;	/* We respond with this id */

#ifdef HAVE_DES
    lanman = 0;
#endif
    switch (chap->auth.in.hdr.code) {
      case CHAP_CHALLENGE:
        bp = mbuf_Read(bp, &alen, 1);
        len -= alen + 1;    /* len -= (alen + 1); */
        if (len < 0) {
          log_Printf(LogERROR, "Chap Input: Truncated challenge !\n");
          m_freem(bp);
          return NULL;
        }
        *chap->challenge.peer = alen;
        bp = mbuf_Read(bp, chap->challenge.peer + 1, alen);
        bp = auth_ReadName(&chap->auth, bp, len);
#ifdef HAVE_DES
        lanman = p->link.lcp.his_authtype == 0x80 &&
                 ((chap->NTRespSent && IsAccepted(p->link.lcp.cfg.chap80lm)) ||
                  !IsAccepted(p->link.lcp.cfg.chap80nt));
#endif
        break;

      case CHAP_RESPONSE:
        auth_StopTimer(&chap->auth);
        bp = mbuf_Read(bp, &alen, 1);    /* read HASH-Size */
        len -= alen + 1;    /* len -= (alen + 1);, len is length of Name Field */
        if (len < 0) {
          log_Printf(LogERROR, "Chap Input: Truncated response !\n");
          m_freem(bp);
          return NULL;
        }
        if ((ans = malloc(alen + 2)) == NULL) {
          log_Printf(LogERROR, "Chap Input: Out of memory !\n");
          m_freem(bp);
          return NULL;
        }
        *ans = chap->auth.id;
        bp = mbuf_Read(bp, ans + 1, alen);    /* cut HASH value */
        ans[alen+1] = '\0';    /* ans is (id, HASH, \0)*/
        bp = auth_ReadName(&chap->auth, bp, len);
#ifdef HAVE_DES
        lanman = alen == 49 && ans[alen] == 0;
#endif
        break;

      case CHAP_SUCCESS:
      case CHAP_FAILURE:
        /* chap->auth.in.name is already set up at CHALLENGE time */
        if ((ans = malloc(len + 1)) == NULL) {
          log_Printf(LogERROR, "Chap Input: Out of memory !\n");
          m_freem(bp);
          return NULL;
        }
        bp = mbuf_Read(bp, ans, len);
        ans[len] = '\0';
        break;
    }

    switch (chap->auth.in.hdr.code) {
      case CHAP_CHALLENGE:
      case CHAP_RESPONSE:
        if (*chap->auth.in.name)
          log_Printf(LogPHASE, "Chap Input: %s (%d bytes from %s%s)\n",
                     chapcodes[chap->auth.in.hdr.code], alen,
                     chap->auth.in.name,
#ifdef HAVE_DES
                     lanman && chap->auth.in.hdr.code == CHAP_RESPONSE ?
                     " - lanman" :
#endif
                     "");
        else
          log_Printf(LogPHASE, "Chap Input: %s (%d bytes%s)\n",
                     chapcodes[chap->auth.in.hdr.code], alen,
#ifdef HAVE_DES
                     lanman && chap->auth.in.hdr.code == CHAP_RESPONSE ?
                     " - lanman" :
#endif
                     "");
        break;

      case CHAP_SUCCESS:
      case CHAP_FAILURE:
        if (*ans)
          log_Printf(LogPHASE, "Chap Input: %s (%s)\n",
                     chapcodes[chap->auth.in.hdr.code], ans);
        else
          log_Printf(LogPHASE, "Chap Input: %s\n",
                     chapcodes[chap->auth.in.hdr.code]);
        break;
    }

    switch (chap->auth.in.hdr.code) {
      case CHAP_CHALLENGE:
        if (*bundle->cfg.auth.key == '!' && bundle->cfg.auth.key[1] != '!')
          chap_StartChild(chap, bundle->cfg.auth.key + 1,
                          bundle->cfg.auth.name);
        else
          chap_Respond(chap, bundle->cfg.auth.name, bundle->cfg.auth.key +
                       (*bundle->cfg.auth.key == '!' ? 1 : 0),
                       p->link.lcp.his_authtype
#ifdef HAVE_DES
                       , lanman
#endif
                      );
        break;

      case CHAP_RESPONSE:
        name = chap->auth.in.name;
        nlen = strlen(name);
#ifndef NORADIUS
        if (*bundle->radius.cfg.file) {
          u_char end;

          end = chap->challenge.local[*chap->challenge.local+1];
          chap->challenge.local[*chap->challenge.local+1] = '\0';
          radius_Authenticate(&bundle->radius, &chap->auth,
                              chap->auth.in.name, ans,
                              chap->challenge.local + 1);
          chap->challenge.local[*chap->challenge.local+1] = end;
        } else
#endif
        {
          key = auth_GetSecret(bundle, name, nlen, p);
          if (key) {
            char *myans;
#ifdef HAVE_DES
            if (lanman && !IsEnabled(p->link.lcp.cfg.chap80lm)) {
              log_Printf(LogPHASE, "Auth failure: LANMan not enabled\n");
              if (chap_HaveAnotherGo(chap))
                break;
              key = NULL;
            } else if (!lanman && !IsEnabled(p->link.lcp.cfg.chap80nt) &&
                       p->link.lcp.want_authtype == 0x80) {
              log_Printf(LogPHASE, "Auth failure: mschap not enabled\n");
              if (chap_HaveAnotherGo(chap))
                break;
              key = NULL;
            } else
#endif
            {
              myans = chap_BuildAnswer(name, key, chap->auth.id,
                                       chap->challenge.local,
                                       p->link.lcp.want_authtype
#ifdef HAVE_DES
                                       , lanman
#endif
                                      );
              if (myans == NULL)
                key = NULL;
              else {
                if (!chap_Cmp(p->link.lcp.want_authtype, myans + 1, *myans,
                              ans + 1, alen
#ifdef HAVE_DES
                              , lanman
#endif
                             ))
                  key = NULL;
                free(myans);
              }
            }
          }

          if (key)
            chap_Success(&chap->auth);
          else
            chap_Failure(&chap->auth);
        }

        break;

      case CHAP_SUCCESS:
        if (p->link.lcp.auth_iwait == PROTO_CHAP) {
          p->link.lcp.auth_iwait = 0;
          if (p->link.lcp.auth_ineed == 0)
            /*
             * We've succeeded in our ``login''
             * If we're not expecting  the peer to authenticate (or he already
             * has), proceed to network phase.
             */
            datalink_AuthOk(p->dl);
        }
        break;

      case CHAP_FAILURE:
        datalink_AuthNotOk(p->dl);
        break;
    }
    free(ans);
  }

  m_freem(bp);
  return NULL;
}
#endif

#endif /* #if(FEATURE_ON == FEATURE_PPP) */

