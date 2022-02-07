
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
							global.c
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
													Forrest Yu, 2005
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "proc.h"
#include "global.h"
#include "string.h"
#include "proto.h"
#include "protect.h"

int disp_pos;
u8 gdt_ptr[6]; /* 0~15:Limit  16~47:Base */
DESCRIPTOR gdt[GDT_SIZE];

u8 idt_ptr[6]; /* 0~15:Limit  16~47:Base */
GATE idt[IDT_SIZE];

TSS tss;
PROCESS *p_proc_ready;

PUBLIC PROCESS proc_table[NR_TASKS + NR_PROCS];
PUBLIC char task_stack[STACK_SIZE_TOTAL];

u32 k_reenter;
u32 k_ticks;

PUBLIC TASK task_table[NR_TASKS] = {
	{task_tty, STACK_SIZE_TTY, "tty"},
};
PUBLIC TASK user_proc_table[NR_PROCS] = {

	{TestA, STACK_SIZE_TESTA, "TestA"},
	{TestB, STACK_SIZE_TESTB, "TestB"},
	{TestC, STACK_SIZE_TESTC, "TestC"},
};

PUBLIC irq_handler irq_table[NR_IRQ];
PUBLIC system_call sys_call_table[NR_SYS_CALL] = {
	sys_get_ticks,
	sys_write,
};

PUBLIC TTY tty_table[NR_CONSOLES];
PUBLIC CONSOLE console_table[NR_CONSOLES];
int nr_current_console;