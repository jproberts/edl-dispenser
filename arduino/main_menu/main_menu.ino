/* Missing many features but this is a basic framework */

#define BUTTON_ONE 7
#define BUTTON_TWO 8
#define BUTTON_THREE 9

enum States {
  WELCOME_MENU,
  USER_MENU_1,
  PRESCRIPTION_MENU,
  TAKING_MEDS_MENU,
  GIVE_USER_INFO,
  AUTHENTICATE_USER,
  USER_MENU_2,
  USER_LIST,
  GIVE_PRESCRIPTION_INFO,
  OPEN_LID_MENU,
  AUTHENTICATE_OTHER,
  MEDS_DASHBOARD,
  LID_IS_OPEN
};

enum States system_state = WELCOME_MENU;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_ONE, INPUT_PULLUP);
  pinMode(BUTTON_TWO, INPUT_PULLUP);
  pinMode(BUTTON_THREE, INPUT_PULLUP);
}

void loop() {
  switch(system_state) {
    case WELCOME_MENU: {
      Serial.println("Welcome! The time is 00:00\n1. User functions\n2. Prescription functions\n3. Give/Get meds");
      while(1) {
        if (digitalRead(BUTTON_ONE) == LOW) {
          system_state = USER_MENU_1;
          break;
        }
        if (digitalRead(BUTTON_TWO) == LOW) {
          system_state = PRESCRIPTION_MENU;
          break;
        }
        if (digitalRead(BUTTON_THREE) == LOW) {
          system_state = TAKING_MEDS_MENU;
          break;
        }
      }
      break;
    }
    case USER_MENU_1: {
      Serial.println("User functions:\n1. Add user\n2. Remove user\n3. More options");
      while(1) {
        if (digitalRead(BUTTON_ONE) == LOW || digitalRead(BUTTON_TWO) == LOW) {
          system_state = GIVE_USER_INFO;
          break;
        }
        if (digitalRead(BUTTON_THREE) == LOW) {
          system_state = USER_MENU_2;
          break;
        }
      }
      break;
    }
    case PRESCRIPTION_MENU: {
      Serial.println("Prescription functions:\n1. Add scrip\n2. Remove scrip\n3. Return to welcome screen");
      while(1) {
        if (digitalRead(BUTTON_ONE) == LOW || digitalRead(BUTTON_TWO) == LOW) {
          system_state = GIVE_PRESCRIPTION_INFO;
          break;
        }
        if (digitalRead(BUTTON_THREE) == LOW) {
          system_state = WELCOME_MENU;
          break;
        }
      }
      break;
    }
    case TAKING_MEDS_MENU: {
      Serial.println("Give/get meds:\n1. Open the box\n2. Get your meds\n3. Return to welcome screen");
      while(1) {
        if (digitalRead(BUTTON_ONE) == LOW) {
          system_state = OPEN_LID_MENU;
          break;
        }
        if (digitalRead(BUTTON_TWO) == LOW) {
          system_state = AUTHENTICATE_OTHER;
          break;
        }
        if (digitalRead(BUTTON_THREE) == LOW) {
          system_state = WELCOME_MENU;
          break;
        }
      }
      break;
    }
    case GIVE_USER_INFO: {
      Serial.println("Please give the necessary info needed to perform this user action. Press (1) to move on and authenticate");
      while(1) {
        if (digitalRead(BUTTON_ONE) == LOW) {
          system_state = AUTHENTICATE_USER;
          break;
        }
      }
      break;
    }
    case AUTHENTICATE_USER: {
      Serial.println("Please authenticate yourself by placing your finger down on the scanner.");
      while(1) {
        //nope, this should be fingerprint authenticating
        if (digitalRead(BUTTON_ONE) == LOW) {
          system_state = WELCOME_MENU;
          break;
        }
      }
      break;
    }
    case USER_MENU_2: {
      Serial.println("More user functions:\n1. Elevate user \n2. Show all users \n3. Return to welcome screen");
      while(1) {
        if (digitalRead(BUTTON_ONE) == LOW) {
          system_state = GIVE_USER_INFO;
          break;
        }
        if (digitalRead(BUTTON_TWO) == LOW) {
          system_state = USER_LIST;
          break;
        }
        if (digitalRead(BUTTON_THREE) == LOW) {
          system_state = WELCOME_MENU;
          break;
        }
      }
      break;
    }
    case USER_LIST: {
      Serial.println("Here is a list of all of the users.\n0. Sarah\n1. James\n2. Elizabeth\n3. Pedro");
      while(1) {
        if (digitalRead(BUTTON_ONE) == LOW) {
          system_state = WELCOME_MENU;
          break;
        }
      }
      break;
    }
    case GIVE_PRESCRIPTION_INFO: {
      Serial.println("Please give the necessary info needed to perform this prescription action. Press (1) to move on and authenticate");
      while(1) {
        if (digitalRead(BUTTON_ONE) == LOW) {
          system_state = AUTHENTICATE_USER;
          break;
        }
      }
      break;
    }
    case OPEN_LID_MENU: {
      Serial.println("Open the box:\n1. Add medication to box\n2. Take medication from the box\n3. Return to welcome screen");
      while(1) {
        if (digitalRead(BUTTON_ONE) == LOW || digitalRead(BUTTON_TWO) == LOW) {
          system_state = AUTHENTICATE_OTHER;
          break;
        }
        if (digitalRead(BUTTON_THREE) == LOW) {
          system_state = WELCOME_MENU;
          break;
        }
      }
      break;
    }
    case AUTHENTICATE_OTHER: {
      Serial.println("Please authenticate yourself by placing your finger down on the scanner\nMore info to come");
      while(1) {
        //nope, this should be fingerprint authenticating
        if (digitalRead(BUTTON_ONE) == LOW) {
          system_state = OPEN_LID_MENU;
          break;
        }
      }
      break;
    }
    case MEDS_DASHBOARD: {
      Serial.println("You will be getting your meds shortly!\nSupply: 30 pills left\nNext medication: 6 hours from now, or 06:00\nPress (1) to return to the welcome screen");
      while(1) {
        if (digitalRead(BUTTON_ONE) == LOW) {
          system_state = WELCOME_MENU;
          break;
        }
      }
      break;
    }
    case LID_IS_OPEN: {
      Serial.println("The lid is open. Please take care of your operation and press (1) when you are finished.");
      while(1) {
        if (digitalRead(BUTTON_ONE) == LOW) {
          system_state = WELCOME_MENU;
          break;
        }
      }
      break;
    }
  }
}
