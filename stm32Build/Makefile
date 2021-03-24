# path to STM32F103 standard peripheral library
STD_PERIPH_LIBS ?= ./

# list of source files
SOURCES  = main.c led/led.c
SOURCES += $(STD_PERIPH_LIBS)Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.c 
START_FILE += $(STD_PERIPH_LIBS)Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/TrueSTUDIO/startup_stm32f10x_hd.s
# name for output binary files
PROJECT ?= led

# compiler, objcopy (should be in PATH)
CC = /home/a/stm32/toolchain/arm-2011.09/bin/arm-none-eabi-gcc
OBJCOPY = /home/a/stm32/toolchain/arm-2011.09/bin/arm-none-eabi-objcopy


# path to st-flash (or should be specified in PATH)
ST_FLASH ?= st-flash

# specify compiler flags
CFLAGS  = -g -O2 -Wall 
CFLAGS += -T./stm32_flash.ld
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork
CFLAGS += -mfloat-abi=softfp -mfpu=fpv4-sp-d16
CFLAGS += -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER
CFLAGS += -Wl,--gc-sections
CFLAGS += -I. -I./led/
CFLAGS += -I$(STD_PERIPH_LIBS)Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/
CFLAGS += -I$(STD_PERIPH_LIBS)Libraries/CMSIS/CM3/CoreSupport
CFLAGS += -I$(STD_PERIPH_LIBS)Libraries/STM32F10x_StdPeriph_Driver/inc

OBJS = $(SOURCES:.c=.o)
START_FILE_OBJ = $(START_FILE:.s=.o)

.PHONY:all burn

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

# flash
burn:
	sudo /home/a/stm32/stm32DownloadTool/test.elf /dev/ttyUSB0 $(PROJECT).hex
