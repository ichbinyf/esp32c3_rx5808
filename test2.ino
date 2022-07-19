
#include <stdint.h>
#include <SPI.h>

const uint16 vtxtable[48] = [5362,5399,5436,5473,5510,5547,5584,5621,5645,5658,5665,5685,5695,5705,5725,5732,5733,5740,5745,5752,5760,5765,5769,5771,5780,5785,5790,5800,5805,5806,5820,5825,5828,5840,5843,5845,5847,5860,5865,5866,5880,5880,5885,5905,5917,5925,5945,5999] ; 
#define SPI_ADDRESS_SYNTH_B 0x01
#define SPI_ADDRESS_POWER   0x0A
#define SPI_ADDRESS_STATE   0x0F
#define PIN_SPI_CLOCK 2
#define PIN_SPI_DATA 3
#define PIN_SPI_SLAVE_SE 6

void sendBit(uint8_t value) {
    digitalWrite(PIN_SPI_CLOCK, LOW);
    delayMicroseconds(1);

    digitalWrite(PIN_SPI_DATA, value);
    delayMicroseconds(1);
    digitalWrite(PIN_SPI_CLOCK, HIGH);
    delayMicroseconds(1);

    digitalWrite(PIN_SPI_CLOCK, LOW);
    delayMicroseconds(1);
}
void sendBits(uint32_t bits, uint8_t count) {
    for (uint8_t i = 0; i < count; i++) {
        sendBit(bits & 0x1);
        bits >>= 1;
    }
}
void sendSlaveSelect(uint8_t value) {
    digitalWrite(PIN_SPI_SLAVE_SE, value);
    delayMicroseconds(1);
}
void sendRegister(uint8_t address, uint32_t data) {
    sendSlaveSelect(LOW);
    sendBits(address, 4);
    sendBit(HIGH); // Enable write.
    sendBits(data, 20);
    sendSlaveSelect(HIGH);
    digitalWrite(PIN_SPI_CLOCK, LOW);
    digitalWrite(PIN_SPI_DATA, LOW);
}
uint16_t getSynthRegisterBFreq(uint16_t f) {
  return ((((f - 479) / 2) / 32) << 7) | (((f - 479) / 2) % 32);
}
void setSynthRegisterB(uint16_t value) {
   sendRegister(SPI_ADDRESS_SYNTH_B, value);
}
void setChannelByFreq(uint16_t freq){
  //setSynthRegisterB(getSynthRegisterBFreq(freq));  
  sendRegister(SPI_ADDRESS_SYNTH_B, getSynthRegisterBFreq(freq));  
}
  

void setup(){
  //spi
  pinMode(6,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  
  //led
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  
  //
  pinMode(10,OUTPUT);
  //SPI.begin(2,10,3,11);
  setChannelByFreq(5945);
  Serial.begin(115200);
}

#define ANALOGREADPIN 0
void loop(){
  Serial.println("searching vtx channel");
  
  for(int i = 0 ; i < 48 ; i ++ ){
	  setChannelByFreq(vtxtable[i]);
	  if(i%8 == 0)Serial.println("");
	  if(i%1 == 0){
		  digitalWrite(12 , HIGH);
		  digitalWrite(13 , HIGH);
	  }else {
		  digitalWrite(12 , LOW) ; 
		  digitalWrite(13 , LOW) ; 
	  } 
	  Serial.print( analogRead(ANALOGREADPIN) ) ; 
	  Serial.print(",") ; 
	  Serial.print( i) ; 
	  Serial.print("\t") ; 
      delay(100);
  }
}
