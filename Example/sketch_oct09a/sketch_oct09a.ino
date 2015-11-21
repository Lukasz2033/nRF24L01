#include <nRF4L01.h>
#include <SPI.h>

nRF4L01 receiver;

unsigned long start;
unsigned long count;

unsigned long f, s, time_out_start, time_out_stop;

int8_t ch;
uint8_t ret, data=9;
int8_t comm_channel;
uint16_t time_out;


// Config
uint8_t print_reg = 1;

void setup(){
 
 Serial.begin(4800);
 
 pinMode(MOSI, OUTPUT);
 pinMode(MISO, INPUT);
 pinMode(SCI, OUTPUT);
 pinMode(CSN, OUTPUT);
 pinMode(CE, OUTPUT);
 pinMode(IRQ, INPUT);
 SPI.begin(); 
 
  // Set up receiver
 receiver.start(Rx);
 
 receiver.configurePipe(0, AutoACK_DIS, 1);
 //receiver.configurePipe(1, AutoACK_EN, 8);
 //receiver.configurePipe(2, AutoACK_DIS, 1);
 //receiver.configurePipe(3, AutoACK_DIS, 1);
 //receiver.configurePipe(4, AutoACK_DIS, 1);
 //receiver.configurePipe(5, AutoACK_DIS, 1);
 
 //      comm_channel = -1;
 //time_out = 0;
 //receiver.changeFreq(1);
  //s = millis();
  ch = 90;
  receiver.changeFreq(ch);
}

void loop(){
  
   /*
   if(print_reg){
     f = millis();
     if( f-s > 1000 ){
       //receiver.flushRx();
       receiver.printstatus();
       //Serial.print("\n");
       s = millis();
     }
   }
   */
   
   // Detect transmission channel
    if(receiver.detectCarrier()){   // Check if there is transmission on this channel
             Serial.print("ch: "); 
             Serial.print(ch); 
             Serial.print(" ----> Transmission detected\n"); 
             //delay(10);
    }
   
    
    /*
    uint8_t c;
    
   // if(comm_channel == -1 && receiver.checkRxEmpty()){ // If no Tx was found and Rx  pipe is empty
      for(c=0; c<40; c++){
        c=30;
         Serial.print("Trying channel: ");
         Serial.print(c);
         Serial.print("\n");
             
         // Change frequency and cleare RX interrupt 
         //receiver.changeFreq(c);
         //receiver.clearRxIRQ();
       
         // Wait 
         delay(1000);
       
         if(receiver.detectCarrier()){   // Check if there is transmission on this channel
             Serial.print("Transmission detected\n");
             
             if(receiver.checkRxIRQ()){  // Check if packet was received
                Serial.print("Message has been received\n");
            
                if(receiver.receiveByte() == 127){ // Check if transmitter is talking to us
                   Serial.print("Transmitter detected\n");
                   
                   comm_channel = c;
                   time_out = 20;
                   time_out_start = millis();
                   Serial.print("comm_channel:");
                   Serial.print(comm_channel);
                   Serial.print("\n");
                   break;
                }
             }
          }
       } 
    //}
    */
  
  //while(/**comm_channel != -1 ||**/ !receiver.checkRxEmpty() ){ // If transmitter was found or there are pckets to be read
    /*
     time_out_stop = millis();
     if((time_out_stop - time_out_start) > 1000){ // decrement every second
        time_out_start = millis();
        
        if(time_out > 0){
          time_out--;
        }
        else{
          time_out = 0;
        }
        
        Serial.print("Time out value:");
        Serial.print(time_out);
        Serial.print("\n");
     }
           
     if(time_out == 0){       // We haven't received ping packet within time_out.
          comm_channel = -1;  // Go back to scaning for transmitter
          Serial.print("Time out\n");
     }
     */
     /*
     while( !receiver.checkRxEmpty() ){
           
           ch   = receiver.checkRxNumber();
           data = receiver.receiveByte();
           
           if(data == 127){ // Reset time_out counter
               time_out = 20;  // reset time_out
           }
           
           Serial.print("Ch:");
           Serial.print(ch);
           Serial.print(" --> data: ");
           Serial.print(data);
           Serial.print("\n");
           
        }
       */
     //}
  // }
}

