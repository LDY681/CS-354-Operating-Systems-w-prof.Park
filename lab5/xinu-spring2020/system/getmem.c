/* getmem.c - getmem */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  getmem  -  Allocate heap storage, returning lowest word address
 *------------------------------------------------------------------------
 */
bool8  getflag = 0;
char  	*getmem(
	  uint32	nbytes		/* Size of memory requested	*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	memblk	*prev, *curr, *leftover;

	mask = disable();
	if (nbytes == 0) {
		restore(mask);
		return (char *)SYSERR;
	}

	nbytes = (uint32) roundmb(nbytes);	/* Use memblk multiples	*/

	prev = &memlist;
	curr = memlist.mnext;
	while (curr != NULL) {			/* Search free list	*/

		if (curr->mlength == nbytes) {	/* Block is exact match	*/
			prev->mnext = curr->mnext;
			memlist.mlength -= nbytes;
			
			/*If getmem is not called by meminsert, the outer getmem()*/
			if (getflag == 0){
				struct procent *prptr = &proctab[currpid];
				getflag = 1;	//set to 1 so when meminsert calls getmem() internally, it won't trap into infinite loop
				meminsert(prptr->prheaphd,(char *)(curr));
				getflag = 0;
			}
			
			restore(mask);
			return (char *)(curr);

		} else if (curr->mlength > nbytes) { /* Split big block	*/
			leftover = (struct memblk *)((uint32) curr +
					nbytes);
			prev->mnext = leftover;
			leftover->mnext = curr->mnext;
			leftover->mlength = curr->mlength - nbytes;
			memlist.mlength -= nbytes;
			
			/*If getmem is not called by meminsert, the outer getmem()*/
			if (getflag == 0){
				struct procent *prptr = &proctab[currpid];
				getflag = 1;	//set to 1 so when meminsert calls getmem() internally, it won't trap into infinite loop
				meminsert(prptr->prheaphd,(char *)(curr));
				getflag = 0;
			}
			
			restore(mask);
			return (char *)(curr);
		} else {			/* Move to next block	*/
			prev = curr;
			curr = curr->mnext;
		}
	}
	restore(mask);
	return (char *)SYSERR;
}
