env = Environment(
    TOOLCHAIN='toolchain/bin',
    CC='$TOOLCHAIN/arm-none-eabi-gcc',
    CXX='$TOOLCHAIN/arm-none-eabi-g++',
    OBJCOPY='$TOOLCHAIN/arm-none-eabi-objcopy',
    CCLDFLAGS='-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Og',
    CONLYFLAGS='-std=gnu99',
    CANDCXXFLAGS='$CCLDFLAGS -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g3 -fabi-version=0 -fno-exceptions -Wabi',
    LINKFLAGS='$CCLDFLAGS -T mem.ld -T libs.ld -T sections.ld -nostartfiles  --specs=nano.specs -Wl,-Map,${TARGET}.map -Xlinker --gc-sections',
    CFLAGS='$CANDCXXFLAGS $CONLYFLAGS',
    CXXFLAGS='$CANDCXXFLAGS -Wnoexcept -Wctor-dtor-privacy  -Wsign-promo -fno-threadsafe-statics -Wnon-virtual-dtor -fno-rtti -Wstrict-null-sentinel -fno-use-cxa-atexit -std=gnu++11',
    CPPPATH='include:system/include:system/include/cmsis:system/include/stm32f4-hal',
    CPPDEFINES= {
        'OS_USE_TRACE_SEMIHOSTING_STDOUT': None,
        'DEBUG': None,
        'USE_FULL_ASSERT': None,
        'TRACE': None,
        'STM32F407xx': None,
        'USE_HAL_DRIVER': None,
        'HSE_VALUE': '8000000',
    },
)

env.Append(LIBPATH='#.:#ldscripts')

SRC = (
    Glob('src/*.c') + Glob('src/*.cpp') +
    Glob('system/src/stm32f4-hal/*.c') + 
    Glob('system/src/newlib/*.c') + Glob('system/src/newlib/*.cpp') +
    Glob('system/src/diag/*.c') +
    Glob('system/src/cortexm/*.c') +
    Glob('system/src/cmsis/*.c')
)

dc = env.Program('DiveComputer', SRC)
SideEffect('DiveComputer.map', dc)
Default(dc)

Default(env.Command('DiveComputer.hex', 'DiveComputer', '$OBJCOPY -O ihex $SOURCES $TARGET'))

