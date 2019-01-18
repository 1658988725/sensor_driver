// *****************************************************
// Company : Techpoint Inc
// $Date: 2014-03-10 
// $Log:  $
// ******************************************************

//#include "Config.h"
//#include "reg.h"
//#include "typedefs.h"
//#include "I2C.h"
//#include "main.h"
//#include "UARTprintf.h"
//#include "Device_Rx.h"
//#include "tp2912.h"
//#include "Table.c"
#include	"video.h"
#include	"osd.h"


#if defined(__USE_TVI_TX__)


#define Test_Pat		1	// 0:enable,  1:disable
#define CurDrive_MD		1	// 0:current drive mode,  1:voltage drive mode
#define AHD_nEN			1	// 0:enable,  1:disable
#if defined(__MDIN_i550_REF_V121__)
#define	TVI_YC_SWAP		1		// 0:normal,  1:Y/C input swap		Set 'TVI_YC_SWAP = 1' only to schematic(i550 + tp2912) version 1.34.
//#define	TVI_YC_SWAP		0	// 0:normal,  1:Y/C input swap
#else
#define	TVI_YC_SWAP		0	// 0:normal,  1:Y/C input swap
#endif

#define	delay(x)		Delay_mSec(x*5)
#define	Printf			UARTprintf
#define	CODE			ROMDATA


#define	TVI_UCC_EN		1	// 0:disable, 1:enable


BYTE	TVITxID;
BYTE	TPIAddr;
BYTE	ManVidRes;

extern  BOOL fTxIRQ;

CODE _TVITx_Dn_cmd TVITx_Dn_cmd_dataset[] = {
		{0x88,0x00,0x00,0x00,0x00},		//No command
		{0x88,0xff,0x00,0x00,0x00},		//Ack
};
/*
enum{
	TP2801A=0,
	TP2801B,
	TP2803,
	TP2910
};
*/

CODE BYTE TP2910_DataSet[] = {

	14,		

//	0x03, 0x4a,
	0x16, 0xeb,
	0x19, 0xf0,
	0x1a, 0x10,
	0x1c, 0x55,
	0x1d, 0x76,
	0x20, 0x48,
	0x21, 0xbb,
	0x22, 0x2e,
	0x23, 0x8b,
	0x41, 0x00,
	0x42, 0x12,
	0x43, 0x07,
	0x44, 0x49,
	0x45, 0xcb,

	0xff, 0xff
};
CODE BYTE TP2912_8M_DataSet[] = {

	23,		
	0x02, 0x8b,
	0x03, 0x52,
	0x05, 0x78,
	0x07, 0x45,
	0x09, 0x50,
	0x0a, 0x50,
	0x0c, 0x00,
	0x0d, 0x80,
	0x0e, 0x50,
	0x12, 0x08,
	0x1c, 0x55,
	0x1d, 0x76,
	0x1e, 0x80,
	0x20, 0x57,
	0x21, 0x43,
	0x22, 0x4e,
	0x23, 0x02,
	0x24, 0xf8,
	0x25, 0xca,
	0x26, 0x00,
	0x27, 0x58,
	0x28, 0x70,
	0x29, 0xb4,

	0xff, 0xff
};

CODE BYTE TP2912_5M20_DataSet[] = {

	28,		
	0x02, 0x8b,
	0x03, 0x52,
	0x05, 0x80,
	0x07, 0x45,
	0x08, 0x80,
	0x09, 0x50,
	0x0a, 0x50,
	0x0b, 0x21,
	0x0c, 0xe0,
	0x0d, 0x80,
	0x0e, 0x50,
	0x0f, 0xa6,
	0x10, 0x3e,
	0x11, 0x00,
	0x12, 0x04,
	0x1c, 0x55,
	0x1d, 0x76,
	0x1e, 0x80,
	0x20, 0x57,
	0x21, 0x7d,
	0x22, 0x52,
	0x23, 0x3b,
	0x24, 0xa7,
	0x25, 0xbc,
	0x26, 0x20,
	0x27, 0x57,
	0x28, 0x98,
	0x29, 0x34,

	0xff, 0xff
};

CODE BYTE TP2912_QHD_DataSet[] = {

	24,		
	0x02, 0x8b,
	0x03, 0x52,
	0x05, 0x80,
	0x07, 0x45,
	0x08, 0xe0,
	0x09, 0x50,
	0x0a, 0x50,
	0x0c, 0x08,
	0x0d, 0x08,
	0x0e, 0x50,
	0x12, 0x05,
	0x1c, 0x55,
	0x1d, 0x76,
	0x1e, 0x80,
	0x20, 0x57,
	0x21, 0x42,
	0x22, 0x77,
	0x23, 0x87,
	0x24, 0xa5,
	0x25, 0xdc,
	0x26, 0x00,
	0x27, 0x55,
	0x28, 0xa0,
	0x29, 0x34,

	0xff, 0xff
};


CODE BYTE TP2912_1080P30_DataSet[] = {

	20,		
	0x02, 0x83,
	0x03, 0x42,
	0x05, 0x40,
	0x08, 0x58,
	0x09, 0x2c,
	0x0a, 0x2c,
	0x0b, 0x00,
	0x0c, 0xc0,
	0x0d, 0xc0,
	0x0f, 0x98,
	0x10, 0x08,
	0x11, 0x6c,
	0x12, 0x04,
	0x1c, 0xa6,
	0x1d, 0xe6,
	0x1e, 0xf8,
	0x20, 0x48,
	0x21, 0xbb,
	0x22, 0x2e,
	0x23, 0x8b,

	0xff, 0xff
};

CODE BYTE TP2912_1080P25_DataSet[] = {

	20,		
	0x02, 0x93,
	0x03, 0x42,
	0x05, 0x40,
	0x08, 0x10,
	0x09, 0x2c,
	0x0a, 0x2c,
	0x0b, 0x20,
	0x0c, 0xc0,
	0x0d, 0xc0,
	0x0f, 0x50,
	0x10, 0x2a,
	0x11, 0x24,
	0x12, 0x04,
	0x1c, 0xa6,
	0x1d, 0xe6,
	0x1e, 0xf8,
	0x20, 0x48,
	0x21, 0xbb,
	0x22, 0x2e,
	0x23, 0x8b,

	0xff, 0xff
};

CODE BYTE TP2912_720P60F50_DataSet[] = {

	16,
	0x03, 0x42,
	0x05, 0x46,
	0x07, 0x41,
	0x09, 0x28,
	0x0a, 0x28,
	0x0c, 0x04,
	0x0d, 0x04,
	0x0e, 0x28,
	0x12, 0x05,
	0x1c, 0xa6,
	0x1d, 0xe6,
	0x1e, 0xf8,
	0x20, 0x48,
	0x21, 0xbb,
	0x22, 0x2e,
	0x23, 0x8b,
	
	0xff, 0xff
};

CODE BYTE TP2912_720P30F25V2_DataSet[] = {

	16,
	0x03, 0x4a,
	0x05, 0x46,
	0x07, 0x41,
	0x09, 0x28,
	0x0a, 0x28,
	0x0c, 0x04,
	0x0d, 0x04,
	0x0e, 0x28,
	0x12, 0x05,
	0x1c, 0xa6,
	0x1d, 0xe6,
	0x1e, 0xf8,
	0x20, 0x24,
	0x21, 0x5d,
	0x22, 0x17,
	0x23, 0x45,
	
	0xff, 0xff
};

