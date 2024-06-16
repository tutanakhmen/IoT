const int pirpin = 2;
#define led 13

void setup (){
  Serial.begin(9600);
pinMode(pirpin, INPUT);
pinMode(led, OUTPUT);
}


void loop () {
int motionsensorValue = digitalRead(pirpin);

if (motionsensorValue == HIGH){
  digitalWrite(led, HIGH);
Serial.println("Gerakan terdeteksil");
}
else{
digitalWrite(led, LOW);
Serial.println("Tidak ada gerakan. ");
}
}