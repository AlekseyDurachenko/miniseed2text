# Build environment can be configured the following
# environment variables:
#   CC : Specify the C compiler to use
#   CFLAGS : Specify compiler options to use

# Required compiler parameters
CFLAGS += -Isubmodules/libmseed -std=c99

LDFLAGS = -Lsubmodules/libmseed
LDLIBS = -lmseed

all: miniseed2text

miniseed2text: miniseed2text.o
	$(CC) $(CFLAGS) -o $@ miniseed2text.o $(LDFLAGS) $(LDLIBS)

clean:
	rm -f miniseed2text.o miniseed2text

install:
	@echo
	@echo "No install target, copy the executable(s) as needed"
	@echo
