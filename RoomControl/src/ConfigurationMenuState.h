#ifndef _ConfigurationMenuState_h
#define _ConfigurationMenuState_h


#include "Controls/ControlContainer.h"
#include "Controls/Label.h"
#include "Controls/Icon.h"
#include "Controls/ButtonBar.h"
#include "RoomControl.h"
#include "RoomControlState.h"

#define MENU_OPTION_COUNT 5

class ConfigurationMenuState : public RoomControlState, private ControlContainer
{ 
    private:
      Label titleLabel;  
      Label optionNameLabel;  
      Label optionValueLabel;  
      Icon  moveLeftIcon;
      Icon  moveRightIcon;
      Icon  selectIcon;
      ButtonBar menuButtonBar;
      
      RoomControlStateMachine* mStateMachine;
      
      const char *menuOptions[MENU_OPTION_COUNT];
      int selectedOption;
 
      void changeSelectedOption(U8GLIB_SH1106_128X64 *u8g, int value);
      void drawMenu(U8GLIB_SH1106_128X64 *u8g);

    public:
      ConfigurationMenuState(RoomControl* rc);
      const char * getName();
     
      
    protected:
      void handleButtonClick(ButtonEventArgs* e);
      void onEnter();      
      void onResume();
      void onExecute();
};


#endif