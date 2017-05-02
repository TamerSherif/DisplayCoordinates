#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

const int xPin = A0;     
const int yPin = A1;    
const int btPin = 7;   
LiquidCrystal_I2C lcd(0x27,16,1);

void setup()
{
  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight 
  pinMode(btPin,INPUT); 
  digitalWrite(btPin, HIGH); 
  // Serial.begin(9600); 
}

void loop()
{
  lcd.scrollDisplayLeft(); 
  lcd.print('X');
  lcd.scrollDisplayLeft(); 
  lcd.print(':');
  lcd.setCursor(15,0);
  char *outp = dec_to_ascii(analogRead(xPin));
  for (int positionCounter1 = 0; positionCounter1 < 26; positionCounter1++)
  {
    lcd.scrollDisplayLeft();  //Scrolls the contents of the display one space to the left.
    if (positionCounter1 == 6 || outp[positionCounter1] == '\0')
    {
      lcd.print(' ');
    }
    else
    {
      lcd.print(outp[positionCounter1]);
    }
  }
  free(outp);
  
  delay(500);//delay 100ms
  lcd.clear();
}

char *dec_to_ascii(int inp)
{
  char *outp = (char *) malloc(sizeof(int) * 5);
  int i = 10000;
  int curch = 0;
  while(i != 1)
  {
    int holder = (inp % i)/ (i / 10);
    if (holder)
    {
      outp[curch] = holder + '0';
      curch++;
    }
    i = i / 10;
  }
  if (curch == 0)
  {
    outp[0] = '0';
    curch++;
  }
  outp[curch] = '\0';
  return outp;
}

