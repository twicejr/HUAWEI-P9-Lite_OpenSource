/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ospf6_api.h
*
*  Project Code: node
*   Module Name:   
*  Date Created: 2009-07-13
*        Author: wangbin (62223)
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-07-13   wangbin (62223)         Create
*
*******************************************************************************/
#ifndef _OSPF6_API_H_
#define _OSPF6_API_H_
    
#ifdef __cplusplus
        extern "C"{
#endif /* __cplusplus */

/*MACRO<OSPF6_Define>*/
#define OSPF6_MAX_PROCESSES                     32         /*最大进程数*/
#define OSPF6_MAX_AREA                          50         /*最大区域数*/

#define OSPF6_MAX_IF_NAME_LENGTH                47         /*接口名最大长度*/
#define OSPF6_MAX_VRFNAME_LENGTH                31         /*VRF名最大长度*/
#define OSPF6_ENCRYPT_DATA_LENGTH               255        /*最大enc 数据长度*/

#define OSPF6_DEFAULT_CALC_DELAY                5000       /*SPF定时器延时时间缺省值*/
#define OSPF6_DEFAULT_CALC_PAUSE                10000      /*SPF定时器中断时间缺省值*/

#define OSPF6_MIN_EQCOST_PATH                   1          /*最大平衡路由个数的最小值*/
#define OSPF6_MAX_EQCOST_PATH                   32         /*最大平衡路由个数的最大值*/
#define OSPF6_DEFAULT_EQCOST_PATH               5          /*最大平衡路由缺省值*/

#define OSPF6_MAX_SPF_TIME                      0x7fffffff /*SPF定时器最大规格限制*/

#define OSPF6_MAX_INTF_PRIORITY                 255        /*Router接口优先级最大值*/
#define OSPF6_DEFAULT_INTF_PRIORITY             1          /*Router接口优先级默认值*/

#define OSPF6_ROUTER_LSA                        (0x2001)   /*路由聚合时，LSDB类型为ROUTE_LSA*/
#define OSPF6_NETWORK_LSA                       (0x2002)   /*路由聚合时，LSDB类型为NETWORK_LSA*/
#define OSPF6_INTER_AREA_PRFX_LSA               (0x2003)   /*路由聚合时，LSDB类型为INTER_AREA_PRFX_LSA */
#define OSPF6_INTER_AREA_RTR_LSA                (0x2004)   /*路由聚合时，LSDB类型为INTER_AREA_RTR_LSA*/
#define OSPF6_AS_EXTERNAL_LSA                   (0x4005)   /*路由聚合时，LSDB类型为AS_EXTERNAL_LSA*/
#define OSPF6_NSSA_EXT_LSA                      (0x2007)   /*路由聚合时，LSDB类型为NSSA_EXT_LSA*/
#define OSPF6_LINK_LSA                          (0x0008)   /*路由聚合时，LSDB类型为LINK_LSA*/
#define OSPF6_INTRA_AREA_PRFX_LSA               (0x2009)   /*路由聚合时，LSDB类型为INTRA_AREA_PRFX_LSA*/
#define OSPF6_AGG_ADVRTISE                      1          /*路由聚合时，effect类型为通告*/
#define OSPF6_AGG_DO_NOT_ADVRTISE               0          /*路由聚合时，effect类型为不通告*/

#define OSPF6_SUMM_NO_AREA_SUMMARY              0          /*配置Stub区域时，summary类型为NO_AREA_SUMMARY*/
#define OSPF6_SUMM_SEND_AREA_SUMMARY            1          /*配置Stub区域时，summary类型为SEND_AREA_SUMMARY*/

#define OSPF6_REDI_INTRA_AREA                   0x000D0000 /*配置路由引入策略时，Metric Type类型为INTRA_AREA*/
#define OSPF6_REDI_INTER_AREA                   0x000D0001 /*配置路由引入策略时，Metric Type类型为INTER_AREA */
#define OSPF6_REDI_TYPE1_EXT                    0x000D0002 /*配置路由引入策略时，Metric Type类型为TYPE1_EXT*/
#define OSPF6_REDI_TYPE2_EXT                    0x000D0003 /*配置路由引入策略时，Metric Type类型为TYPE2_EXT*/


#define OSPF6_PREFERENCE_TYPE_INT               0x01       /*配置路径代价类型为:设置在区域内路径上的代价*/
#define OSPF6_PREFERENCE_TYPE_EXT               0x02       /*配置路径代价类型为:设置在外部路径上的代价*/

#define OSPF6_LSA_MAX_RTR_LINK_D                50         /*路由器LSA路由器描述数量最大值*/
#define OSPF6_LSA_MAX_NET_NBR                   50         /*网络LSA关联网络描述数量最大值*/ 
#define OSPF6_LSA_MAX_PRFX_D                    50         /*链路LSA链路前缀描述数量最大值*/ 

#define OSPF6_DIST_OSPF_TO_RM                   1           /*路由引入方向OSPF->RTM*/
#define OSPF6_DIST_RM_TO_OSPF                   2           /*路由引入方向RTM->OSPF*/

#define OSPF6_INPUT                             1           /*注册，去注册OSPF6钩子函数的方向:接收*/
#define OSPF6_OUTPUT                            2           /*注册，去注册OSPF6钩子函数的方向:发送*/

#define OSPF6_NOFLAG_ADD                        0           /*配置类型为添加*/
#define OSPF6_NOFLAG_DEL                        1           /*配置类型为删除*/

#define OSPF6_NETWORK_BROADCAST                 1           /*接口属性--广播网络类型*/
#define OSPF6_NETWORK_NBMA                      2           /*接口属性--NBMA网络类型*/
#define OSPF6_NETWORK_POINT_TO_POINT            3           /*接口属性--P2P网络类型*/
#define OSPF6_NETWORK_POINT_T_MLTPNT            5           /*接口属性--P2MP网络类型*/

#define OSPF6_MIN_INTF_COST                     1           /*接口属性--最小COST值*/
#define OSPF6_MAX_INTF_COST                     65535       /*接口属性--最大COST值*/

#define OSPF6_MIN_INTF_RXMT_ITVL                1           /*接口属性--重传间隔最小值*/
#define OSPF6_MAX_INTF_RXMT_ITVL                1800        /*接口属性--重传间隔最大值*/
#define OSPF6_DEF_INTF_RXMT_ITVL                5           /*接口属性--重传间隔默认值*/

#define OSPF6_MIN_INTF_TRANS_DELAY              1           /*接口属性--发送延时时间最小值*/
#define OSPF6_MAX_INTF_TRANS_DELAY              1800        /*接口属性--发送延时时间最大值*/
#define OSPF6_DEF_INTF_TRANS_DELAY              1           /*接口属性--发送延时时间默认值*/

#define OSPF6_MIN_INTF_HELLO_ITVL               1           /*接口属性--Hello报文间隔时间最小值*/
#define OSPF6_MAX_INTF_HELLO_ITVL               65535       /*接口属性--Hello报文间隔时间最大值*/
#define OSPF6_DEF_INTF_HELLO_ITVL_0             10          /*接口属性--除NBMA网络外，Hello报文间隔时间默认值*/
#define OSPF6_DEF_INTF_HELLO_ITVL_1             30          /*接口属性--NBMA网络上，Hello报文间隔时间默认值*/

#define OSPF6_MIN_INTF_DEAD_ITVL                1           /*接口属性--Dead Interval最小值*/
#define OSPF6_MAX_INTF_DEAD_ITVL                65535       /*接口属性--Dead Interval最大值*/
#define OSPF6_DEF_INTF_DEAD_ITVL_0              40          /*接口属性--除NBMA网络外，Dead Interval默认值*/
#define OSPF6_DEF_INTF_DEAD_ITVL_1              120         /*接口属性--NBMA网络上，Dead Interval默认值*/

#define OSPF6_MIN_INTF_FAST_HELLO_MULTIPLIER   3            /*接口属性--Fast Hello发送报文个数最小值*/
#define OSPF6_MAX_INTF_FAST_HELLO_MULTIPLIER   20           /*接口属性--Fast Hello发送报文个数最大值*/
#define OSPF6_DEF_INTF_FAST_HELLO_MULTIPLIER   5            /*接口属性--Fast Hello发送报文个数默认值*/

#define OSPF6_DEF_INTF_POLL_ITVL                120         /*接口属性--NBMA网络上，Poll Interval默认值*/

#define DF_OSPF6_TO_RM                          1           /*路由引入方向-OSPF6向RM引*/
#define DF_RM_TO_OSPF6                          2           /*路由引入方向-RM向OSPF6引*/
 
#define OSPF6_MAX_NBR_PRIORITY                  255         /*静态邻居最大优先级*/
#define OSPF6_DEF_NBR_PRIORITY                  1           /*静态邻居默认优先级*/
 
#define OSPF6_ALL_INST_FILTER                   0xFFFFFFFF  /*通配查询实例号*/ 
#define OSPF6_MAX_INSTANCE_ID                   0xFF        /*实例号最大值*/ 
#define OSPF6_MIN_INSTANCE_ID                   0           /*实例号最小值*/

#define OSPF6_INTF_ATTR_NET_TYPE_BITS           0x0001      /*OSPFv3接口属性配置比特位:网络类型*/
#define OSPF6_INTF_ATTR_COST_BITS               0x0002      /*OSPFv3接口属性配置比特位:cost值*/
#define OSPF6_INTF_ATTR_PRIORITY_BITS           0x0004      /*OSPFv3接口属性配置比特位:优先级*/
#define OSPF6_INTF_ATTR_MTU_IGNORE_BITS         0x0008      /*OSPFv3接口属性配置比特位:MTU忽略*/
#define OSPF6_INTF_ATTR_RXMT_ITVL_BITS          0x0010      /*OSPFv3接口属性配置比特位:重传间隔*/
#define OSPF6_INTF_ATTR_TRANS_DELAY_BITS        0x0020      /*OSPFv3接口属性配置比特位:发送延时时间*/
#define OSPF6_INTF_ATTR_HELLO_ITVL_BITS         0x0040      /*OSPFv3接口属性配置比特位:Hello报文发送间隔*/
#define OSPF6_INTF_ATTR_DEAD_ITVL_BITS          0x0080      /*OSPFv3接口属性配置比特位:老化时间*/
#define OSPF6_INTF_ATTR_POLL_ITVL_BITS          0x0100      /*OSPFv3接口属性配置比特位:Poll间隔*/
#define OSPF6_INTF_ATTR_STATIC_NBR_BITS         0x0200      /* OSPFv3静态邻居属性/引用Bits区分 */
#define OSPF6_INTF_ATTR_GR_HELPER_BITS          0x0400      /*OSPFv3接口属性配置比特位：GR Helper参数*/
#define OSPF6_INTF_ATTR_ALL_BITS                0x05FF

#define OSPF6_SET_INTF_ATTR_BIT(bit, flag)    ((bit) |= (flag))
#define OSPF6_CLR_INTF_ATTR_BIT(bit, flag)    ((bit) &= (~flag))

#define OSPF6_AREA_NSSAOPT_DEFAULT              0x01        /* OSPFv3区域属性选项:NSSA区域产生缺省路由(该选项暂不用) */
#define OSPF6_AREA_NSSAOPT_NOIMPORT             0x02        /* OSPFv3区域属性选项:禁止NSSA边界路由器将7类LSA转换成5类LSA */
#define OSPF6_AREA_NSSAOPT_NOSUMMARY            0x04        /* OSPFv3区域属性选项:禁止ABR路由器发送Summary LSA到NSSA/STUB区域 */

#define OSPF6_MAX_AREA_COST_VALUE               0xFFFFFF    /*OSPFv3区域属性--cost最大值*/

#define OSPF6_MIN_AREA_RFSH_ITVL                1           /*OSPFv3区域属性--洪泛间隔最小值*/
#define OSPF6_MAX_AREA_RFSH_ITVL                3599        /*OSPFv3区域属性--洪泛间隔最大值*/

/*默认路由代价同OSPFV2保持一致*/
#define OSPF6_DEF_PREFERENCE_INT                10          /*OSPFv3协议属性--区域内路径上的默认代价*/
#define OSPF6_DEF_PREFERENCE_EXT                150         /*OSPFv3协议属性--外部路径上的默认代价*/

#define OSPF6_IP_STR_LEN 32
#define OSPF6_INPUT  1                                     /*OSPFv3报文接收*/ 
#define OSPF6_OUTPUT 2                                     /*OSPFv3报文发送*/

#define OSPF6_PORCESS_ID_MIN    1
#define OSPF6_ROUTE_ID_MIN    1

#define OSPF6_CFG_RESET_SET_DOWN     0x01
#define OSPF6_CFG_RESET_SET_UP       0x02
#define OSPF6_CFG_RESET_SET_DOWNUP   (OSPF6_CFG_RESET_SET_DOWN | OSPF6_CFG_RESET_SET_UP)

#define OSPFV3_TRUE     1
#define OSPFV3_FALSE    0

/*Added by guojianjun178934, OSPFV3添加接口和邻居状态机状态和事件定义, 2014/7/3   问题单号:DTS2014070303605 */
/*邻居状态定义*/
#define OSPF6_NBR_STATE_DOWN                ((LONG)1)
#define OSPF6_NBR_STATE_ATTEMPT             ((LONG)2)
#define OSPF6_NBR_STATE_INIT                ((LONG)3)
#define OSPF6_NBR_STATE_TWO_WAY             ((LONG)4)
#define OSPF6_NBR_STATE_EXCHANGE_START      ((LONG)5)
#define OSPF6_NBR_STATE_EXCHANGE            ((LONG)6)
#define OSPF6_NBR_STATE_LOADING             ((LONG)7)
#define OSPF6_NBR_STATE_FULL                ((LONG)8)
/*邻居事件定义*/
#define OSPF6_NBR_EVENT_HELLO_RCVD                  0x00
#define OSPF6_NBR_EVENT_INTERFACE_ID_CHANGED        0x01
#define OSPF6_NBR_EVENT_START                       0x02
#define OSPF6_NBR_EVENT_2WAY_RCVD                   0x03
#define OSPF6_NBR_EVENT_NEGOTIATION_DONE            0x04
#define OSPF6_NBR_EVENT_EXCHANGE_DONE               0x05
#define OSPF6_NBR_EVENT_FULLY_EXCHANGED             0x06
#define OSPF6_NBR_EVENT_BAD_LS_REQ                  0x07
#define OSPF6_NBR_EVENT_LOADING_DONE                0x08
#define OSPF6_NBR_EVENT_ADJ_OK                      0x09
#define OSPF6_NBR_EVENT_SEQ_NUMBER_ERR              0x0A
#define OSPF6_NBR_EVENT_1WAY_RCVD                   0x0B
#define OSPF6_NBR_EVENT_KILL_NBR                    0x0C
#define OSPF6_NBR_EVENT_INACTIVITY_TMR              0x0D
#define OSPF6_NBR_EVENT_LL_DOWN                     0x0E
#define OSPF6_NBR_EVENT_JUST_FRIENDS                0x0F
#define OSPF6_NBR_EVENT_SETUP_ADJ                   0x10
#define OSPF6_NBR_EVENT_SLOW_ADJ_ERR                0x11
#define OSPF6_NBR_EVENT_RESET_INACT_TIMER           0x12
/*接口状态定义*/
#define OSPF6_IF_STATE_DOWN                 ((LONG)1)
#define OSPF6_IF_STATE_LOOPBACK             ((LONG)2)
#define OSPF6_IF_STATE_WAITING              ((LONG)3)
#define OSPF6_IF_STATE_POINT_TO_POINT       ((LONG)4)
#define OSPF6_IF_STATE_DESIGNATED_ROUTER    ((LONG)5)
#define OSPF6_IF_STATE_BACKUP_DESIGNTD_RTR  ((LONG)6)
#define OSPF6_IF_STATE_OTHER_DESIGNATD_RTR  ((LONG)7)
#define OSPF6_IF_STATE_STANDBY               ((LONG)8)
/*接口事件定义*/
#define OSPF6_IF_INPUT_NON_BCAST_UP              0x00
#define OSPF6_IF_INPUT_ELIG_BCAST_UP             0x01
#define OSPF6_IF_INPUT_BCAST_UP                  0x02
#define OSPF6_IF_INPUT_WAIT_TIMER                0x03
#define OSPF6_IF_INPUT_BACKUP_SEEN               0x04
#define OSPF6_IF_INPUT_NEIGHBOR_CHANGE          0x05
#define OSPF6_IF_INPUT_DR_LOCAL                  0x06
#define OSPF6_IF_INPUT_BACKUP_LOCAL              0x07
#define OSPF6_IF_INPUT_DR_OTHER                  0x08
#define OSPF6_IF_INPUT_LOOP_IND                  0x09
#define OSPF6_IF_INPUT_UNLOOP_IND               0x0A
#define OSPF6_IF_INPUT_INTERFACE_DOWN            0x0B
#define OSPF6_IF_INPUT_MULTI_IF_TO_LINK         0x0C
/* End of Added by guojianjun178934, 2014/7/3   问题单号:DTS2014070303605 */

/*ERRORCODE<OSPF6错误码>*/
typedef enum tagOSPF6_ERROR_CODE
{
    OSPF6_OK = 0,                                   /*0 <OSPF6配置成功>*/
    OSPF6_NO_ERROR,                                 /*1 <OSPF6通配配置成功>*/
    OSPF6_ERR_GEN_ERROR = MID_COMP_OSPFV3 + 2,      /*0x0E3D0002 <MIB配置通用错误>*/
    OSPF6_ERR_WRONG_VALUE,                          /*0x0E3D0003 <MIB配置的值错误>*/
    OSPF6_ERR_INCONSISTENT_VALUE,                   /*0x0E3D0004 <MIB配置的值不一致>*/
    OSPF6_ERR_RESOURCE_UNAVAILABLE,                 /*0x0E3D0005 <MIB配置的资源无效>*/
    OSPF6_ERR_NO_SUCH_OBJECT,                       /*0x0E3D0006 <对象不存在>*/
    OSPF6_ERR_AMB_RC_END_OF_TABLE,                  /*0x0E3D0007 <表项结束>*/
    OSPF6_ERR_AGENT_ERROR,                          /*0x0E3D0008 <MIB消息构造错误>*/
    OSPF6_ERR_INCOMPLETE,                           /*0x0E3D0009 <MIB 不兼容>*/
    OSPF6_ERR_PARTIAL_FAMILY_OK,                    /*0x0E3D0010 <MIB 远端设置成功>*/
    OSPF6_ERR_PRODUCT_NOT_READY,                    /*0x0E3D0011 <对应组件没有准备>*/
    OSPF6_ERR_NULL_POINTER = MID_COMP_OSPFV3 + 100, /*0x0E3D0064 <入参指针为空>*/
    OSPF6_ERR_NOT_REGISTER,                         /*0x0E3D0065 <OSPFv3没有注册>*/
    OSPF6_ERR_CREATE_MUTUX,                         /*0x0E3D0066 <创建信号量失败>*/
    OSPF6_ERR_GET_IPV6COMP,                         /*0x0E3D0067 <获取IPV6组件失败>*/
    OSPF6_ERR_ACTION,                               /*0x0E3D0068 <操作命令字非法>*/
    OSPF6_ERR_PARAMETER,                            /*0x0E3D0069 <入参取值非法>*/
    OSPF6_ERR_PROCESS,                              /*0x0E3D006A <>*/
    OSPF6_ERR_IF_NOT_EXIST,                         /*0x0E3D006B <接口不存在>*/
    OSPF6_ERR_IF_TYPE,                              /*0x0E3D006C <接口类型错误>*/
    OSPF6_ERR_GET_IF_INFO,                          /*0x0E3D006D <获取接口信息控制块错误>*/
    OSPF6_ERR_PROCESS_NOT_EXIST,                    /*0x0E3D006E <进程不存在>*/
    OSPF6_ERR_MALLOC_FAIL,                          /*0x0E3D006F <内存分配失败>*/
    OSPF6_ERR_SAME_BIND_INFO,                       /*0x0E3D0070 <该进程或实例已经跟接口绑定>*/
    OSPF6_ERR_NOT_MATCH_BIND_INFO,                  /*0x0E3D0071 <指定进程或实例没有绑定到接口上>*/
    OSPF6_ERR_FAIL_TO_BUILD_IPS,                    /*0x0E3D0072 <构建IPS消息失败>*/
    OSPF6_ERR_FALI_TO_OPEN_CONNECTION,              /*0x0E3D0073 <生成发送句柄失败>*/
    OSPF6_ERR_IF_NOT_ENABLE,                        /*0x0E3D0074 <接口没有使能OSPFV3>*/
    OSPF6_ERR_VRF_NOT_INIT,                         /*0x0E3D0075 <VRF组件没有初始化>*/
    OSPF6_ERR_GET_VRF_INDEX,                        /*0x0E3D0076 <获取VRF索引失败>*/
    OSPF6_ERR_GET_RTM_INST,                         /*0x0E3D0077 <获取RTM实例号失败>*/
    OSPF6_ERR_PROCESSES_REACH_MAX,                  /*0x0E3D0078 <进程数达到最大值>*/
    OSPF6_ERR_PROCESS_IPS,                          /*0x0E3D0079 <IPS消息处理失败>*/
    OSPF6_ERR_PROCESS_EXIST,                        /*0x0E3D007A <进程已存在>*/
    OSPF6_ERR_MEM_RELEASE,                          /*0x0E3D007B <内存释放失败>*/
    OSPF6_ERR_KEY_IS_NULL,                          /*0x0E3D007C <句柄指针为空>*/
    OSPF6_ERR_INSTANCE,                             /*0x0E3D007D <进程号非法>*/
    OSPF6_ERR_INVALID_LSA_TYPE,                     /*0x0E3D007E <LSA类型非法>*/
    OSPF6_ERR_HAVE_NO_AVL_NODE,                     /*0x0E3D007F <没有找到指定的AVL节点>*/
    OSPF6_ERR_PROCESS_NOT_BIND_IF,                  /*0x0E3D0080 <进程没有绑定接口>*/
    OSPF6_ERR_PROCESS_IF_NOT_MATCH,                 /*0x0E3D0081 <指定接口没有绑定在指定进程上>*/
    OSPF6_ERR_CFG_PREFERENCE_INT,                   /*0x0E3D0082 <配置区域内路径代价失败>*/
    OSPF6_ERR_CFG_PREFERENCE_EXT,                   /*0x0E3D0083 <配置外部路径代价失败>*/
    OSPF6_ERR_GET_PREFERENCE,                       /*0x0E3D0084 <配置ospfv3协议优先级失败>*/
    OSPF6_ERR_VRFNAME_TOOLONG,                      /*0x0E3D0085 <VRF名过长>*/
    OSPF6_ERR_MAX_SPF_DELAY_TIME,                   /*0x0E3D0086 <SPF定时器最大延时时间错误>*/
    OSPF6_ERR_INVALID_MAX_LOAD_BALANCE,             /*0x0E3D0087 <最大平衡路由个数参数非法>*/
    OSPF6_ERR_INVALID_PREFERENCE_VALUE,             /*0x0E3D0088 <优先级取值非法>*/
    OSPF6_ERR_INVALID_PREFERENCE_TYPE,              /*0x0E3D0089 <优先级类型非法>*/
    OSPF6_ERR_INVALID_NET_TYPE,                     /*0x0E3D008A <OSPFV3网络类型错误>*/
    OSPF6_ERR_INSTANCE_NOT_EXIST,                   /*0x0E3D008B <实例不存在>*/
    OSPF6_ERR_INSTANCE_EXIST,                       /*0x0E3D008C <实例号已存在>*/
    OSPF6_ERR_INVALID_INTF_COST,                    /*0x0E3D008D <接口cost值非法>*/
    OSPF6_ERR_INVALID_INTF_PRIORITY,                /*0x0E3D008E <接口优先级非法>*/
    OSPF6_ERR_INVALID_INTF_RXMT_ITVL,               /*0x0E3D008F <接口重传间隔非法>*/
    OSPF6_ERR_INVALID_INTF_TRANS_DELAY,             /*0x0E3D0090 <接口发送延时非法>*/
    OSPF6_ERR_INVALID_INTF_HELLO_ITVL,              /*0x0E3D0091 <接口hello报文发送间隔非法>*/
    OSPF6_ERR_INVALID_INTF_DEAD_ITVL,               /*0x0E3D0092 <接口老化时间非法>*/
    OSPF6_ERR_INVALID_INTF_FAST_HELLO_MULTI,        /*0x0E3D0093 <接口Fast Hello报文发送个数非法>*/
    OSPF6_ERR_INVALID_NBR_PRIORITY_OPT,             /*0x0E3D0094 <优先级配置标志非法>*/
    OSPF6_ERR_INVALID_NBR_PRIORITY,                 /*0x0E3D0095 <优先级取值非法>*/
    OSPF6_ERR_INVALID_NBR_NETWORK,                  /*0x0E3D0096 <NBR网络类型错误>*/
    OSPF6_ERR_NBR_NOT_EXIST,                        /*0x0E3D0097 <NBR不存在>*/
    OSPF6_ERR_INVALID_NBR_ADDRESS,                  /*0x0E3D0098 <NBR地址无效>*/
    OSPF6_ERR_AREA_NOT_EXIST,                       /*0x0E3D0099 <区域不存在>*/
    OSPF6_ERR_INVALID_AREA,                         /*0x0E3D009A <区域ID非法>*/
    OSPF6_ERR_AAGG_PREFIX_EXIST,                    /*0x0E3D009B <聚合地址已经存在>*/
    OSPF6_ERR_AAGG_PREFIX_NOT_EXIST,                /*0x0E3D009C <聚合地址不存在>*/
    OSPF6_ERR_INVALID_AREA_STUBOPT,                 /*0x0E3D009D <区域选项非法>*/
    OSPF6_ERR_INVALID_AREA_COST,                    /*0x0E3D009E <区域cost值非法>*/
    OSPF6_ERR_INVALID_AREA_RFSH_ITVL,               /*0x0E3D009F <区域洪泛间隔时间非法>*/
    OSPF6_ERR_GETFIRST_FAIL,                        /*0x0E3D00A0 <getfirst操作失败>*/
    OSPF6_ERR_INVALID_AAGG_PREFIX_LENGTH,           /*0x0E3D00A1 <区域聚合前缀长度无效>*/
    OSPF6_ERR_PROCESS_ID_IS_ZERO,                   /*0x0E3D00A2 OSPF6伪进程*/
    OSPF6_ERR_DISABLE_OSPF_ADMIN_STATUS,            /*0x0E3D00A3 disable进程失败*/
    OSPF6_ERR_ENABLE_OSPF_ADMIN_STATUS,             /*0x0E3D00A4 enable进程失败*/
    OSPF6_ERR_INVALID_ACCNUM,                       /*0x0E3D00A5 无效的ACC组号*/
    OSPF6_ERR_CFG_GR_PARA,                          /*0x0E3D00A6 OSPF6 GR配置参数错误*/
    OSPF6_ERR_INVALID_GR_PERIOD,                    /*0x0E3D00A7 OSPF6 GR周期参数错误*/
    OSPF6_ERR_GET_SOCK_INST,                        /*0x0E3D00A8 <获取SOCK实例号失败>*/
    OSPF6_ERR_GET_I3_INST,                          /*0x0E3D00A9 <获取I3实例号失败>*/
    OSPF6_ERR_AREA_EXIST,                           /*0x0E3D00AA <区域已经存在>*/
    OSPF6_ERR_DEAD_ITVL_LESS_HELLO_ITVL,            /*0x0E3D00AB <配置的dead interval小于hello interval>*/
    OSPF6_ERR_AREA_REACH_MAX,                       /*0x0E3D00AC <目前区域数目达到最大>*/
    OSPF6_ERR_END                                   /*0x0E3D00AD <目前错误码上限>*/
}OSPF6_ERROR_E;

/* Added by likaikun00213099, 基于接口统计各状态的邻居, 2014/4/15 */
/* Number of states. */
#define OSPF6_NBR_MAX_STATES  8
/* End of Added by likaikun00213099, 基于接口统计各状态的邻居, 2014/4/15 */

/*Added by guojianjun178934, OSPFV3告警类型定义, 2014/5/12   问题单号:S-IP-005-OSPFv3-005  */
typedef enum tagOSPFV3_WARNING_TYPE
{
    OSPFV3_WARNING_IF_EVENT = 1,    /*接口事件告警*/
    OSPFV3_WARNING_NBR_EVENT,       /*邻居事件告警*/
    OSPFV3_WARNING_NBR_STATE,       /*OSPF邻居告警*/
    OSPFV3_WARNING_MAX
} OSPFV3_WARNING_TYPE_E;

typedef ULONG (*OSPFV3_WARNING_HOOK_FUNC)(ULONG ulWarningType, VOID *pWarningInfo);

#include "ospf6_api_01.h"
/* End of Added by guojianjun178934, 2014/5/12   问题单号:S-IP-005-OSPFv3-005  */
#include "ospf6_cfg_api.h"
#include "ospf6_cmm_api.h"

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _OSPF6_API_H_ */

