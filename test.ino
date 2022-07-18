
#include <stdint.h>
#include <SPI.h>


#define SPI_ADDRESS_SYNTH_B 0x01
#define SPI_ADDRESS_POWER   0x0A
#define SPI_ADDRESS_STATE   0x0F
#define PIN_SPI_CLOCK 2
#define PIN_SPI_DATA 3
#define PIN_SPI_SLAVE_SE 6

void sendBits(uint32_t bits, uint8_t count) {
    for (uint8_t i = 0; i < count; i++) {
        sendBit(bits & 0x1);
        bits >>= 1;
    }
}
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
  pinMode(6,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  //SPI.begin(2,10,3,11);
  setChannelByFreq(5945);
  Serial.begin(115200);
}

#define ANALOGREADPIN 0
void loop(){
  Serial.println("abcd");
  setChannelByFreq(5945);
  digitalWrite(12,HIGH);
  digitalWrite(13,LOW);
  Serial.println( analogRead(ANALOGREADPIN) );delay(50);
  Serial.println( analogRead(ANALOGREADPIN) );delay(100);
  Serial.println( analogRead(ANALOGREADPIN) );delay(100);
  Serial.println( analogRead(ANALOGREADPIN) );delay(100);
  Serial.println( analogRead(ANALOGREADPIN) );delay(100);
  Serial.println( analogRead(ANALOGREADPIN) );delay(100);
  Serial.println( analogRead(ANALOGREADPIN) );delay(100);
  Serial.println( analogRead(ANALOGREADPIN) );delay(100);
  Serial.println( analogRead(ANALOGREADPIN) );delay(100);
  Serial.println( analogRead(ANALOGREADPIN) );delay(100);
  Serial.println( analogRead(ANALOGREADPIN) );delay(100);
  Serial.println( analogRead(ANALOGREADPIN) );delay(100);
  Serial.println( analogRead(ANALOGREADPIN) );delay(100);
  Serial.println( analogRead(ANALOGREADPIN) );delay(100);
  Serial.println( analogRead(ANALOGREADPIN) );delay(100);
  Serial.println( analogRead(ANALOGREADPIN) );delay(100);
  Serial.println( analogRead(ANALOGREADPIN) );delay(100);
  Serial.println( analogRead(ANALOGREADPIN) );delay(100);
  Serial.println( analogRead(ANALOGREADPIN) );delay(100);
  Serial.println( analogRead(ANALOGREADPIN) );delay(100);
  setChannelByFreq(5825);
  digitalWrite(12,LOW);
  digitalWrite(13,HIGH);
  Serial.println( analogRead(ANALOGREADPIN) );delay(50);
  Serial.println( analogRead(ANALOGREADPIN) );delay(100);
  Serial.println( analogRead(ANALOGREADPIN) );delay(100);
  Serial.println( analogRead(ANALOGREADPIN) );delay(100);
  Serial.println( analogRead(ANALOGREADPIN) );delay(100);
  Serial.println( analogRead(ANALOGREADPIN) );delay(100);
  Serial.println( analogRead(ANALOGREADPIN) );delay(100);
  Serial.println( analogRead(ANALOGREADPIN) );delay(100);
  Serial.println( analogRead(ANALOGREADPIN) );delay(100);
  Serial.println( analogRead(ANALOGREADPIN) );delay(100);
  Serial.println( analogRead(ANALOGREADPIN) );delay(100);
  Serial.println( analogRead(ANALOGREADPIN) );delay(100);
  Serial.println( analogRead(ANALOGREADPIN) );delay(100);
  Serial.println( analogRead(ANALOGREADPIN) );delay(100);
  Serial.println( analogRead(ANALOGREADPIN) );delay(100);
  Serial.println( analogRead(ANALOGREADPIN) );delay(100);
  Serial.println( analogRead(ANALOGREADPIN) );delay(100);
  Serial.println( analogRead(ANALOGREADPIN) );delay(100);
  Serial.println( analogRead(ANALOGREADPIN) );delay(100);
  Serial.println( analogRead(ANALOGREADPIN) );delay(100);
}
