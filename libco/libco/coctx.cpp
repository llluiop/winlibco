#include "coctx.h"

bool coctx_init(Coctx* ctx)
{
	memset(ctx->reg, 0, sizeof(ctx->reg));
}

void coctx_make(Coctx *ctx, CoRoutinePfn pfn, Coctx_param* param)
{
	char* sp = ctx->sp + ctx->size;
	sp -= sizeof(Coctx_param*); //make room for ctx_param, used for function parameter

	Coctx_param* cp = (Coctx_param*)sp;
	cp = param;

	sp = sp - sizeof(void*); //make room for ret in stack
	

	ctx->reg[1] = pfn; //eip
	ctx->reg[2] = sp;//esp
}
