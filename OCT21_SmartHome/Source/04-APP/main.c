/***************************************
 * main.c
 *
 *  Created on: Oct , 2022
 *
 ***************************************/
#include "Std_Types.h"
#include "Bit_Math.h"
#include <util/delay.h>
#include "Led.h"
#include "Lcd.h"
#include <stdio.h>
#include "Button.h"
#include "Buzzer.h"
#include "GINT.h"
#include "ExtInt.h"
#include "Adc.h"
#include "Lm35.h"
#include "Uart.h"
#include "Hc05.h"
#include "Eeprom.h"
#include "Dc_Motor.h"
#include "Servo_Motor.h"
#include "TIMER1.h"
#include "KeyPad.h"
#include "Relay.h"



#define FIRST_PAGE           '0'
#define ADMIN_LOGIN_PAGE     '1'
#define USER_LOGIN_PAGE      '2'
#define WELCOME               0
#define ADMIN_SECOND_PAGE     1
#define USER_SECOND_PAGE      2
#define ADMIN_THIRD_PAGE      3
#define ADMIN_FOURTH_PAGE     4
#define IDLE_STATE            5
#define AdminMode             1
#define UserMode              2



//#include "ExtInt.h"
#define F_CPU 16000000UL
#include <util/delay.h>

void InputID    (u8* ID, u8 Mode);
void InputPassword  (u8* Password, u8 Mode);
u8 AdminLogin (u8* ID, u8* Password);
void AddUser (u8* ID, u8* Password);
u8 UserLogin ( u8* ID, u8* Password);
void CheckEEPROM(void);
void DeleteUser (u8 NumberOfUsers, u8* ID);
void DeleteAll (void);
void ACSwitch (u8* ACOpened);
void RelaySwitch(u8* RelayOpened);
void AppInit(void);
void WelcomingMsg(void);
void CheckAC(u8 ACState);
void CheckRelay(u8 RelayState);
void Reset(u8* ACState, u8* DoorState, u8* RelayState);

u8 AppState = WELCOME;


/************************************************************************/
/*  Admin Password is 1234
  Admin UserName is 123
  Admin Location is @ 101 byte address page 1             */
/************************************************************************/

