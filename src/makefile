.SUFFIXES: .c .o
CC          = gcc

CFLAGS      = -O3 -c -Werror
LFLAGS      = -O2 -Werror

INCLUDE     = -I../include
LDFLAGS     = -lpthread
PROJECT     = dfdc

SRC_MAIN   = main.c
MAIN      = main.o
SRCS      = core.c
OBJS      = $(SRCS: .c = .o) 

.c.o:
	$(CC) $(CFLAGS) $(LDFLAGS) $(INCLUDE) $<

all: $(PROJECT)
	
$(PROJECT): $(MAIN) $(OBJS) 
	$(CC) $(SRC_MAIN) -o $@ $(OBJS) $(LDFLAGS) $(INCLUDE)

ifeq ($(PREFIX),)
PREFIX := /usr/local
endif

install: $(PROJECT) $(LIBTARGET)
	install -d $(DESTDIR)$(PREFIX)/bin
	install -m 750 $(PROJECT) $(DESTDIR)$(PREFIX)/bin
uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/$(PROJECT)
	rm -f $(DEAMONDIR)$(SERVICE_FL)
clean:
	rm -rf *.o $(PROJECT)
