#include <SSD1306Wire.h>

#define BOMB_OUT 25
#define LED_COUNT 26
#define UP_BTN 13
#define DOWN_BTN 32
#define ARM_BTN 33

/*
   1=13
   2=32
   3=33
*/

//int claveButton[7] = {13, 13, 32, 32, 13, 32, 33};
int i = -1;
//Clave de desarmado de la bomba en una arreglo
int claveButton[] = {1, 1, 2, 2, 1, 2, 3};
int clavePrueba[] = {0, 0, 0, 0, 0, 0, 0};
int sumador = 0;

int b1 = 0;
int b2 = 0;
int b3 = 0;
int ban = 0;
int var = 0;

// Selecciona uno según tu display.
SSD1306Wire display(0x3c, SDA, SCL, GEOMETRY_64_48);

void setup() {

  Serial.begin(115200);
  pinMode(LED_COUNT, OUTPUT);
  pinMode(BOMB_OUT, OUTPUT);
  pinMode(UP_BTN, INPUT_PULLUP);
  pinMode(DOWN_BTN, INPUT_PULLUP);
  pinMode(ARM_BTN, INPUT_PULLUP);
  display.init();
  display.setContrast(255);
}

void task1() {
  b1 = digitalRead(13);
  b2 = digitalRead(32);
  b3 = digitalRead(33);

  digitalWrite(LED_COUNT, HIGH);
  static uint8_t counter = 20;
  static uint32_t oldTime = 0;
  uint32_t newTime;
  newTime = millis();
  if ((newTime - oldTime) > 1000) {
    oldTime = newTime;

    if (b1 == 0 && counter < 60) {
      counter = counter + 1;
      //Serial.print(counter);
    }

    if (b2 == 0 && counter > 10) {
      counter = counter - 1;
      //Serial.print(counter);
    }

    if (ban == 1) {
      if (b1 == 0) {
        var = 1;
        i = i + 1;
      }
      if (b2 == 0) {
        var = 2;
        i = i + 1;
      }
      if (b3 == 0) {
        var = 3;
        i = i + 1;
      }
      if (i < 7) {
        clavePrueba[i] = var;
      }
      else {
        i = 0;
        // task2(claveButton, clavePrueba);
        Serial.print(task2(claveButton, clavePrueba));
      }
    }
     
    if (b3 == 0 or ban == 1) {
      ban = 1;
      counter = counter - 1;
      //Serial.print(counter);
       
      if (counter % 2 == 0 ) {
        digitalWrite(BOMB_OUT, HIGH);
      }
      else {
        digitalWrite(BOMB_OUT, LOW);
      }
    }

    if (counter == 0) {
      counter = 20;
      ban = 0;
    }
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_16);
    display.clear();
    display.drawString(20, 16, String(counter));
  }
   
  // Serial.println(millis());
  //Serial.println("drawing");
  display.display();
  //Serial.println(millis());
  //Serial.println(b1);
}

boolean task2(int claveButton[], int clavePrueba[]) {

  for (i = 0; i < 7; i++) {
    if (claveButton[i] == clavePrueba[i]) {
      sumador = sumador + 1;
    }
  }
  if (sumador == 7) {
    return true;
  }
  else {
    return false;
  }
}

void loop() {
  task1();
}
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Marzo 6 2022
#include <SSD1306Wire.h>

#define BOMB_OUT 25
#define LED_COUNT 26
#define UP_BTN 13
#define DOWN_BTN 32
#define ARM_BTN 33

void taskSerial();
void taskButtons();
void taskBomb();

// Selecciona uno según tu display.
//SSD1306Wire display(0x3c, SDA, SCL, GEOMETRY_64_48);

//Variables globales

bool evButtons = false;
uint8_t evButtons = 0;

void setup() {
  taskSerial();
  taskButtons();
  taskBomb();
}

void taskSerial() {
  enum class SerialStates {INIT, WAITING_COMMANDS};
  static SerialStates serialStates =  SerialStates::INIT;

  switch (serialStates) {
    case SerialStates::INIT: {
        Serial.begin(115200);
        serialStates = SerialStates::WAITING_COMMANDS;
        break;
      }
    case SerialStates::WAITING_COMMANDS: {
        if (Serial.available() > 0) {
          Serial.read(); 
        }
      }
  }
}

void taskButtons() {

  enum class ButtonsStates {INIT, WAITING_PRESS, WAITING_STABLE, WAITING_RELEASE};
  static ButtonsStates buttonsStates =  ButtonsStates::INIT;
  static uint32_t referenceTime = millis();
  const uint32_t timeOutState = 100; //revisar bien el tiempo 
  //static uint8_t inputPinStableValue; // PENDIENTE

  switch (buttonsStates) {
    case ButtonsStates::INIT: {
        pinMode(UP_BTN, INPUT_PULLUP);
        pinMode(DOWN_BTN, INPUT_PULLUP);
        pinMode(ARM_BTN, INPUT_PULLUP);
        buttonsStates = ButtonsStates::WAITING_PRESS;
        break;
      }
    case ButtonsStates::WAITING_PRESS:{
     
        }
      }
  }
}

void taskBomb(){
  
  static SSD1306Wire display(0x3c, SDA, SCL, GEOMETRY_64_48);
  enum class BombStates{INIT, WAITING_CONFIG, COUNTING, BOMB};
  static BombStates bombStates = BombStates::INIT;
  static uint8_t counter;
  static uint8_t passwordS[7] = {UP_BTN,UP_BTN,DOWN_BTN,DOWN_BTN UP_BTN, DOWN_BTN, ARM_BTN};
  static uint8_t password[3] = {0,0,0,0,0,0,0};
  static uint8_t passwordCount = 0;
  
  display.init();
  display.setContrast(255);
  display.clear();
  static uint8_t counter = 0;
  static uint32_t oldTime = 0;
  uint32_t newTime;
  static int x=10;
  static int y=20;
  }


/*
iif (ppasswordCount == 3) {
bool disarm = true;
for (int i = 0; i < 3; i++) {
if (password[i] != passwordS[i]) {
passwordCount = 0;
disarm = false;
break;
}
}
if (disarm == true) {
bombStates = BombStates :: WAITING_CONFIG;
counter = 20;
display.clear();
display.drawString(10, 20, String("Disarm"));
display.display();
  */
void loop() {
  taskSerial();
  taskButtons();
  taskBomb();
}
