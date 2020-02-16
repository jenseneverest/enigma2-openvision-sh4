#ifndef __lpcqbox_h
#define __lpcqbox_h

#include <asm/types.h>

#define HOLTEK_DEV 				"/dev/lpc_0"

/* IOCTL */

#define IOCTL_LPC_MAGIC				'L'

#define	IOCTL_READ_VERSION			_IOWR(IOCTL_LPC_MAGIC, 1, int)	// a address
#define	IOCTL_READ_TEMP				_IOWR(IOCTL_LPC_MAGIC, 2, int)	// a address
#define	IOCTL_FAN_POWER				_IOWR(IOCTL_LPC_MAGIC, 3, int)	//from 0 to 31 (pwm)
#define	IOCTL_PWM_VALUE				_IOWR(IOCTL_LPC_MAGIC, 4, int)	//from 0 to 255 (pwm)
#define	IOCTL_SET_MAX_MIN_TEMP		_IOWR(IOCTL_LPC_MAGIC, 5, int)	// a address of short -> (Max_byte|Min_byte)
#define	IOCTL_SET_RGB				_IOWR(IOCTL_LPC_MAGIC, 6, Rrgb_Value_t)	// rgb (5bit for each color)

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

class eQBOXFrontButton
{
	static eQBOXFrontButton *instance;
	int fpfd;
	int locked;
#ifdef SWIG
	eQBOXFrontButton();
	~eQBOXFrontButton();
#endif
public:
#ifndef SWIG
	eQBOXFrontButton();
	virtual ~eQBOXFrontButton();
#endif
	static eQBOXFrontButton *getInstance();
	int lock();
	void unlock();
	bool detected() { return fpfd >= 0; }
	int islocked() { return locked; }
	int setLed( unsigned char R, unsigned char G, unsigned char B );
	int enterDeepStandby( void );
	int enterStandby( void );
	int leaveStandby( void );
};

#endif // __lpcqbox_h
