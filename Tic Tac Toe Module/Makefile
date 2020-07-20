obj-m := tictactoe.o

tictactoe-objs := main.o tictactoe_functions.o 

KDIR ?= /lib/modules/$(shell uname -r)/build


all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

install:
	$(MAKE) -C $(KDIR) M=$(PWD) modules_install

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean