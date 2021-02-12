 void servo()
 {
  if(kaukosaato == false)
  {
   for(int PIR = 0; PIR < 5; PIR++)
   {
    currentPIRpin = PIRpin[PIR];    //for loopilla käydään läpi jokainen sensori
    currentLEDpin = LEDpin[PIR];    //ja jokainen led
    PIRstatus = digitalRead(currentPIRpin); //sensorin tila kirjoitetaan muutujaan
  
    if(PIRstatus == HIGH) //jos sensori onko sensori HIGH-tilassa
      {
        digitalWrite (currentLEDpin, HIGH); //liikkeen havainneen sensorin kanssa paritettu led syttyy
        if(PIRprevState[PIR] == 0)           //jos sensorin aiempi tila oli LOW
        {
          //jos servon suunta on eri kuin singnaalin saaneella sensorilla, servo kääntyy
          if(currentPIRposition != currentPIRpin && PIRprevState [PIR] == 0)                                                               
          {
            camServo.write (PIRposition[PIR]);        //käännetään servon kulma
            Serial.print("Taman hetkinen kulma on ");
            Serial.println(PIRposition[PIR]);
            delay(500);
            currentPIRposition = currentPIRpin;       
            PIRprevState[PIR] = 1; // HIGH
            servokulma = PIRposition[PIR];
          }
        PIRprevState[PIR] = 1;
      }
   } 
  
    else 
    {
      digitalWrite(currentLEDpin, LOW);
      PIRprevState[PIR] = 0;              // sensorin aiemmaksi tilaksi tulee LOW
    }
   }
  }
 }
