// ----------------------------------------------------------------------
// Include files
// ----------------------------------------------------------------------
#include	<string.h>
#include	"video.h"

#if	defined(__USE_CMOS_MN34220__)
// ----------------------------------------------------------------------
// Struct/Union Types and define
// ----------------------------------------------------------------------
#define	NORMAL_30FPS_MODE
//#define	NORMAL_60FPS_MODE

// ----------------------------------------------------------------------
// Static Global Data section variables
// ----------------------------------------------------------------------

//#define LAMP_PATTERN
// ----------------------------------------------------------------------
// External Variable 
// ----------------------------------------------------------------------

// ----------------------------------------------------------------------
// Static Prototype Functions
// ----------------------------------------------------------------------
static void INIT_Normal_4CH_MODE(void);

// ----------------------------------------------------------------------
// Static functions
// ----------------------------------------------------------------------

// ----------------------------------------------------------------------
// Exported functions
// ----------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------------
void MN34220_Initialize(void)
{
	INIT_Normal_4CH_MODE();
	UARTprintf("MN34220_Initialize\n\r");
}

//--------------------------------------------------------------------------------------------------------------------------
static void INIT_Normal_4CH_MODE(void)
{
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3000, 0x0000);  //Reset clocks

	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3022, 0x3310);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x300E, 0x0001);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3002, 0x1806);

#if defined(__CMOS_OSC_37125__) // 37.125MHz
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x0304, 0x0200);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x0306, 0x2400);	
#else // 27MHz
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x0304, 0x0100);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x0306, 0x2100);
#endif
	
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3000, 0x0300);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x0102, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x0104, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x0110, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x0112, 0x0C0C);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x0120, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x0300, 0x1000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x0302, 0x0100);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3004, 0x6403);
#if defined(NORMAL_60FPS_MODE)
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3006, 0x1000);
#else
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3006, 0x1400);
#endif
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3008, 0x0691); // 1 ch 6 port
//	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3008, 0x0690); // 2 ch 3 port
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x300A, 0x00FF);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x300C, 0x0100);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3010, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3012, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3014, 0x0100);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3016, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3018, 0x1043);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x301A, 0x00B9);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x301C, 0x1B2B);

  if(GetSS_SensorVoutPAL())
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x301E, 0x100D);
  else
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x301E, 0x1F0D);

	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3020, 0x0008);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3000, 0x5300);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x300E, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x00FF, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x00FF, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x00FF, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x00FF, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x00FF, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x0202, 0x3102);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x0204, 0x0001);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x020E, 0x0001);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x0210, 0x0001);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x0212, 0x0001);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x0214, 0x0001);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x0220, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x033E, 0x0000);

	WORD vmax=0x0465;
	WORD hmax=0x0898*1;
#if defined(__VTOTAL_CTRL_PAL__)
	if(GetSS_SensorVoutPAL())  vmax*=1.2f;
#else
	if(GetSS_SensorVoutPAL())  hmax*=1.2f;
#endif
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x0340, BYTESWAP(vmax));
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x0342, BYTESWAP(hmax));

	CMOS_WordWrite(SPI_MN34220_ADDR, 0x0344, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x0346, 0x3C00);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x0348, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x034A, 0x7F04);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x034C, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x034E, 0x4404);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x0380, 0x0100);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x0382, 0x0100);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x0384, 0x0100);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x0386, 0x0100);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x0500, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x0600, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x0602, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x0604, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x0606, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x0608, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x060A, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x060C, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x060E, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x0610, 0x0000);

  if(GetSS_SensorVoutPAL())
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3030, 0x0000);
  else
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3030, 0x0004);

	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3032, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3034, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3036, 0x1000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3038, 0x2EFF);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x303A, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x303C, 0x2800);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x303E, 0x0303);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3040, 0x2CC0);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3042, 0x1050);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3044, 0x0000);
