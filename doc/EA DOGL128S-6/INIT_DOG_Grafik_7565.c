// Versorgung 3,3V, 4fach-Boost an
//------------------------------------------------------------------------------
// Konstanten fÅr ST7565
//------------------------------------------------------------------------------

#define DISPOFF      0xAE
#define DISPON       0xAF
#define DISPSTART    0x40
#define PAGEADR      0xB0
#define COLADRL      0x00
#define COLADRH      0x10
#define ADCNORMAL    0xA0
#define ADCREVERSE   0xA1
#define COMNORMAL    0xC0
#define COMREVERSE   0xC8
#define DISPNORMAL   0xA6
#define DISPREVERSE  0xA7
#define LCDBIAS9     0xA2
#define LCDBIAS7     0xA3
#define RESET        0xE2
#define SETPOWERCTRL 0x28
#define REGRESISTOR  0x20
#define SETCONTRAST  0x81
#define STATINDMODE  0xAC
#define BOOSTERRATIO 0xF8


//------------------------------------------------------------------------------
// Portdefinitionen
//------------------------------------------------------------------------------

#define DOGCSPORT	PORTC
#define DOGCS		7

#define DOGRESPORT	PORTC
#define DOGRES		6

#define DOGA0PORT	PORTC
#define DOGA0		5

#define DOGSCLPORT	PORTB
#define DOGSCL		0

#define DOGSIPORT	PORTB
#define DOGSI		1


//------------------------------------------------------------------------------
// Makrodefinitionen
//------------------------------------------------------------------------------

#define SetBit(adr, bnr)	( (adr) |=  (1 << (bnr)) )
#define ClrBit(adr, bnr)	( (adr) &= ~(1 << (bnr)) )

#define	DOGENABLE  ClrBit(DOGCSPORT, DOGCS)
#define	DOGDISABLE SetBit(DOGCSPORT, DOGCS)

#define	DOGCOMMAND ClrBit(DOGA0PORT, DOGA0)
#define	DOGDATA    SetBit(DOGA0PORT, DOGA0)


//-----------------------------------------------------------------------------------------

void dogSPIout(char out)
{
  char msk;

  msk = 0x80;
  do
   { ClrBit(DOGSCLPORT, DOGSCL);
     if(out & msk)
        SetBit(DOGSIPORT, DOGSI);
     else
        ClrBit(DOGSIPORT, DOGSI);
     SetBit(DOGSCLPORT, DOGSCL);
     msk >>= 1;
   }
  while(msk > 0);
}

//-----------------------------------------------------------------------------------------

void initDOGM132(void)
{
  contrast = 33;
  Xpixel   = 132;
  Ypages   = 4;

  DOGENABLE;
  DOGCOMMAND;

  dogSPIout(DISPSTART + 0);
  if(topview)
   { xoffset = 0;
     dogSPIout(ADCNORMAL);
     dogSPIout(COMREVERSE);
   }
  else
   { xoffset = 0;
     dogSPIout(ADCREVERSE);
     dogSPIout(COMNORMAL);
   }
  dogSPIout(DISPNORMAL);
  dogSPIout(LCDBIAS9);
  dogSPIout(SETPOWERCTRL+7);
  dogSPIout(BOOSTERRATIO);     dogSPIout(0);
  dogSPIout(REGRESISTOR+3);
  dogSPIout(SETCONTRAST);      dogSPIout(contrast);
  dogSPIout(STATINDMODE);      dogSPIout(0);
  dogSPIout(DISPON);

  DOGDISABLE;
}

//-----------------------------------------------------------------------------------------

void initDOGM128(void)
{
  contrast = 22;
  Xpixel   = 128;
  Ypages   = 8;

  DOGENABLE;
  DOGCOMMAND;

  dogSPIout(DISPSTART + 0);
  if(topview)
   { xoffset = 4;
     dogSPIout(ADCNORMAL);
     dogSPIout(COMREVERSE);
   }
  else
   { xoffset = 0;
     dogSPIout(ADCREVERSE);
     dogSPIout(COMNORMAL);
   }
  dogSPIout(DISPNORMAL);
  dogSPIout(LCDBIAS9);
  dogSPIout(SETPOWERCTRL+7);
  dogSPIout(BOOSTERRATIO);     dogSPIout(0);
  dogSPIout(REGRESISTOR+7);
  dogSPIout(SETCONTRAST);      dogSPIout(contrast);
  dogSPIout(STATINDMODE);      dogSPIout(0);
  dogSPIout(DISPON);

  DOGDISABLE;
}

//-----------------------------------------------------------------------------------------

void initDOGL128(void)
{
  contrast = 16;
  Xpixel   = 128;
  Ypages   = 8;

  DOGENABLE;
  DOGCOMMAND;

  dogSPIout(DISPSTART + 0);
  if(topview)
   { xoffset = 4;
     dogSPIout(ADCNORMAL);
     dogSPIout(COMREVERSE);
   }
  else
   { xoffset = 0;
     dogSPIout(ADCREVERSE);
     dogSPIout(COMNORMAL);
   }
  dogSPIout(DISPNORMAL);
  dogSPIout(LCDBIAS9);
  dogSPIout(SETPOWERCTRL+7);
  dogSPIout(BOOSTERRATIO);     dogSPIout(0);
  dogSPIout(REGRESISTOR+7);
  dogSPIout(SETCONTRAST);      dogSPIout(contrast);
  dogSPIout(STATINDMODE);      dogSPIout(0);
  dogSPIout(DISPON);

  DOGDISABLE;
}

//-----------------------------------------------------------------------------------------

void ResetDOG(void)
{
  SetBit(DOGCSPORT,  DOGCS);
  SetBit(DOGSCLPORT, DOGSCL);
  SetBit(DOGSIPORT,  DOGSI);
  SetBit(DOGA0PORT,  DOGA0);

  ClrBit(DOGRESPORT,  DOGRES);
  waitus(5);
  SetBit(DOGRESPORT,  DOGRES);
}

//-----------------------------------------------------------------------------------------

void DogKontrast(void)
{
  DOGENABLE;
  DOGCOMMAND;

  dogSPIout(SETCONTRAST);
  dogSPIout(contrast);

  DOGDISABLE;
}

