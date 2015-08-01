#ifndef TIMER_H
#define TIMER_H

#include <stddef.h>

#include "types.h"

#define TIMER_WHEEL_SLOTS 64

typedef void timer_callback_t(void *arg);

class TimerItem
{
public:
	TimerItem() {
		active = false;
	}
	timer_callback_t *callback;
	void *arg;

protected:
	friend class TimerWheel;
	TimerItem *next;
	u32 rot;
	u32 reload;
	bool active;
};

class TimerWheel
{
public:
	TimerWheel();
	void tick(void);
	void schedule(TimerItem *item, u32 ticks, bool reload);
	bool cancel(TimerItem *item);
protected:
	size_t current_slot;
	TimerItem *slots[TIMER_WHEEL_SLOTS];
};

extern TimerWheel main_timer;

#endif
