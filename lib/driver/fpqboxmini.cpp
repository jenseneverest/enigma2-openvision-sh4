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

#include "fpqboxmini.h"

int old_status=-1;
void eFButtonDevice::handleCode(long rccode)
{
	old_status=rccode;

	if(rccode==BUTTON_PRESSED)
	{
		rccode=KEY_POWER;
		input->keyPressed(eRCKey(this, (rccode&0x7FFF), 0));
	}
	else
	{
		rccode=KEY_POWER;
		input->keyPressed(eRCKey(this, (rccode&0x7FFF), eRCKey::flagBreak));
	}
}

void eFButtonDevice::timeOut()
{
	int oldcc=ccode;
	ccode=-1;
	if (oldcc!=-1)
		input->keyPressed(eRCKey(this, getKeyCompatibleCode(oldcc&0x7FFF), eRCKey::flagBreak));
}

void eFButtonDevice::repeat()
{
	if (ccode!=-1)
		input->keyPressed(eRCKey(this, getKeyCompatibleCode(ccode&0x7FFF), eRCKey::flagRepeat));
}

eFButtonDevice::eFButtonDevice(eRCDriver *driver)
			: eRCDevice("QBoxHD Mini FrontButton Control", driver), iskeyboard(false)
{
	ccode=-1;
}

const char *eFButtonDevice::getDescription() const
{
	return "QBoxHD Mini FrontButton Control";
}

const char *eFButtonDevice::getKeyDescription(const eRCKey &key) const
{
	switch (key.code)
	{
		case 0x0f: return "standby";
	}
	return 0;
}

int eFButtonDevice::getKeyCompatibleCode(unsigned short rccode) const
{
	switch (rccode&0xFF)
	{
		case 0x0f: return BTN_0; 	//FrontPanel Button
	}

	return -1;
}

eFButtonDriver::eFButtonDriver(char * devname): eRCShortDriver(devname)
{
}
