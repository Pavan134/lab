Step-1: Syscall.h
$ nano syscall.h
#define SYS_backtrace 23
Step 2: Syscall.c
$ nano syscall.c extern int
sys_backtrace(void);
[SYS_backtrace]
sys_backtrace,
Step 3: Sysproc.c $
nano sysproc.c
int
sys_backtrace(void
)
{
 //struct proc *curproc = myproc(); uint
ebp, ret_addr, next_addr; int count = 0;
struct trapframe *tf = myproc()->tf;
cprintf("eax : 0x%x\n", tf->eax);
cprintf("ebx : 0x%x\n", tf->ebx);
cprintf("ecx : 0x%x\n", tf->ecx); cprintf("edx
: 0x%x\n", tf->edx); cprintf("edi : 0x%x\n",
tf->edi); cprintf("esi : 0x%x\n", tf->esi);
cprintf("esp : 0x%x\n", tf->esp);
cprintf("ebp : 0x%x\n", tf->ebp);
cprintf("eip : 0x%x\n", tf->eip); ebp = tf-
>ebp; next_addr = tf->eip;
while(next_addr && next_addr != (uint)-1) {
ret_addr = *(uint *) (ebp + 4);
cprintf("#%d 0x%x\n", count++, ret_addr);
ebp = *(uint *)ebp; next_addr = ret_addr;
 }
 return 0;
}
Step 4: Usys.S
$ nano usys.s
SYSCALL(backtrace
) Step 5: User.h
$ nano user.h int
backtrace(void);
Step 6: defs.h
$ nano defs.h
int backtrace(void);
Step 7: bt.c
$ nano bt.c
#include "types.h"
#include "stat.h" #include
"user.h" int baz()
__attribute__((noinline)); int
baz() { int a; a = backtrace();
return a + uptime();
}
int bar()
__attribute__((noinline)); int
bar() { int b; b = baz(); return
b + uptime();
}
int foo()
__attribute__((noinline)); int
foo() { int c; c = bar(); return c +
uptime();
} int main(int argc, char
*argv[])
{
foo();
exit();
}
Step 8: Makefile
$ nano Makefile
UPROGS: _bt\
EXTRAS: bt