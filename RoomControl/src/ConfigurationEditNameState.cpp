#include <IconCreate.h>
#include <IconPrevious.h>
#include <IconNext.h>
#include "ConfigurationEditNameState.h"
#include "Configuration.h"

const char * ConfigurationEditNameState::getName()
{
    return "ConfigurationEditNameState";
};

ConfigurationEditNameState::ConfigurationEditNameState(RoomControl*  rc)
	: RoomControlState(rc),
	  titleLabel(0, 0, 128, 16, "Nombre"),
	  menuButtonBar(0, 54, 128, 10),
	  moveLeftIcon(0,0, icon_previous_width, icon_previous_height, icon_previous_bits),
	  moveRightIcon(0,0, icon_next_width, icon_next_height, icon_next_bits),
	  selectIcon(0,0, icon_create_width, icon_create_height, icon_create_bits),	
      nameTextBox(0, 22, 128, 16, 8, &menuButtonBar)
{
	titleLabel.setFont(u8g_font_profont12r);
    titleLabel.setBackColor(1);
    titleLabel.setForeColor(0);
    addChild(&titleLabel);
		  
	nameTextBox.setFont(u8g_font_profont22r);
	nameTextBox.addCharacterRange(65, 90); // A..Z
    addChild(&nameTextBox);
	
	menuButtonBar.setLeftIcon(&moveLeftIcon);
	menuButtonBar.setRightIcon(&moveRightIcon);
	menuButtonBar.setCenterIcon(&selectIcon);
	menuButtonBar.setPadding(2, 0, 2, 0);
	addChild(&menuButtonBar);	  
}

void ConfigurationEditNameState::enter()
{
    RoomControlState::enter();
	char *name= new char[CONFIG_NAME_LENGTH+1];
	Configuration::getName(name);
	nameTextBox.setValue(name);
	delete name;
	draw(_owner->u8g);
};


void ConfigurationEditNameState::exit()
{
	char *newName = new char[CONFIG_NAME_LENGTH+1];
	Configuration::getName(newName);
	nameTextBox.getValue(newName);

    Configuration::setName(newName);
	delete newName;
};

void ConfigurationEditNameState::draw(U8GLIB_SH1106_128X64 *u8g)
{
	u8g->firstPage();  
	do
	{
  		drawChildren(u8g);
	} while(u8g->nextPage());
};

void ConfigurationEditNameState::handleButtonClick(ButtonEventArgs* e){
   RoomControl* rc = (RoomControl*)(e->getSender());
    
    switch(e->getButtonName()) {
        case rightButton:
	        nameTextBox.doRight(rc->u8g);
            break;
        case leftButton:
	        nameTextBox.doLeft(rc->u8g);
            break;
        case bothButtons:
	        nameTextBox.doSelect(rc->u8g);
            break;
    };
};