#if defined(LAMP_PATTERN)
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3050, 0x082D);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3052, 0x2201);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3054, 0x0000);
#else
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3050, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3052, 0x2290);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3054, 0x0030);
#endif
	
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3056, 0xFF01);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3058, 0xFE0F);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x305A, 0x0100);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x305C, 0x3100);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x305E, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3060, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3062, 0x1420);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3064, 0x3210);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3066, 0x0200);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3068, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x306A, 0x0300);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x306C, 0x0100);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x306E, 0x000C);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3070, 0xFF3F);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3072, 0xFF3F);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3074, 0x0101);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3076, 0x0042);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3078, 0x1300);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x307A, 0x3012);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x307C, 0x102B);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x307E, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3080, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3082, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3084, 0x3000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3086, 0x0323);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3088, 0x0414);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x308A, 0x0B01);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x308C, 0x0408);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x308E, 0x0904);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3090, 0x0005);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3092, 0x0900);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3094, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3096, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3098, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x309A, 0x0001);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x309C, 0x5453);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x309E, 0x0001);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3100, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3102, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3104, 0x0004);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3106, 0xC000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3108, 0x0001);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x310A, 0x0001);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x310C, 0x0001);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x310E, 0x0001);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3110, 0x0001);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3112, 0x0001);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3114, 0x0001);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3116, 0x0001);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3118, 0x0001);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x311A, 0x0001);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x311C, 0x0001);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x311E, 0x0001);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3120, 0x0001);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3122, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3124, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3126, 0x0200);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3128, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x312A, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x312C, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x312E, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3130, 0x010F);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3132, 0x1067);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3134, 0x0870);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3136, 0xFF03);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3138, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x313A, 0x0100);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x313C, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3140, 0x4000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3142, 0x0250);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3144, 0x0202);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3146, 0x0200);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3148, 0x0202);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x314A, 0x0201);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x314C, 0x0202);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x314E, 0x0201);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3150, 0x0102);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3152, 0xE304);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3154, 0xCA00);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3156, 0xCA00);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3158, 0xCA00);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x315A, 0xCA00);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x315C, 0xCA00);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x315E, 0xCA00);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3160, 0xCA00);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3162, 0xCA00);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3164, 0xCA00);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3166, 0xCA00);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3168, 0xCA00);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x316A, 0xCA00);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x316C, 0xCA00);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x316E, 0xC600);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3170, 0xCA00);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3172, 0xCA00);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3174, 0x800B);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3176, 0xA088);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3178, 0x0008);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x317A, 0xA2A0);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x317C, 0x02A0);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x317E, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3180, 0x8200);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3182, 0x2020);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3184, 0x0002);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3186, 0x1048);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3188, 0xDE00);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x318A, 0x0F6B);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x318C, 0x001F);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x318E, 0x7020);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3190, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3192, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3194, 0x4000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3196, 0x0608);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3198, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x319A, 0x100E);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x319C, 0x5432);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x319E, 0x9876);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31A0, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31A2, 0x1000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31A4, 0x5432);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31A6, 0x0986);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31A8, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31AA, 0x2400);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31AC, 0x8900);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31AE, 0x0002);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31B0, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31B2, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31B4, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31B6, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31B8, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31BA, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31BC, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31BE, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31C0, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31C2, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31C4, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31C6, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31C8, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31CA, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31CC, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31CE, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31D0, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31D2, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31D4, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31D6, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31D8, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31DA, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31DC, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31DE, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31E0, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31E2, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31E4, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31E6, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31E8, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31EA, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31EC, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31EE, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31F0, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31F2, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31F4, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31F6, 0x0300);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31F8, 0x0303);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31FA, 0x0806);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31FC, 0x0802);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x31FE, 0x0007);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3200, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3202, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3204, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3206, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3208, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x320A, 0x0900);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x320C, 0x1A00);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x320E, 0x1B00);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3210, 0x1B00);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3212, 0x0B03);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3214, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3216, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3218, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x321A, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x321C, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x321E, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3220, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3222, 0xFFFF);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3224, 0xFFFF);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3226, 0xFFFF);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3228, 0xFFFF);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x322A, 0xFFFF);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x322C, 0xFFFF);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x322E, 0xFFFF);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3230, 0xFFFF);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3232, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3234, 0xBA01);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3236, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3238, 0xBA01);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x323A, 0x8101);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x323C, 0x8071);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x323E, 0x0001);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3240, 0x1115);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3242, 0xD700);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3244, 0x1800);
#if defined(NORMAL_60FPS_MODE)
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3246, 0x7901);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3248, 0x0000);
#else
  if(GetSS_SensorVoutPAL()) {
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3246, 0x6103);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3248, 0xC802);
  }
  else {
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3246, 0x3801);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3248, 0xE203);
  }
