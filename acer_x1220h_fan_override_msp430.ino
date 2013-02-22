/*
 This code acts as a frequency to voltage converter with a ~50% duty cycle.
 I wrote it to trick an Asus X1220H DLP Projector into thinking the fans were running according to the voltage it was applying to the fan.
 */ 
#define LED0 BIT0

uint16_t timerA = 125;
uint16_t timerB = 125;
uint16_t timerC = 125;

uint32_t startTime=0;

uint32_t lampOnTime = 15000;
uint32_t lampOffTime= 55000;

uint32_t sensor_A_time=0;
uint32_t sensor_B_time=0;
uint32_t sensor_C_time=0;

uint32_t blinker_wait_time=0xFFFFFFFF;
uint32_t last_blinker_time=0;

unsigned short avgA=0;
unsigned short avgB=0;
unsigned short avgC=0;

uint32_t sampleTime=0;

void setup() {
  //Serial.begin(9600);//msp430g2231 must use 4800
  pinMode(P1_0, OUTPUT);   //Red LED
  P1OUT &= 0b11111110;  //disables the Red LED

  pinMode(P1_1, OUTPUT);   //Lamp Ignition Sensor

  P1OUT &= 0b11111101;  //disables the ignition pin
  pinMode(P1_2, OUTPUT);   //Fan A Tach Sensor
  pinMode(P1_3, OUTPUT);   //Fan B Tach Sensor
  pinMode(P1_4, OUTPUT);   //Fan C Tach Sensor
  
  analogRead(A5);        //Fan A Voltage
  sensor_A_time = micros();

  analogRead(A6);        //Fan B Voltage
  sensor_B_time = micros();

  analogRead(A7);        //Fan C Voltage
  sensor_C_time = micros();
  
  while(analogRead(A5)<10) {
    startTime=millis();
  }
}

// 125 microseconds ==8000Hz
// 625 microseconds == 1600Hz
void loop() {
  sampleTime =  millis();
  if ((sampleTime-startTime)>lampOnTime){
    P1OUT |= 0b00000010;  //turn on the ignition pin
    P1OUT |= 0b00000001;  //turn on the Red LED
    blinker_wait_time=325000; //enables the blinker
    lampOnTime=0xFFFFFFFF;
      sampleTime =  millis();

  } 
  if ((sampleTime-startTime)>lampOffTime){
    P1OUT &= 0b11111101;  //disables the ignition pin
    P1OUT &= 0b11111110;  //disables the Red LED
    blinker_wait_time=0xFFFFFFFF; //disables the blinker
    lampOffTime=0xFFFFFFFF;
  }
  
  sampleTime=micros();
  if (uint16_t(sampleTime-sensor_A_time)>=timerA) {
    sensor_A_time=sampleTime;
    P1OUT ^= BIT2;
    timerA=uint16_t(map(analogRead(A5), 0, 340, 650, 150));
    sampleTime=micros();
  }

  if (uint16_t(sampleTime-sensor_B_time)>=timerB) {
    sensor_B_time=sampleTime;
    P1OUT ^= BIT3;
    timerB=uint16_t(map(analogRead(A6), 0, 340, 650, 150));
    sampleTime=micros();
  }
  
  if (uint16_t(sampleTime-sensor_C_time)>=timerC) {
    sensor_C_time=sampleTime;
    P1OUT ^= BIT4;
    //timerC=uint16_t(map(analogRead(A7), 0, 340, 10, 1));
    timerC=uint16_t(map(analogRead(A7), 0, 340, 650, 150));
    sampleTime=micros();
  }
  
  if ((sampleTime-last_blinker_time)>blinker_wait_time) {
    last_blinker_time = sampleTime;
    P1OUT ^= BIT0;
    //blinker_wait_time=uint16_t(map(analogRead(A5), 0, 340, 100050, 15150));
  }
}
