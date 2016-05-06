#include "dhcp_inc.h"

#include "dhcpc_def.h"

#include "dhcpv4s_def.h"
#include "dhcpv4s_type.h"
#include "dhcpv4s_var.h"
#include "dhcpv4s_fun.h"
#include "dhcpv4s_comp.h"
#include "dhcpv4s_dbgcmd.h"

/*****************************************************************************
     协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_DHCPV4S_DBGCMD_C
/*lint +e767*/

ULONG g_ulDhcpsPrintLevel = 0;  /*串口输出的级别*/


/* DHCPV4S调试命令相关定义 */
struct Command_S g_stDhcpV4ShowCommand[] =
{
    #ifdef __SPU_DEBUG_VER__
    {
        "debug",
        "show debug command ",
        NULL,
        DHCPV4S_ShowDbgCommand
    },
    #endif
    {
        "switch",
        "show dhcp server switch ",
        NULL,
        DHCPV4S_ShowSwtichCommand
    },
    {
        "expired",
        "Show dhcp server expired ",
        NULL,
        DHCPV4S_ShowExpired
    },
    {
        "lease",
        "Show lease information ",
        NULL,
        DHCPS_ShowLEASE
    },
    #ifdef __SPU_DEBUG_VER__
    {
        "lease_t",
        "Show leasetimer information ",
        NULL,
        DHCPS_ShowLEASETIMER
    },
    #endif
    {
        "machine",
        "Show the information of machine ",
        NULL,
        DHCPS_ShowStateMachine
    },
    #ifdef __SPU_DEBUG_VER__
    {
        "machine_t",
        "Show MachineStateTimer information ",
        NULL,
        DHCPS_ShowStateTIMER
    },
    #endif
    {
        "fail",
        "Show fail branch ",
        NULL,
        DHCPV4S_ShowFailCounter
    },
    {
        "statics",
        "Show statics information",
        NULL,
        DHCPS_ShowStatisc
    }
};

struct Command_Group_S DHCPV4SShowCmdGroup =
{
    sizeof( g_stDhcpV4ShowCommand ) / sizeof( struct Command_S ), 20, g_stDhcpV4ShowCommand
};


struct Command_S g_stDhcpV4CleanCommand[] =
    {
        {
            "fail",
            "Enter into clean fail entironment ",
            NULL,
            DHCPS_CLEAN_FAIL
        },
        {
            "machine",
            "Enter into clean machine entironment ",
            NULL,
            DHCPS_CleanStateMachine
        },
        {
            "statics",
            "Enter into clean statics information ",
            NULL,
            DHCPS_CleanStatisc
        }
    };

struct Command_Group_S DhcpV4CleanTableCmdGroup =
    {
        sizeof( g_stDhcpV4CleanCommand ) / sizeof( struct Command_S ), 20, g_stDhcpV4CleanCommand
    };



/*DHCPV4S一级命令*/
struct Command_S DHCPV4SCommand[ ] =
{
#ifndef __STARTUP_LOAD_MODE__ /* 启动下载 */
    {"show", "dhcpv4s show info ", &DHCPV4SShowCmdGroup, NULL},

#endif
    {"clean", "dhcpv4s clean info ", &DhcpV4CleanTableCmdGroup, NULL},

    #ifdef __SPU_DEBUG_VER__
    { "mem_print",  "show dhcpv4s memory info",
        NULL,     DHCPV4S_DebugShowMemInfo },
    { "print",  "set print level",
        NULL,     DHCPS_DebugPrintLevelSet },
    #endif
};


struct Command_Group_S DHCPV4SDebugCmdGroup =
{
#ifndef __STARTUP_LOAD_MODE__ /* 启动下载 */

    sizeof ( DHCPV4SCommand ) / sizeof ( DHCPV4SCommand [0] ),
    20,
    DHCPV4SCommand

#endif
};

VOS_VOID DHCPV4S_DebugCmdInit(UINT64 ul64Csi)
{
    ULONG ulRet =VOS_OK;
    ulRet = PTM_CommandsRegister ( &DHCPV4SDebugCmdGroup, "dhcpv4s", "dhcpv4s debug command", ul64Csi);

    if (VOS_OK != ulRet)
    {
        VOS_Assert(VOS_FALSE);
    }

    return;
}

