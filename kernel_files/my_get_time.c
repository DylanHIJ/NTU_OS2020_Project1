#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/time.h>

asmlinkage long timespec my_get_time(){
    struct timespec time;
    getnstimeofday(&time);
    return time.tv_sec * 1000000000 + time.tv_nsec; 
}
