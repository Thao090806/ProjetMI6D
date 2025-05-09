CC = gcc
CFLAGS = -Wall -Wextra -g
SRC = jeu.c \
      modules/initialisation/initialisation.c \
      modules/script/script.c \
      modules/logique/logique.c \
      modules/combat/combat.c \
      modules/finjeu/finjeu.c
OBJ = $(SRC:.c=.o)
TARGET = cy-fighters.exe

all: $(TARGET)

$(TARGET): $(OBJ)
    $(CC) $(CFLAGS) -o $@ $^

%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    del /Q $(subst /,\,$(OBJ)) $(TARGET)

.PHONY: all clean