#endif
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x324A, 0x1830);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x324C, 0x0002);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x324E, 0x1800);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3250, 0x0E31);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3252, 0xDE00);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3254, 0x0803);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3256, 0x0011);
#if defined(NORMAL_60FPS_MODE)
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3258, 0x4901);
#else
  if(GetSS_SensorVoutPAL())
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3258, 0x3103);
  else
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3258, 0x6801);
#endif
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x325A, 0x0039);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x325C, 0x0C00);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x325E, 0x0084);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3260, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3270, 0x0001);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3272, 0xAB46);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3274, 0x1801);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3280, 0x1030);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3282, 0x000E);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3284, 0x1B00);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3286, 0x0018);

#if defined(LAMP_PATTERN)
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3288, 0x0000);
#else
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3288, 0x0001);
#endif	
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x328A, 0x04E8);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x328C, 0x0075);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3300, 0x0103);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3302, 0x0700);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3304, 0x0A06);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3306, 0x1919);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3308, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x330A, 0x1E1E);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x330C, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x330E, 0x1105);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3310, 0x0002);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3312, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3314, 0x1F03);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3316, 0x000A);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3318, 0x0006);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x331A, 0x0202);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x331C, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x331E, 0x0303);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3320, 0x0101);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3322, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3324, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3326, 0x000A);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3328, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x332A, 0x0303);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x332C, 0x0002);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x332E, 0x000A);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3330, 0x0006);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3332, 0x0012);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3334, 0x0003);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3336, 0x0303);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3338, 0x0200);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x333A, 0x0008);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x333C, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x333E, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3340, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3342, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3344, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3346, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3348, 0x0007);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x334A, 0x0005);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x334C, 0x1C05);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x334E, 0x0300);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3350, 0x080E);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3352, 0x0506);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3354, 0x1908);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3356, 0x0300);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3358, 0x0B09);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x335A, 0x000D);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x335C, 0x0100);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x335E, 0x010D);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3360, 0x070D);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3362, 0x000D);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3364, 0x0100);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3366, 0x000D);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3368, 0x010D);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x336A, 0x0300);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x336C, 0x0003);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x336E, 0x0002);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3370, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3372, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3374, 0x0002);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3376, 0x0106);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3378, 0x0606);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x337A, 0x0009);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x337C, 0x000D);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x337E, 0x0100);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3380, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3382, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3384, 0x000D);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3386, 0x0100);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3388, 0x000D);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x338A, 0x0100);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x338C, 0x0804);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x338E, 0x090A);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3390, 0x0F02);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3392, 0x0904);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3394, 0x0A01);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3396, 0x1807);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3398, 0x0100);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x339A, 0x0801);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x339C, 0x010D);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x339E, 0x0300);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x33A0, 0x0100);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x33A2, 0x0303);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x33A4, 0x0300);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x33A6, 0x0006);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x33A8, 0x0000);

#if defined(LAMP_PATTERN)
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x33AA, 0x0501);
#else
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x33AA, 0x0000);
#endif
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x33AC, 0x1403);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x33AE, 0x113F);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x33B0, 0x1A0A);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x33B2, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x33B4, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x00FF, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x00FF, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x00FF, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x00FF, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x00FF, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x00FF, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x00FF, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x00FF, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x00FF, 0x0000);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3000, 0xD300);
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x0100, 0x0001);
}

