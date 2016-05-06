/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasLmmPubMStack.c
    Description : EMM模块收到的所有外部PID的消息, 从这里入口
    History     :
      1.  hanlufeng 41410  Draft Enact
      2.  zhengjunyan 00148421   2011-05-28 文件名由 NasMmPubMStack.c修改为
                                            NasLmmPubMStack.c
******************************************************************************/



/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasLmmPubMInclude.h"
#include    "NasLmmPubMPrint.h"
#include    "NasLmmPubMTimer.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASMMPUBMSTACK_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASMMPUBMSTACK_C
/*lint +e767*/

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/



/*****************************************************************************
  3 Function
*****************************************************************************/


/*****************************************************************************
 Function Name  : NAS_LMM_FSM_PushStackCombine()
 Discription    : 入栈综合操作，包括3个操作:
                                    状态入栈，
                                    定时器入栈，
                                    全局变量入栈;
                  目前只有启动MRRC的RRC连接建立和释放两个过程涉及此操作,
                  后续鉴权过程会涉及到
                  入栈后目的状态的修改不在此函数中执行；
 Input          : 并行状态机ID, UE1.0中固定填NAS_LMM_PARALLEL_FSM_EMM
 Output         : None
 Return         : None
 History:
      1.  hanlufeng 41410  Draft Enact
*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID    NAS_LMM_FSM_PushStackCombine(NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId)
{

    /* 入口检查 */
    if ( enParalFsmId >= NAS_LMM_PARALLEL_FSM_BUTT )
    {
        NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_FSM_PushStackCombine, FsmId error, FsmId",
                            enParalFsmId);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_FSM_PushStackCombine_ENUM
,LNAS_FUNCTION_LABEL1,
                            enParalFsmId );

        return;
    }




    /***************入栈操作***************/

    /* 状态机压栈操作 */
    NAS_LMM_FSM_PushState(enParalFsmId);

    /* 定时器状态入栈 */
    NAS_LMM_FSM_PushTimer(enParalFsmId);

    /* 相关全局变量入栈 */
    NAS_LMM_FSM_PushGlobPar(enParalFsmId);

    return;
}


/*****************************************************************************
 Function Name  : NAS_LMM_FSM_PushState
 Discription    : 当前状态机压栈，不修改状态。即入栈后，当前状态仍保持入栈前
                  的状态，状态修改的工作由执行入栈操作的模块显式执行。
 Input          : 状态机栈地址
 Output         : None
 Return         : None
 History:
      1.  hanlufeng 41410  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LMM_FSM_PushState( NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId)
{

    NAS_LMM_FSM_STATE_STACK_STRU       *pstFsmStack;        /* 状态机栈地址 */
    NAS_LMM_FSM_STATE_STRU             *pstCurFsm;          /* 状态机地址 */
    NAS_LMM_FSM_STATE_STRU             *pstFsmStackTop;     /* 指向栈顶状态 */



    /* 入口检查 */
    if ( NAS_LMM_PARA_FSM_ID_INVALID(enParalFsmId))
    {
        NAS_LMM_PUBM_LOG1_ERR("NAS_EMM_FSM_PushState, The input is illegal! enParalFsmId",
                            enParalFsmId);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_FSM_PushState_ENUM
,LNAS_FUNCTION_LABEL1,
                            enParalFsmId );

        return;
    }

    /* 获取EMM状态机当前状态的地址和状态机栈的地址 */
    pstCurFsm      = NAS_LMM_GetCurFsmAddr(NAS_LMM_PARALLEL_FSM_EMM);
    pstFsmStack    = NAS_LMM_GetFsmStackAddr(NAS_LMM_PARALLEL_FSM_EMM);


    /* 状态机栈是否已满 */
    if ( pstFsmStack->ucStackDepth >= NAS_LMM_MAX_STACK_DEPTH )
    {
        NAS_LMM_PUBM_LOG1_ERR("NAS_EMM_FSM_PushState, The stack depth overflow!, ucStackDepth",
                            pstFsmStack->ucStackDepth);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_FSM_PushState_ENUM
,LNAS_FUNCTION_LABEL2,
                            pstFsmStack->ucStackDepth );

        /* 栈满应该有些出错处理 */

        return;
    }


    /* 获取状态栈栈顶地址 */
    pstFsmStackTop              = &((pstFsmStack->astFsmStack)[pstFsmStack->ucStackDepth]);

    /* 入栈 */
    pstFsmStackTop->enFsmId     = pstCurFsm->enFsmId;
    pstFsmStackTop->enMainState = pstCurFsm->enMainState;
    pstFsmStackTop->enSubState  = pstCurFsm->enSubState;
    pstFsmStackTop->enStaTId    = pstCurFsm->enStaTId;

    /* 栈深度加 1 */
    pstFsmStack->ucStackDepth++;

    return;
}

