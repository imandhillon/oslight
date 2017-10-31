#include <types.h>
#include <lib.h>
#include <thread.h>
#include <synch.h>
#include <test.h>

//int jointest(int, char **);

int jointest(int nargs, char **args)
{
    kprintf("jointest");
    struct proc *proc;
	int result;

	/* Create a process for the new program to run in. */
	proc = proc_create_runprogram(args[0] /* name */);
	if (proc == NULL) {
		return ENOMEM;
    }
    
    int i=0;
    for(i;i<20;i++)
    {
        result = thread_fork(args[0] /* thread name */,
                proc /* new process */,
                cmd_progthread /* thread function */,
                args /* thread arg */, nargs /* thread arg */);
        if (result) {
            kprintf("thread_fork failed: %s\n", strerror(result));
            proc_destroy(proc);
            return result;
	    }
    }

    thread_join(args[0],result);
    return result;
}