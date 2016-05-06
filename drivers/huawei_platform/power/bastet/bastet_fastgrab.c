
/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : bastet_fastgrab.c
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2015年09月30日
  最近修改   :
  功能描述   : 处理快抢技术Kernel层逻辑
  函数列表   :
  修改历史   :
  1.日    期   : 2015年09月30日
    作    者   : d00173029
    修改内容   : 创建文件
******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/spinlock.h>
#include <linux/file.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/err.h>
#include <linux/fs.h>
#include <linux/fdtable.h>
#include <linux/tcp.h>
#include <net/sock.h>
#include <net/ip.h>
#include <net/tcp.h>
#include <net/inet_sock.h>

#include <huawei_platform/power/bastet/bastet_utils.h>

/******************************************************************************
   2 宏定义
******************************************************************************/

/*****************************************************************************
  3 函数声明
*****************************************************************************/

/******************************************************************************
   4 私有定义
******************************************************************************/

/******************************************************************************
   5 全局变量定义
******************************************************************************/
BST_FG_APP_INFO_STRU    g_FastGrabAppInfo[ BST_FG_MAX_APP_NUMBER ];
/******************************************************************************
   6 函数实现
******************************************************************************/

/*****************************************************************************
 函 数 名  : BST_FG_Init
 功能描述  : 初始化快抢技术相关结构体
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年09月30日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
void BST_FG_Init( void )
{
    uint16_t        usLooper1;
    uint16_t        usLooper2;

    for( usLooper1=0; usLooper1<BST_FG_MAX_APP_NUMBER; usLooper1++ )
    {
        g_FastGrabAppInfo[ usLooper1 ].lUid     = BST_FG_INVALID_UID;
        g_FastGrabAppInfo[ usLooper1 ].usIndex  = usLooper1;
        spin_lock_init( &g_FastGrabAppInfo[ usLooper1 ].stLocker );
        for( usLooper2=0; usLooper2<BST_FG_MAX_KW_NUMBER; usLooper2++ )
        {
            g_FastGrabAppInfo[ usLooper1 ].pstKws[ usLooper2 ]
                                                = NULL;
        }
    }
}

/*****************************************************************************
 函 数 名  : BST_FG_ProcWXSock
 功能描述  : 处理微信相关Socket状态变化
 输入参数  : struct sock *pstSock,  sock结构对象
             int state              新的socket状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年09月30日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
static void BST_FG_ProcWXSock( struct sock *pstSock, int state )
{
    /**
     * If new socket is built, we think it to "waiting" state
     */
    if( TCP_ESTABLISHED == state )
    {
        pstSock->fg_Spec = BST_FG_WECHAT_WAIT_HONGBAO;
        BASTET_LOGI( "BST_FG_ProcWXSock Set To WAIT_HONGBAO, PTR=%p", pstSock );
    }
    /**
     * Only out put a log. But now wx socket is using "RST" but "Close", so this
     * can't be printed;
     */
    else if( TCP_CLOSING == state )
    {
        if( BST_FG_WECHAT_HONGBAO == pstSock->fg_Spec )
        {
            BASTET_LOGI( "BST_FG_ProcWXSock Hongbao_socket is Removed" );
        }
    }
    else
    {
        return;
    }
}
/*****************************************************************************
 函 数 名  : BST_FG_ProcWXPacket_DL
 功能描述  : 处理微信socket下行勾包，仅对push信道起作用
 输入参数  :
    struct sock    *pstSock,    sock对象
    uint8_t*        pData,      收到的下行数据(来自skbuff)
    uint32_t        ulLength,   承载的最大有效数据长度
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年09月30日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
static uint8_t BST_FG_ProcWXPacket_DL(
    struct sock    *pstSock,
    uint8_t*        pData,
    uint32_t        ulLength )
{
    BST_FG_KEYWORD_STRU    *pstKwdIns   = NULL;
    static uint32_t         usHbCounter = 0;

    if( BST_FG_WECHAT_PUSH != pstSock->fg_Spec )
    {
        return 0;
    }
    /**
     * Set the "PUSH"( 0 0 4 ) SIP-Command to be compared object.
     */
    pstKwdIns                       = BST_FG_GetAppIns( BST_FG_IDX_WECHAT )->pstKws[BST_FG_FLAG_WECHAT_PUSH];
    if( NULL == pstKwdIns )
    {
        return 0;
    }
    /**
     * probe log, get the packet head
     */
    if( ulLength >= 3 )
    {
        BASTET_LOGI( "BST_FG_ProcWXPacket_DL length=%d, Data[0]=%d, Data[1]=%d, Data[2]=%d",
                     ulLength, pData[0], pData[1], pData[2] );
    }
    /**
     * match the length of XML to dl packet
     */
    if( ( ulLength > pstKwdIns->stLenPorp.usMax )
      ||( ulLength < pstKwdIns->stLenPorp.usMin ) )
    {
        return 0;
    }
    /**
     * match keywords
     */
    if( 0 == memcmp( &pstKwdIns->stKeyWord.aucData[0],
        pData, pstKwdIns->stKeyWord.usTotLen ) )
    {
        usHbCounter++;
        BASTET_LOGI( "BST_FG_ProcWXPacket_DL Got Successfully, Total=%d", usHbCounter );
        return 1;
    }
    return 0;
}

