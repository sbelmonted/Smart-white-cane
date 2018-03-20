#include <Wire.h> //I2C Arduino Library

#define addr 0x0D //I2C Address for The HMC5883
float declinacion = 0.119;//radians
int variacion;
float angulo;
int anguloant = 0;
int variacionant;
int mitjana;
int led = 9;
int transistor=9;
int comprobacion;

int tiger = 2;
int echo = 3;
int Duration, Distance, Duration2, Distance2 ;
int tiger2 = 5;
int echo2 = 4;

int obstaculo = 99;

int intensidad = 0;
int intensidad2 = 0;

void setup() {

  Serial.begin(9600);
  Wire.begin();


  Wire.beginTransmission(addr); //magnetometro
  Wire.write(0x09); 
  Wire.write(0x1D); 
  Wire.endTransmission();

  pinMode(10, OUTPUT); 

  pinMode (tiger, OUTPUT); //ultrasons
  pinMode (tiger2, OUTPUT);
  pinMode (echo, INPUT);
  pinMode (echo2, INPUT);

  pinMode(transistor, OUTPUT); //transistor
  pinMode(led,OUTPUT);
}



void loop() {



  int16_t x, y, z; //triple axis data

  //Tell the HMC what regist to begin writing data into
  Wire.beginTransmission(addr);
  Wire.write(0x00); //start with register 3.
  Wire.endTransmission();


  //Read the data.. 2 bytes for each axis.. 6 total bytes
  Wire.requestFrom(addr, 6);
  if (6 <= Wire.available()) {
    x = Wire.read() << 8; //MSB x
    x |= Wire.read(); //LSB x
    z = Wire.read() << 8; //MSB z
    z |= Wire.read(); //LSB z
    y = Wire.read() << 8; //MSB y
    y |= Wire.read(); //LSB y
  }
  //angulo = abs(atan2(y, x));
  angulo = atan2(y, x);
  angulo = abs(angulo - declinacion);
  angulo = angulo * (180 / PI); //convertimos de Radianes a grados


  // mitjana = (abs(anguloant) + abs(angulo)) / 2;
  mitjana = (anguloant + angulo) / 2;
  variacionant = max(abs(mitjana - anguloant), abs(mitjana - angulo));;

  /*comprobacion = (abs(mitjana) - abs(angulo));
    comprobacion=abs(comprobacion);
    if (comprobacion<10){

      digitalWrite(LED, HIGH);
    }

    else {

      digitalWrite(LED, LOW);
    }
  */
  delay (100);




  // Show Values
  /*
  Serial.print("X Value: ");
  Serial.println(x);
  Serial.print("Y Value: ");
  Serial.println(y);
  Serial.print("Z Value: ");
  Serial.println(z);
  Serial.println();
  Serial.print("Angulo: ");
  Serial.print(angulo);
  Serial.print("  angulo ant:  ");
  Serial.print (anguloant);
  Serial.print("  mitjana:   ");
  Serial.print(mitjana);
  Serial.print("  Variacio maxima:  ");
  Serial.println(variacionant);
*/
  if (variacionant < 10) {
    ultrasonidos();
  }
  else {
    digitalWrite(10, LOW);
  }


  anguloant = angulo;
  delay(100);

}
