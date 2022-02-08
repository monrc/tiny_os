
#ifndef _OS_PROTO_H_
#define _OS_PROTO_H_

#include "type.h"
#include "tty.h"
#include "console.h"
#include "proc.h"

// kernel file

/* clock.c */
PUBLIC void clock_handler(int irq);
PUBLIC void milli_delay(int milli_sec);
PUBLIC void init_clock();

/* console.c */
PUBLIC void init_screen(TTY *p_tty);
PUBLIC int is_current_console(CONSOLE *p_con);
PUBLIC void out_char(CONSOLE *p_con, char ch);
PUBLIC void select_console(int nr_console);
PUBLIC void scroll_screen(CONSOLE *p_con, int direction);

/* i8259.c */
PUBLIC void init_8259A();
PUBLIC void put_irq_handler(int irq, irq_handler handler);
PUBLIC void spurious_irq(int irq);

/* kernel.asm */
void restart();

/* keyboard.c */
PUBLIC void keyboard_handler(int irq);
PUBLIC void init_keyboard();
PUBLIC void keyboard_read(TTY *p_tty);

/* main.c */
void TestA();
void TestB();
void TestC();

/* printf.c */
PUBLIC int printf(const char *fmt, ...);

/* proc.c */
PUBLIC void schedule();

/* protect.c */
PUBLIC void init_prot();
PUBLIC u32 seg2phys(u16 seg);

/* syscall.asm */
PUBLIC int get_ticks();

/* tty.c */
PUBLIC void task_tty();
PUBLIC void in_process(TTY *p_tty, u32 key);

/* vsprintf.c */
int vsprintf(char *buf, const char *fmt, va_list args);


//		lib file
/* klib.c */
PUBLIC void disp_int(int input);
PUBLIC void delay(int time);
PUBLIC void disable_int();
PUBLIC void enable_int();

/* kliba.asm */
PUBLIC char *itoa(char *str, int num);
PUBLIC void disp_str(char *info);
PUBLIC void disp_color_str(char *info, int color);
PUBLIC void out_byte(u16 port, u8 value);
PUBLIC u8 in_byte(u16 port);
PUBLIC void disable_irq(int irq);
PUBLIC void enable_irq(int irq);

/* 以下是系统调用相关 */

/* 系统调用 - 系统级 */
/* proc.c */
PUBLIC int sys_get_ticks();
PUBLIC int sys_write(char *buf, int len, PROCESS *p_proc);
/* syscall.asm */
PUBLIC void sys_call(); /* int_handler */

/* 系统调用 - 用户级 */
PUBLIC int get_ticks();
PUBLIC void write(char *buf, int len);

#endif
