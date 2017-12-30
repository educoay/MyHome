#include <stdio.h>
#include <string.h>
#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <avr/wdt.h>
#include <DebugUtils.h>
#include <Button.h>
#include <EventArgs.h>
#include <Timer.h>
#include "InitializingState.h"
#include "RoomControl.h"



#define INVALID_VALUE -99

RoomControl::RoomControl() : 	ButtonEventsController(this)
{
	line = 0;
	mStateMachine = new RoomControlStateMachine(this);
	mStateMachine->changeTo(new InitializingState(this));
};

RoomControl* RoomControl::Instance()
{
	static RoomControl instance;

	return &instance;
};


 
void RoomControl::loop() {
	Timer::loop();
	mStateMachine->update();
}


void RoomControl::changeToState(RoomControlState* s){
	mStateMachine->changeTo(s);
}

void RoomControl::moveToState(RoomControlState* s){
	mStateMachine->moveTo(s);	
}

void RoomControl::revertState(){
	mStateMachine->revert();	
}


void RoomControl::println(const char* text){
	INFO_PRINT(text)
	int i;
	u8g->setFont(u8g_font_profont10r);

	if (line==5) {
		for(i=0;i<4;i++){
			memcpy(buffer[i],buffer[i+1],81);
		}
		memcpy(buffer[4],text,81);
	} else {
		memcpy(buffer[line],text,81);
	}
	
	
	u8g->firstPage();  
	do
	{
		for(i=0;i<=line;i++){
			u8g->drawStr(2, (i+1)*12, buffer[i]);
		}
	} while(u8g->nextPage() );

	if (line<5) {
		line++;
	}	
}

void RoomControl::onLeftButtonClick(EventArgs* e){
  	if(this->rightButton->isPushed()) 
  	{
  		DEBUG_PRINT("Both after left Click!!")
		previousBothClick = true;
		onClick(ButtonName::bothButtons); 
	} 
	else if (!previousBothClick) 
	{
 		DEBUG_PRINT("Left Click!!")
		onClick(ButtonName::leftButton); 
  	}
	else
	{
  		DEBUG_PRINT("Previous Both Click!!")
		previousBothClick = false;
	}
}

void RoomControl::onRightButtonClick(EventArgs* e){
  	if(this->leftButton->isPushed()) 
  	{
  		DEBUG_PRINT("Both after right Click!!")
		previousBothClick = true;
		onClick(ButtonName::bothButtons); 
  	} 
  	else if (!previousBothClick) 
  	{
  		DEBUG_PRINT("Right Click!!")
		onClick(ButtonName::rightButton); 
	} 
	else
	{
  		DEBUG_PRINT("Previous Both Click!!")
		previousBothClick = false;
	}

}

void RoomControl::onLeftButtonDown(EventArgs* e){
  cout << "ButtonName: " << ButtonName::leftButton << "\n";
  onDown(ButtonName::leftButton);   
}

void RoomControl::onRightButtonDown(EventArgs* e){
  cout << "ButtonName: " << ButtonName::rightButton  << "\n";
  onDown(ButtonName::rightButton);
}

void RoomControl::onLeftButtonUp(EventArgs* e){
  cout << "ButtonName: " << ButtonName::leftButton << "\n";
  onUp(ButtonName::leftButton);
}

void RoomControl::onRightButtonUp(EventArgs* e){
  cout << "ButtonName: " << ButtonName::rightButton  << "\n";
  onUp(ButtonName::rightButton);
}

void RoomControl::reset(){
	wdt_enable(WDTO_60MS);
	while(1) {}
}