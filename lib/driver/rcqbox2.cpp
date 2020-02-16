#include <lib/driver/rcinput.h>
#include <lib/base/eerror.h>
#include <sys/ioctl.h>
#include <linux/input.h>
#include <sys/stat.h>
#include <lib/base/ebase.h>
#include <lib/base/init.h>
#include <lib/base/init_num.h>
#include <lib/driver/input_fake.h>
#include <sys/time.h>

#include "rcqbox2.h"

/* ----------------------- qbox fernbedienung ---------------------- */
void eRCDeviceQBox2::handleCode(long rccode)
{
	unsigned int rc_id = rccode & 0x00FF0000;
	unsigned int buttoncode = rccode & 0x0000FFFF;
	if (buttoncode == 0x00FF) // break code
	{
		//timeout.stop();
		//repeattimer.stop();
		timeOut();
		return;
	}
	//timeout.start(1500, 1);
	int old=ccode;
	ccode=rccode;
	if ((old!=-1) && ( ((old&0x7FFF)!=(rccode&0x7FFF)) || !(rccode&0x8000)) )
	{
		//repeattimer.stop();
		/*emit*/ input->keyPressed(eRCKey(this, getKeyCompatibleCode(old&0xFF7FFF), eRCKey::flagBreak));
	}
	if ((old^buttoncode)&0x7FFF)
	{
		input->keyPressed(eRCKey(this, getKeyCompatibleCode(rccode&0xFF7FFF), 0));
//		usleep(500);
//		input->keyPressed(eRCKey(this, getKeyCompatibleCode(rccode&0x7FFF), eRCKey::flagBreak));
		/*unsigned char p=0;
		for(p=0;p<1;p++)
		{
			usleep(500);
			input->keyPressed(eRCKey(this, getKeyCompatibleCode(rccode&0x7FFF), eRCKey::flagRepeat));
		}
		usleep(500);
		input->keyPressed(eRCKey(this, getKeyCompatibleCode(rccode&0x7FFF), eRCKey::flagBreak));*/

	}
	//else if (rccode&0x8000 && !repeattimer.isActive())
	{
// eRCInput::getInstance()->config.rdelay, eRCInput::getInstance()->config.rrate);
		//repeattimer.start(eRCInput::getInstance()->config.rdelay, 1);
	}

}

void eRCDeviceQBox2::timeOut()
{
	int oldcc=ccode;
	ccode=-1;
	//repeattimer.stop();
	if (oldcc!=-1)
	{
		input->keyPressed(eRCKey(this, getKeyCompatibleCode(oldcc&0xFF7FFF), eRCKey::flagBreak));
	}
}

void eRCDeviceQBox2::repeat()
{
	if (ccode!=-1)
	{
		input->keyPressed(eRCKey(this, getKeyCompatibleCode(ccode&0xFF7FFF), eRCKey::flagRepeat));
	}
	//repeattimer.start(eRCInput::getInstance()->config.rrate, 1);
}

eRCDeviceQBox2::eRCDeviceQBox2(eRCDriver *driver)
			: eRCDevice("QBoxHD Remote Control", driver), iskeyboard(false)
{
	ccode=-1;
	//CONNECT(timeout.timeout, eRCDeviceQBox2::timeOut);
	//CONNECT(repeattimer.timeout, eRCDeviceQBox2::repeat);
}

const char *eRCDeviceQBox2::getDescription() const
{
	return "QBoxHD Remote Control";
}

const char *eRCDeviceQBox2::getKeyDescription(const eRCKey &key) const
{
	switch (key.code)
	{
	case 0x00: return "0";
	case 0x01: return "1";
	case 0x02: return "2";
	case 0x03: return "3";
	case 0x04: return "4";
	case 0x05: return "5";
	case 0x06: return "6";
	case 0x07: return "7";
	case 0x08: return "8";
	case 0x09: return "9";
	case 0x0a: return "volume up";
	case 0x0b: return "volume down";
	case 0x0c: return "tv";
	case 0x0d: return "bouquet up";
	case 0x0e: return "bouquet down";
	case 0x0f: return "standby";
	case 0x20: return "Menu";
	case 0x21: return "up";
	case 0x22: return "down";
	case 0x23: return "left";
	case 0x24: return "right";
	case 0x25: return "ok";
	case 0x26: return "audio";
	case 0x27: return "video";
	case 0x28: return "info";
	case 0x40: return "red";
	case 0x41: return "green";
	case 0x42: return "yellow";
	case 0x43: return "blue";
	case 0x44: return "mute";
	case 0x45: return "text";
	case 0x50: return "forward";
	case 0x51: return "back";
	case 0x52: return "lame";
	case 0x53: return "text";
	case 0x54: return "help";
	}
	return 0;
}

