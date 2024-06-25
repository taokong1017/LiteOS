#include "los_typedef.h"
#include "los_task.h"

static UINT32 g_master_tskHandle;
static UINT32 g_slave_tskHandle;

void master_task_entry(void)
{
	while(1) {
		LOS_TaskDelay(1);
		printf("master task delay!\n");
	}
}

void slave_task_entry(void)
{
	UINT16 priority = 0;
	while (true) {
		priority = LOS_TaskPriGet(g_master_tskHandle);
		printf("slave task priority = %d\n", priority);
		LOS_Mdelay(1000);
	}
}


UINT32 test_tasks_init(VOID)
{
    UINT32 ret = LOS_OK;
    TSK_INIT_PARAM_S task_init_param;
	TSK_INIT_PARAM_S task_init_param1;

    memset(&task_init_param, 0, sizeof(TSK_INIT_PARAM_S));
    task_init_param.usTaskPrio = 3;
    task_init_param.pcName = "master_task";
    task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)master_task_entry;
    task_init_param.uwStackSize = 0x6000;
    ret = LOS_TaskCreate(&g_master_tskHandle, &task_init_param);
	if (ret != LOS_OK) {
		return LOS_NOK;
	}

    memset(&task_init_param1, 0, sizeof(TSK_INIT_PARAM_S));
    task_init_param1.usTaskPrio = 5;
    task_init_param1.pcName = "slave_task";
    task_init_param1.pfnTaskEntry = (TSK_ENTRY_FUNC)slave_task_entry;
    task_init_param1.uwStackSize = 0x6000;
    ret = LOS_TaskCreate(&g_slave_tskHandle, &task_init_param1);
	if (ret != LOS_OK) {
		return LOS_NOK;
	}

	return LOS_OK;
}