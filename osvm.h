/* osvm.h */
#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <errno.h>
#include "osutils.h"

#define ErrMem	0x01
#define NoArgs	{ 0x00, 0x00}

/* 
	16 bits vm
		AX
		BX
		CX
		DX
		SP - stack pointer
		IP - instruction pointer
	65 KB of memory
	Serial COM port
	Floppy drive
*/

typedef unsigned short int reg_t;
typedef int8 args_t;
typedef int8 stack_t[((unsigned int)(-1))];

struct s_registers {
	reg_t ax;
	reg_t bx;
	reg_t cx;
	reg_t dx;
	reg_t sp;
	reg_t ip;
};
typedef struct s_registers registers_t;

struct s_cpu {
	registers_t r;
};
typedef struct s_cpu cpu_t; 

enum e_opcode {
	mov = 0x01,
	nop = 0x02
};
typedef enum e_opcode opcode_t;

struct s_instruction {
	opcode_t o;
	args_t a[]; /* 0-2  bytes*/
};
typedef struct s_instruction *instruction_t; 
typedef instruction_t program_t; //program_t is sequence of instructions

struct s_instrmap {
	opcode_t o;
	int8 size;
};
typedef struct s_instrmap im_t;

struct s_vm {
	cpu_t c;
	stack_t *s;
	program_t *p;
};
typedef struct s_vm vm_t;

static im_t instrmap[]= {
	{ mov, 0x05 },
	{ nop, 0x01 }
};
#define ims (sizeof(instrmap) / sizeof(struct s_instrmap))

	program_t example_program(void);
int8 map(opcode_t);
vm_t *virtual_machine(program_t,int16);
int main(int, char**);
