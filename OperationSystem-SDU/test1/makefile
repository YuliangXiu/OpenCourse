d = os1.h
srcs = os1.c
objs = os1.o
opts = -g -c
all: os1

pctl:	$(objs)
	gcc $(objs) -o os1
pctl.o: $(srcs) $(head)
	gcc $(opts) $(srcs)
clean:
	rm os1 *.o
