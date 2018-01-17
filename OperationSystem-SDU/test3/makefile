srcs = psched.c
objs = psched.o
opts = -g -c
all: psched

psched:	$(objs) 
	gcc $(objs) -o psched
psched.o:$(srcs)
	gcc $(opts) $(srcs)
clean:
	rm psched *.o
