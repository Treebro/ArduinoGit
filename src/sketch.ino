#define UD 2
#define LR 4
#define RR 6
#define joyPinX 1
#define joyPinY 2
int x = 1;
int stringComplete = 0;  // whether the string is complete
int joyX = 0;
int joyY = 0;
int baud = 9600;
String inputString = ""; // a string to hold incoming data
boolean monitorOn = false;
/*char *array[5];*/
/*array[0] = "tree";*/
/*array[1] = "fire";*/
/*array[2] = "water";*/
/*array[3] = "electricity";*/
/*array[4] = "rock;"*/
/*array[5] = "fighting";*/
typedef void (* DigitFuncPtr) ();
void tmonitor (void) {
  Serial.println("tmonitor");
}
void tset (void) {
  Serial.println("tset");
}
void tread (void) {
  Serial.println("tread");
}
DigitFuncPtr werd[3] = {tmonitor, tset, tread};

void setup()
{
    Serial.begin(baud);
    inputString.reserve(200);
    Serial.print("Booted\r\n->");
    pinMode(UD, OUTPUT);
    pinMode(LR, OUTPUT);
    pinMode(RR, OUTPUT);
    digitalWrite(UD, HIGH);
    digitalWrite(LR, HIGH);
    digitalWrite(RR, HIGH);
    delay(800);
    digitalWrite(UD, LOW);
    digitalWrite(LR, LOW);
    digitalWrite(RR, LOW);
}

void(* resetFunc)(void) = 0; //Declares reset function at address 0.

/*void Printarray(){*/
  /*Serial.println(array[0]);*/
  /*Serial.println(array[1]);*/
  /*Serial.println(array[2]);*/
  /*Serial.println(array[3]);*/
  /*Serial.println(array[4]);*/
  /*Serial.println(array[5]);*/
/*}*/
void loop()
{
  //Read monitor mode
  if (stringComplete == 0 && monitorOn == true) {
  Serial.print("\r\033[2A\033[K");
  //First monitoring line goes here:
  Serial.print("X:");
  Serial.print(joyX);
  Serial.print("Y:");
  Serial.print(joyY);

  Serial.print("\r\n\033[K");
  //Second monitoring line goes here:

  Serial.print("\r\n");
  Serial.print("\033[2C");
  x++;
  }
  //If command has been completed by either \n or `
  if (stringComplete == 2) {
    Serial.print("\r\n-ok\r\n");
    if (inputString == "run array") {
        Serial.print("Running array." );
        (werd[0])();
        (werd[1])();
        (werd[2])();
    } else
    if (inputString == "monitor on") {
        Serial.print("Monitor on." );
        monitorOn = true;
    } else
    if (inputString == "monitor off") {
        Serial.print("Monitor off." );
        monitorOn = false;
    } else
    if (inputString == "reset board") {
        Serial.print("Resetting board NOW!\r\n");
        delay(100);
        resetFunc();
    } else
    if (inputString == "reset serial") {
      Serial.print("Reset serial now!");
      Serial.end();
      delay(1000);
      Serial.begin(baud);
    } else
    if (inputString == "read pin 4") {
        x = digitalRead(LR);
        Serial.print("pin 4 " );
        Serial.print(x);
    } else
    if (inputString == "set pin 4 low") {
        digitalWrite(LR,LOW);
        Serial.println("pin 4 low");
    } else
    if (inputString == "set pin 6 low") {
        digitalWrite(RR,LOW);
        Serial.println("pin 6 low");
    } else
    if (inputString == "set pin 2 low") {
        digitalWrite(UD,LOW);
        Serial.println("pin 2 low");
    } else
    if (inputString == "set pin 4 high") {
        digitalWrite(LR,HIGH);
        Serial.println("pin 4 high");
    } else
    if (inputString == "set pin 6 high") {
        digitalWrite(RR,HIGH);
        Serial.println("pin 6 high");
    } else
    if (inputString == "set pin 2 high") {
        digitalWrite(UD,HIGH);
        Serial.println("pin 2 high");
    } else {
    Serial.println("iS:" + inputString + ":Not a valid command");
    }
    inputString = "";
    //Reset to monitor mode
    stringComplete = 0;
    Serial.print("\r\n\n\n->");
  }

  //The actual functions of the arduino.
  joyX = analogRead(joyPinX);
  delay(100);
  joyY = analogRead(joyPinY);
}
void serialEvent() {
  while (Serial.available()) {
    stringComplete = 1;
    // get the new byte:
    char inChar = (char)Serial.read();
    Serial.print(inChar);
    // if it isn't \n or backspace or `, add it to the string
    if ((int)inChar != 13 && (int)inChar != 127  && (int)inChar != 102 && (int)inChar != 96) {
        inputString += inChar;
    }
    //Handling backspace
    if ((int)inChar == 127 ) {
        inputString = inputString.substring(0, inputString.length() - 1);
    }
    // if the incoming character is a newline, set a flag. Also for script compatibility, can be `
    if ((int)inChar == 13 || (int)inChar == 96 || (int)inChar == 102) {
      stringComplete = 2;
    }
  }
}
