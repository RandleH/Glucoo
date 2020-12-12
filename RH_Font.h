#ifndef _RH_FONT_H
#define _RH_FONT_H 

struct __FontChar_t{
	unsigned char        c;
	unsigned int         height;
	unsigned int         width;
	const unsigned char* byte;
	struct __FontChar_t* next;
};

typedef struct __FontChar_t  __FontChar_t;

#endif

