/**
 获取的文件管理信息,检测文件读写操作。
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#define BUFSZ 32
//判断文件类型
void is_filetype(mode_t mode) {
//显示文件类型
	printf("File Type:\t");
//链接文件
	if (S_ISLNK(mode))
		printf("Symbolic Linke\n");
//普通文件
	else if (S_ISREG(mode))
		printf("Regular\n");
//目录文件
	else if (S_ISDIR(mode))
		printf("Directoy\n");
//字符设备
	else if (S_ISCHR(mode))
		printf("Character Device\n");
//块设备
	else if (S_ISBLK(mode))
		printf("Block Device\n");
//管道文件
	else if (S_ISFIFO(mode))
		printf("FIFO\n");
//套接口
	else if (S_ISSOCK(mode))
		printf("Socket\n");
//不可识别的设备
	else
		printf("Unkown type\n");
}