CODE BYTE TP2912_NTSC_DataSet[] = {
	25,		
	0x02, 0x09,
	0x05, 0x24,
	0x07, 0x81,
	0x08, 0x20,
	0x09, 0x42,
	0x0a, 0x28,
	0x0b, 0x05,
	0x0c, 0x04,
	0x0d, 0x04,
	0x0e, 0x3c,
	0x0f, 0x5a,
	0x10, 0x03,
	0x11, 0x16,
	0x12, 0x04,
	0x15, 0x2a,
	0x1b, 0x77,
	0x1c, 0xaa,
	0x1d, 0xf0,
	0x1e, 0xa9,
	0x20, 0x48,
	0x21, 0xbb,
	0x22, 0x2e,
	0x23, 0x8b,
	0x41, 0xc1,
	0x45, 0x8c,
	
	0xff, 0xff
	
};


CODE BYTE TP2912_PAL_DataSet[] = {
	27,		
	0x02, 0x1a,
	0x03, 0x43,
	0x05, 0x20,
	0x07, 0x81,
	0x08, 0x20,
	0x09, 0x42,
	0x0a, 0x28,
	0x0b, 0x05,
	0x0c, 0x04,
	0x0d, 0x04,
	0x0e, 0x3c,
	0x0f, 0x60,
	0x10, 0x03,
	0x11, 0x20,
	0x12, 0x04,
	0x13, 0x3f,
	0x15, 0x2c,
	0x1b, 0x77,
	0x1c, 0xaa,
	0x1d, 0xf0,
	0x1e, 0x76,
	0x20, 0x48,
	0x21, 0xbb,
	0x22, 0x2e,
	0x23, 0x8b,
	0x41, 0xc1,
	0x45, 0x8c,
	
	0xff, 0xff
	
};

CODE BYTE TP2910_1080P30_DataSet[] = {

	11,		
	0x02, 0x87,
	0x05, 0x40,
	0x08, 0x58,
	0x09, 0x2c,
	0x0a, 0x2c,
	0x0b, 0x00,
	0x0c, 0xc0,
	0x0d, 0xc0,
	0x0f, 0x98,
	0x10, 0x08,
	0x11, 0x6c,

	0xff, 0xff
};


CODE BYTE TP2910_1080P25_DataSet[] = {

	11,		
	0x02, 0x97,
	0x05, 0x40,
	0x08, 0x10,
	0x09, 0x2c,
	0x0a, 0x2c,
	0x0b, 0x20,
	0x0c, 0xc0,
	0x0d, 0xc0,
	0x0f, 0x50,
	0x10, 0x2a,
	0x11, 0x24,

	0xff, 0xff
};


CODE BYTE TP2910_720P60_DataSet[] = {

	11,
	0x02, 0x8b,
	0x08, 0x6e,
	0x09, 0x28,
	0x0a, 0x28,
	0x0b, 0x05,
	0x0c, 0x04,
	0x0d, 0x04,
	0x0f, 0x72,
	0x10, 0x06,
	0x11, 0x83,
	0x12, 0x05,
	
	0xff, 0xff
};

CODE BYTE TP2910_720P50_DataSet[] = {

	11,		
	0x02, 0x9b,
	0x08, 0xb8,
	0x09, 0x28,
	0x0a, 0x28,
	0x0b, 0x15,
	0x0c, 0x04,
	0x0d, 0x04,
	0x0f, 0xbc,
	0x10, 0x17,
	0x11, 0xcd,
	0x12, 0x05,
	
	0xff, 0xff
};

CODE BYTE TP2910_720P30_DataSet[] = {

	11,		
	0x02, 0x8f,
	0x08, 0xe0,
	0x09, 0x28,
	0x0a, 0x28,
	0x0b, 0x45,
	0x0c, 0x04,
	0x0d, 0x04,
	0x0f, 0xe4,
	0x10, 0x6c,
	0x11, 0xf5,
	0x12, 0x05,
	
	0xff, 0xff
};

CODE BYTE TP2910_720P25_DataSet[] = {

	11,		
	0x02, 0x9f,
	0x08, 0x74,
	0x09, 0x28,
	0x0a, 0x28,
	0x0b, 0x65,
	0x0c, 0x04,
	0x0d, 0x04,
	0x0f, 0x78,
	0x10, 0x9f,
	0x11, 0x89,
	0x12, 0x05,
	
	0xff, 0xff
};

CODE BYTE TP2910_NTSC_DataSet[] = {
	17,		
	0x02, 0x09,
	0x05, 0x24,
	0x07, 0x81,
	0x08, 0x20,
	0x09, 0x42,
	0x0a, 0x28,
	0x0b, 0x05,
	0x0c, 0x04,
	0x0d, 0x04,
	0x0e, 0x3a,
	0x0f, 0x5a,
	0x10, 0x03,
	0x11, 0x16,
	0x12, 0x04,
	0x1b, 0x97,
	0x1c, 0x81,
	0x1d, 0xb6,
	
	0xff, 0xff
	
};

CODE BYTE TP2910_PAL_DataSet[] = {
	17,		
	0x02, 0x09,
	0x05, 0x24,
	0x07, 0x81,
	0x08, 0x20,
	0x09, 0x42,
	0x0a, 0x28,
	0x0b, 0x05,
	0x0c, 0x04,
	0x0d, 0x04,
	0x0e, 0x3a,
	0x0f, 0x5a,
	0x10, 0x03,
	0x11, 0x16,
	0x12, 0x04,
	0x1b, 0x97,
	0x1c, 0x81,
	0x1d, 0xb6,
	
	0xff, 0xff
	
};


CODE BYTE TP2910_AHD1080P30_DataSet[] = {		
	17,
	0x05, 0x4a,
	0x08, 0xc0,
	0x09, 0x94,
	0x0a, 0x94,
	0x0b, 0x10,
	0x0c, 0x02,
	0x0d, 0x64,
	0x0e, 0x94,
	0x0f, 0x98,
	0x10, 0x08,
	0x11, 0x28,
	0x12, 0x00,
	0x20, 0x29,
	0x21, 0x65,
	0x22, 0x78,
	0x23, 0x16,
	0x29, 0x35,

	0xff, 0xff
};


CODE BYTE TP2910_AHD1080P25_DataSet[] = {		
	17,
	0x05, 0x4a,
	0x08, 0xc0,
	0x09, 0x94,
	0x0a, 0x94,
	0x0b, 0x10,
	0x0c, 0x02,
	0x0d, 0x64,
	0x0e, 0x94,
	0x0f, 0x50,
	0x10, 0x1a,
	0x11, 0xe0,
	0x12, 0x00,
	0x20, 0x29,
	0x21, 0x61,
	0x22, 0x78,
	0x23, 0x16,
	0x29, 0x35,

	0xff, 0xff
};

