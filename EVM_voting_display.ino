//code for display Board Arduino

#include <LiquidCrystal.h>
#include <Wire.h>
int x = 0;
int c = 0;

char cp1, cp2, cp3, cp4, cvp1, cvp2, cvp3, cvp4, cgs1, cgs2, cgs3, cgs4, cjs1, cjs2, cjs3, cjs4, pass;
String candidatep1 = "Rohit";
String candidatep2 = "Ram";
String candidatep3 = "Rohan";
String candidatep4 = "geeta";

String candidatevp1 = "Reena";
String candidatevp2 = "Var";
String candidatevp3 = "Sam";
String candidatevp4 = "Soham";

String candidategs1 = "Somya";
String candidategs2 = "Samar";
String candidategs3 = "Easter";
String candidategs4 = "Norther";

String candidatejs1 = "Ram";
String candidatejs2 = "Rahil";
String candidatejs3 = "Himani";
String candidatejs4 = "Monika";
String password;

int person1 = 0;
int person2 = 0;
int person3 = 0;
int person4 = 0;

int person5 = 0;
int person6 = 0;
int person7 = 0;
int person8 = 0;

int person9 = 0;
int person10 = 0;
int person11 = 0;
int person12 = 0;

int person13 = 0;
int person14 = 0;
int person15 = 0;
int person16 = 0;

const int en1 = 2;
const int en2 = 3;
const int en3 = 4;
const int en4 = 5;
const int en5 = 6;

LiquidCrystal lcd1(12, en1, 8, 9, 10, 11);
LiquidCrystal lcd2(12, en2, 8, 9, 10, 11);
LiquidCrystal lcd3(12, en3, 8, 9, 10, 11);
LiquidCrystal lcd4(12, en4, 8, 9, 10, 11);
LiquidCrystal lcd5(12, en5, 8, 9, 10, 11);

void setup()
{
  pinMode(7,OUTPUT);
  digitalWrite(7,HIGH);
  Serial.begin(11500);
  lcd1.begin(16, 2);
  lcd2.begin(16, 2);
  lcd3.begin(16, 2);
  lcd4.begin(16, 2);
  lcd5.begin(16, 2);

  Wire.begin(9);//Start the I2C bus as Slave on address9
  Wire.onReceive(receiveEvent);
}

