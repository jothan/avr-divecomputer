#include <avr/power.h>
#include <ff.h>
#include "VirtualSerial.h"

#include "spi.h"

void main(void)
{
	bool usb_active=true;
	clock_prescale_set(clock_div_1);
	power_all_disable();

	USB_Init();
	spi_init();

	CDC_Device_CreateStream(&VirtualSerial_CDC_Interface, &USBSerialStream);

	sei();

	for (;;)
	{
		if(usb_active) {
			/* Must throw away unused bytes from the host, or it will lock up while waiting for the device */
			CDC_Device_ReceiveByte(&VirtualSerial_CDC_Interface);

			CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
			USB_USBTask();
		}
	}

	while(1);
}
