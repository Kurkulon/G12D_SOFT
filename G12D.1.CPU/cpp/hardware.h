#ifndef HARDWARE_H__23_12_2013__11_37
#define HARDWARE_H__23_12_2013__11_37

#include "G12D_1_HW_CONF.H"
#include "types.h"
//#include "core.h"
#include "time.h"
#include "i2c.h"
#include "spi.h"

//#include "hw_nand.h"
//#include "hw_rtm.h"
//#include "MANCH\manch.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#define WINDOW_SIZE	256

struct WINDSC
{
	WINDSC*		next;
	u16			rw;
	u16			fireCount;
	u16			genWorkTime;
	u16			temp;
	u16			winCount;
	u16			m_data[WINDOW_SIZE];
	u16			b_data[WINDOW_SIZE];
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


inline i16 GetTemp() { extern i16 temp; return temp; }


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

extern void InitHardware();
extern void UpdateHardware();

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline i32 GetTempCPU() { extern i32 tempCPU; return tempCPU; }
inline u16 GetCoreVCC() { extern u16 coreVCC; return coreVCC; }

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

extern S_SPIM	spiadxl;

#endif // HARDWARE_H__23_12_2013__11_37
