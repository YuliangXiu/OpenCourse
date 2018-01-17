/*
 获取的文件管理信息,检测文件读写操作。
 */
#include "filexm.h"
int main(int argc, char *argv[]) {
	int fd;
//打开文件的文件描述字
	struct stat buf; //保存打开文件信息的缓冲区
	char data[BUFSZ]; //文件读写缓冲区
// 检查命令是否带有指定的文件名
	if (argc != 2) {
		perror("USAGE: ./filexm filename");
		exit(EXIT_FAILURE);
	}
// 检查命令指定的文件名是否存在,如果存在打开该文件
	if ((fd = open(argv[1], O_RDONLY)) < 0) {
		perror("File not Open!");
		exit(EXIT_FAILURE);
	}
//指定的的文件打开,是否能读出该文件的控制信息
	if ((fstat(fd, &buf)) < 0) {
		perror("File stat error!");
		exit(EXIT_FAILURE);
	}
//该文件的控制信息读出,显示文件控制信息
//显示文件名
	printf("File Name:\t%s\n", argv[1]);
//显示节点号
	printf("File INODE:\t%ld\n", buf.st_ino);
//显示设备号
	printf("File DEVICE:\t%d,%d\n", major(buf.st_dev), minor(buf.st_dev));
//显示保护方式
	printf("File MODE:\t%#o\n", buf.st_mode & ~(S_IFMT));
//显示连接数
	printf("File LINKS:\t%d\n", buf.st_nlink);
//显示用户 ID
	printf("File UID:\t%d\n", buf.st_uid);
//显示组 ID
	printf("File GID:\t%d\n", buf.st_gid);
//分析并显示文件的类型
	is_filetype(buf.st_mode);
//显示文件长度
	printf("File SIZE:\t%ld\n", buf.st_size);
//显示文件系统 I/O 块长度
	printf("File BLK SIZE:\t%ld\n", buf.st_blksize);
//显示已分配 I/O 块长度
	printf("File BLOCK:\t%ld\n", buf.st_blocks);
//显示最后访问文件的时间
	printf("File ACCESSED:\t%s", ctime(&buf.st_atime));
//显示最后修改文件的时间
	printf("File MODIFIED:\t%s", ctime(&buf.st_mtime));
//显示最后改变文件的时间
	printf("File CHANGED:\t%s", ctime(&buf.st_ctime));
//显示部分文件的内容
	printf("File Part Content:\n");
	lseek(fd, buf.st_size / 2, SEEK_SET); //读写位置移到文件中部
	if (read(fd, data, BUFSZ) > 0) { //读 BUFSZ 字节
		write(2, data, BUFSZ);
//写到标准输出设备上
		printf("\n");
	}
//关闭文件
	if (close(fd) < 0) {
		perror("Close error");
		exit(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}
