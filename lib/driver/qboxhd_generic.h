/************************/
/*	From rst driver...	*/ 
/************************/

#ifndef _QBOXHD_GENERIC_H
#define _QBOXHD_GENERIC_H

#define DEVICE_NAME                 "rst_0"
#define	RST_NUMBER_OF_CONTROLLERS	1

#define	DEACT_RST					0
#define	ACT_RST						1

/* Ioctl cmd table */
#define RST_IOW_MAGIC			    'R'

#define IOCTL_ACTIVATION_RST		_IOW(RST_IOW_MAGIC, 1,  int)

#endif // _QBOXHD_GENERIC_H