CODE BYTE TP2912_AHD1080P30_DataSet[] = {		
	24,
	0x02, 0x83, 
	0x05, 0x4a,
	0x08, 0x90,
	0x09, 0x94,
	0x0a, 0x94,
	0x0b, 0x00,
	0x0c, 0x04,
	0x0d, 0xf0,
	0x0e, 0x98,
	0x0f, 0x98,
	0x10, 0x08,
	0x11, 0x2a,
	0x12, 0x00,
	0x16, 0xeb,
	0x19, 0xf0,
	0x1a, 0x10,
	0x1c, 0xa6,
	0x1d, 0xe6,
	0x1e, 0xf8,
	0x20, 0x29,
	0x21, 0x65,
	0x22, 0x78,
	0x23, 0x16,
	0x29, 0x37,

	0xff, 0xff
};


CODE BYTE TP2912_AHD1080P25_DataSet[] = {		
	24,
	0x02, 0x83,
	0x05, 0x4a,
	0x08, 0x90,
	0x09, 0x94,
	0x0a, 0x94,
	0x0b, 0x00,
	0x0c, 0x04,
	0x0d, 0xf0,
	0x0e, 0x98,
	0x0f, 0x50,
	0x10, 0x1a,
	0x11, 0xe2,
	0x12, 0x00,
	0x16, 0xeb,
	0x19, 0xf0,
	0x1a, 0x10,
	0x1c, 0xa6,
	0x1d, 0xe6,
	0x1e, 0xf8,
	0x20, 0x29,
	0x21, 0x61,
	0x22, 0xbe,
	0x23, 0xd6,
	0x29, 0x37,

	0xff, 0xff
};

CODE BYTE TP2912_AHD720P30_36M_DataSet[] = {		
	25,
	0x02, 0x8b,
	0x03, 0x42,
	0x05, 0x6c,
	0x08, 0x76,
	0x09, 0x76,
	0x0a, 0x76,
	0x0b, 0x00,
	0x0c, 0x04,
	0x0d, 0xf0,
	0x0e, 0x82,
	0x0f, 0x40,
	0x10, 0x06,
	0x11, 0x3e,
	0x12, 0x00,
	0x16, 0xeb,
	0x19, 0xf0,
	0x1a, 0x10,
	0x1c, 0xa6,
	0x1d, 0xe6,
	0x1e, 0xf8,
	0x20, 0x28,
	0x21, 0xae,
	0x22, 0x14,
	0x23, 0x7a,
	0x29, 0x37,

	0xff, 0xff
};
CODE BYTE TP2912_AHD720P25_36M_DataSet[] = {		
	25,
	0x02, 0x8b,
	0x03, 0x42,
	0x05, 0x6c,
	0x08, 0x76,
	0x09, 0x76,
	0x0a, 0x76,
	0x0b, 0x00,
	0x0c, 0x04,
	0x0d, 0xf0,
	0x0e, 0x82,
	0x0f, 0x80,
	0x10, 0x17,
	0x11, 0x80,
	0x12, 0x00,
	0x16, 0xeb,
	0x19, 0xf0,
	0x1a, 0x10,
	0x1c, 0xa6,
	0x1d, 0xe6,
	0x1e, 0xf8,
	0x20, 0x28,
	0x21, 0xc4,
	0x22, 0x44,
	0x23, 0x44,
	0x29, 0x37,

	0xff, 0xff
};

CODE BYTE TP2912_AHD720P30_DataSet[] = {		
	25,
	0x02, 0x8b,
	0x03, 0x42,
	0x05, 0x70,
	0x08, 0x7a,
	0x09, 0x7a,
	0x0a, 0x7a,
	0x0b, 0x00,
	0x0c, 0x04,
	0x0d, 0xf0,
	0x0e, 0x86,
	0x0f, 0x72,
	0x10, 0x06,
	0x11, 0x68,
	0x12, 0x00,
	0x16, 0xeb,
	0x19, 0xf0,
	0x1a, 0x10,
	0x1c, 0xa6,
	0x1d, 0xe6,
	0x1e, 0xf8,
	0x20, 0x27,
	0x21, 0x72,
	0x22, 0x80,
	0x23, 0x77,
	0x29, 0x37,

	0xff, 0xff
};
CODE BYTE TP2912_AHD720P25_DataSet[] = {		
	25,
	0x02, 0x8b,
	0x03, 0x42,
	0x05, 0x70,
	0x08, 0x7a,
	0x09, 0x7a,
	0x0a, 0x7a,
	0x0b, 0x00,
	0x0c, 0x04,
	0x0d, 0xf0,
	0x0e, 0x86,
	0x0f, 0xbc,
	0x10, 0x17,
	0x11, 0xb0,
	0x12, 0x00,
	0x16, 0xeb,
	0x19, 0xf0,
	0x1a, 0x10,
	0x1c, 0xa6,
	0x1d, 0xe6,
	0x1e, 0xf8,
	0x20, 0x27,
	0x21, 0x88,
	0x22, 0x04,
	0x23, 0x23,
	0x29, 0x37,

	0xff, 0xff
};

CODE BYTE TP2910_AHD720P30_DataSet[] = {		
	12,
	0x02, 0x8f,
	0x05, 0x60,
	0x09, 0x80,
	0x0b, 0x05,
	0x0e, 0x80,
	0x0f, 0x72,
	0x10, 0x06,
	0x20, 0x27,
	0x21, 0x72,
	0x22, 0x80,
	0x23, 0x77,
	0x29, 0x35,

	0xff, 0xff
};

CODE BYTE TP2910_AHD720P25_DataSet[] = {		
	12,
	0x02, 0x9f,
	0x08, 0xb8,
	0x09, 0x8c,
	0x0b, 0x15,
	0x0f, 0xbc,
	0x10, 0x17,
	0x11, 0xcd,
	0x20, 0x27,
	0x21, 0x88,
	0x22, 0x04,
	0x23, 0x23,
	0x29, 0x35,

	0xff, 0xff
};

CODE BYTE TP2912_AHD4M30_DataSet[] = {		
	31,
	0x02, 0x8b,
	0x03, 0x52,
	0x05, 0xd0,
	0x07, 0x45,
	0x08, 0xd0,
	0x09, 0x98,
	0x0a, 0x98,
	0x0b, 0x12,
	0x0c, 0x04,
	0x0d, 0x04,
	0x0e, 0xb0,
	0x0f, 0xe4,
	0x10, 0x1c,
	0x11, 0x12,
	0x12, 0x0a,
	0x19, 0xf0,
	0x1a, 0x10,
	0x1c, 0x72,
	0x1d, 0x9d,
	0x1e, 0x80,
	0x20, 0x36,
	0x21, 0x50,
	0x22, 0x0e,
	0x23, 0xe5,
	0x24, 0xa5,
	0x25, 0xdc,
	0x26, 0x00,
	0x27, 0x55,
	0x28, 0xa0,
	0x29, 0x36,
	0x2a, 0xd7,

	0xff, 0xff
};

