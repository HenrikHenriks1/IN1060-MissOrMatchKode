#include <Wire.h>                                       //bibliotek for kommunikasjon mellom Arduinoene 

const int Spiller1 = 2;                                 //knapper for spillerne sine lys og svar
const int Spiller2 = 3;
const int Neste = 12;                                   //knapp for neste spørsmål
const int Spiller1Leds[4] = {4, 5, 6, 7};               //Lysene til spillerne
const int Spiller2Leds[4] = {8, 9, 10, 11};
int spiller1[4];                                        //Arrays til lysene for å sette dem til å av og på
int spiller2[4];
int Match = 0;                                          //En teller til å regne ut hvor mange % match man er til slutt
bool flag = true;                                       //boolean for neste spørsmål

void setup() {
  Serial.begin(9600);
  Wire.begin();
  pinMode(Spiller1, INPUT_PULLUP);                      //Setter alle knappene til input
  pinMode(Spiller2, INPUT_PULLUP);
  pinMode(Neste, INPUT_PULLUP);
  for (int i = 4 ; i < 12; i++) {                       //for loop for å sette alle LEDs til output
    pinMode(i, OUTPUT);
  }
}

void loop() {
  for (int i = 4 ; i < 12; i++) {
    digitalWrite(i, LOW);                               //Resetter leds og match% ved å skru alle av LEDs
    Serial.println("Resetter LED");
    Match = 0;
  }
  Serial.println(".....");
  for (int i = 0 ; i < 4; i++) {                        //Tømmer arrays for å starte fra start
    spiller1[i] = 0;
    spiller2[i] = 0;
    Serial.println("Resetter array");
  }
  for (int i = 0; i < 4; i++) {           
    Serial.print("Runde: ");                            //skriver ut runde i terminal 
    Serial.println(i);
    while (flag) {                                      //gjør at man kan stå på en runde uten tidsbegrensning med en boolean i stedet for delay();
      if (digitalRead(Spiller1) == HIGH) {              
        while (digitalRead(Spiller1) == HIGH) {}        //Når spiller 1 trykker knapp så setter den 1 i array som lyser når man trykker neste spørsmål 
        spiller1[i] = 1;
        Serial.println("Spiller1 ja");
      }
      if (digitalRead(Spiller2) == HIGH) {              //Når spiller 2 trykker knapp så setter den 1 i array som lyser når man trykker neste spørsmål 
        while (digitalRead(Spiller2) == HIGH) {}
        spiller2[i] = 1;
        Serial.println("Spiller2 ja");
      }
      if (digitalRead(Neste) == HIGH) {
        while (digitalRead(Neste) == HIGH) {}           //Går videre i loopen og til neste spørsmål
        flag = false;
        Serial.println("Neste");
      }
    }
    flag = true;                    
    if ((spiller1[i] == 1) && (spiller2[i] == 1) || (spiller1[i] == 0) && (spiller2[i] == 0)) {     //Sjekker om de har svart det samme på spørsmålet og øker telleren 
      Match++;
    }
    if (spiller1[i] == 1) {                             //Setter spillerne sine lys til av eller på avhengig om de trykket tidligere eller ikke
      digitalWrite(Spiller1Leds[i], HIGH);
    }
    else {
      digitalWrite(Spiller1Leds[i], LOW);
    }
    if (spiller2[i] == 1) {
      digitalWrite(Spiller2Leds[i], HIGH);
    }
    else {
      digitalWrite(Spiller2Leds[i], LOW);
    }
  }
  Wire.beginTransmission(9);                            //Starter kommunikasjon mellom Arduinoene i ghennom wire biblioteket 9
  Wire.write(Match);                                    //Sender info fra Arduino1 til Arduino2
  Wire.endTransmission();                               //Stopper sending
  delay(20000);
}
