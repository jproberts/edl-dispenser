//todo: please clean this up im rusty on this and dont wanna think about it
#include "pin_definitions.h"
#include "FPS_GT511C3.h"
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
// #include "SoftwareSerial.h"
//TODO: i think we dont need this?
#include "medication.h"
#include "user.h"
//how do you include system.h or should we like redo it idk
// use your judgment i trust you

/* DISPLAY */
// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
// If using the breakout, change pins as desired
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

/* SHIFT REGISTER */
#define BUTTON_ONE shiftReg[4]
#define BUTTON_TWO shiftReg[5]

int shiftReg[8];
/* shiftReg
  0: Hall1
  1: Hall2
  2: Hall3
  3: UNUSED
  4: Switch1
  5: Switch2
*/

/* FINGERPRINT SENSOR */

//TODO: plz put the right pins here, james
// I think this should work. I might have them flipped. 26 is FPS_TX, 25 is FPS_RX
// Switched to dummy values to make sure there's no overlap with display tests.
FPS_GT511C3 fps(4, 5);

enum States
{
  Welcome,
  Authenticate,
  Main_Menu,
  User_Menu_1,
  User_Menu_2,
  Add_User,
  Remove_User,
  Elevate_User,
  Meds_Menu_1,
  Meds_Menu_2,
  Supply_Mode,
  Get_Meds,
  Add_Scrips
};

enum States system_state = Welcome;

void setup()
{
  Serial.begin(9600);
  //fps.Open(); // send serial command to initialize fps
  tft.begin(); // Initialize display.
  // Set SHIFTREG and ROT_SWITCH as inputs.
  tft.println("Setting pins");
  //  DDRD &= !(1 << SHIFTREG_Q_pin);
  //  DDRD &= !(1 << ROT_SWITCH_pin);
  tft.println("Testing screen");
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  //testWelcomeScreen();
}

