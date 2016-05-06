/********************************************************************************************
*等待队列实现原理，双向链表+OS对任务操作的API，暂不支持操作等待
*********************************************************************************************/
#include <sre_task.h>
#include <osl_wait.h>/*lint !e322*/
#include <osl_thread.h>
void init_waitqueue_head(wait_queue_head_t *q)
{
    spin_lock_init(&(q->lock));
    INIT_LIST_HEAD(&(q->task_list));
}

static void __add_wait_queue(wait_queue_head_t *head, wait_queue_t *new)
{
	list_add(&new->task_list, &head->task_list);
}

void prepare_to_wait(wait_queue_head_t *q, wait_queue_t *wait)
{
	unsigned long flags;
    char *pucTaskName = NULL;
    UINT32 uwTaskPID = wait->task_id;
	spin_lock_irqsave(&q->lock, flags);
	if (list_empty(&wait->task_list))
		__add_wait_queue(q, wait); 
    spin_unlock_irqrestore(&q->lock, flags);
    
	if(SRE_OK != SRE_TaskSuspend(uwTaskPID))
    {/*lint !e525*/
        if(SRE_OK != SRE_TaskNameGet((TSK_HANDLE_T)uwTaskPID, &pucTaskName))
        {
            (void)SRE_Printf("get task name fail pid= %d\n",uwTaskPID);            
            spin_unlock_irqrestore(&q->lock, flags);
            return;
        }
        (void)SRE_Printf("wait_event_timeout_func suspend %s fail\n", pucTaskName);
    }/*lint !e525*/
}
static void __wake_up_common(wait_queue_head_t *q)
{
	wait_queue_t *curr, *next;
    char *pucTaskName = NULL;

	list_for_each_entry_safe(curr, next, &q->task_list, task_list) /*lint !e10*//*lint !e26*//*lint !e64*//*lint !e530*//*lint !e666*//*lint !e718*//*lint !e746*/
    {/*lint !e525*/
		if(curr->func(curr->data))
		{   
            list_del_init(&curr->task_list);/*lint !e525*/
			if(SRE_OK != SRE_TaskResume(curr->task_id))
			{
                if(SRE_OK != SRE_TaskNameGet((TSK_HANDLE_T)(curr->task_id), &pucTaskName))/*lint !e525*/
                {
                    (void)SRE_Printf("wake_up resume fail,can't get name,pid= %d\n",curr->task_id); 
                }
                else
                {
                    (void)SRE_Printf("wake_up resume %s fail\n", pucTaskName);
                }
            }/*lint !e525*/
		}
	}
}

void __wake_up_wait_queque(wait_queue_head_t *q)
{
	unsigned long flags;

	spin_lock_irqsave(&q->lock, flags);
	__wake_up_common(q);
	spin_unlock_irqrestore(&q->lock, flags);
}
void finish_wait(wait_queue_head_t *q, wait_queue_t *wait)
{
	unsigned long flags;
	if (!list_empty_careful(&wait->task_list)) {
		spin_lock_irqsave(&q->lock, flags);
		list_del_init(&wait->task_list);
		spin_unlock_irqrestore(&q->lock, flags);
	}
}
/********TEST API*******/
wait_queue_head_t test_waitqueue_head;
unsigned int test_flags_q = 0;
static s32 check_state(void *data)
{    
    (void)SRE_Printf("task 1:wait condition: test_flags_q == 0xffffffff\n\n\n");
    return(test_flags_q == 0xffffffff);
}

static s32 check_state1(void *data)
{    
    (void)SRE_Printf("task 2:wait condition: test_flags_q == 0x88888888\n\n\n");
    return(test_flags_q == 0x88888888);
}


void task_1_do_send(void)
{
    test_flags_q = 0x5a5a5a5a;
    (void)SRE_Printf("task_1 \n");
    wait_event_timeout_func(test_waitqueue_head,0,check_state,(void*)(&test_flags_q));/*lint !e438*/
    if(test_flags_q == 0x5a5a5a5a)/*lint !e438*/
        (void)SRE_Printf("wait_event_timeout_func task_1_do_send fail\n");    
    (void)SRE_Printf("task_1 finish\n\n");
}
void task_2_do_send(void)
{
    test_flags_q = 0x777777;    
    (void)SRE_Printf("task_2 \n");
    wait_event_timeout_func(test_waitqueue_head,0,check_state1,(void*)(&test_flags_q));/*lint !e438*/
    if(test_flags_q == 0x777777)/*lint !e438*/
        (void)SRE_Printf("wait_event_timeout_func task_2_do_send fail\n");    
    (void)SRE_Printf("task_2 finish\n\n");
}

void init_test_task(void)
{    
    OSL_TASK_ID       uwTaskUsrInitId;     
    (void)SRE_Printf("init_waitqueue_head\n");
    init_waitqueue_head(&test_waitqueue_head);
    (void)SRE_Printf("init task:task_1\task_2\n");
    (void)osl_task_init("task1", 2, 4096, (OSL_TASK_FUNC)task_1_do_send, 0, &uwTaskUsrInitId);  /*lint !e534*/  
    (void)osl_task_init("task2", 2, 4096, (OSL_TASK_FUNC)task_2_do_send, 0, &uwTaskUsrInitId); /*lint !e534*/    
    (void)osl_task_delay(10);
    test_flags_q = 0xffffffff;    
    (void)SRE_Printf("write test_flags_q = 0x%x,and wake_up waitqueue\n",test_flags_q);
    wake_up(&test_waitqueue_head);
    (void)osl_task_delay(10);    
    (void)SRE_Printf("write test_flags_q = 0x%x,and wake_up waitqueue\n",test_flags_q);
    test_flags_q = 0x88888888;
    wake_up(&test_waitqueue_head);    
    (void)osl_task_delay(10);    
    (void)SRE_Printf("init_test_task finish\n");
}

