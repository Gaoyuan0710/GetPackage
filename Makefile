all:get_package.c
	gcc -g -Wall get_package.c -lpcap
clean:
	rm -rf *.o get_package
