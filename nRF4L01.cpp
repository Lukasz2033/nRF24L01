#include "Arduino.h"
#include "nRF4L01.h"
#include <SPI.h>

nRF4L01::nRF4L01(){
}

void nRF4L01::start(uint8_t mode){
	
	pinMode(CE, OUTPUT);  // Chip enable pin
	pinMode(IRQ, INPUT);  // Interrupt pin
 
	if(mode == Tx){
		config0 |= (MASK_RX_DR | PWR_UP);
		writeReg(CONFIG, &config0, 1);
		digitalWrite(CE, LOW);
	}
	else if(mode == Rx){
		config0 |= (MASK_TX_DS | MASK_MAX_RT | PWR_UP | PRIM_RX);
		writeReg(CONFIG, &config0, 1);
		digitalWrite(CE, HIGH);
	}
	
	en_rxaddr = 0;						//Update virtual register
	writeReg(EN_RXADDR, &en_rxaddr, 1);  	//Disable all pipes by default
	
	en_aa = 0;							//Update virtual register
	writeReg(EN_AA, &en_aa, 1);				//Disable auto ack for all pipes by default
}

void nRF4L01::enableCarrier(uint8_t channel){
	
	config0 |= PWR_UP;
	config0 &= ~PRIM_RX;
	
	writeReg(CONFIG, &config0, 1);
	delay(2);
	
	rf_setup |= (CONT_WAVE | PLL_LOCK );
	rf_setup &= ~0x06;  // Clear Amplification bits
	rf_setup |= Amp18dBm; // And set them to new value
	writeReg(RF_SETUP, &rf_setup, 1);
	
	changeFreq(channel);
	digitalWrite(CE, HIGH);
}
	
void nRF4L01::enableContWave(){
	
	rf_setup |= (CONT_WAVE || PLL_LOCK);
	writeReg(RF_SETUP, &rf_setup, 1);
}

void nRF4L01::disableContWave(){
	
	rf_setup &=  ~(CONT_WAVE || PLL_LOCK);
	writeReg(RF_SETUP, &rf_setup, 1);
}

void nRF4L01::changeFreq(uint8_t newFreq){
  	writeReg(RF_CH, &newFreq, 1);
}

uint8_t nRF4L01::detectCarrier(){
	return (readReg(RPD) & 0x01);
}

// Get Config methods
uint8_t nRF4L01::getConfig(){

	//Serial.print("Stat: ");
	//Serial.print(status0);
	//Serial.print("\n");
	return readReg(CONFIG);
}

// Get Status methods
uint8_t nRF4L01::getStatus(){
	status0 = readReg(STATUS);
	//Serial.print("Stat: ");
	//Serial.print(status0);
	//Serial.print("\n");
	return status0;
}
	
uint8_t nRF4L01::getFifoStatus(){
	return readReg(FIFO_STATUS);
}

uint8_t nRF4L01::getAutoACK(){
	return readReg(EN_AA);
}

uint8_t nRF4L01::getChEnabled(){
	return readReg(EN_RXADDR);
}

uint8_t nRF4L01::getLostPack(){
	return (readReg(OBSERVE_TX) >> 4);
}

uint8_t nRF4L01::getResentPack(){
	return (readReg(OBSERVE_TX) & 0x4);
}

void nRF4L01::configurePipe(uint8_t num, uint8_t ack, uint8_t size){
 
 //Enable a pipe
 en_rxaddr |=  (1 << num);  
 writeReg(EN_RXADDR, &en_rxaddr, 1);

 //Set size of a pipe (between 1 and 32)
 rx_pw_p[num] = size;
 writeReg(RX_PW_BASE+num, &rx_pw_p[num], 1);
 
 //Enable Auto Ack
 if(ack == AutoACK_EN){
	en_aa |= (1 << num);  //Enable Auto ACK
	writeReg(EN_AA, &en_aa, 1);
 }
}

uint8_t nRF4L01::checkRxIRQ(){
	
	if(getStatus() & RX_DR){ // Interrupt is active high
		//Serial.print("IRQ ON\n");
		digitalWrite(CE, LOW);  // Stop receiver
		return 1;
	}
	else{
		//Serial.print("IRQ clear\n");
		return 0;
	}
}

