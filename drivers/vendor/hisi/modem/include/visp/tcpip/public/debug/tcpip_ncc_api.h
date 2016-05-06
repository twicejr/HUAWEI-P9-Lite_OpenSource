/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_ncc_api.h
*
*  Project Code: VR8C01
*   Module Name: PUBLIC
*  Date Created: 2009-4-11
*        Author: w60786
*   Description: NCC所有的类型定义,枚举定义,宏定义
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2009-4-11    w60786           Creat the first version.
*
*******************************************************************************/

#ifndef _TCPIP_NCC_API_H_
#define _TCPIP_NCC_API_H_

#ifdef  __cplusplus
extern "C"{
#endif

/*******************************宏定义*****************************************/



/*******************************枚举定义***************************************/
/* NCC 错误码定义 */
typedef enum enTCPIP_NCC_ERR_CODE
{
    NCC_OK = VOS_OK,                /* 0  OK                                */
    NCC_ERR,                        /* 1  ERR                               */
    NCC_ERR_EXECID_INVALID,         /* 2  NCC用户执行ID不合法               */
    NCC_ERR_EXECID_NOTEXIST,        /* 3  NCC诊断不存在                     */
    NCC_ERR_EXECID_INUSE,           /* 4  NCC用户执行ID已使用               */
    NCC_ERR_TYPE_INVALID,           /* 5  NCC诊断类型不合法                 */
    NCC_ERR_TASKPRI_INVALID,        /* 6  NCC任务优先级不合法               */
    NCC_ERR_POINT_NULL,             /* 7  指针为NULL                        */
    NCC_ERR_TIME_INVALID,           /* 8  NCC诊断时间不合法                 */
    NCC_ERR_IFNET_NULL,             /* 9  接口不存在                        */
    NCC_ERR_IFTYPE_INVALID,         /* 10 接口类型不合法                    */
    NCC_ERR_ALREADY_START,          /* 11 该NCC诊断已启动                   */
    NCC_ERR_CREATE_QUE,             /* 12 创建NCC信息消息队列失败           */
    NCC_ERR_CREATE_TIMER_QUE,       /* 13 创建NCC定时器消息队列失败         */
    NCC_ERR_CREATE_TIMER,           /* 14 创建NCC定时器失败                 */
    NCC_ERR_CREATE_TASK,            /* 15 创建NCC任务失败                   */
    NCC_ERR_IF_COMINIT,             /* 16 获取IFNET组件失败                 */
    NCC_ERR_PPP_COMINIT,            /* 17 获取PPP组件失败                   */
    NCC_ERR_PPP_MAX_NUM,            /* 18 PPP类型已有的诊断数目已达到最大值 */
    NCC_ERR_TIMEBASE_INVALID,       /* 19 循环定时器时间基数值不合法        */
    NCC_ERR_VIRTUAL_IFTYPE_INVALID, /* 20 接口类型是三维虚接口不合法        */
    
    NCC_ERR_MAXCODE,                /* NCC错误码最大值,以后添加错误码请按顺序添加在此之前 */
}TCPIP_NCC_ERR_CODE_E;

/* NCC检查的协商类问题种类 */
typedef enum enTCPIP_NCC_TYPE
{
    NCC_TYPE_PPP = 0,               /* 0  PPP协商类型NCC诊断                */
    NCC_TYPE_3AH,                   /* 1  3AH协商类型NCC诊断                */
    NCC_TYPE_TRUNK,                 /* 2  TRUNK协商类型NCC诊断              */
    NCC_TYPE_TCP,                   /* 3  TCP协商类型NCC诊断                */
    NCC_TYPE_BFD,                   /* 4  BFD协商类型NCC诊断                */
    NCC_TYPE_DHCP,                  /* 5  DHCP协商类型NCC诊断               */
    NCC_TYPE_END,                   /* 最大NCC协商类型值,以后新增协商类型诊断时请按顺序添加在此之前 */
}TCPIP_NCC_TYPE_E;

/* NCC诊断输出信息类型ID(诊断结果类型ID) */
typedef enum enTCPIP_NCC_DIAGNOSEINFO_TYPE
{
    NCC_INFO_RESULT_INFO = 0,           /* 0 诊断过程中的参考信息输出ID */

    NCC_INFO_TYPE_NCC_START,            /* 1 诊断开始 */
    NCC_INFO_TYPE_NCC_END,              /* 2 结束一个NCC诊断:该NCC诊断正常完成结束或者用户停止了诊断 */
    NCC_INFO_TYPE_NCC_END_ALL,          /* 3 结束所有NCC诊断标志:用户停止了当前的所有NCC诊断 */

    /* 以下是各NCC诊断类型诊断结束的原因,无论是否有以下诊断结束原因,最后都会有以上的诊断结束标志输出 */
    NCC_INFO_RESULT_PPP_OK = 100,               /* PPP诊断结果ID */
    
    NCC_INFO_RESULT_PPP_NO_INTERFACE,           /* 101 PPP类型诊断接口不存在 */
    NCC_INFO_RESULT_PPP_NO_PPPCTL,              /* 102 没有接口对应的PPP控制块 */
    NCC_INFO_RESULT_PPP_NO_CONFIG,              /* 103 没有接口对应的PPP配置控制块 */
    NCC_INFO_RESULT_PPP_NO_USEDCONFIG,          /* 104 没有接口对应的PPP生效配置控制块 */

    NCC_INFO_RESULT_PPP_SHUTDOWN,               /* 105 PPP类型诊断接口被shutdown */

    NCC_INFO_RESULT_PPP_PHY_DOWN,               /* 106 PPP类型诊断接口物理状态DOWN */
    NCC_INFO_RESULT_PPP_MP_PHY_DOWN,            /* 107 PPP类型诊断MP接口物理状态DOWN */    
    NCC_INFO_RESULT_PPP_PHY_UPDOWN_REPEAT,      /* 108 PPP类型诊断接口物理状态反复UP/DOWN */
    NCC_INFO_RESULT_PPP_MP_PHY_UPDOWN_REPEAT,   /* 109 PPP类型诊断MP接口物理状态反复UP/DOWN */

    NCC_INFO_RESULT_PPP_LINE_UP,                /* 110 PPP类型诊断接口协议状态UP,接口状态正常 */

    NCC_INFO_RESULT_PPP_LCP_UP,                 /* 111 PPP类型诊断LCP UP,MP子接口状态正常 */
    NCC_INFO_RESULT_PPP_LCP_DOWN,               /* 112 PPP类型诊断LCP DOWN */
    NCC_INFO_RESULT_PPP_LCP_UPDOWN_REPEAT,      /* 113 PPP类型诊断LCP 反复UP/DOWN */

    NCC_INFO_RESULT_PPP_IPCP_UP,                /* 114 PPP类型诊断IPCP UP,接口状态正常 */
    NCC_INFO_RESULT_PPP_IPCP_DOWN,              /* 115 PPP类型诊断IPCP DOWN */
    NCC_INFO_RESULT_PPP_IPCP_UPDOWN_REPEAT,     /* 116 PPP类型诊断IPCP 反复UP/DOWN */

    NCC_INFO_RESULT_PPP_LOCAL_NOBINDTOMP,       /* 117 本端未加入MP,对端已加入MP */
    NCC_INFO_RESULT_PPP_LOCAL_BINDTOMP_NORESET, /* 118 本端已加入MP,但还未生效,对端已加入MP */
    NCC_INFO_RESULT_PPP_REMOTE_NOBINDTOMP,      /* 119 对端未加入MP,本端已加入MP */
    NCC_INFO_RESULT_PPP_LOCAL_NOBINDTOMP_NORESET,/* 120 对端未加入MP,本端已移出MP,但还未生效 */

    NCC_INFO_RESULT_PPP_DISCR_NEG_FAIL,         /* 121 本端希望协商终端描述符,但是终端描述符协商失败,
                                                       协商结果不是两端都协商终端描述符,导致本端LCP协商不过 */
    NCC_INFO_RESULT_PPP_DISCR_CONSISTENT_DADDR, /* 122 该子接口协商到的对端的终端描述符与其MP父接口的对
                                                       端的终端描述符值不相同 */

    NCC_INFO_RESULT_PPP_MHF_PREFIX_CLASS_INVALID, /* 123 对端设置了协商前缀省略,但是本端设置的前缀省略最大等级大于对
                                                         端的MHF最大等级导致协商不过.(原则:MHF选项所协商的class等级数
                                                         必须包容前缀省略所支持的最大等级) */

    NCC_INFO_RESULT_PPP_LCPNEG_NOPAP,                   /* 124 本端使能了PAP认证,作为认证方,但是没有协商通过,
                                                               可能对端没有配置用户名和pwd */
    NCC_INFO_RESULT_PPP_LCP_PAP_AUTH_FAIL_MALLOC_PAP,   /* 125 PAP认证过程中,开始认证时分配PAP控制块失败 */
    NCC_INFO_RESULT_PPP_LCP_PAP_AUTH_SERVER_FAIL,       /* 126 PAP认证过程中,作为认证方Server认证失败 */
    NCC_INFO_RESULT_PPP_LCP_PAP_AUTH_CLIENT_FAIL,       /* 127 PAP认证过程中,作为被认证方Client认证失败 */

    NCC_INFO_RESULT_PPP_PPP_LCPNEG_NOCHAP,              /* 128 本端使能了CHAP认证,作为认证方,但是没有协商通过,
                                                               可能对端没有配置主机名和pwd */
    NCC_INFO_RESULT_PPP_LCP_CHAP_AUTH_FAIL_MALLOC_CHAP, /* 129 CHAP认证过程中,开始认证时分配CHAP控制块失败 */
    NCC_INFO_RESULT_PPP_LCP_CHAP_AUTH_SERVER_FAIL,      /* 130 CHAP认证过程中,作为认证方Server认证失败 */
    NCC_INFO_RESULT_PPP_LCP_CHAP_AUTH_CLIENT_FAIL,      /* 131 CHAP认证过程中,作为被认证方Client认证失败 */
    

    NCC_INFO_RESULT_PPP_MP_NOUPTOLOWLIMIT,          /* 132 MP绑定的子链路数未达到用户指定的最小规格导致未进行NCP的协商*/
    NCC_INFO_RESULT_PPP_NOCONFIGIP,                 /* 133 接口上未配置地址导致IPCP协商不过 */
    NCC_INFO_RESULT_PPP_IPCPNEG_GOTIP_ZERO,         /* 134 本端配置为协商获取地址,但是协商获得的地址为0 */
    NCC_INFO_RESULT_PPP_IPCPNEG_GOTIP_INVALID,      /* 135 本端配置为协商获取地址,但是协商获得的地址非法(无效IP) */
    NCC_INFO_RESULT_PPP_IPCPNEG_HISIP_INVALID,      /* 136 对端配置为协商获取地址,但是对端协商获得的地址非法(无效IP)*/
    NCC_INFO_RESULT_PPP_IPCPNEG_IPCONFLICT_LOCALSAME,/* 137 本端配置为协商获取地址,但是协商获得的地址与本端其他IP相同
                                                            (冲突) */
    NCC_INFO_RESULT_PPP_IPCPNEG_IPCONFLICT_PEERSAME, /* 138 本端配置为协商获取地址,但是协商获得的两端IP相同(冲突),
                                                            或者两端都配置IP但是IP冲突*/
    NCC_INFO_RESULT_PPP_IPCPNEG_GOTIPMODE_CONFLIT,  /* 139 本端已有自己的IP,但对端仍然给本端分配IP导致冲突 */
    NCC_INFO_RESULT_PPP_IPCPNEG_HISIPMODE_CONFLIT,  /* 140 对端已有自己的IP,但本端仍然给对端分配IP导致冲突 */

    NCC_INFO_RESULT_PPP_IPCPNEG_IPHCINIT_FAIL,      /* 141 IPHC模块初始化失败导致IPCP协商失败 */  

    NCC_INFO_RESULT_PPP_RCV_NO_NEGPKT,   /* 142 本端有发送数据,但是没有收到对端的任何数据,可能为底层不通,
                                                或者对端配置为不协商LCP/IPCP */
    NCC_INFO_RESULT_PPP_RCV_WRONG_PKTID, /* 143 收到ID不匹配的报文,可能的原因:底层上送报文不及时,
                                                底层收发时传给的PPP链路错误,底层收到报文时乱序 */

    NCC_INFO_RESULT_PPP_NOT_CONSISTENT_MP, /*144, Inconsistencies in the Group and Member link parameters*/
    NCC_INFO_RESULT_PPP_RECEIVE_TR,                 /*145, Recived termination request caused the link to go down */
    NCC_INFO_RESULT_PPP_ECHO_TIMEOUT,           /*146, Echo packet timed out */
    NCC_INFO_RESULT_PPP_RECEIVE_CR,                 /*147, Recieved the Configuration request packet when the link is in open state and which resulted in link to go dwon.*/
    NCC_INFO_RESULT_PPP_IPCP_RECEIVE_TR,    /* 148, IPCP Recived termination request caused the link to go down */
    NCC_INFO_RESULT_PPP_IPCP_RECEIVE_CR,    /* 149, IPCP Recieved the Configuration request packet when the link is in open state and which resulted in link to go dwon.*/
  
    NCC_INFO_RESULT_PPP_NO_REASON = 299, /* 299 没有诊断出具体原因,请给据本端和对端的参考信息进行定位 */
    
    NCC_INFO_RESULT_3AH_OK = 300,             /* PPP诊断结果ID */
    
    NCC_INFO_RESULT_TRUNK_OK = 500,           /* PPP诊断结果ID */
    
    NCC_INFO_RESULT_TCP_OK = 700,             /* PPP诊断结果ID */
    
    NCC_INFO_RESULT_BFD_OK = 900,             /* PPP诊断结果ID */
    
    NCC_INFO_RESULT_DHCP_OK = 1100,           /* PPP诊断结果ID */
    
    NCC_INFO_RESULT_END = 1300,               /* 最大NCC诊断结果ID,以后新增NCC结束类型ID时请按类型和顺序添加在此之前 */
}TCPIP_NCC_DIAGNOSEINFO_TYPE_E;

/*******************************结构类型定义***********************************/



/*******************************全局变量声明***********************************/

/*******************************************************************************
*    Func Name: TCPIP_NCC
* Date Created: 2009-04-13
*       Author: wangmingxia/wuhailan
*  Description: NCC诊断功能启动设置
*        Input: ULONG ulExecID:用户ID,不能为0,并且要求所有NCC诊断唯一
*               ULONG ulTaskPri:任务优先级,传入0表示使用默认值(同SOCK任务优先级),取值范围[1,255]
*               ULONG ulDetectTime:协商检测时间,传入0表示使用默认值30s,取值范围[10s,600s]
*               ULONG ulType:设置的NCC诊断类型,参见TCPIP_NCC_TYPE_E枚举定义
*               VOID * pstPara:各设置类型对应的参数,当前PPP协商类型对应的参数值为ULONG的接口索引
*       Output: 
*       Return: 成功VOS_OK,其他返回错误码
*      Caution: 实际上NCC任务的优先级使用的是第一次启动NCC时传入的优先级,之后传入的优先级值不使用
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-13   wangmingxia/wuhailan    Create
*
*******************************************************************************/
extern ULONG TCPIP_NCC(ULONG ulExecID, ULONG ulTaskPri, ULONG ulDetectTime, ULONG ulType, VOID * pstPara);

/*******************************************************************************
*    Func Name: TCPIP_StopNCC
* Date Created: 2009-04-13
*       Author: wangmingxia/wuhailan
*  Description: 根据用户ID关闭诊断检查,如果ulExecID为0,则表示关闭所有NCC诊断检查
*        Input: ULONG ulExecID:用户ID
*       Output: 
*       Return: 成功VOS_OK,其他返回错误码
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-13   wangmingxia/wuhailan    Create
*
*******************************************************************************/
extern ULONG TCPIP_StopNCC(ULONG ulExecID);

/*******************************************************************************
*    Func Name: TCPIP_ShowNCCCfgInfo
* Date Created: 2009-04-20
*       Author: wangmingxia/wuhailan
*  Description: 根据用户ID显示NCC配置信息,如果ID值为0则表示显示所有当前诊断的信息
*        Input: ULONG ulExecID:用户ID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-20   wangmingxia/wuhailan    Create
*
*******************************************************************************/
extern VOID TCPIP_ShowNCCCfgInfo(ULONG ulExecID);


#ifdef  __cplusplus 
}
#endif

#endif /* _TCPIP_NCC_API_H_ */


