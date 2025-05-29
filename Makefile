NAME = philosophers

CC      := cc
CFLAGS  := -Wall -Wextra -Werror -MMD -pthread
RM      := rm -rf

D_SRC   := src/
D_INC   := inc/
D_OBJ   := .obj/
D_DEP   := .dep/

D_UTL   := $(D_SRC)utils/
D_PAR   := $(D_SRC)parsing/
D_PRT   := $(D_SRC)print/
D_RTN   := $(D_SRC)routine/
D_INIT  := $(D_SRC)init/
D_SRCS  := $(D_SRC) $(D_PAR) $(D_UTL) $(D_PRT) $(D_INIT) $(D_RTN)

LST_SRC :=	main.c

LST_INIT :=	init_args.c \
			init_philo.c \
			init_time.c \
			handle_thread.c

LST_PAR :=	check_arg.c

LST_RTN :=	routine.c \
			philo_actions.c

LST_UTL :=	str_is_digit.c \
			ft_atoi.c \
			free.c

LST_PRT :=	print.c

LST_SRCS := $(LST_SRC) $(LST_PAR) $(LST_INIT) $(LST_RTN) $(LST_UTL) $(LST_PRT)
INC      := $(addprefix $(D_INC), philosophers.h)

OBJ  := $(addprefix $(D_OBJ), $(notdir $(LST_SRCS:.c=.o)))
DEPS := $(addprefix $(D_DEP), $(notdir $(LST_SRCS:.c=.d)))

INCS := -I$(D_INC)

vpath %.c $(D_SRCS)

all: $(NAME)

$(NAME): $(OBJ) | $(D_OBJ) $(D_DEP)
	@$(CC) $(CFLAGS) $(OBJ) -o $@
	@echo "$(GREEN)$(NAME) program created successfully ! 🧬$(RESET)"

$(D_OBJ):
	@mkdir -p $@

$(D_DEP):
	@mkdir -p $@

$(D_OBJ)%.o: %.c | $(D_OBJ) $(D_DEP)
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@
	@mv $(@:.o=.d) $(D_DEP)

-include $(DEPS)

clean:
	@$(RM) $(D_OBJ) $(D_DEP)
	@echo "$(RED)Cleaned$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)Executable removed$(RESET)"

re: fclean all
