/* memList.c - meminsert,memextract liu1589, lab5 part 4*/

#include <xinu.h>


/*------------------------------------------------------------------------
 *  meminsert  -  insert a inuse memblk into per process memList
 *------------------------------------------------------------------------
*/

void meminsert(
	struct inusememblk *hdptr, 
	char *memptr	/*memblockptr*/
){
	struct inusememblk *memblk = (struct inusememblk *)getmem(sizeof(struct inusememblk));    //getmem2; allocate inusememblk
	memblk->memblockptr = memptr;
	memblk->memlen = 512;
	/*Insert memblk to process inusememblk list*/
	struct inusememblk *curr = hdptr;
	struct inusememblk *prev = NULL;
	
	if (curr == NULL){	//if inusememblk list is empty
		if (XINUDEBUG == 1){
			kprintf("list is empty: inserting first node\n");
		}
		memblk->mnext = NULL;
		struct procent *prptr = &proctab[currpid];
		prptr->prheaphd = memblk;
		return;
	}
	if (XINUDEBUG == 1){
		kprintf("list has elements: inserting a new node\n");
	}
	while (curr != NULL && curr->memblockptr < memptr) {
		prev = curr;
		curr = curr->mnext;
	}
	
	prev->mnext = memblk;
	memblk->mnext = curr;
	return;
}
 
 
/*------------------------------------------------------------------------
 *  memextract  -  extract a inuse memblk into per process memList
 *------------------------------------------------------------------------
*/
void memextract(
	struct inusememblk *hdptr, 
	char *memptr 	/*memblockptr*/
	){
	struct inusememblk *curr = hdptr;
	struct inusememblk *prev = hdptr;
	
	if (curr->mnext == NULL){	//if the only item on the list
		if (XINUDEBUG == 1){kprintf("last item in list: free and set prheaphd to NULL\n");}
		
		//free struct list entry from memory
		freemem((char *)curr,sizeof (struct inusememblk));
		
		//reset prheaphd to NULL
		struct procent *prptr = &proctab[currpid];
		prptr->prheaphd = NULL;
	}
	
	while (curr != NULL && curr->memblockptr != memptr) {
		prev = curr;
		curr = curr->mnext;
	}
	
	if (curr != NULL){
		
		if (prev == curr){	//if the first item in the list to be removed
			//make second item the head
			if (XINUDEBUG == 1){kprintf("first item in list, make second item the head\n");}
			struct procent *prptr = &proctab[currpid];
			prptr->prheaphd = curr->mnext;
		}else{
			//extract curr from list
			if (XINUDEBUG == 1){kprintf("remove item in the middle of list\n");}
			prev->mnext = curr->mnext;
		}
		
		
		//free struct list entry from memory
		freemem((char *)curr,sizeof (struct inusememblk));	
	}else{
		//kprintf("item not found in the list\n");
	}
	
	return;
}

void printMemblkList(bool8 calledByInsert){
	if (calledByInsert == TRUE){
		kprintf("After meminsert: ");
	}else{
		kprintf("After memextract: ");
	}
	struct procent *prptr = &proctab[currpid];
	struct inusememblk *curr = prptr->prheaphd;
	int i = 0;
	while (curr != NULL) {
		i++;
		curr = curr->mnext;
	}
	kprintf("There are %d inusememblk in the list\n",i);
}