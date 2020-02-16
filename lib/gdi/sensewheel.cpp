#include <lib/gdi/sensewheel.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <lib/base/init.h>
#include <lib/base/init_num.h>

struct sw_hsv
{
	unsigned short H;
	unsigned char S;
	unsigned char V;
};

typedef sw_hsv sw_hsv_t;

struct sw_standby
{
	unsigned char standby_mode;         // 0: Exit standby, 1: Enter standby
	unsigned char led_group_map;	    // bit 0: Panel leds, bit 1: Board leds
};

typedef sw_standby sw_standby_t;

eQBOXSenseWheel *eQBOXSenseWheel::instance;

eQBOXSenseWheel::~eQBOXSenseWheel()
{
	if ( swfd != -1 )
	{
		close ( swfd );
		swfd = -1;
	}
}

int eQBOXSenseWheel::lock()
{
	if (locked)
		return -1;
	locked=1;
	return swfd;
}

void eQBOXSenseWheel::unlock()
{
	locked=0;
}

eQBOXSenseWheel::eQBOXSenseWheel()
{
	swfd = -1;
	locked=0;
	standbyonpanel = true;
	swfd = open("/dev/sw0", O_RDONLY);
	if (swfd < 0)
	{
		eDebug("[SENSEWHEEL] No SenseWheel found!\n");
		swfd = -1;
	}
	else
		eDebug("[SENSEWHEEL] found SenseWheel!\n");
	instance=this;
}

void eQBOXSenseWheel::setStandbyOnPanel(unsigned char standbyonpanel )
{
	this->standbyonpanel = standbyonpanel;
}

bool eQBOXSenseWheel::isSetStandbyOnPanel( void )
{
	return (this->standbyonpanel!=0);
}

int eQBOXSenseWheel::setDisableSense()
{
	int fp;
	if((fp=open("/dev/sw0", O_WRONLY))<=0)
	{
		eDebug("[SENSEWHEEL] can't open /dev/sw0\n");
		return(-1);
	}
	if(ioctl(fp, SET_DISABLE_SENSE, 0))
	{
		eDebug("[SENSEWHEEL] can't set disable sense\n");
	}
	close(fp);
	return(0);
}

int eQBOXSenseWheel::setEnableSense()
{
	int fp;
	if((fp=open("/dev/sw0", O_WRONLY))<=0)
	{
		eDebug("[SENSEWHEEL] can't open /dev/sw0\n");
		return(-1);
	}
	if(ioctl(fp, SET_ENABLE_SENSE, 0))
	{
		eDebug("[SENSEWHEEL] can't set enable sense\n");
	}
	close(fp);
	return(0);
}

int eQBOXSenseWheel::setLedsPanel( unsigned short hue, unsigned char saturation, unsigned char value)
{
	int fp;
	sw_hsv_t hsv_data;
	if((fp=open("/dev/sw0", O_WRONLY))<=0)
	{
		eDebug("[SENSEWHEEL] can't open /dev/sw0\n");
		return(-1);
	}
	hsv_data.H = hue;
	hsv_data.S = saturation;
	hsv_data.V = value;
// 	eDebug("[SENSEWHEEL] Set Led Panel");
	if(ioctl(fp, SET_LED_ALL_PANEL_COLOR, &hsv_data))
	{
		eDebug("[SENSEWHEEL] can't set Leds of Panel\n");
	}
	close(fp);
	return(0);
}

int eQBOXSenseWheel::enterStandby( unsigned char standby_panel_leds_status, unsigned char standby_board_leds_status )
{
	int fp;
	sw_standby_t sw_stby;
	if((fp=open("/dev/sw0", O_WRONLY))<=0)
	{
		eDebug("[SENSEWHEEL] can't open /dev/sw0\n");
		return(-1);
	}
	eDebug("[SENSEWHEEL] enter Standby\n");
	sw_stby.standby_mode =  1;
	sw_stby.led_group_map =  0;
	if (standby_panel_leds_status) sw_stby.led_group_map |= 1;
	if (standby_board_leds_status) sw_stby.led_group_map |= 2;
	if(ioctl(fp, STANDBY, &sw_stby))
	{
		eDebug("[SENSEWHEEL] can't set Standby mode\n");
	}
	close(fp);
	return(0);
}

int eQBOXSenseWheel::leaveStandby()
{
	int fp;
	sw_standby_t sw_stby;
	if((fp=open("/dev/sw0", O_WRONLY))<=0)
	{
		eDebug("[SENSEWHEEL] can't open /dev/sw0\n");
		return(-1);
	}
	eDebug("[SENSEWHEEL] leave Standby\n");
	sw_stby.standby_mode =  0;
	sw_stby.led_group_map =  0;
	if(ioctl(fp, STANDBY, &sw_stby))
	{
		eDebug("[SENSEWHEEL] can't set Standby mode\n");
	}
	close(fp);
	// Wait sense is ready ... (4 seconds sense)
	sleep( 4 );
	return(0);
}

int eQBOXSenseWheel::setLedsBoard( unsigned short hue, unsigned char saturation, unsigned char value)
{
	int fp;
	sw_hsv_t hsv_data;
	if((fp=open("/dev/sw0", O_WRONLY))<=0)
	{
		eDebug("[SENSEWHEEL] can't open /dev/sw0\n");
		return(-1);
	}
	hsv_data.H = hue;
	hsv_data.S = saturation;
	hsv_data.V = value;
	if(ioctl(fp, SET_ALL_BOARD_COLOR, &hsv_data))
	{
		eDebug("[SENSEWHEEL] can't set Leds of Board\n");
	}
	close(fp);
	return(0);
}

eQBOXSenseWheel *eQBOXSenseWheel::getInstance()
{
	return instance;
}
