/* SimpleArduinoAcquarium 
This code was born while trying to impress my step father, that owns a huge aquarium,
but was lacking a system to automatically control lights timing. Minimum code knowledge required,
and minimum hardware requirement. this is the stripped down version, i am working on a more complex implementation,
but i will always leave this here, because it is easy to use, functional enough, and easily expandable. 
I had this code running for over six months straight on a Nano, and never had any issue.
Using EEPROM it saves the current state of the light, so in case of a power loss, it will restore at the previous state.
Any suggestion, help needed or request has to be directet to the main GitHub project.
https://github.com/Phoenix1o1/SimpleArduinoAcquarium
there is no warranty for this software, but if i were you, i'd trust me.
*/

#include <Wire.h>               // essential libraries needed for the project
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(0x27, 20, 4);

bool stat1;         //boolean status for EEPROM
bool stat2;
bool stat3;
bool stat4;


#define RELAY1  2    //BLU         //those are the pins the relays are connected to           
#define RELAY2  3    //VER                    
#define RELAY3  4    //ROS                    
#define RELAY4  5    //BIA


  int luce1=0;    //BLU           //integers to state wheter to have lights on or off at startup
  int luce2=0;    //VER           //i'd leave them off to prevent flashing on/off. also those ints 
  int luce3=0;    //ROS           //prevent eccessive EEPROM usages
  int luce4=0;    //BIA


//ORE ACCENSIONE
  int ore1on=10; //HOUR            //BLU           //this is where you set times ON
  int min1on=0;  //MINUTES
  int ore2on=10;                   //VER
  int min2on=30;
  int ore3on=11;                   //ROS
  int min3on=0;
  int ore4on=11;                   //BIA
  int min4on=30;

  //ORE SPEGNIMENTO

  int ore1off=23; //BLU                           //this is where you set times OFF
  int min1off=0;
  int ore2off=22; //VER
  int min2off=30; 
  int ore3off=22; //ROS
  int min3off=0;
  int ore4off=18; //BIA
  int min4off=30;

  int x=0;  //count for cycling lcd info printout
  
void setup () {
  
  stat1 = EEPROM.read(0);     //get previous light status from EEPROM
  stat2 = EEPROM.read(1);
  stat3 = EEPROM.read(2);
  stat4 = EEPROM.read(3);


  luce1= stat1;     //assign that status to variables
  luce2= stat2;
  luce3= stat3;
  luce4= stat4;
  
  Wire.begin();   //init LCD and RTC
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

//the following line sets the RTC to the date & time this sketch was compiled if uncommented

      //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
 
 // This line sets the RTC with an explicit date & time, for example to set
 // January 21, 2014 at 3am you would call:
 
      // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0)); 

  
}

void loop () {


  DateTime now = rtc.now();     //read RTC time
  
  
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
  
  if(x==1||x==2){                   //this is just to circle the set times on the screen, you can either set it up manually or delete alltogether
    lcd.setCursor(0,1);
    lcd.print("BLU 10:00 -> 23:00  ");    //edit this line to display correct timings
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
  lcd.print("BLU  VER  ROS  BIA");      //those are reference name for the four channels

  

  lcd.setCursor(0,3);       //this updates both LCD channel status AND the relays status, it goes off
  if(luce1 == 0){           //a second after the set time
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

int hour=now.hour();          //this is the part of the code that does a second-by-second check to decide what to turn ON or OFF
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

    delay(900);             //tweak this to get a screen update every second (100ms execution plus 900ms delay = almost 1 s)
}

