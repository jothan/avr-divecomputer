MCU          = at90usb1286
ARCH         = AVR8
BOARD        = USER
F_CPU        = 16000000
F_USB        = $(F_CPU)
OPTIMIZATION = s
TARGET       = divecomp
FATFS_PATH   = ../lib/fatfs
FATFS_SRC    = $(wildcard $(FATFS_PATH)/src/*.c)

SRC          = $(FATFS_SRC) $(LUFA_SRC_USB) $(LUFA_SRC_USBCLASS) $(LUFA_SRC_PLATFORM) $(wildcard *.c)
#SRC          = $(FATFS_SRC) $(wildcard *.c)
LUFA_PATH    = ../lib/lufa/LUFA
CC_FLAGS     = -DUSE_LUFA_CONFIG_HEADER -I$(FATFS_PATH)/src -Wall -fstrict-aliasing -finline-small-functions -ffreestanding -ffunction-sections -fdata-sections
LD_FLAGS     = -Wl,-gc-sections

# Default target
all:

# Include LUFA build script makefiles
include $(LUFA_PATH)/Build/lufa_core.mk
include $(LUFA_PATH)/Build/lufa_sources.mk
include $(LUFA_PATH)/Build/lufa_build.mk
include $(LUFA_PATH)/Build/lufa_cppcheck.mk
include $(LUFA_PATH)/Build/lufa_doxygen.mk
include $(LUFA_PATH)/Build/lufa_dfu.mk
include $(LUFA_PATH)/Build/lufa_hid.mk
include $(LUFA_PATH)/Build/lufa_avrdude.mk
include $(LUFA_PATH)/Build/lufa_atprogram.mk