int main ()
{
  Keypad_vidinit();
  Lcd_vidinit();
  Dc_Motor_vidInit();
  Lm35_vidInit();
  ServoMotor_VidInit();
  Led_vidinit();
  Buzzer_vidinit();
  Button_vidbuttonInit();
  Relay_Init();
  Hc05_Init();

  /* Initiate the UserID and Password */
  //Remove two below comments when first use of code
  //  DeleteAll();
  //  AppInit();

  char NumberOfUsers = 0;

  NumberOfUsers = EEPROM_Read(100);
  u8 UserID   [3] = {0, 0, 0};
  u8 UserPassword [4] = {0, 0, 0, 0};
  u8 KeyPressed = 0;
  u8 Trails = 0;
  Door_State_t DoorState = CLOSED;
  u8 ACState = 0;
  u8 RelayState = 0;
  u8 BluetoothData = 0;

  while (1)
  {
    switch (AppState)
    {
      case WELCOME :
        WelcomingMsg();
        AppState = FIRST_PAGE;
        break;
      case FIRST_PAGE:
        Lcd_vidCmd(_LCD_CLEAR);
        Lcd_vidDisplayStr("    Welcome     ");
        Hc05_SendString("Choose user using Keypad");
        Lcd_vidRowColumn(1, 0);
        Lcd_vidDisplayStr("1:Admin 2:User");
        Hc05_SendString("1:Admin 2:User");
        KeyPressed = Keypad_getChar();
        while (!KeyPressed)
        {
          KeyPressed = Keypad_getChar();
          if (KeyPressed == '1')
          {
            AppState = ADMIN_LOGIN_PAGE;
          }
          else if (KeyPressed == '2')
          {
            AppState = USER_LOGIN_PAGE;
          }
          else
          {
            /*DO NOTHING*/
          }

        }
        break;

      case ADMIN_LOGIN_PAGE:
        Trails = 0;
        Lcd_vidCmd(_LCD_CLEAR);
        Hc05_SendString("Welcome Admin");
        Lcd_vidDisplayStr("Welcome Admin");
        _delay_ms(1000);
        Lcd_vidCmd(_LCD_CLEAR);
        Lcd_vidRowColumn(0, 0);
        Lcd_vidDisplayStr("Admin Mode");
        Lcd_vidRowColumn(1, 0);
        Lcd_vidDisplayStr("Use Bluetooth");
        Hc05_SendString("Use Bluetooth");
        _delay_ms(3000);

        while (Trails < 3)
        {
          Hc05_SendString("Enter Username");
          InputID(UserID, AdminMode);
          Hc05_SendString("Enter Password");
          InputPassword(UserPassword, AdminMode);

          if (AdminLogin(UserID, UserPassword) == 0)
          {
            AppState = ADMIN_SECOND_PAGE;
            break;
          }
          else
          {
            Trails++;
            if (Trails == 3)
            {
              Buzzer_vidbuzzerOn();
              ServoMotor_VidCloseDoor();
              KeyPressed = Button_udtbuttonStatus(BUTTON2);
              while (1)
              {
                if (Button_udtbuttonStatus(BUTTON2) == PRESSED)
                {
                  _delay_ms(80);
                  if (Button_udtbuttonStatus(BUTTON2) == PRESSED)
                  {
                    while (Button_udtbuttonStatus(BUTTON2) == PRESSED);
                    Buzzer_vidbuzzerOff();
                    AppState = WELCOME;
                    break;
                  }
                }
              }
            }
          }
        }
        Trails = 0;
        break;

      case USER_LOGIN_PAGE:
        Trails = 0;
        Lcd_vidCmd(_LCD_CLEAR);
        Lcd_vidDisplayStr("Welcome User");
        _delay_ms(1000);
        while (Trails < 3)
        {
          Lcd_vidCmd(_LCD_CLEAR);
          Lcd_vidDisplayStr("Enter Username");
          InputID(UserID, UserMode);
          Lcd_vidCmd(_LCD_CLEAR);
          Lcd_vidDisplayStr("Enter Password");
          InputPassword(UserPassword, UserMode);
          u8 LoginResult = UserLogin(UserID, UserPassword);

          if (LoginResult == 0)
          {
            AppState = USER_SECOND_PAGE;
            break;
          }
          else if (LoginResult == 2)
          {
            AppState = FIRST_PAGE;
            break;
          }
          else if (LoginResult == 1)
          {
            Trails++;
            if (Trails == 3)
            {
              Buzzer_vidbuzzerOn();
              ServoMotor_VidCloseDoor();
              Lcd_vidCmd(_LCD_CLEAR);
              KeyPressed = Button_udtbuttonStatus(BUTTON2);

              while (1)
              {
                if (Button_udtbuttonStatus(BUTTON2) == PRESSED)
                {
                  _delay_ms(80);
                  if (Button_udtbuttonStatus(BUTTON2) == PRESSED)
                  {
                    while (Button_udtbuttonStatus(BUTTON2) == PRESSED);
                    Buzzer_vidbuzzerOff();
                    AppState = WELCOME;
                    break;
                  }
                }
              }
            }
          }
        }
        Trails = 0;
        break;

      case ADMIN_SECOND_PAGE:
        BluetoothData = 0;
        BluetoothData = Hc05_Rec();
        switch (BluetoothData)
        {
          // A ->  A/C Switch
          case 'A':    ACSwitch(&ACState);                          break;
          // B ->  Add user
          case 'B':
        	Lcd_vidCmd(_LCD_CLEAR);
            Lcd_vidDisplayStr("Use KeyPad");
            Hc05_SendString("Use KeyPad");
            _delay_ms(3000);
            InputID(UserID, UserMode);
            InputPassword(UserPassword, UserMode);
            AddUser(UserID, UserPassword);                       break;
          // C -> Remove user
          case 'C':
            NumberOfUsers = EEPROM_Read(100);
            Lcd_vidCmd(_LCD_CLEAR);
            Lcd_vidDisplayStr("Use Bluetooth");
            Hc05_SendString("Use Bluetooth"); _delay_ms(3000);
            InputID(&UserID, AdminMode);
            DeleteUser(NumberOfUsers, UserID);                     break;
          // D -> Door Switch
          case 'D':  ServoMotor_VidSwitchDoor(&DoorState);                         break;
          // R -> Relay Switch
          case 'R':   RelaySwitch(&RelayState);                       break;
          // U -> User Mode
          case 'U':     AppState = USER_LOGIN_PAGE;                      break;
          // S -> Resut Mode
          case 'S': Reset(&ACState, &DoorState, &RelayState);  AppState = WELCOME;         break;
          //I -> Idle State (OK)
          case 'I':     AppState = IDLE_STATE;                       break;
          default:                                        break;
        }
        break;
      case IDLE_STATE:
        BluetoothData = Hc05_Rec();
        while (!BluetoothData)
        {
          BluetoothData = Hc05_Rec();
          CheckAC(ACState);
          CheckRelay(RelayState);
          ServoMotor_VidCheckDoor(DoorState);
        }
        AppState = WELCOME;

        break;

      case USER_SECOND_PAGE :
    	Lcd_vidCmd(_LCD_CLEAR);
        Lcd_vidDisplayStr(" 1:Switch Relay ");
        Lcd_vidRowColumn(1, 0);
        Lcd_vidDisplayStr("2:AcSwitch  3:OK");
        KeyPressed = Keypad_getChar();
        while (!KeyPressed)
        {
          KeyPressed = Keypad_getChar();
          if (KeyPressed == '1')
          {
            RelaySwitch(&RelayState);
          }
          else if (KeyPressed == '2')
          {
            ACSwitch(&ACState);
          }
          else if (KeyPressed == '3')
          {
            AppState = IDLE_STATE;
          }
        }
        break;
    }

  }
  return 0;
}


