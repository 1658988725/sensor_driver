// ----------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------
#include	<string.h>
#include	"video.h"

#if	defined(__USE_CMOS_MN34041__)
// ----------------------------------------------------------------------
// Struct/Union Types and define
// ----------------------------------------------------------------------

// ----------------------------------------------------------------------
// Static Global Data section variables
// ----------------------------------------------------------------------

// ----------------------------------------------------------------------
// External Variable 
// ----------------------------------------------------------------------

// ----------------------------------------------------------------------
// Static Prototype Functions
// ----------------------------------------------------------------------

// ----------------------------------------------------------------------
// Static functions
// ----------------------------------------------------------------------

// ----------------------------------------------------------------------
// Exported functions
// ----------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------------
void MN34041_Initialize(void)
{
#if defined(__USE_FPGA_STRATIX2__)
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0001, 0x0009);	// 10fps
#endif

#if defined(__USE_FPGA_CYCLONE4__)
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0001, 0x0012);	// 20fps
#endif

//#if defined(__USE_FPGA_STRATIX4__)
//	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0001, 0x0009);	// 10fps
//	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0001, 0x0012);	// 20fps // c4
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0001, 0x001b);	// 30fps .. org // s4

//	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0001, 0x001e);	// 30fps .. org
//	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0001, 0x0021);	// 36fps .. WDR
//	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0001, 0x0024);	// 40fps .. test .. noise
//	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0001, 0x002b);	// 48fps .. WDR max NR x
//	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0001, 0x002d);	// 50fps
//	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0001, 0x002f);		// 52fps .. NR max	
//	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0001, 0x0030);	// 54fps	.. display max
//	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0001, 0x0036);	// 60fps
//#endif

	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0002, 0x0002);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0004, 0x01c2);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0000, 0x0003);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0003, 0x0209);

	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0006, 0x442a);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0005, 0x0000);
	Delay_mSec(1);
	
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0000, 0x0013);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0036, 0x0021);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0037, 0x0300);
	Delay_mSec(50);

