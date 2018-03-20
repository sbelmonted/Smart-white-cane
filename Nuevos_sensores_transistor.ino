int tiger=2;
int echo=3;
int led=9;
int Duration,Distance, Duration2, Distance2 ;
int tiger2=5;
int echo2=4;
int brunzidor=12;
int obstaculo=99;
int transistor=9;
int intensidad = 0;
int intensidad2 = 0;

void setup() {

pinMode (tiger, OUTPUT);
pinMode (tiger2, OUTPUT);
pinMode (echo,INPUT);
pinMode (echo2,INPUT);
Serial.begin(9600);
pinMode(led, OUTPUT);
digitalWrite(led, HIGH);
pinMode(brunzidor, OUTPUT);
pinMode(transistor, OUTPUT);
}

void loop() {
 

digitalWrite(tiger, HIGH);
delay(100);
digitalWrite(tiger, LOW);
Duration=pulseIn(echo,HIGH);
Distance=(Duration/2)/29.1;
Serial.print ("cm=");
Serial.print (Distance);
//delay(100);

digitalWrite(tiger2, HIGH);
delay(100);
digitalWrite(tiger2, LOW);
Duration2=pulseIn(echo2,HIGH);
Distance2=(Duration2/2)/29.1;
Serial.print ("      cm2=");
Serial.print (Distance2);
//delay(100);

if (Distance<=-100 && Distance2>=obstaculo){
 digitalWrite(led,LOW); 
}

if (Distance2<=-100 && Distance>=obstaculo){
 digitalWrite(led,LOW); 
}


if (Distance<obstaculo&&Distance>0){
intensidad = map(Distance, obstaculo, 1, 1, 255);
} 

else { 
  intensidad = 0;
}


if (Distance2<obstaculo&&Distance2>0){
intensidad2 = map(Distance2, obstaculo, 1, 1, 255);
}
else{
  intensidad2=0;
}


Serial.print("   intensidad=");
Serial.print(intensidad);
Serial.print("   intensidad2=");
Serial.println(intensidad2);

if (Distance<obstaculo&&Distance>0){
  
  analogWrite(transistor, intensidad);

 
}

if (Distance2<obstaculo&&Distance2>0){

  analogWrite(transistor, intensidad2);

}


if (Distance<obstaculo &&Distance>0 && Distance2<obstaculo&&Distance2>0){

  analogWrite(transistor, intensidad);


}
if (Distance>obstaculo && Distance2>obstaculo){
 digitalWrite(transistor,LOW);
}

}
