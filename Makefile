NAME	=	procgen

LNAME	=	lib$(NAME).so

TNAME	=	unit_tests

CC		=	gcc

OBJDIR	=	.tmp

# Project files

SRC		=	$(shell find src -type f -name '*.c') 

OBJ		=	$(SRC:%.c=$(OBJDIR)/%.o)

DSRC	=	$(shell find debug -type f -name '*.c') 

DOBJ	=	$(DSRC:%.c=$(OBJDIR)/%.o)

TSRC	=	$(shell find tests -type f -name '*.c') 

TOBJ	=	$(TSRC:%.c=$(OBJDIR)/%.o)

# Flags

CFLAGS	=	-Wall -Wextra -Iinclude -lm

DFLAGS	=	-lraylib

TFLAGS	=	-lcriterion

# Rules

$(LNAME): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -shared

all: $(LNAME)

clean:
	rm -rf $(OBJDIR)

fclean:	clean
	rm -f $(NAME)
	rm -f $(LNAME)
	rm -f $(TNAME)

re:	fclean all

$(NAME):	$(LNAME) $(DOBJ)
	$(CC) -o $@ $(DOBJ) -L. -l$(NAME) $(DFLAGS) $(CFLAGS)

debug:	$(NAME)

$(TNAME):	$(OBJ) $(TOBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(TFLAGS)

tests_run:	$(TNAME)
	./$(TNAME)

$(OBJDIR)/%.o:	%.c
	@mkdir -p $(@D)
	$(CC) -o $@ -c $< $(CFLAGS) -fPIC

.PHONY: all clean fclean re
