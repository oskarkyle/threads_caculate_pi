CC = gcc
CFLAG = -Wall -O0 -g -pthread
RM = rm -f
MAKE = make 
OBJS = main.o 
NAME = start

%.o : %.c 
	$(CC) -c $(CFLAG) -o $@ $<

all : 
	$(MAKE) $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAG) -o $(NAME) $(OBJS)

run :
	./$(NAME)

clean:
	$(RM) *.o $(NAME)