CODE BYTE TP2912_AHD4M25_DataSet[] = {		
	31,
	0x02, 0x8b,
	0x03, 0x52,
	0x05, 0xd0,
	0x07, 0x45,
	0x08, 0xd0,
	0x09, 0x98,
	0x0a, 0x98,
	0x0b, 0x12,
	0x0c, 0x04,
	0x0d, 0x04,
	0x0e, 0xb0,
	0x0f, 0x78,
	0x10, 0x3f,
	0x11, 0xa6,
	0x12, 0x0a,
	0x19, 0xf0,
	0x1a, 0x10,
	0x1c, 0x72,
	0x1d, 0x9d,
	0x1e, 0x80,
	0x20, 0x36,
	0x21, 0x53,
	0x22, 0xc8,
	0x23, 0x25,
	0x24, 0xa5,
	0x25, 0xdc,
	0x26, 0x00,
	0x27, 0x55,
	0x28, 0xa0,
	0x29, 0x36,
	0x2a, 0xd7,

	0xff, 0xff
};


CODE BYTE TP2910_TVI_UpData_DataSet[] = {		//26clocks/bit & 34bits/line
	9,
	0x57, 0x04,
	0x58, 0xec,
	0x59, 0x4e,
	0x5a, 0x0d,
	0x5d, 0x00,
	0x5c, 0x00,
	0x5d, 0x0c,
	0x5c, 0x0b,
	0x5e, 0xa1,

	0xff, 0xff
};

CODE BYTE TP2912_TVI_1080P_UpData_DataSet[] = {		//26clocks/bit & 34bits/line
	10,
	0x57, 0x04,
	0x58, 0xec,
	0x59, 0x4e,
	0x5a, 0x0d,
	0x5c, 0x0b,
	0x5d, 0x0c,
	0x5e, 0xa1,
	0x94, 0x00,
	0x95, 0x00,
	0xfc, 0x10,

	0xff, 0xff
};


CODE BYTE TP2912_TVI_720PV2_UHD_UpData_DataSet[] = {		//26clocks/bit & 34bits/line
	10,
	0x57, 0x02,
	0x58, 0x76,
	0x59, 0x27,
	0x5a, 0x1a,
	0x5c, 0x0b,
	0x5d, 0x0c,
	0x5e, 0xa1,
	0x94, 0x00,
	0x95, 0x00,
	0xfc, 0x10,

	0xff, 0xff
};


CODE BYTE TP2910_AHD1080_UpData_DataSet[] = {		
	9,
	0x57, 0x03,
	0x58, 0x75,
	0x59, 0x9f,
	0x5a, 0x13,
	0x5c, 0x11,
	0x5d, 0x12,
	0x5e, 0x97,
	0x7d, 0x13,
	0x7e, 0x14,

	0xff, 0xff
};

CODE BYTE TP2912_AHD_UHD_UpData_DataSet[] = {		
	7,
	0x5a, 0x4e,
	0x5c, 0x0f,
	0x5d, 0x00,
	0x5e, 0x87,
	0x94, 0x09,
	0x95, 0x0b,
	0xfc, 0x10,

	0xff, 0xff
};

CODE BYTE TP2912_AHD_UpData_DataSet[] = {		
	7,
	0x5a, 0x38,
	0x5c, 0x11,
	0x5d, 0x00,
	0x5e, 0x87,
	0x94, 0x09,
	0x95, 0x0b,
	0xfc, 0x10,

	0xff, 0xff
};
CODE BYTE TP2912_AHD_720P_UpData_DataSet[] = {		
	7,
	0x5a, 0x38,
	0x5c, 0x11,
	0x5d, 0x00,
	0x5e, 0x87,
	0x94, 0x09,
	0x95, 0x09,
	0xfc, 0x14,

	0xff, 0xff
};

CODE BYTE TP2912_AHD_720P_36M_UpData_DataSet[] = {		
	7,
	0x5a, 0x36,
	0x5c, 0x11,
	0x5d, 0x00,
	0x5e, 0x87,
	0x94, 0x09,
	0x95, 0x09,
	0xfc, 0x14,

	0xff, 0xff
};

CODE BYTE TP2912_Reset_DataSet[] = {

	53,
	0x02, 0xCB,
	0x03, 0x42,
	0x05, 0x46,
	0x07, 0x41,
	0x08, 0x6E,
	0x09, 0x28,
	0x0A, 0x28,
	0x0B, 0x05,
	0x0C, 0x04,
	0x0D, 0x04,
	0x0E, 0x28,
	0x0F, 0x72,
	0x10, 0x06,
	0x11, 0x8C,
	0x12, 0x04,
	0x13, 0x3C,
	0x14, 0x38,
	0x15, 0x38,
	0x16, 0xEB,
	0x17, 0x10,
	0x18, 0x10,
	0x19, 0xF0,
	0x1A, 0x10,
	0x1B, 0xA4,
	0x1C, 0x55,
	0x1D, 0x76,
	0x1E, 0x80,
	0x1F, 0x00,
	0x20, 0x48,
	0x21, 0xBA,
	0x22, 0x2E,
	0x23, 0x8B,
	0x24, 0x86,
	0x25, 0x40,
	0x26, 0x00,
	0x27, 0x56,
	0x28, 0x00,
	0x29, 0x34,
	0x2A, 0x19,
	0x2B, 0x00,
	0x34, 0x00,
	0x35, 0x00,
	0x3A, 0x00,
	0x3B, 0x10,
	0x3C, 0x50,
	0x3D, 0x80,
	0x3E, 0x18,
	0x3F, 0x00,
	0x41, 0x01,
	0x42, 0x52,
	0x43, 0x07,
	0x44, 0x49,
	0x45, 0x4B,
	
	0xff, 0xff
};



// i2c func
BYTE ReadI2C(BYTE dAddr, BYTE rAddr)
{
	BYTE buff;
	
	I2C_Read(TP2912_I2C_CH, dAddr, rAddr, I2C_ADDR_8BIT, &buff, I2C_DATA_8BIT, 1);
	return buff;
}

void WriteI2C(BYTE dAddr, BYTE rAddr, BYTE buff)
{
	I2C_Write(TP2912_I2C_CH, dAddr, rAddr, I2C_ADDR_8BIT, &buff, I2C_DATA_8BIT, 1);
}

void I2CDeviceSet_(BYTE addr, PBYTE RegSet)
{
	int	cnt=0;
	BYTE index, val;

	// Output discription
	#ifdef TASKING
	while( *RegSet ) 
		RS_tx( *RegSet++ );
	RegSet++;
	#endif

	while ( *RegSet != 0xFF ) {
		if( cnt==0 ) {
			cnt = *RegSet;
			RegSet+=1;
		}
		index = *RegSet;
		val = *(RegSet+1);
//		MonWriteI2C(addr, index, val);
		WriteI2C(addr, index, val);

//		Puts("\r\n");

		RegSet+=2;

		cnt--;
	}

	delay(50);
}


BYTE getbits(BYTE x, BYTE p, BYTE n) {
    return (x >> (p + 1 - n)) & ~(~0 << n);
}


void Set_PLL_StartUp(){
	BYTE PLL_con;
	PLL_con = ReadI2C(TPIAddr,0x43);
	WriteI2C(TPIAddr,0x43,(PLL_con&0xbf));
	delay(100);
	WriteI2C(TPIAddr,0x43,PLL_con);
}