/*****************************************************************************
 函 数 名  : BST_FG_ProcWXPacket_UL
 功能描述  : 处理微信上行数据勾包
 输入参数  :
    struct sock    *pstSock,    sock对象
    uint8_t*        pData,      收到的下行数据(强制转换msg，iov用户空间数据)
    uint32_t        ulLength,   承载的最大有效数据长度
 输出参数  : 无
 返 回 值  :
    0               没有关键数据信息
    1               有关键数据信息
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年09月30日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
static uint8_t BST_FG_ProcWXPacket_UL(
    struct sock    *pstSock,
    uint8_t*        pData,
    uint32_t        ulLength )
{
    BST_FG_KEYWORD_STRU    *pstKwdIns   = NULL;
    char                   *pcFound     = NULL;
    char                   *pUsrData    = NULL;
    struct msghdr          *pUsrMsgHdr  = NULL;

    /**
     * If this sock has been matched tob HONGBAO-Server connection,
     * return 1 direction to let HP data sending.
     */
    if( BST_FG_WECHAT_HONGBAO == pstSock->fg_Spec )
    {
        BASTET_LOGI( "BST_FG_ProcWXPacket_UL Hongbao_socket is sending" );
        return 1;
    }
    /**
     * If this sock is "WAITING" to be matched state, here will Match the first sending packet
     * of this sock to find "hongbao"-URL message.
     * ATENTION: This function only execute matching one time per sock.
     */
    if( BST_FG_WECHAT_WAIT_HONGBAO == pstSock->fg_Spec )
    {
        /**
         * Set the "hongbao"-URL to be compared object.
         */
        pstKwdIns           = BST_FG_GetAppIns( BST_FG_IDX_WECHAT )->pstKws[BST_FG_FLAG_WECHAT_GET];
        if( NULL == pstKwdIns )
        {
            return 0;
        }
        /**
         * too short.
         */
        if( ulLength < pstKwdIns->stLenPorp.usCopy )
        {
            BST_FG_SetSockSpecial( pstSock, BST_FG_NO_SPEC );
            return 0;
        }
        /**
         * Think it to be a common sock firstly.
         */
        pstSock->fg_Spec    = BST_FG_NO_SPEC;
        pUsrData            = ( char *)kmalloc( pstKwdIns->stLenPorp.usCopy, GFP_ATOMIC );
        if( NULL == pUsrData )
        {
            return 0;
        }
        /**
         * Copy data from usr space. Set the last byte to '0' for strstr input.
         */
        pUsrMsgHdr          = ( struct msghdr * )pData;
        if( copy_from_user( pUsrData, pUsrMsgHdr->msg_iov->iov_base, pstKwdIns->stLenPorp.usCopy ) )
        {
            kfree( pUsrData );
            return 0;
        }
        pUsrData[ pstKwdIns->stLenPorp.usCopy - 1] = 0;
        pcFound             = strstr( (const char *)pUsrData,
                                      (const char *)&pstKwdIns->stKeyWord.aucData[0] );
        kfree( pUsrData );

        if( NULL == pcFound )
        {
            pstSock->fg_Spec = BST_FG_NO_SPEC;
            return 0;
        }
        else
        {
            BST_FG_SetSockSpecial( pstSock, BST_FG_WECHAT_HONGBAO );
            BASTET_LOGI( "BST_FG_ProcWXPacket_UL Find New Hongbao_socket" );
            return 1;
        }
    }
    return 0;
}

