
/* EXTERN is defined as extern except in global.c */
#ifndef _OS_GLOBAL_H_
#define _OS_GLOBAL_H_

#include "proc.h"
#include "console.h"
#include "tty.h"
#include "fs.h"

EXTERN int disp_pos;
EXTERN u8 gdt_ptr[6]; /* 0~15:Limit  16~47:Base */
EXTERN descriptor_t gdt[GDT_SIZE];
EXTERN u8 idt_ptr[6]; /* 0~15:Limit  16~47:Base */
EXTERN gate_t idt[IDT_SIZE];

EXTERN tss_t tss;
EXTERN u32 k_reenter;
EXTERN u32 k_ticks;
EXTERN int nr_current_console;

extern char task_stack[];
extern task_t task_table[];
extern task_t user_proc_table[NR_PROCS];

EXTERN proc_t *p_proc_ready;
extern proc_t proc_table[];

extern irq_handler irq_table[];

extern tty_t tty_table[NR_CONSOLES];
extern console_t console_table[NR_CONSOLES];

/* FS */
extern struct dev_drv_map dd_map[];

#endif