void Set_PLL(){
	if((ManVidRes&0x08)==0x08){		//8M/5M/4M resolution
		WriteI2C(TPIAddr,0x42,0x12);
		WriteI2C(TPIAddr,0x43,0x17);
		WriteI2C(TPIAddr,0x44,0xd4);
	}
	else if((ManVidRes==AHD720P30)||(ManVidRes==AHD720P25)){		//vco=144MHz
		WriteI2C(TPIAddr,0x42,0x52);
		WriteI2C(TPIAddr,0x43,0x17);
		WriteI2C(TPIAddr,0x44,0x49);
	}
	else if((ManVidRes==AHD720P30_36M)||(ManVidRes==AHD720P25_36M)){		//vco=144MHz
		WriteI2C(TPIAddr,0x42,0x52);
		WriteI2C(TPIAddr,0x43,0x27);
		WriteI2C(TPIAddr,0x44,0x4e);
	}	
	else{
		WriteI2C(TPIAddr,0x42,0x52);
		WriteI2C(TPIAddr,0x43,0x07);
		WriteI2C(TPIAddr,0x44,0x49);
	}
}


BYTE Det_TVI_addr(){
	BYTE Reg_fe;
	BYTE i;

	Reg_fe = ReadI2C(0x88,0xfe);

	for(i=0;i<=5;i++){
		if((Reg_fe == 0x28)||(Reg_fe == 0x29))
			return 0x88;
		else{
			Reg_fe = ReadI2C(0x8a,0xfe);
			if((Reg_fe == 0x28)||(Reg_fe == 0x29))
				return 0x8a;
		}
	}
	return 0x8a;
}

void En_TxD_TVITx(){
	BYTE Reg56;

	Reg56=ReadI2C(TPIAddr,0x56);
	WriteI2C(TPIAddr,0x56,Reg56|0x80);
	delay(5);
	WriteI2C(TPIAddr,0x56,Reg56&0x7f);
}

void Send_TxD_TVITx(_TVITx_Dn_cmd *ptxd_set){
	BYTE line_cnt,bytecnt;
	BYTE *ptxd;
	BYTE addr = 0x4c;

	ptxd = &ptxd_set->Head;

	line_cnt = 2;										// 2Lines data
	while(line_cnt--){
		for(bytecnt=0;bytecnt<=4;bytecnt++){		// 5bytes Data
			WriteI2C(TPIAddr,addr,*ptxd);
			Printf("\r\nWrite %02xh to addr %02xh",(WORD)*ptxd,(WORD)addr);
			addr++;
			ptxd++;
		}
		ptxd -=5;									//write same data for 2 lines
	}
	En_TxD_TVITx();
	
}

void Init_UpData_Comm(){		
	BYTE *ptr_UpData;
	BYTE Reg94;

	if((ManVidRes&0x10)==0x10){										//AHD
		if(TVITxID==TP2912){
			if((ManVidRes&0x08)==0x08)								// 4M/5M/8M
				ptr_UpData = (PBYTE)&TP2912_AHD_UHD_UpData_DataSet;
			else if((ManVidRes==AHD720P30_36M)||(ManVidRes==AHD720P25_36M))
				ptr_UpData = (PBYTE)&TP2912_AHD_720P_36M_UpData_DataSet;
			else if((ManVidRes==AHD720P30)||(ManVidRes==AHD720P25))
				ptr_UpData = (PBYTE)&TP2912_AHD_720P_UpData_DataSet;
			else
				ptr_UpData = (PBYTE)&TP2912_AHD_UpData_DataSet;
		}
		else
			ptr_UpData = (PBYTE)&TP2910_AHD1080_UpData_DataSet;
	}		
	else{															//TVI: 26clocks/bit & 34bits/line
		if(TVITxID==TP2912){
			if((ManVidRes==R1080P30)||(ManVidRes==R1080P25)||
			   (ManVidRes==R720P60)||(ManVidRes==R720P50))
				ptr_UpData = (PBYTE)&TP2912_TVI_1080P_UpData_DataSet;
			else													//720P30/25-V2.0 and 4M/5M/8M 
				ptr_UpData = (PBYTE)&TP2912_TVI_720PV2_UHD_UpData_DataSet;
		}
		else
			ptr_UpData = (PBYTE)&TP2910_TVI_UpData_DataSet;	
	}
		
	I2CDeviceSet_(TPIAddr,ptr_UpData);
	WriteI2C(TPIAddr,0x6b,0xa8);					// enable Rx data interrupt
	WriteI2C(TPIAddr,0x6d,0x04);					// Interrupt clear mode: clear by read
	if(TVITxID==TP2912){							//Enable Internal slice mode
		Reg94=ReadI2C(TPIAddr,0x94);
		WriteI2C(TPIAddr,0x94,(Reg94|0x10));
		WriteI2C(TPIAddr,0x3b,0x12);
	}
}

void Read_Rxd(BYTE *pRxD){
	BYTE addr;
	
	for(addr=0x5f;addr<=0x68;addr++){
		if((addr==0x5f)||(addr==0x64))				// Header
			*pRxD=ReadI2C(TPIAddr,addr)&0x03;
		else										// Data
			*pRxD = ReadI2C(TPIAddr,addr);
			
		pRxD++;
	}
	for(addr=0x7f;addr<=0x88;addr++){
		if((addr==0x7f)||(addr==0x84))				// Header
			*pRxD=ReadI2C(TPIAddr,addr)&0x03;
		else										// Data
			*pRxD = ReadI2C(TPIAddr,addr);
		
		pRxD++;
	}
}

void Send_TxD(BYTE dat_set){
	
	Send_TxD_TVITx((_TVITx_Dn_cmd*)&TVITx_Dn_cmd_dataset[dat_set]);
}

void Get_RxD(){
	BYTE dat_cnt=0;
	BYTE *pRxD;
	BYTE RxD[10];
	BYTE reg89;
	
	pRxD=RxD;
	Read_Rxd(pRxD);
	reg89=ReadI2C(TPIAddr,0x89);

	if((*pRxD==0x02)&&(*(pRxD+1)==0xb5)){
		if((*(pRxD+2)==0x00)&&(*(pRxD+3)==0x17)&&(*(pRxD+4)==0x5f))	{
			MenuMessageControl();
			Printf("\r\nTVI Menu");
		}
		else if((*(pRxD+2)==0x00)&&(*(pRxD+3)==0x07)&&(*(pRxD+4)==0x00))	{
			DirDMessageControl();
			Printf("\r\nTVI Down");
		}
		else if((*(pRxD+2)==0x00)&&(*(pRxD+3)==0x06)&&(*(pRxD+4)==0x00))	{
			DirUMessageControl();
			Printf("\r\nTVI Up");
		}
		else if((*(pRxD+2)==0x00)&&(*(pRxD+3)==0x09)&&(*(pRxD+4)==0x00))	{
			DirLMessageControl();
			Printf("\r\nTVI Left");
		}
		else if((*(pRxD+2)==0x00)&&(*(pRxD+3)==0x08)&&(*(pRxD+4)==0x00))	{
			DirRMessageControl();
			Printf("\r\nTVI Right");
		}
		else if((*(pRxD+2)==0x00)&&(*(pRxD+3)==0x14)&&(*(pRxD+4)==0x00))	{
			// add function here
			Printf("\r\nTVI Stop");
		}
		else	{
			if(GetOSDMenuID()==0x0000)		MenuMessageControl();
			else							EnterMessageControl();
			Printf("\r\nTVI ESC...");
		}
	}
	else{
		for(dat_cnt=0;dat_cnt<=9;dat_cnt++){
			Printf(" %02xh",(WORD)*pRxD);
			pRxD++;
		}
	}

}

