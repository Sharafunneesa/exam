/***************** HELLO MODULE AND PROCESS TREE *************/

#include<linux/init.h>             // for module init and exit
#include<linux/module.h>           // for module build
#include<linux/sched.h>            // for process structures
#include<linux/kernel.h>           // kernel defnition

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("SIMPLE MODULE TO PRINT PROCESS TREE");
MODULE_AUTHOR("KERNEL MASTER");

// init hello module 
static int __init hello_module_init(void)
{    
     // declairing two pointers for holding the pid and ppid
     struct task_struct *process, *parent_process;
     process = current;
     parent_process = process->parent;
     
     // printing the kernel informations process name, process id, paranet process name and parent process id
     printk(KERN_INFO "Hello module inserted! \n");
     printk(KERN_INFO "Current process :- name = %s, pid = %d\n", process->comm, process->pid);
     printk(KERN_INFO "Parent process:- name = %s, ppid = %d\n",parent_process->comm, parent_process->pid);
      
     // takng a while loop to print the name and pid of the process from current process to  pid 0
     while(process->pid !=0)
     {
        process = process->parent;
        printk(KERN_INFO "Process in tree:- name = %s, pid = %d\n", process->comm, process->pid);
     }
      return 0;
}

// exit hello module
static void __exit hello_module_exit(void)
{
     printk(KERN_INFO " Hello module removed! \n");
}

module_init(hello_module_init);
module_exit(hello_module_exit);


     
         
