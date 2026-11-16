#ifndef REQ_H__16_11_2026__12_07
#define REQ_H__16_11_2026__12_07

#pragma once

#include "types.h"

//#include "G_HW_CONF.h"


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

__packed struct ManMsgHdr
{
	enum { VER = 1 };

	byte ver;
	byte magic;
	u16 dataLen;
	u16 dataCRC;
	u16 crc;
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

__packed struct ManMsg 
{
	ManMsgHdr hdr;
	u16 data[16];
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

__packed struct Rsp30
{
	ManMsgHdr hdr;

	__packed struct
	{
		u16 	rw;				
		u16 	amp; 			
		u16		step;
		u16		size;
		u16		filtr;		
		u16		channels;	
		float	spectPart;
		float	spectStep;
		u16		overlapp;
		u16		ampMax;
		u16		ampMid;
		u16		uTemp;			
		u16		data[2048];		
	} rsp;
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

__packed struct Rsp40
{
	ManMsgHdr hdr;

	__packed struct
	{
		u16 	rw;				//	1. ответное слово
		u16 	gain;		 	//	2. усиление текущее (0..15)
		u16		sl;				//	3. длина оцифровки (ushort)
		u16		st;				//	4. шаг оцифровки (ushort)
		u16		maxAmp;			//	6. максимальная амплитуда волнового пакета(ushort)
		u16		pow;			//	7. энергия волнового пакета(ushort)
		u16		uTemp;			//	8. температура в приборе(ushort)
		i16		iTemp;			//	9. температура в приборе(short)(0.1гр)
		i16		cpuTemp;		//	10. температура процессора(short)(0.1гр)
		u16		data[4096];		//	11-?. данные (до 4096шт)
	} rsp;
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

__packed struct Rsp30_new
{
	ManMsgHdr hdr;

	__packed struct
	{
		u16 	rw;				//	1. ответное слово
		u16 	gain; 			//	2. усиление текущее (0..15)
		u16		spktrNum;		//	3. количество окон спектра (ushort)
		float	freqStep;		//	4,5. Шаг частоты (float)
		u16		maxAmp;			//	6. максимальная амплитуда волнового пакета(ushort)
		u16 	pow;  			//	7. энергия волнового пакета(ushort)
		u16		uTemp;			//	8. температура в приборе(ushort)
		i16		iTemp;			//	9. температура в приборе(short)(0.1гр)
		i16		cpuTemp;		//	10. температура процессора(short)(0.1гр)
		u16		data[2048];		//	11-?. данные (до 2048шт)
	} rsp;
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

__packed struct Rsp40_new
{
	ManMsgHdr hdr;

	__packed struct
	{
		u16 	rw;				//	1. ответное слово
		u16 	gain;		 	//	2. усиление текущее (0..15)
		u16		sl;				//	3. длина оцифровки (ushort)
		u16		st;				//	4. шаг оцифровки (ushort)
		u16		maxAmp;			//	6. максимальная амплитуда волнового пакета(ushort)
		u16		pow;			//	7. энергия волнового пакета(ushort)
		u16		uTemp;			//	8. температура в приборе(ushort)
		i16		iTemp;			//	9. температура в приборе(short)(0.1гр)
		i16		cpuTemp;		//	10. температура процессора(short)(0.1гр)
		u16		data[4096];		//	11-?. данные (до 4096шт)
	} rsp;
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


#endif //REQ_H__16_11_2026__12_07
