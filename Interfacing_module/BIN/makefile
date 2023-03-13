#File name: makefile
#Purpose:   cotains the compiler comands to have the final executable image (.hex)
#Auther:    Ahmed Shawky
#Date:      13/3/2023
#Version:   V2.4

# Include directories
INC_DIR := -I../LIB
INC_DIR += -I../MCAL/MDIO
INC_DIR += -I../MCAL/MTIMER
INC_DIR += -I../HAL/HGLCD

# C source files
C_FILES := ../APP/main.c
C_FILES += ../MCAL/MDIO/MDIO_program.c
C_FILES += ../MCAL/MTIMER/MTIMER_program.c
C_FILES += ../HAL/HGLCD/HGLCD_program.c

# Object files
OBJ_FILES := main.o
OBJ_FILES += MDIO_program.o
OBJ_FILES += MTIMER_program.o
OBJ_FILES += HGLCD_program.o

# AVR Controller configuration
CONTROLLER := atmega32
CONTROLLER_CLK := 16000000

# Compiler configuration variables
CC := avr-gcc
COMPILER_OPTIONS := -mmcu=$(CONTROLLER) -DF_CPU=$(CONTROLLER_CLK) -Wall -Os $(INC_DIR)

# Elf and Hex files
ELF_FILE := main.elf
HEX_FILE := main.hex

############################################ Rules ############################################

all: $(C_FILES) clean main.hex

main.elf:
	@echo "Compiling C files......."
	@$(CC) $(COMPILER_OPTIONS) -c $(C_FILES)
	@echo "Linking C files......."
	@$(CC) -Wl,-Map=main.map -mmcu=$(CONTROLLER) $(OBJ_FILES) -o main.elf

main.hex: main.elf
	@echo "Generating Hex file......."
	@avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature main.elf -O ihex main.hex

flash: $(HEX_FILE)
	@echo "Flashing software......."
	@avrdude -c usbasp -p atmega32 -U flash:w:$(HEX_FILE)

clean:
	@rm -rf *.hex *.elf *.map *.o