/*****************************************************************************
 函 数 名  : BST_FG_ProcWXPacket
 功能描述  : 处理微信的勾包
 输入参数  :
    struct sock    *pstSock,    sock对象
    uint8_t*        pData,      收到的数据
    uint32_t        ulLength,   承载的最大有效数据长度
    uint32_t        ulRole      收发方向
 输出参数  : 无
 返 回 值  :
    0               没有关键数据信息
    1               有关键数据信息
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年09月30日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
static uint8_t BST_FG_ProcWXPacket(
    struct sock    *pstSock,
    uint8_t*        pData,
    uint32_t        ulLength,
    uint32_t        ulRole )
{
    uint8_t         ucRtn   = 0;
    /**
     * Call UL/DL packet proc, according to ROLE
     */
    if( BST_FG_ROLE_RCVER == ulRole )
    {
        ucRtn               = BST_FG_ProcWXPacket_DL( pstSock, pData, ulLength );
    }
    else if( BST_FG_ROLE_SNDER == ulRole )
    {
        ucRtn               = BST_FG_ProcWXPacket_UL( pstSock, pData, ulLength );
    }
    return ucRtn;
}

/*****************************************************************************
 函 数 名  : BST_FG_HookPacket
 输入参数  : 对外接口，处理外部socket收发数据勾包
    struct sock    *pstSock,    sock对象
    uint8_t*        pData,      收到的数据
    uint32_t        ulLength,   承载的最大有效数据长度
    uint32_t        ulRole      收发方向
 输出参数  : 无
 返 回 值  :
    0               没有关键数据信息
    1               有关键数据信息
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年09月30日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
uint8_t BST_FG_HookPacket(
    struct sock    *pstSock,
    uint8_t*        pData,
    uint32_t        ulLength,
    uint32_t        ulRole )
{
    uid_t       lSockUid    = 0;
    uint8_t     ucRtn       = 0;
    uint16_t    usIdx       = BST_FG_IDX_INVALID_APP;

    /**
     * Get and find the uid in fast-grab message information list.
     */
    lSockUid                = sock_i_uid( pstSock );
    for( usIdx=0; usIdx<BST_FG_MAX_APP_NUMBER; usIdx++ )
    {
        if( lSockUid == g_FastGrabAppInfo[usIdx].lUid )
        {
            break;
        }
    }
    if( !BST_FG_IsAppIdxValid(usIdx) )
    {
        return 0;
    }
    BASTET_LOGI( "BST_FG_Hook1  Length=%d, Role=%d, sk_state=%d",
                 ulLength, ulRole, pstSock->fg_Spec );
    /**
     * Call different packet proc according the Application Name(Index).
     */
    switch( usIdx )
    {
        case BST_FG_IDX_WECHAT:
            ucRtn           = BST_FG_ProcWXPacket( pstSock, pData, ulLength, ulRole );
            if( ucRtn )
            {
                post_indicate_packet( BST_IND_FG_KEY_MSG, &lSockUid, sizeof( uid_t ) );
            }
            break;

        default:
            break;
    }
    return ucRtn;
}

