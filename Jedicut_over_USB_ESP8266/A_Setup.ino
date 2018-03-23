/////////////////////////////////////////
void setup() {
// put your setup code here, to run once:

    //WiFi.mode(WIFI_OFF); // This is to make sure wifi is not working
    //WiFi.forceSleepBegin();
    

  Serial.begin(115200); //must match the baud rate of comport.ini file in the folder where jedicut.exe is placed
  // All axis on/off
  pinMode(D0,OUTPUT);      
   
  // Motor Pins  Direction
  pinMode(D5,OUTPUT);   
  pinMode(D6,OUTPUT);   
  pinMode(D7,OUTPUT);  
  pinMode(D8,OUTPUT);  
  // Motor Pins Clock
  pinMode(D1,OUTPUT);   
  pinMode(D2,OUTPUT); 
  pinMode(D3,OUTPUT);   
  pinMode(D4,OUTPUT);   
  // All motors OFF
  digitalWrite(D0,LOW);
  /////////Below the interrupt setup for ESP8266 Thanks, OTP see: http://onetechpulse.com/viewtopic.php?t=2
  timer1_isr_init();
  timer1_attachInterrupt(flip);
  timer1_enable(TIM_DIV16, TIM_EDGE, TIM_LOOP);  //5MHz (5 ticks/us - 1677721.4 us max)
  timer1_write((clockCyclesPerMicrosecond() / 16) * step_period); 

}
