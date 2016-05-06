#ifndef _TRNG_API_H_
#define _TRNG_API_H_


#ifdef __cplusplus
extern "C"
{
#endif


/* 时间段名字的最大长度 */


/* 名字空间的"类值" */
#define ACL_TRNG_MAXBUCKET 4099

#define ACL_ABSOLUTEMAX 4102444799  /* 23:59:59 31 Sep 2099 4134067140 23:59:00 31 12 2100 */


/* 当前时间数据结构 */
/* 周期时间段所使用的宏 */
#define ACL_PERIODIC_SUN   0x1        /* 0000 0001 */
#define ACL_PERIODIC_MON   0x2        /* 0000 0010 */
#define ACL_PERIODIC_TUE   0x4        /* 0000 0100 */
#define ACL_PERIODIC_WED   0x8        /* 0000 1000 */
#define ACL_PERIODIC_THU   0x10       /* 0001 0000 */
#define ACL_PERIODIC_FRI   0x20       /* 0010 0000 */
#define ACL_PERIODIC_SAT   0x40       /* 0100 0000 */
#define ACL_PERIODIC_DAILY (ACL_PERIODIC_MON|ACL_PERIODIC_TUE|ACL_PERIODIC_WED|\
    ACL_PERIODIC_THU|ACL_PERIODIC_FRI|ACL_PERIODIC_SAT|ACL_PERIODIC_SUN)
                                  /* 0111 1111 */
#define ACL_PERIODIC_WEEKDAY (ACL_PERIODIC_MON|ACL_PERIODIC_TUE|ACL_PERIODIC_WED|\
    ACL_PERIODIC_THU|ACL_PERIODIC_FRI)
                                  /* 0011 1110 */
#define ACL_PERIODIC_WEEKEND (ACL_PERIODIC_SAT|ACL_PERIODIC_SUN)
                                  /* 0100 0001 */
#define ACL_PERIODIC_DAY_TO_DAY 0x80  /* 1000 0000 */

/*
typedef struct tagStrToWeekday
{
    CHAR * szName;
    LONG lHelp;
    LONG lVal;
} STRTOWEEKDAY;
*/

/*  绝对时间段数据结构
    模块支持的起始时间为： 00:00  1 jan 1993
    模块支持的终止时间为： 23:59 31 dec 2035
*/

/**
* @defgroup ACLS ACL Structures
* @ingroup accss ACL API Reference
*/

/**
* @defgroup tagAbsoluteTimeRange ACL_ABSOLUTETIMERANGE_S/PACL_ABSOLUTETIMERANGE_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagAbsoluteTimeRange
* {
*     ULONG m_ulStart;
*     ULONG m_ulEnd;
*     ULONG m_ulIndex;
*     struct tagAbsoluteTimeRange *m_pNext;
* }ACL_ABSOLUTETIMERANGE_S, *PACL_ABSOLUTETIMERANGE_S;
* @endcode
*
* @par Description
* This structure is for absolute time range. It is used in the structure ACL_TIMERANGE_S. This defines 
* the absolute time period for which the timer should be active.
*
* @datastruct m_ulStart The timer should be active from this time. This value will be calculated from 
* the number of seconds since "1970-1-1 0:0:0", till the mentioned time.
* @datastruct m_ulEnd The timer should be inactive after this time. This value will be calculated from 
* the number of seconds since "1970-1-1 0:0:0", till the mentioned time.
* @datastruct m_ulIndex This is the absolute timer index and ranges from 1 - 12.
* @datastruct m_pNext Pointer to next absolute timer.
*/
typedef struct tagAbsoluteTimeRange
{
    ULONG m_ulStart;/*以秒数表示*/
    ULONG m_ulEnd;    /*以秒数表示*/
    ULONG m_ulIndex;        /*add by wangning for TRNG MIB*/
    struct tagAbsoluteTimeRange *m_pNext;
}ACL_ABSOLUTETIMERANGE_S, *PACL_ABSOLUTETIMERANGE_S;



/*  周期时间段数据结构
    当m_ucDayofWeek为"1000 0000"时：
      m_ulStart和m_ulEnd为相对"周日00:00"时刻的绝对时间；
      例如：
        m_ulStart = 1950 = （N_day * 24HOUR) * 60 MINUTE + N_hour * 60 MINUTE + N_minute ；
        1950 / 60 = 32（小时数） + 1/5（分钟数）；
                    32 / 24 = 1（天数） + 1/3（小时数）；
    当m_ucDayofWeek不为"1000 0000"时：
      m_ulStart和m_ulEnd为相对"当天00:00"时刻的绝对时间；
*/