/*****************************************************************************
 Function Name  : NAS_LMM_FSM_PushTimer
 Discription    : 当前状态机入栈前,分析当前状态涉及到哪些需要保护的定时器
                    本函数只执行两个操作:
                               暂停当前状态运行的状态保护定时器;
                               修改g_stMmMainContext中对应定时器的运行标识
                    入栈操作在 "状态入栈" 中的 enStaTId入栈 操作中实现；
                    出栈时，根据入栈的enStaTId和当前该enStaTId的运行标识，判断
                    enStaTId是否被暂停，是否需要恢复该enStaTId的运行；
 Input          : 并行状态机ID, UE1.0中固定填NAS_LMM_PARALLEL_FSM_EMM
 Output         : None
 Return         : None
 History:
      1.  hanlufeng 41410  Draft Enact
      2.  X00148705 直接调用NAS_LMM_StopStateTimer,函数NAS_LMM_SuspendStateTimer没有充分验证

*****************************************************************************/
VOS_VOID    NAS_LMM_FSM_PushTimer(  NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId)
{
    NAS_LMM_FSM_STATE_STRU              *pstCurFsm;          /* 状态机地址 */


    /* 入口检查 */
    if ( NAS_LMM_PARA_FSM_ID_INVALID(    enParalFsmId))
    {
        NAS_LMM_PUBM_LOG1_ERR(           "NAS_LMM_FSM_PushTimer, The input is illegal! enParalFsmId",
                                        enParalFsmId);
       TLPS_PRINT2LAYER_ERROR1(NAS_LMM_FSM_PushTimer_ENUM
,LNAS_FUNCTION_LABEL1,
                                        enParalFsmId );

        return;
    }

    pstCurFsm                           = NAS_LMM_GetCurFsmAddr(NAS_LMM_PARALLEL_FSM_EMM);

    /* 停当前状态运行的状态保护定时器*/
    NAS_LMM_StopStateTimer(              pstCurFsm->enStaTId);

    return;
}


/*****************************************************************************
 Function Name  : NAS_LMM_FSM_PushGlobPar
 Discription    : 当前状态机入栈前,分析当前状态涉及到哪些需要保护的全局变量
 Input          : 状态机栈地址 新状态
 Output         : None
 Return         : None
 History:

*****************************************************************************/
VOS_VOID    NAS_LMM_FSM_PushGlobPar(NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId)
{
    (VOS_VOID)(enParalFsmId);
    /*暂时没有需要入栈的变量*/

    return;
}



