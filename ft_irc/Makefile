TARGET = ircserv

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic-errors
CPPFLAGS = -MD
LDFLAGS =

RM = rm -f

SRCS = $(wildcard *.cpp)

OBJS = $(SRCS:.cpp=.o)

DEPS = $(SRCS:.cpp=.d)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(TARGET)

re: fclean
	@make all

-include $(DEPS)

.PHONY: all clean fclean re
