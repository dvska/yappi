#ifndef YCALLSTACK_H
#define YCALLSTACK_H

#include "_yhashtab.h"

typedef struct {
    long long t0;
    void *ckey;
} _cstackitem;

typedef struct {
    int head;
    int size;
    _cstackitem *_items;
    _htab *_counts;	// holds the number of same items in the cs.
} _cstack;

_cstack *screate(int size);
void sdestroy(_cstack * cs);
_cstackitem * spush(_cstack *cs, void *ckey);
_cstackitem *spop(_cstack * cs);
int slen(_cstack *cs);
_cstackitem * shead(_cstack * cs);
int scount(_cstack * cs, void *ckey);

#endif
