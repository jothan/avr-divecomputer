#ifndef SDCARD_H
#define SDCARD_H

class SdCard
{
public:
	void enable(void);
	void disable(void);
};

extern SdCard sdcard;

#endif
