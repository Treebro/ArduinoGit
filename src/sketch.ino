/* Notes
Not currently configured to handle input strings larger than max signed integer. doesn't accept negatives because we have a sentient value to indicate end of string. (poop). Maybe add a negative prefix command later in time.
Integer max in arduino development is 16 bit (min max of 32768)
Should add funcionality of long. but we have floats until then so umm. yeah sure. yayyyyyy. floats are stored in 32bit and are slightly inaccurate, but have much more power. 6-7 digits of precision. This takes a performance hit when calculating in loop.
Should add a define delimiter.
Set initializer so that on start the values stored in input[][] are -1 instead of 0.
make it handle negative integer and float input. shouldn't be too hard. just gotta put the brackets in the right place on the if statements so it accepts hyphens.
*/
#define UD 2
#define LR 4
#define RR 6
#define joyPinX 1
#define joyPinY 2
#define letterCountMax 16
#define wordCountMax 8
int x = 1; //counts loops where Monitor wass called I guess.
int stringComplete = 0;  // whether the string is complete
int wordCount = 0; //stores which word you are currently inputting. Words are delimited by spaces.
int interperetCount = 0; //stores how many legitimate chars were found when starting at end of string.
int letterCount[wordCountMax] = {}; //Stores which letter[of which word] you are on.
char wordType[wordCountMax] = {}; //Saves the type of variable a word is being converted to. Used as an index to determine which array to read from.  Ints are read from intOut[], floats from floatOut[], and char strings will be read from the string. -1 is delim.
int intout[wordCountMax] = {};    //noted above
float floatOut[wordCountMax] = {};//noted above
int joyX; //input from X axis of joystick
int joyY; //input from Y axis of joystick
int baud = 9600;
int input[wordCountMax][letterCountMax]={{}}; //The array of inputs.
/*int input[wordCountMax][letterCountMax]={{0}, {1},{1, 2, 3, 4, 5, 6}};*/
boolean monitorOn = true; //When enabled, shows constant monitor promts of variables stored under monitor() and monitor2() *not implemented yet*
/*char *array[5];*/
/*array[0] = "tree";*/
/*array[1] = "fire";*/
/*array[2] = "water";*/
/*array[3] = "electricity";*/
/*array[4] = "rock;"*/
/*array[5] = "fighting";*/
/* typedef void (* DigitFuncPtr) ();
void tmonitor (void) {
  Serial.println("tmonitor");
}
void tset (void) {
  Serial.println("tset");
}
void tread (void) {
  Serial.println("tread");
}/*
/*DigitFuncPtr werd[3] = {tmonitor, tset, tread};*/
/*char *strs[6] = {"monitor", "set", "read", "system", "test", '\0'};*/
       /* (werd[0])();
        (werd[1])();
        (werd[2])();
        Serial.print(strs[0]);
        Serial.print(strs[1]);
        Serial.print(strs[2]);
        Serial.print(strs[3]);
        Serial.print(strs[4]); */
