

#include "proc.h"
#include "global.h"
#include "string.h"
#include "proto.h"
#include "protect.h"

int disp_pos;
u8 gdt_ptr[6]; /* 0~15:Limit  16~47:Base */
descriptor_t gdt[GDT_SIZE];

u8 idt_ptr[6]; /* 0~15:Limit  16~47:Base */
gate_t idt[IDT_SIZE];

tss_t tss;
proc_t *p_proc_ready;

PUBLIC proc_t proc_table[NR_TASKS + NR_PROCS];
PUBLIC char task_stack[STACK_SIZE_TOTAL];

u32 k_reenter;
u32 k_ticks;

PUBLIC task_t task_table[NR_TASKS] = {
	{task_tty, STACK_SIZE_TTY, "tty"},
	//{task_sys, STACK_SIZE_SYS, "SYS"},
};
PUBLIC task_t user_proc_table[NR_PROCS] = {

	{TestA, STACK_SIZE_TESTA, "TestA"},
	{TestB, STACK_SIZE_TESTB, "TestB"},
	{TestC, STACK_SIZE_TESTC, "TestC"},
};

PUBLIC irq_handler irq_table[NR_IRQ];
PUBLIC system_call sys_call_table[NR_SYS_CALL] = {
	sys_printx,
	sys_sendrec,
};

PUBLIC tty_t tty_table[NR_CONSOLES];
PUBLIC console_t console_table[NR_CONSOLES];
int nr_current_console;