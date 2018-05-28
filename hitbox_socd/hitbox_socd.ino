#include <Bounce.h>
// imgur link  https://imgur.com/gallery/q7Egf
// based on code posted at https://www.reddit.com/r/Teensy/comments/2rfkhw/i_made_a_teensypowered_arcade_stick/
// 10 = 10 ms debounce time
// hitbox button configuration
// 4 directional buttons
// 4 punch buttons (LP, MP, HP, all 3 punch buttons together)
// 4 kick buttons (LK, MK, HK, all 3 kick buttons together)
// 4 control buttons(options, share, L3, R3)

#define DEBOUNCE 10
 
typedef struct Button {
  Bounce button;
  int key;
  byte keynum;    //USB HID's 6-key limit
} Button;

Button buttons[] = {
  // LP+MP+HP+LK+Up alternative costume button input
  // Top row, left-to-right:
  { Bounce(1, DEBOUNCE), KEY_G, 2 }, //LP
  { Bounce(2, DEBOUNCE), KEY_H, 3 }, //MP
  { Bounce(3, DEBOUNCE), KEY_J, 4 }, //HP
 
 // Bottom row, left-to-right
  { Bounce(4, DEBOUNCE), KEY_B, 1 }, //LK
  { Bounce(5, DEBOUNCE), KEY_N, 2 }, //MK
  { Bounce(6, DEBOUNCE), KEY_M, 3 }, //HK

  
  //L1(All punch), L2(All kick)
  { Bounce(7, DEBOUNCE), KEY_K, 1 }, //L1
  { Bounce(8, DEBOUNCE), KEY_COMMA, 1 }, //L2

  //options, select
  { Bounce(9, DEBOUNCE), KEY_PERIOD, 1 },
  { Bounce(10, DEBOUNCE), KEY_SLASH, 1 },
  
  //L3, R31
  { Bounce(11, DEBOUNCE), KEY_ENTER, 1 },
  { Bounce(12, DEBOUNCE), KEY_ESC, 1 },
  
  // Joystick
  { Bounce(22, DEBOUNCE), KEY_D, 5 },
  { Bounce(19, DEBOUNCE), KEY_A, 5 },
  { Bounce(20, DEBOUNCE), KEY_W, 6 },
  { Bounce(21, DEBOUNCE), KEY_S, 6 },
};

void setup() {
  int n;
  for(n=1; n <= 12; n++)
    pinMode(n, INPUT_PULLUP);

  for(n=19; n <= 22; n++)
    pinMode(n, INPUT_PULLUP);
}

void loop() {
  int n;

  for(n=0; n < 16; n++)
    buttons[n].button.update();

  for(n=0; n < 16; n++){
    if(buttons[n].button.fallingEdge()){
      // Falling edge, button is starting being pressed
        switch(buttons[n].keynum){
          case 1: Keyboard.set_key1(buttons[n].key); break;
          case 2: Keyboard.set_key2(buttons[n].key); break;
          case 3: Keyboard.set_key3(buttons[n].key); break;
          case 4: Keyboard.set_key4(buttons[n].key); break;
          case 5: Keyboard.set_key5(buttons[n].key); break;
          case 6: Keyboard.set_key6(buttons[n].key); break;
        }
    } else if(buttons[n].button.risingEdge()){
      // Rising edge, button is coming up
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

  Keyboard.send_now();
}
