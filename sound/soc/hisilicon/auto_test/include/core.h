

#ifndef _AUDIO_AUTO_TEST_CORE_H
#define _AUDIO_AUTO_TEST_CORE_H

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#include <linux/list.h>
#include "util.h"

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define AT_CASE_PRI_HIG  1
#define AT_CASE_PRI_NOR  2
#define AT_CASE_PRI_LOW  3

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 STRUCT定义
*****************************************************************************/

typedef struct at_test_list {
    struct mutex        test_mutex;
    struct list_head    test_list;
    int    priority;
    int    reserved;
}AT_TEST_LIST;

typedef struct at_case_type {

    char   *test_name;
    int     test_result;
    int     test_num;
    int     test_params;
    int     test_pri;

    struct list_head test_node;

    int (*prepare)      (int test_pram);
    int (*begin)        (int test_pram);
    int (*stop)         (int test_pram);

}AT_CASE_TYPE;
/*****************************************************************************
  5 函数指针
*****************************************************************************/


/*****************************************************************************
  6 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  7 全局变量声明
*****************************************************************************/


/*****************************************************************************
  8 函数声明
*****************************************************************************/
extern int at_core_register_test_case(struct at_case_type *test_case);
extern int at_core_unregister_test_case(struct at_case_type *test_case);
extern void at_core_test_list_start (struct at_test_list *test_list);
extern void at_core_start_test_flow (void);

#endif /* _AUDIO_AUTO_TEST_CORE_H */
