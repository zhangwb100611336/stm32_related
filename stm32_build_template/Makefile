# path to STM32F103 standard peripheral library
STD_PERIPH_LIBS ?= ../

# list of source files
SOURCES  = main.c
SOURCES += $(STD_PERIPH_LIBS)Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.c
SOURCES += $(STD_PERIPH_LIBS)Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.c
SOURCES += $(STD_PERIPH_LIBS)Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c
#SOURCES += ./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c
#SOURCES += ./Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.cSTART_FILE += ./Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/TrueSTUDIO/startup_stm32f10x_ld.s
START_FILE += $(STD_PERIPH_LIBS)Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/TrueSTUDIO/startup_stm32f10x_hd.s
# name for output binary files
PROJECT ?= led

# compiler, objcopy (should be in PATH)
CC = /home/repo/linux/toolchain/arm-2011.09/bin/arm-none-eabi-gcc
OBJCOPY = /home/repo/linux/toolchain/arm-2011.09/bin/arm-none-eabi-objcopy



# specify compiler flags
CFLAGS  = -g -O2 -Wall 
CFLAGS += -T./stm32_flash.ld
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork
CFLAGS += -mfloat-abi=softfp -mfpu=fpv4-sp-d16
CFLAGS += -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER
CFLAGS += -Wl,--gc-sections
CFLAGS += -I.
CFLAGS += -I$(STD_PERIPH_LIBS)Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/
CFLAGS += -I$(STD_PERIPH_LIBS)Libraries/CMSIS/CM3/CoreSupport
CFLAGS += -I$(STD_PERIPH_LIBS)Libraries/STM32F10x_StdPeriph_Driver/inc

OBJS = $(SOURCES:.c=.o)
START_FILE_OBJ = $(START_FILE:.s=.o)

.PHONY:all

all:obj $(PROJECT).elf 

# compile

obj:$(OBJS) $(START_FILE_OBJ)

$(OBJS):%.o:%.c
	$(CC) $(CFLAGS) -c $<  -o  $@

$(START_FILE_OBJ):%.o:%.s
	$(CC) -c $< -o $@

$(PROJECT).elf: $(OBJS)
	$(CC) $(CFLAGS) $(START_FILE_OBJ)  $^ -o $@
	$(OBJCOPY) -O ihex $(PROJECT).elf $(PROJECT).hex
	$(OBJCOPY) -O binary $(PROJECT).elf $(PROJECT).bin

# remove binary files
clean:
	rm -f *.o *.elf *.hex *.bin