/**
* @defgroup tagPeriodicTimeRange ACL_PERIODICTIMERANGE_S/PACL_PERIODICTIMERANGE_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagPeriodicTimeRange
* {
*     UCHAR m_ucDayofWeek;
*     ULONG m_ulStart;
*     ULONG m_ulEnd;
*     ULONG m_ulIndex;
*     struct tagPeriodicTimeRange *m_pNext;
* } ACL_PERIODICTIMERANGE_S, * PACL_PERIODICTIMERANGE_S;
* @endcode
*
* @par Description
* This is the structure for periodic time range. It is used in the structure ACL_TIMERANGE_S.
* This defines when the timer should be active on periodic basis. That is, on which
* day and at what time the timer should be active or in a week when the timer should
* be active and inactive.
*
* @datastruct m_ucDayofWeek This will define on which day the timer can be active, OR in a week when the timer 
* should be active. The bit pattern can be as follows:
*	- 00000001 : This pattern indicates that the timer active period is on Sunday.
*	- 00000010 : This pattern indicates that the timer active period is on Monday.
*	- 00000100 : This pattern indicates that the timer active period is on Tuesday.
*	- 00001000 : This pattern indicates that the timer active period is on Wednesday.
*	- 00010000 : This pattern indicates that the timer active period is on Thursday.
*	- 00100000 : This pattern indicates that the timer active period is on Friday.
*	- 01000000 : This pattern indicates that the timer active period is on Saturday.
*	- 10000000 : This pattern indicates that the timer active period is on DAY to DAY. 
* If the "DAY TO DAY" Flag is set then other bits should be used and this is also applicable conversely. 
* This bit to define the the timer active period in a week time.
* 
* @datastruct m_ulStart Start time for timer to be active. Start time should be mentioned in minutes. With 
* "DAY TO DAY" flag, time can be calculated in minutes from Sunday 00:00 Hours. Maximum value can be Sat 23:59 Hours
* Without "DAY TO DAY" flag, time can be calculated in minutes from 00:00 Hours. Maximum value can be 23:59 Hours.
* @datastruct m_ulEnd End time for timer to be inactive. End time should be mentioned in minutes. With "DAY TO DAY" 
* flag, time can be calculated in minutes from Sunday 00:00 Hours. Maximum value can be Sat 23:59 Hours. Without 
* "DAY TO DAY" flag, time can be calculated in minutes from 00:00 Hours. Maximum value can be 23:59 Hours.
* @datastruct m_ulIndex This is the periodic timer index and it ranges from 1 - 32.
* @datastruct m_pNext Pointer to next periodic timer.
*/
typedef struct tagPeriodicTimeRange
{
    UCHAR m_ucDayofWeek;
    UCHAR m_aucPadding[3];  /*Padding - ARM Byte Allignment*/
    ULONG m_ulStart;
    ULONG m_ulEnd;
    ULONG m_ulIndex;        /*add by wangning for TRNG MIB*/
    struct tagPeriodicTimeRange *m_pNext;
} ACL_PERIODICTIMERANGE_S, * PACL_PERIODICTIMERANGE_S;



