#include <Wire.h>               // essential libraries needed for the project
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(0x27, 20, 4);

bool stat1;
bool stat2;
bool stat3;
bool stat4;


#define RELAY1  2    //BLU                    
#define RELAY2  3    //VER                    
#define RELAY3  4    //ROS                    
#define RELAY4  5    //BIA


  int luce1=0;    //BLU
  int luce2=0;    //VER
  int luce3=0;    //ROS
  int luce4=0;    //BIA


//ORE ACCENSIONE
  int ore1on=10;  //BLU
  int min1on=0;
  int ore2on=10;  //VER
  int min2on=30;
  int ore3on=11;  //ROS
  int min3on=0;
  int ore4on=11;  //BIA
  int min4on=30;

  //ORE SPEGNIMENTO

  int ore1off=23; //BLU
  int min1off=0;
  int ore2off=22; //VER
  int min2off=30; 
  int ore3off=22; //ROS
  int min3off=0;
  int ore4off=18; //BIA
  int min4off=30;

  int x=0;
  
void setup () {
  
  stat1 = EEPROM.read(0);
  stat2 = EEPROM.read(1);
  stat3 = EEPROM.read(2);
  stat4 = EEPROM.read(3);


  luce1= stat1;
  luce2= stat2;
  luce3= stat3;
  luce4= stat4;
  
  Wire.begin();
  lcd.begin();
  lcd.backlight();
  lcd.clear();

  pinMode(RELAY1, OUTPUT);       
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);

  digitalWrite(RELAY1,HIGH);
  digitalWrite(RELAY2,HIGH);
  digitalWrite(RELAY3,HIGH);
  digitalWrite(RELAY4,HIGH);


/*
    // following line sets the RTC to the date & time this sketch was compiled if uncommented

    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
     
     // This line sets the RTC with an explicit date & time, for example to set
     // January 21, 2014 at 3am you would call:
     
     // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0)); 
  */
  
}

void loop () {


  DateTime now = rtc.now();

    //ORE
  //lcd.clear();      //MIGHT CAUSE OR FIX RANDOM FLASHES ON SOME lcd's, TRY TO UNCOMMENT AND SEE HOW THAT GOES
  lcd.setCursor(0,0);
  lcd.print("  :  :      /  /");
  lcd.setCursor(0,0);
  lcd.print(now.hour());
  lcd.setCursor(3,0);
  lcd.print(now.minute());
  lcd.setCursor(6,0);
  lcd.print(now.second());
  lcd.setCursor(10,0);
  lcd.print(now.day());
  lcd.setCursor(13,0);
  lcd.print(now.month());
  lcd.setCursor(16,0);
  lcd.print(now.year());
  
  x=x+1;
  
  if(x==1||x==2){                   //this is just t circle the set times on the screen, you can either set it up manually or delete alltogether
    lcd.setCursor(0,1);
    lcd.print("BLU 10:00 -> 23:00  ");
  }
  if(x==3||x==4){
    lcd.setCursor(0,1);
    lcd.print("VERDE 10:30 -> 22:30");
  }
  if(x==5||x==6){
    lcd.setCursor(0,1);
    lcd.print("ROSSO 11:00 -> 22:00");
  }
  if(x==7||x==8){
    lcd.setCursor(0,1);
    lcd.print("BIANCO 11:30 ->18:30");
  }
  if(x==8){
    x=0;
  }
  

  lcd.setCursor(0,2);
  lcd.print("BLU  VER  ROS  BIA");

  //RELAYS

  lcd.setCursor(0,3);
  if(luce1 == 0){
    lcd.print("OFF");
    EEPROM.update(0,0);
    digitalWrite(RELAY1,HIGH);
  } 
  else{
    lcd.print("ON ");
    EEPROM.update(0,1);
     digitalWrite(RELAY1,LOW);
  }

  lcd.setCursor(5,3);
  if(luce2 == 0){
    lcd.print("OFF");
    EEPROM.update(1,0);
    digitalWrite(RELAY2,HIGH);
  }
  else{
    lcd.print("ON ");
    EEPROM.update(1,1);
    digitalWrite(RELAY2,LOW);
  }

  lcd.setCursor(10,3);
  if(luce3 == 0){
    lcd.print("OFF");
    EEPROM.update(2,0);
    digitalWrite(RELAY3,HIGH);
  }
  else{
    lcd.print("ON ");
    EEPROM.update(2,1);
    digitalWrite(RELAY3,LOW);
  }

  lcd.setCursor(15,3);
  if(luce4 == 0){
    lcd.print("OFF");
    EEPROM.update(3,0);
    digitalWrite(RELAY4,HIGH);
  }
  else{
    lcd.print("ON ");
    EEPROM.update(3,1);
    digitalWrite(RELAY4,LOW);
  }

int hour=now.hour();
int minute=now.minute();

  if(hour==ore1on){
    if(minute==min1on) luce1=1;
  }

  if(hour==ore2on){
    if(minute==min2on) luce2=1;
  }

  if(hour==ore3on){
    if(minute==min3on) luce3=1;
  }

  if(hour==ore4on){
    if(minute==min4on) luce4=1;
  }



   //OFF
  if(hour==ore1off){
    if(minute==min1off) luce1=0;
  }

  if(hour==ore2off){
    if(minute==min2off) luce2=0;
  }

  if(hour==ore3off){
    if(minute==min3off) luce3=0;
  }

  if(hour==ore4off){
    if(minute==min4off) luce4=0;
  }

    delay(900);
}