/*****************************************************************************
 函 数 名  :DHCPV4S_ShowDbgCommand
 功能描述  : dhcpv4s模块的调试信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010-08-10
    作    者   : jiahuidong 00142544
    修改内容   : 新生成函数

*****************************************************************************/
VOID DHCPV4S_ShowDbgCommand( ULONG argc,CHAR *argv[] )
{
    if ( argc ==0 )
    {
        vos_printf("\r\nPrint debug info :");
        vos_printf("\r\n dhcpv4s show debug       ---Show Debug Command \n");
        vos_printf("\r\n dhcpv4s show switch      ---display dhcp server switch information\n");
        vos_printf("\r\n dhcpv4s show expired     ---Show expired information\n");
        vos_printf("\r\n dhcpv4s Show lease       ---Show lease information\n");
        vos_printf("\r\n dhcpv4s Show lease_t     ---Show lease timer information\n");
        vos_printf("\r\n dhcpv4s Show machine     ---Show the information of machine\n");
        vos_printf("\r\n dhcpv4s Show machine_t   ---Show machine state timer information\n");
        vos_printf("\r\n dhcpv4s Show fail        ---Show fail branch\n");
        vos_printf("\r\n dhcpv4s Show statics        ---Show statics information\n");
        vos_printf("\r\n dhcpv4s clean fail       ---clean fail conter \n");
        vos_printf("\r\n dhcpv4s clean machine    ---clean fail conter \n");
        vos_printf("\r\n dhcpv4s clean statics    ---clean statics information \n");
        return;
    }
    else
    {
        Dhcp4vs_Debug_OnOff(argc,argv);
    }


    OutString("\r\n please input : dhcpv4s show debug");
    return;
}

VOID DHCPV4S_ShowSwtichCommand(ULONG argc,CHAR *argv[])
{
    if( (argc >= 1 && !VOS_StrCmp ( argv [ argc - 1 ], "?")) )
    {
        vos_printf ( "\r\n display dhcp server function : enable <1> , disable <0> ");

        return;
    }
    if ( argc >= 1 )
    {
        vos_printf("\r\n please input : dhcpv4s show switch");
    }

    vos_printf("\r\n Switch Info :g_ulDhcpV4ServerSwitch = %u", g_ulDhcpServerSwitch);

    return;
}

VOID DHCPV4S_ShowExpired(ULONG argc,CHAR *argv[])
{
    CHAR    acApnName[64] = {0};
    USHORT usApnIndex = 0;
    DHCPS_EXPIRED_REC_S stExpiredInfor;

    if (argc != 1 )
    {
        vos_printf ( "\r\nInput Error!");
        return;
    }

    if(!VOS_StrCmp ( argv [ argc - 1 ], "?"))
    {
        vos_printf ( "\r\n please input apn name : STRING<1-63>");
        return;
    }
    if ( ( VOS_StrICmp( argv [0], "" ) == 0 )
     || ( VOS_StrLen(argv [0]) >= 64 ) )
    {
        OutString ( "\r\n apn name err !");
        return;
    }
    else
    {
        VOS_StrCpy(acApnName, argv [0]);
    }

    /* z00175135 DTS2012012003193 全文件pclint 2012-02-09 start */
    if (CdbGetApnIndexByApnName((VOS_UINT8 *)acApnName, &usApnIndex) != VOS_OK)
    /* z00175135 DTS2012012003193 全文件pclint 2012-02-09 end   */
    {
        OutString ( "\r\n CdbGetApnIndexByApnName err !");
        return;
    }
    VOS_MemSet(&stExpiredInfor, 0 , sizeof(DHCPS_EXPIRED_REC_S));
    VOS_MemCpy(&stExpiredInfor, &g_pstExpiredInfor[usApnIndex], sizeof(DHCPS_EXPIRED_REC_S));

    vos_printf("\r\n Expired Info :usApnIndex = %u", g_pstExpiredInfor[usApnIndex].usApnIndex);
    vos_printf("\r\n Expired Info :usDay = %u", g_pstExpiredInfor[usApnIndex].usDay);
    vos_printf("\r\n Expired Info :ucHour = %u", g_pstExpiredInfor[usApnIndex].ucHour);
    vos_printf("\r\n Expired Info :ucMinute = %u", g_pstExpiredInfor[usApnIndex].ucMinute);
    vos_printf("\r\n Expired Info :usUnlimited = %u", g_pstExpiredInfor[usApnIndex].usUnlimited);

    return;

}

VOID DHCPV4S_ShowFailCounter(  ULONG argc, CHAR * argv [] )
{
    ULONG ulCount = 0;
    ULONG i;

    if(argc >= 1)
    {
        PTM_PRINT_EXCEPTION_INFO( "\r\n please input : dhcpv4s show fail ");
        return;
    }

    PTM_PRINT_EXCEPTION_INFO( "\r\n DHCPV4S Failure Counter is :");

    for ( i = 0; i < DHCPS_MAX_FAILURE_COUNTER; i++)
    {
        if ( (g_aulDHCPSDbgCnt[i]) > 0 )
        {
            ulCount += 1;
        }

        PTM_PRINT_EXCEPTION_LOOP("\r\n DHCPS_INTERNAL_BRANCH_%u = %u ",i,g_aulDHCPSDbgCnt[i]);
    }

    if(0 == ulCount)
    {
        PTM_PRINT_EXCEPTION_INFO("\r\n No  DHCPV4S Stardard Message Counter ");
    }

    PTM_PRINT_EXCEPTION_INFO( "\r\n-------------------------------------");

    PTM_PRINT_EXCEPTION_END(PTM_BATCH_CMD_RSP_END);

    return;
}