//	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0020, 0x0080);
//	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0021, 0x0080);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0022, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0023, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0024, 0x0010);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0025, 0x0011);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0026, 0x0012);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0027, 0x0013);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0028, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0030, 0x0424);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0031, 0x110A);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0032, 0x7450);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0033, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0034, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0035, 0x0281);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0038, 0x0001);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0039, 0x0210);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x003a, 0x0333);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x003b, 0x0111);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x003f, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0040, 0x0004);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0041, 0x0200);
//	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0042, 0x0100);
//	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0043, 0x0070);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0044, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0045, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0046, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0047, 0x0010);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0048, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0049, 0x0002);
//	CMOS_WordWrite(SPI_MN34041_ADDR, 0x004a, 0x0ffe);
//	CMOS_WordWrite(SPI_MN34041_ADDR, 0x004b, 0x0004);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0056, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0057, 0x1fff);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0058, 0x2000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0059, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x005a, 0x0011);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0070, 0x2084);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0071, 0xffff);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0072, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0073, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0074, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0075, 0x0004);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0076, 0x0230);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0077, 0x0541);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0078, 0x0001);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0079, 0x0011);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0080, 0x0002);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0081, 0x0003);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0082, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0083, 0x0001);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0084, 0x0012);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0085, 0x0013);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0086, 0x0010);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0087, 0x0011);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0088, 0x000a);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0089, 0x000b);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x008a, 0x0008);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x008b, 0x0009);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x008c, 0x0006);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x008d, 0x0007);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x008e, 0x0004);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x008f, 0x0005);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0090, 0x0016);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0091, 0x0017);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0092, 0x0014);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0093, 0x0015);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0094, 0x001a);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0095, 0x001b);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0096, 0x0018);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0097, 0x0019);
//	CMOS_WordWrite(SPI_MN34041_ADDR, 0x00a0, 0x3000);
//	CMOS_WordWrite(SPI_MN34041_ADDR, 0x00a1, 0x0000);
//	CMOS_WordWrite(SPI_MN34041_ADDR, 0x00a2, 0x0002);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x00a3, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x00a4, 0x0000);
//	CMOS_WordWrite(SPI_MN34041_ADDR, 0x00a5, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x00a6, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x00a7, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x00a8, 0x000f);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x00a9, 0x0022);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x00c0, 0x5540);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x00c1, 0x5fd5);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x00c2, 0xf757);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x00c3, 0xdf5f);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x00c4, 0x208a);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x00c5, 0x0071);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x00c6, 0x0557);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x00c7, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x00ca, 0x0080);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x00cb, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x00cc, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x00cd, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x00ce, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0100, 0x03a8);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0101, 0x03a8);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0102, 0x02c0);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0103, 0x037a);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0104, 0x002b);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0105, 0x00de);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0106, 0x00fa);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0170, 0x0002);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0171, 0x000d);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0172, 0x0007);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0173, 0x0004);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0174, 0x002a);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0175, 0x0062);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0176, 0x0079);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0177, 0x0326);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0178, 0x0003);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0179, 0x0033);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x017a, 0x0360);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x017b, 0x0002);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x017c, 0x000d);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0190, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0191, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0192, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0193, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0194, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0195, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0196, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0197, 0x01ba);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0198, 0xb060);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0199, 0x7c0a);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x019a, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x019b, 0x0313);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x019c, 0x0b08);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x019d, 0x3906);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x019e, 0x0000);
//	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01a0, 0x0464);
//	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01a1, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01a2, 0x0000);
//	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01a3, 0x0464);
//	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01a4, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01a5, 0x0453);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01a6, 0x0000);
//	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01a7, 0x0464);
//	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01a8, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01a9, 0x0454);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01aa, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01ab, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01ac, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01ad, 0x0454);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01ae, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01af, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01b0, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01b1, 0x0454);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01b2, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01b3, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01b4, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01b5, 0x0454);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01b6, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01b7, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01b8, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01b9, 0x0453);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01ba, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01bb, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01bc, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01bd, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01be, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01c4, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01c5, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01c6, 0x0011);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0200, 0x03a8);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0201, 0x03a8);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0202, 0x02c0);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0203, 0x037a);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0204, 0x002b);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0205, 0x00de);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0206, 0x00fa);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0270, 0x0002);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0271, 0x000d);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0272, 0x0007);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0273, 0x0004);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0274, 0x002a);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0275, 0x0062);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0276, 0x0079);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0277, 0x0326);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0278, 0x0003);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0279, 0x0033);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x027a, 0x0360);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x027b, 0x0002);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x027c, 0x000d);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0290, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0291, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0292, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0293, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0294, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0295, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0296, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0297, 0x01ba);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0298, 0xb060);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0299, 0x7c0a);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x029a, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x029b, 0x0313);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x029c, 0x0b08);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x029d, 0x3906);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x029e, 0x0000);
//	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02a0, 0x0464);
//	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02a1, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02a2, 0x0000);
//	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02a3, 0x0464);
//	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02a4, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02a5, 0x0453);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02a6, 0x0000);
//	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02a7, 0x0464);
//	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02a8, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02a9, 0x0454);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02aa, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02ab, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02ac, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02ad, 0x0454);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02ae, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02af, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02b0, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02b1, 0x0454);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02b2, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02b3, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02b4, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02b5, 0x0454);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02b6, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02b7, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02b8, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02b9, 0x0453);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02ba, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02bb, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02bc, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02bd, 0x0453);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02be, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02c4, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02c5, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02c6, 0x0011);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0108, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0109, 0x000f);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x010a, 0x0009);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x010b, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x010c, 0x0016);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x010d, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x010e, 0x000f);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x010f, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0110, 0x0009);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0111, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0112, 0x0016);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0113, 0x0003);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0114, 0x000a);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0115, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0116, 0x0009);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0117, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0118, 0x0016);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0119, 0x0018);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x011a, 0x0017);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x011b, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x011c, 0x0002);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x011d, 0x0009);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x011e, 0x0012);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x011f, 0x0001);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0120, 0x003a);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0121, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0122, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0123, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0124, 0x0011);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0125, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0126, 0x0003);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0127, 0x0003);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0128, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0129, 0x0010);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x012a, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x012b, 0x0003);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x012c, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x012d, 0x0011);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x012e, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x012f, 0x0009);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0130, 0x0009);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0131, 0x0012);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0132, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0133, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0134, 0x0009);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0135, 0x0009);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0136, 0x0012);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0137, 0x0006);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0138, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0139, 0x0010);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x013a, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0140, 0x0020);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0141, 0x0036);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0142, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0143, 0x0001);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0144, 0x0003);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0145, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0146, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0150, 0x0011);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0151, 0x0001);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0152, 0x0001);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0153, 0x0001);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0154, 0x0010);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0155, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0156, 0x0003);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0157, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0158, 0x0013);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0159, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x015a, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x015b, 0x0008);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x015c, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x015d, 0x0004);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x015e, 0x0005);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x015f, 0x000a);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0160, 0x0006);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0161, 0x000f);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0162, 0x000d);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0163, 0x0004);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0164, 0x0002);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0165, 0x0002);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0166, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0167, 0x0010);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0168, 0x0009);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0169, 0x0003);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x016a, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x016b, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0180, 0x0017);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0181, 0x00c5);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0182, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0183, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0184, 0x00fa);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0185, 0x00a5);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0186, 0x01ef);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0187, 0x03d9);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0188, 0x01fb);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0189, 0x035f);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x018a, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x018b, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x018c, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x018d, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01d0, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01d1, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01d2, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01d3, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01d4, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01d5, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01d6, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01d7, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01d8, 0x0006);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01d9, 0x0005);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01da, 0x0001);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01db, 0x0006);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01dc, 0x0001);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01dd, 0x0007);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01de, 0x0001);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01df, 0x0002);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01e0, 0x0001);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01e1, 0x0001);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01e2, 0x00c9);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01e3, 0x8000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01e4, 0x003e);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01e5, 0x0015);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01e6, 0x003e);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01e7, 0x00c8);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01e8, 0x0043);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01e9, 0x00a9);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01ea, 0x00a9);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01eb, 0x00a9);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01ec, 0x00fb);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01ed, 0x00b0);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01ee, 0x00b9);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01ef, 0x01bb);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01f0, 0x02ec);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01f1, 0x02ec);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01f2, 0x02ec);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01f3, 0x01bd);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01f4, 0x034a);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01f5, 0x03d8);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01f6, 0x03fc);

	// set internal registers
