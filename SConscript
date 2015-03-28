env = Environment(
    TOOLCHAIN='toolchain/bin',
    CC='$TOOLCHAIN/arm-none-eabi-gcc',
    CXX='$TOOLCHAIN/arm-none-eabi-g++',
    RANLIB='$TOOLCHAIN/arm-none-eabi-ranlib',
    AR='$TOOLCHAIN/arm-none-eabi-ar',
    OBJCOPY='$TOOLCHAIN/arm-none-eabi-objcopy',
    CCLDFLAGS='-mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Og',
    CONLYFLAGS='-std=gnu11',
    CANDCXXFLAGS='$CCLDFLAGS -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g3 -fabi-version=0 -fno-exceptions -Wabi',
    LINKFLAGS='$CCLDFLAGS -T mem.ld -T libs.ld -T sections.ld -nostartfiles --specs=nano.specs -Wl,--gc-sections -u _printf_float',
    CFLAGS='$CANDCXXFLAGS $CONLYFLAGS',
    CXXFLAGS='$CANDCXXFLAGS -Wnoexcept -Wctor-dtor-privacy  -Wsign-promo -fno-threadsafe-statics -Wnon-virtual-dtor -fno-rtti -Wstrict-null-sentinel -fno-use-cxa-atexit -std=gnu++11',
    CPPPATH=[
        'include',
        'system/include/diag',
        'system/include',
        'system/include/cmsis',
        'system/include/stm32f4-hal',
        'lib/u8glib/csrc',
        'lib/fatfs/src',
    ],
    CPPDEFINES= {
        'OS_USE_TRACE_SEMIHOSTING_STDOUT': None,
        'DEBUG': None,
        'USE_FULL_ASSERT': None,
        'TRACE': None,
        'STM32F407xx': None,
        'USE_HAL_DRIVER': None,
        'HSE_VALUE': '8000000',
    },
    LIBPATH=['.', '#system/ldscripts', '#system/led-test/ldscripts'],
    OPENOCD_FLAGS='-f board/stm32f4discovery.cfg -c init'
)


env.Library('runtime',
    Glob('system/src/cortexm/*.c') +
    Glob('system/src/diag/*.c') +
    Glob('system/src/newlib/*.cpp') +
    Glob('system/src/stm32f4-hal/*.c') +
    Glob('lib/fatfs/src/*.c') +
    Glob('lib/fatfs/src/option/unicode.c')
)

env.Library('runtimenogc',
    # The following system files are not tolerant to linker GC.
    Glob('system/src/cmsis/*.c') +
    Glob('system/src/newlib/*.c')
)

u8env = env.Clone()
u8env.Append(CANDCXXFLAGS=' -Wno-unused-parameter -Wno-missing-declarations -Wno-unused-variable -Wno-unused-function')
u8env.Library('u8glib', Glob('lib/u8glib/csrc/*') + Glob('lib/u8glib/sfntsrc/*.c'))

Default(env.Command('DiveComputer.hex', 'DiveComputer', '$OBJCOPY -O ihex $SOURCES $TARGET'))
upload = env.Command('upload_phony', 'DiveComputer.hex', 'openocd $OPENOCD_FLAGS -c "reset halt" -c "flash write_image erase ${SOURCES}" -c "verify_image ${SOURCES}" -c shutdown')
env.Alias('upload', 'upload_phony')

run = env.Command('run_phony', 'DiveComputer.hex', 'openocd $OPENOCD_FLAGS -c "reset halt" -c "arm semihosting enable" -c "reset run"')
env.Alias('run', 'run_phony')

attach = env.Command('attach_phony', 'DiveComputer.hex', 'openocd $OPENOCD_FLAGS -c "reset halt" -c "arm semihosting enable"')
env.Alias('attach', 'attach_phony')

SideEffect('openocd', upload + run + attach)

env.Program('DiveComputer', Glob('src/*.c') + Glob('src/*.cpp'), LIBS=['runtime', 'runtimenogc', 'u8glib', 'm'], LINKFLAGS='$LINKFLAGS -Wl,--whole-archive -lruntimenogc -Wl,--no-whole-archive')
