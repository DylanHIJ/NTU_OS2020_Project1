#include <sched.h>
#include <sys/types.h>

int raise_priority(pid_t pid){
    /* Raise the priority of a process */ 
    struct sched_param param;
    param.sched_priority = 80;
    if(sched_setscheduler(pid, SCHED_FIFO, &param) < 0){
        perror("sched_setscheduler");
        return -1;
    }
    return 0; 
}

int reduce_priority(pid_t pid){
    /* Reduce the priority of a process */ 
    struct sched_param param;
    param.sched_priority = 20;
    if(sched_setscheduler(pid, SCHED_FIFO, &param) < 0){
        perror("sched_setscheduler");
        return -1;
    }
    return 0;
}
