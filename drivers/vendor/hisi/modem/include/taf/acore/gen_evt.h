

#ifndef __GEN_EVT_H__
#define __GEN_EVT_H__





/******************************************************************************

 MSP 的事件定义,事件ID的定义和MSG 以不同的段来区分

******************************************************************************/
#define ID_EV_MSP_BASE_ID                      0x10000
#define ID_EV_PS_BASE_ID                       0x10500
#define ID_EV_DSP_BASE_ID                      0x11100

/******************************************************************************
 事件ID定义.
 事件ID命名的一般规则为ID_LOG_EV_XXX,ID_LOG_EV_为工具自动生成的.
 事件ID大小为32bit, 如果需要, 各个模块所属的事件ID可以重复.
******************************************************************************/

/*
 系统级别的事件日志ID, 范围是[0x0000-0x1000).
 *** 任何模块都可以使用以下 系统级别的事件日志ID. ***
 作者:沈汉坤/00130424/2009-03-10
*/

#define ID_LOG_EV_LOW_MEM                            0x10001 /* LOG_TYPE_WARNING
 */
#define ID_LOG_EV_LOW_POWER                          0x10002 /* LOG_TYPE_WARNING
 */
#define ID_LOG_EV_QUEUE_FULL                         0x10003 /* LOG_TYPE_WARNING
 */
#define ID_LOG_EV_OS_RESOURCE_UNAVAILABLE            0x10004 /* LOG_TYPE_WARNING
 */
#define ID_LOG_EV_MALLOC_FAIL                        0x10005 /* LOG_TYPE_WARNING
 */
#define ID_LOG_EV_POST_MESSAGE_FAIL                  0x10006 /* LOG_TYPE_WARNING
 */
#define ID_LOG_EV_API_CALL_FAIL                      0x10007 /* LOG_TYPE_WARNING
 */

#define ID_LOG_EV_START_CPU_FAIL                     0x10010 /* LOG_TYPE_ERROR
 */
#define ID_LOG_EV_LOAD_CODE_FAIL                     0x10011 /* LOG_TYPE_ERROR
 */
#define ID_LOG_EV_INIT_DEVICE_FAIL                   0x10012 /* LOG_TYPE_ERROR
 */
#define ID_LOG_EV_INIT_FAIL                          0x10013 /* LOG_TYPE_ERROR
 */
#define ID_LOG_EV_ACCESS_DEVICE_FAIL                 0x10014 /* LOG_TYPE_ERROR
 */
#define ID_LOG_EV_START_TASK_FAIL                    0x10015 /* LOG_TYPE_ERROR
 */

#define ID_LOG_EV_POWER_ON                           0x10020 /* LO G_TYPE_AUDIT_SUCCESS or LOG_TYPE_AUDIT_FAILURE
 */
#define ID_LOG_EV_POWER_OFF                          0x10021 /* LOG_TYPE_AUDIT_SUCCESS
 */
#define ID_LOG_EV_INIT                               0x10022 /* LOG_TYPE_ERROR
 */
#define ID_LOG_EV_INIT_DEVIC                         0x10023 /* LOG_TYPE_ERROR
 */
#define ID_LOG_EV_CREATE_TASK                        0x10024 /* LOG_TYPE_ERROR
 */
#define ID_LOG_EV_DELETE_TASK                        0x10025 /* LOG_TYPE_ERROR
 */


#define ID_LOG_EV_NV_INIT                            0x10030
#define ID_LOG_EV_NV_WRITE                           0x10031
#define ID_LOG_EV_NV_READ                            0x10032


#define ID_LOG_EV_UNKNOWN                            0x10050
#endif /* __GEN_MOD_ID_H__
 */

