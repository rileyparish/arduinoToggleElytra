// minecraft macro to equip and open the elytra while falling (the arduino MUST be an HID type; Nano, Leonardo, or Due)
// NOTICE: this script has a known issue. After running, it's necessary to move the cursor (and sometimes the player) before the script will run properly again. 
// The mouse position gets off otherwise; it appears to be a strange minecraft quirck.
// the positions and timings here are specific to my laptop, and will likely need to be adjusted to work on other devices

#include<Mouse.h>
#include<Keyboard.h>

// the button pin determines when to run the sequence
const int buttonPin = A0;
int keypressDelay = 25;   // wait a period of time (ms) for minecraft to respond before issuing the next keypress

// NOTE: you will need to adjust these values for different screen and GUI sizes!
int leftmostSquare = -70;   // this is assuming the elytra/chestplate is in the leftmost inventory slot
int chestVertPos = -40;


void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  Mouse.begin();
  Keyboard.begin();
//  Mouse.move(LEFT/RIGHT, UP/DOWN);

}

void loop() {
  // the button was pressed, run the sequence
  // analogRead gets ~650 while connected to the powered Staples "easy" button. When the button is pressed, the reading is 0
  if(analogRead(buttonPin) < 100){
    Serial.println("\n\nButton Pressed.");
    
    Keyboard.print('e');    // open the GUI, wait for it to load. This can take longer than the other operations
    delay(75);
    Mouse.move(leftmostSquare, 0);   // move the cursor down just a bit. For some reason this fixes the issue of removing the elytra and equipping the chestplate
    delay(keypressDelay);
    Mouse.click();      // pick up the elytra
    Mouse.move(0, chestVertPos);    // move the mouse (holding the elytra) to the chestplate position 
    delay(keypressDelay);
    Keyboard.press(KEY_LEFT_SHIFT);   // click shift to shift-click the chestplate into the inventroy
    delay(keypressDelay);
    Mouse.click();    // remove the chestplate and place in inventory
    delay(keypressDelay);
    Keyboard.release(KEY_LEFT_SHIFT);   // release shift
    delay(300);   // for some reason this delay needs to be longer or it doesn't work. There's a visible delay in-game (without a button) as well.
    Mouse.click();   // equip elytra
    delay(keypressDelay);    
    Keyboard.print('e');    // close inventory
    delay(keypressDelay);

    // this specific sequence and timing enables fly mode. I don't know why.
    Keyboard.press(' ');
    delay(50);  // I had to tune this value specifically. It seems that if it's too short, the press doesn't register reliably.
    Keyboard.release(' ');
    delay(keypressDelay);
    Keyboard.press(' ');
    delay(50);
    Keyboard.release(' ');

    delay(200);    // give the button time to be released so it doesn't toggle the state back and forth while the button is being pressed
  }
}
