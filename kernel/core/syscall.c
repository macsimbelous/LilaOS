#include<stdlib.h>

int test_sys_call(unsigned int edi, unsigned int esi, unsigned int ebx, unsigned int edx, unsigned int ecx){
	printf("Test System Call\nRegisters: ECX=%u EDX=%u EBX=%u ESI=%u EDI=%u", ecx, edx, ebx, esi, edi);
	return edi;
}
