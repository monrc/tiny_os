

#include "proc.h"
#include "global.h"
#include "string.h"
#include "proto.h"
#include "protect.h"
#include "fs.h"
#include "hd.h"

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
	{task_sys, STACK_SIZE_SYS, "SYS"},
	{task_hd, STACK_SIZE_HD, "HD"},
	{task_fs, STACK_SIZE_FS, "FS"},
	
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

/* FS related below */
/*****************************************************************************/
/**
 * For dd_map[k],
 * `k' is the device nr.\ dd_map[k].driver_nr is the driver nr.
 *
 * Remeber to modify include/const.h if the order is changed
 *****************************************************************************/
struct dev_drv_map dd_map[] = {
	/* driver nr.		major device nr.
	   ----------		---------------- */
	{INVALID_DRIVER}, /**< 0 : Unused */
	{INVALID_DRIVER}, /**< 1 : Reserved for floppy driver */
	{INVALID_DRIVER}, /**< 2 : Reserved for cdrom driver */
	{TASK_HD},		  /**< 3 : Hard disk */
	{TASK_TTY},		  /**< 4 : TTY */
	{INVALID_DRIVER}  /**< 5 : Reserved for scsi disk driver */
};

/**
 * 6MB~7MB: buffer for FS
 */
PUBLIC u8 *fsbuf = (u8 *)0x600000;
PUBLIC const int FSBUF_SIZE = 0x100000;

PUBLIC struct file_desc f_desc_table[NR_FILE_DESC];
PUBLIC struct inode inode_table[NR_INODE];
PUBLIC struct super_block super_block[NR_SUPER_BLOCK];
PUBLIC message_t fs_msg;
PUBLIC struct proc *pcaller;
PUBLIC struct inode *root_inode;
PUBLIC struct dev_drv_map dd_map[];