VOID DHCPV4S_ShowCode( UCHAR *pucMsg, USHORT usLen )
{
    UCHAR ucMaxPerLine = 16;
    UCHAR ucCodeCount = 0, ucLine = 1;

    if ( NULL == pucMsg || usLen == 0 )
    {
        return;
    }

    if (1 != g_ulDhcpsDebug)
    {
        /*调试开关开时才打印*/
        return;
    }

    DHCPV4S_OutString("\r\n#######Begin Decode Message#######\r\n" );

    DHCPV4S_OutString("[%u]  ",ucLine++ );

    while ( usLen > 0 )
    {
        DHCPV4S_OutString("%.2x ", *pucMsg );

        if ( 0 == ( ++ucCodeCount % ucMaxPerLine ) )
        {
            DHCPV4S_OutString("\r\n" );
            if ( ucLine < 10 )
            {
                DHCPV4S_OutString("[%u]  ",ucLine++ );
            }
            else
            {
                DHCPV4S_OutString("[%u] ",ucLine++ );
            }

        }

        usLen--;
        pucMsg++;
    }

    DHCPV4S_OutString("\r\n#######End Decode Message#######\r\n" );

    return;
}

VOS_UINT32 DHCPS_Char2Int(VOS_UINT8 ucChar)
{
    /* 计算字符对应的数值 */
    if ( ucChar >= '0' && ucChar <= '9' )
    {
        return (VOS_UINT32)(ucChar - '0');
    }
    else if ( ucChar >= 'a' && ucChar <= 'f' )
    {
        return (VOS_UINT32)(ucChar - 'a' + 10);
    }
    else if ( ucChar >= 'A' && ucChar <= 'F' )
    {
        return (VOS_UINT32)(ucChar - 'A' + 10);
    }
    else
    {
        return 0;
    }
}

VOS_UINT32 DHCPS_String2Int(VOS_UINT8* pucString, VOS_UINT32 ulBase)
{
    VOS_UINT32 ulResult = 0;
    VOS_UINT32 ulIdx = 0;

    while ( ('\0' != *pucString)
            && (ulIdx<DHCPV4S_MAX_INTSTRING_LEN) )
    {
        ulResult = ulResult*ulBase + DHCPS_Char2Int(*pucString);
        pucString++;
        ulIdx++;
    }
    return ulResult;
}

VOID DHCPS_ShowLEASE(  ULONG argc, CHAR * argv [] )
{
    ULONG ulIndex = 0;
    ULONG ulIter = 0;
    ULONG ulTotalNum = 0;
    DHCPS_LEASE_S  *pstLease = NULL;

    if(1 != argc)
    {
        vos_printf("\r\n Info:dhcpv4s show lease [index] ");
        return;
    }
    if(!VOS_StrCmp( argv [ argc - 1 ], "?"))
    {
        OutString ( "\r\n dhcpv4s show lease [index]");
        return;
    }

    /* 计算有效租约控制块的个数 */
    if (!VOS_StrCmp(argv [ argc - 1 ], "num"))
    {
        for (ulIter = 1; ulIter <= SDB_MAX_CONTEXT_NUM; ulIter++)
        {
            pstLease = &g_pstDhcpSLease[ulIter];
            if (DHCPS_LEASE_USED == pstLease->ucUsed)
            {
                ulTotalNum++;
                vos_printf("\r\n %u", ulIter);
            }
        }

        vos_printf("\r\n totalnumber = %u", ulTotalNum);
        return;
    }

    ulIndex= DHCPS_String2Int((VOS_UINT8*)argv[0], 10);

    if ((SDB_MAX_CONTEXT_NUM < ulIndex) || (0 == ulIndex))
    {
        vos_printf("\r\n index is disable ");
        return;
    }

    pstLease = &g_pstDhcpSLease[ulIndex];

    /*Lease结构体信息*/
    (VOID)vos_printf ( "\r\n----------------The information of Lease-----------------");
    (VOID)vos_printf ( "\r\nulIndex                :  %x",pstLease->ulIndex);
    (VOID)vos_printf ( "\r\nucLeaseState           :  %d",pstLease->ucLeaseState);
    (VOID)vos_printf ( "\r\nucUsed                 :  %d",pstLease->ucUsed);
    (VOID)vos_printf ( "\r\nulAddr                 :  %x",pstLease->ulAddr);
    (VOID)vos_printf ( "\r\n");

    if (pstLease->pstAnalyzedPacket == NULL)
    {
        vos_printf("\r\n pstAnalyzedPacket is null ");
        return;
    }

    /*dhcp网络包物理结构信息*/
    (VOID)vos_printf ( "\r\n------------The information of AnalyzedPacket------------");
    (VOID)vos_printf ( "\r\naucParaReqList         :  %s", pstLease->pstAnalyzedPacket->aucParaReqList);
    (VOID)vos_printf ( "\r\npucChaddr              :  %s", pstLease->pstAnalyzedPacket->pucChaddr);
    (VOID)vos_printf ( "\r\nucHtype                :  %d",pstLease->pstAnalyzedPacket->ucHtype);
    (VOID)vos_printf ( "\r\nucOptionOverload       :  %d",pstLease->pstAnalyzedPacket->ucOptionOverload);
    (VOID)vos_printf ( "\r\nucPacketType           :  %d",pstLease->pstAnalyzedPacket->ucPacketType);
    (VOID)vos_printf ( "\r\nucParaReqLen           :  %d",pstLease->pstAnalyzedPacket->ucParaReqLen);
    (VOID)vos_printf ( "\r\nulCiaddr               :  %x",pstLease->pstAnalyzedPacket->ulCiaddr);
    (VOID)vos_printf ( "\r\nulGiaddr               :  %x",pstLease->pstAnalyzedPacket->ulGiaddr);
    (VOID)vos_printf ( "\r\nulRequestedAddr        :  %x",pstLease->pstAnalyzedPacket->ulRequestedAddr);
    (VOID)vos_printf ( "\r\nulServerId             :  %x",pstLease->pstAnalyzedPacket->ulServerId);
    (VOID)vos_printf ( "\r\nulXid                  :  %x",pstLease->pstAnalyzedPacket->ulXid);
    (VOID)vos_printf ( "\r\nulYiaddr               :  %x",pstLease->pstAnalyzedPacket->ulYiaddr);
    (VOID)vos_printf ( "\r\nusFlags                :  %d",pstLease->pstAnalyzedPacket->usFlags);
    (VOID)vos_printf ( "\r\nusMaxDhcpSize          :  %d",pstLease->pstAnalyzedPacket->usMaxDhcpSize);
    (VOID)vos_printf ( "\r\nusPacketLength         :  %d",pstLease->pstAnalyzedPacket->usPacketLength);

    return;
}

