/* osvm.c */
#include "osvm.h"

int8 map(opcode_t o) {
	int8 n, ret;
	im_t *p;
	
	ret = 0;
	for (n = ims, p = instrmap; n; n--, p++) {
		if (p->o == o) {
			ret = p->size;
			break;
		}
	}	
	return ret;
}

vm_t *virtual_machine() {
	vm_t *p; //vm pointer
	// program_t *pp; //program pointer
	int16 size;

	// assert((pr) && (progsz));

	size = $2 sizeof(struct s_vm);
	p = (vm_t*)malloc($i size);
	if (!p) {
		errno = ErrMem;
		return (vm_t *)0;
	}

	zero($1 p, size);
	/*	
	pp = (program_t *)malloc($i progsz);
	if (!pp) {
		free(p);
		errno = ErrMem;
		return (vm_t *)0;
	}

	copy(pp, pr, progsz);	
	*/
	return p;
}

program_t *example_program(vm_t *vm) {
	program_t *p;
	instruction_t *i1, *i2;
	args_t *a1;
	int16 s1, s2, sa1; // size of args 

	s1 = map(mov);
	s2 = map(nop);

	i1 = (instruction_t *)malloc($i s1);
	i2 = (instruction_t *)malloc($i s2);
	assert(i1 && i2);

	zero($1 i1, s1);
	zero($1 i2, s2);	
	
	i1->o = mov;
	sa1 = (s1-1);
	if (s1) {
		a1 = (args_t *)malloc($i sa1);
	}

	if (a1) {
		assert(a1);
		zero($1 a1, sa1);
		*a1 = 0x00;
		*(a1+1) = 0x05;
		// 0000 0001 mov eax
		// 0000 0000
		// 0000 0005 mov eax,0x05
	}

	p = vm->m;
	copy($1 p, $1 i1, s1);
	p++;

	if (a1) {
		copy($1 p, $1 a1, sa1); 
		p += sa1;
		free(a1);
	}

	i2->o = nop;
	copy($1 p, $1 i2, s2);

	free(i1);
	free(i2);

	return vm->m;
}

int main() {
	program_t *prog;
	vm_t *vm;

	vm = virtual_machine();
	printf("vm = %p \n", vm);

	prog = example_program(vm);
	printf("prog = %p \n", prog);

	printhex($1 prog, (map(mov) + map(nop)), ' ');

	return 0;
}
