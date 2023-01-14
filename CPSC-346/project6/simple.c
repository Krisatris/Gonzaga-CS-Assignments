#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>

/* IMPORTANT: RUN THIS ON LINUX PREFERABLY IN A VM
   This program interacts with your kernal, will crash
   your OS if something goes wrong                   */

struct person
{
       int month;
       int day;
       int year;
       struct person *next;
};

struct person *head = NULL;

/* This function is called when the module is loaded. */
int simple_init(void)
{
       printk(KERN_INFO "Loading Module\n");

       head = kmalloc(sizeof(*head), GFP_KERNEL);
       head->day = 1;
       head->month = 1;
       head->year = 2000;

       struct person *last = head;
       int i;
       for(i = 1; i < 5; ++i) {
              struct person *new;
              new = kmalloc(sizeof(*new), GFP_KERNEL);
              new->day = i + 1;
              new->month = i + 1;
              new->year = 2000;
              last->next = new;
              last = new;
       }

       struct person *curr = head;
       while(curr) {
              printk("%d-%d-%d\n", curr->month, curr->day, curr->year);
              curr = curr->next;
       }

       return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
	printk(KERN_INFO "Removing Module\n");

       struct person *prev = head;
       struct person *curr = prev->next;
       while(curr) {
              printk("prev day before free: %d\n", prev->day);
              kfree(prev);
              printk("prev day after free: %d\n", prev->day);
              prev = curr;
              curr = curr->next;
       }
       printk("prev day before free: %d\n", prev->day);
       kfree(prev);
       printk("prev day after free: %d\n", prev->day);
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