/* 时间段数据结构*/
/**
* @defgroup tagTimeRange ACL_TIMERANGE_S/PACL_TIMERANGE_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagTimeRange
* {
*     CHAR m_szName[ACL_MAX_TR_NAME_LEN];
*     ULONG ulTrngIndex;
*     BOOL_T m_bInFlag;
*     PACL_ABSOLUTETIMERANGE_S m_pstAbsoluteTimeRange;
*     PACL_PERIODICTIMERANGE_S m_pstPeriodicTimeRange;
*     struct tagTimeRange * m_pNext;
* } ACL_TIMERANGE_S, *PACL_TIMERANGE_S;
* @endcode
*
* @par Description
* This is timer structure, which contains pointers to ACL_ABSOLUTETIMERANGE_S and ACL_PERIODICTIMERANGE_S. This 
* timer determines when this timer is active. A timer can be identified by its name.
* 
* @datastruct m_szName Timer name.
* @datastruct ulTrngIndex Timer index.
* @datastruct m_bInFlag Flag to indicate if timer is active or not. A timer is said to be active when current time 
* satisfies both periodic and absolute configured times. It can have the following values:
*	- BOOL_TRUE - Active
*	- BOOL_FALSE - Inactive
* @datastruct m_pstAbsoluteTimeRange Pointer to first absolute timer.
* @datastruct m_pstPeriodicTimeRange Pointer to first periodic timer.
* @datastruct m_pNext Pointer to next timer.
*/
typedef struct tagTimeRange
{
    /*This structure is not 4Byte aligned, No need to align it
    as this will be used only Control Plane and not in Data Plane*/
    CHAR m_szName[ACL_MAX_TR_NAME_LEN];              /* 时间段名 */
    UCHAR m_ucPadding;                                /*Padding - ARM Byte Allignment*/
    BOOL_T m_bInFlag;                                 /* 当前时间是否在该时间段内 */
    ULONG ulTrngIndex;                              /*时间段名字索引add by wangning for TRNG MIB*/
    PACL_ABSOLUTETIMERANGE_S m_pstAbsoluteTimeRange; /* 指向一个绝对时间段 */
    PACL_PERIODICTIMERANGE_S m_pstPeriodicTimeRange; /* 指向一个周期时间段列表 */
    struct tagTimeRange * m_pNext;               /* 指向下一个时间段的指针 */
} ACL_TIMERANGE_S, *PACL_TIMERANGE_S;



/* 时间段名字空间 */



/*PACL_TIMERANGE_S ACL_TRNG_GetByName(CHAR *szName)*/
/**
* @defgroup ACL_TRNG_GetByName ACL_TRNG_GetByName
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* PACL_TIMERANGE_S ACL_TRNG_GetByName(CHAR *szName);
* @endcode
*
* @par Description
* This function is used to get the timer pointer based on the timer name.
*
* @param[in] szName Timer name []
* @param[out]   []
*
* @retval PACL_TIMERANGE_S Indicates timer pointer [|]
* @retval PACL_TIMERANGE_S Indicates no timer exist [NULL|]
*
* @par Dependency
* acl_trng_api.h
*
*
* @par Note
* \n
*
* None
*
*
* @par Related Topics
* None
*/
extern PACL_TIMERANGE_S ACL_TRNG_GetByName(CHAR *szName);

/*ULONG ACL_TRNG_AddTimeRange(CHAR * szName)*/
/**
* @defgroup ACL_TRNG_AddTimeRange ACL_TRNG_AddTimeRange
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_TRNG_AddTimeRange(CHAR * szName);
* @endcode
*
* @par Description
* This function is used to add a timer. You can add a maximum of 256 timers.
* 
* @param[in] szName It is the timer name. Maximum length of timer is 32. The name should 
* not be "ALL" (any cases that is, all or All). []
* @param[out]   []
*
* @retval ULONG In case of success ACL_TRNG_OK is returned. In error scenarios, corresponding
* unique error code is returned. [ACL_TRNG_OK |]
*
* @par Dependency
* acl_trng_api.h
*
*
* @par Note
* \n
*
* None
*
*
* @par Related Topics
* ACL_TRNG_DelTimeRange
*/
extern ULONG ACL_TRNG_AddTimeRange(CHAR * szName);


/*ULONG ACL_TRNG_DelTimeRange(CHAR * szName)*/
/**
* @defgroup ACL_TRNG_DelTimeRange ACL_TRNG_DelTimeRange
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_TRNG_DelTimeRange(CHAR * szName);
* @endcode
*
* @par Description
* This function deletes the timer name.
*
* @param[in] szName Timer name to be deleted []
* @param[out]   []
*
*
* @retval ULONG In case of success ACL_TRNG_OK is returned. In error scenarios, corresponding
* unique error code is returned. [ACL_TRNG_OK |]
*
* @par Dependency
* acl_trng_api.h
*
*
* @par Note
* \n
*
* None
*
*
* @par Related Topics
* ACL_TRNG_AddTimeRange
*/
extern ULONG ACL_TRNG_DelTimeRange(CHAR * szName);

