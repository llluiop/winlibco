#include "coctx.h"

bool coctx_init(Coctx* ctx)
{
	memset(ctx->reg, 0, sizeof(ctx->reg));
	return true;
}

void coctx_make(Coctx *ctx, CoRoutinePfn pfn, Coctx_param& param)
{
	char* sp = ctx->sp + ctx->size;
	sp -= sizeof(Coctx_param*); //make room for ctx_param, used for function parameter

	Coctx_param* cp = (Coctx_param*)sp;
	cp->s1 = param.s1;
	cp->s2 = param.s2;

	sp = sp - sizeof(void*); //make room for ret in stack
	

	ctx->reg[0] = pfn; //eip
	ctx->reg[7] = sp;//esp
}

__declspec(naked) void coctx_swap(Coctx * cur, Coctx * pending)
{
	__asm
	{
		lea eax, [esp+4]
		mov esp, [esp+4]
		lea esp, [esp+32]

		push eax //把cur.reg[7]作为堆栈起始进行操作，压栈等于对reg进行赋值

		push ebp
		push esi
		push edi
		push edx
		push ecx
		push ebx
		push [eax-4]


		mov esp, [eax+4] //把pending.reg[0]作为堆栈进行操作，出栈等于把reg中的值赋给寄存器

		pop eax
		pop ebx
		pop ecx
		pop edx
		pop edi
		pop esi
		pop ebp
		pop esp
		push eax

		xor eax, eax
		ret
	}

}