VOID DHCPS_ShowLEASETIMER(  ULONG argc, CHAR * argv [] )
{
    ULONG ulIndex = 0;
    DHCPS_TIMER_LINKLIST_S  *pstLeaseTimer = NULL;

    if(1 != argc)
    {
        vos_printf("\r\n Info:dhcpv4s show lease_t [index] ");
        return;
    }
    if(!VOS_StrCmp ( argv [ argc - 1 ], "?"))
    {
        OutString ( "\r\n dhcpv4s show lease_t [index]");
        return;
    }

    ulIndex= DHCPS_String2Int((VOS_UINT8*)argv[0], 10);

    if ((SDB_MAX_CONTEXT_NUM < ulIndex) || (0 == ulIndex))
    {
        vos_printf("\r\n index is disable ");
        return;
    }

    pstLeaseTimer = &g_pstLeaseTimer[ulIndex];

    /*LeaseTimer结构体信息*/
    (VOID)vos_printf ( "\r\n----------------The information of LeaseTimer-----------------");
    (VOID)vos_printf ( "\r\n PdpIndex         :  %u",pstLeaseTimer->ulPdpIndex);
    (VOID)vos_printf ( "\r\n State            :  %d",pstLeaseTimer->ucState);
    (VOID)vos_printf ( "\r\n TimerType        :  %u",pstLeaseTimer->enTimerType);

    (VOID)vos_printf ( "\r\n NodeTimerCount        :  %u",pstLeaseTimer->ulNodeTimerCount);
    (VOID)vos_printf ( "\r\n g_ulLeaseTimerCount  :  %u", g_ulLeaseTimerCount);
    (VOID)vos_printf ( "\r\n");

    return;
}

VOID DHCPS_ShowStateTIMER(  ULONG argc, CHAR * argv [] )
{
    ULONG ulIndex = 0;
    DHCPS_TIMER_LINKLIST_S  *pstStateTimer = NULL;

    if(1 != argc)
    {
        vos_printf("\r\n Info:dhcpv4s show machine_t [index] ");
        return;
    }
    if(!VOS_StrCmp ( argv [ argc - 1 ], "?"))
    {
        OutString ( "\r\n dhcpv4s show machine_t [index]");
        return;
    }

    ulIndex= DHCPS_String2Int((VOS_UINT8*)argv[0], 10);

    if ((SDB_MAX_CONTEXT_NUM < ulIndex) || (0 == ulIndex))
    {
        vos_printf("\r\n index is disable ");
        return;
    }

    pstStateTimer = &g_pstStateTimer[ulIndex];

    /*MachineStateTimer结构体信息*/
    (VOID)vos_printf ( "\r\n----------------The information of MachineStateTimer-----------------");
    (VOID)vos_printf ( "\r\n PdpIndex        :  %u",pstStateTimer->ulPdpIndex);
    (VOID)vos_printf ( "\r\n State           :  %d",pstStateTimer->ucState);
    (VOID)vos_printf ( "\r\n TimerType       :  %u",pstStateTimer->enTimerType);

    (VOID)vos_printf ( "\r\n NodeTimerCount       :  %u", pstStateTimer->ulNodeTimerCount);
    (VOID)vos_printf ( "\r\n g_ulStateTimerCount  :  %u", g_ulStateTimerCount);


    (VOID)vos_printf ( "\r\n");

    return;
}

