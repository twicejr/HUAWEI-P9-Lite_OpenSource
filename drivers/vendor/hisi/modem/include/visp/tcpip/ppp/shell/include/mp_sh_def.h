/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                               mp_sh_def.h
 *
 *  Project Code: VISP1.5
 *   Module Name: MP
 *  Date Created: 2005-09-30
 *        Author: songrujie
 *   Description: VISP3 MP component，macro define
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2005-09-28      songrujie       Create
 *  2006-03-31      ZhuKun          Adjust for D00663
 *  2006-04-21      ZhuKun          Adjust for D00876
 *
 *************************************************************************/
 
#ifndef _MP_SH_DEF_H_
#define _MP_SH_DEF_H_

#ifdef  __cplusplus
extern "C"{
#endif

/* 每次从MP接收队列中取出报文的数目; from 40 to 200 */
#define MP_GET_FROM_QUE                 200 

/* y43322 add for visp3 2005/09/24 重新定义的SHOW的消息类型*/
#define MSG_BASE_MP_SHOW                20
#define MSG_MP_DISP_GROUP               (MSG_BASE_MP_SHOW +1)   /*获取MP-group的MP信息*/
#define MSG_MP_DISP_FIRST_VA            (MSG_BASE_MP_SHOW +2)   /*获取第一个VA的MP信息*/
#define MSG_MP_DISP_NEXT_VA             (MSG_BASE_MP_SHOW +3)   /*获取下一个VA的MP信息*/

#define MP_DISP_IO_TIMEOUT_LIMIT        4000                    /* 分布式show的接口板同步取的超时时间 */

#define MSG_MP_GET_MULTILINK_DESCR      (MSG_BASE_MP_SHOW+5)    /*取得子通道所绑定的父接口的描述信息*/
#define MSG_MP_MIB_MULTILINKTABLE_INFO  (MSG_BASE_MP_SHOW+6)    /*获取父通道信息表*/
#define MSG_MP_MIB_MEMBERLINKTABLE_INFO (MSG_BASE_MP_SHOW+7)    /*获取子通道信息表*/

/*IPC通信消息类型*/
#define MP_ADD_FATHER_INDEX             1
#define MP_DEL_FATHER_INDEX             2
#define MP_ADD_SON_INDEX                3
#define MP_DEL_SON_INDEX                4
#define MP_RESP_FATHER_INDEX_TO_VT      5
#define MP_RESP_FATHER_INDEX_TO_SON     6
/*-------------------------------------------------------------*/
/*              以下消息由施勇根据绑定流程添加                 */
/*-------------------------------------------------------------*/
/* 其中Up,Down的含义同ppp状态机中的含义 */
#define MSG_MP_FIND_FATHER_CHANEL       7
#define MSG_MP_NOTIFY_IO_FATHER_CHANEL  8
#define MSG_MP_SON_UP                   9
#define MSG_MP_SON_DOWN                 10
#define MSG_MP_CLOSE_SON                11
#define MSG_MP_OPEN_SON                 12
#define MSG_MP_FATHER_DOWN              13
#define MSG_MP_GET_DISCR_ADDR           14
#define MSG_MP_SEND_DISCR_ADDR          15

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _MP_SH_DEF_H_ */
