#ifndef _CINTERRUPT_H_
#define _CINTERRUPT_H_

enum
{
	INTRPT_NONE = 0,								// No interrupt
	INTRPT_CH_BTILE = 0x00000001,		// interrupt via bg tile change
	INTRPT_CH_FTILE = 0x00000002,		// interrupt via fg tile change
};

class CInterrupt
{
public:
  CInterrupt();

public:
  
};

#endif
