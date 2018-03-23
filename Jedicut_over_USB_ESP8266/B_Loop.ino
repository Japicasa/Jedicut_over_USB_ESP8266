/////////////////////////////////////////////////////
void loop() {

  // Each command consists of 2 bytes
  if (Serial.available() > 1)
  {
    Serial.readBytes((char*)&cmdArray[arrayIdxWrite], 2);


    // korrekt the write index
    arrayIdxWrite += 2;
    if (arrayIdxWrite == CMD_BUFFER_SIZE) arrayIdxWrite = 0;

    noInterrupts();
    cmdCounter++;
    interrupts();


    // check for oncoming overflow
    if (cmdCounter >= CMD_BUFFER_SIZE / 2 - 20)
    {
      ovf = true;
      Serial.print('S'); // Stop transmission, Buffer full
    }
    
  }
  //isrActive = false;
    if (timemark > 0) {
      isrActive = true;
      if (millis() > timemark) {
        isrActive = false;
        timemark = 0;
      }
    }
}