VOID DHCPS_ShowStateMachine()
{
    ULONG ulState,ulMsg,ulNewState;
    ULONG ulCount = 0;

    /*当ulAllShowFlag为VOS_OK时，显示所有的计数
    否则只显示有技术的技术*/


    (VOID)vos_printf("\r\n DHCPV4  MachineState Process Statistic Start ");

    for ( ulState = 0 ; ulState < DHCPS_STATE_MAX ; ulState++ ) /*状态循环*/
    {
        (VOID)vos_printf("\r\n  ");
        (VOID)vos_printf("\r\n ------------------------------- ");
        (VOID)vos_printf("\r\n State %s" , g_DHCPStateMachineDescrip[ulState]);

        ulCount = 0;
        for ( ulMsg = 0 ; ulMsg < DHCPS_MSG_MAX ; ulMsg++ )/*消息循环*/
        {
            for ( ulNewState = 0 ; ulNewState < DHCPS_STATE_MAX ; ulNewState++ )/*消息循环*/
            {
                if( 0 != g_stDHCPSStateMachine[ulState].StateChangeOKCount[ulMsg][ulNewState])
                {
                    (VOID)vos_printf("\r\n Change to new state: %s : %u <-Message :%s ",
                        g_DHCPStateMachineDescrip[ulNewState],
                        g_stDHCPSStateMachine[ulState].StateChangeOKCount[ulMsg][ulNewState],
                        g_DHCPMsgNodeDescrip[ulMsg]);
                    ulCount++;
                }
            }

            if( 0 != g_stDHCPSStateMachine[ulState].MsgNOChangeCount[ulMsg])
            {
                (VOID)vos_printf("\r\n NoChange:%u <-Message :%s ",
                    g_stDHCPSStateMachine[ulState].MsgNOChangeCount[ulMsg],
                    g_DHCPMsgNodeDescrip[ulMsg]);
                ulCount++;

            }
            if( 0 != g_stDHCPSStateMachine[ulState].MsgSysERRCount[ulMsg])
            {
                (VOID)vos_printf("\r\n System error:%u <-Message :%s ",
                    g_stDHCPSStateMachine[ulState].MsgSysERRCount[ulMsg],
                    g_DHCPMsgNodeDescrip[ulMsg]);
                ulCount++;
            }
            if( 0 != g_stDHCPSStateMachine[ulState].MsgChangeERRCount[ulMsg])
            {
                (VOID)vos_printf("\r\n Change error:%u <-Message :%s ",
                    g_stDHCPSStateMachine[ulState].MsgChangeERRCount[ulMsg],
                    g_DHCPMsgNodeDescrip[ulMsg]);
                ulCount++;
            }
            if( 0 != g_stDHCPSStateMachine[ulState].StateChangeUNKNOWCount[ulMsg])
            {
                (VOID)vos_printf("\r\n UNKONW Change:%u <-Message :%s ",
                    g_stDHCPSStateMachine[ulState].StateChangeUNKNOWCount[ulMsg],
                    g_DHCPMsgNodeDescrip[ulMsg]);
                ulCount++;
            }


            if( 0 != g_stDHCPSStateMachine[ulState].ErrMsgCount[ulMsg])
            {
                (VOID)vos_printf("\r\n Error Message:%u <-Message :%s ",
                    g_stDHCPSStateMachine[ulState].ErrMsgCount[ulMsg],
                    g_DHCPMsgNodeDescrip[ulMsg]);
                ulCount++;
            }



        }
        if(ulCount == 0)
        {
            (VOID)vos_printf("\r\n State %s Receive no message" , g_DHCPStateMachineDescrip[ulState]);
        }

    }

    (VOID)vos_printf("\r\n DHCPV4  MachineState Process Statistic End ");
    return;

}

VOID DHCPS_CleanStateMachine()
{
    ULONG ulState = 0;
    ULONG ulMsg = 0;
    ULONG ulNewState = 0;

    for ( ulState = 0 ; ulState < DHCPS_STATE_MAX ; ulState++ ) /*状态循环*/
    {
        for ( ulMsg = 0 ; ulMsg < DHCPS_MSG_MAX ; ulMsg++ )/*消息循环*/
        {
            for ( ulNewState = 0 ; ulNewState < DHCPS_STATE_MAX ; ulNewState++ )/*消息循环*/
            {
                g_stDHCPSStateMachine[ulState].StateChangeOKCount[ulMsg][ulNewState] = 0;
            }

            g_stDHCPSStateMachine[ulState].MsgNOChangeCount[ulMsg] = 0;
            g_stDHCPSStateMachine[ulState].MsgSysERRCount[ulMsg] = 0;
            g_stDHCPSStateMachine[ulState].MsgChangeERRCount[ulMsg] = 0;
            g_stDHCPSStateMachine[ulState].StateChangeUNKNOWCount[ulMsg] = 0;
            g_stDHCPSStateMachine[ulState].ErrMsgCount[ulMsg] = 0;
        }
    }

    return;
}



