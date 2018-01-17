/*
 * 文件名称：	os1.c
 *
 * 程序目的：一个多进程并发执行程序。
 * 父进程首先创建一个执行 ls 命令的子进程。
 * 然后再创建一个执行 ps 命令的子进程。
 * 并控制 ps 命令总在 ls 命令之前执行。
 */
#include "os1.h"

int main(int argc, char *argv[]) {
	int i;
	int pid_ls; //存放子进程号
	int pid_ps; //存放子进程号
	int status_ls; //存放子进程返回状态
	int status_ps; //存放子进程返回状态
	char *args_ls[] = { "/bin/ls", "-a", NULL }; //ls子进程要缺省执行的命令
	char *args_ps[] = { "/bin/ps", "-l", NULL }; //ps子进程要缺省执行的命令
    
	signal(SIGINT, (sighandler_t) sigcatch); //注册一个本进程处理键盘中断的函数
    
	pid_ls = fork();	//创建子进程并和其子进程并发执行
	printf("pid_ls = %d \n", pid_ls);
    
	// 建立 ls 进程失败
	if (pid_ls < 0) {
		printf(" pid_ls 进程创建失败\n");
		exit(EXIT_FAILURE);
	}
    
	// ls 子进程执行代码段
	if (pid_ls == 0) {
		printf("我是当前进程(ls)： %d 号\n", getpid()); //返回当前进程的进程号
		printf("我当前的父进程(ls)： %d 号\n", getppid()); //返回当前进程父进程的进程号
        
		//调用 Pause 函数会令调用进程的执行挂起直到一个任意信号到来后再继续运行。
		printf("我(ls)暂停了，等待键盘的中断信号将我唤醒！\n");
		pause(); //暂停,等待中断信号唤醒
        
		//子进程被键盘中断信号唤醒继续执
		printf("我是ls进程： %d 号！已经被唤醒！即将执行！\n", getpid()); //返回当前进程的进程号
        
		printf("ls 子进程要执行的命令如下：\n");
		for (i = 0; args_ls[i] != NULL ; i++)
			printf("%s ", args_ls[i]);			//执行程序中定义的命令
		printf("\n");
		//装入并执行新的程序
		status_ls = execve(args_ls[0], args_ls, NULL );
		printf("status_ls = %d \n", status_ls);
	}
    
	// ls 父进程执行代码段
	if (pid_ls > 0) {
		pid_ps = fork();	//创建 ps 子进程并和其子进程并发执行
		printf("pid_ps = %d \n", pid_ps);
        
		// 建立 ps 子进程失败
		if (pid_ps < 0) {
			printf("创建 pid_ps 进程失败\n");
			exit(EXIT_FAILURE);
		}
        
		// ps 子进程执行代码段
		if (pid_ps == 0) {
			printf("我是当前进程(ps)： %d 号\n", getpid()); //返回当前进程的进程号
			printf("当前的父进程(ps)： %d 号\n", getppid()); //返回当前进程父进程的进程号
            
			printf("ps 子进程将要执行的命令如下：\n");
			for (i = 0; args_ps[i] != NULL ; i++)
				printf("%s ", args_ps[i]);			//执行程序中定义的命令
			printf("\n");
			//装入并执行新的程序
			status_ps = execve(args_ps[0], args_ps, NULL );
			printf("status_ps = %d \n", status_ps);
            
		}
        
		// ps 父进程执行代码段
		if (pid_ps > 0) {
			printf("%d 等待 ps 子进程结束！\n", pid_ps);
			waitpid(pid_ps, &status_ps, 0); //等待子进程结束
			printf("我的 ps 子进程结束了！status = %d \n", status_ps);
			if (kill(pid_ls, SIGINT) >= 0) {
				printf("%d 号进程 唤醒 %d 号子进程！\n", getpid(), pid_ls);
			} else {
				printf("%d 号进程 唤醒 ls 进程失败！\n", getpid());
			}
		}
	}
	return EXIT_SUCCESS;
}