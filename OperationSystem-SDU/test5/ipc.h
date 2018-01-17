/**
 以下示例实验程序应能模拟一个读者/写者问题,它应能实现一下功能:
 1. 任意多个读者可以同时读;
 2. 任意时刻只能有一个写者写;
 3. 如果写者正在写,那么读者就必须等待;
 4. 如果读者正在读,那么写者也必须等待;
 5. 允许写者优先;
 6. 防止读者或写者发生饥饿。
 为了能够体验 IPC 机制的消息队列的用法,
 本示例程序采用了 Theaker & Brookes 提出的消息传递算法。
 该算法中有一控制进程,带有 3 个不同类型的消息信箱,
 它们分别是:读请求信箱、写请求信箱和操作完成信箱。
 读者需要访问临界资源时首先要向控制进程发送读请求消息,
 写者需要访问临界资源时也要先向控制进程发送写请求消息,
 在得到控制进程的允许消息后方可进入临界区读或写。
 读或写者在完成对临界资源的访问后还要向控制进程发送操作完成消息。
 控制进程使用一个变量 count 控制读写者互斥的访问临界资源并允许写者优先。
 count 的初值需要一个比最大读者数还要大的数,本例取值为100。
 当 count 大于 0 时说明没有新的读写请求,控制进程接收读写者新的请求,
 如果收到读者完成消息,对 count 的值加 1,
 如果收到写者请求消息,count 的值减100,
 如果收到读者请求消息,对 count 的值减 1。
 当 count 等于 0时说明写者正在写,控制进程等待写者完成后再次令 count 的值等于 100。
 当count 小于 0 时说明读者正在读,控制进程等待读者完成后对 count 的值加 1。
 */

/**
 * 文件名称：	ipc.h
 *
 * 程序目的：声明 IPC 机制的函数原型和全局变量
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <unistd.h>

#define BUFSZ	256
#define MAXVAL	100
#define STRSIZ	8
#define WRITERQUEST		1	//写请求标识
#define READERQUEST		2	//读请求标识
#define FINISHED		3	//读写完成标识
/*信号灯控制用的共同体*/
typedef union semuns {
	int val;
} Sem_uns;

/*消息结构体*/
typedef struct msgbuf {
	long mtype;
	int mid;
} Msg_buf;

key_t buff_key;
int buff_num;
char *buff_ptr;
int shm_flg;
int quest_flg;
key_t quest_key;
int quest_id;
int respond_flg;
key_t respond_key;
int respond_id;

int get_ipc_id(char *proc_file, key_t key);
char *set_shm(key_t shm_key, int shm_num, int shm_flag);
int set_msq(key_t msq_key, int msq_flag);
int set_sem(key_t sem_key, int sem_val, int sem_flag);
int down(int sem_id);
int up(int sem_id);
