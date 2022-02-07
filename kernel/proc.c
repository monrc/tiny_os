/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
							   proc.c
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
													Forrest Yu, 2005
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include "proc.h"
#include "global.h"
#include "string.h"
#include "proto.h"
#include "protect.h"

/*======================================================================*
						   sys_get_ticks
 *======================================================================*/
PUBLIC int sys_get_ticks()
{
	return k_ticks;
}

/*======================================================================*
						   schedule
 *======================================================================*/
PUBLIC void schedule()
{
	PROCESS *p;
	int greatest_ticks = 0;
	
	for (p = proc_table; p < proc_table + NR_TASKS + NR_PROCS; p++)
	{
		if (p->ticks > greatest_ticks)
		{
			greatest_ticks = p->ticks;
			p_proc_ready = p;
		}
	}
	
	if (!greatest_ticks)
	{
		for (p = proc_table; p < proc_table + NR_TASKS + NR_PROCS; p++)
		{
			p->ticks = p->priority;
		}
	}
}