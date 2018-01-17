srcs = filexm.c
objs = filexm.o
all:		filexm
filexm: 	$(objs)
		gcc $(objs) -o filexm
filexm.o: 	$(srcs)
		gcc -c $(srcs)
clean:
		rm filexm *.o