//--------------------------------------------------------------------------------------------------------------------------
static void stMN34220_SetRate(MN34220_Mode_t mode) {
	#define REG_NUM  8

	ROMDATA WORD reg_set_addr[REG_NUM]={
		 0x0306, 0x3006, 0x301E, 0x3030, 0x3202, 0x3246, 0x3248, 0x3258};

	ROMDATA WORD reg_set_val[MN34220_FPS_NUM][REG_NUM]={
		{0x2100, 0x1000, 0x1F0D, 0x0004, 0x0000, 0x7901, 0x0000, 0x4901},  //MN34220_FPS_60Hz
		{0x2100, 0x1000, 0x100D, 0x0000, 0x0000, 0x6103, 0x0000, 0x3103},  //MN34220_FPS_50Hz
		{0x2100, 0x1400, 0x1F0D, 0x0004, 0x0000, 0x3801, 0xE203, 0x6801},  //MN34220_FPS_30Hz
		{0x2100, 0x1400, 0x100D, 0x0000, 0x0000, 0x6103, 0xC802, 0x3103},  //MN34220_FPS_25Hz
#if defined(__MDIN_i5XX_FPGA__)  //FPGA (Half FPS - reg.3006h)
		{0x2100, 0x1400, 0x100D, 0x0000, 0x0000, 0xD601, 0x0000, 0xE601},  //MN34220_FPS_60Hz_DOL2
		{0x2100, 0x1400, 0x100D, 0x0000, 0x0000, 0x1C01, 0x0000, 0x2C01},  //MN34220_FPS_50Hz_DOL2
		{0x2100, 0x1400, 0x100D, 0x0000, 0x3503, 0xC900, 0x0000, 0x5C00},  //MN34220_FPS_90Hz_DOL3 (445.5M)
		{0x2100, 0x1400, 0x100D, 0x0000, 0xDE03, 0xB400, 0x0000, 0xEB00},  //MN34220_FPS_75Hz_DOL3 (445.5M)
		{0x2C00, 0x1400, 0x100D, 0x0000, 0x3503, 0xC900, 0x0000, 0x5C00},  //MN34220_FPS_120Hz_DOL3 (594M)
		{0x2C00, 0x1400, 0x100D, 0x0000, 0xDE03, 0xB400, 0x0000, 0xEB00},  //MN34220_FPS_100Hz_DOL3 (594M)
#else
		{0x2100, 0x1000, 0x100D, 0x0000, 0x0000, 0xD601, 0x0000, 0xE601},  //MN34220_FPS_60Hz_DOL2
		{0x2100, 0x1000, 0x100D, 0x0000, 0x0000, 0x1C01, 0x0000, 0x2C01},  //MN34220_FPS_50Hz_DOL2
		{0x2100, 0x1000, 0x100D, 0x0000, 0x3503, 0xC900, 0x0000, 0x5C00},  //MN34220_FPS_90Hz_DOL3 (445.5M)
		{0x2100, 0x1000, 0x100D, 0x0000, 0xDE03, 0xB400, 0x0000, 0xEB00},  //MN34220_FPS_75Hz_DOL3 (445.5M)
		{0x2C00, 0x1000, 0x100D, 0x0000, 0x3503, 0xC900, 0x0000, 0x5C00},  //MN34220_FPS_120Hz_DOL3 (594M)
		{0x2C00, 0x1000, 0x100D, 0x0000, 0xDE03, 0xB400, 0x0000, 0xEB00},  //MN34220_FPS_100Hz_DOL3 (594M)
#endif
	};

	MN34220_Fps_t fps;
	switch(mode) {
		case MN34220_WDR:
#if	defined(__MDIN_i5XX_FPGA__)
			if(GetSS_SensorVoutPAL())  fps=MN34220_FPS_25Hz;
			else                       fps=MN34220_FPS_30Hz;
#else
			if(GetSS_SensorVoutPAL())  fps=MN34220_FPS_50Hz;  //50Hz->25Hz
			else                       fps=MN34220_FPS_60Hz;  //60Hz->35Hz
#endif
			break;
		case MN34220_DOL2:  //n/a
			if(GetSS_SensorVoutPAL())  fps=MN34220_FPS_50Hz_DOL2;
			else                       fps=MN34220_FPS_60Hz_DOL2;
			break;
		case MN34220_DOL3:
#if WDR_DOL_OVER_SYN  //445.5Mbps system
			if(GetSS_SensorVoutPAL())  fps=MN34220_FPS_75Hz_DOL3;  //75Hz->25Hz
			else					   fps=MN34220_FPS_90Hz_DOL3;  //90Hz->30Hz
#else  //594Mbps system
			if(GetSS_SensorVoutPAL())  fps=MN34220_FPS_100Hz_DOL3;	//100Hz->25Hz
			else					   fps=MN34220_FPS_120Hz_DOL3;	//120Hz->30Hz
#endif
			break;
		default:
			if     (GetSS_SensorVoutFps()==60)  fps=MN34220_FPS_60Hz;
			else if(GetSS_SensorVoutFps()==50)  fps=MN34220_FPS_50Hz;
			else if(GetSS_SensorVoutFps()==25)  fps=MN34220_FPS_25Hz;
			else                                fps=MN34220_FPS_30Hz;
			break;
	}

	BYTE i;
	for(i=0; i<REG_NUM; i++) {
		CMOS_WordWrite(SPI_MN34220_ADDR, reg_set_addr[i], reg_set_val[fps][i]);
	}

	//set H/V size
	WORD hmax, vmax;
	switch(mode) {
		case MN34220_DOL2:  hmax=2200*2;  vmax=1125;  break;  //n/a
#if WDR_DOL_OVER_SYN  //445.5Mbps system
		case MN34220_DOL3:	hmax=2200*3;  vmax=1125;  break;
#else 
		case MN34220_DOL3:	hmax=2200*3;  vmax=1500;  break;
#endif
		default:            hmax=2200*1;  vmax=1125;  break;
	}
#if defined(__VTOTAL_CTRL_PAL__)
	if(GetSS_SensorVoutPAL())  vmax*=1.2f;
#else
	if(GetSS_SensorVoutPAL())  hmax*=1.2f;
#endif
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x0340, BYTESWAP(vmax));
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x0342, BYTESWAP(hmax));
	return;
}

