#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "libusb-1.0/libusb.h"

#define DEV_VID 0x04D8
#define DEV_PID 0xE11C
#define DEV_INTF 0

int main(int argc, char * argv[])
{
	libusb_device_handle * handle;

	libusb_init(NULL);
	libusb_set_debug(NULL, 3);
	handle = libusb_open_device_with_vid_pid(NULL, DEV_VID, DEV_PID);

	if (handle == NULL) {
	    printf("Can't find device!\n");
	    libusb_exit(NULL);
	 	return 0;
	}

	libusb_attach_kernel_driver(handle, DEV_INTF);
	libusb_close(handle);
	libusb_exit(NULL);

	return 0;
}