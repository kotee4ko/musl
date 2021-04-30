MUSL Shell

This is recepie how to write static & pie hellcodes on GNU C with (MUSL) LIBC. 
Goal of project: escape to use asm on large shellcodes, and just training my skills.

Howto: git clone && cd MUSLShell && ./make.sh

after that you should see folder MS
cd ./MS && start playing :)


sample output:
```
lol kek 31337 p0x3k
uid=0(root) gid=0(root) groups=0(root)
MS  kopycatim.lds  libmc.a  ms.c  msmake.sh  msxxd.c  shellms.c  wrapms  wrapms.c
mypid 3609952
fd = 3
#include <sys/mman.h>
#include "msxxd.c"
#define MSOFFSET 0x00

int main(){
	mprotect( (void*)( ((unsigned long long int)&(MS[0x00])) & 0xfffffffff000),  MS_len, PROT_READ|PROT_WRITE|PROT_EXEC);
	void *shellcode = (void*)( MSOFFSET+(unsigned long long int)&(MS[0x00] ) );
	return (( int(*)(void) ) ( shellcode )) ();
}
chunk 0x7f33ad051000
WIN
So, as u can see - this is code, which was compiled via GCC, linked with MUSL (and some black magic),
and after that -- hexdumped into the raw shell form.
Wrapper - just emulate situation, in which we are using shellcode: making mem rwx, then call to start of the shellcode
Pay attention at W bit - since we working with data in our muslshell - we *MUST* be able to write to the mem, not only eXec
And one more thing: idk why, but stdin/stdout/stderr don't work correctly, to work around I use dprintf(0x01, ... )
instead of printf(...), and so on...
Btw, 'volatile' attribute used not only for songs, it tell gcc that this varible can be chandged suddenly from outside.
Also, musl don't like to free() chunks after malloc. I'm too lazy to research why. As for me - this is enougf for shell.Stay tunde :3
556884f47000-556884f48000 r--p 00000000 fe:01 14273896                   /opt/wokr/l1nux/MUSLSHELL/MS/wrapms
556884f48000-556884f49000 r-xp 00001000 fe:01 14273896                   /opt/wokr/l1nux/MUSLSHELL/MS/wrapms
556884f49000-556884f4a000 r--p 00002000 fe:01 14273896                   /opt/wokr/l1nux/MUSLSHELL/MS/wrapms
556884f4a000-556884f4b000 r--p 00002000 fe:01 14273896                   /opt/wokr/l1nux/MUSLSHELL/MS/wrapms
556884f4b000-556884f51000 rwxp 00003000 fe:01 14273896                   /opt/wokr/l1nux/MUSLSHELL/MS/wrapms
7f33ace24000-7f33ace49000 r--p 00000000 fe:01 5011270                    /usr/lib/x86_64-linux-gnu/libc-2.31.so
7f33ace49000-7f33acf94000 r-xp 00025000 fe:01 5011270                    /usr/lib/x86_64-linux-gnu/libc-2.31.so
7f33acf94000-7f33acfde000 r--p 00170000 fe:01 5011270                    /usr/lib/x86_64-linux-gnu/libc-2.31.so
7f33acfde000-7f33acfdf000 ---p 001ba000 fe:01 5011270                    /usr/lib/x86_64-linux-gnu/libc-2.31.so
7f33acfdf000-7f33acfe2000 r--p 001ba000 fe:01 5011270                    /usr/lib/x86_64-linux-gnu/libc-2.31.so
7f33acfe2000-7f33acfe5000 rw-p 001bd000 fe:01 5011270                    /usr/lib/x86_64-linux-gnu/libc-2.31.so
7f33acfe5000-7f33acfeb000 rw-p 00000000 00:00 0 
7f33ad028000-7f33ad029000 r--p 00000000 fe:01 5011262                    /usr/lib/x86_64-linux-gnu/ld-2.31.so
7f33ad029000-7f33ad049000 r-xp 00001000 fe:01 5011262                    /usr/lib/x86_64-linux-gnu/ld-2.31.so
7f33ad049000-7f33ad051000 r--p 00021000 fe:01 5011262                    /usr/lib/x86_64-linux-gnu/ld-2.31.so
7f33ad052000-7f33ad053000 r--p 00029000 fe:01 5011262                    /usr/lib/x86_64-linux-gnu/ld-2.31.so
7f33ad053000-7f33ad054000 rw-p 0002a000 fe:01 5011262                    /usr/lib/x86_64-linux-gnu/ld-2.31.so
7f33ad054000-7f33ad055000 rw-p 00000000 00:00 0 
7ffdfdf3a000-7ffdfdf5b000 rw-p 00000000 00:00 0                          [stack]
7ffdfdf86000-7ffdfdf8a000 r--p 00000000 00:00 0                          [vvar]
7ffdfdf8a000-7ffdfdf8c000 r-xp 00000000 00:00 0                          [vdso]
f_size = 32048
fread = 32048
ELF
```
