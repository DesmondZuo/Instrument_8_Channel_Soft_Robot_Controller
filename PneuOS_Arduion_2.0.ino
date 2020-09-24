#include <Nextion.h>
#include <Wire.h>
#include <math.h>

//SoftwareSerial HMISerial(10, 11);

// constants
#define HOLD 0
#define OUT  -1
#define IN   1

// Valve Aliases
const int P[12] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

// I/O Port Aliases
const int CH0[2] = {P[0], P[2]}; // IN, OUT
const int CH1[2] = {P[1], P[3]}; // IN, OUT
const int CH2[2] = {P[4], P[6]}; // IN, OUT
const int CH3[2] = {P[5], P[7]}; // IN, OUT
const int CH4[2] = {P[8], P[10]}; // IN, OUT
const int CH5[2] = {P[9], P[11]}; // IN, OUT

// GUI objects
NexButton ch1_in = NexButton(0, 2, "ch1_in");
NexButton ch1_hold = NexButton(0, 3, "ch1_hold");
NexButton ch1_out = NexButton(0, 4, "ch1_out");

NexButton ch2_in = NexButton(0, 6, "ch2_in");
NexButton ch2_hold = NexButton(0, 7, "ch2_hold");
NexButton ch2_out = NexButton(0, 8, "ch2_out");

NexButton ch3_in = NexButton(0, 10, "ch3_in");
NexButton ch3_hold = NexButton(0, 11, "ch3_hold");
NexButton ch3_out = NexButton(0, 12, "ch3_out");

NexButton ch4_in = NexButton(0, 14, "ch4_in");
NexButton ch4_hold = NexButton(0, 15, "ch4_hold");
NexButton ch4_out = NexButton(0, 16, "ch4_out");

NexButton ch5_in = NexButton(0, 18, "ch5_in");
NexButton ch5_hold = NexButton(0, 19, "ch5_hold");
NexButton ch5_out = NexButton(0, 20, "ch5_out");

NexButton ch6_in = NexButton(0, 22, "ch6_in");
NexButton ch6_hold = NexButton(0, 23, "ch6_hold");
NexButton ch6_out = NexButton(0, 24, "ch6_out");

NexSlider h0 = NexSlider(0, 28, "h0");  // Slider added

// Nextion listen list
NexTouch *nex_listen_list[] = 
{
  &ch1_in,
  &ch1_hold,
  &ch1_out,
  &ch2_in,
  &ch2_hold,
  &ch2_out,
  &ch3_in,
  &ch3_hold,
  &ch3_out,
  &ch4_in,
  &ch4_hold,
  &ch4_out,
  &ch5_in,
  &ch5_hold,
  &ch5_out,
  &ch6_in,
  &ch6_hold,
  &ch6_out,
  &h0,
  NULL
};


// ON/OFF Valve Control Class
class control {
  private:
    int id;
    int dir;
    int OValve[2]; // In, Out

    void actuate() {
      if (dir == IN) {
        digitalWrite(OValve[0], HIGH);
        digitalWrite(OValve[1], LOW);
      } else if (dir == OUT) {
        digitalWrite(OValve[0], LOW);
        digitalWrite(OValve[1], HIGH);
      } else if (dir == HOLD) {
        digitalWrite(OValve[0], LOW);
        digitalWrite(OValve[1], LOW);
      }
    }
  public:
    control() { // default constructor
      id = 0;
      dir = HOLD;
      OValve[0] = 0;
      OValve[1] = 0;
    }
    void in() {
      dir = IN;
      actuate();
    }
    void out() {
      dir = OUT;
      actuate();
    }
    void hold() {
      dir = HOLD;
      actuate();
    }
    void setID (int ID) {
      id = ID;
      if (id == 0) {
        OValve[0] = CH0[0];
        OValve[1] = CH0[1];
      } else if (id == 1) {
        OValve[0] = CH1[0];
        OValve[1] = CH1[1];
      } else if (id == 2) {
        OValve[0] = CH2[0];
        OValve[1] = CH2[1];
      } else if (id == 3) {
        OValve[0] = CH3[0];
        OValve[1] = CH3[1];
      } else if (id == 4) {
        OValve[0] = CH4[0];
        OValve[1] = CH4[1];
      } else if (id == 5) {
        OValve[0] = CH5[0];
        OValve[1] = CH5[1];
      }
      pinMode (OValve[0], OUTPUT);
      pinMode (OValve[1], OUTPUT);
      hold();
    }
};

// Declaration of control objects (channels)
control ch1;
control ch2;
control ch3;
control ch4;
control ch5;
//control ch6;