void AddUser (u8* ID, u8* Password)
{
  u8 NumberOfUsers = EEPROM_Read(100);
  if (NumberOfUsers < 10)
  {
    u8 Counter = 0, UserLocation  = 0;

    if (NumberOfUsers > 0)
    {
      u8 WrongEntry = 0;

      for (; Counter < NumberOfUsers; Counter++)
      {

        UserLocation = (Counter * 7);
        u8 Check = 0, EEPROMData = 0, EEPROMDataLocation = 0, ValidEntries = 3;

        for (; Check < 3; Check++)
        {
          EEPROMDataLocation = UserLocation + Check;
          EEPROMData = EEPROM_Read(EEPROMDataLocation);
          if (ID[Check] == EEPROMData )
          {
            ValidEntries--;
          }

        }

        if (ValidEntries == 0)
        {
          /*print on LCD invalid username*/
          WrongEntry ++;
          Lcd_vidCmd(_LCD_CLEAR);
          Lcd_vidDisplayStr("Invalid Username");
          Hc05_SendString("Invalid Username");
          _delay_ms(500);
        }
      }


      if (WrongEntry == 0)
      {
        /*print on LCD valid entry*/
    	Lcd_vidCmd(_LCD_CLEAR);
        Lcd_vidDisplayStr("Valid Entry");
        Hc05_SendString("Valid Entry");
        _delay_ms(500);
        u8 Check = 0, EEPROMDataLocation = 0;
        UserLocation = NumberOfUsers * 7;
        for (; Check < 3; Check++)
        {
          EEPROMDataLocation = UserLocation + Check;
          EEPROM_Write(EEPROMDataLocation, ID[Check]);
        }

        for (Check = 0; Check < 4; Check++)
        {
          EEPROMDataLocation = UserLocation + Check + 3;
          EEPROM_Write(EEPROMDataLocation, Password[Check]);
        }
        NumberOfUsers++;
        EEPROM_Write(100, NumberOfUsers);

      }
    }
    else /*There isn't any user yet*/
    {
      Lcd_vidCmd(_LCD_CLEAR);
      Lcd_vidDisplayStr("Valid Entry");
      _delay_ms(500);
      Hc05_SendString("Valid Entry");
      u8 Check = 0, EEPROMDataLocation = 0;
      UserLocation = NumberOfUsers * 7;     /*UserLocation = 0*/
      for (; Check < 3; Check++)
      {
        EEPROMDataLocation = UserLocation + Check;
        EEPROM_Write(EEPROMDataLocation, ID[Check] );
      }

      for (Check = 0; Check < 4; Check++)
      {
        EEPROMDataLocation = UserLocation + Check + 3;
        EEPROM_Write(EEPROMDataLocation, Password[Check]);
      }
      NumberOfUsers++;
      EEPROM_Write(100, NumberOfUsers );

      Lcd_vidCmd(_LCD_CLEAR);
      Lcd_vidDisplayStr("User Added");
      Hc05_SendString("User Added");
      Lcd_vidRowColumn(1, 0);
      Lcd_vidDisplayStr("No of Users ");
      Hc05_SendString("No of Users ");
      Lcd_vidDisplayInt(EEPROM_Read(100));
      Hc05_Send(EEPROM_Read(100));
      _delay_ms(500);
    }
  }
  else /*Number of users is equal or more than 10 users */
  {
    /*Print on LCD you reached max number of users*/
	Lcd_vidCmd(_LCD_CLEAR);
    Lcd_vidDisplayStr("Reached max");
    Lcd_vidRowColumn(1, 0);
    Lcd_vidDisplayStr("Number Of Users");
    Hc05_SendString("Reached max number Of Users");
    _delay_ms(500);
  }
}

