/* clock.h */

/* Intel 8254-2 clock chip constants */

#define	CLOCKBASE	0x40		/* I/O base port of clock chip	*/
#define	CLOCK0		CLOCKBASE
#define	CLKCNTL		(CLOCKBASE+3)	/* chip CSW I/O port		*/


#define CLKTICKS_PER_SEC  1000	/* clock timer resolution		*/

extern	uint32	clktime;	/* current time in secs since boot	*/
extern	uint32 clktimemilli;	/* time in ms since boot, liu1589,2/23,lab3.1*/
extern	qid16	sleepq;		/* queue for sleeping processes		*/
extern	uint32	preempt;	/* preemption counter			*/
