## Cross-compilation commands 
CC      := arm-none-eabi-gcc
LD      := arm-none-eabi-ld
AS      := arm-none-eabi-as
OBJCOPY := arm-none-eabi-objcopy
SIZE    := arm-none-eabi-size
LOAD		:= ST-LINK_CLI

#Add include driectory of header file
PROJ_DIR          := .
PROJ_NAME         := test
PATH_OUPUT        := $(PROJ_DIR)/output

INCLUDE_DIRS      := $(PROJ_DIR)/include
SRC_DIRS          := $(PROJ_DIR)/source
OBJ_DIRS	        := $(PROJ_DIR)/object
LINKER            := $(PROJ_DIR)/linker/stm32f030k6t6.ld
STARTUP_FILE      := $(PROJ_DIR)/startup/stm32f030k6t6_startup.c
#
INCLUDE_FILES := $(foreach INCLUDE_DIRS, $(INCLUDE_DIRS), $(wildcard $(INCLUDE_DIRS)/*))
SRC_FILE      := $(foreach SRC_DIRS, $(SRC_DIRS), $(wildcard $(SRC_DIRS)/*.c))
#Object
OBJ_STARTUP   := startup_file.o
OBJ_FILE      := $(notdir $(SRC_FILE))
OBJ_FILE      := $(subst .c,.o, $(OBJ_FILE))
PATH_OBJ      := $(foreach OBJ_FILE, $(OBJ_FILE), $(OBJ_DIRS)/$(OBJ_FILE))
PATH_OBJ      += $(OBJ_DIRS)/$(OBJ_STARTUP)

OUTPUT_FILE   := $(wildcard $(PATH_OUPUT)/*)

## Platform and optimization options
CFLAGS = -mcpu=cortex-m0 -mthumb -O0 -g3 -c -I$(INCLUDE_DIRS)
LFLAGS = -T $(LINKER) -Map $(PATH_OUPUT)/out.map

vpath %.c $(SRC_DIRS)
vpath %.h $(INCLUDE_DIRS)

## Rules
all: out.elf out.bin out.hex size

out.elf: $(OBJ_FILE) $(LINKER) $(OBJ_STARTUP)
	$(LD) $(LFLAGS) -o $(PATH_OUPUT)/out.elf $(PATH_OBJ)

out.hex: out.elf
	$(OBJCOPY) -O ihex "$(PATH_OUPUT)/out.elf" "$(PATH_OUPUT)/out.hex"

out.bin: out.elf
	$(OBJCOPY) -O binary "$(PATH_OUPUT)/out.elf" "$(PATH_OUPUT)/out.bin"

%.o: %.c $(INCLUDE_FILES)
	$(CC) $(CFLAGS) -c $< -o $(OBJ_DIRS)/$@

$(OBJ_STARTUP): $(STARTUP_FILE) $(INCLUDE_FILES)
	$(CC) $(CFLAGS) -c $< -o $(OBJ_DIRS)/$@
	
size: $(PATH_OUPUT)/out.elf
	$(SIZE) $< 

run: $(PATH_OUPUT)/out.hex
	$(LOAD) -p "$(PATH_OUPUT)/out.hex" 0x08000000 -rst

clean:
	rm -r -f $(PATH_OBJ) $(OUTPUT_FILE)

print-%:
	echo $($(subst print-,,$@))