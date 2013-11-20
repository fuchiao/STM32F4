all: demos

libstm_build:
	$(MAKE) -C libstm/STM32F4xx_StdPeriph_Driver/build

demos:  libstm_build
	$(MAKE) -C test
	$(MAKE) -C test flash

clean:
	$(MAKE) -C test clean
	$(MAKE) -C libstm/STM32F4xx_StdPeriph_Driver/build clean
