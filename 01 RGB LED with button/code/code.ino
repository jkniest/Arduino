#define RED 7
#define GREEN 8
#define BLUE 9
#define BUTTON 10

bool toggleActive = false;
bool lightOn = false;

int current = RED;
bool isOff = false;
float timer = 0;

int lastFrame = millis();

void setup() {
  Serial.begin(9600);
  
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);

  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, HIGH);

  analogWrite(RED, 0);
  analogWrite(GREEN, 0);
  analogWrite(BLUE, 0);
}

void loop() {
  handleButtonClick();

  if (!lightOn) {
    disableAllLights();
    return;
  }

  int deltaTime = millis() - lastFrame;
  lastFrame = millis();
  
  timer += deltaTime;
  if (timer < 1000) {
    return;
  }

  timer = 0;

  if (!isOff) {
    disableAllLights();
    isOff = true;
    
    return; 
  }

  int target = RED;
  
  switch(current) {
    case RED:
      target = BLUE;
      break;

    case BLUE:
      target = GREEN;
      break;
  }

  analogWrite(current, 0);
  analogWrite(target, 255);

  current = target;
  isOff = false;
}

void handleButtonClick() {
  if (digitalRead(BUTTON) == LOW) {
    if (!toggleActive) {
      toggleActive = true;
    }
  } else if (toggleActive) {
    lightOn = !lightOn;
    toggleActive = false;
  }
}

void disableAllLights() {
  analogWrite(RED, 0);
  analogWrite(BLUE, 0);
  analogWrite(GREEN, 0);
}
