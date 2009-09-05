.PHONY : all clean library

CFLAGS := -Wall -D_GNU_SOURCE
OBJS := $(addsuffix .o, $(basename $(wildcard *.c)))
APP := ElfSword
LIBNAME := elfsword.a

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(APP)

clean:
	rm -f $(OBJS) $(APP) $(OBJS:.o=.d) $(LIBNAME)
	rm -f $(DOCDIR)

%.d: %.c
	$(CC) -MM -MF $@ $<

library: all
	ar rcs $(LIBNAME) $(subst main.o,, $(OBJS))

-include $(OBJS:.o=.d)
