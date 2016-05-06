/*******************************************************************************
  ts04.18_support.c  Developed by OBJ System
*******************************************************************************/
#include "ed_user.h"

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TS04_C
/*lint -e961*/
/*lint -e958*/


/*------------------------------------------------------------------------------
    TS 04.18 Table 9.1.54.1 - p-function
------------------------------------------------------------------------------*/
unsigned DECODE_FDD_CELL_INFORMATION_p (unsigned n)
{
    switch (n) {
        case     0: return     0;
        case     1: return    10;
        case     2: return    19;
        case     3: return    28;
        case     4: return    36;
        case     5: return    44;
        case     6: return    52;
        case     7: return    60;
        case     8: return    67;
        case     9: return    74;
        case    10: return    81;
        case    11: return    88;
        case    12: return    95;
        case    13: return   102;
        case    14: return   109;
        case    15: return   116;
        case    16: return   122;
        default   : return     0;
    }
}


/*------------------------------------------------------------------------------
    TS 04.18 Table 9.1.54.1 - q-function
------------------------------------------------------------------------------*/
unsigned DECODE_TDD_CELL_INFORMATION_q (unsigned n)
{
    switch (n) {
        case     0: return     0;
        case     1: return     9;
        case     2: return    17;
        case     3: return    25;
        case     4: return    32;
        case     5: return    39;
        case     6: return    46;
        case     7: return    53;
        case     8: return    59;
        case     9: return    65;
        case    10: return    71;
        case    11: return    77;
        case    12: return    83;
        case    13: return    89;
        case    14: return    95;
        case    15: return   101;
        case    16: return   106;
        case    17: return   111;
        case    18: return   116;
        case    19: return   121;
        case    20: return   126;
        default   : return     0;
    }
}

/*------------------------------------------------------------------------------
    TS 04.60 12.42 PS Handover Radio Resources, 12.42a PS Handover Radio Resources 2
    M&N:Get Timeslot Number for TIMESLOT_ALLOCATION
------------------------------------------------------------------------------*/
unsigned char DECODE_TIMESLOT (unsigned char TimeslotAllocation)
{
    
    unsigned char                       index           = 0;
    unsigned char                       TimeslotNum     = 0;
    unsigned char                       TimeslotMask    = 0x80;
    unsigned char                       Timeslot        = 0;

    /* 8 指的是TIMESLOT_ALLOCATION的8个bit位.*/
    for ( index = 0; index < 8; index++ )                 
    {
        Timeslot = TimeslotAllocation & ( TimeslotMask >> index );
        
        /* TIMESLOT_ALLOCATION中对应的bit位为1是表示分配了时隙 */
        if ( 0 != Timeslot )
        {
            TimeslotNum++;
        }
    }

    return TimeslotNum;
    
}

/*lint +e958*/
/*lint +e961*/