/**
* @defgroup ACL_TRNG_AddPeriodic ACL_TRNG_AddPeriodic
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_TRNG_AddPeriodic( PACL_TIMERANGE_S pThis, 
*                             UCHAR ucDayofWeek, 
*                             ULONG ulStartTime, 
*                             ULONG ulEndTime, 
*                             ULONG ulSubIndex);
* @endcode
*
* @par Description
* This function is used to configure the periodic time range in a timer. That is, periodicity of timer on 
* daily basis or weekly basis at which the timer should be active. Maximum of 32 periodic timers can be added 
* in a timer. Two periodic timers with same periodicity cannot be added.
*
* @param[in] pThis Pointer to the timer to which the periodic timer has to be configured. []
* @param[in] ucDayofWeek This is to mention if the timer should be active on daily basis or weekly basis. 
* The bit pattern can be as follows:
*	- 00000001 : This pattern indicates that the timer active period is on Sunday.
*	- 00000010 : This pattern indicates that the timer active period is on Monday.
*	- 00000100 : This pattern indicates that the timer active period is on Tuesday.
*	- 00001000 : This pattern indicates that the timer active period is on Wednesday.
*	- 00010000 : This pattern indicates that the timer active period is on Thursday.
*	- 00100000 : This pattern indicates that the timer active period is on Friday.
*	- 01000000 : This pattern indicates that the timer active period is on Saturday.
*	- 10000000 : This pattern indicates that the timer active period is on DAY to DAY basis(daily). 
* If the "DAY TO DAY" Flag is set then other bits should not be used and this is also applicable conversely. 
* This bit defines the timer active period in a week time. []
* @param[in] ulStartTime Start time for timer to be active. Start time should be mentioned in minutes. With 
* "DAY TO DAY" flag, time can be calculated in minutes from Sunday 00:00 Hours. Maximum value can be Sat 23:59 Hours.
* Without "DAY TO DAY" flag, time can be calculated in minutes from 00:00 Hours. Max value can be 23:59 Hours. []
* @param[in] ulEndTime End time for timer to be inactive. End time should be mentioned in minutes. With "DAY TO DAY" 
* flag, time can be calculated in minutes from Sunday 00:00 Hours. Maximum value can be Sat 23:59 Hours. Without 
* "DAY TO DAY" flag, time can be calculated in minutes from 00:00 Hours. Maximum value can be 23:59 Hours. []
* @param[in] ulSubIndex Periodic timer index, the value for which ranges from 1 to 32. One cannot add two periodic 
* timers at same index until existing one at that index is deleted. If value "0" is used for index, index will be 
* assigned automatically. []
* @param[out]   []
*
* @retval ULONG In case of success ACL_TRNG_OK is returned. In error scenarios, corresponding
* unique error code is returned. [ACL_TRNG_OK |]
*
* @par Dependency
* acl_trng_api.h
*
*
* @par Note
* \n
*
* None
*
*
* @par Related Topics
* ACL_TRNG_DelPeriodic
*/
extern ULONG ACL_TRNG_AddPeriodic(PACL_TIMERANGE_S pThis, UCHAR ucDayofWeek, ULONG ulStartTime,
    ULONG ulEndTime, ULONG ulSubIndex);

/*ULONG ACL_TRNG_DelPeriodic(PACL_TIMERANGE_S pThis, UCHAR ucDayofWeek,
    ULONG ulStartTime, ULONG ulEndTime)*/
/**
* @defgroup ACL_TRNG_DelPeriodic ACL_TRNG_DelPeriodic
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_TRNG_DelPeriodic(PACL_TIMERANGE_S pThis, UCHAR ucDayofWeek,
*     ULONG ulStartTime, ULONG ulEndTime);
* @endcode
*
* @par Description
* This function deletes a periodic timer from a specified timer. A periodic timer can be identified by its periodicity. 
* The periodic timer can be deleted by providing the periodicity.
*
* @param[in] pThis Timer from which the periodic timer should be deleted. []
* @param[in] ucDayofWeek Same as used in ACL_TRNG_AddPeriodic. []
* @param[in] ulStartTime Same as used in ACL_TRNG_AddPeriodic []
* @param[in] ulEndTime Same as used in ACL_TRNG_AddPeriodic []
* @param[out]   []
*
* @retval ULONG In case of success ACL_TRNG_OK is returned. In error scenarios, corresponding
* unique error code is returned. [ACL_TRNG_OK |]
*
* @par Dependency
* acl_trng_api.h
*
*
* @par Note
* \n
*
* None
*
*
* @par Related Topics
* ACL_TRNG_AddPeriodic
*/
extern ULONG ACL_TRNG_DelPeriodic(PACL_TIMERANGE_S pThis, UCHAR ucDayofWeek,
    ULONG ulStartTime, ULONG ulEndTime);

