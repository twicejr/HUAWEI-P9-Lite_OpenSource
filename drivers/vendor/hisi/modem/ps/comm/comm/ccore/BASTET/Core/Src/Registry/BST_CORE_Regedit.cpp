

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "BST_CORE_Regedit.h"
#include "BST_DBG_MemLeak.h"
#include "BST_OS_Memory.h"
#include "BST_DSPP_Define.h"
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_CORE_REGEDIT_CPP
/*lint +e767*/
/******************************************************************************
   2 函数实现
******************************************************************************/


BST_CORE_CRegedit *BST_CORE_CRegedit::GetInstance ( BST_VOID )
{
    static BST_CORE_CRegedit           *pcInstance = BST_NULL_PTR;

    if ( BST_NULL_PTR == pcInstance )
    {
        pcInstance                      = new BST_CORE_CRegedit;
    }
    return pcInstance;
}

BST_UINT16 BST_CORE_CRegedit::GetLen(
    BST_OBJT_ADDR_T            usObjtAddr,
    BST_OFST_ADDR_T            usOfstAddr,
    BST_CORE_PID_ENUM_UINT16   enParamId )
{
    BST_CORE_PIDNODE_STRU             *pRegParam;

    pRegParam                           = Select ( usObjtAddr, usOfstAddr, enParamId );
    if ( BST_NULL_PTR == pRegParam )
    {
        BST_RLS_LOG( "BST_CORE_CRegedit::GetLen pRegParam=NULL" );
        return 0;
    }
    return pRegParam->stParamInfo.usLen;
}

BST_UINT16 BST_CORE_CRegedit::Inquire(
    BST_OBJT_ADDR_T           usObjtAddr,
    BST_OFST_ADDR_T           usOfstAddr,
    BST_CORE_PID_ENUM_UINT16  enParamId,
    BST_UINT16                usDataSize,
    BST_VOID                 *const pData)
{
    BST_CORE_REGNODE_STRU          *pstTaskNode;
    BST_CORE_PIDNODE_STRU          *pstPidNode;
    BST_UINT16                      usInquireLen;

    if ( BST_NULL_PTR == pData )
    {
        return 0;
    }
    pstTaskNode                     = Select ( usObjtAddr, usOfstAddr );
    usInquireLen                    = 0;
    if ( BST_NULL_PTR == pstTaskNode )
    {
        BST_RLS_LOG( "BST_CORE_CRegedit::Inquire pstTaskNode=NULL" );
        return 0;
    }
    if ( BST_NULL_PTR == pstTaskNode->pcApAItf )
    {
        BST_RLS_LOG( "BST_CORE_CRegedit::Inquire pcCallBack=NULL" );
        return 0;
    }
    for( pstPidNode  = ( BST_CORE_PIDNODE_STRU * )
                        lstFirst( &pstTaskNode->RegParamList ); 
       ( pstPidNode != BST_NULL_PTR );
         pstPidNode  = ( BST_CORE_PIDNODE_STRU * )
                        lstNext( ( NODE * )pstPidNode ) )
    {
        if ( pstPidNode->stParamInfo.enPid != enParamId )
        {
            continue;
        }
        usInquireLen            = pstTaskNode->pcApAItf->Inquired
                                  ( enParamId, usDataSize, pData );
        if ( BST_CORE_INVALID_INQUIRED_LEN == usInquireLen )
        {
            BST_RLS_LOG( "Regedit::Inquire Error: CallBack No Item Fail!" );
            return 0;
        }
        if ( 0 != usInquireLen )
        {
            return usInquireLen;
        }
        /* If the Call-back return 0, We will Try to find it in Pid Table */
        if ( 0 == pstPidNode->stParamInfo.usLen )
        {
            BST_RLS_LOG( "Regedit::Inquire Error: usLen = 0!" );
            return 0;
        }
        if ( usDataSize < pstPidNode->stParamInfo.usLen )
        {
            BST_RLS_LOG2( "Regedit::Inquire Error: Size Fail! usData=u%, param_len=%u",\
                          usDataSize, pstPidNode->stParamInfo.usLen );
            return 0;
        }
        if ( BST_NULL_PTR == pstPidNode->stParamInfo.pvContent )
        {
            BST_RLS_LOG( "Regedit::Inquire Error: pvContent Void!" );
            return 0;
        }
        BST_OS_MEMCPY ( pData, pstPidNode->stParamInfo.pvContent, pstPidNode->stParamInfo.usLen );
        return pstPidNode->stParamInfo.usLen;
    }
    return 0;
}


