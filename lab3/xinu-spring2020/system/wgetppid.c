/* wgetppid.c - wgetppid */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  wgetppid  -  wrapper function for syscall getppid
 *  liu1589, 2/14, lab2 5.2
 *------------------------------------------------------------------------
 */
syscall	wgetppid(
	  pid32		proc		/* Process ID			*/
	)
{
	int output;
	asm ("movl $6, %%eax\n\t" 
		 "movl %1, %%ebx\n\t"
		 "int $33\n\t"
		 "movl %%eax, %0\n\t"
		 :"=r"(output)        /* output */
		 :"r" (proc)/* input */
		 :"%eax","%ebx"      /* clobbered register */
		 );       
	return output;
}
