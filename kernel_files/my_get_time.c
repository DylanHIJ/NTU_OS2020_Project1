#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/time.h>

asmlinkage struct timespec my_get_time(){
    struct timespec time;
    getnstimeofday(&time);
    return time; 
}