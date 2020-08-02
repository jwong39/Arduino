#include <LiquidCrystal.h>
#include <stdio.h>
#include<stdlib.h>
#include <string.h>

const int morseButton = 3;     // the number of the pushbutton pin
const int sendButton = 2;     // the number of the pushbutton pin
int morseState = 0;
int sendState = 0;
char binaryChar;
int i = 0;
int count = 0;
char morseString[4] = {' ',' ',' ',' '};
int Time = -1;
int test = 0;
char theMessage[16] = "               "; // Default message string size 15
char sendingMessage[]= " ";
char readingMessage[]=" ";

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

void setup() {
  pinMode(morseButton, INPUT_PULLUP);
  pinMode(sendButton, INPUT_PULLUP); 
  lcd.begin(16, 2);
  Serial.begin(9600);
}

String newMessage(char input){
  char ch = input;
  strncat(sendingMessage, &ch, 1);
  theMessage[count] = input;
  lcd.setCursor(0,1);
  lcd.print(theMessage);
  count++;
  return theMessage;
}

char decoder(char morseString[4]){
  morseString[4] = '-'; // signal the end of string
  if (strcmp(morseString,"10  -") == 0){newMessage('A');} // print second line function
  else if (strcmp(morseString,"0111-") == 0){newMessage('B');}
  else if (strcmp(morseString,"0101-") == 0){newMessage('C');}
  else if (strcmp(morseString,"011 -") == 0){newMessage('D');}
  else if (strcmp(morseString,"1   -") == 0){newMessage('E');}
  else if (strcmp(morseString,"1101-") == 0){newMessage('F');}
  else if (strcmp(morseString,"001 -") == 0){newMessage('G');}
  else if (strcmp(morseString,"1111-") == 0){newMessage('H');}
  else if (strcmp(morseString,"11  -") == 0){newMessage('I');}
  else if (strcmp(morseString,"1000-") == 0){newMessage('J');}
  else if (strcmp(morseString,"010 -") == 0){newMessage('K');}
  else if (strcmp(morseString,"1011-") == 0){newMessage('L');}
  else if (strcmp(morseString,"00  -") == 0){newMessage('M');}
  else if (strcmp(morseString,"01  -") == 0){newMessage('N');}
  else if (strcmp(morseString,"000 -") == 0){newMessage('O');}
  else if (strcmp(morseString,"1001-") == 0){newMessage('P');}
  else if (strcmp(morseString,"0010-") == 0){newMessage('Q');}
  else if (strcmp(morseString,"101 -") == 0){newMessage('R');}
  else if (strcmp(morseString,"111 -") == 0){newMessage('S');}
  else if (strcmp(morseString,"0   -") == 0){newMessage('T');}
  else if (strcmp(morseString,"110 -") == 0){newMessage('U');}
  else if (strcmp(morseString,"1110-") == 0){newMessage('V');}
  else if (strcmp(morseString,"100 -") == 0){newMessage('W');}
  else if (strcmp(morseString,"0110-") == 0){newMessage('X');}
  else if (strcmp(morseString,"0100-") == 0){newMessage('Y');}
  else if (strcmp(morseString,"0011-") == 0){newMessage('Z');}
  else {lcd.setCursor(0,0);lcd.print("                ");lcd.print("Invalid entry!");}
}


void printMorse(char morseString[4]){ //  This prints the morse code onto LCD screen
  i = i + 1;
  lcd.setCursor(0,0);
  lcd.print("                ");//16
  lcd.setCursor(0,0);
  lcd.print(morseString);
  lcd.setCursor(4,0);
  lcd.print(" ");
  Time = -1;
}