VOID DHCPS_CLEAN_FAIL(ULONG argc, CHAR*argv[])
{
    if( argc != 0 )
    {
       (VOID)vos_printf("\r\n please input : dhcpv4s clean fail ");
       return;
    }
    PGP_MemZero((VOID *)g_aulDHCPSDbgCnt,
                                  (sizeof(ULONG)*DHCPS_MAX_FAILURE_COUNTER));
    return;
}


VOID DHCPS_ShowStatisc(ULONG argc, CHAR*argv[])
{
    ULONG i = 0;
    DHCPS_MSG_BUFFLIST_NODE *pstNode = NULL;
    ULONG ulNodeNum = 0;

    for(i = 0; i < DHCPS_MAX_STATISC; i++)
    {
        if(0 != g_ulDhcpStatisc[i])
        {
            vos_printf("\r\n %s %u",g_DHCPStatiscDescrip[i], g_ulDhcpStatisc[i]);
        }
    }
    vos_printf("\r\n DHCPS_ShowStatisc is over");

    if((1 == argc) && ( 0 == VOS_StrCmp(argv[0],"relay"))&& (NULL != g_pstDHCPMsgBuffList))
    {
        ulNodeNum = g_pstDHCPMsgBuffList->ulNodeNum;
        DHCPV4S_OutString("\r\n g_pstDHCPMsgBuffList number = %u\r\n",ulNodeNum);
        pstNode = g_pstDHCPMsgBuffList->stFistNode.pNext;
        for(i=0; i<ulNodeNum; i++)
        {
            if(NULL == pstNode)
            {
                return;
            }
            DHCPV4S_OutString("--%u",pstNode->ulPdnIndex);
            pstNode = pstNode->pNext;
        }
    }
}


VOID DHCPS_CleanStatisc(ULONG argc, CHAR*argv[])
{
    if( argc != 0 )
    {
       (VOID)vos_printf("\r\n please input : dhcpv4s clean fail ");
       return;
    }
    PGP_MemZero((VOID *)g_ulDhcpStatisc,
                                  (sizeof(ULONG)*DHCPS_MAX_STATISC));
    return;
}


VOID DHCPS_DebugOut_Stub(ULONG ulLevel, CHAR *pszFormat, ...)
{
    va_list ArgList;
    CHAR szBuffer[512];
    CHAR *pcTmpBuf = szBuffer;

    /*lint -e746*/
    va_start(ArgList, pszFormat);
    VOS_vsprintf(pcTmpBuf, pszFormat, ArgList);
    va_end(ArgList);
    /*lint +e746*/

    (VOID)vos_printf("[DHCPS]: %s\r\n", szBuffer);

    return;
}

VOID DHCPS_DebugPrintLevelSet( ULONG ulArgc, CHAR *szArgv[] )
{
    ULONG ulPrintLevel = 0;

    if (1 != ulArgc)
    {
        vos_printf( "\r\n Please input print level!" );
        return;
    }

    if (0 != VOS_StrToUint32(szArgv[0], &ulPrintLevel))
    {
        vos_printf("\r\n Please input parameter(1~4) !");
        return;
    }

    g_ulDhcpsPrintLevel = ulPrintLevel;

    return;
}


VOID DHCPS_DebugOut(ULONG ulLevel, CHAR* pszFile, ULONG ulLineNo, CHAR *pszFuncName, CHAR *pszFormat, ...)
{
    va_list ArgList;
    CHAR szBuffer[512];
    CHAR *pcTmpBuf = szBuffer;

    pcTmpBuf += VOS_sprintf(pcTmpBuf, "%s: ", pszFuncName);

    va_start(ArgList, pszFormat);
    VOS_vsprintf(pcTmpBuf, pszFormat, ArgList);
    va_end(ArgList);

    if ( (1 == g_ulDhcpsPrintLevel && ulLevel <= PTM_LOG_ERR )
        || (1 < g_ulDhcpsPrintLevel ) )
    {
        (VOID)vos_printf("[%s %u]%s\r\n", pszFile, ulLineNo, szBuffer);
    }

    if (PTM_LOG_ERR >= ulLevel)
    {
        //DBG_WriteDiagLog2SRU(g_ulDhcpv4sLogRecordRegId, ulLevel, pszFile, ulLineNo, szBuffer, ArgList);
        PTM_WriteDiagLog(g_ulDhcpv4sLogRecordRegId, ulLevel, pszFile, ulLineNo, "%s", szBuffer);
    }

    return;
}


