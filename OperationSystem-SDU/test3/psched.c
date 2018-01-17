#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(int argc, char *argv[]) {
	printf("\n");
    
	int i;
	int pid[3]; //存放进程号的数组
    
	/*
	 结构体sched_param中的属性：
	 __sched_priority：存有调度优先数
	 */
	struct sched_param p[3]; //设置调度策略时使用的数据结构
    
	//循环创建 3 个子进程
	for (i = 0; i < 3; i++) {
		pid[i] = fork(); //创建一个新的进程
        
		//父进程设置子进程的相关参数
		if ((pid[i]) > 0) {
            
			//取进程优先数放在调度策略数据结构中
			if (argv[i + 1] != NULL ) {
				//如果命令行第 4,5,6 参数指定了优先级则按指定的数设置
				p[i].sched_priority = atoi(argv[i + 1]);
			} else {
				//如果没有指定则都为10
				p[i].sched_priority = 10;
			}
            
			/**
			 设置进程动态优先数的系统调用语法为:
			 int setpriority(int which,int who,int prio);
			 which：设置的对象。可以是: 进程PRIO_PROCESS，进程组PRIO_PGRP，用户PRIO_USER
			 who：对应设置对象的进程号或组号或用户号
			 prio：要设置的进程优先数
			 返回值: 所有匹配进程中的最高优先数
			 */
			//父进程设置子进程的优先数，如果命令行第 1,2,3 参数指定了 3 个优先数则按指定的数设置,否则都为 10
			if (argv[i + 1] != NULL ) {
				setpriority(PRIO_PROCESS, pid[i], atoi(argv[i + 1]));
			} else {
				setpriority(PRIO_PROCESS, pid[i], 10);
			}
            
			/**
			 设置进程调度策略的系统调用：
			 int sched_setscheduler(pid_t pid,int policy,const struct sched_param *sp);
			 pid：进程号
			 policy：3种调度策略之一
			 sp：调度参数结构指针,调度参数结构主要存有调度优先数。（结构体sched_param）
			 返回值: 执行成功后返回 0
			 */
			//父进程设置子进程的调度策略
			if (argv[i + 4] != NULL ) {
				//如果命令行第 4,5,6 参数指定了策略值则按指定的数设置
				printf("set pid%d policy = %d \n", pid[i], atoi(argv[i + 4]));
				int res = sched_setscheduler(pid[i], atoi(argv[i + 4]), &p[i]);
				printf("set result:%d\n", res);
                
			} else {
				//否则都为默认策略
				sched_setscheduler(pid[i], SCHED_OTHER, &p[i]);
			}
            
		}
        
		//各子进程循环报告其优先数和调度策略
		if ((pid[i]) == 0) {
			sleep(2);
			printf("\n");
            
			/**
			 获得进程动态优先数的系统调用语法为:
			 int getpriority(int which,int who);
			 which：设置的对象。可以是: 进程PRIO_PROCESS，进程组PRIO_PGRP，用户PRIO_USER
			 who：对应设置对象的进程号或组号或用户号
			 返回值: 所有匹配进程中的最高优先数
			 */
			//每隔 1 妙报告一次进程号和优先级
			for (i = 0; i < 10; i++) {
				sleep(1);
				printf("PID = %d    priority = %d    policy = %d\n\n", getpid(),
                       getpriority(PRIO_PROCESS, 0),
                       sched_getscheduler(0));
                
			}
			exit(EXIT_SUCCESS);
		}
	}
    
	//父进程报告子进程调度策略后先行退出
	printf("My child %d policy is %d\n", pid[0], sched_getscheduler(pid[0]));
	printf("My child %d policy is %d\n", pid[1], sched_getscheduler(pid[1]));
	printf("My child %d policy is %d\n", pid[2], sched_getscheduler(pid[2]));
    
	return EXIT_SUCCESS;
}