/*****************************************************************************
 Function Name  : NAS_LMM_FSM_PopStackCombine()
 Discription    : 出栈综合操作，包括3个操作:
                                    状态出栈，
                                    定时器出栈，
                                    全局变量出栈，
                  目前只有启动MRRC的RRC连接建立和释放两个过程涉及此操作,
                  后续鉴权过程会涉及到;
 Input          : 并行状态机ID, UE1.0中固定填NAS_LMM_PARALLEL_FSM_EMM
 Output         : None
 Return         : None
 History:
      1.  hanlufeng 41410  Draft Enact
*****************************************************************************/
VOS_VOID    NAS_LMM_FSM_PopStackCombine(
                NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId)
{

    /* 入口检查 */
    if ( NAS_LMM_PARA_FSM_ID_INVALID(enParalFsmId))
    {
        NAS_LMM_PUBM_LOG1_ERR("RRC_FSM_BeginProcess, FsmId error, FsmId",
                            enParalFsmId);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_FSM_PopStackCombine_ENUM
,LNAS_FUNCTION_LABEL1,
                                        enParalFsmId );

        return;
    }


    /***************出栈前环境打印操作***************/

    /* 打印当前状态涉及到的全局变量的值 */




    /***************出栈操作***************/

    /* 状态机出栈操作 */
    NAS_LMM_FSM_PopState(enParalFsmId);

    /* 定时器状态出栈*/
    NAS_LMM_FSM_PopTimer(enParalFsmId);

    /* 相关全局变量出栈*/
    NAS_LMM_FSM_PopGlobPar();



    /***************出栈后环境打印操作***************/
    NAS_LMM_PUBM_LOG_NORM("======================================================================================");
    NAS_LMM_PUBM_LOG_NORM("======NAS_EMM Pop State To:======");
    TLPS_PRINT2LAYER_ERROR(NAS_LMM_FSM_PopStackCombine_ENUM
,LNAS_FUNCTION_LABEL2);

    /* 打印当前状态 */
    NAS_LMM_PrintFsmState(enParalFsmId);
    NAS_LMM_PUBM_LOG_NORM("======================================================================================");
    /* 打印当前状态涉及到的定时器状态 */
   /* NAS_LMM_PrintFsmTimer(enParalFsmId);
    */
    /* 打印当前状态涉及到的全局变量的值 */


    return;
}


/*****************************************************************************
 Function Name  : NAS_LMM_FSM_PopState
 Discription    : 将CCB状态栈中栈顶的状态弹出堆栈，填入当前状态。在流程模块调用
                  RRC_FSM_EndProcess时由MAIN模块自动完成，该接口不对外提供。
 Input          : 状态机栈地址
 Output         : None
 Return         : None
 History:
      1.  hanlufeng 41410  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LMM_FSM_PopState( NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId )
{

    NAS_LMM_FSM_STATE_STACK_STRU       *pstFsmStack;        /* 状态机栈地址 */
    NAS_LMM_FSM_STATE_STRU             *pstCurFsm;          /* 状态机地址 */
    NAS_LMM_FSM_STATE_STRU             *pstFsmStackTop;     /* 指向栈顶状态 */


    /* 入口检查 */
    if ( NAS_LMM_PARA_FSM_ID_INVALID(enParalFsmId))
    {
        NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_FSM_PopState, FsmId error, FsmId", enParalFsmId);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_FSM_PopState_ENUM
,LNAS_FUNCTION_LABEL1,enParalFsmId);
        return;
    }

    /* 获取EMM状态机当前状态的地址和状态机栈的地址 */
    pstCurFsm      = NAS_LMM_GetCurFsmAddr(enParalFsmId);
    pstFsmStack    = NAS_LMM_GetFsmStackAddr(enParalFsmId);


    /* 栈越界 */
    if ( (pstFsmStack->ucStackDepth) > NAS_LMM_MAX_STACK_DEPTH )
    {
        NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_FSM_PopState, The stack depth overflow, ucStackDepth",
                            (pstFsmStack->ucStackDepth));
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_FSM_PopState_ENUM
,LNAS_FUNCTION_LABEL2,
                            (pstFsmStack->ucStackDepth));
        return;
    }

    /* 栈已空 */
    if ( 0 == (pstFsmStack->ucStackDepth) )
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_FSM_PopState, The stack is empty!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_FSM_PopState_ENUM
,LNAS_FUNCTION_LABEL3);
        return;
    }


    /* 获取栈顶第一个有效状态的位置，即栈顶的下一个位置 */
    pstFsmStack->ucStackDepth--;

    /* 获取栈顶第一个有效状态 */
    pstFsmStackTop  = &((pstFsmStack->astFsmStack)[pstFsmStack->ucStackDepth]);

    /* 设置当前状态机 */
    pstCurFsm->enFsmId     = pstFsmStackTop->enFsmId;
    pstCurFsm->enMainState = pstFsmStackTop->enMainState;
    pstCurFsm->enSubState  = pstFsmStackTop->enSubState;
    pstCurFsm->enStaTId    = pstFsmStackTop->enStaTId;

    return;
}

