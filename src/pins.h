#ifndef PINS_H
#define PINS_H

#define SDCARD_CS C,0
#define SCREEN_CS C,1
#define SENSOR_CS C,2


#define DDR(p) (DDR ## p)
#define PORT(p) (PORT ## p)
#define PIN(p) (PIN ## p)

// An extra indirection level is needed to split the macro arguments.
#define PIN_OUTPUT(pb) _PIN_OUTPUT(pb)
#define _PIN_OUTPUT(p, b) (DDR(p) |= _BV(b))

#define PIN_INPUT(pb) _PIN_INPUT(pb)
#define _PIN_INPUT(p, b) (DDR(p) &= ~_BV(b))

#define PIN_SET(pb) _PIN_SET(pb)
#define _PIN_SET(p, b) (PORT(p) |= _BV(b))

#define PIN_CLEAR(pb) _PIN_CLEAR(pb)
#define _PIN_CLEAR(p, b) (PORT(p) &= ~_BV(b))

#endif
