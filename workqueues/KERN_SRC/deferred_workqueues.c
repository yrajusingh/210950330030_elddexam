/*
 =============================================================================
 Driver Name : DEFERRED_WORKQUEUES
 Author      : Rajendra
 Version     :
 License	 : GPL
 Description : Sample driver code demonstrating the concept of Work queues.
 	 	 	   The driver loads by first creating a workqueue by calling
 	 	 	   create_singlethread_workqueue(). Next a work is created by
 	 	 	   INIT_WORK() and then the work is queued into the workqueue.
 	 	 	   The kernel finds the appropriate time and executes the work
 	 	 	   function.
 	 	 	   Finally, before the module unloads, the workqueue is destroyed
 	 	 	   by destroy_workqueue().
 =============================================================================
 */

#include"deferred_workqueues.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rajendra");

/* Create a work queue by declaring a pointer of type 'struct workqueue_struct' */
struct workqueue_struct *workqueue;

/*
 * Declare a variable of type 'struct work_struct', which specifies the parameters
 * of a particular work that has to be added to the work queue created above
 */
struct work_struct work;

/* Work Queue Function */
void wrq_func(struct work_struct *work)
{
	PINFO("Workqueue's work function executing \n");
}

static int __init deferred_workqueues_init(void)
{
	PINFO("In init() function \n");

	/* First, create a workqueue that is capable of holding the works */
	workqueue = create_singlethread_workqueue("Sample Workqueue");

	/* Initialise the work */
	INIT_WORK(&work ,wrq_func);

	/* Now push the work to the workqueue */
	queue_work(workqueue, &work);

	return 0;
}

static void __exit deferred_workqueues_exit(void)
{
	/* Destroy the workqueue created */
	destroy_workqueue(workqueue);

	PINFO("Hello World EXIT \n");
}

module_init(deferred_workqueues_init)
module_exit(deferred_workqueues_exit)
