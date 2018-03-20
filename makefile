CC=gcc
DEPS = os.h 
OBJ = echo.o directory.o ls.o pinfo.o parse.o main.o execute.o pipe.o redirection.o var_env.o

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

os: $(OBJ)
		gcc -o $@ $^ $(CFLAGS)
