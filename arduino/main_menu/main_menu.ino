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
  pinMode(BUTTON_ONE, INPUT_PULLUP);
  pinMode(BUTTON_TWO, INPUT_PULLUP);
  pinMode(BUTTON_THREE, INPUT_PULLUP);
}

void loop() {
  switch(system_state) {
    case WELCOME_MENU: {
      break;
    }
    case USER_MENU_1: {
      break;
    }
    case PRESCRIPTION_MENU: {
      break;
    }
    case TAKING_MEDS_MENU: {
      break;
    }
    case GIVE_USER_INFO: {
      break;
    }
    case AUTHENTICATE_USER: {
      break;
    }
    case USER_MENU_2: {
      break;
    }
    case USER_LIST: {
      break;
    }
    case GIVE_PRESCRIPTION_INFO: {
      break;
    }
    case OPEN_LID_MENU: {
      break;
    }
    case AUTHENTICATE_OTHER: {
      break;
    }
    case MEDS_DASHBOARD: {
      break;
    }
    case LID_IS_OPEN: {
      break;
    }
  }
}
