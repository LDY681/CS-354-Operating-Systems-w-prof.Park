/* wgetpid.c - wgetpid */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  wgetpid  -  wrapper function for syscall getpid
 *  liu1589, 2/14, lab2 5.2
 *------------------------------------------------------------------------
 */
 pid32	wgetpid()
{
	int output;
	asm ("movl $4, %%eax\n\t" 
		 "int $33\n\t"
		 "movl %%eax, %0\n\t"
		 :"=r"(output)        /* output */
		 :/* input */
		 :"%eax"         /* clobbered register */
		 );       
	return output;
}