BST_ERR_ENUM_UINT8  BST_CORE_CRegedit::Config(
    BST_OBJT_ADDR_T             usObjtAddr,
    BST_OFST_ADDR_T             usOfstAddr,
    const BST_CORE_PID_STRU    *pstRegParam )
{
    if ( BST_NULL_PTR == pstRegParam )
    {
        return BST_ERR_INVALID_PTR;
    }
    return ( Config ( usObjtAddr,
                      usOfstAddr,
                      pstRegParam->enPid,
                      pstRegParam->usLen,
                      pstRegParam->pvContent ) );
}

BST_ERR_ENUM_UINT8 BST_CORE_CRegedit::Save(
    BST_CORE_CAPACallBack      *pCallBack,
    BST_CORE_PIDNODE_STRU      *pstPid,
    BST_UINT16                  usDataLen,
    BST_VOID                   *pData )
{
    BST_CORE_PID_LUT_STRU          *pstParamAttri;
    BST_UINT8                      *pNewData;
    BST_ERR_ENUM_UINT8              enRet;

    if ( BST_TRUE != InputCheck( pstPid->stParamInfo.enPid, usDataLen, pData ) )
    {
        BST_RLS_LOG( "BST_CORE_CRegedit::Save InputCheck Err" );
        return BST_ERR_PAR_OVERRUN;
    }
    pstParamAttri                   = BST_CORE_GetPidHandle( pstPid->stParamInfo.enPid );
    if ( BST_NULL_PTR  == pstParamAttri )
    {
        BST_RLS_LOG( "BST_CORE_CRegedit::Save BST_CORE_GetPidHandle Err" );
        return BST_ERR_INVALID_PTR;
    }

    if ( ( BST_NULL_PTR  == pstPid->stParamInfo.pvContent )
      || ( BST_CORE_PID_VAR_LEN == pstParamAttri->enLenType ) )
    {
        if ( BST_NULL_PTR == pCallBack )
        {
            BST_RLS_LOG( "BST_CORE_CRegedit::Save pstPid->pcCallBack=NULL" );
            return BST_ERR_INVALID_PTR;
        }
        enRet                   = pCallBack->Configed ( pstPid->stParamInfo.enPid,
                                                        usDataLen,
                                                        ( void * )pData,
                                                        &pNewData );
        if ( BST_NO_ERROR_MSG == enRet )
        {
            if ( BST_NULL_PTR != pNewData )
            {
                pstPid->stParamInfo.pvContent = pNewData;
                pstPid->stParamInfo.usLen     = usDataLen;
            }
        }
    }
    else if ( usDataLen == pstPid->stParamInfo.usLen )
    {
        if( ( BST_NULL_PTR != pCallBack )
          &&( BST_TRUE == pstPid->ulNotice ) )
        {
             enRet              = pCallBack->Configed ( pstPid->stParamInfo.enPid,
                                                        usDataLen,
                                                        ( void * )pData,
                                                        &pNewData );
        }
        else
        {
            BST_OS_MEMCPY ( pstPid->stParamInfo.pvContent, pData, usDataLen );
            enRet               = BST_NO_ERROR_MSG;
        }
    }
    else
    {
        BST_RLS_LOG2( "BST_CORE_CRegedit::Save usDataLen, pstPid->stParamInfo.usLen",
                      usDataLen, pstPid->stParamInfo.usLen );
        enRet                   = BST_ERR_PAR_LEN;
    }
    return enRet;
}


