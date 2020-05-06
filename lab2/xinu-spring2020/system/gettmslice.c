/* gettmslice.c - gettmslice */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  gettmslice  -  get the remaining time in a timeslice of a process
 *  liu1589, 2/14, lab2 4(b)
 *------------------------------------------------------------------------
 */
 uint32	gettmslice(void)
{
	uint32 tmslice;
	intmask	mask;			/* Saved interrupt mask		*/
	mask = disable();		/*Disable Interrupt*/
    tmslice = preempt;
	restore(mask);
	return tmslice;
}