uint8_t nRF4L01::checkRxFull(){
	
	if(readReg(FIFO_STATUS) & FIFO_RX_FULL){ // Interrupt is active high
		return 1;
	}
	else{
		return 0;
	}
}

uint8_t nRF4L01::checkRxEmpty(){
	
	if(readReg(FIFO_STATUS) & FIFO_RX_EMPTY){ // Interrupt is active high
		return 1;
	}
	else{
		return 0;
	}
}

uint8_t nRF4L01::checkMaxRTIRQ(){
	
	if(getStatus() & MAX_RT){ 
		Serial.print("Max RT ON\n");
		
		return 1;
	}
	else{
		//Serial.print("IRQ clear\n");
		return 0;
	}
}

void nRF4L01::clearTxIRQ(){
		status0 |= TX_DS; // Clear data ready interrupt by writing 1 to it
		writeReg(STATUS, &status0, 1);
		status0 &= ~TX_DS;
}

void nRF4L01::clearRxIRQ(){
		status0 |= RX_DR; // Clear data ready interrupt by writing 1 to it
		writeReg(STATUS, &status0, 1);
		digitalWrite(CE, HIGH); // Enable receiver
		status0 &= ~RX_DR;
}

void nRF4L01::clearMaxRtIRQ(){
		status0 |= MAX_RT; // Clear data ready interrupt by writing 1 to it
		writeReg(STATUS, &status0, 1);
		status0 &= ~RX_DR;
}

//----------------------------------------------------//
// Check what pipe contains packet(s)
// returns 0 if there are no packets available
// returns number of pipe ( 1-6 ) containing packets
//----------------------------------------------------//
int8_t nRF4L01::checkRxNumber(){
	uint8_t ret = (readReg(STATUS) & 0xe) >> 1;
   //Serial.print(ret);
   //Serial.print("\n");
	if(ret == 0x7)  // Pipes are empty
		return -1;
	else
		return ret; // Number of pipe to be red
}

uint8_t nRF4L01::isFifoEmpty(){
		if((readReg(FIFO_STATUS) & FIFO_RX_EMPTY) == FIFO_RX_EMPTY){ // Fifo empty, set high when empty
			Serial.print("Fifo empty \n");
			return 0;
		}
		else{ // Fifo not empty
			Serial.print("Fifo not empty\n");
			return 1;
		}
}
void nRF4L01::setAddressSize(uint8_t size){
	writeReg(SETUP_AW, &size, 1);
	addrSize = size + 2; // 2 is an offset  to set 5 Bytes write 3 to hardware
}

// Transmit function
void nRF4L01::transmitByte(uint8_t pipeNumber, uint8_t value){
	
 // Update address register
 writeReg(TX_ADDR, tx_addr_p[pipeNumber], addrSize);
 digitalWrite(CSN, LOW); 	// Pull CSN Down
 SPI.transfer(W_TX_PAYLOAD);
 SPI.transfer(value);
 
 //Transmit buffered message
 digitalWrite(CE, HIGH);
 delayMicroseconds(100);
 digitalWrite(CE, LOW);
 
 digitalWrite(CSN, HIGH); // Pull CSN Up
}

void nRF4L01::transmit8Bytes(uint8_t pipeNumber, uint64_tt value){
	
 uint8_t c, r8, *ptr8;
 
 // Update address register
 writeReg(TX_ADDR, tx_addr_p[pipeNumber], addrSize);
 
 digitalWrite(CSN, LOW); 	// Pull CSN Down
 SPI.transfer(W_TX_PAYLOAD);
 
 ptr8 = (uint8_t*)&value; 
 
 for(c=0; c<8; c++){
	SPI.transfer(ptr8[7-c]);
	//Serial.print(ptr8[7-c], HEX);
    //Serial.print(":");
 }
 //Serial.print("\n");
 
 //Transmit buffered message
 digitalWrite(CE, HIGH);
 delayMicroseconds(10);
 digitalWrite(CE, LOW);
 
 digitalWrite(CSN, HIGH); // Pull CSN Up
}

