#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <time.h>
#include "process.h"

#define MY_GET_TIME
#define MY_PRINTK

void unit_time(){
    volatile unsigned long i;
    for(i = 0; i < 1000000UL; i ++);
    return; 
}

void assign_proc_to_cpu(pid_t pid, int cpu_id){
    /* Assign a process to a particular cpu */
    if(cpu_id > sizeof(cpu_set_t)){
        fprintf(stderr, "Invalid CPU ID.");
        return; 
    }

    cpu_set_t cpu_mask;
    CPU_ZERO(&cpu_mask);
    CPU_SET(cpu_id, &cpu_mask);

    if(sched_setaffinity(pid, sizeof(cpu_mask), &mask) < 0){
        perror("sched_setaffinity");
        exit(0);
    }
}

int exec_process(Process proc){
    /* Execute the given process */
    pid_t pid = fork();
    
    if(pid < 0){
        perror("fork");
        return -1;
    }

    if(pid == 0){
        pid_t cur_pid = getpid();
        
        printf("%s %d\n", proc.name, cur_pid);
        struct timespec start_time, end_time;
        start_time = syscall(MY_GET_TIME);

        for(int t = 0; t < proc.exec_time; t ++)
            unit_time();

        end_time = syscall(MY_GET_TIME);
       
        char print_to_dmesg[100];
        
        sprintf(print_to_dmesg, "[Project1] %d %lld.%.9ld %lld.%.9ld\n", 
            cur_pid, (long long) start_time.tv_sec, start_time.tv_nsec,
            (long long) end_time.tv_sec, end_time.tv_nsec);
        
        syscall(MY_PRINTK, print_to_dmesg);
    }

    assign_proc_to_cpu(pid, 1);
    return pid;
}

