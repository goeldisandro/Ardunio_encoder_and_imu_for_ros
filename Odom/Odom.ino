/* 
 * UosseUial PlanaU OdometUy
 */

#include <ros.h>
#include <ros/time.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <SPI.h>


ros::NodeHandle nh;

geometry_msgs::TransformStamped t;        //message that is sent
tf::TransformBroadcaster broadcaster;     //broadcaster sends the messaages

// define the pins connected with the encoder Shield
int chipSelectPin1=10;
int chipSelectPin2=9;
int chipSelectPin3=8;


// x and y translation and angle of the robot
double x = 0.0;
double y = 0.0;
double theta = 0;

// names of the two refferencesystems
char base_link[] = "/base_link";  // middle of the roboters axe
char odom[] = "/odom";            // odom Map

// old eoncoder values
long oldEr  = 0;
long oldEl  = 0;

double U = 0.633;   // circumference of a wheel
double D = 0.561;    // distance between wheels

int first = 1;

void setup()
{
  nh.getHardware()->setBaud(76800);
  nh.initNode();
  broadcaster.init(nh);


  Serial.begin(9600);
  Serial.println("Basic Encoder Test:");

  // declare the pinmodes
  pinMode(chipSelectPin1, OUTPUT);
  pinMode(chipSelectPin2, OUTPUT);
  pinMode(chipSelectPin3, OUTPUT);

  // chipselect is aktiv low
  digitalWrite(chipSelectPin1, HIGH);
  digitalWrite(chipSelectPin2, HIGH);
  digitalWrite(chipSelectPin3, HIGH);   
  
  LS7366_Init();   // init the encoder shield
}

void loop()
{  
  // calculations
  if (first){                     // reads the Encoder values in case they're not =0 the first time
    oldEr = getEncoderValue(3);
    oldEl = getEncoderValue(2);
    first = 0;
    }

  // reads the new Encoder values
  long newEr = getEncoderValue(3);
  long newEl = getEncoderValue(2);

  // calculates the difference to the old values
  long dEr = newEr -oldEr;
  long dEl = newEl -oldEl;

  // if there's a difference it calculates the new position
  if (newEr != oldEr or newEl != oldEl) {     
    theta += U*(dEr-dEl)/(D*2000);      // angle of the robot, 2000 are the ticks per wheel rotation
    if(theta > 6.283) theta=0;
    if(theta < 0) theta=6.283;
    x += U/2000*(dEr+dEl)/2*cos(theta); //calculate x value
    y += U/2000*(dEr+dEl)/2*sin(theta); //calculate y value
    

    // Write Encoder values for the next time
    oldEr = newEr;
    oldEl = newEl;

  }
  Serial.println(newEl);
  // tf odom->base_link
  t.header.frame_id = odom;
  t.child_frame_id = base_link;
  
  t.transform.translation.x = x;
  t.transform.translation.y = y;
  
  t.transform.rotation = tf::createQuaternionFromYaw(theta);
  t.header.stamp = nh.now();
  
  broadcaster.sendTransform(t);
  nh.spinOnce();
    
  delay(100); // delay is necessery as othewise the USB connenction gets troubles with the SPI communication
  
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
