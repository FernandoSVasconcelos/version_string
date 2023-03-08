CC := gcc
FLAGS := -c

CSRC := string_main.c

$(CSRC):
	$(CC) $@ -o $(patsubst %.c, %.o, $@)


all: $(CSRC)
.PHONY: all $(CSRC)