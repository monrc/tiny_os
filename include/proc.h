
#ifndef _OS_PROC_H_
#define _OS_PROC_H_

#include "protect.h"

typedef struct stackframe
{					/* proc_ptr points here		↑ Low		*/
	u32 gs;			/* ┓						│			*/
	u32 fs;			/* ┃						│			*/
	u32 es;			/* ┃						│			*/
	u32 ds;			/* ┃						│			*/
	u32 edi;		/* ┃						│			*/
	u32 esi;		/* ┣ pushed by save()		│			*/
	u32 ebp;		/* ┃						│			*/
	u32 kernel_esp; /* <- 'popad' will ignore it│			*/
	u32 ebx;		/* ┃						↑栈从高地址往低地址增长*/
	u32 edx;		/* ┃						│			*/
	u32 ecx;		/* ┃						│			*/
	u32 eax;		/* ┛						│			*/
	u32 retaddr;	/* return address for assembly code save()		*/
	u32 eip;		/*  ┓						│			*/
	u32 cs;			/*  ┃						│			*/
	u32 eflags;		/*  ┣ these are pushed by CPU during interrupt	*/
	u32 esp;		/*  ┃						│			*/
	u32 ss;			/*  ┛						┷High		*/
} stackframe_t;

typedef struct proc
{
	stackframe_t regs; 			/* process registers saved in stack frame */

	u16 ldt_sel;			   /* gdt selector giving ldt base and limit */
	descriptor_t ldts[LDT_SIZE]; /* local descriptors for code and data */

	int ticks;					/* remained ticks */
	int priority;

	u32 pid;				   /* process id passed in from MM */
	char name[16];		   		/* name of the process */

	int p_flags; 				/* process flags. A proc is runnable iff p_flags==0 */

	message_t *p_msg;
	int p_recvfrom;
	int p_sendto;

	int has_int_msg; 			/* nonzero if an INTERRUPT occurred when  the task is not ready to deal with it.*/
	struct proc *q_sending; 	/* queue of procs sending messages to this proc */
	struct proc *next_sending; /* next proc in the sending queue (q_sending) */

	int nr_tty;
} proc_t;

typedef struct task
{
	task_handler initial_eip;
	int stacksize;
	char name[32];
} task_t;

#define proc2pid(x) (x - proc_table)

#define NR_TASKS 2	/* Number of tasks */
#define NR_PROCS 3	/* Number of procs */
#define FIRST_PROC proc_table[0]
#define LAST_PROC  proc_table[NR_TASKS + NR_PROCS - 1]

/* stacks of tasks */
#define STACK_SIZE_TTY	 0x8000
#define STACK_SIZE_SYS	 0x8000
#define STACK_SIZE_TESTA 0x8000
#define STACK_SIZE_TESTB 0x8000
#define STACK_SIZE_TESTC 0x8000

#define STACK_SIZE_TOTAL (STACK_SIZE_TTY + STACK_SIZE_SYS + STACK_SIZE_TESTA + STACK_SIZE_TESTC + STACK_SIZE_TESTB)

#endif