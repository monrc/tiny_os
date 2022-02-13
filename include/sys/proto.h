
#ifndef _OS_PROTO_H_
#define _OS_PROTO_H_

#include "type.h"
#include "tty.h"
#include "console.h"
#include "proc.h"

/*======================================================================*
							kernel folder
 *======================================================================*/
/* clock.c */
PUBLIC void init_clock();
PUBLIC void clock_handler(int irq);
PUBLIC void milli_delay(int milli_sec);

/* console.c */
PUBLIC void out_char(console_t *p_con, char ch);
PUBLIC void init_screen(tty_t *p_tty);
PUBLIC int is_current_console(console_t *p_con);
PUBLIC void select_console(int nr_console);
PUBLIC void scroll_screen(console_t *p_con, int direction);

/* global.c */

/* hd.c */
PUBLIC void task_hd();
PUBLIC void hd_handler(int irq);

/* i8259.c */
PUBLIC void init_8259A();
PUBLIC void put_irq_handler(int irq, irq_handler handler);
PUBLIC void spurious_irq(int irq);

/* kernel.asm */
PUBLIC void restart();

/* keyboard.c */
PUBLIC void init_keyboard();
PUBLIC void keyboard_read(tty_t *p_tty);

/* main.c */
PUBLIC void TestA();
PUBLIC void TestB();
PUBLIC void TestC();
PUBLIC int get_ticks();
PUBLIC void panic(const char *fmt, ...);

/* proc.c */
PUBLIC void schedule();
PUBLIC void *va2la(int pid, void *va);
PUBLIC int ldt_seg_linear(struct proc *p, int idx);
PUBLIC void reset_msg(message_t *p);
PUBLIC void dump_msg(const char *title, message_t *m);
PUBLIC void dump_proc(struct proc *p);
PUBLIC int send_recv(int function, int src_dest, message_t *msg);
PUBLIC void inform_int(int task_nr);

/* protect.c */
PUBLIC void init_prot();
PUBLIC u32 seg2phys(u16 seg);



/* systask.c */
PUBLIC void task_sys();

/* tty.c */
PUBLIC void task_tty();
PUBLIC void in_process(tty_t *p_tty, u32 key);

/*======================================================================*
							   lib folder
 *======================================================================*/
/* close.c */
PUBLIC int close(int fd);

/* klib.c */
PUBLIC void disp_int(int input);
PUBLIC void delay(int time);
PUBLIC char *itoa(char *str, int num);

/* kliba.asm */
PUBLIC void disp_str(char *info);
PUBLIC void disp_color_str(char *info, int color);
PUBLIC void out_byte(u16 port, u8 value);
PUBLIC u8 in_byte(u16 port);
PUBLIC void disable_irq(int irq);
PUBLIC void enable_irq(int irq);
PUBLIC void disable_int();
PUBLIC void enable_int();
PUBLIC void port_read(u16 port, void *buf, int n);
PUBLIC void port_write(u16 port, void *buf, int n);
PUBLIC void glitter(int row, int col);

/* misc.c */
PUBLIC void spin(char *func_name);

/* open.c */
PUBLIC int open(const char *pathname, int flags);

/* string.asm */

/* syscall.asm */

/* printf.c */
PUBLIC int printf(const char *fmt, ...);
#define printl printf

/* vsprintf.c */
PUBLIC int vsprintf(char *buf, const char *fmt, va_list args);
PUBLIC int sprintf(char *buf, const char *fmt, ...);




/*======================================================================*
							   fs folder
 *======================================================================*/
/* main.c */
PUBLIC void task_fs();
PUBLIC int rw_sector(int io_type, int dev, u64 pos, int bytes, int proc_nr, void *buf);
PUBLIC struct inode *get_inode(int dev, int num);
PUBLIC void put_inode(struct inode *pinode);
PUBLIC void sync_inode(struct inode *p);
PUBLIC struct super_block *get_super_block(int dev);

/* misc.c */
PUBLIC int do_stat();
PUBLIC int strip_path(char *filename, const char *pathname, struct inode **ppinode);
PUBLIC int search_file(char *path);

/* open.c */
PUBLIC int do_open();
PUBLIC int do_close();

/* 以下是系统调用相关 */

/*======================================================================*
						系统调用 - 系统级
 *======================================================================*/
/* proc.c */
PUBLIC int sys_sendrec(int function, int src_dest, message_t *m, struct proc *p);
PUBLIC int sys_printx(int _unused1, int _unused2, char *s, struct proc *p_proc);

/* syscall.asm */
PUBLIC void sys_call(); /* int_handler */

/*======================================================================*
						系统调用 - 用户级
 *======================================================================*/
PUBLIC int sendrec(int function, int src_dest, message_t *p_msg);
PUBLIC int printx(char *str);

#endif
