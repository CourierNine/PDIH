#include <LiquidCrystal.h>

int buttonPin = 13;
int ledPin = 8;
int debounceDelay = 30;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int dotLength = 150; 

int dashLength = dotLength*3;
int letterSpace = dotLength*3;
int wordSpace = dotLength*7; 
  
int t1, t2, onTime, gap;
bool newLetter, newWord, letterFound;

char* letters[] = 
{
".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", // A-I
".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", // J-R 
"...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.." // S-Z
};

char* numbers[] = 
{
"-----", ".----", "..---", "...--", "....-", //0-4
".....", "-....", "--...", "---..", "----." //5-9
};

String dashSeq = "";
char keyLetter;
int i, index;

void setup() 
{
  delay(500);
  pinMode(buttonPin, INPUT_PULLUP);
  lcd.begin(16, 2);
  lcd.print("Morse decoder.");
  delay(500);
  lcd.clear();
  
  newLetter = false; 
  newWord = false;  
  keyboardText = false; 
}

void loop() 
{ 
  if (digitalRead(buttonPin) == HIGH ) 
  {
    digitalWrite(ledPin, HIGH);
    newLetter = true; 
    newWord = true;
    t1=millis(); 

    delay(debounceDelay);     
    while (digitalRead(buttonPin) == HIGH )
      {delay(debounceDelay);}
    
     delay(debounceDelay);
    digitalWrite(ledPin, LOW);
       
    t2 = millis();  
    onTime=t2-t1; 
    
    if (onTime <= dotLength*1.5) 
      {dashSeq = dashSeq + ".";} 
    else 
      {dashSeq = dashSeq + "-";}
  }
  
  gap=millis()-t2; 

  if (newLetter == true && gap>=letterSpace)  
  {    
    letterFound = false; 
    for (i=0; i<=25; i++)
    {
      if (dashSeq == letters[i]) 
      {
        keyLetter = i+65;
        letterFound = true;   
        break ;
      }
    }
    if(letterFound == false)
    {
      for (i=0; i<=10; i++)
      {
      if (dashSeq == numbers[i]) 
        {
          keyLetter = i+48;
          letterFound = true;   
          break ;   
        }
      }
    }    

    lcd.print(keyLetter);
    
    if(letterFound == false)
    {
      lcd.print("Error");
    }  
    
    newLetter = false; 
    dashSeq = "";
  }  

  if (newWord == true && gap>=wordSpace*1.5)
    { 
     newWord = false; 
     lcd.print(" ");  
    } 


  if (gap>=wordSpace*4) 
    {
      lcd.clear();
    }      
} 

