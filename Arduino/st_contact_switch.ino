/**
 *  Arduino Contact Sensor Monitor 
 *
 *  Author: Christopher Etheridge
 *  Date: 2015-10-16
 */

//*****************************************************************************
#include <SoftwareSerial.h>
#include <SmartThings.h>

//*****************************************************************************
// Pin Definitions
//*****************************************************************************
#define PIN_THING_RX                3
#define PIN_THING_TX                2
#define PIN_RESERVED                6     

#define PIN_OFFICE_CONTACT          4     // input
#define PIN_DININGROOM_CONTACT      5     // input
#define PIN_BEDROOM_CONTACT         7     // input
#define PIN_LIVINGROOM_CONTACT      8     // input
#define PIN_KITCHEN_CONTACT         9     // input
#define PIN_FRONTDOOR_CONTACT       10    // input
#define PIN_BACKDOOR_CONTACT        11    // input
#define PIN_GARAGEDOOR_CONTACT      12    // input

#define OPEN                  1     // HIGH
#define CLOSED                0     // LOW
#define UNKNOWN               2     // --- reset / force update

//*****************************************************************************
// Global Variables
//*****************************************************************************
SmartThingsCallout_t messageCallout;    // call out function forward decalaration
SmartThings smartthing(PIN_THING_RX, PIN_THING_TX, messageCallout);  // constructor

int officeStatus  = UNKNOWN;
int diningRoomStatus = UNKNOWN;
int bedroomStatus = UNKNOWN;
int livingRoomStatus = UNKNOWN;
int kitchenStatus = UNKNOWN;
int frontDoorStatus = UNKNOWN;
int backDoorStatus = UNKNOWN;
int garageDoorStatus = UNKNOWN;

bool isDebugEnabled=true;    // enable or disable debug in this example
int stateLED;           // state to track last set value of LED
int stateNetwork;       // state of the network

//*****************************************************************************
// Logic
//*****************************************************************************

int contactState(int pin)
{
  // LOW  -> closed
  // HIGH -> open
  return (digitalRead(pin) == HIGH)?CLOSED:OPEN;
}

void updateContactStatus()
{
  int currentStatus;
  char* msg = NULL;

  currentStatus = contactState(PIN_OFFICE_CONTACT);
  if (officeStatus != currentStatus)
  {
    officeStatus = currentStatus;
    if(officeStatus == CLOSED) msg = "office closed";
    else                     msg = "office open";

    smartthing.shieldSetLED(0, 2, 0); // green
    smartthing.send(msg);
    if(isDebugEnabled) Serial.println(msg);
    return; // only one message per loop
  }

  currentStatus = contactState(PIN_DININGROOM_CONTACT);
  if (diningRoomStatus != currentStatus)
  {
    diningRoomStatus = currentStatus;
    if(diningRoomStatus == CLOSED) msg = "diningroom closed";
    else                     msg = "diningroom open";

    smartthing.shieldSetLED(0, 2, 0); // green
    smartthing.send(msg);
    if(isDebugEnabled) Serial.println(msg);
    return; // only one message per loop
  }
  
  currentStatus = contactState(PIN_BEDROOM_CONTACT);
  if (bedroomStatus != currentStatus)
  {
    bedroomStatus = currentStatus;
    if(bedroomStatus == CLOSED) msg = "bedroom closed";
    else                     msg = "bedroom open";

    smartthing.shieldSetLED(0, 2, 0); // green
    smartthing.send(msg);
    if(isDebugEnabled) Serial.println(msg);
    return; // only one message per loop
  }
    
  currentStatus = contactState(PIN_LIVINGROOM_CONTACT);
  if (livingRoomStatus != currentStatus)
  {
    livingRoomStatus = currentStatus;
    if(livingRoomStatus == CLOSED) msg = "livingroom closed";
    else                     msg = "livingroom open";

    smartthing.shieldSetLED(0, 2, 0); // green
    smartthing.send(msg);
    if(isDebugEnabled) Serial.println(msg);
    return; // only one message per loop
  }
  
  currentStatus = contactState(PIN_KITCHEN_CONTACT);
  if (kitchenStatus != currentStatus)
  {
    kitchenStatus = currentStatus;
    if(kitchenStatus == CLOSED) msg = "kitchen closed";
    else                     msg = "kitchen open";

    smartthing.shieldSetLED(0, 2, 0); // green
    smartthing.send(msg);
    if(isDebugEnabled) Serial.println(msg);
    return; // only one message per loop
  }
  
  currentStatus = contactState(PIN_FRONTDOOR_CONTACT);
  if (frontDoorStatus != currentStatus)
  {
    frontDoorStatus = currentStatus;
    if(frontDoorStatus == CLOSED) msg = "frontdoor closed";
    else                     msg = "frontdoor open";

    smartthing.shieldSetLED(0, 2, 0); // green
    smartthing.send(msg);
    if(isDebugEnabled) Serial.println(msg);
    return; // only one message per loop
  }
  
  currentStatus = contactState(PIN_BACKDOOR_CONTACT);
  if (backDoorStatus != currentStatus)
  {
    backDoorStatus = currentStatus;
    if(backDoorStatus == CLOSED) msg = "backdoor closed";
    else                     msg = "backdoor open";
    
    smartthing.shieldSetLED(0, 2, 0); // green
    smartthing.send(msg);
    if(isDebugEnabled) Serial.println(msg);
    return; // only one message per loop
  }
  
  currentStatus = contactState(PIN_GARAGEDOOR_CONTACT);
  if (garageDoorStatus != currentStatus)
  {
    garageDoorStatus = currentStatus;
    if(garageDoorStatus == CLOSED) msg = "garagedoor closed";
    else                     msg = "garagedoor open";

    smartthing.shieldSetLED(0, 2, 0); // green
    smartthing.send(msg);
    if(isDebugEnabled) Serial.println(msg);
    return; // only one message per loop
  }
  

}

