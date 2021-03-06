#ifndef _RoomControl_h
#define _RoomControl_h


#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <U8glib.h>
#include <DebugUtils.h>
#include <Button.h>
#include <EventArgs.h>
#include <PubSubClient.h>


#include "RoomControlState.h"
#include "RoomControlStateMachine.h"
#include "RoomControlEventsController.h"


class RoomControl : public RoomControlEventsController {
    public:
        static RoomControl* Instance();
        void loop();
        U8GLIB_SH1106_128X64 *u8g;
        EthernetClient* ethClient;
        PubSubClient* mqttClient;
 
        void changeToState(RoomControlState* s);
        void moveToState(RoomControlState* s);
        void revertState();
        void println(const char* text);
        Button* leftButton;
        Button* rightButton; 
        void onLeftButtonClick(EventArgs* e);
        void onRightButtonClick(EventArgs* e);
        void onLeftButtonDown(EventArgs* e);
        void onRightButtonDown(EventArgs* e);
        void onLeftButtonUp(EventArgs* e);
        void onRightButtonUp(EventArgs* e);
        void reset();
        static void onMQTTMessage(char* topic, byte* payload, unsigned int length);
        bool reconnect();
        void publishCommand(const char* item, const char* payload );
        void publishInitialize();
        void setMQTTState(const char* state);
     
    private:
        RoomControl();
        ~RoomControl();
        char buffer[5][81];
        int line = 0;
        bool previousBothClick = false;
        RoomControlStateMachine* mStateMachine;
        const char* MQTTState;        
};
#endif