void morsePress(){  //  This lets me press
  morseState = digitalRead(morseButton);
  sendState = digitalRead(sendButton);
  
  if (morseState == HIGH){ // If button pressed, increment time
    Time = Time + 1;
    Serial.println(Time);
    delay(1000);
  }
  if (morseState == LOW && Time == 0 && i <= 4){ //  Input 0
    morseString[i] = '0';
    printMorse(morseString);
  }
  else if (morseState == LOW && Time == 1 && i <= 4){ // Input 1
    morseString[i] = '1';
    printMorse(morseString);
  }
  else if (morseState == LOW && Time >= 2 || i > 4){ //  Send it decoder
    lcd.setCursor(0,0);
    lcd.print("                ");//16
    lcd.print("loading");
    delay(500);
    lcd.print("                ");//16
    decoder(morseString);

    // Clean Up
    Time = -1;
    i = 0;
    int x = 0;
    while (x < 4){
      morseString[x] = ' ';
      x = x + 1;
    }
  }
}


void writeSerial(){ // Writing a message to Serial based on button status
  if(digitalRead(sendButton) == HIGH){
    int i = 0;
    while(i > strlen(sendingMessage)){
      char letter = sendingMessage[i];
      Serial.write(letter);
    }
  }
  else{
    Serial.write("0");
  }
  sendingMessage = " "; //clear the string after sending it
}


void readSerial(){ // Reading a message from the other board through Serial
  buf[0] = Serial.read();
  buf[1] = '\0';

  if(buf[0] == 'A'){char temp = buf[0]; strncat(readingMessage, &temp, 1);}
  else if(buf[0] == 'B'){char temp = buf[0]; strncat(readingMessage, &temp, 1);}
  else if(buf[0] == 'C'){char temp = buf[0]; strncat(readingMessage, &temp, 1);}
  else if(buf[0] == 'D'){char temp = buf[0]; strncat(readingMessage, &temp, 1);}
  else if(buf[0] == 'E'){char temp = buf[0]; strncat(readingMessage, &temp, 1);}
  else if(buf[0] == 'F'){char temp = buf[0]; strncat(readingMessage, &temp, 1);}
  else if(buf[0] == 'G'){char temp = buf[0]; strncat(readingMessage, &temp, 1);}
  else if(buf[0] == 'H'){char temp = buf[0]; strncat(readingMessage, &temp, 1);}
  else if(buf[0] == 'I'){char temp = buf[0]; strncat(readingMessage, &temp, 1);}
  else if(buf[0] == 'J'){char temp = buf[0]; strncat(readingMessage, &temp, 1);}
  else if(buf[0] == 'K'){char temp = buf[0]; strncat(readingMessage, &temp, 1);}
  else if(buf[0] == 'L'){char temp = buf[0]; strncat(readingMessage, &temp, 1);}
  else if(buf[0] == 'M'){char temp = buf[0]; strncat(readingMessage, &temp, 1);}
  else if(buf[0] == 'N'){char temp = buf[0]; strncat(readingMessage, &temp, 1);}
  else if(buf[0] == 'O'){char temp = buf[0]; strncat(readingMessage, &temp, 1);}
  else if(buf[0] == 'P'){char temp = buf[0]; strncat(readingMessage, &temp, 1);}
  else if(buf[0] == 'Q'){char temp = buf[0]; strncat(readingMessage, &temp, 1);}
  else if(buf[0] == 'R'){char temp = buf[0]; strncat(readingMessage, &temp, 1);}
  else if(buf[0] == 'S'){char temp = buf[0]; strncat(readingMessage, &temp, 1);}
  else if(buf[0] == 'T'){char temp = buf[0]; strncat(readingMessage, &temp, 1);}
  else if(buf[0] == 'U'){char temp = buf[0]; strncat(readingMessage, &temp, 1);}
  else if(buf[0] == 'V'){char temp = buf[0]; strncat(readingMessage, &temp, 1);}
  else if(buf[0] == 'W'){char temp = buf[0]; strncat(readingMessage, &temp, 1);}
  else if(buf[0] == 'X'){char temp = buf[0]; strncat(readingMessage, &temp, 1);}
  else if(buf[0] == 'Y'){char temp = buf[0]; strncat(readingMessage, &temp, 1);}
  else if(buf[0] == 'Z'){char temp = buf[0]; strncat(readingMessage, &temp, 1);}
  else if(buf[0] == '0') {//do nothing
  }
}


void loop() { // Main loop
  morsePress();
}


 
