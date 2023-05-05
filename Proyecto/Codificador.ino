int tonePin = 2;
int toneFreq = 1000;
int ledPin = 13;

int dotLength = 150; 

int dashLength = dotLength*3;
int letterSpace = dotLength*3;
int wordSpace = dotLength*7;

bool keyboardText = false;
  
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

char ch;
int i, index;

void setup() 
{
  delay(500);
  pinMode(ledPin, OUTPUT);
  pinMode(tonePin, OUTPUT);
  Serial.begin(9600);
  Serial.println();
  Serial.println("-------------------------------");
  Serial.println("Morse Code encoder");
  Serial.print("dot=");
  Serial.print(dotLength);
  Serial.println("ms");   

  Serial.println();
  Serial.println("-------------------------------");
  Serial.println("Type text and press Enter");
  Serial.println("-------------------------------");
      
 
}

void loop() 
{
  if (Serial.available() > 0)
  {
    if (keyboardText == false) 
    {
      Serial.println();
      Serial.println("-------------------------------");
    }

    keyboardText = true;

    ch = Serial.read();

    if (ch >= 'a' && ch <= 'z')
    { 
      ch = ch-32; 
    }
    
    if (ch >= 'A' && ch <= 'Z')
    {
      Serial.print(ch); 
      Serial.print(" ");
      Serial.println(letters[ch-'A']);
      flashSequence(letters[ch-'A']);
      delay(letterSpace);
    }

    if (ch >= '0' && ch <= '9')
    {
      Serial.print(ch);
      Serial.print(" ");
      Serial.println(numbers[ch-'0']);
      flashSequence(numbers[ch-'0']);
      delay(letterSpace);
    }

    if (ch == ' ')
    {
      Serial.println("_");
      delay(wordSpace);    
    } 

     if (Serial.available() <= 0) 
     {
      Serial.println();
      Serial.println("Enter text:");
      Serial.println("-------------------------------");
      keyboardText = false;
     }
  }
  
        
} 

void flashSequence(char* sequence)
{
  int i = 0;
  while (sequence[i] == '.' || sequence[i] == '-')
  {
    flashDotOrDash(sequence[i]);
    i++;
  }
}

void flashDotOrDash(char dotOrDash)
{
  digitalWrite(ledPin, HIGH);
  tone(tonePin, toneFreq);
  if (dotOrDash == '.')
   { delay(dotLength); }
  else
   { delay(dashLength); }

  digitalWrite(ledPin, LOW);
  noTone(tonePin);
  delay(dotLength); 
}