/*****************************************************************************
 函 数 名  :Dhcp4vs_Debug_OnOff
 功能描述  : dhcpv4s模块的调试开关
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010-08-10
    作    者   : jiahuidong 00142544
    修改内容   : 新生成函数

*****************************************************************************/
VOID Dhcp4vs_Debug_OnOff( ULONG argc, CHAR * argv [ ] )
{
    ULONG ulRet = 0;

    if(argc > 1)
    {
        vos_printf("\r\n Dhcp4vs_Debug_OnOff Parameter Error.");
        return;
    }

    if(!VOS_StrCmp ( argv [0], "$"))
    {
       vos_printf("\r\n 1 deubg on,and 0 is off");
       return;
    }

    (VOID)VOS_StrToUint32(argv[0],&ulRet);

    if(0 == ulRet)
    {
        vos_printf("\r\n Dhcp4vs_Debug_OnOff is OFF.");
        g_ulDhcpsDebug = 0;
        return;
    }
    if(1 == ulRet)
    {
        g_ulDhcpsDebug = 1;
        vos_printf("\r\n Dhcp4vs_Debug_OnOff is ON.");
        return;
    }
    vos_printf("\r\n Dhcp4vs_Debug_OnOff Parameter Error.");
    return;
}


/*****************************************************************************
 函 数 名  : DHCPV4S_OutString
 功能描述  :DHCPV4S模块的调试打印函数
 输入参数  :
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :
 修改历史       :
  1.日      期   : 2009年07月04日
    作      者   : jiahuidong00142544
    修改内容   : 新生成函数
*****************************************************************************/
//[EBCC]2847
VOID DHCPV4S_OutString(CHAR *fmt,...)
{
    /*lint +e530*/
    va_list arg;
    /*lint -e530*/
    CHAR DbgInfo[256] = {0};

    va_start(arg,fmt);
    (VOS_VOID)VOS_nvsprintf(DbgInfo,256, fmt, arg);
    va_end(arg);
#ifdef __WIN32_PLATFORM__
    printf("%s", DbgInfo);
#else
    (VOID)vos_printf("%s", DbgInfo);
#endif

    return;
}

/*****************************************************************************
 函 数 名   : DHCPV4S_PrintMemInfo
 功能描述   : 获取显示dhcpv4s在sc上的内存信息
 输入参数   : ULONG argc, CHAR* argv[], UCHAR ucParIdx
 输出参数   : ULONG *pulParValue
 返 回 值   :

 调用函数   :
 被调函数   :

 修改历史   :
 1.日    期 : 2012年1月18日
   作    者 : guolixian
   修改内容 : 新增函数
 2.日    期 : 2012年2月18日
   作    者 : z00175135
   修改内容 : 修改函数 DTS2011120504839 全pclint修改 2012-02-18
*****************************************************************************/
VOID DHCPV4S_PrintMemInfo(UCHAR *pucStructName,ULONG ulUnitSize, ULONG ulUnitNum, ULONG ulMemSize, UCHAR *pucMemType, UCHAR ucStatic)
{
    ULONG ulCpuId = 0;
    ULONG ulVcpuId = 0;

    ulCpuId = DVM_GetSelfCpuId();
    ulVcpuId = DVM_GetSelfVcpuID();
    /*StructName,UnitSize,UnitNum,ulMemSize,MemType,Static,Mid,Sub-System,CPU,vCPU*/
    if((NULL == pucStructName) || (NULL == pucMemType))
    {
        DHCPV4S_OutString("\r\n print info is wrong\r\n");
        return;
    }
    ulMemSize = ulMemSize >> 20;
    if(ulMemSize > 0)
    {
        DHCPV4S_OutString("%23s,%10u,%12u,%8u,%12s,%8c,%12x,%8s,%6u,%4u\r\n",pucStructName,ulUnitSize,ulUnitNum,
            ulMemSize,pucMemType,ucStatic,MID_DHCPS,"PTM",ulCpuId,ulVcpuId);
    }
    return;
}


