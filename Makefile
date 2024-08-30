NAME	=	procgen

LNAME	=	lib$(NAME).so

CC		=	gcc

OBJDIR	=	.tmp

# Project files

SRC		=	$(shell find src -type f -name '*.c') 

OBJ		=	$(SRC:%.c=$(OBJDIR)/%.o)

DSRC	=	$(shell find debug -type f -name '*.c') 

DOBJ	=	$(DSRC:%.c=$(OBJDIR)/%.o)

# Flags

CFLAGS	=	-Wall -Wextra -Iinclude

LDFLAGS	=	-lm -Llib/linked -llinked

DFLAGS	=	-lraylib

# Rules

$(LNAME): lib $(OBJ)
	$(CC) -o $@ $(OBJ) $(CFLAGS) $(LDFLAGS) -shared

all: $(LNAME)

lib:
	$(MAKE) -C lib/linked

clean:
	rm -rf $(OBJDIR)
	$(MAKE) -C lib/linked clean

fclean:	clean
	rm -f $(NAME)
	rm -f $(LNAME)
	$(MAKE) -C lib/linked fclean

re:	fclean all

$(NAME):	lib $(LNAME) $(DOBJ)
	$(CC) -o $@ $(DOBJ) -L. -l$(NAME) $(DFLAGS) $(CFLAGS) $(LDFLAGS)

debug:	$(NAME)

$(OBJDIR)/%.o:	%.c
	@mkdir -p $(@D)
	$(CC) -o $@ -c $< $(CFLAGS) -fPIC

.PHONY: all clean fclean re lib
