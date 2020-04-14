#include <linux/kernel.h>
#include <linux/linkage.h>

asmlinkage void my_printk(char *str){
    printk("%s", str);
}