/*****************************************************************************
 函 数 名   : DHCPC_DebugShowMemInfo
 功能描述   : 获取显示dhcpc的内存信息
 输入参数   : ULONG argc, CHAR* argv[], UCHAR ucParIdx
 输出参数   : ULONG *pulParValue
 返 回 值   :

 调用函数   :
 被调函数   :

 修改历史   :
 1.日    期 : 2012年1月18日
   作    者 : guolixian
   修改内容 : 新增函数
*****************************************************************************/
VOID DHCPV4S_DebugShowMemInfo(ULONG argc, CHAR* argv[])
{
    if( 0 == DHCPS_SELF_CSI )
    {
        return;
    }

    DHCPV4S_OutString("\r\n ---------------------------- TABLE INFO--------------------------------------------\r\n");
    DHCPV4S_OutString("\r\n *************************************The DHCPV4S memory info Begin*******************************************************");

    DHCPV4S_OutString("\r\n    StructName,            UnitSize,   UnitNum,    ulMemSize,  MemType,    Static, Mid,      Sub-System, CPU, vCPU\r\n");

    /* z00175135 DTS2012012003193 全文件pclint 2012-02-09 start */
    DHCPV4S_PrintMemInfo(((UCHAR *)"g_ulDhcpStatisc"),(sizeof(ULONG) * DHCPS_MAX_STATISC),1,
        (sizeof(ULONG) * DHCPS_MAX_STATISC), ((UCHAR *)"SC"),('N'));

    /*lint -save -e564*/
    DHCPV4S_PrintMemInfo(((UCHAR *)"g_pstDhcpSLease"),(sizeof(DHCPS_LEASE_S)),((SDB_MAX_CONTEXT_NUM)+1),
        (sizeof(DHCPS_LEASE_S)*((SDB_MAX_CONTEXT_NUM)+1)), ((UCHAR *)"SC"),('Y'));
    /*lint -restore*/

    DHCPV4S_PrintMemInfo(((UCHAR *)"g_pstOption"),(sizeof(DHCPS_CFG_OPTION_S)),256,
        (sizeof(DHCPS_CFG_OPTION_S) * 256), ((UCHAR *)"SC"),('N'));

    DHCPV4S_PrintMemInfo(((UCHAR *)"g_pstExpiredInfor"),(sizeof(DHCPS_EXPIRED_REC_S)),(MAX_APN_NUM+1) ,
        (sizeof( DHCPS_EXPIRED_REC_S )*( MAX_APN_NUM+1 )) , ((UCHAR *)"SC"),('N'));

    DHCPV4S_PrintMemInfo(((UCHAR *)"g_aulDHCPSDbgCnt"),(sizeof(ULONG)),(DHCPS_MAX_FAILURE_COUNTER),
        (sizeof(ULONG)*DHCPS_MAX_FAILURE_COUNTER), ((UCHAR *)"SC"),('Y'));
    /* z00175135 DTS2012012003193 全文件pclint 2012-02-09 end   */
    DHCPV4S_OutString("\r\n *************************************The DHCPV4S memory info END*********************************************************\r\n ");
    DHCPV4S_OutString("\r\n ---------------------------------------------------------------------------------\r\n");
}

/*****************************************************************************
 函 数 名  : DHCPS_RegLogCnt
 功能描述  : 注册计数打印日志
 输出参数  : 无
 返 回 值  : ULONG
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年1月17日
    作    者   : jixiaoming 00180244
    修改内容   : 新生成函数

*****************************************************************************/
ULONG DHCPS_RegLogCnt(VOID)
{
    ULONG ulResult = VOS_OK;
    ULONG *aulCntUnit[2] = {0};

    PTM_LogCnt_RecRegInfo_S stRegInfo = {0};

    stRegInfo.ul64ComCsi = DHCPS_SELF_CSI;
    stRegInfo.ulComHandle = DHCPS_HANDLE;
    stRegInfo.ulTimeMsgType = DHCPS_MSG_TYPE_TIMER;
    stRegInfo.ulIsTimerSupport = VOS_TRUE;
    stRegInfo.ulDBGLogRegId = g_ulDhcpv4sLogRecordRegId;

    stRegInfo.ulCntUnitNum = 1;
    stRegInfo.ppulCntAddr = aulCntUnit;

    /* 注册打印DHCPV4C计数 */
    PTM_StrNCpy(stRegInfo.aucPrefixName, "DHCPV4SCnt", PTM_LOG_CNT_PREFIX_NAME_MAX_LEN);

    aulCntUnit[0] = g_aulDHCPSDbgCnt;
    stRegInfo.ulTotalCntElemNum = DHCPS_MAX_FAILURE_COUNTER;

    ulResult = PTM_LogCnt_RecordReg(&stRegInfo);
    if (VOS_OK != ulResult)
    {
        DHCPS_DebugPrint(PTM_LOG_ERR, "call PTM_LogCnt_RecordReg fail! DHCPV4C ulResult=%u", ulResult);
    }

    /* 注册打印DHCPV4C计数 */
    PTM_StrNCpy(stRegInfo.aucPrefixName, "DHCPV4SStat", PTM_LOG_CNT_PREFIX_NAME_MAX_LEN);

    aulCntUnit[0] = g_ulDhcpStatisc;
    stRegInfo.ulTotalCntElemNum = DHCPS_MAX_STATISC;

    ulResult = PTM_LogCnt_RecordReg(&stRegInfo);
    if (VOS_OK != ulResult)
    {
        DHCPS_DebugPrint(PTM_LOG_ERR, "call PTM_LogCnt_RecordReg fail! DHCPV4C ulResult=%u", ulResult);
    }

    return ulResult;
}



