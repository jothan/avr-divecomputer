#ifndef DEPTH_H
#define DEPTH_H

#include "types.h"

enum DepthSampling: unsigned {
	OSR_256 = 0,
    OSR_512 = 1,
	OSR_1024 = 2,
	OSR_2048 = 3,
	OSR_4096 = 4,
};


class DepthSensor {
public:
	DepthSensor();
	void enable(void);
	void disable(void);
	void reset(void);
	static u8 crc4(const u8 *data, size_t size);
	void convert_values(u32 pressure_in, u32 temperature_in, i32 &pressure_out, i32 &temperature_out);
	u32 sample_temperature(DepthSampling osr);
	u32 sample_pressure(DepthSampling osr);
protected:
	u8 prom[16];
	SPI_HandleTypeDef spi;
	void pin_enable(void);
	void pin_disable(void);
	void read_prom(void);
	void cs(bool);
	u32 sample(u8 cmd, DepthSampling osr);
};

#endif