void setup()
{
    Serial.begin(baud);
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

void loop()
{
  //If command has been completed by either \n or `
  if (stringComplete == 2) {
    Serial.print("\r\n-ok\r\n");
    //This big brick right here takes all the input and crunches it down to a usable output like word 1 = int of 1, word2 is float of 3.14, word 3 is int of 2, word4 is string of "lcd_text"
    //We read it backwards to detect the length that the integer value is going to be.  We input it in decimal with the most important at the start. so we gotta read it backwards with this fucky power of 10 incrememtal crap.
    for (int wordCounti = 0; wordCounti < wordCountMax; wordCounti++) {
      if (input[wordCounti][0] == -1) {
        break;
      }
      for (int letterCounti = letterCountMax - 1; letterCounti >= 0; letterCounti--) {
        if (!(input[wordCounti][letterCounti] == -1)) {
          if (input[wordCounti][letterCounti] >= 48 && input[wordCounti][letterCounti] <= 57 && wordType[wordCounti] == 'i') { //type is set to 'i' upon completion. it is the default starting point. it assumes it is reading an integer until it is proven to be otherwise.
          //do stuff for integer value.
          // int = int + inputbyte * loopcount ^ 10
          //needs a seperate loop counter because of the possible float conversion. maybe not, maybe I can make some magic and have it store where the . is in the next one. but meh.
          //loopcount ++
          } else 
          if ((input[wordCounti][letterCounti] == 46 && wordType[wordCounti] = 'i') || wordType[wordCounti] == 'f') { //if it is a period, and currently set to integer, make it into a float and continue reading.  It only accepts a period when the type is integer so that it doesn't accept two instances of period.
          // do float stuff
            //if its still type i,
            //take current integer, and blast it right into the thing past the decimal.  something like float = currentoutput/(interperetercount^10) which should leave you with .1234 or whatever.
            //reset interperetercount. need to add correct variable on decimal notation addition.
            //erase the integerbyte
            //}
            //float[wordc] = float[wordc] + inputbyte * loopcount ^ 10
            //loopcount++;
            wordType[wordCounti] = 'f'; //lock this as a float unless a char is supplied.
          } else
          {
            //its obviously a charachter.
            //ditch ths for loop and move on to next char. later  we will read directly from input[x][y] because it has the literal string saved there already.
            wordType[wordCounti] = 'c'; //lock this word as char. In every instance if one part is a letter it has to be a string in total. even if it is a typo or whatever and it was supposed to be int. too bad. syntax error.
          }
        }
        Serial.print(input[wordCounti][letterCounti]-48);
        Serial.print(" ");
      }
      Serial.println("");
    }



    //reset all variables and prep for next input.
    for (int wordCounti = 0; wordCounti < wordCountMax; wordCounti++) { //This cleans the entire array of values
      for (int letterCounti = 0; letterCounti < letterCountMax; letterCounti++) {
        input[wordCounti][letterCounti] = -1;
      }
      wordType[wordCounti] = 'i';
    }
    stringComplete = 0; //Reset to default/monitor available mode
    wordCount = 0; //this sets it back to the first word
    for(int wordCounti = 0; wordCounti  < wordCountMax; wordCounti ++)
    letterCount[wordCounti] = 0;//sets all of the letter pointers in all words back to 0
    Serial.print("\r-done\n"); //Provide end message to indicate end out output.
    if (monitorOn == true) {
      Serial.print("\n\n"); //Add the two lines that monitor occupies. If monitor is not active, do not add space.
    }
    Serial.print("\r\n->");
  }


  //Note, make into two functions that take in a variable amount of variables.
  //Read monitor mode
  if (true) { //stringComplete == 0 && monitorOn == true) { //(
  Serial.print("\r\033[3A\033[K"); //returns to start of line, moves up 2 rows, clears line
  //First monitoring line goes here:
  Serial.print("X:");
  Serial.print(joyX);
  Serial.print("Y:");
  Serial.print(joyY);
  //End of first line.
  Serial.print("\r\n\033[K"); // returns to start of next line and clears.
  //Second monitoring line goes here:
  Serial.print("L:");
  Serial.print(letterCount[wordCount]);
  Serial.print("W:");
  Serial.print(wordCount);
  Serial.print("X:");
  Serial.print(x);
  //End of second line.
  Serial.print("\r\n\n\033[2C"); //Set curser to after "->", leave the line for input status.
  }

  //The actual functions of the arduino.
  joyX = analogRead(joyPinX);
  delay(100);
  joyY = analogRead(joyPinY);
  x++;
}



void serialEvent() {
  while (Serial.available()) {
    /*
    ? = 63
    backspace = 127
    enter = 13
    tab = 9
    ` = 96 //alternate return sequence for perl scripts because im a lazy dunderfuck that doesn't want to learn how to send return commands within perl.
    32 = spacebar
    */
    stringComplete = 1; //Disables the monitor from updating. Over ShellInABox and low bandwidth connections it looks pretty messy otherwise.
    int inChar = (int)Serial.read(); //Get the new byte:
    // if the incoming character is a newline, set a flag. Also for script compatibility, can be `
    if (inChar == 13 || inChar == 96) { //|| (int)inChar == 102 <- its f
      stringComplete = 2;
      Serial.print((char)inChar);
    } else
    //Handling backspace
    if (inChar == 127 ) {
      if (letterCount[wordCount] == 0 && wordCount != 0) { //If the current position is the first letter of the xth word, go back a word. We don't need to delete any chars because we don't save spaces.
        wordCount--;
        Serial.print((char)inChar);
      } else
      if (letterCount[wordCount] != 0) { //If the currrent letter is not the 0th position, we shall delete a letter and move the cursor back.
        input[wordCount][letterCount[wordCount] -1] = -1;
        letterCount[wordCount]--;
        Serial.print((char)inChar);
      }
    } else
    /*
    if((int)inChar == 63) {
      Serial.println();
      for(int i = 0; i < 9; i++) {
        if (strstr((char*)inputString, strs[i]) != NULL) {
          Serial.print(strs[i]);
          Serial.print(" ");
        }
        if (strs[i+1] == '\0')
          i = 9;
      }
      Serial.print("\r\n->");
      Serial.print(inputString);
    } else */
    if (inChar == 32) {
      if(wordCount < wordCountMax - 1) { //when wordcount hits 8, it serioudly fucks up lettercount. So we don't let that happen.  Its different than loopcount below because it is not an array that the max reads one shorter on.
        wordCount++;
        Serial.print((char)inChar);
      } else
        Serial.print("\033[1A\r\033[K:Exceeded max wordCount\n");
    } else {
      // if it isn't \n or backspace or `, add it to the string
      if (letterCount[wordCount] < letterCountMax) { //don't overflow max letters. bad stuff happens when we reach out of the array.
        input[wordCount][letterCount[wordCount]] = inChar; //set current editing int to value of input
        letterCount[wordCount]++;
        Serial.print((char)inChar);
      } else {
        Serial.print("\033[1A\r\033[K:Exceeded max lettercount\n");
      }
    }
  }
}
