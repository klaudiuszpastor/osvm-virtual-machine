#pragma once
#include <stdio.h>

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;
typedef unsigned long long int int64;

#define $1 (int8 *)
#define $2 (int16)
#define $3 (int32)
#define $4 (int64)
#define $c (char *)
#define $i (int)


void copy(int8 *dst, int8 *src, int16 size); 
void zero(int8 *dst, int16 size);
void printhex(int8 *p, int16 size, int8 delim);

