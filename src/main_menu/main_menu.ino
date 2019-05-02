#include "pin_definitions.h"
#include "FPS_GT511C3.h"
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <util/delay.h>
#include "medication.h"
#include "user.h"
#include "SimpleTimer.h"
#include <Encoder.h>

/* DISPLAY */
// TODO: Find out what these should be in avr land
#define TFT_DC 9
#define TFT_CS 10

/* ROTARY */
#define debounce 200 //milliseconds
#define ENCODER_DO_NOT_USE_INTERRUPTS
char my_name[6] = {'j', 'a', 'm', 'e', 's', '\0'};
char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
  'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
  'u', 'v', 'w', 'x', 'y', 'z'}; // TODO: do i have to null terminate this or is it ok
uint8_t current_index;
unsigned long prevTime, position;
Encoder rotary(ROTA_pin, ROTB_pin); //TODO: map from avr land again

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
// If using the breakout, change pins as desired
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

/* SHIFT REGISTER */
#define BUTTON_ONE shiftReg[4]
#define BUTTON_TWO shiftReg[5]
#define BUTTON_THREE (ROT_SWITCH_PIN & (1 << ROT_SWITCH_pin))

/* SYSTEM */

#define MAX_USERS 8
#define MAX_MEDICATIONS 24

uint8_t numUsers;
uint8_t numMeds;
User *UserList;
Medication *MedicationList;
char availableMeds[3];

userIdType addUser(char *name, fingerIdType fingerprint);
bool removeUser(uint8_t userId, fingerIdType fingerprint);
bool elevateUser(uint8_t userId, fingerIdType fingerprint);
User *getUserFromId(userIdType userId);
User *getUserFromPrint(fingerIdType fingerprint);
bool addPrescription(User *user, Medication *meds);
bool removePrescription(User *user, Medication *meds);
void alertUser(Medication *meds);

SimpleTimer ttimer;

uint8_t shiftReg[8];
/* shiftReg
  0: Hall1
  1: Hall2
  2: Hall3
  3: UNUSED
  4: Switch1
  5: Switch2
*/

/* FINGERPRINT SENSOR */

// TODO: put the right pins here
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
  // fps.Open(); // TODO: uncomment
  tft.begin(); // Initialize display.
  // Set SHIFTREG and ROT_SWITCH as inputs.
  DDRD &= !(1 << SHIFTREG_Q_pin);
  DDRD &= !(1 << ROT_SWITCH_pin);
  // Also do that for rotary channels A and B.
  DDRD &= !(1 << ROTA_pin);
  DDRD &= !(1 << ROTB_pin);
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
}

User *currentUser = NULL;

