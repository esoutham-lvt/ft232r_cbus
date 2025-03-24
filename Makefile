CFLAGS = -Wall -O2 -s -Werror
LDFLAGS = -lusb -lftdi1 -s
PROG = ft232r_cbus
INCLUDES = -I/usr/include/ -I/opt/homebrew/include/

all:	$(PROG)

$(PROG):	main.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS) -I $(INCLUDES)

clean:
	rm -f $(PROG)
