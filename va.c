#include <stdio.h>
#include <stdarg.h>

void
foo(char *fmt, ...)
{
	va_list ap;
	int d, c;
	char *s;
	double f;

	va_start(ap, fmt);
	while (*fmt)
	   switch (*fmt++) {
	   case 's':                       /* string */
		   s = va_arg(ap, char *);
		   printf("string %s\n", s);
		   break;
	   case 'd':                       /* int */
		   d = va_arg(ap, int);
		   printf("int %d\n", d);
		   break;
	   case 'c':                       /* char */
		   c = va_arg(ap, int);    /* promoted */
		   printf("char %c\n", c);
		   break;
	   case 'f':                       /* float */
		   f = va_arg(ap, double); /* promoted */
		   printf("float %f\n", f);
	   }
	va_end(ap);
}

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

}

int
main()
{
	printf("hey!\n");
	f1(2, "v1..", "v2..");
	return 0;
}