/*ULONG ACL_TRNG_AddAbsolute(PACL_TIMERANGE_S pThis, ULONG ulStartTime, ULONG ulEndTime, ULONG ulSubIndex)*/
/**
* @defgroup ACL_TRNG_AddAbsolute ACL_TRNG_AddAbsolute
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_TRNG_AddAbsolute( PACL_TIMERANGE_S pThis, 
*                             ULONG ulStartTime, 
*                             ULONG ulEndTime, 
*                             ULONG ulSubIndex);
* @endcode
*
* @par Description
* This function is used to configure the absolute time in a timer. That is, absolute period when a timer should be 
* active. Maximum of 12 absolute timers can be added in a timer. Two absolute timers with same period cannot be added.
*
* @param[in] pThis Pointer to the timer to which the periodic timer has to be configured. []
* @param[in] ulStartTime Start time in seconds (Calculated from from "1970-1-1 0:0:0"). Maximum value is 
* ACL_ABSOLUTEMAX. For calculating the time in seconds for the parameters, the function "ACL_TRNG_TimeToSeconds" 
* can be used. []
* @param[in] ulEndTime End time in seconds (Calculated from from "1970-1-1 0:0:0"). Maximum value is ACL_ABSOLUTEMAX.
* For calculating the time in seconds for the parameters, the function "ACL_TRNG_TimeToSeconds" can be used. []
* @param[in] ulSubIndex Absolute timer index, the value ranges from 1 to 12. One cannot add two absolute 
* timers at same index until existing one at that index is deleted. If value "0" is used for index, index is 
* assigned automatically. []
* @param[out]   []
*
*
*
* @retval Adding absolute timer is success [ULONGACL_TRNG_OK | ]
* @retval Timer pointer is Null [ULONGACL_TRNG_ADD_ABS_TMR_NULL_POINTER_FOR_TIMER | ]
* @retval Invalid index for absolute timer [ULONGACL_TRNG_ADD_ABS_TMR_INVALID_INDEX | ]
* @retval Start time should not be greater than End time [ULONGACL_TRNG_ADD_ABS_TMR_START_TIME_MORE_THAN_END_TIME | ]
* @retval Start/End time cannot maximum time period supported [ULONGACL_TRNG_ADD_ABS_TMR_TIME_OUT_OF_RANGE | ]
* @retval Memory allocation failed [ULONGACL_TRNG_ADD_ABS_TMR_CREATION_FAILED | ]
* @retval Duplicate Time Range [ULONGACL_TRNG_ADD_ABS_TMR_DUPLICATE_TIME_RANGE | ]
* @retval Wrong timer index [ULONGACL_TRNG_ADD_ABS_TMR_WRONG_TMR_INDEX | ]
* @retval Maximum timer reached [ULONGACL_TRNG_ADD_ABS_TMR_MAX_TIMERS_REACHED | ]
* @retval Timer insert failed [ULONGACL_TRNG_ADD_ABS_TMR_FIRST_INSERT_FAILED | ]
* @retval Duplicate timer ID [ULONGACL_TRNG_ADD_ABS_TMR_DUPLICATE_FAILED | ]
* @retval Inserting absolute timer failed [ULONGACL_TRNG_ADD_ABS_TMR_INSERT_FAILED | ]
*
* @par Dependency
* acl_trng_api.h
*
*
* @par Note
* \n
*
* None
*
*
* @par Related Topics
* ACL_TRNG_DelAbsolute
*/

extern ULONG ACL_TRNG_AddAbsolute(PACL_TIMERANGE_S pThis, ULONG ulStartTime, ULONG ulEndTime, ULONG ulSubIndex);

