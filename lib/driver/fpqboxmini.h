#ifndef DISABLE_DREAMBOX_RC

#ifndef __fpqboxmini_h
#define __fpqboxmini_h

#include <lib/driver/rc.h>

/* some define for protocol st-fpga */
#define MYVERS "0.0.1"  // 25 sept 2009

#define dprintk(args...) \
	do { \
		if (debug) printk("starci2win: " args); \
	} while (0)

#define SUCCESS 0
#define FAIL -1
#define MAJOR_NR                    175
#define LED_MAGIC                   0xBC
#define FPANEL_NUMBER_DEVICES       1
#define DEVICE_NAME					fpanel_0 /* The equivalent in qboxhd is sw0 */
#define FPANEL_PORT5_IRQ			113

/* When the button is released the logical value is 1 (so in the port is 0x80: bit 7),
	when the button is pressed the logical value is 0 (so in te port is 0x00) */
#define BUTTON_PRESSED				0x00	//
#define BUTTON_RELEASED				0x80

typedef struct
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
}Rrgb_Value_t;

typedef struct
{
	Rrgb_Value_t clr;
	unsigned char button;
}Global_Status_t;

/* IOCTL */
#define IOCTL_SET_RGB_COLOR				_IOW(LED_MAGIC, 1, Rrgb_Value_t)
#define IOCTL_READ_BUTTON_STATUS		_IOR(LED_MAGIC, 2, int)
#define IOCTL_READ_GLOBAL_STATUS		_IOR(LED_MAGIC, 3, Global_Status_t)

///* Device */
class eFButtonDevice: public eRCDevice
{
	int last, ccode;
	int iskeyboard;
private:
	void timeOut();
	void repeat();
	int getRepeatDelay();
	int getRepeatRate();
	int getKeyCode(int key);
	const char *getKeyDescription(const eRCKey &key) const;
	int getKeyCompatibleCode(unsigned short rccode) const;
public:
	void handleCode(long code);
	eFButtonDevice(eRCDriver *driver);
	const char *getDescription() const;
};

///* Driver */
class eFButtonDriver: public eRCShortDriver
{
public:
	eFButtonDriver(char * devname);
};

#endif // __fpqboxmini_h

#endif // DISABLE_DREAMBOX_RC