/*****************************************************************************
 函 数 名  : BST_FG_SetHongbaoPushSock
 功能描述  : 找到并设置微信的PUSH-Sock
 输入参数  :
    int32_t     tid_num,    共多少个pid需要匹配
    int32_t    *tids        pid内容信息列表
 输出参数  : 无
 返 回 值  : 匹配出错情况信息
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年09月30日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
static int BST_FG_SetHongbaoPushSock( int32_t tid_num, int32_t *tids )
{
	struct task_struct     *pstTask     = NULL;
	struct files_struct    *pstFiles    = NULL;
	struct fdtable         *pstFdt      = NULL;
	struct sock            *pstSock     = NULL;
	struct sock            *pstSockReg  = NULL;
    struct inet_sock       *pstInet     = NULL;
    uint16_t                usLooper    = 0;
    int                     fd          = -1;
    uint16_t                usFoundPort = 0;
    int                     lFoundFd    = -1;

    /**
     * use pid to proc.
     */
	for( usLooper = 0; usLooper < tid_num; usLooper++ )
    {
        /**
         * Find task message head
         */
		pstTask             = find_task_by_vpid(tids[usLooper]);
		if(  NULL == pstTask )
        {
            BASTET_LOGE( "BST_FG_SetHongbaoPushSock pstTask error" );
			return -EFAULT;
        }
        /**
         * Find File sys head according to task
         */
		pstFiles            = pstTask->files;
		if( NULL == pstFiles )
        {
            BASTET_LOGE( "BST_FG_SetHongbaoPushSock pstFiles error" );
			return -EFAULT;
		}

        /**
         * list the fd table
         */
		pstFdt              = files_fdtable(pstFiles);
		for (fd = 0; fd < pstFdt->max_fds; fd++)
        {
            /**
             * check the state, ip-addr, port-num of this sock
             */
        	pstSock         = get_sock_by_fd_pid(fd, tids[usLooper]);
        	if( NULL == pstSock )
            {
        		continue;
        	}
        	if( pstSock->sk_state != TCP_ESTABLISHED )
            {
		        sock_put(pstSock);
        		continue;
        	}
        	if( pstSock->sk_socket->type != SOCK_STREAM )
            {
		        sock_put(pstSock);
        		continue;
        	}
            pstInet         = inet_sk(pstSock);
        	if( NULL == pstInet )
            {
				sock_put(pstSock);
        		continue;
        	}
            if( ( BST_FG_INVALID_INET_ADDR == pstInet->inet_daddr)
             && ( BST_FG_INVALID_INET_ADDR == pstInet->inet_dport ) )
            {
				sock_put(pstSock);
        		continue;
            }

            /**
             * If there no sock be found, set the ptr to tmp-ptr,
             */
            if( NULL == pstSockReg )
            {
                lFoundFd    = fd;
                usFoundPort = pstInet->inet_sport;
                pstSockReg  = pstSock;
            }
            else
            {
                /**
                 * If there is a sock has been recorded, we will check fd/port to judge if it is the same one.
                 * If it's another one, it means that there is not only one sock in this uid, unsuccessful.
                 */
				if( ( fd == lFoundFd )&& ( usFoundPort == pstInet->inet_sport) )
                {
					sock_put(pstSock);
					continue;
				}
                else
                {
					sock_put(pstSock);
					sock_put(pstSockReg);
                    BASTET_LOGI( "BST_FG_SetHongbaoPushSock More than One Push Socket Found" );
				    return 0;
                }
            }
		}
	}
    if( NULL != pstSockReg )
    {
        /**
         * record the PUSH special flag to this sock
         */
        BST_FG_SetSockSpecial( pstSockReg, BST_FG_WECHAT_PUSH );
		sock_put(pstSockReg);
        BASTET_LOGI( "BST_FG_SetHongbaoPushSock Found Success!" );
    }
    return 0;
}

/*****************************************************************************
 函 数 名  : BST_FG_SaveKeyword
 功能描述  : 保存应用匹配关键字信息
 输入参数  : unsigned long arg  用户空间iov指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年09月30日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
static void BST_FG_SaveKeyword( unsigned long arg )
{
    void __user                *argp = (void __user *)arg;
    BST_FG_APP_INFO_STRU       *pstAppIns   = NULL;
    BST_FG_KEYWORD_STRU        *pstKwdSrc   = NULL;
    BST_FG_KEYWORD_STRU        *pstKwdDst   = NULL;
    BST_FG_KWS_COMM_STRU        stKwsComm   = { 0 };
    uint16_t                    usCopyed    = 0;
    uint16_t                    usLooper    = 0;

    /**
     * Get keyword head information from usr space
     */
    if( copy_from_user( &stKwsComm, argp, sizeof( BST_FG_KWS_COMM_STRU ) ) )
    {
        BASTET_LOGE( "BST_FG_SaveKeyword copy_from_user stKwsComm error" );
        return;
    }
    if( !BST_FG_IsAppIdxValid( stKwsComm.usIndex ) )
    {
        return;
    }
    BASTET_LOGI( "BST_FG_SaveKeyword stKwsComm.usIndex=%d", stKwsComm.usIndex );
    pstKwdSrc                           = ( BST_FG_KEYWORD_STRU *)kmalloc(
                                            sizeof( BST_FG_KEYWORD_STRU ), GFP_ATOMIC );
    if( NULL == pstKwdSrc )
    {
        return;
    }
    pstAppIns                           = BST_FG_GetAppIns( stKwsComm.usIndex );
    usLooper                            = 0;
    spin_lock_bh( &pstAppIns->stLocker );
    while( 1 )
    {
        /**
         * Get keyword data structure from usr space
         */
        if( copy_from_user( pstKwdSrc,
                            (uint8_t *)argp + usCopyed + sizeof( BST_FG_KWS_COMM_STRU ),
                            sizeof( BST_FG_KEYWORD_STRU ) ) )
        {
            BASTET_LOGE( "BST_FG_SaveKeyword copy_from_user pstKwdSrc error" );
            break;
        }
        pstKwdDst                       = ( BST_FG_KEYWORD_STRU *)kmalloc(
                                           sizeof( BST_FG_KEYWORD_STRU ) + pstKwdSrc->stKeyWord.usTotLen,
                                           GFP_ATOMIC );
        if( NULL == pstKwdDst )
        {
            break;
        }
        memcpy( pstKwdDst, pstKwdSrc, sizeof( BST_FG_KEYWORD_STRU ) );
        usCopyed                       += sizeof( BST_FG_KEYWORD_STRU );
        if( pstKwdSrc->stKeyWord.usTotLen > 0 )
        {
            /**
             * Get keyword data block from usr space
             */
            if( copy_from_user( &pstKwdDst->stKeyWord.aucData[0],
                                (uint8_t *)argp + usCopyed+ sizeof( BST_FG_KWS_COMM_STRU ),
                                pstKwdSrc->stKeyWord.usTotLen ) )
            {
                BASTET_LOGE( "BST_FG_SaveKeyword copy_from_user aucData error" );
                kfree( pstKwdDst );
                break;
            }
            usCopyed                   += pstKwdSrc->stKeyWord.usTotLen;
        }
        if( NULL != pstAppIns->pstKws[ usLooper ] )
        {
            kfree( pstAppIns->pstKws[ usLooper ] );
        }

        pstAppIns->pstKws[ usLooper ]   = pstKwdDst;
        usLooper                       += 1;

        if( usCopyed >= stKwsComm.usKeyLength )
        {
            break;
        }
    }
    kfree( pstKwdSrc );
    spin_unlock_bh( &pstAppIns->stLocker );
}