void loop()
{
  //TODO: hi pls get this to work, yay!
  //readShiftRegister(shiftReg);
  switch (system_state)
  {
  case Welcome:
  {
    tft.println("Welcome! Press 1 to authenticate");
    while (1)
    {
      if (BUTTON_ONE == 0)
      {
        system_state = Authenticate;
        break;
      }
    }
    break;
  }
  case Main_Menu:
  {
    tft.println("1) Meds menu\n2) User menu\n3) Log out");
    while (1)
    {
      if (BUTTON_ONE == 0)
      {
        system_state = Meds_Menu_1;
        break;
      }
      if (BUTTON_TWO == 0)
      {
        system_state = User_Menu_1;
        break;
      }
      if (ROT_SWITCH_PIN & (1 << ROT_SWITCH_pin) == 0)
      {
        system_state = Welcome;
        break;
      }
    }
    break;
  }
  case Add_User:
  {
    tft.println("Add user! Follow the instructions");
    while (1)
    {
      // TODO: micro-code to capture all of the inputs, buttons 2 and 3
      // don't forget to like... get their fingerprint

      if (BUTTON_ONE == 0)
      {
        //TODO: look at the diagram, I think I meant to have b1 going to main menu, not authenticate
        system_state = Main_Menu;
        break;
      }
    }
    break;
  }
  case User_Menu_1:
  {
    tft.println("1) Add\n2) Remove\n3) More options");
    while (1)
    {
      if (BUTTON_ONE == 0)
      {
        system_state = Add_User;
        break;
      }
      if (BUTTON_TWO == 0)
      {
        system_state = Remove_User;
        break;
      }
      if (ROT_SWITCH_PIN & (1 << ROT_SWITCH_pin) == 0)
      {
        system_state = User_Menu_2;
        break;
      }
    }
    break;
  }
  case User_Menu_2:
  {
    tft.println("1) Elevate \n2) Back to main menu");
    while (1)
    {
      if (BUTTON_ONE == 0)
      {
        system_state = Elevate_User;
        break;
      }
      if (BUTTON_TWO == 0)
      {
        system_state = Main_Menu;
        break;
      }
    }
    break;
  }

  //TODO: when do you want to fps.SetLED(false), in the welcome menu or at the end of this?
  // I put it after the finger press is recognized.
  case Authenticate:
  {
    tft.println("Please authenticate yourself by placing your finger down on the scanner.");
    fps.SetLED(true); // turn on LED so fps can see fingerprint
    while (1)
    {
      // Identify fingerprint
      if (fps.IsPressFinger())
      {
        fps.SetLED(false);
        fps.CaptureFinger(false);
        int id = fps.Identify1_N();

        if (id < 200)
        {
          //TODO: get this to work
          /*if (getUserFromId(id)) // Checks that user is registered
          {
            Serial.print("Access granted. Verified ID:");
            tft.println(id);
            system_state = Main_Menu;
          }
          else
          {
            tft.println("Access denied. You're being sent to jail, don't collect $200");
            buzz();
              system_state = Welcome;
          }
          */
        }
        else
        {
          tft.println("Finger not found. You're being sent to jail, don't collect $200");
          buzz();
          system_state = Welcome;
          break;
        }
      }
      else
      {
        tft.println("Please press finger");
      }
      delay(100);
    }
    break;
  }
  case Remove_User:
  {
    tft.println("Scroll through this list of users and press down on the rotary encoder.");
    while (1)
    {
      // TODO: add rotary code to actually scroll through the users

      //then once you pressed it, beep and leave
      if (ROT_SWITCH_PIN & (1 << ROT_SWITCH_pin) == 0)
      {
        buzz();
        system_state = Main_Menu;
        break;
      }
    }
    break;
  }
  case Elevate_User:
  {
    tft.println("Scroll through this list of users and press down on the rotary encoder.");
    while (1)
    {
      // TODO: add rotary code to actually scroll through the users

      //then once you pressed it, beep and leave
      if (ROT_SWITCH_PIN & (1 << ROT_SWITCH_pin) == 0)
      {
        buzz();
        system_state = Main_Menu;
        break;
      }
    }
    break;
  }
  case Meds_Menu_1:
  {
    tft.println("1) Get meds\n2) Add scrip\n3) More options");
    while (1)
    {
      if (BUTTON_ONE == 0)
      {
        system_state = Get_Meds;
        break;
      }
      if (BUTTON_TWO == 0)
      {
        system_state = Add_Scrips;
        break;
      }
      if (ROT_SWITCH_PIN & (1 << ROT_SWITCH_pin) == 0)
      {
        system_state = Meds_Menu_2;
        break;
      }
    }
    break;
  }
  case Meds_Menu_2:
  {
    tft.println("1) Supply mode\n2) Main menu");
    while (1)
    {
      if (BUTTON_ONE == 0)
      {
        system_state = Supply_Mode;
        break;
      }
      if (BUTTON_TWO == 0)
      {
        system_state = Main_Menu;
        break;
      }
    }
    break;
  }
  case Supply_Mode:
  {
    tft.println("Supply mode time");

    //TODO: add micro code to select container, open lid (waiting for b1)
    //select scrip, then add it, then go back
    while (1)
    {
      if (BUTTON_TWO == 0)
      {
        system_state = Main_Menu;
        break;
      }
      break;
    }
  }
  case Get_Meds:
  {
    tft.println("Get meds!");

    // TODO: if meds available, dispense and show remaining count
    // else display time for next dispensing
    while (1)
    {
      // go back to main menu after all that stuff happens
      if (BUTTON_ONE == 0)
      {
        system_state = Main_Menu;
        break;
      }
    }
    break;
  }
  case Add_Scrips:
  {
    tft.println("Add scrips! Follow the instructions");
    while (1)
    {
      // TODO: micro-code to capture all of the inputs, buttons 2 and 3

      if (BUTTON_ONE == 0)
      {
        system_state = Main_Menu;
        break;
      }
    }
    break;
  }
  }
}

void buzz()
{
  tft.println("BEEP");
}

unsigned long testWelcomeScreen()
{
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(0, 0);
  //  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(1);
  //  tft.println("Hello World!");
  //  tft.setTextColor(ILI9341_YELLOW); tft.setTextSize(2);
  //  tft.println(1234.56);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(3);
  tft.println("WELCOME TO");
  tft.print("PHARM");
  tft.setTextColor(ILI9341_RED);
  tft.print("-");
  tft.setTextColor(ILI9341_WHITE);
  tft.println("ASSIST");
  tft.println();
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(2);
  tft.println("Press Button 1");
  tft.println("to authenticate yourself.");
  return 0;
}