/*****************************************************************************
 Function Name  : NAS_LMM_FSM_PopTimer
 Discription    : 栈顶状态出栈，该栈顶状态对应的定时器在压栈时同步入栈了，则
                  此时需要同步恢复，常见的情况是，把暂停的定时器重新启动；
                    本函数只执行两个操作:
                               恢复运行出栈后的状态的状态保护定时器;
                               修改g_stMmMainContext中对应定时器的运行标识
 Input          : 并行状态机ID, UE1.0中固定填NAS_LMM_PARALLEL_FSM_EMM
 Output         : None
 Return         : None
 History:
      1.  hanlufeng 41410  Draft Enact
      2.  X00148705 直接调用NAS_LMM_StartStateTimer,函数NAS_LMM_ResumeStateTimer没有充分验证

*****************************************************************************/
VOS_VOID    NAS_LMM_FSM_PopTimer(  NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId)
{
    NAS_LMM_FSM_STATE_STRU               *pstCurFsm;          /* 状态机地址 */


    /* 入口检查 */
    if ( NAS_LMM_PARA_FSM_ID_INVALID(    enParalFsmId))
    {
        NAS_LMM_PUBM_LOG1_ERR(           "NAS_LMM_FSM_PushTimer, The input is illegal! enParalFsmId",
                                        enParalFsmId);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_FSM_PopTimer_ENUM
,LNAS_FUNCTION_LABEL1,
                                        enParalFsmId);

        return;
    }

    pstCurFsm                           = NAS_LMM_GetCurFsmAddr(NAS_LMM_PARALLEL_FSM_EMM);

    /* 继续当前状态运行的状态保护定时器，即
        g_stMmMainContext.stNasEmmFsm.astCurFsm.enStaTId*/
    NAS_LMM_StartStateTimer(             pstCurFsm->enStaTId);

    return;

}


/*****************************************************************************
 Function Name  : NAS_LMM_FSM_PopGlobPar
 Discription    : 当前状态机出栈
 Input          : 状态机栈地址 新状态
 Output         : None
 Return         : None
 History:
      1.  hanlufeng 41410  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_LMM_FSM_PopGlobPar(VOS_VOID)
{

    /*暂时没有需要入栈的变量*/

    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_FSM_GetStaAtStackBase
 Description     : 获取栈底的状态
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.z00148421      2010-10-23  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_FSM_GetStaAtStackBase(
                                        NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId)
{
    NAS_LMM_MAIN_STATE_ENUM_UINT16       enMainState;
    NAS_LMM_SUB_STATE_ENUM_UINT16        enSubState;
    NAS_LMM_FSM_STATE_STACK_STRU        *pstFsmStack = VOS_NULL_PTR;
    NAS_LMM_FSM_STATE_STRU              *pstFsmStackBase = VOS_NULL_PTR;

    /* 获取状态栈栈底地址 */
    pstFsmStack  =  NAS_LMM_GetFsmStackAddr(enParalFsmId);
    pstFsmStackBase = &((pstFsmStack->astFsmStack)[NAS_LMM_STACK_BASE]);

    /* 从状态栈获取状态 */
    enMainState                         = pstFsmStackBase->enMainState;
    enSubState                          = pstFsmStackBase->enSubState;

    return NAS_LMM_PUB_COMP_EMMSTATE(enMainState, enSubState);
}

/*****************************************************************************
 Function Name   : NAS_LMM_FSM_GetStaAtStackTop
 Description     : 获取栈顶的状态
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2012-8-10  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_FSM_GetStaAtStackTop(
                                        NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId)
{
    NAS_LMM_MAIN_STATE_ENUM_UINT16       enMainState;
    NAS_LMM_SUB_STATE_ENUM_UINT16        enSubState;
    NAS_LMM_FSM_STATE_STACK_STRU        *pstFsmStack = VOS_NULL_PTR;
    NAS_LMM_FSM_STATE_STRU              *pstFsmStackTop = VOS_NULL_PTR;

    /* 获取状态栈栈底地址 */
    pstFsmStack  =  NAS_LMM_GetFsmStackAddr(enParalFsmId);
    pstFsmStackTop = &((pstFsmStack->astFsmStack)[pstFsmStack->ucStackDepth-1]);

    /* 从状态栈获取状态 */
    enMainState                         = pstFsmStackTop->enMainState;
    enSubState                          = pstFsmStackTop->enSubState;

    return NAS_LMM_PUB_COMP_EMMSTATE(enMainState, enSubState);
}


