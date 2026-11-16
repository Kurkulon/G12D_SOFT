#ifndef G12D_1_HW_CONF_H__13_11_2026__13_16
#define G12D_1_HW_CONF_H__13_11_2026__13_16

#pragma once

#include <types.h>
#include <core.h>

#define CLKIN_MHz		16
#define CLKIN_XOSC_NUM	1
#define MCK_MHz			200
#define MCK				(MCK_MHz*1000000)
#define NS2CLK(x)		(((x)*MCK_MHz+500)/1000)
#define US2CLK(x)		((x)*MCK_MHz)
#define MS2CLK(x)		((x)*MCK_MHz*1000)

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//#define COMPRESS_REQ20

//#define FRAM_SPI_MAINVARS_ADR 0

#define FRAM_I2C_MAINVARS_ADR	0
#define FRAM_I2C_GENTIME_ADR	0x200

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#define REAL_TIME_CLOCK_DISABLE
#define SYSTEM_TICK_TIMER_ENABLE

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifdef CPU_SAME53	

	// Test Pins
	// 1	- PA00  
	// 2	- PA01 
	// 3	- PC00
	// 4	- PC01
	// 7	- PC02
	// 9	- PA02	
	// 11	- PB04	
	// 13	- PD00
	// 16	- PD01
	// 17	- PB06
	// 19	- PB08	

	// 35	- PA10
	// 36	- PA11
	// 39	- PB10
	// 41	- PB12
	// 43	- PB14
	// 44	- PB15
	// 47	- PD08
	// 49	- PD10
	// 51	- PD12
	// 52	- PC10
	// 55	- PC11
	// 57	- PC13
	// 59	- PC15
	// 61	- PA13
	// 62	- PA14
	// 63	- PA15	- main loop	
	// 66	- PA16
	// 68	- PA18
	// 70	- PC16
	// 72	- PC18
	// 74	- PC20
	// 76	- PC22
	// 77	- PC23
	// 80	- PD20
	// 82	- PB16
	// 84	- PB18
	// 88	- PA20
	// 89	- PA21
	// 94	- PA24
	// 95	- PA25
	// 100	- PB24
	// 102	- PB26
	// 104	- PB28
	// 105	- PB29
	// 108	- PC24
	// 110	- PC26
	// 122	- PB31
	// 124	- PC31
	// 126	- PB01
	// 127	- PB02
	// 128	- PB03


	// ++++++++++++++	GEN	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	#define GEN_MCK				0
	#define GEN_32K				1
	#define GEN_16M				2
	#define GEN_1M				3
	#define GEN_DAC				4
	//#define GEN_500K			4
	//#define GEN_EXT32K		5

	#define GEN_DAC_DIV			((u32)((MCK_MHz+6)/12))

	#define GEN_MCK_CLK			MCK
	#define GEN_32K_CLK			32768
	#define GEN_25M_CLK			25000000
	#define GEN_1M_CLK			1000000
	#define GEN_EXT32K_CLK		32768
	#define GEN_DAC_CLK			(MCK/GEN_DAC_DIV)

	// ++++++++++++++	SERCOM	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	#define MUX_SERCOM_NUM		0
	//#define SERCOM_1			1
	//#define 					2
	#define I2C_SERCOM_NUM		3
	#define ADXL_SERCOM_NUM		4
	//#define SPI_SERCOM_NUM		5
	#define ADC_SERCOM_NUM		6
	#define UART0_SERCOM_NUM	7


	// ++++++++++++++	DMA	0...31	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	#define	HF1_DMACH_NUM		0
	#define	HF2_DMACH_NUM		1
	#define	HFR_DMACH_NUM		2
	#define	LF_DMACH_NUM		3
	#define	UART0_DMACH_NUM		4
	#define	I2C_DMACH_NUM		5
	#define	SPI_DMA_TX_CH		6
	#define	SPI_DMA_RX_CH		7