/*
void Get_RxD(){
	BYTE dat_cnt;
	BYTE RxD[10];
	BYTE val,reg89;
	
	Read_Rxd(RxD);
	reg89=ReadI2C(TPIAddr,0x89);
//	Printf("\r\nLINE8-1 Status:%02x",(WORD)reg89);
	val=ReadI2C(TPIAddr,0x5e);
	for(dat_cnt=0;dat_cnt<=9;dat_cnt++){
		if(dat_cnt==0 || dat_cnt==5){
			if(RxD[dat_cnt]!=0x02){								// check head information. should be 0x02
	//			Printf("...Header data(0x02) is not correct. Try again...");
				return;
			}
		}
		else
			Printf(" %02xh",(WORD)RxD[dat_cnt]);
		
	}

}
*/
BYTE BitsReverse(BYTE val){
	BYTE i;
	BYTE cnt=7;
	BYTE bitflag=0x01;
	BYTE rval=0x00;
	for(i=0;i<4;i++){
		rval|=((val>>cnt)&bitflag);
		bitflag<<=1;
		cnt-=2;
	}
	cnt=7;
	bitflag=0x80;
	for(i=0;i<4;i++){
		rval|=((val<<cnt)&bitflag);
		bitflag>>=1;
		cnt-=2;
	}
	return rval;
}

void Get_AHD_RxD_wACP(){
	BYTE Reg_RxD[20];
	BYTE *pRxD;
	BYTE cmd1,cmd2,cmd3,cmd4;
	
	pRxD=Reg_RxD;
	Read_Rxd(pRxD);
	cmd1=BitsReverse(*(pRxD+4));
	cmd2=BitsReverse(*(pRxD+9));
	if((cmd1==0x02)&&(cmd2==0x00))
		Printf("\r\nAHD Menu");
	else if((cmd1==0x00)&&(cmd2==0x02))
		Printf("\r\nAHD Right");
	else if((cmd1==0x00)&&(cmd2==0x04))
		Printf("\r\nAHD Left");
	else if((cmd1==0x00)&&(cmd2==0x08))
		Printf("\r\nAHD Up");
	else if((cmd1==0x00)&&(cmd2==0x10))
		Printf("\r\nAHD Down");
	else{
		cmd3=BitsReverse(*(pRxD+14));
		cmd4=BitsReverse(*(pRxD+19));
		Printf("\r\nAHD_Data=%02x,%02x,%02x,%02x",(WORD)cmd1,(WORD)cmd2,(WORD)cmd3,(WORD)cmd4);
	}
}

void Get_AHD_RxD(){
	BYTE bitpos=0;
	BYTE get_bit;
	BYTE line_cnt=0,byte_pos=0;
	BYTE Reg_RxD[20];
	BYTE *RxD;
	BYTE AHD_RxD[4]={0,0,0,0};
	BYTE AHD_bit=8;
	BYTE *pAHD_RxD;

	Read_Rxd(Reg_RxD);
	RxD = Reg_RxD;
	pAHD_RxD=AHD_RxD;

	while(AHD_bit--){
		switch(AHD_bit) {
			case 7:
				byte_pos = 2;
				bitpos = 6;
				break;
			case 6:
				byte_pos = 2;
				bitpos = 3;	
				break;
			case 5:
				byte_pos = 2;
				bitpos = 0;
				break;
			case 4:
				byte_pos = 3;
				bitpos = 5;
				break;
			case 3:
				byte_pos = 3;
				bitpos = 2;
				break;
			case 2:
				byte_pos = 4;
				bitpos = 7;
				break;
			case 1:
				byte_pos = 4;
				bitpos = 4;
				break;
			case 0:
				byte_pos = 4;
				bitpos = 1;
				break;
			default:
				break;
		}
		RxD += byte_pos;
		for(line_cnt=0;line_cnt<=3;line_cnt++){

			get_bit = getbits(*RxD,bitpos,1);
			*pAHD_RxD |= (get_bit << AHD_bit);

			RxD += 5;
			pAHD_RxD++;
		}

		pAHD_RxD -= line_cnt;
		RxD -= 5*line_cnt+byte_pos;
	}
	
	Printf("\r\nAHD Data1:%02xh, Data2:%02xh, Data3:%02xh, Data4:%02xh\r\n",(WORD)*pAHD_RxD,(WORD)*(pAHD_RxD+1), (WORD)*(pAHD_RxD+2),(WORD)*(pAHD_RxD+3));
}

void GetTVI_Interrupt(){
	if(TVI_UCC_EN==OFF)			return;
	
	if(fTxIRQ != TRUE)			return;			// check INT(pin.37)
	else						fTxIRQ = FALSE;
	
	if((ReadI2C(TPIAddr,0x69)&0x01)==0x01){
		delay(10);
//		if(AHD_nEN==0)
		if((ManVidRes&0x10)==0x10){		// AHD
			if(TVITxID==TP2912){
				Get_AHD_RxD_wACP();
			}
			else
				Get_AHD_RxD();
		}
		else
			Get_RxD();	
	}
}

void Clear_Interrupt(){
	BYTE Reg69;
	Reg69=ReadI2C(TPIAddr,0x69);
}

