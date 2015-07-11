#ifndef SCREEN_H
#define SCREEN_H

#include <u8g.h>

#include "types.h"

class Screen
{
public:
	Screen();
	void enable(void);
	u8g_t u8g;
protected:
	static const u8 WIDTH = 128;
	static const u8 HEIGHT = 64;
	static const u8 PAGE_HEIGHT = 8;
	void dev_init(void);
	static void cmd(u8 cmd);
	static void data(u8 data);
	static u8 u8g_fn(u8g_t *u8g, u8g_dev_t *dev, u8 msg, void *arg);

	u8g_pb_t u8g_pb;
	u8g_dev_t u8g_dev;
	uint8_t u8g_buf[WIDTH/4*PAGE_HEIGHT];

	inline void set_row(u8 row)
	{
		cmd(0x75);
		cmd(row);
		cmd(HEIGHT-1);
	}

	inline void set_column(u8 col)
	{
		cmd(0x15);
		cmd(col);
		cmd(WIDTH-1);
	}
};

extern Screen screen;

#endif
