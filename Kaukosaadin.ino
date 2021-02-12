void kaukosaadin()
{
  irrecv.resume(); // ir-sensori on valmis ottamaan uuden komennon
  delay(500);
  if (irrecv.decode(&results)) // jos kaukosäätimen nappia painetaan
  {
    long int kaukKoodi = results.value; // kirjoitetaan painetun napin desimaali long int muuttujaan
    if (kaukKoodi == MODE)              // onko painettu näppäin mode-näppäin 
      {
        kaukosaato = !kaukosaato;       // vaihdetaan kaukosaato booleania
        if(kaukosaato == false)
        {
          Serial.println("Liikenunnistinohjaus");
        } 
        else if(kaukosaato == true)
        {
          servokulma = 96;
          Serial.println("Kauko-ohjaus");
        }
      }
    if(kaukosaato == true)
    {
        if (kaukKoodi == OIKEA & servokulma < 136)    //desimaali luku oikealle napille ja
        {                                             //estetään, ettei servo käänny yli 160 asteeseen 
          for(int i = 0; i < 23; i++)                 //käännetään servoa 23 astetta oikeaan
          {
            servokulma +=1;
            camServo.write(servokulma);
            Serial.print("Taman hetkinen kulma on ");
            Serial.println(servokulma);
            delay(10);
          }
        } 
        else if(kaukKoodi == VASEN & servokulma > 24) //desimaali luku vasemmalle napille ja
        {                                             //estetään, ettei servo käänny alle 0 asteeseen
          for(int i = 23; i > 0; i--)                 //käännetään servoa 23 astetta oikeaan
          {
            servokulma -=1;
            camServo.write(servokulma);
            Serial.print("Taman hetkinen kulma on ");
            Serial.println(servokulma);
            delay(10); 
          }
        }
    }
  }
}
