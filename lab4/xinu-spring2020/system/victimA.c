/*  victimA.c  - victimA */

#include <xinu.h>

void victimA(void) {
  int x;

  x = 5;
  kprintf("before funcA: %d %d\n", getpid(), x);
  sleepms(300);
  kprintf("after funcA: %d %d\n", getpid(), x);
}