void DeleteUser (u8 NumberOfUsers, u8* ID)
{
  _delay_ms(100);
  Lcd_vidCmd(_LCD_CLEAR);

  if (NumberOfUsers > 0)
  {
    u8 Counter = 0, UserLocation  = 0, PerfectMatch = 0;

    for (; Counter < NumberOfUsers; Counter++)
    {
      UserLocation = (Counter * 7);
      u8 Check = 0, EEPROMData = 0, EEPROMDataLocation = 0, ValidEntries = 0;

      for (; Check < 3; Check++)
      {
        EEPROMDataLocation = UserLocation + Check;
        EEPROMData = EEPROM_Read(EEPROMDataLocation);
        if (ID[Check] == EEPROMData )
        {
          ValidEntries++;
        }

      }

      if (ValidEntries == 3)
      {
        /*print on LCD valid username*/
        Lcd_vidDisplayStr("Valid Username");
        Hc05_SendString("Valid Username");
        _delay_ms(200);
        PerfectMatch ++;

      }
      if (PerfectMatch == 1)
      {
        u8 Check = 0, EEPROMDataLocation = 0;
        for (; Check < 3; Check++)
        {
          EEPROMDataLocation = UserLocation + Check;
          EEPROMData = EEPROM_Read( EEPROMDataLocation + 7);
          EEPROM_Write(EEPROMDataLocation, EEPROMData );
        }
        Check = 0;
        for (; Check < 4; Check++)
        {
          EEPROMDataLocation = UserLocation + Check + 3;
          EEPROMData = EEPROM_Read( EEPROMDataLocation + 7);
          EEPROM_Write(EEPROMDataLocation, EEPROMData );
        }
      }
    }
    if (PerfectMatch == 1)
    {
      NumberOfUsers--;
      EEPROM_Write(100, NumberOfUsers);
    }

  }

  else
  {
    /*print on LCD There is no any users yet*/
	  Lcd_vidDisplayStr("No users yet");

  }

}