// Receive functions
uint8_t nRF4L01::receiveByte(){

 uint8_t result;
 
 digitalWrite(CSN, LOW); // Pull CSN Down
 
 SPI.transfer(R_RX_PAYLOAD); 
 result = SPI.transfer(NOP);
 
 digitalWrite(CSN, HIGH); // Pull CSN Up
 
 return result;
}

uint64_tt nRF4L01::receive8Bytes(){

 uint8_t c, r8;
 uint64_tt result = 0;
 
 digitalWrite(CSN, LOW); // Pull CSN Down
 
 SPI.transfer(R_RX_PAYLOAD); 
 for(c=0; c<8; c++){
	r8 =  SPI.transfer(NOP);
	//Serial.print(r8, HEX);
    //Serial.print(":");
    result |= ((uint64_t)r8 << ((7-c) * 8));
 }
 //Serial.print("\n");
 
 digitalWrite(CSN, HIGH); // Pull CSN Up
 
 return result;
}

void nRF4L01::writeReg(uint8_t reg, uint8_t *values, int8_t length){
 
 int8_t c;
 uint8_t command = W_REGISTER | reg;

 digitalWrite(CSN, LOW); // Pull CSN Down
 SPI.transfer(command);
 for(c=length-1; c>=0; c--){ //
	//Serial.print(values[c], HEX);
	//Serial.print(":");
	SPI.transfer(values[c]);
 }
 //Serial.print("\n");
 digitalWrite(CSN, HIGH); // Pull CSN Up
}

uint8_t nRF4L01::readReg(uint8_t reg){

 uint8_t result;
 uint8_t command = R_REGISTER | reg;

 digitalWrite(CSN, LOW); // Pull CSN Down
 SPI.transfer(command); 
 result = SPI.transfer(NOP);
 digitalWrite(CSN, HIGH); // Pull CSN Up

 return result;
}

void nRF4L01::readAddr(){

 uint8_t result, c;
 uint8_t command = R_REGISTER | TX_ADDR;

 digitalWrite(CSN, LOW); // Pull CSN Down
 SPI.transfer(command); 
 for(c=0; c<5; c++){
	result = SPI.transfer(NOP);
	Serial.print(result, HEX);
	Serial.print(".");
 }
 Serial.print("\n");
 digitalWrite(CSN, HIGH); // Pull CSN Up

}

void nRF4L01::flushRx(){

	digitalWrite(CSN, LOW); // Pull CSN Down
	SPI.transfer(FLUSH_RX); 
	digitalWrite(CSN, HIGH); // Pull CSN Up
	
}

// print functions

void nRF4L01::printstatus(){
	
	uint8_t stat   =  readReg(STATUS);
	Serial.print("RX_DR:");
	Serial.print((stat&0x40)>>6);
	Serial.print(" ");
	Serial.print("TX_DS:");
	Serial.print((stat&0x20)>>5);
	Serial.print(" ");
	Serial.print("MAX_RT:");
	Serial.print((stat&0x10)>>4);
	Serial.print(" ");
	Serial.print("RX_P_NO:");
	Serial.print((stat&0x0E)>>1);
	Serial.print(" ");
	Serial.print("TX_FULL:");
	Serial.print((stat&0x01));
	Serial.print(" ");
	Serial.print("\n");
	
	uint8_t fstat  =  readReg(FIFO_STATUS);
	Serial.print("TX_REUSE:");
	Serial.print((fstat&0x40)>>6);
	Serial.print(" ");
	Serial.print("TX_FULL:");
	Serial.print((fstat&0x20)>>5);
	Serial.print(" ");
	Serial.print("TX_EMPTY:");
	Serial.print((fstat&0x10)>>4);
	Serial.print(" ");
	Serial.print("RX_FULL:");
	Serial.print((fstat&0x02)>>1);
	Serial.print(" ");
	Serial.print("RX_EMPTY:");
	Serial.print(fstat&0x01);
	Serial.print(" ");
	Serial.print("\n");
	
}
