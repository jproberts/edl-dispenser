#include <Encoder.h>
#define debounce 200
#define ENCODER_DO_NOT_USE_INTERRUPTS

char my_name[6] = {'!', '#', '@', '?', ':', '\0'};
char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
  'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
  'u', 'v', 'w', 'x', 'y', 'z'};
uint8_t current_index = 0;
unsigned long prevTime, position;
Encoder rotary(0, 1);

void setup()  {
  Serial.begin(9600);
  pinMode(7, INPUT_PULLUP);
} 

void loop()  {
  unsigned long newPos = abs(rotary.read() % 26);
  if (newPos != position && newPos >= 0) {
    position = newPos;
  }

  if (millis() - prevTime > debounce) {
    if (digitalRead(7) == LOW) {
      current_index++;
      my_name[current_index % 6] = letters[position];
      prevTime = millis();  
    }
  }              
}
