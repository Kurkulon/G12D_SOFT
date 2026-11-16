#ifndef HARDWARE_H__23_12_2013__11_37
#define HARDWARE_H__23_12_2013__11_37

#include "G12D_1_HW_CONF.H"
#include "time.h"
#include "i2c.h"
#include "spi.h"
#include <MEM\mem.h>

//#include "hw_nand.h"
//#include "hw_rtm.h"
//#include "MANCH\manch.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


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

inline void StartLF() { extern bool cmdStartLF; cmdStartLF = true;  }
inline void StartHF() { extern bool cmdStartHF; cmdStartHF = true;  }

extern Ptr<MB> GetReadyLF();
extern Ptr<MB> GetReadyHF();

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//extern S_SPIM	spiadxl;

#endif // HARDWARE_H__23_12_2013__11_37
