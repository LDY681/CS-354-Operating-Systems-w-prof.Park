/* cbregister.c - cbregister, cbunregister */

#include <xinu.h>

umsg32 ubuffer = 0;	//define ubuffer

/*------------------------------------------------------------------------
 *  cbregister  -  register callback function
 *	liu1589, lab5.3, 4.14
 *------------------------------------------------------------------------
 */
 syscall cbregister(
	void (* fp)(void) 	/* function pointer to a user callback function */
	,umsg32 *mbufptr	/* pointer to a 1-word message buffer */
	)
{
	intmask mask;
	mask = disable();
	struct procent	*prptr = &proctab[currpid];
	
	if (XINUDEBUG == 1){
		kprintf("The text segment boundary is: [0x%08X to 0x%08X]\n",(uint32)&text, (uint32)&etext - 1);
		kprintf("addr of fp is: 0x%08X & addr of mbufptr is 0x%08X\n",(uint32)fp, (uint32)mbufptr);
	}
	/* If fp does not lie in the address boundary of the text segment
	and/or mbufptr points inside the text segment */
	if ( (uint32)fp < (uint32)&text || (uint32)fp > (uint32)&etext - 1 || ((uint32)mbufptr < (uint32)&etext - 1 && (uint32)mbufptr > (uint32)&text) ){
		kprintf("fp and doesn't lie in their boundaries!\n");
		restore(mask);
		return SYSERR;
	}
	
	//When a process tries to register a second callback function
	if (prptr->prcbvalid == TRUE) {
		restore(mask);
		return SYSERR;
	}

	//Set cbvalid to true and set callback function pointer
	prptr->prcbvalid = TRUE;
	prptr->prcbptr = fp;

	//TODO: what about umsg32 *mbufptr?
	prptr->prmbufptr = mbufptr;
	
	restore(mask);
	return OK;
}

/*------------------------------------------------------------------------
 *  cbunregister  -  unregister callback function
 *	liu1589, lab5.3, 4.15
 *------------------------------------------------------------------------
 */
syscall cbunregister(void){
	intmask mask;
	mask = disable();
	struct procent	*prptr = &proctab[currpid];
	
	//If there was no registered callback function
	if (prptr->prcbvalid == FALSE) {
		restore(mask);
		return SYSERR;
	}
	prptr->prcbvalid = FALSE;
	restore(mask);
	return OK;
}

/*------------------------------------------------------------------------
 *  usercb  -  The callback function to be executed
 *	liu1589, lab5.3, 4.15
 *------------------------------------------------------------------------
 */
void usercb(void) {
	extern umsg32 ubuffer;
	kprintf("usercb: callback message is %d\n", ubuffer);
	return;
}