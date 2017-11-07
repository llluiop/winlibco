#pragma once
#include "libco.h"




typedef void(*CoRoutinePfn)(Coctx*);

bool coctx_init(Coctx*);
void coctx_make(Coctx*, CoRoutinePfn pfn, Coctx_param& param);
void coctx_swap(Coctx* cur, Coctx* pending);