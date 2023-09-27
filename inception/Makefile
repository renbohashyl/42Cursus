SRCS_DIR		= srcs

DOC				= docker compose
DOC_OPT			= -f
DOC_FILE		= $(addprefix $(SRCS_DIR),/docker-compose.yml)

DATAPATH		= ${HOME}/data

DB_NAME			= mariadb
WEB_NAME		= wordpress
SERV_NAME		= nginx

CONTAINER_DB	= $(addprefix $(SRCS_DIR),-$(DB_NAME))
CONTAINER_WEB	= $(addprefix $(SRCS_DIR),-$(WEB_NAME))
CONTAINER_NGIN	= $(addprefix $(SRCS_DIR),-$(SERV_NAME))

TOOLS_DIR		= ./srcs/requirements/tools

install :
	@$(TOOLS_DIR)/for_root_docker_install.sh
	@$(TOOLS_DIR)/docker_rootless_setting.sh

all : build up

MAKE_DIRS :
	@mkdir -p $(DATAPATH)/$(DB_NAME)
	@mkdir -p $(DATAPATH)/$(WEB_NAME)

build : MAKE_DIRS
	@$(DOC) $(DOC_OPT) $(DOC_FILE) build

up :
	@$(DOC) $(DOC_OPT) $(DOC_FILE) up -d --build

down :
	@$(DOC) $(DOC_OPT) $(DOC_FILE) down

clean :
	@$(DOC) $(DOC_OPT) $(DOC_FILE) down

fclean : clean
	@docker image rm -f $(CONTAINER_DB) $(CONTAINER_WEB) $(CONTAINER_NGIN)
	@docker image prune -f

re : fclean
	@make all

.PHONY : all MAKE_DIRS build up down clean fclean re
