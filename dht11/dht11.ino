#include <DHT11.h>

DHT11 bacatemperature(2);


void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  int temperature = bacatemperature.readTemperature();
  int humid = bacatemperature.readHumidity();

  Serial.print(humid);
  Serial.print("%     ");

  Serial.print(temperature);
  Serial.println("C");

  // put your main code here, to run repeatedly:

}
