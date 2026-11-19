#include "hardware.h"
#include "CRC\CRC16_8005.h"
#include "list.h"
#include "PointerCRC.h"
#include "req.h"

#include "SEGGER_RTT\SEGGER_RTT.h"
//#include "hw_rtm.h"
//#include "hw_nand.h"
#include "DMA\DMA.h"
//#include "MANCH\manch.h"
//#include <math.h>
#include "spi.h"
#include <MEM\mem.h>
#include <math.h>

//#define WIN_TEST

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef PI
#define PI 3.1415926535897932384626433832795
#endif

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

struct complex_float
{
	float re;
	float im;
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

TaskList globalTaskList;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static u32 MUX_CS_MASK[] = { MUXSYNC };

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static S_SPIM	spimux(MUX_SERCOM_NUM, PIO_MUXSCLK, PIO_MUXDIN, PIO_MUXSDO, PIO_MUXSYNC, MUXSCLK, MUXDIN, MUXSDO, MUX_PMUX_SCLK, MUX_PMUX_DIN, MUX_PMUX_SDO, MUX_CS_MASK, ArraySize(MUX_CS_MASK), 
	MUX_DIPO_BITS, MUX_DOPO_BITS, MUX_GEN_SRC, MUX_GEN_CLK, MUX_DMA_TX_CH, MUX_DMA_RX_CH);

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//static u32 ADXL_CS_MASK[] = { ADXL_CS };

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//S_SPIM	spiadxl(ADXL_SERCOM_NUM, PIO_ADXLSPCK, PIO_ADXLMOSI, PIO_ADXLMISO, PIO_ADXL_CS, ADXLSPCK, ADXLMOSI, ADXLMISO, ADXL_PMUX_SPCK, ADXL_PMUX_MOSI, ADXL_PMUX_MISO, ADXL_CS_MASK, ArraySize(ADXL_CS_MASK), 
//	ADXL_DIPO_BITS, ADXL_DOPO_BITS, ADXL_GEN_SRC, ADXL_GEN_CLK, ADXL_DMA_TX_CH, ADXL_DMA_RX_CH);

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <ARM\system_imp.h>

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <time_imp.h>

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <SPIM_imp.h>

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static void WDT_Init()
{
	SEGGER_RTT_WriteString(0, RTT_CTRL_TEXT_BRIGHT_YELLOW "WDT Init ... ");

	#ifdef CPU_SAME53	

		HW::MCLK->APBAMASK |= APBA_WDT;
		HW::WDT->CONFIG = WDT_WINDOW_CYC512|WDT_PER_CYC1024;
		//while(HW::WDT->SYNCBUSY);

		#ifndef _DEBUG
		HW::WDT->CTRLA = WDT_ENABLE;
		#else
		HW::WDT->CTRLA = 0;
		#endif

		//while(HW::WDT->SYNCBUSY);

	#elif defined(CPU_XMC48)

		#ifndef _DEBUG
	
		//HW::WDT_Enable();

		//HW::WDT->WLB = OFI_FREQUENCY/2;
		//HW::WDT->WUB = (3 * OFI_FREQUENCY)/2;
		//HW::SCU_CLK->WDTCLKCR = 0|SCU_CLK_WDTCLKCR_WDTSEL_OFI;

		//HW::WDT->CTR = WDT_CTR_ENB_Msk|WDT_CTR_DSP_Msk;

		#else

		HW::WDT_Disable();

		#endif

	#endif

	SEGGER_RTT_WriteString(0, "OK\n");
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// GENTCC_OVF ->	WINTC_EVU(RETRIGER)
// 					BTCC_EV1(RETRIGER)
//					MTCC_EV1(RETRIGER)
// 
// DNNKB_EXTINT ->	DNNKB_EVSYS_CHANNEL -> BTCC0_EVSYS_USER(BTCC_EV_0)
// DNNKM_EXTINT ->	DNNKM_EVSYS_CHANNEL -> MTCC0_EVSYS_USER(MTCC_EV_0)
// 
// WINTC_OVF ->		BTCC_MC0 EVGEN_MC_0 -> bDMA(DMCH_TRIGSRC_MC0) -> DMCH_TCMPL B_DMA_IRQ(Win_DMA_IRQ)
//					MTCC_MC0 EVGEN_MC_0 -> mDMA(DMCH_TRIGSRC_MC0) -> DMCH_TCMPL M_DMA_IRQ(Win_DMA_IRQ)

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifdef ADC_TCC

	#define adcTCC						HW::ADC_TCC
	#define ADCTCC_GEN					CONCAT2(GEN_,ADC_TCC)
	#define ADCTCC_GEN_CLK				CONCAT2(CLK_,ADC_TCC) 
	#define ADCTCC_IRQ					CONCAT2(ADC_TCC,_0_IRQ)
	#define GCLK_ADCTCC					CONCAT2(GCLK_,ADC_TCC)
	#define PID_ADCTCC					CONCAT2(PID_,ADC_TCC)

	#if (ADCTCC_GEN_CLK > 100000000)
			#define ADCTCC_PRESC_NUM	1
	#elif (ADCTCC_GEN_CLK > 50000000)
			#define ADCTCC_PRESC_NUM	1
	#elif (ADCTCC_GEN_CLK > 20000000)
			#define ADCTCC_PRESC_NUM	1
	#elif (ADCTCC_GEN_CLK > 10000000)
			#define ADCTCC_PRESC_NUM	1
	#elif (ADCTCC_GEN_CLK > 5000000)
			#define ADCTCC_PRESC_NUM	1
	#else
			#define ADCTCC_PRESC_NUM	1
	#endif

	#define ADCTCC_PRESC_DIV			CONCAT2(TCC_PRESCALER_DIV,ADCTCC_PRESC_NUM)
	#define US2ADCTCC(v)				(((v)*(ADCTCC_GEN_CLK/ADCTCC_PRESC_NUM/1000)+500)/1000)

	//#define GENTCC_EVSYS_USER			CONCAT3(EVSYS_USER_, GEN_TCC, _EV_0)
	#define ADCTCC_EVENT_GEN			CONCAT3(EVGEN_, ADC_TCC, _OVF)
	#define ADCTCC_EVSYS_CHANNEL		(GENTCC_EVENT_GEN|EVSYS_PATH_ASYNCHRONOUS|EVSYS_EDGSEL_RISING_EDGE)

	#define ADCTCC_DMCH_TRIGSRC1		CONCAT3(DMCH_TRIGSRC_, ADC_TCC, _MC0)
	#define ADCTCC_DMCH_TRIGSRC2		CONCAT3(DMCH_TRIGSRC_, ADC_TCC, _MC1)

	inline void ADCTCC_ClockEnable()	{ HW::GCLK->PCHCTRL[GCLK_ADCTCC] = ADCTCC_GEN|GCLK_CHEN; HW::MCLK->ClockEnable(PID_ADCTCC); }

#else
	#error  Must defined ADC_TCC
#endif

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifdef ADC_SERCOM_NUM

	#define adcspi						CONCAT2(HW::SPI,ADC_SERCOM_NUM)
	#define ADCSPI_GEN					GEN_MCK
	#define ADCSPI_GEN_CLK				GEN_MCK_CLK
	#define GCLK_ADCSPI					CONCAT3(GCLK_SERCOM,ADC_SERCOM_NUM,_CORE)
	#define PID_ADCSPI					CONCAT2(PID_SERCOM,ADC_SERCOM_NUM)
	
	#define ADCSPI_DMCH_TRIGSRC			CONCAT3(DMCH_TRIGSRC_SERCOM,ADC_SERCOM_NUM,_RX)

	inline void ADCSPI_ClockEnable()	{ HW::GCLK->PCHCTRL[GCLK_ADCSPI] = ADCSPI_GEN|GCLK_CHEN; HW::MCLK->ClockEnable(PID_ADCSPI); }

#else
	#error  Must defined ADC_SERCOM_NUM
#endif

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//u32 m_ts[256];
//u32 b_ts[256];



//u16 temp = 0;


//static void* eepromData = 0;
//static u16 eepromWriteLen = 0;
//static u16 eepromReadLen = 0;
//static u16 eepromStartAdr = 0;

//inline u16 ReverseWord(u16 v) { __asm	{ rev16 v, v };	return v; }

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static DMA_CH lfDMA(LF_DMACH_NUM);
static DMA_CH hfDMA1(HF1_DMACH_NUM);
static DMA_CH hfDMA2(HF2_DMACH_NUM);
static DMA_CH hfDMAR(HFR_DMACH_NUM);

bool cmdStartLF = false;
bool cmdStartHF = false;

ListPtr<MB> readyLF;
ListPtr<MB> readyHF;

ListPtr<MB> processLF;
ListPtr<MB> processHF;

ListPtr<MB> spectrLF;
ListPtr<MB> spectrHF;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

i32 tempCPU = 0;
u16 PTAT = 0;
u16 CTAT = 0;
u16 coreVCC = 0;

static i32 temp_k1 = 0;
static i32 temp_k2 = 0;
static i16 temp_k3 = 0;
static i16 temp_k4 = 0; 

static i32 maxAmpHF = 0;

static byte gainDataBuf		= 0;
static byte mainGain		= 0;	// (0 - автоподстройка, 1..16)	
static byte autoGain		= 0;

static byte gainValue[16] = {1,2,3,4,5,6,7,8,11,12,13,14,15,16,17,18};

//	Усиление:
//	0	1
//	1	2
//	2	3.05
//	3	4.05
//	4	5.17
//	5	6.17
//	6	7.22
//	7	8.22
//	8	11
//	9	12
//	10	13.05
//	11	14.05
//	12	15.17
//	13	16.17
//	14	17.22
//	15	18.22

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static void SetGainDataBuf(byte gain) 
{
	gainDataBuf = (gain&15) | ((gain&15)<<4);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void SetGain(byte v) 
{
	mainGain = v;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Ptr<MB> GetReadyLF()
{
	return readyLF.Get();
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Ptr<MB> GetReadyHF()
{
	return readyHF.Get();
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Ptr<MB> GetSpectrLF()
{
	return spectrLF.Get();
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Ptr<MB> GetSpectrHF()
{
	return spectrHF.Get();
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

MB* AllocRsp30()
{
	MB* mb = AllocMemBuffer(sizeof(Rsp30));

	return mb;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

MB* AllocRsp40()
{
	MB* mb = AllocMemBuffer(sizeof(Rsp40));

	return mb;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

MB* AllocFFT()
{
	MB* mb = AllocMemBuffer(32768);

	return mb;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

complex_float _coef[16];

bool FFT(complex_float *data, u32 size, bool inverse)
{
	if ((size > (1u << 13)) || (size < (1u << 1))) return false;

	i32 size_pow = 0;

	while ((1u << (size_pow + 1)) <= size) size_pow++;

	size = (1u << size_pow);

	i32 i, j, n, k, io, ie, in, nn;
	float ru, iu, rtp, itp, rtq, itq, rw, iw, sr;
	
	nn = size >> 1;
	ie = size;
	
	for (n = 1; n <= size_pow; n++)
	{
		rw = _coef[size_pow - n].re;
		iw = _coef[size_pow - n].im;
		
		if (inverse) iw = -iw;
		
		in = ie >> 1;
		ru = 1.0f;
		iu = 0.0f;
		
		for (j = 0; j < in; j++)
		{
			for (i = j; i < size; i += ie)
			{
				io = i + in;
				rtp = data[i].re + data[io].re;
				itp = data[i].im + data[io].im;
				rtq = data[i].re - data[io].re;
				itq = data[i].im - data[io].im;
				data[io].re = rtq * ru - itq * iu;
				data[io].im = itq * ru + rtq * iu;
				data[i].re = rtp;
				data[i].im = itp;
			};

			sr = ru;
			ru = ru * rw - iu * iw;
			iu = iu * rw + sr * iw;
		};

		ie >>= 1;
	};

	for (j = i = 1; i < size; i++)
	{
		if (i < j)
		{
			io = i - 1;
			in = j - 1;
			rtp = data[in].re;
			itp = data[in].im;
			data[in].re = data[io].re;
			data[in].im = data[io].im;
			data[io].re = rtp;
			data[io].im = itp;
		};

		k = nn;

		while (k < j)
		{
			j = j - k;
			k >>= 1;
		};

		j = j + k;
	};

	//if (inverse) return true;

	//rw = 1.0f / (size);
	//
	//for (i = 0; i < (size); i++)
	//{
	//	data[i].re *= rw;
	//	data[i].im *= rw;
	//};

	return true;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Init_FFT()
{
	for (u32 i = 0; i < ArraySize(_coef); i++)
	{
		_coef[i].re = cosf(-PI / (1u << i));
		_coef[i].im = sinf(-PI / (1u << i));
	}
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static Ptr<MB> mb_Update_LF;
static Ptr<MB> fft_Update_LF;
static Ptr<MB> sp_Update_LF;

static void Update_LF()
{
	static byte i = 0;
	static DSCSPI dsc;

	Ptr<MB> &mb		= mb_Update_LF;
	Ptr<MB> &fft	= fft_Update_LF;
	Ptr<MB> &sp		= sp_Update_LF;

	switch (i)
	{
		case 0:

			if (cmdStartLF)
			{
				mb = AllocRsp40();

				if (mb.Valid())
				{
					cmdStartLF = false;

					Rsp40 &rsp = *((Rsp40*)mb->GetDataPtr());

					lfDMA.ReadPeripheral(&HW::ADC0->RESULT, (void*)(rsp.rsp.data-1), ArraySize(rsp.rsp.data)+1, DMCH_TRIGACT_BURST|DMCH_TRIGSRC_ADC0_RESRDY, DMDSC_BEATSIZE_HWORD|DMDSC_BLOCKACT_NOACT); 

					i++;
				};
			};

			break;

		case 1:

			if (lfDMA.CheckComplete())
			{
				i++;
			};

			break;

		case 2:

			fft = AllocFFT();

			if (fft.Valid())
			{
				Rsp40 &rsp = *((Rsp40*)mb->GetDataPtr());

				complex_float *fftbuf = (complex_float*)fft->GetDataPtr();

				__packed u16 *p = rsp.rsp.data;

				i32 max = 0;
				u32 sum = 0;

				for(u16 n = 0; n < ArraySize(rsp.rsp.data); n++)
				{
					i32 t = p[0]; t -= 32768; *(p++) = t;
					//i32 t = (n&2) ? 32767 : -32767; *(p++) = t;

					fftbuf[n].re = t;
					fftbuf[n].im = 0;

					if (t < 0) t = -t;

					if (t > max) max = t;

					sum += t;
				};

				rsp.rsp.gain	= autoGain;
				rsp.rsp.sl		= ArraySize(rsp.rsp.data);
				rsp.rsp.st		= 10000;
				rsp.rsp.maxAmp	= max;
				rsp.rsp.pow		= sum / rsp.rsp.sl;

				if (maxAmpHF > max) max = maxAmpHF;

				maxAmpHF = 0;

				if (mainGain == 0) // 0 - автоподстройка
				{
					if (max > 30000)
					{
						if (autoGain > 0) autoGain -= 1;
					}
					else
					{
						i32 amp = max/gainValue[autoGain];

						for (byte n = autoGain; n < ArraySize(gainValue); n++)
						{
							autoGain = n;

							max = amp*gainValue[n];

							if (max > 24000) break;
						};

						if (max > 30000)
						{
							if (autoGain > 0) autoGain -= 1;
						};
					};
				}
				else
				{
					autoGain = mainGain-1;
				};

				SetGainDataBuf(autoGain);

				i++;

			};
			
			break;

		case 3:

			dsc.adr = gainDataBuf;
			dsc.alen = 1;
			dsc.csnum = 0;
			dsc.wdata = 0;
			dsc.rdata = 0;
			dsc.wlen = 0;
			dsc.rlen = 0;

			spimux.AddRequest(&dsc);

			i++;

			break;

		case 4:

			if (dsc.ready)
			{
				i++;
			}
			else
			{
				spimux.Update();
			};

			break;

		case 5:
		{
			Rsp40 &rsp				= *((Rsp40*)mb->GetDataPtr());
			complex_float *fftbuf	= (complex_float*)fft->GetDataPtr();

			FFT(fftbuf, ArraySize(rsp.rsp.data), false);

			i++;

			break;
		};

		case 6:

			sp = AllocRsp30();

			if (sp.Valid())
			{
				Rsp30 &rsp30 = *((Rsp30*)sp->GetDataPtr());
				Rsp40 &rsp40 = *((Rsp40*)mb->GetDataPtr());

				complex_float *fftbuf = (complex_float*)fft->GetDataPtr();

				__packed u16 *dst = rsp30.rsp.data;

				fftbuf->re *= 0.5f; fftbuf->im *= 0.5f;

				float k = 1.0f / ArraySize(rsp30.rsp.data);

				for(u16 n = 0; n < ArraySize(rsp30.rsp.data); n++)
				{
					float re = fftbuf->re * k;
					float im = fftbuf->im * k;

					i32 t = sqrtf(re*re + im*im); fftbuf++;
					*(dst++) = LIM(t, 0, 65535);
				};

				rsp30.rsp.gain  	= rsp40.rsp.gain;		
				rsp30.rsp.spktrNum 	= ArraySize(rsp30.rsp.data);		
				rsp30.rsp.freqStep 	= 2.44140625;		
				rsp30.rsp.freqStart	= 0;		
				rsp30.rsp.maxAmp   	= rsp40.rsp.maxAmp;			
				rsp30.rsp.pow 		= rsp40.rsp.pow;		

				readyLF.Add(mb);	mb.Free();
				spectrLF.Add(sp);	sp.Free();

				fft.Free();

				i = 0;
			};

			break;
	};
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static Ptr<MB> mb_Update_HF;
static Ptr<MB> fft_Update_HF;
static Ptr<MB> sp_Update_HF;

static void Update_HF()
{
	static byte i = 0;

	Ptr<MB> &mb		= mb_Update_HF;
	Ptr<MB> &fft	= fft_Update_HF;
	Ptr<MB> &sp		= sp_Update_HF;

	switch (i)
	{
		case 0:

			if (cmdStartHF)
			{
				mb = AllocRsp40();

				if (mb.Valid())
				{
					register volatile byte t;

					cmdStartHF = false;

					Rsp40 &rsp = *((Rsp40*)mb->GetDataPtr());

					while(adcspi->SYNCBUSY);

					do t = adcspi->DATA; while(adcspi->INTFLAG & SPI_RXC); 

					hfDMA1.WritePeripheral((void*)(rsp.rsp.data), &adcspi->DATA, 4096, DMCH_TRIGACT_BURST|ADCTCC_DMCH_TRIGSRC1, DMDSC_BEATSIZE_BYTE|DMDSC_BLOCKACT_NOACT); 
					hfDMA2.WritePeripheral((void*)(rsp.rsp.data), &adcspi->DATA, 4096, DMCH_TRIGACT_BURST|ADCTCC_DMCH_TRIGSRC2, DMDSC_BEATSIZE_BYTE|DMDSC_BLOCKACT_NOACT); 
					hfDMAR.ReadPeripheral(&adcspi->DATA, (void*)(rsp.rsp.data), 8192, DMCH_TRIGACT_BURST|ADCSPI_DMCH_TRIGSRC, DMDSC_BEATSIZE_BYTE|DMDSC_BLOCKACT_NOACT); 

					adcTCC->WAVE = TCC_WAVEGEN_NPWM;
					adcTCC->PER = US2ADCTCC(5)-1;
					adcTCC->CC[0] = US2ADCTCC(1);
					adcTCC->CC[1] = US2ADCTCC(2);

					adcTCC->INTENCLR = ~0;
					//adcTCC->INTENSET = TCC_OVF;

					adcTCC->INTFLAG = ~0;

					adcTCC->EVCTRL = TCC_MCEO0|TCC_MCEO1;

					adcTCC->CTRLA = ADCTCC_PRESC_DIV;
					adcTCC->CTRLA = ADCTCC_PRESC_DIV|TCC_ENABLE;

					adcTCC->CTRLBSET = TCC_CMD_RETRIGGER; 

					i++;
				};
			};

			break;

		case 1:

			if (hfDMA1.CheckComplete() && hfDMA2.CheckComplete() && hfDMAR.CheckComplete())
			{
				adcTCC->CTRLA = 0; 
				adcTCC->CTRLA = TCC_SWRST; 

				hfDMA1.Disable();
				hfDMA2.Disable();
				hfDMAR.Disable();

				i++;
			};

			break;

		case 2:

			fft = AllocFFT();

			if (fft.Valid())
			{
				Rsp40 &rsp = *((Rsp40*)mb->GetDataPtr());

				complex_float *fftbuf = (complex_float*)fft->GetDataPtr();

				__packed u16 *src = rsp.rsp.data;
				__packed u16 *dst = rsp.rsp.data;

				src[0] = src[1];

				i32 max = 0;
				u32 sum = 0;

				for(u16 n = 0; n < ArraySize(rsp.rsp.data); n++)
				{
					i32 t = ReverseWord(*(src++)); t -= 32768; *(dst++) = t;
					//i32 t = (n&2) ? 32767 : -32767; *(p++) = t;

					fftbuf[n].re = t;
					fftbuf[n].im = 0;

					if (t < 0) t = -t;

					if (t > max) max = t;

					sum += t;
				};

				maxAmpHF = max;

				rsp.rsp.gain	= autoGain;
				rsp.rsp.sl		= ArraySize(rsp.rsp.data);
				rsp.rsp.st		= 500;
				rsp.rsp.maxAmp	= max;
				rsp.rsp.pow		= sum / rsp.rsp.sl;

				i++;
			};

			break;

		case 3:
		{
			Rsp40 &rsp				= *((Rsp40*)mb->GetDataPtr());
			complex_float *fftbuf	= (complex_float*)fft->GetDataPtr();

			FFT(fftbuf, ArraySize(rsp.rsp.data), false);

			i++;

			break;
		};

		case 4:

			sp = AllocRsp30();

			if (sp.Valid())
			{
				Rsp30 &rsp30 = *((Rsp30*)sp->GetDataPtr());
				Rsp40 &rsp40 = *((Rsp40*)mb->GetDataPtr());

				complex_float *fftbuf = (complex_float*)fft->GetDataPtr();

				__packed u16 *dst = rsp30.rsp.data;

				fftbuf->re *= 0.5f; fftbuf->im *= 0.5f;

				float k = 1.0f / ArraySize(rsp30.rsp.data);

				for(u16 n = 0; n < ArraySize(rsp30.rsp.data); n++)
				{
					float re = fftbuf->re * k;
					float im = fftbuf->im * k;

					i32 t = sqrtf(re*re + im*im); fftbuf++;
					*(dst++) = LIM(t, 0, 65535);
				};

				rsp30.rsp.gain  	= rsp40.rsp.gain;		
				rsp30.rsp.spktrNum 	= ArraySize(rsp30.rsp.data);		
				rsp30.rsp.freqStep 	= 48.828125;		
				rsp30.rsp.freqStart	= 0;		
				rsp30.rsp.maxAmp   	= rsp40.rsp.maxAmp;			
				rsp30.rsp.pow 		= rsp40.rsp.pow;		

				readyHF.Add(mb);	mb.Free();
				spectrHF.Add(sp);	sp.Free();

				fft.Free();

				i = 0;
			};

			break;

	};
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static void UpdateADC()
{
	static byte i = 0;

	switch (i)
	{
		case 0:

			HW::ADC1->INPUTCTRL = ADC_MUXPOS_PTAT;
			HW::ADC1->INTFLAG = ~0;
			HW::ADC1->SWTRIG = ADC_START;

			i++;

			break;

		case 1:

			if (HW::ADC1->INTFLAG & ADC_RESRDY)
			{
				PTAT = HW::ADC1->RESULT;

				HW::ADC1->INPUTCTRL = ADC_MUXPOS_CTAT;
				HW::ADC1->INTFLAG = ~0;
				HW::ADC1->SWTRIG = ADC_START;

				i++;
			};

			break;

		case 2:

			if (HW::ADC1->INTFLAG & ADC_RESRDY)
			{
				CTAT = HW::ADC1->RESULT;

				HW::ADC1->INTFLAG = ~0;

				u16 TP	= PTAT;
				u16 TC	= CTAT;

				i32 a = SMUL64(temp_k1,TC)>>8;
				i32 b = SMUL64(temp_k2,TP)>>8;
				i32 c = (temp_k3*TP - temp_k4*TC)/256;

				if (c != 0) tempCPU = ((a-b)+c/2)/c;

				HW::ADC1->INPUTCTRL = ADC_MUXPOS_SCALEDCOREVCC;
				HW::ADC1->INTFLAG = ~0;
				HW::ADC1->SWTRIG = ADC_START;

				i++;
			};

			break;

		case 3:

			if (HW::ADC1->INTFLAG & ADC_RESRDY)
			{
				u16 res = HW::ADC1->RESULT;

				coreVCC = (4125*res+1024)>>11;

				i = 0;
			};

	};
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static Task  taskUpdateADC(	UpdateADC,	US2CTM(1000)	);
static Task  taskUpdateLF(	Update_LF,	US2CTM(10)		);

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static void Init_ADC()
{
#ifdef CPU_SAME53

	HW::GCLK->PCHCTRL[GCLK_ADC0] = GEN_16M|GCLK_CHEN; 
	HW::GCLK->PCHCTRL[GCLK_ADC1] = GEN_16M|GCLK_CHEN; 
	HW::MCLK->ClockEnable(PID_ADC0); 
	HW::MCLK->ClockEnable(PID_ADC1); 

	HW::SUPC->VREF = VREF_ONDEMAND|VREF_TSEN;

	HW::PIOA->SetWRCONFIG(PA09,		PORT_PMUX_B|PORT_WRPMUX|PORT_WRPINCFG|PORT_PMUXEN);

	HW::ADC0->CTRLB		= ADC_RESSEL_16BIT|ADC_FREERUN;
	HW::ADC0->REFCTRL	= ADC_REFSEL_VDDANA|ADC_REFCOMP;
	HW::ADC0->INPUTCTRL	= ADC_MUXPOS_AIN9;
	HW::ADC0->AVGCTRL	= ADC_SAMPLENUM_16;
	HW::ADC0->SAMPCTRL	= ADC_SAMPLEN(12);
	HW::ADC0->CTRLA		= ADC_PRESCALER_DIV4|ADC_ENABLE; 
	HW::ADC0->SWTRIG	= ADC_START;

	HW::ADC1->CTRLB		= ADC_RESSEL_16BIT;//|ADC_FREERUN;
	HW::ADC1->REFCTRL	= ADC_REFSEL_VDDANA|ADC_REFCOMP;
	HW::ADC1->INPUTCTRL	= ADC_MUXPOS_PTAT;
	HW::ADC1->AVGCTRL	= ADC_SAMPLENUM_1024;
	HW::ADC1->SAMPCTRL	= ADC_SAMPLEN(24);
	HW::ADC1->CTRLA		= ADC_PRESCALER_DIV4|ADC_ENABLE; 
	//HW::ADC1->SWTRIG	= ADC_START;

	u16 TLI	= HW::TEMPCAL->TLI;
	u16 TLD	= HW::TEMPCAL->TLD;
	u16 THI	= HW::TEMPCAL->THI;
	u16 THD	= HW::TEMPCAL->THD;
	u16 VPL	= HW::TEMPCAL->VPL;
	u16 VPH	= HW::TEMPCAL->VPH;
	u16 VCL	= HW::TEMPCAL->VCL;
	u16 VCH	= HW::TEMPCAL->VCH;

	u16 TL = TLI*10+TLD;
	u16 TH = THI*10+THD;

	temp_k1 = TL*VPH - VPL*TH;
	temp_k2 = TL*VCH - VCL*TH;
	temp_k3 = VCL-VCH;
	temp_k4 = VPL-VPH;

	globalTaskList.Add(&taskUpdateADC);
	globalTaskList.Add(&taskUpdateLF);

#endif
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static Task  taskUpdateHF(	Update_HF,	US2CTM(10)		);

static void Init_ADCHF()
{
#ifdef CPU_SAME53

	ADCTCC_ClockEnable();

	HW::PIOA->SetWRCONFIG(PA08,	PORT_PMUX_F | PORT_WRPINCFG | PORT_PMUXEN | PORT_WRPMUX);

	adcTCC->CTRLA = TCC_SWRST;

	while(adcTCC->SYNCBUSY);

	//adcTCC->WAVE = TCC_WAVEGEN_NPWM;
	//adcTCC->PER = US2ADCTCC(2.5)-1;
	//adcTCC->CC[0] = US2ADCTCC(0.8);
	//adcTCC->CC[1] = US2ADCTCC(1.6);

	//adcTCC->INTENCLR = ~0;
	////adcTCC->INTENSET = TCC_OVF;

	//adcTCC->INTFLAG = ~0;

	//adcTCC->EVCTRL = TCC_MCEO0|TCC_MCEO1;

	//adcTCC->CTRLA = ADCTCC_PRESC_DIV;
	//adcTCC->CTRLA = ADCTCC_PRESC_DIV|TCC_ENABLE;

	//adcTCC->CTRLBSET = TCC_CMD_STOP; 

	ADCSPI_ClockEnable();

	PIO_ADCSCLK->SetWRCONFIG(ADCSCLK, ADC_PMUX_SCLK|PORT_WRPINCFG|PORT_PMUXEN|PORT_WRPMUX);
	PIO_ADCMISO->SetWRCONFIG(ADCMISO, ADC_PMUX_MISO|PORT_WRPINCFG|PORT_PMUXEN|PORT_WRPMUX);
	//ADCFS->DIRSET = _MASK_CS_ALL; 

	PIO_ADCMOSI->SetWRCONFIG(ADCMOSI, PORT_WRPINCFG|PORT_WRPMUX);
	PIO_ADCMOSI->DIRSET	= ADCMOSI;
	PIO_ADCMOSI->SET(ADCMOSI);

	adcspi->CTRLA = SPI_SWRST;

	while(adcspi->SYNCBUSY);

	adcspi->CTRLA = SERCOM_MODE_SPI_MASTER;

	adcspi->CTRLA = SERCOM_MODE_SPI_MASTER|ADC_DIPO_BITS|ADC_DOPO_BITS;
	adcspi->CTRLB = SPI_RXEN;
	adcspi->CTRLC = SPI_ICSPACE(0);
	adcspi->BAUD = NS2CLK(50)/2-1;

	adcspi->DBGCTRL = 1;

	adcspi->CTRLA |= SPI_ENABLE;

	while(adcspi->SYNCBUSY);

	adcspi->STATUS = ~0;

#endif

	globalTaskList.Add(&taskUpdateHF);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static void Init_ADG739()
{
	spimux.Connect(MUX_BAUDRATE);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void InitHardware()
{
	SEGGER_RTT_WriteString(0, RTT_CTRL_TEXT_BRIGHT_YELLOW "Hardware Init ... ");

#ifdef CPU_SAME53	

	using namespace HW;

	//	HW::PIOA->BSET(13);

	HW::GCLK->GENCTRL[GEN_32K]		= GCLK_DIV(1)			| GCLK_SRC_OSCULP32K	| GCLK_GENEN;

	HW::GCLK->GENCTRL[GEN_1M]		= GCLK_DIV(CLKIN_MHz)	| CLKIN_XOSC_NUM		| GCLK_GENEN	| GCLK_OE;

	HW::GCLK->GENCTRL[GEN_16M]		= GCLK_DIV(1)			| CLKIN_XOSC_NUM		| GCLK_GENEN;

	//	HW::GCLK->GENCTRL[GEN_500K] 	= GCLK_DIV(50)	|GCLK_SRC_XOSC1		|GCLK_GENEN;

	//HW::PIOA->SetWRCONFIG(PA17, PORT_PMUX_M|PORT_WRPINCFG|PORT_PMUXEN|PORT_WRPMUX|PORT_PULLEN);

	//HW::GCLK->GENCTRL[GEN_EXT32K]	= GCLK_DIV(1)	|GCLK_SRC_GCLKIN	|GCLK_GENEN		;


	HW::MCLK->APBAMASK |= APBA_EIC;
	HW::GCLK->PCHCTRL[GCLK_EIC] = GCLK_GEN(GEN_MCK)|GCLK_CHEN;

	HW::MCLK->APBBMASK |= APBB_EVSYS;

	HW::GCLK->PCHCTRL[GCLK_SERCOM_SLOW]		= GCLK_GEN(GEN_32K)|GCLK_CHEN;	// 32 kHz

#endif

	SEGGER_RTT_WriteString(0, RTT_CTRL_TEXT_BRIGHT_GREEN "OK\n");

	Init_time();
	I2C_Init();

	Init_ADC();
	Init_ADCHF();

	Init_ADG739();

	Init_FFT();

	WDT_Init();

	HW::PIOA->BCLR(13);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//void UpdateHardware()
//{
//	static byte i = 0;
//
//#define CALL(p) case (__LINE__-S): p; break;
//
//	enum C { S = (__LINE__+3) };
//	switch(i++)
//	{
//		CALL( I2C_Update();		);
//		CALL( UpdateADC();		);
//		CALL( Update_LF();		);
//		CALL( Update_HF();		);
//	};
//
//	i = (i > (__LINE__-S-3)) ? 0 : i;
//}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
