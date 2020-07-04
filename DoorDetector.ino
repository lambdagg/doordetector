/* TONES */

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

/* END TONES */
#define trigPin 9
#define echoPin 8
#define buzzer 2

const double threshold = (0.75*29.1);
const double maxdist = (150*29.1);

long max = 0;
int i = 0;

void(* resetFunc) (void) = 0; //declare reset function @ address 0

void setup() {
  Serial.begin(9600);
  Serial.println("[*] Starting...");
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.println("[*] Playing start tones in 1 second...");
  delay(1000);
  Serial.println("[!] Playing start tones");
  digitalWrite(13, HIGH);
  tone(buzzer, NOTE_DS4);
  delay(125);
  noTone(buzzer);
  delay(10);
  tone(buzzer, NOTE_DS4);
  delay(125);
  noTone(buzzer);
  Serial.println("[*] Couting in .5 second...");
  long values[10];
  delay(500);
  Serial.println("[!] Couting now");
  long value;
  long temp = 0;
  long successcount = 0;
  for(int integer = 0;integer<9;integer++) {
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    value = (pulseIn(echoPin, HIGH))/2;
    if(value <= 0 || value > maxdist) {
      Serial.print("[!] Value #");
      Serial.print(integer);
      Serial.println(" was equal to zero or bigger than maxdist. Skipping it.");
      tone(buzzer, NOTE_DS4);
      delay(125);
      noTone(buzzer);
      delay(10);
      tone(buzzer, NOTE_B3);
      delay(125);
      noTone(buzzer);
      value = 0;
    } else if(integer != 0 && (value > (values[integer-1] + 29.1) || value < (values[integer-1] - 29.1))) {
      Serial.print("[!] Value #");
      Serial.print(integer);
      Serial.print(" was too far from the value #");
      Serial.print(integer-1);
      Serial.println(". Stopping.");
      tone(buzzer, NOTE_FS4);
      delay(125);
      noTone(buzzer);
      delay(10);
      tone(buzzer, NOTE_DS4);
      delay(125);
      noTone(buzzer);
      tone(buzzer, NOTE_B3);
      delay(175);
      noTone(buzzer);
      delay(1000);
      resetFunc();
    } else {
      successcount++;
      temp = temp + value;
    }
    Serial.print("[?] ");
    Serial.print(value/29.1);
    Serial.print(" cm (");
    Serial.print(value);
    Serial.println(")");
    values[integer] = value;
    delay(500);
  }
  if(temp == 0 || successcount == 0) {
      Serial.println("[!] There were no successful calculations. Stopping.");
      tone(buzzer, NOTE_FS4);
      delay(125);
      noTone(buzzer);
      delay(10);
      tone(buzzer, NOTE_DS4);
      delay(125);
      noTone(buzzer);
      tone(buzzer, NOTE_B3);
      delay(175);
      noTone(buzzer);
      delay(1000);
      resetFunc();
  }
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
  max = temp/successcount;
  Serial.print("[!] Max set to ");
  Serial.print(max/29.1);
  Serial.print("cm (threshold +/- ");
  Serial.print(threshold/29.1);
  Serial.println("cm)");
  Serial.println("[*] Loop starting in .25 second");
  delay(250);
  digitalWrite(13, LOW);
  Serial.println("[!] Loop starting");
}

void loop() {
  if(i == 0) {
    digitalWrite(22,LOW);
  }
  long duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2);
  Serial.print("[*] Distance: ");
  Serial.print(distance/29.1);
  Serial.print("cm (");
  Serial.print(distance);
  Serial.println(")");
  if((distance > (max + threshold) || (distance > 0 && distance < (max - threshold))) && distance < maxdist) {
    Serial.println("[!] Max/min distance exceeded");
    digitalWrite(13, HIGH);
    tone(buzzer, NOTE_DS4);
    delay(125);
    noTone(buzzer);
    delay(10);
    tone(buzzer, NOTE_DS4);
    delay(125);
    noTone(buzzer);
    delay(4500);
    digitalWrite(13, LOW);
    delay(500);
  }
  i++;
}
