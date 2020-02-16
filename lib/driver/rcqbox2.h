#ifndef DISABLE_DREAMBOX_RC

#ifndef __rcqbox2_h
#define __rcqbox2_h

#include <lib/driver/rc.h>

#define QBOXONE_RC_ID 0x00010000
#define QBOXHD_RC_ID  0x00020000

class eRCDeviceQBox2: public eRCDevice
{
	int last, ccode;
	//eTimer timeout, repeattimer;
	int iskeyboard;
private:
	void timeOut();
	void repeat();
	int getRepeatDelay();
	int getRepeatRate();
	int getKeyCode(int key);
	const char *getKeyDescription(const eRCKey &key) const;
	int getKeyCompatibleCode(unsigned int rccode) const;
//	int getKeyCompatibleCode(const eRCKey &key) const;
public:
	void handleCode(long code);
	eRCDeviceQBox2(eRCDriver *driver);
	const char *getDescription() const;
};

class eRCDeviceQBoxButton: public eRCDevice
{
	int last;
	//eTimer repeattimer;
private:
	void repeat();
	int getRepeatDelay();
	int getRepeatRate();
	int getKeyCode(int button);
public:
	void handleCode(long code);
	eRCDeviceQBoxButton(eRCDriver *driver);
	const char *getDescription() const;
};

class eRCQBoxDriver2: public eRCShortDriver
{
public:
	eRCQBoxDriver2(char *devname);
};

#endif

#endif // DISABLE_DREAMBOX_RC
