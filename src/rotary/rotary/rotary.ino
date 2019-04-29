#include <Encoder.h>
#define channelA 5
#define debounce 200
#define channelB 6
#define rotary_button 8
#define name_length 5
#define ENCODER_DO_NOT_USE_INTERRUPTS

char my_name[name_length + 1] = {'!', '#', '@', '?', ':', '\0'};
char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
  'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
  'u', 'v', 'w', 'x', 'y', 'z'};
char current_letter;
int current_index = 0;
unsigned long prevTime;

Encoder rotary(channelA, channelB);
long position;

void setup()  {
  Serial.begin(9600);
  pinMode(rotary_button, INPUT_PULLUP);
} 

void loop()  {
  long newPos = abs(rotary.read() % 26);
  if (newPos != position && newPos >= 0) {
    position = newPos;
  }
  
  current_letter = letters[position];

  if (millis() - prevTime > debounce) {
    if (digitalRead(rotary_button) == LOW) {
      current_index++;
      my_name[current_index % name_length] = current_letter;
      Serial.println(my_name);
      prevTime = millis();  
    }
  }              
}
