
#ifndef _OS_TTY_H_
#define _OS_TTY_H_

#include "type.h"
#include "console.h"

#define TTY_IN_BYTES 256 /* tty input queue size */

/* TTY */
typedef struct tty
{
	u32 in_buf[TTY_IN_BYTES]; /* TTY 输入缓冲区 */
	u32 *p_inbuf_head;		  /* 指向缓冲区中下一个空闲位置 */
	u32 *p_inbuf_tail;		  /* 指向键盘任务应处理的键值 */
	int inbuf_count;		  /* 缓冲区中已经填充了多少 */

	console_t *p_console;
} tty_t;

#endif /* _OS_TTY_H_ */