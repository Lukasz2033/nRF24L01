#ifndef nRF4L01_h
#define nRF4L01_h

typedef unsigned char uint8_t;
typedef unsigned short uint16_tt;
typedef unsigned long long int uint64_tt;
typedef signed char int8_t;

//Mode
#define Tx 					0
#define Rx 					1

//Pipe configuration
#define AutoACK_EN   		0
#define AutoACK_DIS  		1

//Global configuration

//Pins
#define SCI   				13
#define CSN   				10
#define CE    				9  // Chip enabled
#define IRQ   				8  // Interupt

//Commands
#define R_REGISTER 			0x00  // 000A AAAA where A AAAA is register address
#define W_REGISTER 			0x20  // 001A AAAA where A AAAA is register address
#define R_RX_PAYLOAD 		0x61  // 
#define W_TX_PAYLOAD		0xA0  //
#define FLUSH_TX			0xE1  //
#define FLUSH_RX			0xE2  //
#define REUSE_TX_PL			0xE3  //
#define R_RX_PL_WID			0x60  //
#define W_TX_PAYLOAD_NOACK 	0xB0  //
#define NOP					0xFF  // No operation, used for reading registers

//Register hash defines
#define CONFIG 				0x00  // Configuration Register
 #define MASK_RX_DR  		0x40
 #define MASK_TX_DS  		0x20
 #define MASK_MAX_RT 		0x10
 #define EN_CRC	     		0x08
 #define CRC0	     		0x04
 #define PWR_UP	     		0x02
 #define PRIM_RX     		0x01
#define EN_AA 				0x01  // Enable Auto Acknowledgment
 #define ENAA_P5    		0x20
 #define ENAA_P4    		0x10
 #define ENAA_P3    		0x08
 #define ENAA_P2    		0x04
 #define ENAA_P1    		0x02
 #define ENAA_P0    		0x01
#define EN_RXADDR 			0x02  // Enabled RX Addresses
 #define ERX_P5	     		0x20
 #define ERX_P4      		0x10
 #define ERX_P3      		0x08
 #define ERX_P2      		0x04
 #define ERX_P1      		0x02
 #define ERX_P0      		0x01
#define SETUP_AW 			0x03  // Setup of Rx/Tx Address Width
 #define AddrWidth5B   		0x03
 #define AddrWidth4B   		0x02
 #define AddrWidth3B   		0x01
#define SETUP_RETR 			0x04  // Setup of Automatic Retransmission Time Out
 // Auto Retransmit Delay
 #define RetDel250uS   		0x00
 #define RetDel500uS   		0x01
 #define RetDel750uS   		0x02
 #define RetDel1000uS  		0x03
 #define RetDel1250uS  		0x04
 #define RetDel1500uS  		0x05
 #define RetDel1750uS  		0x06
 #define RetDel2000uS  		0x07
 #define RetDel2250uS  		0x08
 #define RetDel2500uS  		0x09
 #define RetDel2750uS  		0x0A
 #define RetDel3000uS  		0x0B
 #define RetDel3250uS  		0x0C
 #define RetDel3500uS  		0x0D
 #define RetDel3750uS  		0x0E
 #define RetDel4000uS  		0x0F
 // Auto Retransmit Count
 #define RETR_0	     		0x00
 #define RETR_1	     		0x01
 #define RETR_2      		0x02
 #define RETR_3	     		0x03
 #define RETR_4	     		0x04
 #define RETR_5      		0x05
 #define RETR_6      		0x06
 #define RETR_7      		0x07
 #define RETR_8      		0x08
 #define RETR_9      		0x09
 #define RETR_10     		0x0A
 #define RETR_11     		0x0B
 #define RETR_12     		0x0C
 #define RETR_13     		0x0D
 #define RETR_14     		0x0E
 #define RETR_15     		0x0F
#define RF_CH 				0x05
#define RF_SETUP			0x06
 #define Amp18dBm	 		0x00
 #define Amp12dBm	 		0x02
 #define Amp6dBm	 		0x04
 #define Amp0dBm	 		0x06
 #define Bw250kbps   		0x20
 #define Bw1Mbps	 		0x00
 #define Bw2Mbps	 		0x08
 #define PLL_LOCK    		0x10
 #define CONT_WAVE   		0x80
#define STATUS 				0x07 
 #define RX_DR 	     		0x40	// Data Ready interrupt, write 1 to clear.
 #define TX_DS	     		0x20	// Data Send interrupt, asserted when packet transmitted on TX.
 #define MAX_RT	     		0x10	// Maximum number of TX retransmit interrut
 #define NOT_USED    		0x0C
 #define EMPTY	     		0x0E
 #define TX_FULL     		0x01