BST_ERR_ENUM_UINT8  BST_CORE_CRegedit::Config(
    BST_OBJT_ADDR_T           usObjtAddr,
    BST_OFST_ADDR_T           usOfstAddr,
    BST_CORE_PID_ENUM_UINT16  enParamId,
    BST_UINT16                usDataLen,
    BST_VOID                 *pData )
{
    BST_CORE_REGNODE_STRU          *pstTaskNode;
    BST_CORE_PIDNODE_STRU          *pstPidNode;
    BST_ERR_ENUM_UINT8              enRet;
#ifdef BST_SSL_SUPPORT
    BST_UINT16                      usOutDataLen;
    BST_VOID                       *pOutData;
    BST_ERR_ENUM_UINT8              enDecryterCheck;
#endif

    enRet                               = BST_NO_ERROR_MSG;
    pstTaskNode                         = Select ( usObjtAddr, usOfstAddr );
#ifdef BST_SSL_SUPPORT
    usOutDataLen                        = 0;
    pOutData                            = BST_NULL_PTR;
    enDecryterCheck                     = BST_ERR_UNKNOW_OBJ;
#endif

    if ( BST_NULL_PTR == pstTaskNode )
    {
        return BST_ERR_INVALID_PTR;
    }
    for( pstPidNode  = ( BST_CORE_PIDNODE_STRU * )
                        lstFirst( &pstTaskNode->RegParamList ); 
       ( pstPidNode != BST_NULL_PTR );
         pstPidNode  = ( BST_CORE_PIDNODE_STRU * )
                        lstNext( ( NODE * )pstPidNode ) )
    {
        if ( pstPidNode->stParamInfo.enPid != enParamId )
        {
            continue;
        }
#ifdef   BST_SSL_SUPPORT
        enDecryterCheck                 = BST_CORE_DencryptChk
                                          ( enParamId, pData, usDataLen,
                                          &pOutData, &usOutDataLen );

        if ( ( BST_NO_ERROR_MSG == enDecryterCheck )
          && ( BST_NULL_PTR != pOutData )
          && ( 0 != usOutDataLen ) )
        {
            pData                       = pOutData;
            usDataLen                   = usOutDataLen;
        }
#endif

        enRet                           = Save
                                        ( pstTaskNode->pcApAItf,
                                          pstPidNode, usDataLen, pData );

#ifdef BST_SSL_SUPPORT
        if ( pOutData != BST_NULL_PTR )
        {
            BST_OS_FREE ( pOutData );
            pOutData                    = BST_NULL_PTR;
        }
#endif
        return enRet;
    }
    return BST_ERR_ITEM_NOT_EXISTED;
}


BST_ERR_ENUM_UINT8  BST_CORE_CRegedit::Update(
    BST_OBJT_ADDR_T           usObjtAddr,
    BST_OFST_ADDR_T           usOfstAddr,
    BST_CORE_PID_ENUM_UINT16  enParamId,
    BST_UINT16                usDataLen,
    BST_VOID                 *pData )
{
    BST_CORE_REGNODE_STRU          *pstTaskNode;
    BST_CORE_PIDNODE_STRU          *pstPidNode;
    BST_CORE_PID_LUT_STRU          *pstParamAttri;

    pstTaskNode                     = Select ( usObjtAddr, usOfstAddr );
    if ( BST_NULL_PTR == pstTaskNode )
    {
        BST_RLS_LOG( "CRegedit::Update Fail! Can't Find Task. " );
        return BST_ERR_INVALID_PTR;
    }
    for( pstPidNode  = ( BST_CORE_PIDNODE_STRU * )
                        lstFirst( &pstTaskNode->RegParamList ); 
       ( pstPidNode != BST_NULL_PTR );
         pstPidNode  = ( BST_CORE_PIDNODE_STRU * )
                        lstNext( ( NODE * )pstPidNode ) )
    {
        if ( pstPidNode->stParamInfo.enPid != enParamId )
        {
            continue;
        }
        pstParamAttri               = BST_CORE_GetPidHandle ( enParamId );
        if ( BST_NULL_PTR  == pstParamAttri )
        {
            BST_RLS_LOG( "CRegedit::Update Fail! pstParamAttri INVALID_PTR " );
            return BST_ERR_INVALID_PTR;
        }
        if ( BST_CORE_PID_VAR_LEN == pstParamAttri->enLenType )
        {
            pstPidNode->stParamInfo.usLen    = usDataLen;
            pstPidNode->stParamInfo.pvContent= pData;
        }
        return BST_NO_ERROR_MSG;
    }
    BST_RLS_LOG( "CRegedit::Update Fail!ITEM_NOT_EXISTED " );
    return BST_ERR_ITEM_NOT_EXISTED;
}



