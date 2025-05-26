.PHONY : all clean fclean re libft norminette valgrind

NAME = philosophers

# ╭━━━━━━━━━━━━══════════╕出 ❖ BASICS VARIABLES ❖ 力╒═══════════━━━━━━━━━━━━╮ #

CC				:=	cc

CFLAGS			:= -Wall -Wextra -Werror -MMD

RM				:=	rm	-rf

SHOW_MSG_CLEAN	=	true

MAKEFLAGS		+=	--no-print-directory

# ╰━━━━━━━━━━━━━━━━════════════════╛出 ❖ 力╘════════════════━━━━━━━━━━━━━━━━╯ #

# ╭━━━━━━━━━━━━══════════╕出 ❖ FILE TREE ❖ 力╒═══════════━━━━━━━━━━━━╮ #

# directories
D_SRC	=	src/
D_INC	=	inc/
D_OBJ	=	.obj/
D_DEP	=	.dep/
D_LFT	=	libft/

D_UTL	=	$(D_SRC)utils/
D_PAR	=	$(D_SRC)parsing/

D_SRCS	= $(D_SRC) $(D_PAR) $(D_UTL)

# file lists
LST_SRC		=	main.c

LST_PAR		=	check_arg.c

LST_UTL		=	str_is_digit.c

LST_INC		=	philosophers.h

LST_SRCS	=	$(LST_SRC) $(LST_PAR) $(LST_SIG) $(LST_UTL)

INC			=	$(addprefix $(D_INC), $(LST_INC))

OBJ			=	$(addprefix $(D_OBJ), $(notdir $(LST_SRCS:.c=.o)))

DEPS		=	$(addprefix $(D_DEPS), $(notdir $(LST_SRCS:.c=.d)))

LIBS		:=	-L$(D_LFT) -lft

INCS		:=	-I$(D_INC) -I$(D_LFT)

# ╭━━━━━━━━━━━━══════════╕出 ❖ RULES ❖ 力╒═══════════━━━━━━━━━━━━╮ #

all:	$(NAME)

$(NAME):	libft $(OBJ) $(INC) | $(D_OBJ) $(D_DEP) Makefile
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)
	@$(MAKE) clean
	@echo "\e[0;32m$(NAME) program created successfully ! 🧬\e[0m"
	@clear

debug:	libft $(OBJ) $(INC) | $(D_OBJ) $(D_DEP) Makefile
	@$(CC) $(CFLAGS) -g3 $(OBJ) $(LIBS) -o $(NAME)
	@echo "\e[0;32m$(NAME) program created successfully ! 🧬\e[0m"

$(D_OBJ):
	@mkdir -p $@

$(D_DEP):
	@mkdir -p $(D_DEP)

vpath %.c $(D_SRCS)

$(D_OBJ)%.o: %.c | $(D_OBJ) $(D_DEP)
# @echo "Compiling $< → $@"
	@$(CC) $(CFLAGS) -g3 $(INCS) -c $< -o $@
	@mv $(@:.o=.d) $(D_DEP)

-include $(DEPS)

libft:	$(D_LFT)
	$(MAKE) -C $(D_LFT)

clean:
ifeq ($(SHOW_MSG_CLEAN), true)
	@echo "\e[0;36mAll $(NAME) objects have been removed 🧹\e[0m"
endif
	@$(MAKE) -s -C $(D_LFT) clean
	@$(RM) $(D_OBJ) $(D_DEP) $(D_DOC)

fclean:
	@$(MAKE) -s SHOW_MSG_CLEAN=false clean
	@$(MAKE) -s -C $(D_LFT) fclean
	@$(RM) $(NAME)
	@clear
	@echo "\e[0;34m$(NAME) executable deleted ! 🧼\e[0m"

re:
	@$(MAKE) fclean
	@$(MAKE) all
	@echo "\e[0;32m$(NAME) program recreated successfully ! 🫡\e[0m"

norminette:
	norminette $(D_SRC) $(D_INC)

valgrind: supp_file
	@$(MAKE) debug
	@clear
	valgrind							\
		--leak-check=full					\
		--show-leak-kinds=all				\
		--track-origins=yes 				\
		--track-fds=yes						\
		./$(NAME)