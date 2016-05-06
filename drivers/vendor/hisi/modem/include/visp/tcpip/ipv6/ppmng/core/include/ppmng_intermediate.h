/******************************************************************************
 *
 *        Copyright 2003-2006  Huawei Technologies India Private Limited
 *                          All Rights Reserved
 *
 *------------------------------------------------------------------------------
 *                            ppmng_intermediate.h
 *    Project Code:  VRP5.0
 *    Module Name:  IP6 PP
 *    Create Date:  2003/06/10
 *         Author:  Arun H S
 *     Description: 
 *------------------------------------------------------------------------------
 *  Modification History                                                        
 *  DATE        NAME             DESCRIPTION                                    
 *  ----------------------------------------------------------------------------
 *  2003-06-10  Arun H S         Create
 ******************************************************************************/ 
#ifndef _IP6_PPMNGINTERMEDIATE_H
#define _IP6_PPMNGINTERMEDIATE_H

#ifdef __cplusplus
extern "C"{
#endif

/* Stack (PP) will do the processing*/
#define PP_NO_PROCESS_NEEDED_BY_INTER_FUNCTION              1 

/* Packet has Error, Stack will Destroy the Packet */
#define PP_RET_ERROR                                        2

/* Intermediate Processing will continue processing and will own the packet and if needed will destroy it */
#define PP_PROCESS_BY_INTER_FUNCTION                        3 

/* Packet has been administratively prohibited (for eg: by ACL) */
#define PP_SEND_ICMP_ERROR                                  4
/* Packet has been processed by Qos Input */
#define PP_PROCESS_BY_INTER_FUNCTION_QOSINPUT                       5

#define PP_INPUT_TYPE                   0x01
#define PP_OUTPUT_TYPE                  0x02
#define PP_IO_TYPE                       0x04
#define PP_IFOUTPUT_TYPE                0x08
/*add by peigangqiang for VRP_MODULE_QOS_NEST_POLICY_II*/
#define PP_QOSOUTPUT_TYPE               0x10 

#define PP_LOOP_BACK_IFINDEX   128
typedef struct tagIntermediate
{
    /* The registered function to be used in input processing or output processing */
    ULONG ulType;

    /* Determines the order of executing the function that is  registered. 
     * (Higher the value, higher is the priority level)
     */
    ULONG ulPriority;

    IP6_PP_Register pfIpFwHookFunc;  /* The Registered Function Pointer */
    struct tagIntermediate *pstNext, *pstPrev;
} IP6_PP_IntermediateFunction;


ULONG IP6_PP_Inter_Process (MBUF_S *pstMBuf, ULONG ulType);

/* END: Function Prototypes. */

#ifdef __cplusplus
}
#endif

#endif 

