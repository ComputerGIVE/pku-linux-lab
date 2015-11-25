#include <stdio.h>

int main()
{
	long long a = 0x400921fb4d12d84a; 
	double b = *((double*) &a); 
	printf("%lf\n", b);
}
