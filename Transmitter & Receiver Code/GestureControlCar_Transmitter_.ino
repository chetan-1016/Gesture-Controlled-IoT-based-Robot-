#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

//These are need for RF handlling
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//#define PRINT_DEBUG   //Uncomment this line if you want to print the MPU6050 initialization information on serial monitor

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

// MPU control/status vars
MPU6050 mpu;
bool dmpReady = false;  
uint8_t devStatus;  
uint16_t packetSize;    
uint8_t fifoBuffer[64]; 
Quaternion q;           
VectorFloat gravity;    
float ypr[3];           

// RF control
const uint64_t pipeOut = 0xF9E8F0F0E1LL;   
RF24 radio(8, 9); 

struct PacketData 
{
  byte xAxisValue;
  byte yAxisValue;
} data;

void setupRadioTransmitter()
{
  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(pipeOut);
  radio.stopListening();   

  data.xAxisValue = 127; // Center
  data.yAxisValue = 127; // Center 
}


void setupMPU()
{
  
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
      Wire.begin();
      Wire.setClock(400000); 
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
      Fastwire::setup(400, true);
  #endif

  #ifdef PRINT_DEBUG
    
    Serial.begin(115200);
    while (!Serial); 
    // initialize device
    Serial.println(F("Initializing I2C devices..."));
  #endif
  
  mpu.initialize();

  #ifdef PRINT_DEBUG  
    Serial.println(F("Testing device connections..."));
    Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));
    // wait for ready
    Serial.println(F("\nSend any character to begin DMP programming and demo: "));
    while (Serial.available() && Serial.read()); 
    while (!Serial.available());                 
    while (Serial.available() && Serial.read()); 
       Serial.println(F("Initializing DMP..."));
  #endif
  
  devStatus = mpu.dmpInitialize();
  
  // make sure it worked (returns 0 if so)
  if (devStatus == 0) 
  {
            mpu.CalibrateAccel(6);
      mpu.CalibrateGyro(6);
      
      #ifdef PRINT_DEBUG      
        mpu.PrintActiveOffsets();
        // turn on the DMP, now that it's ready
        Serial.println(F("Enabling DMP..."));
      #endif
      mpu.setDMPEnabled(true);
  
     
      #ifdef PRINT_DEBUG      
        Serial.println(F("DMP ready! Waiting for first interrupt..."));
      #endif
      dmpReady = true;
  
      // get expected DMP packet size for later comparison
      packetSize = mpu.dmpGetFIFOPacketSize();
  } 
  else 
  {
      // ERROR!
      // 1 = initial memory load failed
      // 2 = DMP configuration updates failed
      // (if it's going to break, usually the code will be 1)
      #ifdef PRINT_DEBUG       
        Serial.print(F("DMP Initialization failed (code "));
        Serial.print(devStatus);
        Serial.println(F(")"));
      #endif
  }
}


void setup()
{
  //This is to set up radio transmitter for rf
  setupRadioTransmitter();   
  //This is to set up MPU6050 sensor
  setupMPU();
}

void loop() 
{
  // if programming failed, don't try to do anything
  if (!dmpReady) return;
  // read a packet from FIFO. Get the Latest packet
  if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) 
  {  
    // display Euler angles in degrees
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

    int xAxisValue = constrain(ypr[2] * 180/M_PI, -90, 90);
    int yAxisValue = constrain(ypr[1] * 180/M_PI, -90, 90);
    data.xAxisValue = map(xAxisValue, -90, 90, 0, 254); 
    data.yAxisValue = map(yAxisValue, -90, 90, 254, 0);

    radio.write(&data, sizeof(PacketData));

    #ifdef PRINT_DEBUG  
      Serial.println(xAxisValue);  
      Serial.println(yAxisValue);        
    #endif
  }
}
