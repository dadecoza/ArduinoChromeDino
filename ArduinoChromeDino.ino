
int step = 13;
int dir = 12;
int ldr = A0;

int mx, cr, lt;

void setup() {
  pinMode(step, OUTPUT);
  pinMode(dir, OUTPUT);
  lt = 1025;
  mx = 1025;
  Serial.begin(9600);
  home();
  calibrate();
  punch();
}

void home() {
  pinMode(dir, LOW);
  for (int i=0; i<30; i++) {
    digitalWrite(step, HIGH);
    delay(30);
    digitalWrite(step, LOW);    
  }
  pinMode(dir, HIGH);
  for (int i=0; i<40 ; i++) {
    digitalWrite(step, HIGH);
    delay(30);
    digitalWrite(step, LOW);    
  }
}

void calibrate() {
  Serial.println("Calibrating LDR...");
  Serial.println(lt);
  for (int i=0; i<512; i++) {
    cr = analogRead(ldr);
    if (cr < lt) {
      lt = cr;
    }
    delay(5);
  }
  lt = lt - 15;
  Serial.print("LDR Threshold: ");
  Serial.println(lt);
}

void punch() {
  pinMode(dir, HIGH);
  for (int i=0; i<30; i++) {
    digitalWrite(step, HIGH);
    delay(2);
    digitalWrite(step, LOW);    
  }
  pinMode(dir, LOW);
  for (int i=0; i<30; i++) {
    digitalWrite(step, HIGH);
    delay(2);
    digitalWrite(step, LOW);    
  }
}

// the loop function runs over and over again forever
void loop()
{ 
  cr = analogRead(ldr);
  if (cr < lt) {
    Serial.println("jump");
    delay(180); 
    punch();
  }
}
