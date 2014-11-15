#ifndef SCREEN_H
#define SCREEN_H

#include "types.h"

class Screen
{
public:
	void enable(void);
	void disable(void);
protected:
	static void cmd(u8 cmd);
	static void data(u8 data);
};

extern Screen screen;

#endif
