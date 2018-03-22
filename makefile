#! /bin/bash

# --------------------------------------------------------------------------------
# file: makefile
# version: 0.3
# author: smaiter
# disc: makefile for stm32f103
# last date mod: 25.01.18
# docs:		
# changes: 
# v.0.1; created 29.11.16
# v.0.2; 29.01.17 переделан запуск линкера, линковка производится gcc. Стандарный
#									линкер ld не подхваьывает libgcc
# v.0.3; 25.01.18 переделан под свои бибилотеки, сделан вывод доп инфо make info и 
#									дисассемблер make disasm
# TODO:	
#				
# --------------------------------------------------------------------------------

# --------------------------------------------------------------------------------
# PROJECT SETTINGS
#
# END OF PROJECT SETTINGS

# --------------------------------------------------------------------------------
# LIBRARIES

# CMSIS 
INCL +=-I inc/

#LCD_1602
#INCL +=-I ./inc/
#PLCD1602 = libs/LCD_1602/

# Delay
#INCL +=-I libs/Delay/
#PDelay = libs/Delay/

#PCMSIS = libs/CMSIS/CM3/DeviceSupport/ST/STM32F10x/
# END OF LIBRARIES 

# --------------------------------------------------------------------------------
# DEFINITIONS
TARGET=main.elf
OBJ=obj/
OUT=out/
SRC=src/
INC=inc/


PREFIX=arm-none-eabi-

CC=$(PREFIX)gcc
AS=$(PREFIX)as
LD=$(PREFIX)ld
OD=$(PREFIX)objdump
OC=$(PREFIX)objcopy
SZ=$(PREFIX)size
NM=$(PREFIX)nm

# END OF DEFINITIONS

# --------------------------------------------------------------------------------
# OBJECT FILES
#OBJECTS += $(OBJ)startup.o
#OBJECTS += $(OBJ)system_stm32f10x.o #system_init; core clock; etc
#OBJECTS += $(OBJ)main.o
#OBJECTS += $(OBJ)delay.o
#OBJECTS += $(OBJ)lcd_1602.o 

# END OF OBJECTS FILES

# --------------------------------------------------------------------------------
# FLAGS
# C flags
#CFLAGS += --specs=nano.specs
CFLAGS+=-O0
CFLAGS+=-g3 #for debagging
CFLAGS+=-mthumb
CFLAGS+=-mcpu=cortex-m3
CFLAGS+=-Wall #enable all warnings
CFLAGS+=-c #only objecting, not linking
CFLAGS+=-ffunction-sections #for clean code, without not used code, use with --gc-sections in linker
CFLAGS+=-fdata-sections #for clean code, without not used code, use with --gc-sections in linker
#CFLAFS += -flto	
#CFLAFS += -pfkegf
#CFLAGS += -fno-common 
#CFLAGS += -nostartfiles
#CFLAFS += -ffreestanding

# asm flags
#ASFLAGS += -O0
ASFLAGS += -g
ASFLAGS += -mthumb
ASFLAGS += -mcpu=cortex-m3
ASFLAGS += -c
ASFLAGS += -Wall

				# linker flags
				#LDFLAGS += -T linker.ld
LDFLAGS += -T linker.ld
				#LDFLAGS += -Map $(OUT)map.map
				#LDFLAGS += -m
				#LDFLAGS += -lm
LDFLAGS += -gc-sections #for cleaning not used code
				#LDFLAGS += -nostdlib



				# END OF FLAGS

.PHONY:all clean disasm info

				#all:$(TARGET).elf

				# # заливка кода в МК
				# load:$(TARGET).bin
				# 		st-flash write $(OUT)$(TARGET).bin 0x08000000
				# # ----------двоичный код для прошивки-----------------------------------
				# $(TARGET).bin:$(TARGET).elf
				# 		$(OC) -O binary $(OUT)$(TARGET).elf $(OUT)$(TARGET).bin
				# # ---------------Линковка (сборка объектных файлов в один elf-файл)--------------
				# $(TARGET).elf:$(BOOT).o $(TARGET).o
				# # За одно создаем файл карты памяти
				# 		$(LD) -Map $(OUT)$(TARGET).map -T $(LINKER)linker.ld -o $(OUT)$@ $(OUT)$(BOOT).o $(OUT)$(TARGET).o
				#  # Узнаем чего и сколько мы наплодили
				#  #	$(SZ) $(OUT)$(TARGET).elf



				# ---------------Компиляция (ассемблирование) исходных кодов----------------------
				# На выходе получаем объектные файлы *.o
				#VPATH := $(LIB) $(SRC)
