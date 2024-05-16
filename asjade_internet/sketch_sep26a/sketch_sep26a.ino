int buttonState = 0;
int buttonPin = 1;

unsigned long previousMillis = 0;
const long interval = 1000;
int yesButtonPin = D1;
int noButtonPin = D2;

void setup() {
  Serial.begin(9600);
  pinMode(yesButtonPin, INPUT);
  pinMode(noButtonPin, INPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
    int buttonState1 = digitalRead(yesButtonPin);
    int buttonState2 = digitalRead(noButtonPin);
    Serial.print("yesButton: ");
    Serial.println(buttonState1);
    Serial.print("noButton: ");
    Serial.println(buttonState2);
    
  }

  
}
