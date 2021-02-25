TARGET	=	program.exe
CC	= gcc
CFLAGS	= -ansi -std=c99 -Wall -g 


default: $(TARGET)
all: clean default

OBJECTS	= $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
		$(CC) $(CFLAGS) -c $< -o $@


$(TARGET): $(OBJECTS)
		$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
		-del *.o
		-del $(TARGET)