u8 AdminLogin (u8* ID, u8* Password)
{
  Lcd_vidCmd(_LCD_CLEAR);
  u8 ByteAddress = 0, ValidUsername = 0, ValidPassword = 0, Counter = 0, EEPROMData = 0, WrongEntry = 0;
  for (; Counter < 3; Counter++)
  {
    ByteAddress = 101 + Counter;
    EEPROMData = EEPROM_Read( ByteAddress );
    if (ID[Counter] == EEPROMData)
    {
      ValidUsername++;

    }
    else
    {
      /*Do Nothing*/

      //      H_Lcd_WriteNumber(ValidUsername);
      //      _delay_ms(500);
    }
    //  ValidUsername++;
  }

  for (Counter = 0; Counter < 4; Counter++)
  {
    ByteAddress = 101 + Counter + 3;
    EEPROMData = EEPROM_Read(ByteAddress);
    if (Password[Counter] == EEPROMData)
    {
      ValidPassword++;
    }
    else
    {
      /*Do Nothing*/
    }

  }
  if ((ValidUsername == 3) && (ValidPassword == 4))
  {
    /*Print on LCD Login Successful*/
    Lcd_vidDisplayStr("Login Successful");
    Hc05_SendString("Login Successful");
    _delay_ms(500);
  }
  else if ((ValidPassword == 4) && (ValidUsername != 3)  )
  {
    /*Print on LCD invalid Username*/
    Lcd_vidDisplayStr("Invalid Username");
    Hc05_SendString("Invalid Username");
    _delay_ms(500);
    WrongEntry++;
  }
  else if ((ValidUsername == 3) && (ValidPassword != 4))
  {
    /*Print on LCD Invalid Password*/
    Lcd_vidDisplayStr("Invalid Password");
    Hc05_SendString("Invalid Password");
    _delay_ms(500);
    WrongEntry++;
  }
  else if ((ValidUsername != 3) && (ValidPassword != 4))
  {
    Lcd_vidDisplayStr("Invalid Username");
    Lcd_vidRowColumn(1, 0);
    Lcd_vidDisplayStr("Invalid Password");
    _delay_ms(500);
    Hc05_SendString("Invalid Username & Password");
    /*Print on LCD Invalid Username & Invalid Password*/
    WrongEntry++;
  }
  else
  {
    /*Do Nothing*/
  }
  _delay_ms(300);
  Lcd_vidCmd(_LCD_CLEAR);
  _delay_ms(300);
  return WrongEntry;
}

u8 UserLogin (u8* ID, u8* Password)
{
  u8 NumberOfUsers = EEPROM_Read(100);
  u8 UserLocation = 0, ValidUsername = 0, ValidPassword = 0, Counter = 0, EEPROMData = 0, WrongEntry = 0, EEPROMDataLocation = 0;
  if (NumberOfUsers > 0)
  {
    for (; Counter < NumberOfUsers; Counter++)
    {
      ValidPassword = 0;
      ValidUsername = 0;
      UserLocation = Counter * 7;
      u8 Check = 0;

      for (; Check < 3; Check++)
      {
        EEPROMDataLocation = UserLocation + Check;
        EEPROMData = EEPROM_Read((EEPROMDataLocation));
        if (ID[Check] == EEPROMData)
        {
          ValidUsername++;
        }

      }

      for (Check = 0; Check < 4; Check++)
      {
        EEPROMDataLocation = UserLocation + Check + 3;
        EEPROMData = EEPROM_Read( (EEPROMDataLocation));
        if (Password[Check] == EEPROMData)
        {
          ValidPassword++;
        }

      }

      if (ValidUsername == 3 && ValidPassword == 4)
      {
        break;
      }
      else
      {
        ValidUsername = 0;
        ValidPassword = 0;
      }
    }
    if (ValidUsername == 3 && ValidPassword == 4)
    {
      /*print on LCD Login Successful*/
      Lcd_vidDisplayStr("Login Successful");
      Hc05_SendString("Login Successful");
    }
    else
    {
      /*print on LCD Invalid Username Or Password*/
      Lcd_vidCmd(_LCD_CLEAR);
      Lcd_vidDisplayStr("Invalid Username");
      Lcd_vidRowColumn(1, 0);
      Lcd_vidDisplayStr("Or Password");
      Hc05_SendString("Invalid Username Or Password");
      _delay_ms(1000);
      WrongEntry++;

    }
  }
  else
  {
    /*print on LCD There is no users added yet*/
	Lcd_vidCmd(_LCD_CLEAR);
    Lcd_vidDisplayStr("There is no users");
    Lcd_vidRowColumn(1, 0);
    Lcd_vidDisplayStr("added yet");
    Hc05_SendString("There is no users added yet");
    _delay_ms(1000);
    WrongEntry = 2;
  }
  return WrongEntry;
}

