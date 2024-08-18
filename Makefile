NAME	=	procgen

CC		=	gcc

OBJDIR	=	.tmp

# Project files

SRC		=	$(shell find src -type f -name '*.c') 

OBJ		=	$(SRC:%.c=$(OBJDIR)/%.o)

# Flags

CFLAGS	=	-Wall -Wextra -Iinclude -lm

# Rules

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

all: $(NAME)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

$(OBJDIR)/%.o:	%.c
	@mkdir -p $(@D)
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: all clean fclean re
