

#ifndef _OS_STRING_H_
#define _OS_STRING_H_

#include "type.h"

PUBLIC void *memcpy(void *p_dst, void *p_src, int size);
PUBLIC void memset(void *p_dst, char ch, int size);
PUBLIC char *strcpy(char *p_dst, char *p_src);
int strlen(char *p_str);

#endif