

#include "protect.h"
#include "string.h"
#include "proc.h"
#include "tty.h"
#include "console.h"
#include "global.h"
#include "keyboard.h"
#include "proto.h"


/*****************************************************************************
 *                                task_sys
 *****************************************************************************/
/**
 * <Ring 1> The main loop of TASK SYS.
 *
 *****************************************************************************/
PUBLIC void task_sys()
{
	message_t msg;
	while (1)
	{
		continue;
		
		send_recv(RECEIVE, ANY, &msg);
		int src = msg.source;

		switch (msg.type)
		{
			case GET_TICKS:
				msg.RETVAL = k_ticks;
				send_recv(SEND, src, &msg);
				break;
			default:
				panic("unknown msg type");
				break;
		}
	}
}
