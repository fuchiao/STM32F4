EXECUTABLE=test.elf
BIN_IMAGE=test.bin

CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy

CFLAGS=-g -O0 -mlittle-endian -mthumb
CFLAGS+=-mcpu=cortex-m4
CFLAGS+=-mfpu=fpv4-sp-d16 -mfloat-abi=hard
CFLAGS+=-ffreestanding #-nostdlib

# to run from FLASH
CFLAGS+=-Wl,-T,stm32_flash.ld

CFLAGS+=-I./
CFLAGS+=-I./lwip-1.4.1/src/include
CFLAGS+=-I./lwip-1.4.1/src/include/lwip
CFLAGS+=-I./lwip-1.4.1/src/include/ipv4
CFLAGS+=-I./lwip-1.4.1/port/STM32F4x7
CFLAGS+=-I./lwip-1.4.1/port/STM32F4x7/Standalone

# stm32f4_discovery lib
CFLAGS+=-I../libstm/STM32F4xx_StdPeriph_Driver/inc
CFLAGS+=-I../libstm/CMSIS/Device/ST/STM32F4xx/Include/
CFLAGS+=-I../libstm/CMSIS/Include/
#CFLAGS+=-I../libstm/STM32F4xx_StdPeriph_Driver/inc/device_support
#CFLAGS+=-I../libstm/STM32F4xx_StdPeriph_Driver/inc/core_support

#STM32_USB_Device_Library
#CFLAGS+=-I../libstm/STM32_USB_Device_Library/Class/hid/inc
#CFLAGS+=-I../libstm/STM32_USB_Device_Library/Core/inc

#STM32_USB_OTG_Driver
#CFLAGS+=-I../libstm/STM32_USB_OTG_Driver/inc

#STM32F4xx_StdPeriph_Driver\inc
#CFLAGS+=-I../libstm/STM32F4xx_StdPeriph_Driver/inc

#Utilities
#CFLAGS+=-I../libstm/Utilities/STM32F4-Discovery



all: $(BIN_IMAGE)

$(BIN_IMAGE): $(EXECUTABLE)
	$(OBJCOPY) -O binary $^ $@

$(EXECUTABLE): main.c system_stm32f4xx.c startup_stm32f40xx.s syscalls.c stm32f4x7_eth.c stm32f4x7_eth_bsp.c udp_echoserver.c \
	netconf.c stm32f4xx_it.c \
	lwip-1.4.1/src/core/def.c \
	lwip-1.4.1/src/core/dhcp.c \
	lwip-1.4.1/src/core/dns.c \
	lwip-1.4.1/src/core/init.c \
	lwip-1.4.1/src/core/pbuf.c \
	lwip-1.4.1/src/core/raw.c \
	lwip-1.4.1/src/core/stats.c \
	lwip-1.4.1/src/core/sys.c \
	lwip-1.4.1/src/core/netif.c \
	lwip-1.4.1/src/core/mem.c \
	lwip-1.4.1/src/core/memp.c \
	lwip-1.4.1/src/core/tcp.c \
	lwip-1.4.1/src/core/tcp_in.c \
	lwip-1.4.1/src/core/tcp_out.c \
	lwip-1.4.1/src/core/timers.c \
	lwip-1.4.1/src/core/udp.c \
	lwip-1.4.1/src/core/ipv4/autoip.c \
	lwip-1.4.1/src/core/ipv4/icmp.c \
	lwip-1.4.1/src/core/ipv4/igmp.c \
	lwip-1.4.1/src/core/ipv4/inet.c \
	lwip-1.4.1/src/core/ipv4/inet_chksum.c \
	lwip-1.4.1/src/core/ipv4/ip.c \
	lwip-1.4.1/src/core/ipv4/ip_addr.c \
	lwip-1.4.1/src/core/ipv4/ip_frag.c \
	lwip-1.4.1/src/netif/ethernetif.c \
	lwip-1.4.1/port/STM32F4x7/Standalone/ethernetif.c \
	lwip-1.4.1/src/netif/etharp.c
#	../libstm/Utilities/STM32F4-Discovery/stm32f4_discovery.c
	$(CC) $(CFLAGS) $^ -o $@  -L../libstm/STM32F4xx_StdPeriph_Driver/build \
		-lSTM32F4xx_StdPeriph_Driver 

clean:
	rm -rf $(EXECUTABLE)
	rm -rf $(BIN_IMAGE)

flash:
	st-flash write $(BIN_IMAGE) 0x8000000

.PHONY: all clean
