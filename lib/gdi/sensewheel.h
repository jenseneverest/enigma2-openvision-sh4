#ifndef __sensewheel_h
#define __sensewheel_h

#include <asm/types.h>

#define LED_MAGIC		0xBC

/* IOCTL */
#define SET_LED_COLOR			_IO(LED_MAGIC,11)   
#define SET_LED_OFF			_IO(LED_MAGIC,12)   
#define SET_LED_ALL_PANEL_COLOR		_IO(LED_MAGIC,13)   
#define SET_LED_ALL_PANEL_OFF		_IO(LED_MAGIC,14)   
#define SET_ALL_BOARD_COLOR		_IO(LED_MAGIC,15)    
#define SET_ALL_BOARD_OFF		_IO(LED_MAGIC,16)    
#define SET_LED_ALL_COLOR		_IO(LED_MAGIC,17)   
#define SET_LED_ALL_OFF			_IO(LED_MAGIC,18)
#define SET_DISABLE_SENSE		_IO(LED_MAGIC,19)  
#define SET_ENABLE_SENSE		_IO(LED_MAGIC,20) 
#define STANDBY           	        _IO(LED_MAGIC,25)

class eQBOXSenseWheel
{
	static eQBOXSenseWheel *instance;
	int swfd;
	int locked;
	unsigned char standbyonpanel;
#ifdef SWIG
	eQBOXSenseWheel();
	~eQBOXSenseWheel();
#endif
public:
#ifndef SWIG
	eQBOXSenseWheel();
	virtual ~eQBOXSenseWheel();
#endif
	static eQBOXSenseWheel *getInstance();
	int lock();
	void unlock();
	bool detected() { return swfd >= 0; }
	int islocked() { return locked; }
	int setDisableSense();
	int setEnableSense();
	int setLedsPanel( unsigned short hue, unsigned char saturation, unsigned char value);
	int setLedsBoard( unsigned short hue, unsigned char saturation, unsigned char value);
	int enterStandby( unsigned char standby_panel_leds_status, unsigned char standby_board_leds_status );
	int leaveStandby();
	void setStandbyOnPanel( unsigned char standbyonpanel );
	bool isSetStandbyOnPanel( void );
};

#endif // __sensewheel_h