//*****************************************************************************
void setNetworkStateLED()
{
  SmartThingsNetworkState_t tempState = smartthing.shieldGetLastNetworkState();
  if (tempState != stateNetwork)
  {
    switch (tempState)
    {
      case STATE_NO_NETWORK:
        if (isDebugEnabled) Serial.println("ST Network State is : NO_NETWORK");
          smartthing.shieldSetLED(2, 2, 0); // red
          break;
      case STATE_JOINING:
        if (isDebugEnabled) Serial.println("ST Network State is : JOINING");
          smartthing.shieldSetLED(2, 2, 0); // yellow
          break;
      case STATE_JOINED:
        if (isDebugEnabled) Serial.println("ST Network State is : JOINED");
          smartthing.shieldSetLED(0, 0, 2); // blue

          // force report of current door state
          officeStatus  = UNKNOWN;
          diningRoomStatus = UNKNOWN;
          bedroomStatus = UNKNOWN;
          livingRoomStatus = UNKNOWN;
          kitchenStatus = UNKNOWN;
          frontDoorStatus = UNKNOWN;
          backDoorStatus = UNKNOWN;
          garageDoorStatus = UNKNOWN;
  
          break;
      case STATE_JOINED_NOPARENT:
        if (isDebugEnabled) Serial.println("ST Network State is : JOINED_NOPARENT");
          smartthing.shieldSetLED(2, 0, 2); // purple
          break;
      case STATE_LEAVING:
        if (isDebugEnabled) Serial.println("ST Network State is : LEAVING");
          smartthing.shieldSetLED(2, 2, 0); // yellow
          break;
      default:
      case STATE_UNKNOWN:
        if (isDebugEnabled) Serial.println("ST Network State is : UNKNOWN");
          smartthing.shieldSetLED(2, 0, 0); // red
          break;
    }
    stateNetwork = tempState;
  }
}

//*****************************************************************************
// API Functions    | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
//                  V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V
//*****************************************************************************
void setup()
{
  // setup default state of global variables
  isDebugEnabled = true;
  stateNetwork = STATE_JOINED;  // set to joined to keep state off if off

  // setup hardware pins
  
  pinMode(PIN_OFFICE_CONTACT, INPUT);
  pinMode(PIN_DININGROOM_CONTACT, INPUT);
  pinMode(PIN_BEDROOM_CONTACT, INPUT);
  pinMode(PIN_LIVINGROOM_CONTACT, INPUT);
  pinMode(PIN_KITCHEN_CONTACT, INPUT);
  pinMode(PIN_FRONTDOOR_CONTACT, INPUT);
  pinMode(PIN_BACKDOOR_CONTACT, INPUT);
  pinMode(PIN_GARAGEDOOR_CONTACT, INPUT);

  if(isDebugEnabled)
  { // setup debug serial port
    Serial.begin(9600);         // setup serial with a baud rate of 9600
    Serial.println("Starting up..");  // print out 'setup..' on start
  }

}

//*****************************************************************************
void loop()
{
  // run smartthing logic
  smartthing.run();

  // Check network connections (and send initial states on Join)
  setNetworkStateLED();

  if(stateNetwork == STATE_JOINED)
  {
    // Check the open/closed state of the doors
    updateContactStatus();
  }
}

//*****************************************************************************
void messageCallout(String message)
{
  smartthing.shieldSetLED(2, 2, 2); // white

  // if debug is enabled print out the received message
  if(isDebugEnabled)
  {
    Serial.print("Received message: '");
    Serial.print(message);
    Serial.println("' ");
  }

  if(message.equals("poll"))
  {
    // if asked for polling update then force update by setting all devices to unknown.
    officeStatus  = UNKNOWN;
    diningRoomStatus = UNKNOWN;
    bedroomStatus = UNKNOWN;
    livingRoomStatus = UNKNOWN;
    kitchenStatus = UNKNOWN;
    frontDoorStatus = UNKNOWN;
    backDoorStatus = UNKNOWN;
    garageDoorStatus = UNKNOWN;
  }

  smartthing.shieldSetLED(0, 0, 0); // off
}
