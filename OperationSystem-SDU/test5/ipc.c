/*
 * 文件名称：	ipc.c
 *
 * 程序目的：一组建立 IPC 机制的函数
 */
#include "ipc.h"

/*
 * 从/proc/sysvipc/文件系统中获取 IPC 的 id 号
 * proc_file：对应/proc/sysvipc/目录中的 IPC 文件（分别为：msg-消息队列,sem-信号量,shm-共享内存）
 * key：对应要获取的 IPC 的 id 号的键值
 */
int get_ipc_id(char *proc_file, key_t key) {
	printf("proc_file = %s    key_t = %d", proc_file, key);

	FILE *pf; //读取的proc文件
	int i, j;
	char line[BUFSZ], colum[BUFSZ];
	if ((pf = fopen(proc_file, "r")) == NULL ) {
		//如果打开文件错误则输出错误的内容
		perror("Proc file not open");
		exit(EXIT_FAILURE);
	}
	fgets(line, BUFSZ, pf); //获取文件？？为什么BUFSZ是256？？？
	while (!feof(pf)) {
		i = j = 0;
		fgets(line, BUFSZ, pf);
		//一直读取到不为空格的字符
		while (line[i] == ' ')
			i++;

		//如果不为空格则将该行的数据写入到colum数组中
		while (line[i] != ' ')
			colum[j++] = line[i++];

		colum[j] = '\0'; //字符串的结尾标志
		printf("colum = %s  ", colum);

		if (atoi(colum) != key) //如果没有读出来需要的key，直接下一行
			continue;

		//读到了需要的key值
		j = 0;
		while (line[i] == ' ')
			i++;
		while (line[i] != ' ')
			colum[j++] = line[i++];
		colum[j] = '\0';
		i = atoi(colum);
		fclose(pf);
		return i;
	}
	fclose(pf);
	return -1;
}

/*
 * 信号灯上的 down/up 操作
 * semid:信号灯数组标识符
 * semnum:信号灯数组下标
 * buf:操作信号灯的结构
 */
