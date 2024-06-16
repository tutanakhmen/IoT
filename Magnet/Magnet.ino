/* MECHATRON ROBOTIC SCHOOL
PROJECT : LED Blink
INPUT: Sensor Magnet 
OUTPUT  : Buzzer
MECHATRON ROBOTIC SCHOOL */

#define SENSOR  2
#define PIEZO   8

#define NOTE_G4  392
#define NOTE_C5  523
#define NOTE_G5  784
#define NOTE_C6  1047

int Sound[] = {NOTE_G5, NOTE_C6};
int SoundNoteDurations[] = {12, 8};

#define playSound() playMelody(Sound, SoundNoteDurations, 2)

char inChar;
String inString;

// variables will change:
int sensorState = 0;         // variable for reading the sensor status

void setup() {
  pinMode(PIEZO, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(SENSOR, INPUT_PULLUP);
}

void loop() {
  // read the state of the pushbutton value:
  sensorState = digitalRead(SENSOR);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (sensorState == HIGH) {
    playSound();
  } else {
   noTone(PIEZO);
  }
}

void playMelody(int *melody, int *noteDurations, int notesLength)
{
  pinMode(PIEZO, OUTPUT);

  for (int thisNote = 0; thisNote < notesLength; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(PIEZO, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(PIEZO);
  }
}