BYTE CHIPnREV_ID(){
	BYTE Reg01, Reg04, Regff;
	BYTE ChipID=0;
	
	Regff=ReadI2C(TPIAddr,0xff);

	if(Regff==0x01){
		WriteI2C(TPIAddr,0x06,0x80);		//soft reset
		Reg01=ReadI2C(TPIAddr,0x01);
		Reg04=ReadI2C(TPIAddr,0x04);
		if((Reg01==0x00)&&(Reg04==0x00)){
			ChipID=TP2801B;
			Printf("\r\nChip ID=TP2801B");
		}
		else{
			ChipID=TP2801A;
			Printf("\r\nChip ID=TP2801A");
		}
	}
	else if(Regff==0x10)
	{
		ChipID=TP2910;
		Printf("\r\nChip ID=TP2910");
	}
	else if(Regff==0x03){
		ChipID=TP2803;
		Printf("\r\nChip ID=TP2803");
	}
	else if(Regff==0x12){
		ChipID=TP2912;
		Printf("\r\nChip ID=TP2912");
	}

	return ChipID;
}
void AHD_Init(){
	
	BYTE *ptr_AHD_Res;

	switch (ManVidRes){
		case AHD1080P30:
			if(TVITxID==TP2912)
				ptr_AHD_Res=(PBYTE)&TP2912_AHD1080P30_DataSet;
			else
				ptr_AHD_Res=(PBYTE)&TP2910_AHD1080P30_DataSet;
			Printf("\r\nAHD 1080P30");
			break;
		case AHD1080P25:
			if(TVITxID==TP2912)
				ptr_AHD_Res=(PBYTE)&TP2912_AHD1080P25_DataSet;
			else
				ptr_AHD_Res=(PBYTE)&TP2910_AHD1080P25_DataSet;
			Printf("\r\nAHD 1080P25");
			break;
		case AHD720P30:
			if(TVITxID==TP2912)
				ptr_AHD_Res=(PBYTE)&TP2912_AHD720P30_DataSet;
			else
				ptr_AHD_Res=(PBYTE)&TP2910_AHD720P30_DataSet;
			Printf("\r\nAHD 720P30");
			break;
		case AHD720P25:
			if(TVITxID==TP2912)
				ptr_AHD_Res=(PBYTE)&TP2912_AHD720P25_DataSet;
			else
				ptr_AHD_Res=(PBYTE)&TP2910_AHD720P25_DataSet;
			Printf("\r\nAHD 720P25");
			break;
		case AHD720P30_36M:
			ptr_AHD_Res=(PBYTE)&TP2912_AHD720P30_36M_DataSet;
			Printf("\r\nAHD 720P30 36MHz");
			break;
		case AHD720P25_36M:
			ptr_AHD_Res=(PBYTE)&TP2912_AHD720P25_36M_DataSet;
			Printf("\r\nAHD 720P25 36MHz");
			break;
		case AHD_QHD30:
			Printf("\r\nAHD 4M30");
			ptr_AHD_Res=(PBYTE)&TP2912_AHD4M30_DataSet;
			break;
		case AHD_QHD25:
			Printf("\r\nAHD 4M25");
			ptr_AHD_Res=(PBYTE)&TP2912_AHD4M25_DataSet;
			break;
		default:
			if(TVITxID==TP2912)
				ptr_AHD_Res=(PBYTE)&TP2912_AHD1080P30_DataSet;
			else
				ptr_AHD_Res=(PBYTE)&TP2910_AHD1080P30_DataSet;
			Printf("\r\nAHD 1080P30");
			break;
	}
	I2CDeviceSet_(TPIAddr, ptr_AHD_Res);
}

void TVI_Init(){
	BYTE *ptr_TVI_Res;
	switch (ManVidRes) {
			case R8M15:
				ptr_TVI_Res = (PBYTE)&TP2912_8M_DataSet;
				WriteI2C(TPIAddr,0x08,0x80);
				WriteI2C(TPIAddr,0x0b,0x15);
				WriteI2C(TPIAddr,0x0f,0x30);
				WriteI2C(TPIAddr,0x10,0x01);
				WriteI2C(TPIAddr,0x11,0xaa);
				Printf("\r\nSetting registers for 8M 15F...");
				break;
			case R8M125:
				ptr_TVI_Res = (PBYTE)&TP2912_8M_DataSet;
				WriteI2C(TPIAddr,0x08,0xe0);
				WriteI2C(TPIAddr,0x0b,0x35);
				WriteI2C(TPIAddr,0x0f,0xa0);
				WriteI2C(TPIAddr,0x10,0x44);
				WriteI2C(TPIAddr,0x11,0x18);
				Printf("\r\nSetting registers for 8M 12.5F...");
				break;
			case R5M20:
				ptr_TVI_Res = (PBYTE)&TP2912_5M20_DataSet;
				Printf("\r\nSetting registers for 5M 20F...");
				break;
			case RQHD30:
				ptr_TVI_Res = (PBYTE)&TP2912_QHD_DataSet;
				WriteI2C(TPIAddr,0x0b,0x0a);
				WriteI2C(TPIAddr,0x0f,0xe4);
				WriteI2C(TPIAddr,0x10,0x1c);
				WriteI2C(TPIAddr,0x11,0x00);
				Printf("\r\nSetting registers for QHD 30F...");
				break;
			case RQHD25:
				ptr_TVI_Res = (PBYTE)&TP2912_QHD_DataSet;
				WriteI2C(TPIAddr,0x0b,0x3a);
				WriteI2C(TPIAddr,0x0f,0x78);
				WriteI2C(TPIAddr,0x10,0x3f);
				WriteI2C(TPIAddr,0x11,0x90);
				Printf("\r\nSetting registers for QHD 25F...");
				break;
			case R1080P30:
				if(TVITxID==TP2912)
					ptr_TVI_Res = (PBYTE)&TP2912_1080P30_DataSet;
				else
					ptr_TVI_Res = (PBYTE)&TP2910_1080P30_DataSet;
				Printf("\r\nSetting registers for 1080p 30F...");
				break;
			
			case R1080P25:
				if(TVITxID==TP2912)
					ptr_TVI_Res = (PBYTE)&TP2912_1080P25_DataSet;
				else
					ptr_TVI_Res = (PBYTE)&TP2910_1080P25_DataSet;
				Printf("\r\nSetting registers for 1080p 25F...");
				break;
			case R720P60:
				if(TVITxID==TP2912){
					ptr_TVI_Res = (PBYTE)&TP2912_720P60F50_DataSet;
					WriteI2C(TPIAddr,0x02,0x8b);
					WriteI2C(TPIAddr,0x08,0x6e);
					WriteI2C(TPIAddr,0x0b,0x05);
					WriteI2C(TPIAddr,0x0f,0x72);
					WriteI2C(TPIAddr,0x10,0x06);
					WriteI2C(TPIAddr,0x11,0x83);
				}
				else
					ptr_TVI_Res = (PBYTE)&TP2910_720P60_DataSet;
				Printf("\r\nSetting registers for 720p 60F...");
				break;

			case R720P50:
				if(TVITxID==TP2912){
					ptr_TVI_Res = (PBYTE)&TP2912_720P60F50_DataSet;
					WriteI2C(TPIAddr,0x02,0x9b);
					WriteI2C(TPIAddr,0x08,0xb8);
					WriteI2C(TPIAddr,0x0b,0x15);
					WriteI2C(TPIAddr,0x0f,0xbc);
					WriteI2C(TPIAddr,0x10,0x17);
					WriteI2C(TPIAddr,0x11,0xcd);
				}
				else
					ptr_TVI_Res = (PBYTE)&TP2910_720P50_DataSet;
				Printf("\r\nSetting registers for 720p 50F...");
				break;

			case R720P30_TVI20:
				if(TVITxID==TP2912){
            		ptr_TVI_Res = (PBYTE)&TP2912_720P30F25V2_DataSet;
					WriteI2C(TPIAddr,0x02,0x8b);
					WriteI2C(TPIAddr,0x08,0x6e);
					WriteI2C(TPIAddr,0x0b,0x05);
					WriteI2C(TPIAddr,0x0f,0x72);
					WriteI2C(TPIAddr,0x10,0x06);
					WriteI2C(TPIAddr,0x11,0x83);
				}
				else{
					ptr_TVI_Res = (PBYTE)&TP2910_720P60_DataSet;
					WriteI2C(TPIAddr,0x43,0x17);
				}
				Printf("\r\nSetting registers for 720p 30F V2.0...");
		    	break;
		
			case R720P25_TVI20:
				if(TVITxID==TP2912){
					ptr_TVI_Res = (PBYTE)&TP2912_720P30F25V2_DataSet;
					WriteI2C(TPIAddr,0x02,0x9b);
					WriteI2C(TPIAddr,0x08,0xb8);
					WriteI2C(TPIAddr,0x0b,0x15);
					WriteI2C(TPIAddr,0x0f,0xbc);
					WriteI2C(TPIAddr,0x10,0x17);
					WriteI2C(TPIAddr,0x11,0xcd);
				}
				else{
					ptr_TVI_Res = (PBYTE)&TP2910_720P50_DataSet;
					WriteI2C(TPIAddr,0x43,0x17);
				}
				Printf("\r\nSetting registers for 720p 25F V2.0...");
				break;

			case NTSC:
				if(TVITxID==TP2912)
					ptr_TVI_Res = (PBYTE)&TP2912_NTSC_DataSet;
				else
					ptr_TVI_Res = (PBYTE)&TP2910_NTSC_DataSet;
				Printf("\r\nSetting registers for NTSC...");
				break;
			case PAL:
				if(TVITxID==TP2912)
					ptr_TVI_Res = (PBYTE)&TP2912_PAL_DataSet;
				else
					ptr_TVI_Res = (PBYTE)&TP2910_PAL_DataSet;
				Printf("\r\nSetting registers for PAL...");
				break;
			default:
				ptr_TVI_Res = (PBYTE)&TP2910_1080P30_DataSet;
				Printf("\r\nNo resolution selection. Set to 1080p 30F...");
				break;
			
		}

		I2CDeviceSet_(TPIAddr, ptr_TVI_Res);
}