int down(int sem_id) {
	struct sembuf buf;
	buf.sem_op = -1;
	buf.sem_num = 0;
	buf.sem_flg = SEM_UNDO;
	/**操作信号灯数组的系统调用语法:
	 int semop(int semid,struct sembuf *semop, unsigned nops);
	 semid：由 semget 创建的信号灯数组的标识符
	 semop：指向 sembuf 数据结构的指针
	 nops：信号灯数组元素的个数。
	 semop调用成功返回 0,不成功返回-1。
	 */
	if ((semop(sem_id, &buf, 1)) < 0) {
		perror("down error ");
		exit(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}
int up(int sem_id) {
	struct sembuf buf;
	buf.sem_op = 1;
	buf.sem_num = 0;
	buf.sem_flg = SEM_UNDO;
	if ((semop(sem_id, &buf, 1)) < 0) {
		perror("up error ");
		exit(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}

/*
 建立一个具有 n 个信号灯的信号量
 如果建立成功，返回一个信号灯数组的标识符sem_id
 输入参数：
 sem_key 信号灯数组的键值
 sem_val 信号灯数组中信号灯的个数
 sem_flag 信号等数组的存取权限
 */
int set_sem(key_t sem_key, int sem_val, int sem_flg) {
	int sem_id;
	Sem_uns sem_arg;
	//测试由 sem_key 标识的信号灯数组是否已经建立
	if ((sem_id = get_ipc_id("/proc/sysvipc/sem", sem_key)) < 0) {
		/**创建一个信号灯数组的系统调用有语法:
		 int semget(key_t key,int nsems, int flags);
		 key：信号灯数组的键值,可以为 IPC_PRIVATE,也可以用整数指定一个
		 nsems：信号灯数组中信号灯的个数
		 flags：信号灯数组权限位。如果 key 用整数指定,应设置 IPC_CREAT 位。
		 semget：调用成功返回一个新建立的信号等数组标识符。
		 */
		//semget 新建一个信号灯,其标号返回到 sem_id
		if ((sem_id = semget(sem_key, 1, sem_flg)) < 0) {
			perror("semaphore create error");
			exit(EXIT_FAILURE);
		}
		//设置信号灯的初值
		sem_arg.val = sem_val;
		/**
		 控制信号灯数组的系统调用语法:
		 int semctl(int semid,int semnum,int cmd, union semun arg);
		 semid：由semget创建的信号灯数组的标识符
		 semnum：该信号灯数组中的第几个信号灯
		 cmd：对信号灯发出的控制命令。
		 例如:
		 GETVAL 返回当前信号灯状态
		 SETVAL 设置信号灯状态
		 IPC_RMD 删除标号为 semid 的信号灯
		 arg：保存信号灯状态的联合体，信号灯的值是其中一个基本成员
		 union semun {int val;//value for SETVAL};
		 semctl执行不成功返回-1，否则返回指定的 cmd 的值。
		 */
		if (semctl(sem_id, 0, SETVAL, sem_arg) < 0) {
			perror("semaphore set error");
			exit(EXIT_FAILURE);
		}
	}
	return sem_id;
}

/*
 函数建立一个具有n个字节的共享内存区
 如果建立成功,返回一个指向该内存区首地址的指针shm_buf
 输入参数:
 shm_key 共享内存的键值
 shm_val 共享内存字节的长度
 shm_flag 共享内存的存取权限
 */
char * set_shm(key_t shm_key, int shm_num, int shm_flg) {
	int i, shm_id;
	char * shm_buf;
	//测试由 shm_key 标识的共享内存区是否已经建立，如果还没有创建则开始创建
	if ((shm_id = get_ipc_id("/proc/sysvipc/shm", shm_key)) < 0) {
		/**创建一段共享内存系统调用语法 :
		 int shmget(key_t key,int size,int flags);
		 key：共享内存的键值,可以为 IPC_PRIVATE,也可以用整数指定一个
		 size：共享内存字节长度
		 flags：共享内存权限位。
		 shmget调用成功后,返回一个新建立的共享内存段标识符。
		 */
		//shmget新建一个长度为shm_num字节的共享内存，其标号返回到shm_id
		if ((shm_id = shmget(shm_key, shm_num, shm_flg)) < 0) {
			perror("shareMemory set error");
			exit(EXIT_FAILURE);
		}

		/**令一段共享内存附加到调用进程中的系统调用语法:
		 char *shmat(int shmid, char *shmaddr,int flags)
		 shmid：由 shmget 创建的共享内存的标识符
		 shmaddr：总为 0,表示用调用者指定的指针指向共享段
		 flags：共享内存权限位
		 shmat调用成功后返回附加的共享内存首地址
		 */
		//shmat将由shm_id标识的共享内存附加给指针shm_buf
		if ((shm_buf = (char *) shmat(shm_id, 0, 0)) < (char *) 0) {
			perror("get shareMemory error");
			exit(EXIT_FAILURE);
		}

		for (i = 0; i < shm_num; i++)
			shm_buf[i] = 0; //初始为 0
	}
	//shm_key 标识的共享内存区已经建立,将由 shm_id 标识的共享内存附加给指针 shm_buf
	if ((shm_buf = (char *) shmat(shm_id, 0, 0)) < (char *) 0) {
		perror("get shareMemory error");
		exit(EXIT_FAILURE);
	}
	return shm_buf;
}

/*
 建立一个消息队列
 如果建立成功，返回一个消息队列的标识符msq_id
 输入参数:
 msq_key 消息队列的键值
 msq_flag 消息队列的存取权限
 */
int set_msq(key_t msq_key, int msq_flg) {
	int msq_id;
	//测试由 msq_key 标识的消息队列是否已经建立
	if ((msq_id = get_ipc_id("/proc/sysvipc/msg", msq_key)) < 0) {
		/**创建消息队列的系统调用语法：
		 int msgget(key_t key,int flags)
		 key：消息队列的键值,可以为 IPC_PRIVATE,也可以用整数指定一个
		 flags：消息队列权限位。
		 msgget调用成功返回一个新建立的消息队列标识符。
		 */
		//msgget新建一个消息队列，其标号返回到 msq_id
		if ((msq_id = msgget(msq_key, msq_flg)) < 0) {
			perror("messageQueue set error");
			exit(EXIT_FAILURE);
		}
	}
	return msq_id;
}
