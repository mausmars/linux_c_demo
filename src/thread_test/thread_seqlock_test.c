#include <linux/module.h>
#include <linux/version.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/jiffies.h>
#include <linux/delay.h>

//这三个头文件与内核线程的使用有关;
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/err.h>

//顺序锁相关
#include <linux/seqlock.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("*************");
MODULE_VERSION("2.6.35.000");

int sleep_time = (1 * 10 * HZ);
int shared_res = 0;

//STEP1:定义顺序锁
seqlock_t my_seq_lock;

//STEP5:实现线程函数
int thread_process1(void* param) {
	//int val = 0, ret = 0;

	while (1) {
		set_current_state(TASK_UNINTERRUPTIBLE);

		if (kthread_should_stop()) {
			printk("kernel thread '%s' should stop;file:%s;line:%d\n",
					__FUNCTION__, __FILE__, __LINE__);
			break;
		}

		//STEP3:对临界区加锁
		write_seqlock(&my_seq_lock);
		shared_res++;
		//STEP4:对临界区解锁
		write_sequnlock(&my_seq_lock);

		mdelay(sleep_time);
	}
	return 12;
}
;

int thread_process2(void* param) {
	//int val = 0, ret = 0;

	while (1) {
		set_current_state(TASK_UNINTERRUPTIBLE);

		if (kthread_should_stop()) {
			printk("kernel thread '%s' should stop;file:%s;line:%d\n",
					__FUNCTION__, __FILE__, __LINE__);
			break;
		}

		//STEP3:对临界区加锁
		write_seqlock(&my_seq_lock);
		shared_res++;
		//STEP4:对临界区解锁
		write_sequnlock(&my_seq_lock);

		msleep(sleep_time);
	}
	return 34;
}
;

int thread_process3(void* param) {
	int val = 0; //, ret = 0;
	unsigned int seq_num = 0;

	while (1) {
		set_current_state(TASK_UNINTERRUPTIBLE);

		if (kthread_should_stop()) {
			printk("kernel thread '%s' should stop;file:%s;line:%d\n",
					__FUNCTION__, __FILE__, __LINE__);
			break;
		}

		//seq lock read --- begin
		do {
			seq_num = read_seqbegin(&my_seq_lock);
			val = shared_res;
			printk("%s: shared resource = %d;\n%s", __FUNCTION__, val,
					((val % 3) ? "" : "\n"));
		} while (read_seqretry(&my_seq_lock, seq_num));
		//seq lock read --- end

		msleep(sleep_time);
	}
	return 56;
}
;

int thread_process4(void* param) {
	int val = 0; //, ret = 0;
	unsigned int seq_num = 0;

	while (1) {
		set_current_state(TASK_UNINTERRUPTIBLE);

		if (kthread_should_stop()) {
			printk("kernel thread '%s' should stop;file:%s;line:%d\n",
					__FUNCTION__, __FILE__, __LINE__);
			break;
		}

		//seq lock read --- begin
		do {
			seq_num = read_seqbegin(&my_seq_lock);
			val = shared_res;
			printk("%s: shared resource = %d;\n%s", __FUNCTION__, val,
					((val % 3) ? "" : "\n"));
		} while (read_seqretry(&my_seq_lock, seq_num));
		//seq lock read --- end

		msleep(sleep_time);
	}
	return 78;
}
;

struct task_struct* my_thread1 = NULL;
struct task_struct* my_thread2 = NULL;
struct task_struct* my_thread3 = NULL;
struct task_struct* my_thread4 = NULL;

int __init study_init(void)
{
	int err = 0;
	printk("%s\n", __PRETTY_FUNCTION__);

	//STEP2:初始化顺序锁
	seqlock_init(&my_seq_lock);
	printk("init seq lock ok\n");

	my_thread1 = kthread_create(thread_process1, NULL, "my_thread1");
	if(IS_ERR(my_thread1))
	{
		err = PTR_ERR(my_thread1);
		my_thread1 = NULL;
		printk(KERN_ERR "unable to start kernel thread1:%d\n", err);
		return err;
	}

	my_thread2 = kthread_create(thread_process2, NULL, "my_thread2");
	if(IS_ERR(my_thread2))
	{
		err = PTR_ERR(my_thread2);
		my_thread2 = NULL;
		printk(KERN_ERR "unable to start kernel thread2:%d\n", err);
		return err;
	}

	my_thread3 = kthread_create(thread_process3, NULL, "my_thread3");
	if(IS_ERR(my_thread3))
	{
		err = PTR_ERR(my_thread3);
		my_thread3 = NULL;
		printk(KERN_ERR "unable to start kernel thread3:%d\n", err);
		return err;
	}

	my_thread4 = kthread_create(thread_process4, NULL, "my_thread4");
	if(IS_ERR(my_thread4))
	{
		err = PTR_ERR(my_thread4);
		my_thread4 = NULL;
		printk(KERN_ERR "unable to start kernel thread4:%d\n", err);
		return err;
	}

	wake_up_process(my_thread1);
	wake_up_process(my_thread2);
	wake_up_process(my_thread3);
	wake_up_process(my_thread4);
	printk("%s:all kernel thread start;\n", __FUNCTION__);
	return 0;
}

void __exit study_exit(void)
{
	int ret = -1;
	printk("%s\n",__PRETTY_FUNCTION__);

	if(my_thread1)
	{
		ret = kthread_stop(my_thread1);
		my_thread1 = NULL;
		printk("kernel thread1 stop,exit code is %d;\n",ret);
	}

	if(my_thread2)
	{
		ret = kthread_stop(my_thread2);
		my_thread2 = NULL;
		printk("kernel thread2 stop,exit code is %d;\n",ret);
	}

	if(my_thread3)
	{
		ret = kthread_stop(my_thread3);
		my_thread3 = NULL;
		printk("kernel thread3 stop,exit code is %d;\n",ret);
	}

	if(my_thread4)
	{
		ret = kthread_stop(my_thread4);
		my_thread4 = NULL;
		printk("kernel thread4 stop,exit code is %d;\n",ret);
	}

	printk("%s:all kernel thread stop;\n", __FUNCTION__);
}

module_init( study_init);
module_exit( study_exit);