void loop()
{
  // Reset display
  tft.fillScreen(ILI9341_OLIVE);
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println();
  // readShiftRegister(shiftReg); 
  // TODO: uncomment this
  switch (system_state)
  {
  case Welcome:
  {
    showWelcomeScreen();
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
    showMainMenu();
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
      if (BUTTON_THREE == 0)
      {
        system_state = Welcome;
        break;
      }
    }
    break;
  }
  case Add_User:
  {
    tft.println(F("Add user! Follow the instructions"));
    // TODO: add more instructions i guess
    while (1)
    {
      // Once you press button two, you're done with your name
      while(BUTTON_TWO == 1) {
          unsigned long newPos = abs(rotary.read() % 26);
          if (newPos != position && newPos >= 0) {
            position = newPos;
          }

          if (millis() - prevTime > debounce) {
            if (BUTTON_THREE == 0) {
              current_index++;
              my_name[current_index % 6] = letters[position];
              tft.println(my_name); // TODO: check to see if this looks good
              prevTime = millis();  
           }
        }    
      }  
    
      // TODO: Enroll your fingerprint and press button three to end it
      while(BUTTON_THREE == 1) {
        fps.SetLED(true);
        int enrollid = 0;
        bool usedid = true;
        while (usedid == true)
        {
          usedid = fps.CheckEnrolled(enrollid);
          if (usedid==true) enrollid++;
        }
        fps.EnrollStart(enrollid);

        // enroll
        tft.println(F("Press finger to Enroll #"));
        tft.println(enrollid);
        while(fps.IsPressFinger() == false) delay(100);
        bool bret = fps.CaptureFinger(true);
        int iret = 0;
        if (bret != false)
        {
          tft.println("Remove finger");
          fps.Enroll1(); 
          while(fps.IsPressFinger() == true) delay(100);
          tft.println(F("Press same finger again"));
          while(fps.IsPressFinger() == false) delay(100);
          bret = fps.CaptureFinger(true);
          if (bret != false)
          {
            tft.println(F("Remove finger"));
            fps.Enroll2();
            while(fps.IsPressFinger() == true) delay(100);
            tft.println("Press same finger yet again");
            while(fps.IsPressFinger() == false) delay(100);
            bret = fps.CaptureFinger(true);
            if (bret != false)
            {
              tft.println(F("Remove finger"));
              iret = fps.Enroll3();
              if (iret == 0)
              {
                tft.println(F("Enrolling Successful"));
              }
            else
            {
          tft.print(F("Enrolling Failed with error code:"));
          system_state = Welcome;
          break;
        }
      }
      else Serial.println(F("Failed to capture third finger"));
    }
    else Serial.println(F("Failed to capture second finger"));
  }
  else Serial.println(F("Failed to capture first finger"));
        
      }

    // Press button one to get out of here
    if (BUTTON_ONE == 0)
    {
      system_state = Main_Menu;
      break;
     }
  }
    break;
  }
  case User_Menu_1:
  {
    showUserMenu1();
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
    showUserMenu2();
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

  case Authenticate:
  {
    showAuthenticateScreen();
    fps.SetLED(true);
    while (1)
    {
      if (fps.IsPressFinger())
      {
        fps.SetLED(false);
        fps.CaptureFinger(false);
        int id = fps.Identify1_N();

        if (id < 200)
        {
          currentUser = getUserFromId(id);
          if (currentUser) // Checks that user is registered
          {
            tft.print(F("Access granted. Verified ID: "));
            tft.println(id);
            system_state = Main_Menu;
          }
          else
          {
            tft.println(F("Access denied. You're being sent to jail, don't collect $200"));
            buzz();
            system_state = Welcome;
          }
        }
        else
        {
          tft.println(F("Finger not found. You're being sent to jail, don't collect $200"));
          buzz();
          system_state = Welcome;
          break;
        }
      }
      else
      {
        tft.println(F("Please press finger"));
      }
      _delay_ms(100);
    }
    break;
  }
  case Remove_User:
  {
    tft.println(F("Scroll through this list of users and press down on the rotary encoder."));
    while (1)
    {
      // TODO: add rotary code to actually scroll through the users

      if (BUTTON_THREE == 0)
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
    tft.println(F("Scroll through this list of users and press down on the rotary encoder."));
    while (1)
    {
      // TODO: add rotary code to actually scroll through the users

      if (BUTTON_THREE == 0)
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
    showMedsMenu1();
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
    showMedsMenu2();
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
    tft.println(F("Supply mode time"));

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
    break;
  }
  case Get_Meds:
  {
    tft.println(F("Get meds!"));
    // Todo: move this stuff inside the while, otherwise it's going to happen a million times

    // TODO: if meds available, dispense and show remaining count
    // else display time for next dispensing
    bool dispensed = false;
    for (uint8_t i = 0; i < 3; i++)
    {
      if (availableMeds[i] & (1 << currentUser->UserId))
      {
        dispenseMedication(i);
        dispensed = true;
      }
    }
    if (!dispensed)
    {
      tft.print(F("You have no medication available at this time."));
    }
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
    tft.println(F("Add scrips! Follow the instructions"));
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
  // TODO: make a tone
  tft.println(F("BEEP"));
}

void showWelcomeScreen()
{
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(3);
  tft.println(F("    WELCOME TO"));
  tft.print(F("   PHARM"));
  tft.setTextColor(ILI9341_RED);
  tft.print(F("-"));
  tft.setTextColor(ILI9341_WHITE);
  tft.println(F("ASSIST"));
  tft.println();
  tft.setTextColor(ILI9341_MAROON);
  tft.setTextSize(2);
  tft.println(F(" Press Button 1"));
  tft.println(F(" to authenticate yourself."));
  _delay_ms(4000);
  return;
}

void showMainMenu()
{
  tft.setTextColor(ILI9341_MAROON);
  tft.setTextSize(3);
  tft.println(F("  \t\tMAIN MENU\t\t\n"));
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println(F(" 1) Meds menu\n 2) User menu\n 3) Log out")); // Note: tft handles \n characters, so this will work.
  _delay_ms(4000);
}

void showUserMenu1()
{
  tft.setTextColor(ILI9341_MAROON);
  tft.setTextSize(3);
  tft.println(F("   \tUSER MENU\t\n"));
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println(F(" 1) Add user\n 2) Remove user\n 3) More options"));
  _delay_ms(4000);
}

void showUserMenu2()
{
  tft.setTextColor(ILI9341_MAROON);
  tft.setTextSize(3);
  tft.println(F(" \tUSER MENU cont\t\n"));
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println(F(" 1) Elevate user \n 2) Back to main menu"));
  _delay_ms(4000);
}

void showAuthenticateScreen()
{
  tft.setTextColor(ILI9341_MAROON);
  tft.setTextSize(3);
  tft.println(F("  \tAUTHENTICATE\t\n"));
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println(F(" Please place your finger\nto authenticate yourself."));
}

void showMedsMenu1()
{
  tft.setTextColor(ILI9341_MAROON);
  tft.setTextSize(3);
  tft.println(F("   \tMEDS MENU\t\n"));
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println(F(" 1) Get meds\n 2) Add perscription\n 3) More options"));
  _delay_ms(4000);
}

void showMedsMenu2()
{
  tft.setTextColor(ILI9341_MAROON);
  tft.setTextSize(3);
  tft.println(F(" \tMEDS MENU cont\t\n"));

  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println(F(" 1) Supply mode\n 2) Main menu"));
  _delay_ms(4000);
}

User *getUserFromId(userIdType userId)
{
  for (uint8_t i = 0; i < numUsers; i++)
  {
    User *user = UserList + i;
    if (user->UserId == userId)
      return user;
  }
  return nullptr;
}

User *getUserFromPrint(fingerIdType fingerprint)
{
  for (uint8_t i = 0; i < numUsers; i++)
  {
    User *user = UserList + i;
    if (user->Fingerprint == fingerprint)
      return user;
  }
  return nullptr;
}

userIdType addUser(char *name, fingerIdType fingerprint)
{
  if (numUsers == MAX_USERS)
  {
    return -1;
  }
  User newUser = User(name, fingerprint);
  UserList[numUsers++] = (newUser);
  return newUser.UserId;
}

bool removeUser(uint8_t userId, fingerIdType fingerprint)
{
  User *admin = getUserFromPrint(fingerprint);
  if (admin == nullptr || !admin->Trusted)
    return false;
  else
  {
    bool swap = false;
    for (uint8_t i = 0; i < numUsers; i++)
    {
      User *user = UserList + i;
      if (user->Fingerprint == fingerprint)
      {
        swap = true;
      }
      if (swap)
      {
        UserList[i] = UserList[i + 1];
      }
    }
    if (swap)
    {
      numUsers--;
    }
    return swap;
  }
}

bool elevateUser(uint8_t userId, fingerIdType fingerprint)
{
  User *admin = getUserFromPrint(fingerprint);
  User *user = getUserFromId(userId);

  if (admin == nullptr || user == nullptr)
    return false;
  else
    return user->elevateTrust(admin);
}

bool addPrescription(User *user, Medication *meds)
{
  return true;
}

void dispenseMedication(uint8_t containerNum)
{
  return;
}

void revokeMeds(uint8_t id)
{
  availableMeds[id / 10] &= ~(1 << id % 10);
}

void alertUser(Medication *meds)
{
  Serial.print(meds->Name);
  Serial.println(F(" is ready."));
  for (uint8_t i = 0; i < numUsers; i++)
  {
    for (uint8_t j = 0; j < 3; j++)
    {
      if (UserList[i].Prescriptions[j].UniqueId == meds->UniqueId)
      {
        availableMeds[meds->ContainerNum] |= (1 << UserList[i].UserId);
        ttimer.setTimeout(1800000, revokeMeds, meds->ContainerNum * 10 + UserList[i].UserId);
      }
    }
  }
}

void createAlert(Medication *meds)
{
  ttimer.setTimer(meds->Frequency, alertUser, meds, 10);
}

void setupAlert(Medication *meds)
{
  ttimer.setTimeout(meds->TimeOfDay, createAlert, meds);
}

void openLid()
{
  SOLENOID_FORWARD_PORT |= (1 << SOLENOID_FORWARD_pin);
  SOLENOID_REVERSE_PORT &= ~(1 << SOLENOID_REVERSE_pin);
  _delay_us(10); // Delays are all in microseconds, so this should be plenty.
  SOLENOID_FORWARD_PORT &= ~(1 << SOLENOID_FORWARD_pin);
  _delay_us(10);
}

void closeLid()
{
  SOLENOID_REVERSE_PORT |= (1 << SOLENOID_REVERSE_pin);
  SOLENOID_FORWARD_PORT &= ~(1 << SOLENOID_FORWARD_pin);
  _delay_us(10); // Delays are all in microseconds, so this should be plenty.
  SOLENOID_REVERSE_PORT &= ~(1 << SOLENOID_REVERSE_pin);
  _delay_us(10);
}
