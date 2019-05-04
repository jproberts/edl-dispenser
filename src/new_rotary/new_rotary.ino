#include <Encoder.h>
#define ENCODER_DO_NOT_USE_INTERRUPTS

char my_name[] = {' ', ' ', ' ', ' ', ' ', '\0'};
char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
  'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
  'u', 'v', 'w', 'x', 'y', 'z', '\0'};
char current_letter;
uint8_t name_index, rotary_selection;
unsigned long prevTime, newPos, position;
Encoder rotary(5, 6);

void setup()  {
  Serial.begin(9600);
  pinMode(8, INPUT_PULLUP);
} 

void loop()  {
  newPos = abs(rotary.read() % 26);
  if (newPos != position && newPos >= 0) {
    position = newPos;
    Serial.println(letters[position]);
  }

  if (millis() - prevTime > 200) {
    if (digitalRead(8) == LOW) {
      my_name[name_index % 5] = letters[position];
      name_index++;
      Serial.print("Current name: ");
      Serial.println(my_name);
      prevTime = millis();  
    }
  }              
}
