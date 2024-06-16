/*AT-MO PRODUCTION
RFID scan card
tolong jika menggunakan code ini
mohon masukan sumber seperti di bawah ini

"AT-MO PRODUCTION 
di BUAT BY OGI SINATRA"
*/


#include <RFID.h>
#include <SPI.h>

#define SS_PIN 10 //pin RFID yang bisa di ubah
#define RST_PIN 9 //pin RFID yang bisa di ubah

const int merah = 5;  
const int hijau = 2; 

RFID rfid(SS_PIN,RST_PIN);

void setup(){

    Serial.begin(9600);
    SPI.begin();
    rfid.init();

    pinMode(merah, OUTPUT);
    pinMode(hijau, OUTPUT);   

    digitalWrite(merah, LOW);
    digitalWrite(hijau, LOW);
}

void loop(){
    
    if(rfid.isCard()){
    
        if(rfid.readCardSerial()){
            Serial.print(rfid.serNum[0]);
            Serial.print(" ");
            Serial.print(rfid.serNum[1]);
            Serial.print(" ");
            Serial.print(rfid.serNum[2]);
            Serial.print(" ");
            Serial.print(rfid.serNum[3]);
            Serial.print(" ");
            Serial.print(rfid.serNum[4]);
            Serial.println("");}
    }

 rfid.halt();
}
    
