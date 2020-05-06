/* testcpu.c - testcpu */

#include <xinu.h>
/*------------------------------------------------------------------------
 *  testcpu  -  testcpu liu1589, lab3 part5
 *------------------------------------------------------------------------
 */
void	testcpu()
{
int x, y;
x = 0;
y = clktimemilli;
while(clktimemilli - y < 8000){ // until wall clock time of 8 sec is reached do
   x++;
}
kprintf("cpu: %d %d %d %d\n", currpid, x, proctab[currpid].prgrosscpu, procgrosscpumicro(currpid));
}


