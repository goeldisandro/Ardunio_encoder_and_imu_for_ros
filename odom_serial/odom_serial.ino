/* 
 * UosseUial PlanaU OdometUy
 */
#define LED_PIN 13 // (Arduino is 13, Teensy is 11, Teensy++ is 6)
bool blinkState = false;

#include <SPI.h>


// packet structure for InvenSense teapot demo
uint8_t teapotPacket[14] = { '$', 0x03, 0,0, 0,0, 0,0, 0,0, 0x00, 0x00, '\r', '\n' };
uint8_t debugPacket[6] = { '$', 0x03, 0x00, '!', '\r', '\n' };


// define the pins connected with the encoder Shield
int chipSelectPin1=10;
int chipSelectPin2=9;
int chipSelectPin3=8;

long Er  = 0;
long El  = 0;

void setup()
{
  //Serial.begin(9600);
  //Serial.println("Basic Encoder Test:");

  // declare the pinmodes
  pinMode(chipSelectPin1, OUTPUT);
  pinMode(chipSelectPin2, OUTPUT);
  pinMode(chipSelectPin3, OUTPUT);

  // chipselect is aktiv low
  digitalWrite(chipSelectPin1, HIGH);
  digitalWrite(chipSelectPin2, HIGH);
  digitalWrite(chipSelectPin3, HIGH);
 
  LS7366_Init();   // init the encoder shield

  // initialize serial communication
  // (115200 chosen because it is required for Teapot Demo output, but it's
  // really up to you depending on your project)
  Serial.begin(57600);
  while (!Serial); // wait for Leonardo enumeration, others continue immediately


  // wait for ready
  Serial.println(F("\nSend any character to begin DMP programming and demo: "));
  while (Serial.available() && Serial.read()); // empty buffer
  while (!Serial.available());                 // wait for data
  while (Serial.available() && Serial.read()); // empty buffer again
  
  // configure LED for output
  pinMode(LED_PIN, OUTPUT);

  
  // wait for ready
  Serial.println(F("\nSend any character to begin DMP programming and demo: "));
  while (Serial.available() && Serial.read()); // empty buffer
  while (!Serial.available());                 // wait for data
  while (Serial.available() && Serial.read()); // empty buffer again
  debugPacket[2]=0x0A;
  Serial.write(debugPacket, 6);
  delay(100);
    
}
void loop()
{  
    Er = getEncoderValue(1);
    El = getEncoderValue(2);
            
        teapotPacket[2] = (uint8_t)(Er >> 24);
        teapotPacket[3] = ((Er >> 16) & 0xFF);
        teapotPacket[4] = ((Er >> 8) & 0xFF);
        teapotPacket[5] = (Er & 0xFF);
        teapotPacket[6] = (uint8_t)(El >> 24);
        teapotPacket[7] = (uint8_t)((El >> 16) & 0xFF);
        teapotPacket[8] = (uint8_t)((El >> 8) & 0xFF);
        teapotPacket[9] = (uint8_t)(El & 0xFF);
        Serial.write(teapotPacket, 14);
        //Serial.println(((long)teapotPacket[2]<<24) |((long)teapotPacket[3]<<16) | (teapotPacket[4]<<8) | (teapotPacket[5]) );
        teapotPacket[10]++; // packetCount, loops at 0xFF on purpose

        // blink LED to indicate activity
        blinkState = !blinkState;
        digitalWrite(LED_PIN, blinkState);
  delay(10);
}

// Methods for the communication with the encoder shield (SPI connection)
//*****************************************************  
long getEncoderValue(int encoder)
//*****************************************************
{
    unsigned int count1Value, count2Value, count3Value, count4Value;
    long result;
    
    selectEncoder(encoder);
    
    SPI.transfer(0x60); // Request count
    count1Value = SPI.transfer(0x00); // Read highest order byte
    count2Value = SPI.transfer(0x00);
    count3Value = SPI.transfer(0x00);
    count4Value = SPI.transfer(0x00); // Read lowest order byte
    
    deselectEncoder(encoder);
   
    result= ((long)count1Value<<24) + ((long)count2Value<<16) + ((long)count3Value<<8) + (long)count4Value;
    
    return result;
}//end func

//*************************************************
void selectEncoder(int encoder)
//*************************************************
{
  switch(encoder)
  {
     case 1:
        digitalWrite(chipSelectPin1,LOW);
        break;
     case 2:
       digitalWrite(chipSelectPin2,LOW);
       break;
     case 3:
       digitalWrite(chipSelectPin3,LOW);
       break;    
  }//end switch
  
}//end func

//*************************************************
void deselectEncoder(int encoder)
//*************************************************
{
  switch(encoder)
  {
     case 1:
        digitalWrite(chipSelectPin1,HIGH);
        break;
     case 2:
       digitalWrite(chipSelectPin2,HIGH);
       break;
     case 3:
       digitalWrite(chipSelectPin3,HIGH);
       break;    
  }//end switch
  
}//end func



// LS7366 Initialization and configuration
//*************************************************
void LS7366_Init(void)
//*************************************************
{
   
    
    // SPI initialization
    SPI.begin();
    //SPI.setClockDivider(SPI_CLOCK_DIV16);      // SPI at 1Mhz (on 16Mhz clock)
    delay(10);
   
   digitalWrite(chipSelectPin1,LOW);
   SPI.transfer(0x88); 
   SPI.transfer(0x03);
   digitalWrite(chipSelectPin1,HIGH); 
   
   
   digitalWrite(chipSelectPin2,LOW);
   SPI.transfer(0x88); 
   SPI.transfer(0x03);
   digitalWrite(chipSelectPin2,HIGH); 
   
   
   digitalWrite(chipSelectPin3,LOW);
   SPI.transfer(0x88); 
   SPI.transfer(0x03);
   digitalWrite(chipSelectPin3,HIGH); 
   
}//end func
