#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/delay.h>

static struct task_struct *thr1, *thr2;

// Thread 선언
int thread_function(void *arg)
{
	// 반환값이 1이 될때까지 반복
	char *thr_name = (char*) arg;
	while(!kthread_should_stop())
	{
		printk("Thread [%s] running\n",thr_name);
		ssleep(3);
	}
	printk("%s Stopped\n", thr_name);

	return 0;
}

int __init thread_init (void)
{
	printk("Init thread test\n");
	
	// Thread 함수를 콜백으로 넘겨준다.
	thr1 = kthread_create(thread_function, "Worker 1", "thread1");
	if(thr1)
	{
		wake_up_process(thr1);
		printk("Success to create thread 1\n");
	}

	thr2 = kthread_create(thread_function, "Worker 2", "thread2");
	if(thr2)
	{
		wake_up_process(thr2);
		printk("Success to create thread 2\n");
	}
	return 0;
}

void __exit thread_exit (void)
{
	// thread가 exit될 때 함수를 멈춘다.
	if(kthread_stop(thr1) != EINTR)
		printk("Thread 1 Stopped Successfully\n");
	if(kthread_stop(thr2) != EINTR)
		printk("Thread 2 Stopped Successfully\n");
}

module_init(thread_init);
module_exit(thread_exit);
