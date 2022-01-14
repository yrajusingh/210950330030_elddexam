Readme - Workqueues
===================

Concept
-------
	Workqueues have one or more dedicated processed("kernel threads"), which run functions submitted
to the queue. Workqueues are, superficially, similar to tasklets; they allow kernel code to request
that a function be called at some future time. There are, however, some significant differences between
the two, including :
	-- Tasklets run in interrupt context, thus the code being atomic. Instead, workqueue functions run 
	   in the context of a special kernel process; as a result, they have more flexibility. In particular,
	   workqueue functions can sleep.
	-- Tasklets always run on the processor from which they were originally submitted. Workqueues work in
	   the same way by default.
	-- Kernel code can request that the execution of workqueue functions be delayed for an explicit interval.
	
Syntax & Semantics
------------------
	Workqueues are implemented using two structures : 'struct workqueue_struct' & 'struct work_struct', 
defined in <linux/workqueue.h>. 
	
	For the workqueues to start running, first declare & initialise the workqueue :
	struct workqueue_struct *workqueue;
	workqueue = create_singlethread_workqueue("Sample Workqueue");
	
	Now a work has to created and submitted to the workqueue created above :
	struct work_struct work;
	INIT_WORK(&work ,wrq_func);
	
	Now push the work to the workqueue :
	queue_work(workqueue, &work);
	
	The kernel then finds the appropriate time execute the work function.
	
	Finally, before unloading the module, destroy the workqueue :
	destroy_workqueue(workqueue); 
	
	Workqueues also support other APIs such as : queue_delayed_work(), cancel_delayed_work(), flush_workqueue(), etc.
	
