#include <Bounce.h>
//imgur link  https://imgur.com/gallery/q7Egf
//based on code posted at https://www.reddit.com/r/Teensy/comments/2rfkhw/i_made_a_teensypowered_arcade_stick/
// 10 = 10 ms debounce time

#define DEBOUNCE 10
 
typedef struct Button {
  Bounce button;
  int key;
  byte modifier;
  byte keynum;
} Button;

Button buttons[] = {
  // Top row, left-to-right:
  { Bounce(3, DEBOUNCE), KEY_A, 0, 2 },
  { Bounce(2, DEBOUNCE), KEY_S, 0, 3 },
  { Bounce(1, DEBOUNCE), KEY_5, 0, 4 },

  // Bottom row, left-to-right
  { Bounce(6, DEBOUNCE), MODIFIERKEY_SHIFT, 1, 0 },
  { Bounce(5, DEBOUNCE), MODIFIERKEY_CTRL, 1, 0 },
  { Bounce(4, DEBOUNCE), KEY_1, 0, 1 },
  
  // Joystick
  { Bounce(22, DEBOUNCE), KEY_RIGHT, 0, 5 },
  { Bounce(19, DEBOUNCE), KEY_LEFT, 0, 5 },
  { Bounce(20, DEBOUNCE), KEY_UP, 0, 6 },
  { Bounce(21, DEBOUNCE), KEY_DOWN, 0, 6 },
};

int current_modifiers = 0;

void setup() {
  int n;
  for(n=1; n <= 6; n++)
    pinMode(n, INPUT_PULLUP);

  for(n=19; n <= 22; n++)
    pinMode(n, INPUT_PULLUP);
}

void loop() {
  int n;

  for(n=0; n < 10; n++)
    buttons[n].button.update();

  for(n=0; n < 10; n++){
    if(buttons[n].button.fallingEdge()){
      // Falling edge, button is starting being pressed
      if(buttons[n].modifier) current_modifiers |= buttons[n].key;
      else {
        switch(buttons[n].keynum){
          case 1: Keyboard.set_key1(buttons[n].key); break;
          case 2: Keyboard.set_key2(buttons[n].key); break;
          case 3: Keyboard.set_key3(buttons[n].key); break;
          case 4: Keyboard.set_key4(buttons[n].key); break;
          case 5: Keyboard.set_key5(buttons[n].key); break;
          case 6: Keyboard.set_key6(buttons[n].key); break;
        }
      }
    } else if(buttons[n].button.risingEdge()){
      // Rising edge, button is coming up
      if(buttons[n].modifier) current_modifiers &= ~(buttons[n].key);
      else {
        switch(buttons[n].keynum){
          case 1: Keyboard.set_key1(0); break;
          case 2: Keyboard.set_key2(0); break;
          case 3: Keyboard.set_key3(0); break;
          case 4: Keyboard.set_key4(0); break;
          case 5: Keyboard.set_key5(0); break;
          case 6: Keyboard.set_key6(0); break;
        }
      }      
    }
  }

  Keyboard.send_now();
}
