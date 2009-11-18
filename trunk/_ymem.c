#include "_ymem.h"

static unsigned long memused=0;

unsigned long
ymemusage(void)
{
	return memused;
}

void *
ymalloc(size_t size)
{	
	void *p;
#ifdef DEBUG_MEM
	dnode_t *v;
#endif
	
	p = malloc(size+sizeof(size_t));
	if (!p) {
		yerr("malloc(%d) failed. No memory?", size);
		return NULL;
	}
	memused += size;
	*(size_t *)p = size;
#ifdef DEBUG_MEM

	if (dhead)
		dprintf("_ymalloc(%d) called[%p].[old_head:%p]", size, p, dhead->ptr);
	else
		dprintf("_ymalloc(%d) called[%p].[old_head:nil]", size, p);
	v = malloc(sizeof(dnode_t));
	v->ptr = p;
	v->size = size;
	v->next = dhead;
	dhead = v;
	dsize++;	
#endif
	return (char *)p+sizeof(size_t);
}

void 
yfree(void *p)
{
#ifdef DEBUG_MEM
	dnode_t *v;
	dnode_t *prev;
#endif
	p = (char *)p - sizeof(size_t);
	memused -= *(size_t *)p;
#ifdef DEBUG_MEM
	v = dhead;
	prev = NULL;
	while(v) {
		if (v->ptr == p) {
			if (prev)
				prev->next = v->next;
			else 				
				dhead = v->next;
			
			dprintf("_yfree(%p) called.", p);
			free(v);
			dsize--;
			break;	
		}
		prev = v;
		v = v->next;
	}
#endif
	free(p);
}