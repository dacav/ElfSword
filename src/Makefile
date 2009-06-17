.PHONY : all clean

CFLAGS := -Wall -D_GNU_SOURCE
OBJS := $(addsuffix .o, $(basename $(wildcard *.c)))
APP := test

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(APP)

clean:
	rm -f $(OBJS) $(APP) $(OBJS:.o=.d)
	rm -f $(DOCDIR)

%.d: %.c
	$(CC) -MM -MF $@ $<

-include $(OBJS:.o=.d)
