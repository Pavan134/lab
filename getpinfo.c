-------------------
code getpinfo.c
------------------
#include "types.h"
	#include "stat.h"
	#include "user.h"
	#include "fcntl.h"
	
	int main(void){
	  getpinfo ();
	  exit();
	}
------------------
proc.c
------------------
int
	getpinfo ()
	{
	struct proc *p;
	//Enables interrupts on this processor.
	sti();
	
	//Loop over process table looking for process with pid.
	acquire(&ptable.lock);
	cprintf("name \t pid \t state \t \n");
	for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
	  if(p->state == SLEEPING)
		  cprintf("%s \t %d \t SLEEPING \t  \n ", p->name,p->pid);
		else if(p->state == RUNNING)
	 	  cprintf("%s \t %d \t RUNNING \t \n ", p->name,p->pid);
		else if(p->state == RUNNABLE)
	 	  cprintf("%s \t %d \t RUNNABLE \t  \n ", p->name,p->pid);
	}
	release(&ptable.lock);
	return 22;
	}

----------------
sysproc.c
-----------------
int
	sys_getpinfo(void)
	{
	  return getpinfo();
	}
