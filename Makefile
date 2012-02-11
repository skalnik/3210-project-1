obj-m = lfprng.o
KVERSION = '2.6.24.6'
all:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) modules
	cc -lpthread multi_reader.c
clean:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD)
	rm a.out