void Set_OutputMode(){


	if(CurDrive_MD==0){							// current drive mode
		if(TVITxID==TP2912)
			WriteI2C(TPIAddr,0x3e,0x10);
	}
	else{										// voltage drive mode
		if(TVITxID==TP2910){
			WriteI2C(TPIAddr,0x3e,0x08);
			WriteI2C(TPIAddr,0x3d,0x05);
			if((ManVidRes==R720P30_TVI20)||(ManVidRes==R720P25_TVI20))
				WriteI2C(TPIAddr,0x3c,0x10);
			else
				WriteI2C(TPIAddr,0x3c,0x00);
		}
		else if(TVITxID==TP2912){
			if((ManVidRes&0x08)==0x08){			// 4M/5M/8M
				WriteI2C(TPIAddr,0x3c,0x10);
				WriteI2C(TPIAddr,0x3e,0x1d);
			}
			else if((ManVidRes==NTSC)||(ManVidRes==PAL)){
				WriteI2C(TPIAddr,0x3c,0x90);
				WriteI2C(TPIAddr,0x3e,0x1c);
			}
			else if((ManVidRes==R720P30_TVI20)||(ManVidRes==R720P25_TVI20)||
				    (ManVidRes==AHD720P30)||(ManVidRes==AHD720P25) ||
				    (ManVidRes==AHD720P30_36M)||(ManVidRes==AHD720P25_36M)){
				WriteI2C(TPIAddr,0x3c,0x90);
				WriteI2C(TPIAddr,0x3e,0x1e);
			}
			else{								//1080p30/25, 720p60/50
				WriteI2C(TPIAddr,0x3c,0x50);
				WriteI2C(TPIAddr,0x3e,0x1e);
			}
		}
	}
	
}

void Init_TVITx_RegSet(){

	BYTE dat;

	TPIAddr = Det_TVI_addr();
	TVITxID=CHIPnREV_ID();
	if(TVITxID==TP2912){
		WriteI2C(TPIAddr,0x43,0x47);	// pll power down
		delay(20);						// delay 100ms
		
		I2CDeviceSet_(TPIAddr, (PBYTE)&TP2912_Reset_DataSet[0]);
		
		WriteI2C(TPIAddr,0x45,0x8b);
	}
	else
		I2CDeviceSet_(TPIAddr,(PBYTE)&TP2910_DataSet);

	ManVidRes = CnvMainFrmtToTVI();
	
	Set_PLL();
	Set_PLL_StartUp();
	delay(20);
	if((TVITxID==TP2801B)||(TVITxID==TP2803))
		WriteI2C(TPIAddr,0x43,0x47);
	
	if(AHD_nEN==0){
		ManVidRes |= 0x10;
		AHD_Init();
	}
	else
		TVI_Init();

	Set_OutputMode();	
	if(TVI_UCC_EN==1)	Init_UpData_Comm();

	if(!Test_Pat){		//for internal test pattern out
		dat = ReadI2C(TPIAddr,0x02)| 0x40;
		WriteI2C(TPIAddr,0x02,dat);
	}
		
	// y/c input swap
	dat = ReadI2C(TPIAddr,0x06);
	dat &= (~0x20);
	dat |= (TVI_YC_SWAP)?  0x20:  0x00;
	WriteI2C(TPIAddr,0x06,dat);
}


BYTE CnvMainFrmtToTVI(void)
{
	switch(GetOUT_MainFrmt())	{
		case MISP_VIDOUT_720x480i60:
		case MISP_VIDOUT_960x480i60:	return	NTSC;
		case MISP_VIDOUT_720x576i50:
		case MISP_VIDOUT_960x576i50:	return  PAL;
		
#if (AHD_nEN==0)						// when use AHD format
		case MISP_VIDOUT_1920x1080p30:	return  AHD1080P30;
		case MISP_VIDOUT_1920x1080p25:	return  AHD1080P25;
		case MISP_VIDOUT_1280x720p60:	return  AHD720P60;
		case MISP_VIDOUT_1280x720p50:	return  AHD720P50;
		case MISP_VIDOUT_1280x720p30:	return  AHD720P30;
		case MISP_VIDOUT_1280x720p25:	return  AHD720P25;
#else
		case MISP_VIDOUT_1920x1080p30:	return  R1080P30;
		case MISP_VIDOUT_1920x1080p25:	return  R1080P25;
		case MISP_VIDOUT_1280x720p60:	return  R720P60;
		case MISP_VIDOUT_1280x720p50:	return  R720P50;
		//case MISP_VIDOUT_1280x720p30:	return  R720P30;
		//case MISP_VIDOUT_1280x720p25:	return  R720P25;
		//case MISP_VIDOUT_1280x720p30:	return  R720P30_TVI20;
		//case MISP_VIDOUT_1280x720p25:	return  R720P25_TVI20;

	#if defined(__USE_MDIN_i540__) || defined(__USE_MDIN_i550__)
		case MISP_VIDOUT_3840x2160p15:	return  R8M15;
		case MISP_VIDOUT_3840x2160p12:	return  R8M125;
		case MISP_VIDOUT_2560x1440p30:	return  RQHD30;
		case MISP_VIDOUT_2560x1440p25:	return  RQHD25;
	#endif
#endif
		
#if defined(__USE_59Hz_OUTPUT__)
		case MISP_VIDOUT_1920x1080p29:	return  R1080P30;
		case MISP_VIDOUT_1280x720p59:	return  R720P60;
#endif
		default:						return  R1080P30;	// default 1080p30
	}
}


void SetTVITx_Frmt(void)
{
	Init_TVITx_RegSet();
}


#endif	//__USE_TVI_TX__
