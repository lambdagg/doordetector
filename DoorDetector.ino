/* TONES */

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

/* END TONES */

#define trigPin 5
#define echoPin 4
#define buzzer 2
long max = 0;
int i = 0;
int lastdetection = -1;

void setup() {
  Serial.begin (9600);
  Serial.println("[*] Starting...");
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.println("[*] Playing start tones in 1 second...");
  delay(1000);
  Serial.println("[!] Playing start tones");
  tone(buzzer, NOTE_DS4);
  delay(125);
  noTone(buzzer);
  delay(10);
  tone(buzzer, NOTE_DS4);
  delay(125);
  noTone(buzzer);
  Serial.println("[*] Couting in .5 second...");
  long one,two,three,four,five,six,seven,eight,nine,ten;
  delay(500);
  Serial.println("[!] Couting now");
  one = (pulseIn(echoPin, HIGH)/2) / 29.1;
  Serial.print("[?] ");
  Serial.print(one);
  Serial.println(" cm");
  delay(500);
  two = (pulseIn(echoPin, HIGH)/2) / 29.1;
  Serial.print("[?] ");
  Serial.print(two);
  Serial.println(" cm");
  delay(500);
  three = (pulseIn(echoPin, HIGH)/2) / 29.1;
  Serial.print("[?] ");
  Serial.print(three);
  Serial.println(" cm");
  delay(500);
  four = (pulseIn(echoPin, HIGH)/2) / 29.1;
  Serial.print("[?] ");
  Serial.print(four);
  Serial.println(" cm");
  delay(500);
  five = (pulseIn(echoPin, HIGH)/2) / 29.1;
  Serial.print("[?] ");
  Serial.print(five);
  Serial.println(" cm");
  delay(500);
  six = (pulseIn(echoPin, HIGH)/2) / 29.1;
  Serial.print("[?] ");
  Serial.print(six);
  Serial.println(" cm");
  delay(500);
  seven = (pulseIn(echoPin, HIGH)/2) / 29.1;
  Serial.print("[?] ");
  Serial.print(seven);
  Serial.println(" cm");
  delay(500);
  eight = (pulseIn(echoPin, HIGH)/2) / 29.1;
  Serial.print("[?] ");
  Serial.print(eight);
  Serial.println(" cm");
  delay(500);
  nine = (pulseIn(echoPin, HIGH)/2) / 29.1;
  Serial.print("[?] ");
  Serial.print(nine);
  Serial.println(" cm");
  delay(500);
  ten = (pulseIn(echoPin, HIGH)/2) / 29.1;
  Serial.print("[?] ");
  Serial.print(ten);
  Serial.println(" cm");
  Serial.println("[*] Finished counting. Playing success tones...");
  tone(buzzer, NOTE_B3);
  delay(125);
  noTone(buzzer);
  tone(buzzer, NOTE_DS4);
  delay(125);
  noTone(buzzer);
  tone(buzzer, NOTE_FS4);
  delay(175);
  noTone(buzzer);
  Serial.println("[*] Calculating max distance...");
  max = (one+two+three+four+five+six+seven+eight+nine+ten)/10;
  max = max + 1;
  Serial.print("[!] Max set to ");
  Serial.print(max);
  Serial.println(" cm");
  Serial.println("[*] Loop starting in .25 second");
  delay(250);
  Serial.println("[!] Loop starting");
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  Serial.print("[*] Distance:");
  Serial.println(distance);
  if(distance > max) {
    Serial.println("[!] Detected distance > max");
    if(lastdetection > 5000 || lastdetection < 0) {
      tone(buzzer, NOTE_DS4);
      delay(125);
      noTone(buzzer);
      delay(10);
      tone(buzzer, NOTE_DS4);
      delay(125);
      noTone(buzzer);
    }
    lastdetection = i;
    delay(1000);
  }
  i++;
}
