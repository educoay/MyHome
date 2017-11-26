#include <stdio.h>
#include <string.h>
#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <avr/wdt.h>
#define TRACE_LEVEL_DEBUG
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
  DEBUG_PRINT("Left Click!!")
  if(this->rightButton->isPushed()) {
		onClick(ButtonName::bothButtons); 
	} else {
		onClick(ButtonName::leftButton); 
  }
}

void RoomControl::onRightButtonClick(EventArgs* e){
  DEBUG_PRINT("Right Click!!")
  if(this->leftButton->isPushed()) {
		onClick(ButtonName::bothButtons); 
	} else {
		onClick(ButtonName::rightButton); 
  }
}

void RoomControl::onLeftButtonDown(EventArgs* e){
  onDown(ButtonName::leftButton);   
}

void RoomControl::onRightButtonDown(EventArgs* e){
  onDown(ButtonName::rightButton);
}

void RoomControl::onLeftButtonUp(EventArgs* e){
  onUp(ButtonName::leftButton);
}

void RoomControl::onRightButtonUp(EventArgs* e){
  onUp(ButtonName::rightButton);
}

void RoomControl::reset(){
	wdt_enable(WDTO_60MS);
	while(1) {}
}