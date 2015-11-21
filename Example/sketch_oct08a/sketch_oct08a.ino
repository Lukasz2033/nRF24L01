#include <nRF4L01.h>
#include <SPI.h>

nRF4L01 transmiter;

unsigned long start;

unsigned long f, s, time_out_start, time_out_stop;
uint16_t time_out;

uint64_tt val = 2000;
uint8_t carrier;

uint8_t rx_found = 0;

void setup(){
  
 //s = millis();
 //time_out_start = millis();
 
 carrier = 1;
 Serial.begin(4800);
 
 pinMode(MOSI, OUTPUT);
 pinMode(MISO, INPUT);
 pinMode(SCI, OUTPUT);
 pinMode(CSN, OUTPUT);
 pinMode(CE, OUTPUT);
 pinMode(IRQ, INPUT);
 SPI.begin(); 
 
 // Set up transmitter
 //transmiter.start(Tx);
 //transmiter.configurePipe(0, AutoACK_DIS, 1);
  uint8_t c;
  while(1){
  for(c=80; c<100; c++){
    transmiter.enableCarrier(c);
    Serial.print(c);
    Serial.print("\n");
    delay(3000);
  }
  }
}

void loop(){
  
   
 // f = millis();
   //if( f-s > 1000 ){
     //receiver.flushRx();
     //transmiter.printstatus();
     //Serial.print("\n");
     //s = millis();
   //}
   
   
   /*
  time_out_stop = millis();
  if((time_out_stop - time_out_start) > 1000){ // decrement every second
      time_out_start = millis();
      time_out--;
      
      Serial.print("Time out value:");
      Serial.print(time_out);
      Serial.print("\n");
   }
   */
   
   //while(!rx_found){
     // Advertise itself by enabling continues wave for 10 ms
     //transmiter.enableContWave();
   
   //}
   
   //if(time_out == 0){       // Send a ping
       // transmiter.transmitByte(0, 127);
       // Serial.print("Sending a ping\n");
  // }
   
   /*  
   transmiter.transmitByte(0, 11);
   if(transmiter.checkMaxRTIRQ()){
     transmiter.clearMaxRtIRQ();
   }
   */
   //transmiter.clearTxIRQ();
   //transmiter.transmit8Bytes(0, 0x1234567812345678);
  
   //delay(5000);
    //delayMicroseconds(1);
}