/*****************************************************************************
 Function Name   : NAS_LMM_PrintFsmTimer
 Description     : 打印当前状态定时器处于哪种状态，打印当前所有协议定时器处于
                   哪种状态
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.qilili 00145085      2008-11-14  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LMM_PrintFsmTimer(NAS_LMM_PARALLEL_FSM_ENUM_UINT16         enParallelFsmId)
{
    NAS_LMM_FSM_STATE_STRU              *pstCurFsm;          /* 状态机地址 */
    NAS_LMM_TIMER_CTRL_STRU             *pstTimerSta;        /* 状态定时器 */
    NAS_LMM_TIMER_CTRL_STRU             *pstTimerPtl;        /* 协议定时器 */
    VOS_UINT16                          usPtlTid;


    /* 入口检查 */
    if ( NAS_LMM_PARA_FSM_ID_INVALID(enParallelFsmId))
    {
        NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_FSM_PushTimer, The input is illegal! enParalFsmId",
                             enParallelFsmId);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_PrintFsmTimer_ENUM
,LNAS_FUNCTION_LABEL1,
                                        enParallelFsmId);

        return;
    }

    pstCurFsm      = NAS_LMM_GetCurFsmAddr(NAS_LMM_PARALLEL_FSM_EMM);
    pstTimerSta    = NAS_LMM_GetMmTimerStaCtrlAddrByIdx(pstCurFsm->enStaTId);

    /*判断当前状态定时器状态为停止和挂起*/
    if(VOS_NULL_PTR == pstTimerSta->psthTimer)
    {
        /*状态定时器处于挂起状态*/
        if((NAS_LMM_TIMER_SS_SUSPENDING == pstTimerSta->ucTimerSs)
           && (NAS_LMM_TIMER_RS_RUNNING == pstTimerSta->ucTimerRs))
        {
            NAS_LMM_PUBM_LOG1_WARN("NAS_LMM_PrintFsmTimer: State Timer is suspended! enStaTId:",
                                  pstCurFsm->enStaTId);
            TLPS_PRINT2LAYER_WARNING1(NAS_LMM_PrintFsmTimer_ENUM
,LNAS_FUNCTION_LABEL2,
                                        pstCurFsm->enStaTId);
        }
        /*状态定时器处于停止状态*/
        else
        {
            NAS_LMM_PUBM_LOG1_WARN("NAS_LMM_PrintFsmTimer: State Timer is stoped! enStaTId:",
                                  pstCurFsm->enStaTId);
            TLPS_PRINT2LAYER_WARNING1(NAS_LMM_PrintFsmTimer_ENUM
,LNAS_FUNCTION_LABEL3,
                                        pstCurFsm->enStaTId);
        }

    }
    /*状态定时器处于运行状态*/

    /*协议定时器*/
    for(usPtlTid = TI_NAS_LMM_PTL_TI_PUB_BOUNDARY_START+1; usPtlTid < NAS_LMM_PTL_TI_BUTT; usPtlTid++)
    {
        pstTimerPtl    = NAS_LMM_GetMmTimerPtlCtrlAddrByIdx(usPtlTid);

        /*协议定时器处于运行状态*/
        if(VOS_NULL_PTR != pstTimerPtl->psthTimer)
        {
            NAS_LMM_PUBM_LOG1_NORM("NAS_LMM_PrintFsmTimer: Ptl Timer is running! PtlTid:",
                                  usPtlTid);
            TLPS_PRINT2LAYER_INFO1(NAS_LMM_PrintFsmTimer_ENUM
,LNAS_FUNCTION_LABEL4,
                                       usPtlTid);
        }
        /*协议定时器处于停止状态*/
        else
        {
            NAS_LMM_PUBM_LOG1_NORM("NAS_LMM_PrintFsmTimer: Ptl Timer is stoped! PtlTid:",
                                  usPtlTid);
            TLPS_PRINT2LAYER_INFO1(NAS_LMM_PrintFsmTimer_ENUM
,LNAS_FUNCTION_LABEL5,
                                       usPtlTid);
        }
    }

    return;
}

