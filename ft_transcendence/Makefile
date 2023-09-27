SRCS_DIR		= ./

DOC				= docker compose
DOC_OPT			= -f
DOC_FILE		= $(addprefix $(SRCS_DIR),/docker-compose.yml)

DATAPATH		= ./apprun

DB_NAME			= database
SERVER_NAME		= backend
OBJS			= dist
PACKAGES		= node_modules
WEB_NAME		= frontend

INIT_FILE		= .confirm

ORG_DEV_CONFIG	= $(addprefix ${HOME},/tscen_configs)
CONFIG_DIR		= $(addprefix $(DATAPATH),/$(WEB_NAME)/config/)

ifeq ($(shell uname), Darwin)
	ifeq ($(wildcard $(INIT_FILE)),)
		TARGET = MacBuild
	else
		TARGET = LinuxBuild
	endif
else
	TARGET = LinuxBuild
endif

all: $(TARGET)

MacBuild: DOCKER_CONFIG | WAIT_FOR_DOCKER | build up
LinuxBuild: WAIT_FOR_DOCKER | build up

WAIT_FOR_DOCKER :
	@while ! docker info > /dev/null 2>&1; do echo "Waiting for Docker to start..."; sleep 5; done

DOCKER_CONFIG :
	@./_docker.sh
	@touch $(INIT_FILE)

MAKE_DIRS :
	@mkdir -p $(DATAPATH)/$(DB_NAME)
	@mkdir -p $(DATAPATH)/$(SERVER_NAME)
	@mkdir -p $(DATAPATH)/$(WEB_NAME)

build : MAKE_DIRS
	@$(DOC) $(DOC_OPT) $(DOC_FILE) build

config :
	@cp -f $(ORG_DEV_CONFIG)/development.yml $(CONFIG_DIR)
	@cp -f $(ORG_DEV_CONFIG)/.env .

up :
	@$(DOC) $(DOC_OPT) $(DOC_FILE) up -d --build --wait

down :
	@$(DOC) $(DOC_OPT) $(DOC_FILE) down

clean :
	@$(DOC) $(DOC_OPT) $(DOC_FILE) down

fclean : clean
	@docker system prune -a -f
	@rm -rf $(DATAPATH)/$(SERVER_NAME)/$(PACKAGES)
	@rm -rf $(DATAPATH)/$(SERVER_NAME)/$(OBJS)
	@rm -rf $(DATAPATH)/$(WEB_NAME)/$(PACKAGES)
	@rm -rf $(DATAPATH)/$(DB_NAME)

re : fclean
	@make LinuxBuild

.PHONY : all tempNest build up down clean fclean re