BST_ERR_ENUM_UINT8 BST_CORE_CRegedit::Regist(
    BST_CTask                  *pTask, 
    BST_VOID                   *pAPInf,
    BST_UINT32                  ulAPVersion )
{
    BST_CORE_REGNODE_STRU              *pstTaskNode;
    if ( BST_NULL_PTR == pTask )
    {
        return BST_ERR_INVALID_PTR;
    }
    pstTaskNode                         = Select ( pTask->m_usProcId, pTask->m_usTaskId );
    if ( BST_NULL_PTR == pstTaskNode )
    {
        pstTaskNode                     = (BST_CORE_REGNODE_STRU *)
                                          BST_OS_MALLOC ( BST_OS_SIZEOF ( BST_CORE_REGNODE_STRU ) );

        if ( BST_NULL_PTR == pstTaskNode )
        {
            return BST_ERR_NO_MEMORY;
        }

        pstTaskNode->pTask              = pTask;
        lstInit( &pstTaskNode->RegParamList );
        lstAdd( &m_RegistryList, (NODE *)pstTaskNode );
    }
    if( BST_DSPP_VER_A == ulAPVersion )
    {
        pstTaskNode->pcApAItf           = (BST_CORE_CAPACallBack *)pAPInf;
    }
    if( BST_DSPP_VER_C == ulAPVersion )
    {
        pstTaskNode->pcApCItf           = (BST_CORE_CAPCCallBack *)pAPInf;
    }
    return BST_NO_ERROR_MSG;
}


/*lint -e429*/
/*lint -e438*/
BST_ERR_ENUM_UINT8  BST_CORE_CRegedit::Regist(
    BST_CTask                *pTask,
    const BST_UINT32          ulNoticeFlag,
    BST_CORE_PID_ENUM_UINT16  enParamId,
    BST_CORE_PID_LEN_T        usLen,
    const void               *const pValue )
{
    BST_CORE_REGNODE_STRU              *pstTaskNode;
    BST_CORE_PIDNODE_STRU              *pstNewRegItem;
    BST_CORE_PID_LUT_STRU              *pstParam;

    if ( BST_NULL_PTR == pTask )
    {
        return BST_ERR_INVALID_PTR;
    }

    pstParam                            = BST_CORE_GetPidHandle ( enParamId );
    if ( BST_NULL_PTR == pstParam )
    {
        return BST_ERR_PAR_UNKNOW;
    }

    if ( ( BST_CORE_PID_FIX_LEN == pstParam->enLenType ) && ( usLen <  pstParam->usPlen ) )
    {
        return BST_ERR_PAR_LEN;
    }
    else
    {
        usLen                           = pstParam->usPlen;
    }
    pstNewRegItem                       = Select ( pTask->m_usProcId, pTask->m_usTaskId, enParamId );
    if ( BST_NULL_PTR != pstNewRegItem )
    {
        return BST_ERR_ITEM_EXISTED;
    }

    pstTaskNode                         = Select ( pTask->m_usProcId, pTask->m_usTaskId );
    if ( BST_NULL_PTR == pstTaskNode )
    {
        pstTaskNode                     = (BST_CORE_REGNODE_STRU *)
                                          BST_OS_MALLOC ( BST_OS_SIZEOF ( BST_CORE_REGNODE_STRU ) );

        if ( BST_NULL_PTR == pstTaskNode )
        {
            return BST_ERR_NO_MEMORY;
        }

        pstTaskNode->pTask              = pTask;
        lstInit( &pstTaskNode->RegParamList );
        lstAdd( &m_RegistryList, (NODE *)pstTaskNode );
    }
   /*
    * 先建立一个PID管理列表项
    */
    pstNewRegItem                       = ( BST_CORE_PIDNODE_STRU * )BST_OS_MALLOC
                                          ( BST_OS_SIZEOF (BST_CORE_PIDNODE_STRU) );
    if ( BST_NULL_PTR == pstNewRegItem )
    {
        BST_OS_FREE ( pstTaskNode );
        return BST_ERR_NO_MEMORY;
    }

    pstNewRegItem->stParamInfo.enPid    = enParamId;
    pstNewRegItem->ulNotice             = ulNoticeFlag;
    pstNewRegItem->stParamInfo.usLen    = usLen;
    pstNewRegItem->stParamInfo.pvContent= const_cast<BST_VOID *>(pValue);
    lstAdd( &pstTaskNode->RegParamList, (NODE *)pstNewRegItem );

    return BST_NO_ERROR_MSG;
}


/*lint -e429*/
/*lint -e438*/
BST_ERR_ENUM_UINT8  BST_CORE_CRegedit::Regist(
    BST_CTask                *pTask,
    BST_CORE_PID_ENUM_UINT16  enParamId,
    BST_CORE_PID_LEN_T        usLen,
    const void               *const pValue )
{
    BST_UINT32                          ulRtnVal;
    ulRtnVal                            = Regist
                                        ( pTask, BST_TRUE,
                                          enParamId, usLen, pValue );
    return ulRtnVal;
}
/*lint +e438*/
/*lint +e429*/

