#ifndef DISABLE_DREAMBOX_RC

#ifndef __swqbox2_h
#define __swqbox2_h

#include <lib/driver/rc.h>

class eSWDeviceQBox2: public eRCDevice
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
	int getKeyCompatibleCode(unsigned short rccode) const;
//	int getKeyCompatibleCode(const eSWKey &key) const;

public:
	void handleCode(long code);
	eSWDeviceQBox2(eRCDriver *driver);
	const char *getDescription() const;
};

class eSWDeviceQBoxButton: public eRCDevice
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
	eSWDeviceQBoxButton(eRCDriver *driver);
	const char *getDescription() const;
};

class eSWQBoxDriver2: public eRCShortDriver
{
public:
	eSWQBoxDriver2(char * devname);
};
#endif // DISABLE_DREAMBOX_RC
#endif //__swqbox2_h
