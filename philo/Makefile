# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::   #
#    Makefile                                           :+:      :+:    :+:   #
#                                                     +:+ +:+         +:+     #
#    By: miguel-f <miguel-f@student.42.fr>          +#+  +:+       +#+        #
#                                                 +#+#+#+#+#+   +#+           #
#    Created: 2025/07/21 00:00:00 by miguel-f          #+#    #+#             #
#    Updated: 2025/07/21 00:00:00 by miguel-f         ###   ########.fr       #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -f

SRCDIR = src
INCDIR = include
OBJDIR = obj

SRCS = $(SRCDIR)/main.c \
       $(SRCDIR)/init.c \
       $(SRCDIR)/philosopher.c \
       $(SRCDIR)/monitor.c \
       $(SRCDIR)/utils_lib.c \
       $(SRCDIR)/utils_time.c \
       $(SRCDIR)/utils_print.c \
       $(SRCDIR)/actions.c

OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

INCLUDES = -I$(INCDIR)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
