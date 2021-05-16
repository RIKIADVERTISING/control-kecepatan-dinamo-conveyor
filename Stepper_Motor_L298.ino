#include <LCD_I2C.h>
LCD_I2C lcd(0x27);

#define potentiometer  A0  //10k potensio
#define bt_F A1 
#define bt_S A2 
#define bt_B A3 

#define in1 11 //Motor  L298 Pin in1 
#define in2 10 //Motor  L298 Pin in2 
#define in3 9  //Motor  L298 Pin in3 
#define in4 8  //Motor  L298 Pin in4

int read_ADC;
int Speed_LCD;
int Speed;
int Step;
int Mode=0;

void setup() { 
  
pinMode(potentiometer, INPUT); 

pinMode(bt_F, INPUT_PULLUP); 
pinMode(bt_S, INPUT_PULLUP); 
pinMode(bt_B, INPUT_PULLUP); 

pinMode(in1, OUTPUT); 
pinMode(in2, OUTPUT); 
pinMode(in3, OUTPUT); 
pinMode(in4, OUTPUT); 
  
lcd.begin(); 
lcd.backlight(); 
lcd.setCursor(0,0);
lcd.print("RIKI ADVERTISING");
lcd.setCursor(0,1);
lcd.print(" MESIN CONVEYOR ");
delay(2000); 
lcd.clear();
}

void loop() { 

read_ADC = analogRead(potentiometer); 
Speed = map(read_ADC, 0, 1023, 100, 0);
Speed_LCD = map(read_ADC, 0, 1023, 0, 100); 


lcd.setCursor(0,0);
lcd.print("   SPEED: ");
lcd.print(Speed_LCD); 
lcd.print("%  ");

if(digitalRead (bt_F) == 0){Mode = 1;} 
if(digitalRead (bt_S) == 0){Mode = 0;} 
if(digitalRead (bt_B) == 0){Mode = 2;} 

lcd.setCursor(0,1);

if(Mode==0){ lcd.print("      STOP      ");}
if(Mode==1){ lcd.print("      MAJU      ");}
if(Mode==2){ lcd.print("     MUNDUR     ");}

if(Speed_LCD>0){
if(Mode==1){  
Step = Step+1;
if(Step>3){Step=0;}    
call_Step(Step);
}

if(Mode==2){
Step = Step-1;
if(Step<0){Step=3;}  
call_Step(Step);
}

delay(Speed);
}  


}



void call_Step(int i){
    switch (i) {
      case 0: 
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
      break;
      case 1:  
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
      break;
      case 2:  
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
      break;
      case 3:  
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
      break;
    }
  }
