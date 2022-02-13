
#include "proc.h"
#include "global.h"
#include "string.h"
#include "proto.h"
#include "protect.h"
#include "stdio.h"

/*======================================================================*
							kernel_main
 *======================================================================*/
PUBLIC int kernel_main()
{
	disp_str("-----\"kernel_main\" begins-----\n");

	task_t *p_task = task_table;
	proc_t *p_proc = proc_table;
	char *p_task_stack = task_stack + STACK_SIZE_TOTAL;
	u16 selector_ldt = SELECTOR_LDT_FIRST;
	int i, j;
	u8 privilege;
	u8 rpl;
	int eflags;
	int priority;

	for (i = 0; i < NR_TASKS + NR_PROCS; i++)
	{
		if (i < NR_TASKS)
		{
			p_task = task_table + i;
			privilege = PRIVILEGE_TASK;
			rpl = RPL_TASK;
			eflags = 0x1202; /* IF=1, IOPL=1, bit 2 is always 1 */
			priority = 15;
		}
		else
		{
			p_task = user_proc_table + (i - NR_TASKS);
			privilege = PRIVILEGE_USER;
			rpl = RPL_USER;
			eflags = 0x202; /* IF=1, bit 2 is always 1 */
			priority = 5;
		}

		p_proc->regs.cs = (0 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | rpl;
		p_proc->regs.ds = (8 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | rpl;
		p_proc->regs.es = (8 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | rpl;
		p_proc->regs.fs = (8 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | rpl;
		p_proc->regs.ss = (8 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | rpl;
		p_proc->regs.gs = (SELECTOR_KERNEL_GS & SA_RPL_MASK) | rpl;

		p_proc->regs.eip = (u32)p_task->initial_eip;
		p_proc->regs.esp = (u32)p_task_stack;
		p_proc->regs.eflags = eflags;

		p_proc->ldt_sel = selector_ldt;

		memcpy(&p_proc->ldts[0], &gdt[SELECTOR_KERNEL_CS >> 3], sizeof(descriptor_t));
		p_proc->ldts[0].attr1 = DA_C | privilege << 5; // change the DPL
		memcpy(&p_proc->ldts[1], &gdt[SELECTOR_KERNEL_DS >> 3], sizeof(descriptor_t));
		p_proc->ldts[1].attr1 = DA_DRW | privilege << 5; // change the DPL

		p_proc->pid = i;
		strcpy(p_proc->name, p_task->name);

		p_proc->flags = 0;
		p_proc->recvfrom = NO_TASK;
		p_proc->sendto = NO_TASK;

		p_proc->has_int_msg = 0;
		p_proc->q_sending = 0;
		p_proc->next_sending = 0;

		p_proc->priority = priority;
		p_proc->ticks = priority;

		p_proc->nr_tty = 0;

		for (j = 0; j < NR_FILES; j++)
		{
			p_proc->filp[j] = 0;
		}

		p_task_stack -= p_task->stacksize;
		p_proc++;
		p_task++;
		selector_ldt += 8; //一个描述符占8个字节
	}

	proc_table[NR_TASKS + 0].nr_tty = 0;
	proc_table[NR_TASKS + 1].nr_tty = 1;
	proc_table[NR_TASKS + 2].nr_tty = 1;

	k_reenter = 0;
	k_ticks = 0;
	p_proc_ready = proc_table;

	init_clock();
	init_keyboard();

	restart();

	while (1)
	{
	}
}

/*****************************************************************************
 *                                get_ticks
 *****************************************************************************/
PUBLIC int get_ticks()
{
	message_t msg;
	reset_msg(&msg);
	msg.type = GET_TICKS;
	send_recv(BOTH, TASK_SYS, &msg);
	return msg.RETVAL;
}

/*****************************************************************************
 *                                panic
 *****************************************************************************/
PUBLIC void panic(const char *fmt, ...)
{
	int i;
	char buf[256];

	/* 4 is the size of fmt in the stack */
	va_list arg = (va_list)((char *)&fmt + 4);

	i = vsprintf(buf, fmt, arg);

	printl("%c !!panic!! %s", MAG_CH_PANIC, buf);

	/* should never arrive here */
	__asm__ __volatile__("ud2");
}

/*======================================================================*
							   TestA
 *======================================================================*/
void TestA()
{
	int i = 0;
	while (1)
	{
		// printf("A");
		// disp_str("A");
		// disp_int(get_ticks());
		int fd = open("/blah", O_CREAT);
		printf("fd: %d\n", fd);
		close(fd);
		spin("TestA");

		milli_delay(1000);
	}
}

/*======================================================================*
							   TestB
 *======================================================================*/
void TestB()
{
	int i = 0x1000;
	while (1)
	{
		printf("B");
		milli_delay(500);
	}
}

/*======================================================================*
							   TestC
 *======================================================================*/
void TestC()
{
	int i = 0x2000;
	while (1)
	{
		printf("C");
		milli_delay(500);
	}
}
