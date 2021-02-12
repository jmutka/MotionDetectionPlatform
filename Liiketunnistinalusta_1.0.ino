#include <Servo.h>
#include <IRremote.h>


Servo camServo;             // Servomoottorin nimeäminen
int currentPIRposition = 0; // Servon aloitus paikka 
int servokulma = 0;         // muuttuja servon kulmalle

// LEDIT
int LEDpin[] = {9,10,11,12,13}; // LEDien pinnien paikat
int currentLEDpin = 9;          // ensimmäinen pinni 

//PIR sensorit
int PIRpin[] = {2,3,4,5,6};             // PIR sensorien paikat
int currentPIRpin = 2;                  // PIR numero 2 on siis kytkettynä 9 pinnin LEDiin
int PIRprevState[] = {1,1,1,1,1};       // PIRien tila
int PIRposition[] = {157,110,80,50,10}; // PIR sensorien asennuskulmat. Servosta riippuen
boolean PIRstatus;                      // PIRien tila tosi tai epätosi

//Kaukosäädin
#define MODE 16753245     // kaukosäätimen mode-näppäimen desimaaliluku
#define VASEN 16769055    // kaukosäätimen vasen-näppäimen desimaaliluku
#define OIKEA 16748655    // kaukosäätimen oikea-näppäimen desimaaliluku
int RECV_PIN = 8;         // ir-vastaanotin 8 pinniin
IRrecv irrecv(RECV_PIN);  // Kaukosäädinobjekti
decode_results results;   // muuttuja kaukosäätimen näppäimelle
bool kaukosaato = false;  // boolean kaukosäädinohjaukselle
void setup()
{
  Serial.begin(9600);
  camServo.attach(7);   // Servomoottorin singnaali yhdistetään 7 pinniin.
  irrecv.enableIRIn();  // Käynnistetään ir-vastaanottimen
  
  for (int p = 0; p < 5; p++)
  {
    pinMode (PIRpin[1], INPUT); // PIR sensorit määrätään INPUTeiksi.
  }
  for (int l = 0; l < 5; l++)
  {
    pinMode (LEDpin[l], OUTPUT); // ledit OUTPUTeiksi
  }

  Serial.print ("Kalibroi PIR sensorit ");

  for(int k = 0; k < 5; k++) // kalibroi sensoreita 5 sekunin ajan 
  {
    Serial.print ("...");
    delay(1000); // lopettaa kalibroinnin ja odottaa sekunnin ennen tulostusta
  }
  Serial.println(" Sensorit kalibroitu");

  camServo.write (96);  // keskittää servon
  servokulma = 96;      //servon kulma muuttujaan
}

void loop()
{
  kaukosaadin();        // suoritetaan kaukosäädin -aliohjelma
  servo();              // suoritetaan servo -aliohjelma
}
 