//	#define	ADXL_DMA_TX_CH		8
//	#define	ADXL_DMA_RX_CH		9
	//#define	ADC_DMA					30
	//#define	CRC_DMA					31

	// ++++++++++++++	EVENT 0...31	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	#define EVENT_DNNKB			0
	#define EVENT_DNNKM			1
	#define EVENT_GEN			2
	#define EVENT_WIN			3
	//#define EVENT_MANR_1		4
	//#define EVENT_MANR_2		5
	//#define EVENT_BTCC_RETRG	6
	//#define EVENT_MTCC_RETRG	7

	// ++++++++++++++	TC	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	//#define	WIN_TC				TC0
	//#define					TC1
	//#define					TC2
	//#define					TC3
	//#define 					TC4
	//#define 					TC5

	#define GEN_TC0_TC1			GEN_MCK
	#define GEN_TC2_TC3			GEN_MCK
	#define GEN_TC4_TC5			GEN_MCK

	#define CLK_TC0_TC1			GEN_MCK_CLK
	#define CLK_TC2_TC3			GEN_MCK_CLK
	#define CLK_TC4_TC5			GEN_MCK_CLK

	#define GEN_TC0				GEN_TC0_TC1
	#define GEN_TC1				GEN_TC0_TC1
	#define GEN_TC2				GEN_TC2_TC3
	#define GEN_TC3				GEN_TC2_TC3
	#define GEN_TC4				GEN_TC4_TC5
	#define GEN_TC5				GEN_TC4_TC5

	#define GCLK_TC0			GCLK_TC0_TC1
	#define GCLK_TC1			GCLK_TC0_TC1
	#define GCLK_TC2			GCLK_TC2_TC3
	#define GCLK_TC3			GCLK_TC2_TC3
	#define GCLK_TC4			GCLK_TC4_TC5
	#define GCLK_TC5			GCLK_TC4_TC5

	#define CLK_TC0				CLK_TC0_TC1
	#define CLK_TC1				CLK_TC0_TC1
	#define CLK_TC2				CLK_TC2_TC3
	#define CLK_TC3				CLK_TC2_TC3
	#define CLK_TC4				CLK_TC4_TC5
	#define CLK_TC5				CLK_TC4_TC5

	// ++++++++++++++	TCC	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


	#define	ADC_TCC			TCC0
	//#define GEN_TCC			TCC1
	//#define B_TCC				TCC2
	//#define M_TCC				TCC3
	//#define					TCC4

	#define GEN_TCC0_TCC1		GEN_MCK
	#define GEN_TCC2_TCC3		GEN_MCK
	#define GEN_TCC4			GEN_MCK

	#define CLK_TCC0_TCC1		GEN_MCK_CLK
	#define CLK_TCC2_TCC3		GEN_MCK_CLK
	#define CLK_TCC4			GEN_MCK_CLK

	#define GEN_TCC0			GEN_TCC0_TCC1
	#define GEN_TCC1			GEN_TCC0_TCC1
	#define GEN_TCC2			GEN_TCC2_TCC3
	#define GEN_TCC3			GEN_TCC2_TCC3


	#define GCLK_TCC0			GCLK_TCC0_TCC1
	#define GCLK_TCC1			GCLK_TCC0_TCC1
	#define GCLK_TCC2			GCLK_TCC2_TCC3
	#define GCLK_TCC3			GCLK_TCC2_TCC3


	#define CLK_TCC0			CLK_TCC0_TCC1
	#define CLK_TCC1			CLK_TCC0_TCC1
	#define CLK_TCC2			CLK_TCC2_TCC3
	#define CLK_TCC3			CLK_TCC2_TCC3

	// ++++++++++++++	I2C	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//	#define I2C					CONCAT2(HW::I2C,I2C_SERCOM_NUM)
	#define PIO_I2C				HW::PIOA 
	#define PIN_SDA				22 
	#define PIN_SCL				23 
	#define SDA					(1<<PIN_SDA) 
	#define SCL					(1<<PIN_SCL) 
	#define I2C_PMUX_SDA		PORT_PMUX_C 
	#define I2C_PMUX_SCL		PORT_PMUX_C 
	#define I2C_GEN_SRC			GEN_MCK
	#define I2C_GEN_CLK			GEN_MCK_CLK
	#define I2C_BAUDRATE		400000 

	// ++++++++++++++	USART	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	#define PIO_UTXD0			HW::PIOB 
	#define PIO_URXD0			HW::PIOB 
	#define PIO_RTS0			HW::PIOB 

	#define PMUX_UTXD0			PORT_PMUX_D
	#define PMUX_URXD0			PORT_PMUX_D 

	#define UART0_TXPO			USART_TXPO_0 
	#define UART0_RXPO			USART_RXPO_1 

	#define PIN_UTXD0			21 
	#define PIN_URXD0			20 
	#define PIN_RTS0			19 

	#define UTXD0				(1UL<<PIN_UTXD0) 
	#define URXD0				(1UL<<PIN_URXD0) 
	#define RTS0				(1UL<<PIN_RTS0) 

	#define UART0_GEN_SRC		GEN_MCK
	#define UART0_GEN_CLK		GEN_MCK_CLK

	// ++++++++++++++	ADC		++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	#define PIO_ADCSCLK			HW::PIOC
	#define PIO_ADCMOSI			HW::PIOC
	#define PIO_ADCMISO			HW::PIOC
	#define PIO_ADCFS			HW::PIOC

	#define PIN_ADCSCLK			5
	#define PIN_ADCMOSI			4 
	#define PIN_ADCMISO			7 
	#define PIN_ADCFS			6 

	#define ADCSCLK				(1<<PIN_ADCSCLK	) 
	#define ADCMOSI				(1<<PIN_ADCMOSI	) 
	#define ADCMISO				(1<<PIN_ADCMISO	) 
	#define ADCFS				(1<<PIN_ADCFS	) 

	#define ADC_PMUX_SCLK		PORT_PMUX_C 
	#define ADC_PMUX_MOSI		PORT_PMUX_C 
	#define ADC_PMUX_MISO		PORT_PMUX_C 
	#define ADC_DIPO_BITS		SPI_DIPO(3)
	#define ADC_DOPO_BITS		SPI_DOPO(0) 

	// ++++++++++++++	FBHV		++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	//#define PIO_FBHV			HW::PIOB
	//#define PIN_FBHV			16
	//#define FBHV				(1UL<<PIN_FBHV	) 

	// ++++++++++++++ AD5312 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	
	#define PIO_SCLK			HW::PIOB
	#define PIO_MOSI			HW::PIOB
	#define PIO_SYNC			HW::PIOA

	#define PIN_SCLK			17
	#define PIN_MOSI			16 
	#define PIN_SYNC			20 

	#define SCLK				(1<<PIN_SCLK) 
	#define MOSI				(1<<PIN_MOSI) 
	#define SYNC				(1<<PIN_SYNC) 

	#define SPI_PMUX_SCLK		PORT_PMUX_C 
	#define SPI_PMUX_MOSI		PORT_PMUX_C 
	#define SPI_DIPO_BITS		SPI_DIPO(2)
	#define SPI_DOPO_BITS		SPI_DOPO(0) 

	#define SPI_GEN_SRC			GEN_MCK
	#define SPI_GEN_CLK			GEN_MCK_CLK
	#define SPI_BAUDRATE		8000000

	//#define Pin_SPI_IRQ_Set()	HW::PIOB->BSET(15)		
	//#define Pin_SPI_IRQ_Clr()	HW::PIOB->BCLR(15)		

	// ++++++++++++++ ADXL355  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	
	#define PIO_ADXLSPCK		HW::PIOB
	#define PIO_ADXLMOSI		HW::PIOB
	#define PIO_ADXLMISO		HW::PIOB
	#define PIO_ADXL_CS			HW::PIOB

	#define PIN_ADXLSPCK		13
	#define PIN_ADXLMOSI		12 
	#define PIN_ADXLMISO		15 
	#define PIN_ADXL_CS			14

	#define ADXLSPCK			(1<<PIN_ADXLSPCK) 
	#define ADXLMOSI			(1<<PIN_ADXLMOSI) 
	#define ADXLMISO			(1<<PIN_ADXLMISO) 
	#define ADXL_CS				(1<<PIN_ADXL_CS	) 

	#define ADXL_PMUX_SPCK		PORT_PMUX_C 
	#define ADXL_PMUX_MOSI		PORT_PMUX_C
	#define ADXL_PMUX_MISO		PORT_PMUX_C

	#define ADXL_DIPO_BITS		SPI_DIPO(3)
	#define ADXL_DOPO_BITS		SPI_DOPO(0) 

	#define ADXL_GEN_SRC		GEN_MCK
	#define ADXL_GEN_CLK		GEN_MCK_CLK
	#define ADXL_BAUDRATE		8000000

	// ++++++++++++++	PIO INIT	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	#define PIOA_INIT_DIR		(PA01|PA02|PA03|PA04|PA05|PA06|PA07|PA10|PA11|PA15|PA17|PA18|PA19|RTS0|PA27)
	#define PIOA_INIT_SET		(0)
	#define PIOA_INIT_CLR		(PA01|PA02|PA03|PA04|PA05|PA06|PA07|PA10|PA11|PA15|PA17|PA18|PA19|RTS0|PA27)
	#define PIOA_TEST_MASK		(PA01|PA02|PA03|PA04|PA05|PA06|PA07|PA10|PA11|UTXD0|PA15|PA17|PA18|PA19|PA20|RTS0|PA22|PA23|PA27)

	#define PIOB_INIT_DIR		(PB00|PB01|PB02|PB03|PB05|PB07|PB08|PB09|PB10|PB11|PB12|PB13|PB14|PB15|PB16|PB17|PB18|PB30|PB31)
	#define PIOB_INIT_SET		(0)
	#define PIOB_INIT_CLR		(PB00|PB01|PB02|PB03|PB05|PB07|PB08|PB09|PB10|PB11|PB12|PB13|PB14|PB15|PB16|PB17|PB18|PB30|PB31)
	#define PIOB_TEST_MASK		(PB00|PB01|PB02|PB03|PB05|PB07|PB08|PB09|PB10|PB11|PB12|PB13|PB14|PB15|PB16|PB17|PB18|PB30|PB31)

	#define PIOC_INIT_DIR		(PC00|PC01|PC02|PC03|PC10|PC11|PC12|PC13|PC14|PC15|PC16|PC17|PC18|PC19|PC20|PC21|PC22|PC23|PC24|PC25|PC26|PC27|PC28|PC30|PC31)
	#define PIOC_INIT_SET		(0)
	#define PIOC_INIT_CLR		(PC00|PC01|PC02|PC03|PC10|PC11|PC12|PC13|PC14|PC15|PC16|PC17|PC18|PC19|PC20|PC21|PC22|PC23|PC24|PC25|PC26|PC27|PC28|PC30|PC31)
	#define PIOC_TEST_MASK		(PC00|PC01|PC02|PC03|PC10|PC11|PC12|PC13|PC14|PC15|PC16|PC17|PC18|PC19|PC20|PC21|PC22|PC23|PC24|PC25|PC26|PC27|PC28|PC30|PC31)

	#define PIOD_INIT_DIR		(PD00|PD01|PD08|PD09|PD10|PD11|PD12|PD20|PD21)
	#define PIOD_INIT_SET		(0)
	#define PIOD_INIT_CLR		(PD00|PD01|PD08|PD09|PD10|PD11|PD12|PD20|PD21)
	#define PIOD_TEST_MASK		(PD00|PD01|PD08|PD09|PD10|PD11|PD12|PD20|PD21)

	#define Pin_MainLoop_Set()	HW::PIOA->BSET(15)
	#define Pin_MainLoop_Clr()	HW::PIOA->BCLR(15)
	#define Pin_MainLoop_Tgl()	HW::PIOA->BTGL(15)	

#elif defined(WIN32) //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	#define BAUD2CLK(x)				(x)
	#define MT(v)					(v)
	#define Pin_MainLoop_Set()	
	#define Pin_MainLoop_Clr()	

#endif

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++




#endif // G12D_1_HW_CONF_H__13_11_2026__13_16
