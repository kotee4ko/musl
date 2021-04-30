#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <malloc.h>
#include <sys/stat.h>
#include <sys/types.h>

#define DBGHB		0x00
#define RETURNED 	0x00
#define u_int64_t	unsigned long long int
typedef u_int64_t	volatile (*func)(void *, ...);
__asm__ ("jmp main;	\n\t");	//ninja
#if DBGHB > 0x00
# define HB __asm__ volatile ("int 3")
#else
# define HB do{;}while(0x00)
#endif
#define handle_error(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while (0)
size_t len = 0x00;

u_int64_t
main(void);
func _start(){
	__asm__("jmp [rip];\n\n"); //super anti debug technique
}

size_t f_size(FILE *f){
        size_t ret = 0x00;
	struct stat sb;
	HB;
	fstat(fileno(f), &sb);
	return sb.st_size;

        //lseek(f->_fileno, 0, SEEK_END); //libc got _fileno, but musl got nothing
        //ret = ftell(f);
        //lseek(f->_fileno, 0, SEEK_SET);
        //return ret;
}


u_int64_t main(void){
	int pid = 0x00, fd = 0x00;
	char *ptr = NULL;
	char cmd[0xff] = { 0x00 };
	FILE *f = NULL;
	volatile char *_31337_=&("lol kek 31337 p0x3k\n"[0x00]);

	HB;
	mprotect( (void*)((u_int64_t)((u_int64_t)&(_31337_[0x00]))&0xfffffffff000),  0x8b000, PROT_READ|PROT_WRITE|PROT_EXEC);
	HB;

	write(0x01, (const void *)_31337_, strlen((const void *)_31337_));
	sleep(1);
	system("id; ls");
	pid = getpid();
	dprintf(0x01, "mypid %d\n", pid);

	fd = open("./wrapms.c", 'r');
	if ( fd <= 0x00 )
		return -1;
	dprintf(0x01, "fd = %d\n", fd);
	ptr = (char*)mmap(0x00, 0x1000, PROT_EXEC|PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0x00);
	dprintf(0x01, "%s", ptr);
	if ( ptr == ((void*)-1) )
		handle_error("mmap");
	dprintf(0x01, "chunk %p\n", ptr);
	close(fd);
	write(0x01, "WIN\n", 0x04);
	dprintf(0x01, "So, as u can see - this is code, which was compiled via GCC, linked with MUSL (and some black magic),\n"
		"and after that -- hexdumped into the raw shell form.\n"
		"Wrapper - just emulate situation, in which we are using shellcode: making mem rwx, then call to start of the shellcode\n"
		"Pay attention at W bit - since we working with data in our muslshell - we *MUST* be able to write to the mem, not only eXec\n"
		"And one more thing: idk why, but stdin/stdout/stderr don't work correctly, to work around I use dprintf(0x01, ... )\n"
		"instead of printf(...), and so on...\n"
		"Btw, 'volatile' attribute used not only for songs, it tell gcc that this varible can be chandged suddenly from outside.\n"
		"Also, musl don't like to free() chunks after malloc. I'm too lazy to research why. As for me - this is enougf for shell."

		"Stay tunde :3\n"
	);
	munmap(ptr, 0x1000);

	sprintf(cmd, "cat /proc/%d/maps", getpid());
	system(cmd);

	f = fopen("./MS", "r");
	if ( !f )
		handle_error("fopen");
	ptr = (char*)malloc(f_size(f));
	if ( !ptr )
		handle_error("malloc");

	dprintf(0x01, "f_size = %d\n", f_size(f));

	len = fread(ptr, 0x01, f_size(f), f);

	dprintf(0x01, "fread = %d\n", len);
	dprintf(0x01, "%s\n", ptr);

//	dprintf(0x01, "chunk ptr = %p\n", ptr); //also, musl don't like to free() chunks after malloc.
//	if ( ptr ) free ( ptr );

#if RETURNED == 0x01
	return 0xd34db33fc4f3f33d;
#else
	_exit(0x00);
#endif
}
