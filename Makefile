CFLAGS = -Wall -O2 -s -Werror
LDFLAGS = -lusb -lftdi -s
PROG = ft232r_cbus

all:	$(PROG)

$(PROG):	main.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -f $(PROG)
