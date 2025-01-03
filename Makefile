SERVER_NAME = server
CLIENT_NAME = client
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L$(LIBFT_DIR) -lft
LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

MINITALK_DIR = mandatory

HEADER_DIR = $(MINITALK_DIR)/inc
HEADER = $(HEADER_DIR)/minitalk.h
INCLUDES = -I$(HEADER_DIR) -I$(LIBFT_DIR)

SERVER_SRCS_DIR = $(MINITALK_DIR)/src_server
SERVER_SRCS_FILES = main.c
SERVER_SRCS = $(addprefix $(SERVER_SRCS_DIR)/, $(SERVER_SRCS_FILES))

CLIENT_SRCS_DIR = $(MINITALK_DIR)/src_client
CLIENT_SRCS_FILES = main.c
CLIENT_SRCS = $(addprefix $(CLIENT_SRCS_DIR)/, $(CLIENT_SRCS_FILES))

OBJS_DIR = $(MINITALK_DIR)/objs
SERVER_OBJS = $(addprefix $(OBJS_DIR)/server_, $(CLIENT_SRCS_FILES:.c=.o))
CLIENT_OBJS = $(addprefix $(OBJS_DIR)/client_, $(CLIENT_SRCS_FILES:.c=.o))

all: $(SERVER_NAME) $(CLIENT_NAME)

clean:
	rm -rf $(SERVER_OBJS) $(CLIENT_OBJS) $(OBJS_DIR)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	rm -rf $(SERVER_NAME) $(CLIENT_NAME) $(LIBFT_LIB)

re: fclean all

$(SERVER_NAME): $(LIBFT_LIB) $(SERVER_OBJS)
	$(CC) $(CFLAGS) $(SERVER_OBJS) $(LDFLAGS) -o $(SERVER_NAME)

$(CLIENT_NAME): $(LIBFT_LIB) $(CLIENT_OBJS)
	$(CC) $(CFLAGS) $(CLIENT_OBJS) $(LDFLAGS) -o $(CLIENT_NAME)

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/server_%.o: $(SERVER_SRCS_DIR)/%.c $(HEADER) | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR)/client_%.o: $(CLIENT_SRCS_DIR)/%.c $(HEADER) | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: all clean fclean re
