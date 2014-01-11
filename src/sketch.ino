#define UD 2
#define LR 4
#define RR 6
int analogValueUD = 0;
int analogValueLR = 0;
boolean digitalValueRR = 0;
int x = 0;

void setup()
{
Serial.begin(9600);
pinMode(UD, OUTPUT);
pinMode(LR, OUTPUT);
pinMode(RR, OUTPUT);
delay(800);
digitalWrite(UD, HIGH);
digitalWrite(LR, HIGH);
digitalWrite(RR, HIGH);
delay(800);
digitalWrite(UD, LOW);
digitalWrite(LR, LOW);
digitalWrite(RR, LOW);
delay(800);
digitalWrite(UD, HIGH);
digitalWrite(LR, HIGH);
digitalWrite(RR, HIGH);
delay(800);
digitalWrite(UD, LOW);
digitalWrite(LR, LOW);
digitalWrite(RR, LOW);
delay(800);
digitalWrite(UD, HIGH);
digitalWrite(LR, HIGH);
digitalWrite(RR, HIGH);
delay(500);
digitalWrite(UD, LOW);
delay(500);
digitalWrite(LR, LOW);
delay(500);
digitalWrite(RR, LOW);
}
void loop()
{
delay(500);
//Serial.print("this ");
//Serial.print("is ");
//Serial.print("a line!\n");
//Serial.print("this shold be the second.");
//Serial.println(" To the third after.");
//Serial.println("yep.");
Serial.print("X is:");
Serial.print(x);
Serial.print("\r");
x++;
}
