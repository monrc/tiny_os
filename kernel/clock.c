

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
							   clock.c
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
													Forrest Yu, 2005
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "global.h"
#include "string.h"
#include "proto.h"
#include "protect.h"

/*======================================================================*
						   clock_handler
 *======================================================================*/
PUBLIC void clock_handler(int irq)
{
	k_ticks++;
	p_proc_ready->ticks--;

	if (k_reenter)
	{
		//disp_str("!");
		return;
	}

	if (p_proc_ready->ticks > 0)
	{
		return;
	}

	schedule();
}

PUBLIC void milli_delay(int milli_sec)
{
	u32 tick = k_ticks;
	u32 elaspTime = 0;

	milli_sec /= (1000 / HZ);

	while (elaspTime < milli_sec)
	{
		elaspTime = (k_ticks - tick);
	}
}

PUBLIC void init_clock()
{
	/* 初始化 8253 PIT */
	out_byte(TIMER_MODE, RATE_GENERATOR);

	out_byte(TIMER0, (u8)(TIMER_FREQ / HZ));
	out_byte(TIMER0, (u8)((TIMER_FREQ / HZ) >> 8));

	put_irq_handler(CLOCK_IRQ, clock_handler); /* 设定时钟中断处理程序 */
	enable_irq(CLOCK_IRQ);					   /* 让8259A可以接收时钟中断 */
}