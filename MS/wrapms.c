#include <sys/mman.h>
#include "msxxd.c"
#define MSOFFSET 0x00

int main(){
	mprotect( (void*)( ((unsigned long long int)&(MS[0x00])) & 0xfffffffff000),  MS_len, PROT_READ|PROT_WRITE|PROT_EXEC);
	void *shellcode = (void*)( MSOFFSET+(unsigned long long int)&(MS[0x00] ) );
	return (( int(*)(void) ) ( shellcode )) ();
}
