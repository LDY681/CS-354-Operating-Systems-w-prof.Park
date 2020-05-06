/*  mymotd.c  - mymotd */

#include <xinu.h>

/*print my own welcome messge before calling main*/
syscall mymotd(void){
	if (XINUTEST == 1){
		kprintf("\nHello From liu1589, Dayu Liu\n");
	}
	return OK;
}