//--------------------------------------------------------------------------------------------------------------------------
static void stMN34220_SetMode(MN34220_Mode_t mode) {
	#define REG_MODE_NUM  60

	//reg.3280h : OB speed (1030:slow, 1000:fast)
	//reg.3054h : OB reset (0035:reset, 0030:default)
	WORD reg_set_addr[REG_MODE_NUM]={
		0x3004, 0x3008, 0x0202, 0x3040, 0x3058, 0x306E, 0x3098, 0x309A,
		0x3100, 0x3106, 0x312A, 0x312C, 0x312E, 0x3140, 0x3142, 0x3144,
		0x3146, 0x3148, 0x314A, 0x314C, 0x314E, 0x3150, 0x3152, 0x3154,
		0x3156, 0x3158, 0x315A, 0x315C, 0x315E, 0x3160, 0x3162, 0x3164,
		0x3166, 0x3168, 0x316A, 0x316C, 0x316E, 0x3170, 0x3172, 0x31FC,
		0x31FE, 0x3200, 0x323C, 0x323E, 0x3242, 0x324A, 0x3252, 0x3256,
		0x325A, 0x3272, 0x3280, 0x3282, 0x3284, 0x3288, 0x331A, 0x332C,
		0x3338, 0x336A, 0x339E, 0x33A2 };

	WORD reg_set_norm[REG_MODE_NUM]={
		0x6403, 0x0691, 0x6304, 0x2CC0, 0xFE0F, 0x000C, 0x0000, 0x0001,
		0x0000, 0xC000, 0x0000, 0x0000, 0x0000, 0x4000, 0x0250, 0x0202,
		0x0200, 0x0202, 0x0201, 0x0202, 0x0201, 0x0102, 0xE304, 0xCA00,
		0xCA00, 0xCA00, 0xCA00, 0xCA00, 0xCA00, 0xCA00, 0xCA00, 0xCA00,
		0xCA00, 0xCA00, 0xCA00, 0xCA00, 0xC600, 0xCA00, 0xCA00, 0x0802,
		0x0007, 0x0000, 0x8071, 0x0001, 0xD700, 0x1830, 0xDE00, 0x0011,
		0x0039, 0xAB46, 0x1030, 0x000E, 0x1B00, 0x0001, 0x0202, 0x0002,
		0x0200, 0x0300, 0x0300, 0x0303 };

	WORD reg_set_dol2[REG_MODE_NUM]={
		0x6703, 0x0691, 0x2000, 0x2CC0, 0xFE0F, 0x000C, 0x0000, 0x0001,
		0x0100, 0xC000, 0x0000, 0x0000, 0x0000, 0x4000, 0x0350, 0x0304,
		0x0505, 0x0202, 0x0305, 0x0706, 0x0606, 0x0107, 0xE306, 0xCA00,
		0xCA00, 0xCA00, 0xCA00, 0xCA00, 0xCA00, 0xCA00, 0xCA00, 0xCA00,
		0xCA00, 0xCA00, 0xCA00, 0xCA00, 0xC600, 0xCA00, 0xCA00, 0x0802,
		0x0007, 0x0000, 0x8070, 0x0000, 0xD100, 0x1830, 0xD400, 0x0011,
		0x0039, 0xAB55, 0x1000, 0x000E, 0x1B00, 0x0001, 0x0202, 0x0002,
		0x0200, 0x0300, 0x0300, 0x0303 };

	WORD reg_set_dol3[REG_MODE_NUM]={
		0x6704, 0x0601, 0x2000, 0x12C0, 0xFE03, 0x0009, 0x0004, 0x0010,
		0x0200, 0x4000, 0x0000, 0x0000, 0x0000, 0x7000, 0x0150, 0x0203,
		0x0005, 0x0000, 0x0103, 0x0101, 0x0202, 0x0102, 0x0701, 0x1100,
		0x3000, 0x3300, 0x3600, 0x3500, 0x3C00, 0x3F00, 0x3A00, 0x3900,
		0x2800, 0x2B00, 0x2E00, 0x2D00, 0x2200, 0x2200, 0x6100, 0x0803,
		0x0006, 0x0100, 0x8070, 0x0000, 0x7500, 0x1B30, 0x7B00, 0x0032,
		0x0014, 0xAB0C, 0x1000, 0x0007, 0x1900, 0x4000, 0x0303, 0x0000,
		0x0300, 0x0200, 0x0100, 0x0101 };

	PWORD pReg_set_val;
	switch(mode) {
		case MN34220_DOL2:  pReg_set_val=reg_set_dol2;  break;
		case MN34220_DOL3:  pReg_set_val=reg_set_dol3;  break;
		default:            pReg_set_val=reg_set_norm;  break;
	}

	BYTE i;
	for(i=0; i<REG_MODE_NUM; i++) {
		CMOS_WordWrite(SPI_MN34220_ADDR, reg_set_addr[i], pReg_set_val[i]);
	}
}


//--------------------------------------------------------------------------------------------------------------------------
void MN34220_ChangeFps_Normal(void) {
	//normal mode frame rate
	stMN34220_SetRate(MN34220_NORMAL);
}

//--------------------------------------------------------------------------------------------------------------------------
void MN34220_WDR_Mode(MN34220_Mode_t mode) {
	//[MN34220_DOL2] may not work properly since deserializer does not support 4ch line mode.

	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3000, 0x5300);  //TG reset (H->L)
	stMN34220_SetRate(mode);  //set Rate(fps)
	stMN34220_SetMode(mode);  //set Mode
	CMOS_WordWrite(SPI_MN34220_ADDR, 0x3000, 0xD300);  //TG reset (L->H)
}

#endif	/* __USE_CMOS_MN34220__ */

/*  FILE_END_HERE */