/*****************************************************************************
 Function Name  : NAS_LMM_FSM_ClearstackCombine()
 Discription    : 清空栈的综合操作，包括3个操作:
                                    状态清空，
                                    定时器清空
                                    全局变量清空，
                  目前只有收到AUTH REJ过程涉及此操作,
 Input          : 并行状态机ID, UE1.0中固定填NAS_LMM_PARALLEL_FSM_EMM
 Output         : None
 Return         : None
 History:
      1.  leili 00132387    2009-03-31  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_FSM_ClearStackCombine( NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId)
{

    /* 入口检查 */
    if ( NAS_LMM_PARA_FSM_ID_INVALID(enParalFsmId))
    {
        NAS_LMM_PUBM_LOG1_ERR("RRC_FSM_BeginProcess, FsmId error, FsmId",
                            enParalFsmId);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_FSM_ClearStackCombine_ENUM
,LNAS_FUNCTION_LABEL1,
                                       enParalFsmId);

        return;
    }


    /***************出栈前环境打印操作***************/
    /* 打印出栈前的状态 */
    NAS_LMM_PrintFsmState(enParalFsmId);

    /* 打印当前状态涉及到的定时器状态 */
    NAS_LMM_PrintFsmTimer(enParalFsmId);

    /* 打印当前状态涉及到的全局变量的值 */




    /***************出栈操作***************/

    /* 状态机出栈操作 */
    NAS_LMM_FSM_ClearState(enParalFsmId);

    /* 定时器状态出栈*/
    NAS_LMM_FSM_ClearTimer(enParalFsmId);

    /* 相关全局变量出栈*/
    NAS_LMM_FSM_ClearGlobPar();



    /***************出栈后环境打印操作***************/
    /* 打印当前状态 */
    NAS_LMM_PrintFsmState(enParalFsmId);

    /* 打印当前状态涉及到的定时器状态 */
    NAS_LMM_PrintFsmTimer(enParalFsmId);

    /* 打印当前状态涉及到的全局变量的值 */


    return;
}


/*****************************************************************************
 Function Name  : NAS_LMM_FSM_ClearState
 Discription    : 将CCB状态栈中状态清空。在流程模块调用
                  RRC_FSM_EndProcess时由MAIN模块自动完成，该接口不对外提供。
 Input          : 状态机栈地址
 Output         : None
 Return         : None
 History:
      1.  leili 00132387   Draft Enact

*****************************************************************************/
VOS_VOID NAS_LMM_FSM_ClearState( NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId )
{

    NAS_LMM_FSM_STATE_STACK_STRU       *pstFsmStack;        /* 状态机栈地址 */


    /* 入口检查 */
    if ( NAS_LMM_PARA_FSM_ID_INVALID(enParalFsmId))
    {
        NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_FSM_PopState, FsmId error, FsmId", enParalFsmId);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_FSM_ClearState_ENUM
,LNAS_PARAM_INVALID,
                                       enParalFsmId);
        return;
    }

    /* 获取EMM状态机当前状态的地址和状态机栈的地址 */
    pstFsmStack    = NAS_LMM_GetFsmStackAddr(enParalFsmId);


    /* 栈越界 */
    if ( (pstFsmStack->ucStackDepth) > NAS_LMM_MAX_STACK_DEPTH )
    {
        NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_FSM_PopState, The stack depth overflow, ucStackDepth",
                            (pstFsmStack->ucStackDepth));
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_FSM_ClearState_ENUM
,LNAS_FUNCTION_LABEL1,
                                       (pstFsmStack->ucStackDepth));
        return;
    }

    /* 栈已空 */
    if ( 0 == (pstFsmStack->ucStackDepth) )
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_FSM_PopState, The stack is empty!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_FSM_ClearState_ENUM
,LNAS_FUNCTION_LABEL2);
        return;
    }

    /*清除栈内存储的状态机*/
    pstFsmStack->ucStackDepth           = 0;

    NAS_LMM_MEM_SET_S(  pstFsmStack,
                        sizeof(NAS_LMM_FSM_STATE_STACK_STRU),
                        0,
                        sizeof(NAS_LMM_FSM_STATE_STACK_STRU));

    return;
}