/*****************************************************************************
 函 数 名  : BST_FG_SaveUidInfo
 功能描述  : 保存对应应用的UID更新信息
 输入参数  : unsigned long arg  用户空间iov指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年09月30日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
static void BST_FG_SaveUidInfo( unsigned long arg )
{
    void __user                *argp = (void __user *)arg;
    BST_FG_APP_INFO_STRU       *pstAppIns   = NULL;
    BST_FG_UID_COMM_STRU        stUidComm   = { 0 };

    /**
     * Get uid message structure from usr space
     */
    if( copy_from_user( &stUidComm, argp, sizeof( BST_FG_UID_COMM_STRU ) ) )
    {
        BASTET_LOGE( "BST_FG_SaveUidInfo copy_from_user error" );
        return;
    }
    if( !BST_FG_IsAppIdxValid( stUidComm.usIndex ) )
    {
        return;
    }
    pstAppIns                           = BST_FG_GetAppIns( stUidComm.usIndex );
    spin_lock_bh( &pstAppIns->stLocker );
    pstAppIns->lUid                     = stUidComm.lUid;
    BASTET_LOGI( "BST_FG_SaveUidInfo app_index=%d, uid=%d", pstAppIns->usIndex, pstAppIns->lUid );
    spin_unlock_bh( &pstAppIns->stLocker );
}

/*****************************************************************************
 函 数 名  : BST_FG_SaveTidInfo
 功能描述  : 获取承载UID中关键PID信息列表
 输入参数  : unsigned long arg  用户空间iov指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年09月30日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
static void BST_FG_SaveTidInfo( unsigned long arg )
{
    void __user                *argp = (void __user *)arg;
    BST_FG_APP_INFO_STRU       *pstAppIns   = NULL;
    int32_t                    *plTids      = NULL;
    BST_FG_TID_COMM_STRU        stTidComm   = { 0 };
    int32_t                     lTotlen     = 0;

    /**
     * Get tid message structure from usr space
     */
    if( copy_from_user( &stTidComm, argp, sizeof( BST_FG_TID_COMM_STRU ) ) )
    {
        BASTET_LOGE( "BST_FG_SaveTidInfo copy_from_user stTidComm error" );
        return;
    }
    if( !BST_FG_IsAppIdxValid( stTidComm.usIndex ) )
    {
        return;
    }
    lTotlen                             = stTidComm.usTotle * sizeof( int32_t );
    plTids                              = ( int32_t *)kmalloc( lTotlen, GFP_ATOMIC );
    if( NULL == plTids )
    {
        return;
    }
    /**
     * Get tid list from usr space
     */
    if( copy_from_user( plTids, (uint8_t *)argp + sizeof( BST_FG_TID_COMM_STRU ), lTotlen ) )
    {
        BASTET_LOGE( "BST_FG_SaveTidInfo copy_from_user plTids error" );
        kfree( plTids );
        return;
    }
    pstAppIns                           = BST_FG_GetAppIns( stTidComm.usIndex );
    spin_lock_bh( &pstAppIns->stLocker );

    if( !BST_FG_IsUidValid( pstAppIns->lUid ) )
    {
        spin_unlock_bh( &pstAppIns->stLocker );
        kfree( plTids );
        return;
    }
    switch( stTidComm.usIndex )
    {
        case BST_FG_IDX_WECHAT:
            /**
             * If wechat, find the push socket according the pid message
             */
            BST_FG_SetHongbaoPushSock( stTidComm.usTotle, plTids );
            break;

        default:
            break;
    }
    kfree( plTids );
    spin_unlock_bh( &pstAppIns->stLocker );
}

