// constants
#define HOLD 0
#define OUT  -1
#define IN   1

// Valve Aliases
const int P[12] = {22, 24, 26, 28, 30, 32, 34, 36, 23, 25, 27, 29};

// I/O Port Aliases
const int CH0[2] = {P[0], P[2]}; // IN, OUT
const int CH1[2] = {P[1], P[3]}; // IN, OUT
const int CH2[2] = {P[4], P[6]}; // IN, OUT
const int CH3[2] = {P[5], P[7]}; // IN, OUT
const int CH4[2] = {P[8], P[10]}; // IN, OUT
const int CH5[2] = {P[9], P[11]}; // IN, OUT

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
control ch0;
control ch1;
control ch2;
control ch3;
control ch4;
control ch5;

void setup() {
  ch0.setID(0);
  ch1.setID(1);
  ch2.setID(2);
  ch3.setID(3);
  ch4.setID(4);
  ch5.setID(5);
}

void loop() {
  ch0.in();
  delay(1000);
  ch0.out();
  delay(1000);
  
  ch1.in();
  delay(1000);
  ch1.out();
  delay(1000);
  
  ch2.in();
  delay(1000);
  ch2.out();
  delay(1000);
  
  ch3.in();
  delay(1000);
  ch3.out();
  delay(1000);
  
  ch4.in();
  delay(1000);
  ch4.out();
  delay(1000);
  
  ch5.in();
  delay(1000);
  ch5.out();
  delay(1000);

  delay(5000);
}
