#include <avr/power.h>
#include <ff.h>
#include "VirtualSerial.h"

#include "spi.h"
#include "sdcard.h"

const spi_device_t* const spi_devices[] = {&sdcard_device};

void main(void)
{
	bool usb_active=true;
	clock_prescale_set(clock_div_1);
	power_all_disable();

	USB_Init();
	spi_init(sizeof(spi_devices));

	CDC_Device_CreateStream(&VirtualSerial_CDC_Interface, &USBSerialStream);
	spi_enable();
	spi_select(&sdcard_device);

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
