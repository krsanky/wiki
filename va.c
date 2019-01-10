#include <stdio.h>
#include <stdarg.h>

void
f1(int n, ...)
{
	char		*v;
	va_list ap;
	va_start(ap, n);

	for (int i=0; i<n; i++) {
		v = va_arg(ap, char *);
		printf("%d %s\n", i, v);
	}

	va_end(ap);
}

int
main()
{
	printf("hey!\n");
	f1(2, "v1..", "v2..");
	return 0;
}
