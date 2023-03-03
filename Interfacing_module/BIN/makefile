#File name: makefile
#Purpose:   cotains the compiler comands to have the final executable image (.hex)
#Auther:    Ahmed Shawky
#Date:      29/10/2022
#Version:   V2.1

# Include directories
INC_DIR := -I../LIB
INC_DIR += -I../MCAL/MADC
INC_DIR += -I../MCAL/MDIO
INC_DIR += -I../MCAL/MTIMER
INC_DIR += -I../MCAL/MUART
INC_DIR += -I../MCAL/MSPI
INC_DIR += -I../MCAL/MEXTI
INC_DIR += -I../HAL/HLED
INC_DIR += -I../HAL/HPBUTT
INC_DIR += -I../HAL/HSEV_SEG
INC_DIR += -I../HAL/HLCD
INC_DIR += -I../HAL/HKPD

# C source files
C_FILES := ../main.c
C_FILES += ../MCAL/MADC/MADC_program.c
C_FILES += ../MCAL/MDIO/MDIO_program.c
C_FILES += ../MCAL/MTIMER/MTIMER_program.c
C_FILES += ../MCAL/MUART/MUART_program.c
C_FILES += ../MCAL/MSPI/MSPI_program.c
C_FILES += ../MCAL/MEXTI/MEXTI_program.c
C_FILES += ../HAL/HLED/HLED_program.c
C_FILES += ../HAL/HPBUTT/HPBUTT_program.c
C_FILES += ../HAL/HSEV_SEG/HSEV_SEG_program.c
C_FILES += ../HAL/HLCD/HLCD_program.c
C_FILES += ../HAL/HKPD/HKPD_program.c


# Object files
OBJ_FILES := main.o
OBJ_FILES += MADC_program.o
OBJ_FILES += MDIO_program.o
OBJ_FILES += MTIMER_program.o
OBJ_FILES += MUART_program.o
OBJ_FILES += MSPI_program.o
OBJ_FILES += MEXTI_program.o
OBJ_FILES += HLED_program.o
OBJ_FILES += HPBUTT_program.o
OBJ_FILES += HSEV_SEG_program.o
OBJ_FILES += HLCD_program.o
OBJ_FILES += HKPD_program.o

# AVR Controller configuration
CONTROLLER := atmega32
CONTROLLER_CLK := 16000000

# Compiler configuration variables
CC := avr-gcc
COMPILER_OPTIONS := -mmcu=$(CONTROLLER) -DF_CPU=$(CONTROLLER_CLK) -Wall -Os $(INC_DIR)

all: $(C_FILES) clean main.hex

main.elf:
	@echo "Compiling C files......."
	@$(CC) $(COMPILER_OPTIONS) -c $(C_FILES)
	@echo "Linking C files......."
	@$(CC) -Wl,-Map=main.map -mmcu=$(CONTROLLER) $(OBJ_FILES) -o main.elf

main.hex: main.elf
	@echo "Generating Hex file......."
	@avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature main.elf -O ihex main.hex

clean:
	@rm -rf *.hex *.elf *.map *.o	