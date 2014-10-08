all:get_package.c
	gcc -g -Wall simplesniffer.c -lpcap
clean:
	rm -rf *.o a.out