/************************************************************************/
/*Parameters input array to save in it the input from keypad      */
/*for the ID                              */
/************************************************************************/
void InputID (u8* ID, u8 Mode)
{
  u8  DigitsEntered = 0, KeyPressed = 0 , BluetoothData = 0;
  switch (Mode)
  {
    case AdminMode:
      Lcd_vidCmd(_LCD_CLEAR);
      Lcd_vidRowColumn(0, 0);
      Lcd_vidDisplayStr("Enter User ID");
      Lcd_vidRowColumn(1, 0);
      while (DigitsEntered < 3)
      {
        BluetoothData = Hc05_Rec();
        if (BluetoothData)
        {
          ID[DigitsEntered] = BluetoothData;
          Lcd_vidDisplayChar(ID[DigitsEntered]);
          DigitsEntered++;
        }
      }
      _delay_ms(50);
      break;

    case UserMode:
      Lcd_vidRowColumn(1, 0);
      while (DigitsEntered < 3)
      {
        KeyPressed = Keypad_getChar();
        if (KeyPressed)
        {
          ID[DigitsEntered] = KeyPressed;
          /*Print on LCD Numbers Entered*/
          Lcd_vidDisplayChar(ID[DigitsEntered]);
          DigitsEntered++;
        }
      }
      _delay_ms(300);
      break;

    default:      break;
  }
}

/************************************************************************/
/*Parameters input array to save in it the input from keypad      */
/*for the password                            */
/************************************************************************/
void InputPassword (u8* Password, u8 Mode)
{
  u8 BluetoothData = 0, DigitsEntered = 0, KeyPressed = 0;
  switch (Mode)
  {
    case AdminMode:
      Lcd_vidCmd(_LCD_CLEAR);
      Lcd_vidRowColumn(0, 0);
      Lcd_vidDisplayStr("Enter Password");
      Lcd_vidRowColumn(1, 0);
      while (DigitsEntered < 4)
      {
        BluetoothData = Hc05_Rec();
        if (BluetoothData)
        {
          Password[DigitsEntered] = BluetoothData;
          Lcd_vidDisplayChar('*');
          DigitsEntered++;
        }
      }
      _delay_ms(50);
      break;

    case UserMode:
      Lcd_vidRowColumn(1, 0);
      while (DigitsEntered < 4)
      {
        KeyPressed = Keypad_getChar();
        if (KeyPressed)
        {
          Password[DigitsEntered] = KeyPressed;
          /*Print on LCD Stars for every character entered*/
          Lcd_vidDisplayChar('*');
          DigitsEntered++;
        }
      }
      _delay_ms(300);
  }

}


void RelaySwitch(u8* RelayOpened)
{
  if (*RelayOpened == 0)
  {
	Lcd_vidCmd(_LCD_CLEAR);
    Lcd_vidRowColumn(0, 0);
    Lcd_vidDisplayStr("LAMPS Is ON");
    Hc05_SendString("LAMPS Is ON");
    Relay_On();
    *RelayOpened = 1;
  }
  else if (*RelayOpened == 1)
  {
	Lcd_vidCmd(_LCD_CLEAR);
    Lcd_vidRowColumn(0, 0);
    Lcd_vidDisplayStr("LAMPS Is OFF");
    Hc05_SendString("LAMPS Is OFF");
    Relay_Off();
    *RelayOpened = 0;
  }
}

