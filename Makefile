CFLAGS = -Wall -O2  -Werror
LDFLAGS = -lusb -lftdi -s						# linux-build on linux (original-library
#LDFLAGS = /opt/homebrew/lib/libftdi1.dylib 	# macos-build (updated-library)
INCLUDES = /opt/homebrew/include/libftdi1		# macos-additional include path

PROG = ft232r_cbus

all:	$(PROG)

$(PROG):	main.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS) -I $(INCLUDES)

clean:
	rm -f $(PROG)
