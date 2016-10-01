CC=clang
CFLAGS=-O3 -Weverything -g
LIBS=#-lreadline -lpthread -lncursesw
OBJS=main.o
TARGET=a.out

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) -o $(.TARGET) $(OBJS)

$(OBJS): $(.PREFIX).c
	$(CC) $(CFLAGS) -o $(.TARGET) -c $(.PREFIX).c

clean:
	rm -f $(OBJS)
	rm -f $(TARGET)

.PHONY: clean
