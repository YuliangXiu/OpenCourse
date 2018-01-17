head = vmrp.h
srcs = vmrp.cpp
objs = vmrp.o
opts = -w -g -c
all: 		vmrp
vmrp:		$(objs)
		gcc $(objs) -o vmrp
vmrp.o: 	$(srcs) $(head)
		gcc $(opts) $(srcs)
clean:
		rm vmrp *.o