BST_ERR_ENUM_UINT8  BST_CORE_CRegedit::unRegist(
    const BST_CTask            *pTask,
    BST_CORE_PID_ENUM_UINT16    enParamId )
{
    BST_CORE_REGNODE_STRU              *pstTaskNode;
    BST_CORE_PIDNODE_STRU              *pstPidNode;

    if ( BST_NULL_PTR == pTask )
    {
        return BST_ERR_INVALID_PTR;
    }

   /*
    *先查找Task注册信息，如果无此Task则失败
    */
    pstTaskNode                         = Select ( pTask->m_usProcId, pTask->m_usTaskId );

    if ( BST_NULL_PTR == pstTaskNode )
    {
        return BST_ERR_INVALID_PTR;
    }

   /*
    * 遍历PID列表，找到对应的条目并删除其中信息
    */
    for( pstPidNode  = ( BST_CORE_PIDNODE_STRU * )
                        lstFirst( &pstTaskNode->RegParamList ); 
       ( pstPidNode != BST_NULL_PTR );
         pstPidNode  = ( BST_CORE_PIDNODE_STRU * )
                        lstNext( ( NODE * )pstPidNode ) )
    {
        if ( pstPidNode->stParamInfo.enPid != enParamId )
        {
            continue;
        }
        lstDelete( &pstTaskNode->RegParamList, ( NODE * )pstPidNode );
        BST_OS_FREE ( pstPidNode );
       /*
        * 如果该任务PID列表已空，那么从注册表总表中删除相应条目
        */
        if ( 0 == lstCount( &pstTaskNode->RegParamList ) )
        {
            lstDelete( &m_RegistryList, ( NODE * )pstTaskNode );
            BST_OS_FREE ( pstTaskNode );
        }
        return BST_NO_ERROR_MSG;
    }
    return BST_ERR_ITEM_NOT_EXISTED;
}

/*lint -e438*/
BST_ERR_ENUM_UINT8  BST_CORE_CRegedit::unRegist ( const BST_CTask *pTask )
{
    BST_CORE_REGNODE_STRU              *pstTaskNode;
    BST_CORE_PIDNODE_STRU              *pstPidNode;
    BST_CORE_PIDNODE_STRU              *pstPidNextNode;

    if ( BST_NULL_PTR == pTask )
    {
        return BST_ERR_INVALID_PTR;
    }

   /*
    *先查找Task注册信息，如果无此Task则失败
    */
    pstTaskNode                 = Select
                                         ( pTask->m_usProcId, pTask->m_usTaskId );
    if ( BST_NULL_PTR == pstTaskNode )
    {
        return BST_ERR_INVALID_PTR;
    }
   /*
    * 必须要辅助表指针pstPidNextNode，因为需要遍历并删除其中所有条目，当前
    * 条目删除后则无法取出NEXT项
    */
    for( pstPidNode = ( BST_CORE_PIDNODE_STRU * )lstFirst( &pstTaskNode->RegParamList );
         BST_NULL_PTR != pstPidNode;
         pstPidNode = pstPidNextNode )
    {
        pstPidNextNode          = ( BST_CORE_PIDNODE_STRU * )
                                  lstNext( ( NODE * )pstPidNode );
        lstDelete( &pstTaskNode->RegParamList,( NODE * ) pstPidNode );
        BST_OS_FREE ( pstPidNode );
    }
    lstDelete( &m_RegistryList, ( NODE * )pstTaskNode );
    BST_OS_FREE ( pstTaskNode );
    return BST_NO_ERROR_MSG;
}
/*lint +e438*/

BST_ERR_ENUM_UINT8 BST_CORE_CRegedit::ChnlCtrl(
    BST_OBJT_ADDR_T            usObjtAddr,
    BST_OFST_ADDR_T            usOfstAddr,
    BST_SRV_CHNL_HEAD_STRU    *pstChnHead )
{
    BST_CORE_REGNODE_STRU          *pstTaskNode;

    pstTaskNode                     = Select ( usObjtAddr, usOfstAddr );
    if ( BST_NULL_PTR == pstTaskNode )
    {
        BST_RLS_LOG( "BST_CORE_CRegedit::ChnlCtrl pstTaskNode=NULL" );
        BST_SRV_FreeIpBlock( pstChnHead );
        return BST_ERR_INVALID_PTR;
    }
    if ( BST_NULL_PTR == pstTaskNode->pcApCItf )
    {
        BST_RLS_LOG( "BST_CORE_CRegedit::ChnlCtrl pstTaskNode.pcApCItf=NULL" );
        BST_SRV_FreeIpBlock( pstChnHead );
        return BST_ERR_PAR_UNKNOW;
    }

    switch( pstChnHead->usCmdId )
    {
        case BST_DSPP_FLG_CMD_CLEAR:
            pstTaskNode->pcApCItf->ChnlCtrlClear();
            BST_SRV_FreeIpBlock( pstChnHead );
        break;

        case BST_DSPP_FLG_CMD_CLOSE:
            pstTaskNode->pcApCItf->ChnlCtrlClose();
            BST_SRV_FreeIpBlock( pstChnHead );
        break;

        case BST_DSPP_FLG_CMD_SEND:
            pstTaskNode->pcApCItf->ChnlCtrlSend( pstChnHead );
        break;

        default:
            BST_SRV_FreeIpBlock( pstChnHead );
        break;
    }

    return BST_NO_ERROR_MSG;
}


