#include "osutils.h"

void copy(int8 *dst, int8 *src, int16 size) {
	int8 *d, *s;
	int16 n;

	for (n = size, d = dst, s = src; n; n--, d++, s++)
		*d = *s;
	return;
}	

void zero(int8 *dst, int16 size) {
	int8 *p;
	int16 n;

	for (n = 0, p = dst; n < size; n++, p++)
		*p = 0;
	return;
}

void printhex(int8 *str, int16 size, int8 delim) {
	int16 n;
	int8 *p;

	for (n = size, p = str; n; n--, p++) {
		printf("%.02x", *p);
		if (delim && n)
			printf("%c", delim);
		fflush(stdout);
	}
	printf("\n");
	return;
}
