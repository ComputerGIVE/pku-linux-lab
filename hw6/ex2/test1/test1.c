#include <stdio.h>

int main()
{
	int a = 1;
	int b = 2;
	printf("[User] Warning! Here is an illegal instruction!\n"); 
	asm("nop");
	printf("[User] Yeah! I have jumped over it!\n"); 
	b = 3; 
	printf("[User] Oh f**k! One after another!\n"); 
	asm("nop");
	asm("nop");
	printf("[User] Hmm...\n"); 
	printf("[User] Goodbye!\n"); 
	return 0;
}
