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

vm_t *virtual_machine(program_t pr, int16 progsz) {
	vm_t *p; //vm pointer
	program_t pp; //program pointer
	int16 size;

	assert((pr) && (progsz));

	size = $2 sizeof(struct s_vm);
	p = (vm_t*)malloc($i size);
	if (!p) {
		errno = ErrMem;
		return (vm_t *)0;
	}
	
	zero($1 p, size);

	pp = (program_t)malloc($i progsz);
	if (!pp) {
		free(p);
		errno = ErrMem;
		return (vm_t *)0;
	}

	copy($1 pp,$1 pr, progsz);	
	return p;
}

program_t example_program() {
	int16 size;
	instruction_t i1, i2;
	
	size = map(mov);
	i1 = (instruction_t)malloc($i size); 
	if (!i1) {
		errno = ErrMem;
		return (program_t)0;
	}
	
	size = map(nop);
	i2 = (instruction_t)malloc($i size); 
	if (!i2) {
		errno = ErrMem;
		return (program_t)0;
	}

	program_t prog = {i1, i2};
	
	return prog;
}

int main(int argc, char *argv[]) {
	int8 size;
	program_t prog;
	vm_t *vm;

	size = (map(mov) + map(nop));
	prog = example_program();
	printf("prog = %p \n", prog);

	vm = virtual_machine(prog, size);
	printf("vm = %p \n", vm);

	return 0;
}