/*ULONG ACL_TRNG_DelAbsolute(PACL_TIMERANGE_S pThis, ULONG ulStartTime, ULONG ulEndTime)*/
/**
* @defgroup ACL_TRNG_DelAbsolute ACL_TRNG_DelAbsolute
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_TRNG_DelAbsolute(PACL_TIMERANGE_S pThis, 
*                            ULONG ulStartTime, 
*                            ULONG ulEndTime);
* @endcode
*
* @par Description
* This function deletes an absolute timer from a specified timer. An absolute timer can be identified by its absolute 
* period. The absolute timer can be deleted by providing the absolute period.
* 
* @param[in] pThis Timer from which the absolute timer should be deleted. []
* @param[in] ulStartTime Same as used in ACL_TRNG_AddAbsolute. []
* @param[in] ulEndTime Same as used in ACL_TRNG_AddAbsolute. []
* @param[out]   []
*
*
* @retval ULONG Delete absolute timer is success [ACL_TRNG_OK | ]
* @retval ULONG Null timer range [ACL_TRNG_DEL_ABS_TMR_NULL_PTR | ]
* @retval ULONG No absolute timers are present [ACL_TRNG_DEL_ABS_TMR_NO_ABSOLUTE_TIMERS | ]
* @retval ULONG Absolute timer does not exist [ACL_TRNG_DEL_ABS_TMR_NO_TIMER_EXIST | ]
*
* @par Dependency
* acl_trng_api.h
*
*
* @par Note
* \n
*
* None
*
*
* @par Related Topics
* ACL_TRNG_AddAbsolute
*/
extern ULONG ACL_TRNG_DelAbsolute(PACL_TIMERANGE_S pThis, ULONG ulStartTime, ULONG ulEndTime);

/*ULONG ACL_TRNG_TimeToSeconds (ULONG ulMin, ULONG ulHour, ULONG ulDate, ULONG ulMonth, ULONG ulYear,
    ULONG *pulRetTimeInSeconds)*/
/**
* @defgroup ACL_TRNG_TimeToSeconds ACL_TRNG_TimeToSeconds
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_TRNG_TimeToSeconds (ULONG ulMin, ULONG ulHour, ULONG ulDate, ULONG ulMonth,
*     ULONG ulYear, ULONG *pulRetTimeInSeconds);
* @endcode
*
* @par Description
* This function calculates the time in seconds from "1970-1-1 0:0:0" till the date and time provided.
*
* @param[in] ulMin The minutes [0-59]
* @param[in] ulHour The hours [0-23]
* @param[in] ulDate The date. The maximum value varies with the specified month and year [1-31]
* @param[in] ulMonth The month [1-12]
* @param[in] ulYear The year [1970-2099]
* @param[in,out] pulRetTimeInSeconds The calculated seconds for the specified time will be placed in this 
* variable. []
*
* @retval ULONG In case of success ACL_TRNG_OK is returned. In error scenarios, corresponding
* unique error code is returned. [ACL_TRNG_OK |]
*
* @par Dependency
* acl_trng_api.h
*
*
* @par Note
* \n
*
* None
*
*
* @par Related Topics
* None
*/
extern ULONG ACL_TRNG_TimeToSeconds (ULONG ulMin, ULONG ulHour, ULONG ulDate, ULONG ulMonth,
    ULONG ulYear, ULONG *pulRetTimeInSeconds);


/**
* @defgroup ACL_TRNG_ShowTimeRange ACL_TRNG_ShowTimeRange
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* VOID ACL_TRNG_ShowTimeRange (CHAR * szName);
* @endcode
*
* @par Description
* This function displays the timer configuration including the following:
*	- Absolute timer details
*	- Periodic timer details
*	- Active OR Inactive
* \n\n
* A timer is active only if current time satisfies both Absolute and Periodic timer configurations.
* The state change of timer (Active or Inactive) happens when timer is refreshed. The refresh is done 
* with maximum delay of one minute. If the timer name is provided as "ALL", (irrespective of cases) the function 
* displays all timer status with details specified above.
* 
* @param[in] szName Pointer to the timer name for which the configuration needs to be displayed. []
* @param[out]   []
*
* @retval ULONG In case of success ACL_TRNG_OK is returned. In error scenarios, corresponding
* unique error code is returned. [ACL_TRNG_OK |]
*
* @par Dependency
* acl_trng_api.h
*
*
* @par Note
* \n
*
* None
*
*
* @par Related Topics
* None
*/
VOID ACL_TRNG_ShowTimeRange (CHAR * szName);



#ifdef __cplusplus
}
#endif


#endif

