CC=gcc
CFLAGS= -I/usr/include/libxml2 -W -Wall -pedantic 
LDFLAGS= -lSDL -lSDL_ttf -lSDL_gfx -lxml2 -lm -lSDL_image 
EXEC= cproj
HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

cproj: $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)

r%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
