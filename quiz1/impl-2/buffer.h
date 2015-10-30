#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <linux/string.h>
#define STR_SIZE 200
#define BUFFER_SIZE 1024

struct buffer {
	int tail; 
	char data[BUFFER_SIZE][STR_SIZE]; 
}; 

inline void INIT_BUFFER(struct buffer *buf)
{
	buf->tail = -1; 
}

inline int buffer_empty(const struct buffer *buf)
{
	return (buf->tail >= 0); 
}

inline void buffer_add(struct buffer *buf, const char *s){
	buf->tail++;
	strcpy(buf->data[buf->tail], s); 
}

#define buffer_clear(buf) (INIT_BUFFER(buf))

#define foreach_buffer(i, chptr, buf) \
	for (chptr = (char *) buf->data, i = 0;       \
	     i <= buf->tail; 				\
	     chptr = buf->data[++i])

#endif
