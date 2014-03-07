#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <libusb-1.0/libusb.h>

#define DEV_VID  0x04D8
#define DEV_PID  0xE11C
#define DEV_INTF 0

struct devinf {
	unsigned char previus[7];
	unsigned char devcode[8];
	unsigned char serial[24];
	unsigned char endchar[1];
} devinfo;

int main(int argc, char * argv[]) 
{
	libusb_device_handle * handle;

	int buffer_size = 48;
	unsigned char data[buffer_size];
	unsigned char command_getinfo[] = {0x00, 0x00, 0x00, 0x00, 0x00};
	unsigned char command_getinfo[] = {0x00, 0x00, 0x00, 0x00, 0x00};
	int actual_length;
	int result = 0;

	libusb_init(NULL);
	libusb_set_debug(NULL, 3);
	handle = libusb_open_device_with_vid_pid(NULL, DEV_VID, DEV_PID);

	if (handle == NULL) {
	    printf("Can't find device !\n");
	    libusb_exit(NULL);
	 	return 0;
	} else {
		result = libusb_bulk_transfer(handle, LIBUSB_ENDPOINT_OUT + 1, command_getinfo, sizeof(command_getinfo), &actual_length, 0);
		if(result == 0 && actual_length == sizeof(command_getinfo)) {
			result = libusb_bulk_transfer(handle, LIBUSB_ENDPOINT_IN + 1, data, sizeof(data), &actual_length, 0);
			memcpy(&devinfo, &data, actual_length);
			if(result == 0) {
				//printf("previus: %s\n", devinfo.previus);
				printf("devcode: %s\n", devinfo.devcode);
				printf("serial:  %s\n", devinfo.serial);
				//printf("endchar: %s\n", devinfo.endchar);
			} else {
				printf("Error read\n");
			}
		} else {
			printf("Error send command\n");
		}
	}

	libusb_attach_kernel_driver(handle, DEV_INTF);
	libusb_close(handle);
	libusb_exit(NULL);

	return 0;
}