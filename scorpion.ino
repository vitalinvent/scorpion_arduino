#include "SoftwareSerial.h"
#include <AFMotor.h> // подключаем библиотеку для шилда

const int deadZone = 5; //deadZone for joystick input
const int DEF_DELAY_MOVING = 10;
int DEF_SPEED_LEFT = 255;
int DEF_SPEED_RIGHT = 255;
String command;
String inpLine;

AF_DCMotor motorLeftFirst(3);   // подключаем мотор к клеммникам M3
AF_DCMotor motorRightFirst(1);  // подключаем мотор к клеммникам M1
AF_DCMotor motorLeftSecond(4);  // подключаем мотор к клеммникам M4
AF_DCMotor motorRightSecond(2); // подключаем мотор к клеммникам M2

SoftwareSerial BTserial(18, 19); // порт RX, порт TX

void setup()
{
  Serial.begin(9600);
  BTserial.begin(9600);                 // По умолчанию 9600 бот.
  motorLeftFirst.setSpeed(DEF_SPEED_LEFT);   // задаем максимальную скорость мотора
  motorLeftSecond.setSpeed(DEF_SPEED_LEFT);  // задаем максимальную скорость мотора
  motorRightFirst.setSpeed(DEF_SPEED_RIGHT);  // задаем максимальную скорость мотора
  motorRightSecond.setSpeed(DEF_SPEED_RIGHT); // задаем максимальную скорость мотора
}

void loop()
{
  char inpComm = BTserial.read();  
  if (isAscii(inpComm)) {
    command +=inpComm;
      if (inpComm == (char)'#')
      {
        String xSpeed = getValue(command, ':', 0);
        String ySpeed = getValue(command, ':', 1);
        String Rotate = getValue(command, ':', 2);
        xSpeed.replace(":","");
        ySpeed.replace(":","");
        Rotate.replace(":","");
        Serial.println("command:"+String(command)+" xSpeed:"+String(xSpeed)+" ySpeed:"+String(ySpeed)+" Rotate:"+String(Rotate));
        if (Rotate.equals("R")){
          rotate(command);
          Serial.println("rotate command:"+command);
        } else{
          move(command);
          Serial.println("move command:"+command);
        }
        command = "";
      }
  }
  if (BTserial.available())
  {
    // Serial.write(inpComm);
  }
  if (Serial.available())
  {
    // BTserial.write(Serial.read());
  }
}


void rotate(String command)
{
//  Serial.println(command);  
  int xSpeed = getValue(command, ':', 0).toInt();
  int ySpeed = getValue(command, ':', 1).toInt();
//  Serial.println("xSpeed:"+String(xSpeed)+"ySpeed:"+String(ySpeed));
  DEF_SPEED_LEFT=-abs(xSpeed);
  DEF_SPEED_RIGHT=-abs(xSpeed);
  if (xSpeed > 0)
  {
    motorLeftFirst.setSpeed(DEF_SPEED_LEFT); 
    motorLeftSecond.setSpeed(DEF_SPEED_LEFT); 
    motorRightFirst.setSpeed(DEF_SPEED_RIGHT);  
    motorRightSecond.setSpeed(DEF_SPEED_RIGHT);
    motorLeftFirst.run(FORWARD);         
    motorLeftSecond.run(FORWARD);        
    motorRightFirst.run(BACKWARD);       
    motorRightSecond.run(BACKWARD);     
  }
  else
  {
//    Serial.println("xSpeed:"+String(xSpeed)+"ySpeed:"+String(ySpeed));
    motorLeftFirst.setSpeed(DEF_SPEED_LEFT);  
    motorLeftSecond.setSpeed(DEF_SPEED_LEFT); 
    motorRightFirst.setSpeed(DEF_SPEED_RIGHT); 
    motorRightSecond.setSpeed(DEF_SPEED_RIGHT);
    motorLeftFirst.run(BACKWARD);         
    motorLeftSecond.run(BACKWARD);     
    motorRightFirst.run(FORWARD);       
    motorRightSecond.run(FORWARD);         
  }
  if ((xSpeed==0) && (ySpeed==0)){
    motorLeftFirst.run(RELEASE);        
    motorLeftSecond.run(RELEASE);       
    motorRightFirst.run(RELEASE);        
    motorRightSecond.run(RELEASE); 
  }
}

void move(String command)
{
//  Serial.println(command);  
  int xSpeed = getValue(command, ':', 0).toInt();
  int ySpeed = getValue(command, ':', 1).toInt();
//  Serial.println("xSpeed:"+String(xSpeed)+"ySpeed:"+String(ySpeed));
  DEF_SPEED_LEFT=-abs(ySpeed);
  DEF_SPEED_RIGHT=-abs(ySpeed);
  if (ySpeed > 0)
  {
    motorLeftFirst.setSpeed(DEF_SPEED_LEFT); 
    motorLeftSecond.setSpeed(DEF_SPEED_LEFT); 
    motorRightFirst.setSpeed(DEF_SPEED_RIGHT);  
    motorRightSecond.setSpeed(DEF_SPEED_RIGHT);
    motorLeftFirst.run(FORWARD);         
    motorLeftSecond.run(FORWARD);        
    motorRightFirst.run(FORWARD);       
    motorRightSecond.run(FORWARD);     
//    delay(DEF_DELAY_MOVING);           
//    motorLeftFirst.run(RELEASE);       
//    motorLeftSecond.run(RELEASE);         
//    motorRightFirst.run(RELEASE);        
//    motorRightSecond.run(RELEASE);      
  }
  else
  {
//    Serial.println("xSpeed:"+String(xSpeed)+"ySpeed:"+String(ySpeed));
    motorLeftFirst.setSpeed(DEF_SPEED_LEFT);  
    motorLeftSecond.setSpeed(DEF_SPEED_LEFT); 
    motorRightFirst.setSpeed(DEF_SPEED_RIGHT); 
    motorRightSecond.setSpeed(DEF_SPEED_RIGHT);
    motorLeftFirst.run(BACKWARD);         
    motorLeftSecond.run(BACKWARD);     
    motorRightFirst.run(BACKWARD);       
    motorRightSecond.run(BACKWARD);      
//    delay(DEF_DELAY_MOVING);           
//    motorLeftFirst.run(RELEASE);        
//    motorLeftSecond.run(RELEASE);       
//    motorRightFirst.run(RELEASE);        
//    motorRightSecond.run(RELEASE);     
  }
  if ((xSpeed==0) && (ySpeed==0)){
    motorLeftFirst.run(RELEASE);        
    motorLeftSecond.run(RELEASE);       
    motorRightFirst.run(RELEASE);        
    motorRightSecond.run(RELEASE); 
  }
}

String getValue(String data, char separator, int index)
{
    int maxIndex = data.length() - 1;
    int j = 0;
    String chunkVal = "";

    for (int i = 0; i <= maxIndex && j <= index; i++)
    {
        chunkVal.concat(data[i]);

        if (data[i] == separator)
        {
            j++;

            if (j > index)
            {
                chunkVal.trim();
                return chunkVal;
            }

            chunkVal = "";
        }
        else if ((i == maxIndex) && (j < index)) {
            chunkVal = "";
            return chunkVal;
        }
    }   
}

// "D:\\dev\\bin\\Arduino\\libraries",
// "C:\\Users\\vital\\AppData\\Local\\Arduino15\\packages\\esp8266\\hardware",
// "C:\\Users\\vital\\Documents\\Arduino\\libraries"
