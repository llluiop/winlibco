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
	cp = &param;

	sp = sp - sizeof(void*); //make room for ret in stack
	

	ctx->reg[1] = pfn; //eip
	ctx->reg[2] = sp;//esp
}

__declspec(naked) void coctx_swap(Coctx * cur, Coctx * pending)
{
	__asm
	{
		//leal 4(%esp), %eax //sp 
		lea eax, [esp+4]
		//movl 4(%esp), %esp
		mov esp, [esp+4]
		//leal 32(%esp), %esp //parm a : &regs[7] + sizeof(void*)
		lea esp, [esp+32]

		push eax //esp ->parm a 

		//pushl %ebp
		push ebp
		//pushl %esi
		push esi
		//pushl %edi
		push edi
		//pushl %edx
		push edx
		//pushl %ecx
		push ecx
		//pushl %ebx
		push ebx
		//pushl -4(%eax)
		push [eax-4]


		//movl 4(%eax), %esp //parm b -> &regs[0]
		mov esp, [eax+4]

		//popl %eax  //ret func addr
		pop eax
		//popl %ebx
		pop ebx
		//popl %ecx
		pop ecx
		//popl %edx
		pop edx
		//popl %edi
		pop edi
		//popl %esi
		pop esi
		//popl %ebp
		pop ebp
		//popl %esp
		pop esp
		//pushl %eax //set ret func addr
		push eax

		//xorl %eax, %eax
		xor eax, eax
		ret
	}

}
