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

#include "swqbox2.h"
#include <lib/gdi/sensewheel.h>

/* ----------------------- qbox fernbedienung ---------------------- */
void eSWDeviceQBox2::handleCode(long rccode)
{

//	eDebug("-----------------------------------------------> CODICE %04x", rccode);

	if (rccode == 0x00FF) // break code
	{
		//timeout.stop();
		//repeattimer.stop();
//		eDebug("-----------------------------------------------> Timeout %04x", rccode);
		timeOut();
		return;
	}

	//timeout.start(1500, 1);

	int old=ccode;
	ccode=rccode;
	if ((old!=-1) && ( ((old&0x7FFF)!=(rccode&0x7FFF)) || !(rccode&0x8000)) )
	{
//		eDebug("-----------------------------------------------> pulsante rilasciato %04x", old&0x7FFF);
		//repeattimer.stop();
		/*emit*/ input->keyPressed(eRCKey(this, getKeyCompatibleCode(old&0x7FFF), eRCKey::flagBreak));
	}
	if ((old^rccode)&0x7FFF)
	{
//		eDebug("-----------------------------------------------> pulsante premuto %04x", (rccode&0x7FFF));
		input->keyPressed(eRCKey(this, getKeyCompatibleCode(rccode&0x7FFF), 0));
	}
}

void eSWDeviceQBox2::timeOut()
{
	int oldcc=ccode;
	ccode=-1;
	//repeattimer.stop();
	if (oldcc!=-1)
	{
		input->keyPressed(eRCKey(this, getKeyCompatibleCode(oldcc&0x7FFF), eRCKey::flagBreak));
	}
}

void eSWDeviceQBox2::repeat()
{
	if (ccode!=-1)
	{
		input->keyPressed(eRCKey(this, getKeyCompatibleCode(ccode&0x7FFF), eRCKey::flagRepeat));
	}
	//repeattimer.start(eRCInput::getInstance()->config.rrate, 1);
}

eSWDeviceQBox2::eSWDeviceQBox2(eRCDriver *driver)
			: eRCDevice("QBoxHD SenseWheel Control", driver), iskeyboard(false)
{
	ccode=-1;
	//CONNECT(timeout.timeout, eSWDeviceQBox2::timeOut);
	//CONNECT(repeattimer.timeout, eSWDeviceQBox2::repeat);
}

const char *eSWDeviceQBox2::getDescription() const
{
	return "QBoxHD SenseWheel Control";
}

const char *eSWDeviceQBox2::getKeyDescription(const eRCKey &key) const
{
	switch (key.code)
	{
		case 0x0f: return "standby";
		case 0x20: return "Menu";
		case 0x21: return "up";
		case 0x22: return "down";
		case 0x25: return "ok";
		case 0x26: return "audio";
		case 0x27: return "video";
		case 0x28: return "info";
		case 0x50: return "volume up";
		case 0x51: return "volume down";
		case 0x52: return "lame";
	}
	return 0;
}

int eSWDeviceQBox2::getKeyCompatibleCode(unsigned short rccode) const
{
	switch (rccode&0xFF)
	{
		case 0x0f: 
				if ( eQBOXSenseWheel::getInstance()->isSetStandbyOnPanel() )
					return KEY_POWER; 	//Central long press
				else
					return -1;
		case 0x25: return BTN_0; 	//Central 		//KEY_OK;
		case 0x21: return BTN_1; 	//Nord			//KEY_UP;
		case 0x20: return BTN_2; 	//Nord Est 		//KEY_MENU; 
		case 0x50: return BTN_3; 	//Est 			//KEY_LEFT;
		case 0x52: return BTN_4; 	//Sud Est		//KEY_EXIT;
		case 0x22: return BTN_5; 	//Sud			//KEY_DOWN;
		case 0x26: return BTN_6;	//Sud Ovest		//KEY_AUDIO;
		case 0x51: return BTN_7;	//Ovest			//KEY_RIGHT;
		case 0x28: return BTN_8;	//Nord Ovest	//KEY_HELP;
	}
	return -1;
}

eSWQBoxDriver2::eSWQBoxDriver2(char * devname): eRCShortDriver(devname)
{
}
