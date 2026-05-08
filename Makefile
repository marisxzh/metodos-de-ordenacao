# Compilador e Flags
CC       := gcc
CFLAGS   := -Wall -Wextra -Iinclude
LDFLAGS  := -lm
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)
TARGET   := app

# Fontes: Captura o main.c na raiz E todos os .c na pasta src/
SRC      := main.c $(wildcard src/*.c)

# Mapeia os arquivos .c para .o dentro da pasta de objetos
# Usamos patsubst para garantir que o caminho src/ seja preservado no nome
OBJECTS  := $(SRC:%.c=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)

# Regra para criar o executável final
$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)

# Regra para compilar cada arquivo .c em um .o
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all build clean debug release run

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CFLAGS += -DDEBUG -g
debug: all

release: CFLAGS += -O3
release: all

clean:
	rm -rf $(BUILD)

run:
	$(APP_DIR)/$(TARGET)