CC = gcc

LIBRARYDIRECTORY  = "lib/"

CFLAGS = -O2 -Wall -std=c99 -Wno-missing-braces -I include/

LDFLAGS = -L ${LIBRARYDIRECTORY} -lraylib -lopengl32 -lgdi32 -lwinmm -mwindows

OUTPUT = Counter.exe

SRC = main.c

OBJS = app_icon.o

# Build Target
all: $(OUTPUT)

$(OUTPUT): $(SRC) $(OBJS)
	$(CC) $(CFLAGS) $(SRC) $(OBJS) -o $(OUTPUT) $(LDFLAGS)

# Clean Target
clean:
	rm -f $(OUTPUT)