/*****************************************************************************
 Function Name  : NAS_LMM_FSM_ClearTimer
 Discription    : 栈顶状态出栈，该栈顶状态对应的定时器在压栈时同步入栈了，则
                  此时需要同步恢复，常见的情况是，把暂停的定时器重新启动；
                    本函数只执行两个操作:
                               恢复运行出栈后的状态的状态保护定时器;
                               修改g_stMmMainContext中对应定时器的运行标识
 Input          : 并行状态机ID, UE1.0中固定填NAS_LMM_PARALLEL_FSM_EMM
 Output         : None
 Return         : None
 History:
      1.  hanlufeng 41410  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_LMM_FSM_ClearTimer(  NAS_LMM_PARALLEL_FSM_ENUM_UINT16 enParalFsmId)
{
    NAS_LMM_FSM_STATE_STRU              *pstCurFsm;          /* 状态机地址 */



    /* 入口检查 */
    if ( NAS_LMM_PARA_FSM_ID_INVALID(enParalFsmId))
    {
        NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_FSM_ClearTimer, The input is illegal! enParalFsmId",
                            enParalFsmId);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_FSM_ClearTimer_ENUM
,LNAS_PARAM_INVALID,
                            enParalFsmId);

        return;
    }

    pstCurFsm      = NAS_LMM_GetCurFsmAddr(NAS_LMM_PARALLEL_FSM_EMM);

    /* 继续当前状态运行的状态保护定时器，即
        g_stMmMainContext.stNasEmmFsm.astCurFsm.enStaTId*/
    NAS_LMM_StopStateTimer(pstCurFsm->enStaTId);

    return;

}
/*lint +e961*/
/*lint +e960*/

/*****************************************************************************
 Function Name  : NAS_LMM_FSM_ClearGlobPar
 Discription    : 当前状态机出栈
 Input          : 状态机栈地址 新状态
 Output         : None
 Return         : None
 History:
      1.  leili 00132387  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_LMM_FSM_ClearGlobPar(VOS_VOID)
{

    /*暂时没有需要入栈的变量*/

    return;
}


/*****************************************************************************
 Function Name  : 清除MM层各状态机的栈
 Discription    : NAS_LMM_FSM_ClearStackResource
 Input          :
 Output         : None
 Return         : None
 History:
      1.  hanlufeng 41410  Draft Enact
*****************************************************************************/
VOS_VOID    NAS_LMM_FSM_ClearStackResource(VOS_VOID)
{
    VOS_UINT32                          ulFsmId;
    NAS_LMM_FSM_STATE_STACK_STRU        *pEmmStack;

    NAS_LMM_PUBM_LOG_NORM("NAS_LMM_FSM_ClearStackResource enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_FSM_ClearStackResource_ENUM
,LNAS_ENTRY);

    for(ulFsmId = NAS_LMM_PARALLEL_FSM_EMM;
        ulFsmId < NAS_LMM_PARALLEL_FSM_BUTT;
        ulFsmId++)
    {
        pEmmStack   = NAS_LMM_GetFsmStackAddr(ulFsmId);

        /* 栈顶位置指示，即栈深度，设为0 */
        pEmmStack->ucStackDepth             = NAS_EMM_STACK_EMPTY;
    }

    return;
}


/*****************************************************************************
 Function Name  :
 Discription    :
 Input          :
 Output         : None
 Return         : None
 History:
      1.  hanlufeng 41410  Draft Enact
*****************************************************************************/





#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of 子系统+模块+文件名.c */
