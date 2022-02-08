
/* EXTERN is defined as extern except in global.c */
#ifndef _OS_GLOBAL_H_
#define _OS_GLOBAL_H_

#include "proc.h"
#include "console.h"
#include "tty.h"

EXTERN int disp_pos;
EXTERN u8 gdt_ptr[6]; /* 0~15:Limit  16~47:Base */
EXTERN DESCRIPTOR gdt[GDT_SIZE];
EXTERN u8 idt_ptr[6]; /* 0~15:Limit  16~47:Base */
EXTERN GATE idt[IDT_SIZE];

EXTERN TSS tss;
EXTERN u32 k_reenter;
EXTERN u32 k_ticks;

extern char task_stack[];
extern TASK task_table[];
extern TASK user_proc_table[NR_PROCS];

EXTERN PROCESS *p_proc_ready;
extern PROCESS proc_table[];

extern irq_handler irq_table[];

extern TTY tty_table[NR_CONSOLES];
extern CONSOLE console_table[NR_CONSOLES];
extern int nr_current_console;

#endif