CC = arm-none-eabi-gcc
LIBS =  Common                                              \
		Core\Inc 											\
		Crc 												\
		Drivers\CMSIS\Device\ST\STM32F4xx\Include			\
		Drivers\CMSIS\Include								\
		Drivers\STM32F4xx_HAL_Driver\Inc                    \
		Drivers\STM32F4xx_HAL_Driver\Inc\Legacy				\
		Flash												\
		Host												

VPATH = Core\Src 		\
		Core\Startup    \
		Crc             \
		Flash           \
		Host            \
		Drivers\STM32F4xx_HAL_Driver\Src
		    
TARGET_HW = cortex-m4 
CC_OPTS =  -mcpu=$(TARGET_HW) -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -O0 -ffunction-sections -fdata-sections -std=gnu11 -DUSE_HAL_DRIVER  $(addprefix -I ,$(LIBS))  -Wall
CC_ELF_OPTS = -mcpu=$(TARGET_HW) -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -O0 -ffunction-sections -fdata-sections -DUSE_HAL_DRIVER --specs=nano.specs -T custom_ls_stm32f407.ld  

SRC = main.c \
	  stm32f4xx_hal_msp.c \
	  stm32f4xx_it.c \
	  syscalls.c \
	  system_stm32f4xx.c \
	  stm32f407vg_startup.c \
	  calculate_crc.c \
	  stm32f4xx_hal.c \
	  stm32f4xx_hal_cortex.c \
	  stm32f4xx_hal_crc.c \
	  stm32f4xx_hal_dma.c \
	  stm32f4xx_hal_dma_ex.c \
	  stm32f4xx_hal_exti.c \
	  stm32f4xx_hal_flash.c \
	  stm32f4xx_hal_flash_ex.c \
	  stm32f4xx_hal_flash_ramfunc.c \
	  stm32f4xx_hal_gpio.c \
	  stm32f4xx_hal_pwr.c \
	  stm32f4xx_hal_pwr_ex.c \
	  stm32f4xx_hal_rcc.c \
	  stm32f4xx_hal_rcc_ex.c \
	  stm32f4xx_hal_tim.c \
	  stm32f4xx_hal_tim_ex.c \
	  stm32f4xx_hal_uart.c \
	  erase_flash_memory.c \
	  write_flash_memory.c \
	  parse_message.c \
	  receive_message_from_host.c \
	  send_message_to_host.c
	  
OBJS = $(SRC:.c=.o)

all: 
	echo $(LIBS)
	make my_program.elf
	make my_program.bin
	make my_program.hex

my_program.elf: $(OBJS)
	$(CC) $(CC_ELF_OPTS) $^ -o $@ 
	
include Core\Makefile
include Crc\Makefile
include Drivers\Makefile
include Flash\Makefile
include Host\Makefile

my_program.bin: my_program.elf
	arm-none-eabi-objcopy -O binary my_program.elf my_program.bin

my_program.hex: my_program.elf
	arm-none-eabi-objcopy -O ihex my_program.elf my_program.hex

# Clean rule to remove generated files
clean:
	del *.o my_program.elf my_program.bin my_program.hex