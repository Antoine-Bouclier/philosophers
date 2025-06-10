NAME = philosophers

CC      := cc
CFLAGS  := -Wall -Wextra -Werror -MMD -pthread
RM      := rm -rf

D_SRC   := src/
D_INC   := inc/
D_OBJ   := .obj/
D_DEP   := .dep/

D_SRCS  := $(D_SRC)

LST_SRC :=	exit.c ft_atoi.c init.c main.c philo_actions.c routine.c valid_arg.c

LST_SRCS := $(LST_SRC)
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