BST_CORE_PIDNODE_STRU* BST_CORE_CRegedit::Select(
    BST_OBJT_ADDR_T            usObjtAddr,
    BST_OFST_ADDR_T            usOfstAddr,
    BST_CORE_PID_ENUM_UINT16   enParamId )
{
    BST_CORE_REGNODE_STRU      *pstTaskNode;
    BST_CORE_PIDNODE_STRU      *pstPidNode;

   /*
    *先查找Task注册信息，如果无此Task则失败
    */
    pstTaskNode                 = Select ( usObjtAddr, usOfstAddr );
    if ( BST_NULL_PTR == pstTaskNode )
    {
        return BST_NULL_PTR;
    }
   /*
    *在该任务注册的PID列表中找到与之匹配的PID条目
    */
    for( pstPidNode  = ( BST_CORE_PIDNODE_STRU * )
                        lstFirst( &pstTaskNode->RegParamList ); 
       ( pstPidNode != BST_NULL_PTR );
         pstPidNode  = ( BST_CORE_PIDNODE_STRU * )
                        lstNext( ( NODE * )pstPidNode ) )
    {
        if ( pstPidNode->stParamInfo.enPid == enParamId )
        {
            return pstPidNode;
        }
    }
    return BST_NULL_PTR;
}

BST_CORE_REGNODE_STRU* BST_CORE_CRegedit::Select(
    BST_OBJT_ADDR_T   usObjtAddr,
    BST_OFST_ADDR_T   usOfstAddr )
{
    BST_CORE_REGNODE_STRU          *pstTaskNode;

   /*
    *遍历注册表，寻找objtid,ofstid与之匹配的任务
    */
    for( pstTaskNode  = ( BST_CORE_REGNODE_STRU * )lstFirst( &m_RegistryList ); 
       ( pstTaskNode != BST_NULL_PTR );
         pstTaskNode  = ( BST_CORE_REGNODE_STRU * )
                         lstNext( ( NODE * )pstTaskNode ) )

    {
        if ( BST_NULL_PTR == pstTaskNode->pTask )
        {
            continue;
        }
        if ( ( pstTaskNode->pTask->m_usProcId == usObjtAddr )
          && ( pstTaskNode->pTask->m_usTaskId == usOfstAddr ) )
        {
            return pstTaskNode;
        }
    }
    return BST_NULL_PTR;
}

BST_BOOL BST_CORE_CRegedit::InputCheck(
    BST_CORE_PID_ENUM_UINT16    enParamId,
    BST_UINT16                  usDataLen,
    const BST_VOID             *const pData ) const
{
    BST_CORE_PID_LUT_STRU  *pstParamAttri;
    pstParamAttri           = BST_CORE_GetPidHandle ( enParamId );

   /*
    *入口检查
    */
    if ( ( BST_NULL_PTR == pstParamAttri ) || ( BST_NULL_PTR == pData ) )
    {
        return BST_FALSE;
    }
   /*
    *定长型数据，如果输入长度与设置不符合或为0，均视为无效
    */
    if ( ( ( BST_CORE_PID_FIX_LEN == pstParamAttri->enLenType )
        && ( usDataLen != pstParamAttri->usPlen ) )
        || ( 0 == usDataLen ) )
    {
        BST_RLS_LOG2( "BST_CORE_CRegedit::InputCheck usDataLen, pstParamAttri->usPlen",
                      usDataLen, pstParamAttri->usPlen );
        return BST_FALSE;
    }
    return BST_TRUE;
}

BST_CORE_CRegedit::BST_CORE_CRegedit ( BST_VOID )
{
   /*
    *初始化注册表
    */
    lstInit( &m_RegistryList );
}

