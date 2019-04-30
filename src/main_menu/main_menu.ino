//todo: please clean this up im rusty on this and dont wanna think about it
#include "pin_definitions.h"
#include "FPS_GT511C3.h"
#include "SoftwareSerial.h"
//TODO: i think we dont need this?
#include "medication.h"
#include "user.h"
//how do you include system.h or should we like redo it idk
// use your judgment i trust you

#define BUTTON_ONE shiftReg[4]
#define BUTTON_TWO shiftReg[5]
#define BUTTON_THREE (ROT_SWITCH_PIN & (1 << ROT_SWITCH_pin))

//TODO: plz put the right pins here, james
FPS_GT511C3 fps(4, 5);

int shiftReg[8];
/* shiftReg
  0: Hall1
  1: Hall2
  2: Hall3
  3: UNUSED
  4: Switch1
  5: Switch2
*/

enum States
{
  Welcome, Authenticate, Main_Menu, User_Menu_1, User_Menu_2,
  Add_User, Remove_User, Elevate_User, Meds_Menu_1,
  Meds_Menu_2, Supply_Mode, Get_Meds, Add_Scrips
};

enum States system_state = Welcome;

void setup()
{
  Serial.begin(9600);
  fps.Open(); //send serial command to initialize fps
  // Set SHIFTREG and ROT_SWITCH as inputs.
  DDRD &= !(1 << SHIFTREG_Q_pin);
  DDRD &= !(1 << ROT_SWITCH_pin);
  Serial.println("SETUP TEST");
}

void loop()
{
  //TODO: hi pls get this to work, yay!
  //readShiftRegister(shiftReg);
  switch (system_state)
  {
  case Welcome:
  {
    Serial.println("Welcome! Press 1 to authenticate");
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
    Serial.println("1) Meds menu\n2) User menu\n3) Log out");
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
      if (BUTTON_THREE == 0) {
        system_state = Welcome;
        break;
      }
    }
    break;
  }
  case Add_User:
  {
    Serial.println("Add user! Follow the instructions");
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
    Serial.println("1) Add\n2) Remove\n3) More options");
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
      if (BUTTON_THREE == 0)
      {
        system_state = User_Menu_2;
        break;
      }
    }
    break;
  }
  case User_Menu_2:
  {
    Serial.println("1) Elevate \n2) Back to main menu");
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
  case Authenticate:
  {
    Serial.println("Please authenticate yourself by placing your finger down on the scanner.");
    fps.SetLED(true); // turn on LED so fps can see fingerprint
    while (1)
    {
      // Identify fingerprint
      if (fps.IsPressFinger())
      {
        fps.CaptureFinger(false);
        int id = fps.Identify1_N();

        if (id < 200)
        {
          //TODO: get this to work
          /*if (getUserFromId(id)) // Checks that user is registered
          {
            Serial.print("Access granted. Verified ID:");
            Serial.println(id);
            system_state = Main_Menu;
          }
          else
          {
            Serial.println("Access denied. You're being sent to jail, don't collect $200");
            // TODO: add a buzz here
            system_state = Welcome;
          }
          */
        }
        else
        {
          Serial.println("Finger not found. You're being sent to jail, don't collect $200");
          // TODO: add a buzz here
          system_state = Welcome;
        }
      }
      else
      {
        Serial.println("Please press finger");
      }
      delay(100);
    }
    break;
  }
  case Remove_User:
  {
    Serial.println("Scroll through this list of users and press down on the rotary encoder.");
    while (1)
    {
      // TODO: add rotary code to actually scroll through the users

      //then once you pressed it, beep and leave
      if (BUTTON_THREE == 0)
      {
        // TODO: add a beep
        system_state = Main_Menu;
        break;
      }
    }
    break;
  }
  case Elevate_User:
  {
    Serial.println("Scroll through this list of users and press down on the rotary encoder.");
    while (1)
    {
      // TODO: add rotary code to actually scroll through the users

      //then once you pressed it, beep and leave
      if (BUTTON_THREE == 0)
      {
        // TODO: add a beep
        system_state = Main_Menu;
        break;
      }
    }
    break;
  }
  case Meds_Menu_1:
  {
    Serial.println("1) Get meds\n2) Add scrip\n3) More options");
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
      if (BUTTON_THREE == 0)
      {
        system_state = Meds_Menu_2;
        break;
      }
    }
    break;
  }
  case Meds_Menu_2:
  {
    Serial.println("1) Supply mode\n2) Main menu");
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
    Serial.println("Supply mode time");

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
    Serial.println("Get meds!");

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
    Serial.println("Add scrips! Follow the instructions");
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
 delay(100);
}
