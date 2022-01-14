Readme - Semaphore
==================

Concept
-------
	"Go to sleep" is a well-defined term in this context. When a linux process reaches a point where it
cannot make any further progress, it goes to sleep(or blocks), yielding the processor to somebody else
until sometime in the future when it can get work done again. Not all locking mechanisms can be used where
sleeping is a possibility. The mechanism that fits best is a semaphore.
	At its core, a semaphore is a single integer value combined with a pair of functions that are typically
called P and V. A process wishing to enter a critical section will call P on the relevant semaphore; if the
semaphore's value is greater than zero, that value is decremented by one and the process continues. If,
instead, the semaphore's value is 0(or less), the process must wait until somebody else releases the semaphore.
Unlocking a semaphore is accomplished by calling V; this function increments the value of the semaphore
and, if necessary, wakes up process that are waiting.
	When semaphores are used for mutual exclusion, i.e., keeping multiple processes from running within a
critical section simultaneously - their value will be initially set to 1. Such a semaphore can be held only
by a single process or thread at any given time. A semaphore used in this mode is sometimes called a mutex, which
is, of course, an abbreviation for 'mutual exclusion'.

Syntax & Semantics
------------------
	Semaphores are built upon 'struct semaphore', present in <linux/semaphore.h>. Initially, create a variable
of this type and then follow on with the operations :
	struct semaphore sample_sem;
	
	The first thing after defining a variable is that, you need to initialise it :
	sema_init(&sample_sem, 1);
	
	The first argument is the associated semaphore variable and the second argument is the initial value that is
to be setup, well in this case 1, which means that we are initialising the semaphore in a unlocked state.

	Now the semaphores can be acquired and released as such :
	down_interruptible(&sample_sem);
	
	/* Critical section */
	
	up(&sample_sem); 
	
	There are other APIs for use, such as :
	void down(struct semaphore *sem);
		The above function decrements the value of the semaphore and waits as long as need be. 'down_interruptible',
which we have used does the same, but the operation is interruptible. The interruptible version is almost
always the one you want; it allows a user-space process that is waiting on a semaphore to be interrupted by the user.
Non-interruptible operations are good way to create unkillable processes. Using 'down_interruptible' require some
extra care, however, if the operation is interrupted, the function returns a nonzero value and the caller
does not hold the semaphore. Hence proper use of 'down_interruptible' requires always checking the return value and
responding accordingly.	
		
	int down_trylock(struct semaphore *sem);
 		The function never sleeps; if the semaphore is not available at the time of the call, 'down_trylock'
returns imediately with a nonzero return value.
