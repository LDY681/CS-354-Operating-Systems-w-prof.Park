/* wgetprio.c - wgetpid */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  wgetprio  -  wrapper function for syscall getprio
 *  liu1589, 2/14, lab2 5.2
 *------------------------------------------------------------------------
 */
syscall wgetprio(pid32 proc)
{
	int output;
	asm ("movl $5, %%eax\n\t" 
		 "movl %1, %%ebx\n\t"
		 "int $33\n\t"
		 "movl %%eax, %0\n\t"
		 :"=r"(output)        /* output */
		 :"r" (proc)/* input */
		 :"%eax","%ebx"      /* clobbered register */
		 );       
	return output;
}