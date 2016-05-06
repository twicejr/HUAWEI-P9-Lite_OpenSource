#ifndef NSR_FSM_COMMON_INCLUDED
#define NSR_FSM_COMMON_INCLUDED

#ifdef  __cplusplus
extern "C"{
#endif

#define NSR_NULL_EVENT 0xFF

#define NSR_ACT_NO   0
#define NSR_FSM_ERR  0xFF

#define NSR_ACT_A    1
#define NSR_ACT_B    2
#define NSR_ACT_C    3
#define NSR_ACT_D    4
#define NSR_ACT_E    5
#define NSR_ACT_F    6
#define NSR_ACT_G    7
#define NSR_ACT_H    8
#define NSR_ACT_I    9
#define NSR_ACT_J    10
#define NSR_ACT_K    11
#define NSR_ACT_L    12
#define NSR_ACT_M    13
#define NSR_ACT_N    14
#define NSR_ACT_O    15
#define NSR_ACT_P    16
#define NSR_ACT_Q    17
#define NSR_ACT_R    18
#define NSR_ACT_S    19
#define NSR_ACT_T    20
#define NSR_ACT_U    21
#define NSR_ACT_V    22
#define NSR_ACT_W    23
#define NSR_ACT_X    24
#define NSR_ACT_Y    25
#define NSR_ACT_Z    26

typedef struct nsr_fsm_entry
{
  UCHAR next_state;
  UCHAR action;
}NSR_FSM_ENTRY;

#define NSR_EXECUTE_FSM(FSM, INPUT, STATE, ACTION)    \
  ACTION = FSM[INPUT][STATE].action;      \
  STATE = FSM[INPUT][STATE].next_state;

#ifdef  __cplusplus
}
#endif

#endif

