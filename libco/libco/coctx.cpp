#include "coctx.h"

bool coctx_init(Coctx* ctx)
{
	memset(ctx->reg, 0, sizeof(ctx->reg));
}

void coctx_make(Coctx *ctx, CoRoutinePfn pfn, Coctx_param& param)
{
	char* sp = ctx->sp + ctx->size;
	sp -= sizeof(Coctx_param*); //make room for ctx_param, used for function parameter

	Coctx_param* cp = (Coctx_param*)sp;
	cp = &param;

	sp = sp - sizeof(void*); //make room for ret in stack
	

	ctx->reg[1] = pfn; //eip
	ctx->reg[2] = sp;//esp
}

__declspec(naked) void coctx_swap(Coctx * cur, Coctx * pending)
{
	__asm
	{
		leal 4(%esp), %eax //sp 
		movl 4(%esp), %esp
		leal 32(%esp), %esp //parm a : &regs[7] + sizeof(void*)

		pushl %eax //esp ->parm a 

		pushl %ebp
		pushl %esi
		pushl %edi
		pushl %edx
		pushl %ecx
		pushl %ebx
		pushl - 4(%eax)


		movl 4(%eax), %esp //parm b -> &regs[0]

		popl %eax  //ret func addr
		popl %ebx
		popl %ecx
		popl %edx
		popl %edi
		popl %esi
		popl %ebp
		popl %esp
		pushl %eax //set ret func addr

		xorl %eax, %eax
		ret
	}

}