void CH1_in_callback(void *ptr);
void CH1_hold_callback(void *ptr);
void CH1_out_callback(void *ptr);
void CH2_in_callback(void *ptr);
void CH2_hold_callback(void *ptr);
void CH2_out_callback(void *ptr);
void CH3_in_callback(void *ptr);
void CH3_hold_callback(void *ptr);
void CH3_out_callback(void *ptr);
void CH4_in_callback(void *ptr);
void CH4_hold_callback(void *ptr);
void CH4_out_callback(void *ptr);
void CH5_in_callback(void *ptr);
void CH5_hold_callback(void *ptr);
void CH5_out_callback(void *ptr);
void CH6_in_callback(void *ptr);
void CH6_hold_callback(void *ptr);
void CH6_out_callback(void *ptr);

void h0_PopCallback(void *ptr);

void setup() {
  Serial.begin(9600);
  
  ch1.setID(0);
  ch2.setID(1);
  ch3.setID(2);
  ch4.setID(3);
  ch5.setID(4);
  //ch6.setID(5);
  
  ch1_in.attachPop (CH1_in_callback);
  ch1_hold.attachPop (CH1_hold_callback);
  ch1_out.attachPop (CH1_out_callback);

  ch2_in.attachPop (CH2_in_callback);
  ch2_hold.attachPop (CH2_hold_callback);
  ch2_out.attachPop (CH2_out_callback);

  ch3_in.attachPop (CH3_in_callback);
  ch3_hold.attachPop (CH3_hold_callback);
  ch3_out.attachPop (CH3_out_callback);

  ch4_in.attachPop (CH4_in_callback);
  ch4_hold.attachPop (CH4_hold_callback);
  ch4_out.attachPop (CH4_out_callback);

  ch5_in.attachPop (CH5_in_callback);
  ch5_hold.attachPop (CH5_hold_callback);
  ch5_out.attachPop (CH5_out_callback);

  ch6_in.attachPop (CH6_in_callback);
  ch6_hold.attachPop (CH6_hold_callback);
  ch6_out.attachPop (CH6_out_callback);

  h0.attachPop (h0_PopCallback);

  Serial.print("t6.txt=\"Yes\"");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
  Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  Serial.write(0xff);
  Serial.write(0xff);

  Serial.print("t6.bco=44689");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
  Serial.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  Serial.write(0xff);
  Serial.write(0xff);

  pinMode(10, OUTPUT);
}

void loop() {
  delay(30);
  nexLoop(nex_listen_list);
}

void CH1_in_callback(void *ptr) {
  ch1.in();
}

void CH1_hold_callback(void *ptr) {
  ch1.hold();
}

void CH1_out_callback(void *ptr) {
  ch1.out();
}

void CH2_in_callback(void *ptr) {
  ch2.in();
}

void CH2_hold_callback(void *ptr) {
  ch2.hold();
}

void CH2_out_callback(void *ptr) {
  ch2.out();
}

void CH3_in_callback(void *ptr) {
  ch3.in();
}

void CH3_hold_callback(void *ptr) {
  ch3.hold();
}

void CH3_out_callback(void *ptr) {
  ch3.out();
}

void CH4_in_callback(void *ptr) {
  ch4.in();
}

void CH4_hold_callback(void *ptr) {
  ch4.hold();
}

void CH4_out_callback(void *ptr) {
  ch4.out();
}

void CH5_in_callback(void *ptr) {
  ch5.in();
}

void CH5_hold_callback(void *ptr) {
  ch5.hold();
}

void CH5_out_callback(void *ptr) {
  ch5.out();
}

void CH6_in_callback(void *ptr) {
  //ch6.in();
}

void CH6_hold_callback(void *ptr) {
  //ch6.hold();
}

void CH6_out_callback(void *ptr) {
  //ch6.out();
}

void h0_PopCallback(void *ptr)  // Release event for slider
{
  uint32_t number2 = 0;  // Create variable to store value of slider
  h0.getValue(&number2);  // Read the value of the slider
  
  // I got a problem where sometimes I received a 0 instead of the correct slider value.
  // To fix this I will put a condition that if I get a 0, I am going to read again the slider to make sure I get the real value.
  // I am going to do this a few times because sometimes it takes a few tries to get the correct value.
  // The problem looks like it have something to do with touch events. Everytime the display sends a touch event,
  // we need to wait that data to finish transmiting before we can get another data from the display (in this case
  // we want the slider position). For this reason it's important to use a high serial baud (ideally 115200)
  // so it doesn't have to wait too long for the touch event to finish sending the data.

  // The "Are you sure is 0?" begins:
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  if(number2==0){  // If I got a 0, then recheck:
    h0.getValue(&number2);  // Read the value of the slider
  }
  // The "Are you sure is 0?" ended. At this point, if the slider keep showing as 0, then it really is at 0.
  analogWrite(10, number2 * 2.55);
  
  
}  // End of release event
