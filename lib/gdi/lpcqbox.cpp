#include <lib/gdi/lpcqbox.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <lib/base/init.h>
#include <lib/base/init_num.h>

eQBOXFrontButton *eQBOXFrontButton::instance;

eQBOXFrontButton::eQBOXFrontButton()
{
	fpfd = -1;
	locked=0;
	if((fpfd=open(HOLTEK_DEV, O_WRONLY))<=0)
	{
		eFatal("[eQBOXFrontButton] No FrontPanel found!\n");
		fpfd = -1;
	}
	else
		eDebug("[eQBOXFrontButton] found FrontPanel!\n");
	instance=this;
}

eQBOXFrontButton::~eQBOXFrontButton()
{
	if ( fpfd != -1 )
	{
		close ( fpfd );
		fpfd = -1;
	}
}

int eQBOXFrontButton::lock()
{
	if (locked)
		return -1;
	locked=1;
	return fpfd;
}

void eQBOXFrontButton::unlock()
{
	locked=0;
}

int eQBOXFrontButton::setLed( unsigned char R, unsigned char G, unsigned char B)
{
	Rrgb_Value_t rgb_data;
	if ( fpfd > 0 ) {
		rgb_data.red = R;
		rgb_data.green = G;
		rgb_data.blue = B;
		ioctl(fpfd, IOCTL_SET_RGB, &rgb_data);
		return 0;
	}
	else {
		return -1;
	}
}

int eQBOXFrontButton::enterDeepStandby( void )
{
	return(0);
}

int eQBOXFrontButton::enterStandby( void )
{
	return(0);
}

int eQBOXFrontButton::leaveStandby()
{
	return(0);
}

eQBOXFrontButton *eQBOXFrontButton::getInstance()
{
	return instance;
}
