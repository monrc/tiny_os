

#ifndef _OS_STUDIO_H_
#define _OS_STUDIO_H_

#include "type.h"

/* EXTERN */
#define EXTERN extern /* EXTERN is defined as extern except in global.c */

/* string */
#define STR_DEFAULT_LEN 1024

#define O_CREAT 1
#define O_RDWR	2

#define SEEK_SET 1
#define SEEK_CUR 2
#define SEEK_END 3

#define MAX_PATH 128

/*--------*/
/* ¿âº¯Êý */
/*--------*/

/* lib/open.c */
PUBLIC int open(const char *pathname, int flags);

/* lib/close.c */
PUBLIC int close(int fd);


#endif