//	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0000, 0x0013);
//	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0003, 0x0209);	// output = 12bit
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0020, 0x00c0);	// col/ana gain = 6db
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0021, 0x0090);	// digital gain = 1.49db

	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0042, 0x0100);	// OUT-Offset = 0x100
// jwlee 20120809
//	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0042, 0x0000);	// OUT-Offset = 0x000

	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0043, 0x0070);	// OB clamp = on
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x004a, 0x0ffe);	// MAX level = 0xffe
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x004b, 0x0004);	// MIN level = 0x004
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x00a0, 0x3000);	// flip off, full scan
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x00a2, 0x0002);	// shutter[16]
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x00a5, 0x0000);	// long exposure
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01a0, 0x0464);	// V-line[15:0]
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01a1, 0x0000);	// V-line[16]
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01a3, 0x0464);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01a4, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01a7, 0x0464);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x01a8, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02a0, 0x0464);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02a1, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02a3, 0x0464);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02a4, 0x0000);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02a7, 0x0464);
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x02a8, 0x0000);

#if defined(__USE_FPGA_STRATIX2__)
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x00a1, 0x03a8);	// shutter[15:0] = 1/60s at 10fps
#endif

#if defined(__USE_FPGA_CYCLONE4__)
//	CMOS_WordWrite(SPI_MN34041_ADDR, 0x00a1, 0x02ec);	// shutter[15:0] = 1/60s at 20fps
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x00a1, 0x0000);	// shutter[15:0] = 1/20s at 20fps
#endif

//#if defined(__USE_FPGA_STRATIX4__)
//	CMOS_WordWrite(SPI_MN34041_ADDR, 0x00a1, 0x0231);	// shutter[15:0] = 1/60s at 30fps
	CMOS_WordWrite(SPI_MN34041_ADDR, 0x00a1, 0x0000);	// shutter[15:0] = 1/30s at 30fps
//	CMOS_WordWrite(SPI_MN34041_ADDR, 0x00a1, 0x01c1);
	
//#endif

	CMOS_WordWrite(SPI_MN34041_ADDR, 0x0000, 0x0113);	// TG setting
}

#endif	/* __USE_CMOS_MN34041__ */

/*  FILE_END_HERE */