SRC_FILES:=$(wildcard $(SRC)*.c)
OBJ_FILES=$(OBJ)startup.o $(OBJ)main.o 
OBJ_FILES+=$(addprefix $(OBJ), $(patsubst %c, %o, $(notdir $(SRC_FILES))))

all:separator $(OUT)$(TARGET)
#all:
#	@echo $(OBJ_FILES)
$(OBJ)startup.o: startup.s
	@echo COMPILE $< ---------------------------------------------------------
	$(AS) $(ASFLAGS) $< -o $@
	@echo DONE
	@echo

$(OBJ)main.o: main.c
	@echo COMPILE $< ---------------------------------------------------------
	$(CC) $(CFLAGS) -MD -I $(INC) $< -o $@
	@echo DONE
	@echo 

#$(OBJ)system_stm32f10x.o:system_stm32f10x.c
#	$(CC) $(CFLAGS) -I $(INC) $< -o $@
#	@echo COMPILED: $<
#	@echo --------------------------------------------------------------------
#
$(OBJ)%.o:$(SRC)%.c
	@echo COMPILE $< ---------------------------------------------------------
	$(CC) $(CFLAGS) -I $(INC) $< -o $@
	@echo DONE
	@echo 

#$(OBJ)delay.o: $(SRC)delay.c
#	$(CC) $(CFLAGS) -MD -I $(INC) $< -o $@
#	@echo COMPILED: $<
#	@echo --------------------------------------------------------------------
#
#$(OBJ)lcd_1602.o: $(SRC)lcd_1602.c
#	$(CC) $(CFLAGS) -I $(INC) $< -o $@
#	@echo COMPILED: $<
#	@echo --------------------------------------------------------------------
#
$(OUT)$(TARGET):$(OBJ_FILES) linker.ld 
#	@#$(LD) $(LDFLAGS) -o $@ $(OBJECTS) #-i /usr/lib/gcc/arm-none-eabi/6.2.0/armv7-m/libgcc.a
	@echo CREATE .elf --------------------------------------------------------
	$(LD) $(LDFLAGS) -o $@ $(OBJ_FILES) 
	@echo DONE
	@echo
#	@#@$(LD) $(LDFLAGS) -i /usr/lib/libc.a -o $@ $(OBJECTS)
#	$(CC) $(LDFLAGS) -mthumb -mcpu=cortex-m3 -nostartfiles -o $@ $(OBJ_FILES) 
#	@echo LINKING: $(OBJECTS)
#	@echo --------------------------------------------------------------------
#	@$(OC) -O binary $(OUT)main.elf $(OUT)main.bin
#	@echo BINARY: $(OUT)main.bin
#	@echo --------------------------------------------------------------------
#	@$(OC) -O ihex $(OUT)main.elf $(OUT)main.hex
#	@echo HEX: $(OUT)main.hex
#	@echo --------------------------------------------------------------------
#$(MAIN).o:$(MAIN).c
#		$(CC) -MMD -I $(CMSIS) -nostdlib -nostartfiles -O0 -g -Wall  $(CC_FLAG) -o $(OUT)$@ $<
info:
	@echo SYMBOLS ------------------------------------------------------------
	$(NM) $(OBJ_FILES) $(OUT)$(TARGET) 
	@echo 
	@echo SECTIONS -----------------------------------------------------------
	$(SZ) $(OBJ_FILES) -x $(OUT)$(TARGET)

disasm:
	$(OD) -Sd $(OUT)$(TARGET)
#-Wall -enable warnings

# Извлечение HEX-кода для прошивки
# arm-none-eabi-objcopy -j .flash -j .data_at_ram -O ihex blinky.elf blinky.hex

# Заливаем код в микроконтроллер
#stm32flash -o /dev/ttyS0
#stm32flash -c -w blinky.bin -g 0x0 /dev/ttyS0

# Далее следуют старые (можно сказать архивные) записи, которые уже не нужны, но
# (но кто знает!), может придеся опять к ним когда-нибудь обратиться

# Заливка кода в МК через программатор ST-Link, который расположен на
# плате STM32_VLDISCOVERY

#st-flash read /dev/sg0 flash.bin 0x08000000 0x100
separator:
	@echo
clean:
	@echo '--------------------------------------------------------------------'
#TODO: output in file
	rm -f obj/*.* out/*.*
