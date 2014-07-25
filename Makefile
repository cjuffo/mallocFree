DIR ?= $(shell pwd)

dynamic:
	cc -fPIC -c mallocfree.c
	cc -shared -o libmalfree.so mallocfree.o 
	cc test.c -o DynaMalloc -L. libmalfree.so
	cc -L. -Wl,-rpath=$(DIR) -Wall -o DynaMalloc test.c -lmalfree

static:
	cc  -c mallocfree.c 
	ar -cvq libmalfree.a mallocfree.o
	cc -o StaticMalloc test.c libmalfree.a

test:
	./StaticMalloc
	./DynaMalloc

clean:
	-rm mallocfree.o libmalfree.a libmalfree.so StaticMalloc DynaMalloc

submit:
	svn commit -m "READY FOR GRADING"