void receiveEvent(int a)
{
  x = Wire.read();
  if (x == 1)
  {
    lcd1.setCursor(0, 0);
    lcd1.print("your vote has");
    lcd1.setCursor(0, 1);
    lcd1.print("been RECORDED");

    lcd2.setCursor(0, 0);
    lcd2.print("your vote has");
    lcd2.setCursor(0, 1);
    lcd2.print("been RECORDED");
    Serial.print("Your Vote has been Recorded.");
    c = 1;
  }

  if (x == 2)
  {
    lcd3.setCursor(0, 0);
    lcd3.print("your vote has");
    lcd3.setCursor(0, 1);
    lcd3.print("been RECORDED");

    lcd4.setCursor(0, 0);
    lcd4.print("your vote has");
    lcd4.setCursor(0, 1);
    lcd4.print("been RECORDED");

    c = 2;
  }

  if (x == 3)
  {
    person1 = Wire.read();
    person2 = Wire.read();
    person3 = Wire.read();
    person4 = Wire.read();
    person5 = Wire.read();
    person6 = Wire.read();
    person7 = Wire.read();
    person8 = Wire.read();

    person9 = Wire.read();
    person10 = Wire.read();
    person11 = Wire.read();
    person12 = Wire.read();
    person13 = Wire.read();
    person14 = Wire.read();
    person15 = Wire.read();
    person16 = Wire.read();
    c = 3;
  }
  if (x == 5) {
    candidatep1 = "";
    while (0 < Wire.available()) {
      cp1 = Wire.read();
      candidatep1 = candidatep1 + String(cp1);
    }
  }
  if (x == 6) {
    candidatep2 = "";
    while (0 < Wire.available()) {
      cp2 = Wire.read();
      candidatep2 = candidatep2 + String(cp2);
    }
  }

  if (x == 7) {
    candidatep3 = "";
    while (0 < Wire.available()) {
      cp3 = Wire.read();
      candidatep3 = candidatep3 + String(cp3);
    }
  }

  if (x == 8) {
    candidatep4 = "";
    while (0 < Wire.available()) {
      cp4 = Wire.read();
      candidatep4 = candidatep4 + String(cp4);
    }
  }
  if (x == 9) {
    candidatevp1 = "";
    while (0 < Wire.available()) {
      cvp1 = Wire.read();
      candidatevp1 = candidatevp1 + String(cvp1);
    }
  }

  if (x == 10) {
    candidatevp2 = "";
    while (0 < Wire.available()) {
      cvp2 = Wire.read();
      candidatevp2 = candidatevp2 + String(cvp2);
    }
  }

  if (x == 11) {
    candidatevp3 = "";
    while (0 < Wire.available()) {
      cvp3 = Wire.read();
      candidatevp3 = candidatevp3 + String(cvp3);
    }
  }

  if (x == 12) {
    candidatevp4 = "";
    while (0 < Wire.available()) {
      cvp4 = Wire.read();
      candidatevp4 = candidatevp4 + String(cvp4);
    }
  }
  if (x == 13) {
    candidategs1 = "";
    while (0 < Wire.available()) {
      cgs1 = Wire.read();
      candidategs1 = candidategs1 + String(cgs1);
    }
  }
  if (x == 14) {
    candidategs2 = "";
    while (0 < Wire.available()) {
      cgs2 = Wire.read();
      candidategs2 = candidategs2 + String(cgs2);
    }
  }
  if (x == 15) {
    candidategs3 = "";
    while (0 < Wire.available()) {
      cgs3 = Wire.read();
      candidategs3 = candidategs3 + String(cgs3);
    }
  }
  if (x == 16) {
    candidategs4 = "";
    while (0 < Wire.available()) {
      cgs4 = Wire.read();
      candidategs4 = candidategs4 + String(cgs4);
    }
  }
  if (x == 17) {
    candidatejs1 = "";
    while (0 < Wire.available()) {
      cjs1 = Wire.read();
      candidatejs1 = candidatejs1 + String(cjs1);
    }
  }
  if (x == 18) {
    candidatejs2 = "";
    while (0 < Wire.available()) {
      cjs2 = Wire.read();
      candidatejs2 = candidatejs2 + String(cjs2);
    }
  }
  if (x == 19) {
    candidatejs3 = "";
    while (0 < Wire.available()) {
      cjs3 = Wire.read();
      candidatejs3 = candidatejs3 + String(cjs3);
    }
  }
  if (x == 20) {
    candidatejs4 = "";
    while (0 < Wire.available()) {
      cjs4 = Wire.read();
      candidatejs4 = candidatejs4 + String(cjs4);
    }
  }

  if (x == 21) {
    password = "";
    while (0 < Wire.available()) {
      pass = Wire.read();
      password = password + String(pass);
    }
  }

}

