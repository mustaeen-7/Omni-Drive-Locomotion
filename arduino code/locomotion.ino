#include <PS2X_lib.h>
#define PS2_DAT        53
#define PS2_CMD        51
#define PS2_SEL        49
#define PS2_CLK        47
PS2X ps2x;
bool prg;
int error = 1;
byte type = 0;
byte vibrate = 0;
int LX = 0, LY = 0, b = 0, f = 0, r = 0, l = 0, ef = 0, er = 0, left = 0, right = 0, L2 = 0, R2 = 0, i = 0;
int MotorA = 30, MotorB = 32, p1 = 8, p2 = 9, p3 = 10, p4 = 11;
int quad1 = 0, quad2 = 0, quad3 = 0, quad4 = 0;
int stop_flag = 0, flag = 0;
class TR {
  public:
    int LX = 0, LY = 0, b = 0, f = 0, r = 0, l = 0, ef = 0, er = 0, left = 0, right = 0, L2 = 0, R2 = 0, i = 0;
    int MotorA = 30, MotorB = 32, p1 = 8, p2 = 9, p3 = 10, p4 = 11;
    int quad1 = 0, quad2 = 0, quad3 = 0, quad4 = 0;
    int stop_flag = 0;
    void M110(int g) {
      digitalWrite(30, 1);
      digitalWrite(32, 0);
      analogWrite(p1, g);
    }
    void M101(int g) {
      digitalWrite(30, 0);
      digitalWrite(32, 1);
      analogWrite(p1, g);
    }
    void M210(int g) {
      digitalWrite(34, 1);
      digitalWrite(36, 0);
      analogWrite(p2, g);
    }
    void M201(int g) {
      digitalWrite(34, 0);
      digitalWrite(36, 1);
      analogWrite(p2, g);
    }
    void M310(int g) {
      digitalWrite(38, 1);
      digitalWrite(40, 0);
      analogWrite(p3, g);
    }
    void M301(int g) {
      digitalWrite(38, 0);
      digitalWrite(40, 1);
      analogWrite(p3, g);
    }
    void M410(int g) {
      digitalWrite(42, 1);
      digitalWrite(44, 0);
      analogWrite(p4, g);
    }
    void M401(int g) {
      digitalWrite(42, 0);
      digitalWrite(44, 1);
      analogWrite(p4, g);
    }
    void M1(int x, int y, int z)
    {
      digitalWrite(30, x);
      digitalWrite(32, y);
      analogWrite(p1, z);
    }
    void M2(int x, int y, int z)
    {
      digitalWrite(34, x);
      digitalWrite(36, y);
      analogWrite(p2, z);
    }
    void M3(int x, int y, int z)
    {
      digitalWrite(38, x);
      digitalWrite(40, y);
      analogWrite(p3, z);
    }
    void M4(int x, int y, int z)
    {
      digitalWrite(42, x);
      digitalWrite(44, y);
      analogWrite(p4, z);
    }
    void loco() {
      prg = ps2x.read_gamepad(false, vibrate);
      if (error == 0 and prg == 1)
      {
        ps2x.read_gamepad();
        L2 = ps2x.ButtonPressed(PSB_L2);
        R2 = ps2x.ButtonPressed(PSB_R2);
        LY = ps2x.Analog(PSS_LY);
        LX = ps2x.Analog(PSS_LX);
        left = ps2x.Button(PSB_L1);
        right = ps2x.Button(PSB_R1);
        int a[5] = {255, 127, 63, 31, 0};

        f = map(LY, 125, 0, 0, a[i]);
        f = constrain(f, 0, a[i]);
        b = map(LY, 130, 255, 0, a[i]);
        b = constrain(b, 0, a[i]);
        l = map(LX, 125, 0, 0, a[i]);
        l = constrain(l, 0, a[i]);
        r = map(LX, 130, 255, 0, a[i]);
        r = constrain(r, 0, a[i]);
        if (L2) {
          i = i + 1;
          if (i >= 5) {
            i = 5;
          }
        }
        if (R2) {
          i = i - 1;
          if (i <= 0) {
            i = 0;
          }
        }
        if (f >= 0 and r == 0 and l == 0 and b == 0) {
          stop_flag == 0;
          M110(f);
          M201(f);
          M310(f);
          M401(f);
          if (ps2x.Button(PSB_L1)) {
            M1(0, 1, a[i]);
            M2(0, 1, a[i]);
            M3(1, 0, a[i]);
            M4(1, 0, a[i]);
          }
          else if (ps2x.Button(PSB_R1)) {
            M1(1, 0, a[i]);
            M2(1, 0, a[i]);
            M3(0, 1, a[i]);
            M4(0, 1, a[i]);
          }
        }
        else if (f > 0 and r >= 0 and l <= 0 and b <= 0) {
          stop_flag == 0;
          if (ps2x.Button(PSB_L1)) {
            M1(0, 1, a[i]);
            M2(0, 1, a[i]);
            M3(1, 0, a[i]);
            M4(1, 0, a[i]);
          }
          else if (ps2x.Button(PSB_R1)) {
            M1(1, 0, a[i]);
            M2(1, 0, a[i]);
            M3(0, 1, a[i]);
            M4(0, 1, a[i]);
          }
          else if (f >= r) {
            if (quad1 == 0)
            {
              M1(0, 0, 0);
              M2(0, 0, 0);
              M3(0, 0, 0);
              M4(0, 0, 0);
              delay(150);
              quad1 = 1;
              quad2 = 0;
              quad3 = 0;
              quad4 = 0;
            }
            M110(f);
            M201(f - r);
            M310(f);
            M401(f - r);
          }
          else if (r > f) {
            if (quad1 == 0)
            {
              M1(0, 0, 0);
              M2(0, 0, 0);
              M3(0, 0, 0);
              M4(0, 0, 0);
              delay(150);
              quad1 = 1;
              quad2 = 0;
              quad3 = 0;
              quad4 = 0;
            }
            M110(r);
            M210(r - f);
            M310(r);
            M410(r - f);
          }
        }
        else if (l >= 0 and f == 0 and b == 0 and r == 0) {
          stop_flag == 0;
          M101(l);
          M201(l);
          M301(l);
          M401(l);
          if (ps2x.Button(PSB_L1)) {
            M1(0, 1, a[i]);
            M2(0, 1, a[i]);
            M3(1, 0, a[i]);
            M4(1, 0, a[i]);
          }
          else if (ps2x.Button(PSB_R1)) {
            M1(1, 0, a[i]);
            M2(1, 0, a[i]);
            M3(0, 1, a[i]);
            M4(0, 1, a[i]);
          }
        }
        else if (f >= 0 and l > 0 and b <= 0 and r <= 0) {
          stop_flag == 0;
          if (ps2x.Button(PSB_L1)) {
            M1(0, 1, a[i]);
            M2(0, 1, a[i]);
            M3(1, 0, a[i]);
            M4(1, 0, a[i]);
          }
          else if (ps2x.Button(PSB_R1)) {
            M1(1, 0, a[i]);
            M2(1, 0, a[i]);
            M3(0, 1, a[i]);
            M4(0, 1, a[i]);
          }
          else if (f >= l) {
            if (quad2 == 0)
            {
              M1(0, 0, 0);
              M2(0, 0, 0);
              M3(0, 0, 0);
              M4(0, 0, 0);
              delay(150);
              quad1 = 0;
              quad2 = 1;
              quad3 = 0;
              quad4 = 0;
            }
            M110(f - l);
            M201(f);
            M310(f - l);
            M401(f);
          }
          else if (l > f) {
            if (quad2 == 0)
            {
              M1(0, 0, 0);
              M2(0, 0, 0);
              M3(0, 0, 0);
              M4(0, 0, 0);
              delay(150);
              quad1 = 0;
              quad2 = 1;
              quad3 = 0;
              quad4 = 0;
            }
            M101(l - f);
            M201(l);
            M301(l - f);
            M401(l);
          }
        }
        else if (b >= 0 and f == 0 and l == 0 and r == 0) {
          stop_flag == 0;
          M101(b);
          M210(b);
          M301(b);
          M410(b);
          if (ps2x.Button(PSB_L1)) {
            M1(0, 1, a[i]);
            M2(0, 1, a[i]);
            M3(1, 0, a[i]);
            M4(1, 0, a[i]);
          }
          else if (ps2x.Button(PSB_R1)) {
            M1(1, 0, a[i]);
            M2(1, 0, a[i]);
            M3(0, 1, a[i]);
            M4(0, 1, a[i]);
          }
        }
        else if (b > 0 and r >= 0 and l <= 0 and f <= 0) {
          stop_flag == 0;
          if (ps2x.Button(PSB_L1)) {
            M1(0, 1, a[i]);
            M2(0, 1, a[i]);
            M3(1, 0, a[i]);
            M4(1, 0, a[i]);
          }
          else if (ps2x.Button(PSB_R1)) {
            M1(1, 0, a[i]);
            M2(1, 0, a[i]);
            M3(0, 1, a[i]);
            M4(0, 1, a[i]);
          }
          else if (b >= r) {
            if (quad3 == 0)
            {
              M1(0, 0, 0);
              M2(0, 0, 0);
              M3(0, 0, 0);
              M4(0, 0, 0);
              delay(150);
              quad1 = 0;
              quad2 = 0;
              quad3 = 1;
              quad4 = 0;
            }
            M101(b - r);
            M210(b);
            M301(b - r);
            M410(b);
          }
          else if (r > b) {
            if (quad3 == 0)
            {
              M1(0, 0, 0);
              M2(0, 0, 0);
              M3(0, 0, 0);
              M4(0, 0, 0);
              delay(150);
              quad1 = 0;
              quad2 = 0;
              quad3 = 1;
              quad4 = 0;
            }
            M110(r - b);
            M210(r);
            M310(r - b);
            M410(r);
          }
        }
        else if (r >= 0 and l == 0 and b == 0 and f == 0) {
          stop_flag == 0;
          M110(r);
          M210(r);
          M310(r);
          M410(r);
          if (ps2x.Button(PSB_L1)) {
            M1(0, 1, a[i]);
            M2(0, 1, a[i]);
            M3(1, 0, a[i]);
            M4(1, 0, a[i]);
            //Serial.println("leftt");
          }
          else if (ps2x.Button(PSB_R1)) {
            M1(1, 0, a[i]);
            M2(1, 0, a[i]);
            M3(0, 1, a[i]);
            M4(0, 1, a[i]);
          }
        }
        else if (b >= 0 and l > 0 and r <= 0 and f <= 0) {
          stop_flag == 0;
          if (ps2x.Button(PSB_L1)) {
            M1(0, 1, a[i]);
            M2(0, 1, a[i]);
            M3(1, 0, a[i]);
            M4(1, 0, a[i]);
          }
          else if (ps2x.Button(PSB_R1)) {
            M1(1, 0, a[i]);
            M2(1, 0, a[i]);
            M3(0, 1, a[i]);
            M4(0, 1, a[i]);
          }
          else if (b >= l) {
            if (quad4 == 0)
            {
              M1(0, 0, 0);
              M2(0, 0, 0);
              M3(0, 0, 0);
              M4(0, 0, 0);
              delay(150);
              quad1 = 0;
              quad2 = 0;
              quad3 = 0;
              quad4 = 1;
            }
            M101(b);
            M210(b - l);
            M301(b);
            M410(b - l);
          }
          else if (l > b) {
            if (quad4 == 0)
            {
              M1(0, 0, 0);
              M2(0, 0, 0);
              M3(0, 0, 0);
              M4(0, 0, 0);
              delay(150);
              quad1 = 0;
              quad2 = 0;
              quad3 = 0;
              quad4 = 1;
            }
            M101(l);
            M201(l - b);
            M301(l);
            M401(l - b);
          }
        }
        else if (ps2x.Button(PSB_R1)) {
          M110(a[i]);
          M210(a[i]);
          M310(a[i]);
          M410(a[i]);
        }
        else if (ps2x.Button(PSB_L1)) {
          M101(a[i]);
          M201(a[i]);
          M301(a[i]);
          M401(a[i]);
        }
        else {
          if (stop_flag == 0)
          {
            M1(1, 1, 0);
            M2(1, 1, 0);
            M3(1, 1, 0);
            M4(1, 1, 0);
            delay(150);
            stop_flag = 1;
          }
          else if (stop_flag == 1)
          {
            M1(1, 1, 255);
            M2(1, 1, 255);
            M3(1, 1, 255);
            M4(1, 1, 255);
          }
        }
      }
      else {
        M1(1, 1, 255);
        M2(1, 1, 255);
        M3(1, 1, 255);
        M4(1, 1, 255);
      }
    }

};
TR tr = TR();

void setup() {

  Serial.begin (57600);
  while (error != 0)
    error = ps2x.config_gamepad(47, 51, 49, 53, false, false);
  type = ps2x.readType();
  pinMode(30, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(36, OUTPUT);
  pinMode(34, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(38, OUTPUT);
  pinMode(40, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(42, OUTPUT);
  pinMode(44, OUTPUT);
  pinMode(11, OUTPUT);
  L2 = ps2x.ButtonPressed(PSB_L2);
  R2 = ps2x.ButtonPressed(PSB_R2);
  LY = ps2x.Analog(PSS_LY);
  LX = ps2x.Analog(PSS_LX);
  left = ps2x.Button(PSB_L1);
  right = ps2x.Button(PSB_R1);
}
void loop() {
  prg = ps2x.read_gamepad(false, vibrate);
  if (ps2x.ButtonPressed(PSB_SELECT)) {
    flag++;
    if (flag == 4) {
      flag = 1;
    }
  }
  else if (flag == 1) {
    tr.loco();
  }
}
