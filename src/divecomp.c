#include <avr/power.h>

#include <ff.h>

void main(void)
{
	clock_prescale_set(clock_div_1);

	while(1);
}