void loop()
{
  lcd5.setCursor(7, 0);
  lcd5.print("  WELCOME!!   WELCOME!!  ");
  lcd5.setCursor(0, 1);
  lcd5.print("Vote for President on LEFT Side.");
  while (c == 0) {
    lcd1.setCursor(0, 0);
    lcd1.print(candidatep1);
    lcd1.setCursor(0, 1);
    lcd1.print(candidatep2);

    lcd2.setCursor(0, 0);
    lcd2.print(candidatep3);
    lcd2.setCursor(0, 1);
    lcd2.print(candidatep4);

    lcd3.setCursor(0, 0);
    lcd3.print(candidatevp1);
    lcd3.setCursor(0, 1);
    lcd3.print(candidatevp2);

    lcd4.setCursor(0, 0);
    lcd4.print(candidatevp3);
    lcd4.setCursor(0, 1);
    lcd4.print(candidatevp4);
    
    lcd5.command(0x18);//to move text on lcd in Right side.
    delay(600);
  }


  if (c == 1)
  {
    delay(2000);
    lcd5.clear();
    while (c != 2 ) {
      lcd5.setCursor(7, 0);
      lcd5.print("  WELCOME!!   WELCOME!!    ");
      lcd5.setCursor(0, 1);
      lcd5.print("Vote for Vice President on RIGHT Side.");
      while (c == 1) {
        lcd5.command(0x18);//to move text on lcd in Right side.
        delay(600);
      }
    }
    delay(2000);
    lcd1.clear();
    lcd2.clear();
    lcd3.clear();
    lcd4.clear();
    lcd5.clear();
  }

  if (c == 2)
  {
    c = 0;
    lcd5.setCursor(7, 0);
    lcd5.print("  WELCOME!!   WELCOME!!  ");
    lcd5.setCursor(0, 1);
    lcd5.print("Vote for General Secretary on LEFT Side.");
    while (c == 0) {
      lcd1.setCursor(0, 0);
      lcd1.print(candidategs1);
      lcd1.setCursor(0, 1);
      lcd1.print(candidategs2);

      lcd2.setCursor(0, 0);
      lcd2.print(candidategs3);
      lcd2.setCursor(0, 1);
      lcd2.print(candidategs4);

      lcd3.setCursor(0, 0);
      lcd3.print(candidatejs1);
      lcd3.setCursor(0, 1);
      lcd3.print(candidatejs2);

      lcd4.setCursor(0, 0);
      lcd4.print(candidatejs3);
      lcd4.setCursor(0, 1);
      lcd4.print(candidatejs4);

      lcd5.command(0x18);//to move text on lcd in Right side.
      delay(600);
    }


    if (c == 1)
    {
      delay(2000);
      lcd5.clear();
      lcd5.setCursor(7, 0);
      lcd5.print("  WELCOME!!   WELCOME!!    ");
      lcd5.setCursor(0, 1);
      lcd5.print("Vote for Joint Secretary on RIGHT Side.");
      while (c == 1) {
        lcd5.command(0x18);//to move text on lcd in Right side.
        delay(600);
      }
      delay(2000);
      lcd1.clear();
      lcd2.clear();
      lcd3.clear();
      lcd4.clear();
      lcd5.clear();
      c = 0;
    }
  }

  if (c == 3)
  {
    lcd1.clear();
    lcd2.clear();
    lcd3.clear();
    lcd4.clear();
    lcd5.clear();

    lcd1.setCursor(0, 0);
    lcd1.print("Result OUT!!!");
    lcd2.setCursor(0, 0);
    lcd2.print("Result OUT!!!");
    lcd3.setCursor(0, 0);
    lcd3.print("Result OUT!!!");
    lcd4.setCursor(0, 0);
    lcd4.print("Result OUT!!!");

    while (password) {
      if (password == "varun2023") {
        lcd1.clear();
        lcd2.clear();
        lcd3.clear();
        lcd4.clear();

        lcd1.setCursor(0, 0);
        lcd1.print(candidatep1 + "- " + person1);
        lcd1.setCursor(0, 1);
        lcd1.print(candidatep2 + "- " + person2);
        lcd2.setCursor(0, 0);
        lcd2.print(candidatep3 + "- " + person3);
        lcd2.setCursor(0, 1);
        lcd2.print(candidatep4 + "- " + person4);
        lcd3.setCursor(0, 0);
        lcd3.print(candidatevp1 + "- " + person5);
        lcd3.setCursor(0, 1);
        lcd3.print(candidatevp2 + "- " + person6);
        lcd4.setCursor(0, 0);
        lcd4.print(candidatevp3 + "- " + person7);
        lcd4.setCursor(0, 1);
        lcd4.print(candidatevp4 + "- " + person8);

        lcd5.clear();
        lcd5.setCursor(8, 0);
        lcd5.print("Results for President on LEFT");
        lcd5.setCursor(8, 1);
        lcd5.print("Results for Vise President on RIGHT");
        int i = 0;
        while (i != 50) {
          lcd5.command(0x18);
          delay(600);
          i++;
        }
        delay(1000);
        lcd1.clear();
        lcd2.clear();
        lcd3.clear();
        lcd4.clear();
        lcd5.clear();
        lcd1.setCursor(0, 0);
        lcd1.print(candidategs1 + "- " + person9);
        lcd1.setCursor(0, 1);
        lcd1.print(candidategs2 + "- " + person10);
        lcd2.setCursor(0, 0);
        lcd2.print(candidategs3 + "- " + person11);
        lcd2.setCursor(0, 1);
        lcd2.print(candidategs4 + "- " + person12);
        lcd3.setCursor(0, 0);
        lcd3.print(candidatejs1 + "- " + person13);
        lcd3.setCursor(0, 1);
        lcd3.print(candidatejs2 + "- " + person14);
        lcd4.setCursor(0, 0);
        lcd4.print(candidatejs3 + "- " + person15);
        lcd4.setCursor(0, 1);
        lcd4.print(candidatejs4 + "- " + person16);

        lcd5.clear();
        lcd5.setCursor(8, 0);
        lcd5.print("Results for General Secretary on LEFT");
        lcd5.setCursor(8, 1);
        lcd5.print("Results for Joint Secretary on RIGHT");
        i = 0;
        while (i != 50) {
          lcd5.command(0x18);
          delay(600);
          i++;
        }
        lcd1.clear();
        lcd2.clear();
        lcd3.clear();
        lcd4.clear();
        lcd5.clear();
        delay(1000);
        break;
      }
      else {
        lcd5.setCursor(0, 0);
        lcd5.print("Please enter the");
        lcd5.setCursor(0, 1);
        lcd5.print("CORRECT PASSWORD");
      }
    }
  }
  password = "0";
  c = 0;
}
