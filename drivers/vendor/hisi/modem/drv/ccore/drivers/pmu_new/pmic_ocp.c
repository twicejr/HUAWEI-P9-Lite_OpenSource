#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <osl_sem.h>
#include <osl_malloc.h>
#include <osl_thread.h>
#include <bsp_icc.h>
#include <bsp_pmu.h>
#include <pmu_balong.h>
#include <pmu_pmic.h>

extern struct pmic_volt_info g_pmic_voltinfo;

#define PMU_OCP_TASK_STACK_SIZE  (0x1000)
#define PMU_OCP_TASK_PRIORITY    (VX_DEFAULT_PRIORITY - 1)

struct pmic_ocp{
    osl_sem_id      sem_id;
    int             ocp_id;/*用于识别不同的电压源 */
};

struct pmic_ocp g_pmic_ocp;

/*ocp register*/
int pmic_ocp_register(int volt_id,PMU_OCP_FUNCPTR func)
{
    struct pmic_volt_ocp *ocp = NULL;

    if(volt_id < g_pmic_voltinfo.volt_min || volt_id > g_pmic_voltinfo.volt_max)
    {
        pmu_print_error("error, check input param:volt_id:%d\n", volt_id);
        return -1;
    }
    ocp = (struct pmic_volt_ocp *)osl_malloc(sizeof(struct pmic_volt_ocp));
    if (NULL == ocp)
    {
        pmu_print_error("ocp malloc failed ,err %d\n", ocp);
        return -1;
    }

    INIT_LIST_HEAD(&ocp->list);
    ocp->func = func;
    list_add(&ocp->list, &g_pmic_voltinfo.volt_ctrl[volt_id].ocp_list);

    return 0;
}

void pmic_ocp_event_report(void *para)
{
    struct pmic_volt_ocp *ocp = NULL;

    /*coverity[no_escape] */
    while(1)
    {
        osl_sem_down(&g_pmic_ocp.sem_id);

        pmu_print_error("pmu has ocp ,power id %d.\n", g_pmic_ocp.ocp_id);
        
        /*lint -save -e613*/
        list_for_each_entry(ocp, &g_pmic_voltinfo.volt_ctrl[g_pmic_ocp.ocp_id].ocp_list, list)
        {
            if(ocp->func)
            {
                (void) (*(ocp->func))(g_pmic_ocp.ocp_id);
            }
        }
        
        /*lint -restore */
    }
}

int pmic_ocp_receive(void)
{
    int  len        = 0;
    u32  channel_id = ICC_CHN_IFC << 16 | IFC_RECV_FUNC_PMU_OCP;

    len = bsp_icc_read(channel_id, (u8*)&g_pmic_ocp.ocp_id, sizeof(int));
    if((u32)len != sizeof(int))
    {
        pmu_print_error("read len(%x) != expected len(%x).\n", len, sizeof(int));
        return     BSP_PMU_ERROR;
    }

    osl_sem_up(&g_pmic_ocp.sem_id);

    return BSP_PMU_OK;
}

void pmic_ocp_init(void)
{
    u32 chan_id = ICC_CHN_IFC << 16 | IFC_RECV_FUNC_PMU_OCP;
    u32 task_id = 0;
    int ret = 0;
    int volt_id = 0;
    struct pmic_volt_ctrl* volt_ctrl = NULL;

    for(volt_id = g_pmic_voltinfo.volt_min;volt_id <= g_pmic_voltinfo.volt_max;volt_id++)
    {
        volt_ctrl = (struct pmic_volt_ctrl*)(&g_pmic_voltinfo.volt_ctrl[volt_id]);
        //LIST_HEAD(volt_ctrl->ocp_list);
        INIT_LIST_HEAD((struct list_head *)&(volt_ctrl->ocp_list));
    }

    osl_sem_init(0, &g_pmic_ocp.sem_id);

    ret = osl_task_init("pmu_ocp_task", PMU_OCP_TASK_PRIORITY , PMU_OCP_TASK_STACK_SIZE, (OSL_TASK_FUNC)pmic_ocp_event_report, NULL, &task_id);

    ret |= bsp_icc_event_register(chan_id, (read_cb_func)pmic_ocp_receive, NULL, NULL, NULL);
    if(0 != ret)
    {
        pmu_print_error("register is error.\n");
        return ;
    }

    pmu_print_error("pmu ocp init ok!,task id is %d.\n", task_id);

    return ;
}
