/***************** HELLO MODULE AND PROCESS TREE *************/

#include<linux/init.h>
#include<linux/module.h>
#include<linux/sched.h>
#include<linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("SIMPLE MODULE TO PRINT PROCESS TREE");
MODULE_AUTHOR("KERNEL MASTER");

static int __init hello_module_init(void)
{
     struct task_struct *process, *parent_process;
     process = current;
     parent_process = process->parent;
     
     printk(KERN_INFO "Hello module inserted! \n");
     printk(KERN_INFO "Current process :- name = %s, pid = %d\n", process->comm, process->pid);
     printk(KERN_INFO "Parent process:- name = %s, ppid = %d\n",parent_process->comm, parent_process->pid);
       
       
     while(process->pid !=0)
     {
        process = process->parent;
        printk(KERN_INFO "Process in tree:- name = %s, pid = %d\n", process->comm, process->pid);
     }
      return 0;
}

static void __exit hello_module_exit(void)
{
     printk(KERN_INFO " Hello module removed! \n");
}

module_init(hello_module_init);
module_exit(hello_module_exit);


     
         