#if 0
int eRCDeviceQBox2::getKeyCompatibleCode(const eRCKey &key) const
{
	switch (key.code&0xFF)
	{
	case 0x00: return KEY_0;
	case 0x01: return KEY_1;
	case 0x02: return KEY_2;
	case 0x03: return KEY_3;
	case 0x04: return KEY_4;
	case 0x05: return KEY_5;
	case 0x06: return KEY_6;
	case 0x07: return KEY_7;
	case 0x08: return KEY_8;
	case 0x09: return KEY_9;
	case 0x0a: return KEY_VOLUMEUP;
	case 0x0b: return KEY_VOLUMEDOWN;
	case 0x0c: return KEY_HOME;
	case 0x0d: return KEY_VOLUMEUP;
	case 0x0e: return KEY_VOLUMEDOWN;
	case 0x0f: return KEY_POWER;
	case 0x20: return KEY_MENU;
	case 0x21: return KEY_UP;
	case 0x22: return KEY_DOWN;
	case 0x23: return KEY_LEFT;
	case 0x24: return KEY_RIGHT;
	case 0x25: return KEY_OK;
	case 0x26: return KEY_YELLOW;
	case 0x27: return KEY_GREEN;
	case 0x28: return KEY_HELP;
	case 0x40: return KEY_RED;
	case 0x41: return KEY_GREEN;
	case 0x42: return KEY_YELLOW;
	case 0x43: return KEY_BLUE;
	case 0x44: return KEY_MUTE;
	case 0x45: return KEY_HOME;
	case 0x50: return KEY_RIGHT;
	case 0x51: return KEY_LEFT;
	case 0x52: return KEY_HELP;
	case 0x53: return KEY_POWER;
	case 0x54: return KEY_HELP;
	}
	return -1;
}
#endif

int eRCDeviceQBox2::getKeyCompatibleCode(unsigned int rccode) const
{
	unsigned int rcid = rccode & 0x00FF0000;
	unsigned int buttoncode = rccode & 0xFF;
	switch (buttoncode)
	{
	case 0x00: return KEY_0;
	case 0x01: return KEY_1;
	case 0x02: return KEY_2;
	case 0x03: return KEY_3;
	case 0x04: return KEY_4;
	case 0x05: return KEY_5;
	case 0x06: return KEY_6;
	case 0x07: return KEY_7;
	case 0x08: return KEY_8;
	case 0x09: return KEY_9;
	case 0x0C: return KEY_TV;
	case 0x0f: return KEY_POWER;
	case 0x20: return KEY_MENU;
	case 0x21: return KEY_UP;
	case 0x22: return KEY_DOWN;
	case 0x23: return KEY_LEFT;
	case 0x24: return KEY_RIGHT;
	case 0x25: return KEY_OK;
	case 0x26: return KEY_AUDIO;
	case 0x27: return KEY_HELP;
	case 0x28: return KEY_INFO;
	case 0x40: return KEY_RED;
	case 0x41: return KEY_GREEN;
	case 0x42: return KEY_YELLOW;
	case 0x43: return KEY_BLUE;
	case 0x44: return KEY_MUTE;
	case 0x45: return KEY_TEXT;
	case 0x50: if (rcid == QBOXONE_RC_ID)	return KEY_VOLUMEDOWN;
		   if (rcid == QBOXHD_RC_ID)	return KEY_PREVIOUS;
	case 0x51: if (rcid == QBOXONE_RC_ID)	return KEY_VOLUMEUP;
		   if (rcid == QBOXHD_RC_ID)	return KEY_NEXT;
	case 0x52: return KEY_EXIT;
	case 0x53: return KEY_RADIO;
	case 0x54: return KEY_VIDEO;
	/* new code added for QBOX_HD RC */
	case 0xa3: return KEY_VOLUMEUP;
	case 0xa5: return KEY_VOLUMEDOWN;
	case 0xa9: return KEY_STOP;
	case 0xAB: return KEY_RECORD;
	case 0xa8: return KEY_CHANNELUP;
	case 0xb1: return KEY_CHANNELDOWN;
	case 0xba: return KEY_MEDIA;
	case 0xaa: return KEY_OPTION;
	}
	return -1;
}

eRCQBoxDriver2::eRCQBoxDriver2(char *devname): eRCShortDriver(devname)
{
}