#define OBSERVE_TX			0x08
 #define PLOS_CNT_MASK 		0xF0 	// Count lost packets, Reset by writing to RF_CH
 #define ARC_CNT_MASK  		0x0F     // Count retransmitted packets, Resets when transmission of a new packet starts. 
#define RPD					0x09
 #define REC_POW_DET_RD 	0x01   // See section 6.4 on page 24

//Rx pipe address registers
#define RX_ADDR_P0			0x0A
#define RX_ADDR_P1			0x0B
#define RX_ADDR_P2			0x0C
#define RX_ADDR_P3			0x0D
#define RX_ADDR_P4			0x0E
#define RX_ADDR_P5			0x0F

//Tx pipe address register
#define TX_ADDR				0x10

//Rx pipe size
#define RX_PW_BASE			0x11
#define RX_PW_P0			0x11
#define RX_PW_P1			0x12
#define RX_PW_P2			0x13
#define RX_PW_P3			0x14
#define RX_PW_P4			0x15
#define RX_PW_P5			0x16

#define FIFO_STATUS			0x17
 #define FIFO_TX_REUSE 		0x40
 #define FIFO_TX_FULL		0x20
 #define FIFO_TX_EMPTY		0x10
 #define FIFO_RX_FULL		0x02
 #define FIFO_RX_EMPTY		0x01

class nRF4L01{
	
 public:
 
	nRF4L01();
	
	void start(uint8_t mode);
	void configurePipe(uint8_t num, uint8_t ack, uint8_t size);
	
	void changeFreq(uint8_t newFreq);
  	
	uint8_t detectCarrier();
	
	uint8_t receiveByte();
	uint64_tt receive8Bytes();
	void transmitByte(uint8_t pipeNumber, uint8_t value);
	void transmit8Bytes(uint8_t pipeNumber, uint64_tt value);
	
	void flushRx();
	
	void setAddressSize(uint8_t size);
	
	// Read Status Methods
	void enableCarrier(uint8_t channel);
	void enableContWave();
	void disableContWave();
	uint8_t getConfig();
	uint8_t getStatus();
	uint8_t getFifoStatus();
	uint8_t getAutoACK();
	uint8_t getChEnabled();
	uint8_t getLostPack();
	uint8_t getResentPack();
	void readAddr();
	uint8_t checkRxIRQ();
	uint8_t checkRxFull();
	uint8_t checkRxEmpty();
	void clearRxIRQ();
	void clearTxIRQ();
	void clearMaxRtIRQ();
	uint8_t isFifoEmpty();
	int8_t checkRxNumber();
	uint8_t checkMaxRTIRQ();
	
	void printstatus();
    
 private:
 
	uint8_t addrSize	= 5; //Default
	
	//Default values
	//Used to keep track of current values hold in registers
	
	uint8_t config0   	= 0x08; 	// b00001000
	uint8_t en_aa  	  	= 0x3f; 	// b00111111
	uint8_t en_rxaddr 	= 0x03; 	// b00000011
	uint8_t setup_aw  	= 0x03; 	// b00000011
	uint8_t setup_retr 	= 0x03; 	// b00000011
	uint8_t rf_ch	  	= 0x02; 	// b00000010
	uint8_t rf_setup  	= 0x0e; 	// b00001110
	uint8_t status0    	= 0x0e; 	// b00001110
	uint8_t observe_tx 	= 0x00;
	uint8_t rpd 		= 0x00;
	uint8_t rx_pw_p[6] 	= { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

	//				  Tx destination address table 				    //
	//					  LSB is writen first						//  
	//						 	 | 				5 Byte addr. space  |
	//						 	   	   | 		4 Byte addr. space	|
	//										 |  3 Byte addr. space 	|
	uint8_t tx_addr_p[6][5] = { { 0xe7, 0xe7, 0xe7, 0xe7, 0xe7 },
								{ 0xc2, 0xc2, 0xc2, 0xc2, 0xc2 },
								{ 0xc2, 0xc2, 0xc2, 0xc2, 0xc3 },
								{ 0xc2, 0xc2, 0xc2, 0xc2, 0xc4 },
								{ 0xc2, 0xc2, 0xc2, 0xc2, 0xc5 },
								{ 0xc2, 0xc2, 0xc2, 0xc2, 0xc6 } };
								
	void writeReg(uint8_t reg, uint8_t *values, int8_t length);
    uint8_t readReg(uint8_t reg);
	
};

#endif