void ACSwitch (u8* ACOpened)
{
    if (*ACOpened == 0)
    {
     u16 Temperature = 0;
     Temperature = Lm35_u8TempRead();
     if (Temperature > 26)
     {
    	 Dc_Motor_vidStart(DIR_CW);
     }
     else if (Temperature < 21)
     {
    	 Dc_Motor_vidStop();
     }
     
     *ACOpened = 1;
     
 }
 else
 {
	 Dc_Motor_vidStop();
	 Led_vidledOff(LED1);
	 Led_vidledOff(LED0);
     *ACOpened = 0;
 }
}

void CheckEEPROM (void)
{
  //char NumberOfUsers = 0;
  //NumberOfUsers = EEPROM_Read(100);
  //Lcd_vidDisplayInt(NumberOfUsers);
  //char counter = NumberOfUsers* 7;
  for (char i = 0; i <= 16; i++)
  {
    Lcd_vidDisplayChar(EEPROM_Read( i));
    //_delay_ms(250);
    //  Lcd_vidCmd(_LCD_CLEAR);
  }
  Lcd_vidRowColumn(1, 0);
  for (char i = 17; i < 33; i++)
  {
    Lcd_vidDisplayChar(EEPROM_Read( i));
    //_delay_ms(250);
    //  Lcd_vidCmd(_LCD_CLEAR);
  }
}


void DeleteAll (void)
{
  for (u16 i = 0; i <= 0xFF; i++)
  {
    EEPROM_Write(i,0xFF);
  }
  EEPROM_Write(0xFF,0xFF);
  EEPROM_Write(100, 0);
}


void AppInit(void)
{
    //Store number of users, initially = 0
    EEPROM_Write( 100,  0);
    
    //Create admin username & pass
    EEPROM_Write( 101, '0');
    EEPROM_Write( 102, '0');
    EEPROM_Write( 103, '1');
    EEPROM_Write( 104, '0');
    EEPROM_Write( 105, '0');
    EEPROM_Write( 106, '0');
    EEPROM_Write( 107, '0');
}

void WelcomingMsg(void)
{
  Lcd_vidCmd(_LCD_CLEAR);
  Lcd_vidDisplayStr("Welcome to Smart");
  Lcd_vidRowColumn(1, 0);
  Lcd_vidDisplayStr("Home Project");
  _delay_ms(2000);
  Lcd_vidCmd(_LCD_CLEAR);
  Hc05_SendString("Welcome to Smart Home Project");
}

/*void CloseTheDoor(void)
{
  H_Servo_SetAngel(0);
  Relay_Off();
}*/


void CheckAC(u8 ACState)
{
  if (ACState == 1)
  {
      u16 Temperature = 0;
      Temperature = Lm35_u8TempRead();
      if (Temperature >= 28)
      {
    	  Dc_Motor_vidStart(DIR_CW);
      }
      else if (Temperature < 21)
      {
    	  Led_vidledOn(LED1);
    	  Led_vidledOff(LED0);
    	  Dc_Motor_vidStop();
      }
      Lcd_vidCmd(_LCD_CLEAR);
      Lcd_vidDisplayStr("AC Opened");
      Hc05_SendString("AC Opened");
  }
  else
  {
	  Dc_Motor_vidStop();
	  Lcd_vidCmd(_LCD_CLEAR);
      Lcd_vidDisplayStr("AC Closed");
      Hc05_SendString("AC Closed");
  }
}

void CheckRelay(u8 RelayState)
{
  if (RelayState == 1)
  {
    Lcd_vidDisplayStr(" Relay On");
    Hc05_SendString(" Relay On");
    Relay_On();
  }
  else if (RelayState == 0)
  {
    Lcd_vidDisplayStr(" Relay Off");
    Hc05_SendString(" Relay Off");
    Relay_Off();
  }
}


void Reset(u8* ACState, Door_State_t* DoorState, u8* RelayState)
{
  *ACState = 0;
  *DoorState = CLOSED;
  *RelayState = 0;
  Dc_Motor_vidStop();
  ServoMotor_VidCloseDoor();
  Relay_Off();
  Hc05_SendString("A/C Off");
  Hc05_SendString("Door is closed");
  Hc05_SendString("Relay Off");
  Hc05_SendString("Resetting  the system...");
  DeleteAll();
  AppInit();
}