/*****************************************************************************
 函 数 名  : BST_FG_IoCtrl
 功能描述  : Fast-grab技术对外IoCtrl接口
 输入参数  : unsigned long arg  用户空间iov指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年09月30日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
void BST_FG_IoCtrl( unsigned long arg )
{
    void __user        *argp = (void __user *)arg;
    fastgrab_info       stIoCmd;

    if( NULL == argp )
    {
        return;
    }
    /**
     * Copy io ctrl message of fast-grab from usr space.
     */
    if( copy_from_user( &stIoCmd, argp, sizeof( fastgrab_info ) ) )
    {
        BASTET_LOGE( "BST_FG_IoCtrl copy_from_user error" );
        return;
    }
    BASTET_LOGI( "BST_FG_IoCtrl command=%d, msg_len=%d",stIoCmd.cmd, stIoCmd.len );

    /**
     * Call branched function according to the fast-grab command.
     */
    switch( stIoCmd.cmd )
    {
        case CMD_LOAD_KEYWORDS:
            BST_FG_SaveKeyword( arg + sizeof( fastgrab_info ) );
            break;
        case CMD_UPDATE_UID:
            BST_FG_SaveUidInfo( arg + sizeof( fastgrab_info ) );
            break;
        case CMD_UPDATE_TID:
            BST_FG_SaveTidInfo( arg + sizeof( fastgrab_info ) );
            break;
        default:
            break;
    }
}

/*****************************************************************************
 函 数 名  : BST_FG_CheckSockUid
 功能描述  : 处理uid相关的socket状态变化信息
 输入参数  : struct sock *pstSock,  sock结构对象
             int state              新的socket状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :
 修改历史  :
    1.日    期   : 2015年09月30日
      作    者   : d00173029
      修改内容   : 新生成函数
*****************************************************************************/
void BST_FG_CheckSockUid( struct sock *pstSock, int state )
{
	uid_t           lUid    = BST_FG_INVALID_UID;
    uint16_t        usIdx   = BST_FG_IDX_INVALID_APP;

    /**
     * Judge the state if it's should be cared.
     */
    if( !BST_FG_IsCaredSkState( state ) )
    {
        return;
    }
    /**
     * Reset the sock fg special flag to inited state.
     */
    BST_FG_InitSockSpec( pstSock );
    lUid            = sock_i_uid( pstSock );
    if( !BST_FG_IsUidValid( lUid ) )
    {
        return;
    }
    /**
     * Find the application name(index) according to uid.
     */
    lUid                    = sock_i_uid( pstSock );
    for( usIdx=0; usIdx<BST_FG_MAX_APP_NUMBER; usIdx++ )
    {
        if( lUid == g_FastGrabAppInfo[ usIdx ].lUid )
        {
            BASTET_LOGI( "BST_FG_CheckSockUid Cared Uid Found, uid=%d", lUid );
            post_indicate_packet( BST_IND_FG_UID_SOCK_CHG, &lUid, sizeof( uid_t ) );
            break;
        }
    }
    if( !BST_FG_IsAppIdxValid(usIdx) )
    {
        return;
    }
    BASTET_LOGI( "BST_FG_CheckSockUid AppIdx=%d ", usIdx );
    /**
     * Call branched function of different application.
     */
    switch( usIdx )
    {
        case BST_FG_IDX_WECHAT:
            BST_FG_ProcWXSock( pstSock, state );
            break;

        default:
            break;
    }
}

