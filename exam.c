/****** SIMPLE MODULE FOR "HELLO WORLD" ******/

/* Adding header files */
#include <linux/module.h>    // MODULE_AUTHOR , MODULE_LICENSE, MODULE_DESCRIPTION
#include <linux/init.h>      // module_init & module_exit macro  
#include <linux/kernel.h>    // printk function prototype
#include<linux/sched.h>      // print pid of process

/* function for init the module */
static int __init hello_world_init(void)
{
    printk("Module init function\n");
    printk("\n Adding Hello_world module \n");                     //printing the message
    printk(KERN_DEBUG  "pid:%d name:%s \n",current->pid,__func__); //printing the name and pid of process
    //printk(KERN_DEBUG  "ppid:%d\n", current->ppid);
   
    return 0;
    
}

/* function for the exit module */ 
static void __exit hello_world_exit(void)
{
 
   printk("Module exit function\n");
   printk("\n Removing Hello_world module \n");
   
}

module_init(hello_world_init);
module_exit(hello_world_exit);

MODULE_AUTHOR("Kernel Masters");
MODULE_DESCRIPTION("Hello World Module");
MODULE_LICENSE("GPL");





