/////////////////////////////////
void  sendMotorCmd(byte cmd){

  // "pines[]" 0-3 step
  // "pines[]" 4-7 direction
  // we set direction first 

  for(int i=7;i>=0;i--)
    {
      digitalWrite(pines[i],!bitRead(cmd,i));//seems TB6560is falling edge triggering, we change the actual Jedicut command 
                                                          //Direction of motors should be "inversed"  as needed in Jedicut
    }
    delayMicroseconds(tickPeriod);
  
  // and then trip back the step pins after some time (tickperiod)
  for(int i=3;i>=0;i--)
    {
      digitalWrite(pines[i],1); //seems TB6560is falling edge triggering
    }
    
}

////////////////////////////
void handleCommand(){
  val = cmdArray[arrayIdxRead+1]; // The command parameter value
  //BufferRecep[0]=cmdArray[arrayIdxRead+0];
  //BufferRecep[1]=cmdArray[arrayIdxRead+1];
  switch(cmdArray[arrayIdxRead])
  {
    case 'A':   // All Motors on/off
    {
      if(val == '1')  {
        digitalWrite(D4,LOW);
        digitalWrite(D0,HIGH);
        }
      else  {
        digitalWrite(D4,HIGH);
        digitalWrite(D0, LOW);
        }
    break;
    }
    case 'H':   // Wire Heat ON/OFF (may be programmed as PWM (analog out)) 
    {
     //Heating is not managed in this version since Wemos D1 mini has only nine input/output pins, already all used
     // Future implementation is possible  wifi may be used to transmit somewhere thiese values
      /*if(val > 0)   {digitalWrite(2, LOW);}
      else          {digitalWrite(2, HIGH);}*/
    //  analogWrite(3,val*2.55); // PWM for wire heating (stretch 0-100% to a range of 0-255)
    break;
    }
    case 'M':   // Motor step Command
    {
      sendMotorCmd(val);
    break;
    }
    case 'F':   // Change the timer frequency, the time between two steps
    {
        Serial.print(char(cmdArray[arrayIdxRead]));
        Serial.print(cmdArray[arrayIdxRead + 1]);
        Serial.println("y");
        switch (val)
        {
          case 1:   // Fast Speed
            {
              step_period = stepmin_period;
              noInterrupts();
              timer1_write((clockCyclesPerMicrosecond() / 16) * step_period);
              interrupts();
              break;
            }
          case 255:   // Cut Speed
            {
              step_period = stepmax_period;
              noInterrupts();
              timer1_write((clockCyclesPerMicrosecond() / 16) * step_period);
              interrupts();
              break;
            }
          default: // Pause (value in Jedicut) = pause in tenths of second
            timemark=(100*(256-val))+millis();
           
             break;
        }
        //break;
      }
  }
}



//////////////////////////////////////////////////////
// the interrupt funtion
void flip() {
  if (isrActive) return;
  isrActive = true;  
  
  
      // check if the buffer is empty
      if((arrayIdxRead != arrayIdxWrite) || ovf)
      {
        
        handleCommand();
        
        arrayIdxRead += 2;
        if(arrayIdxRead==CMD_BUFFER_SIZE) arrayIdxRead=0;
    
        noInterrupts();
        cmdCounter--;
        interrupts();
    
        if (ovf && (cmdCounter<CMD_BUFFER_SIZE/2-26))
        {
          Serial.write('C'); //buffer not full: continue sending commands
          ovf = false;
        } 
        
      }
      else
      {
        // underflow! break;
      }
   
  isrActive = false;
}

