// v0.3
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <ezTime.h>

#include "ritos.h" // https://github.com/0ingchun/RITOS-lib-Arduino
#include "MyConfig.h"
#include "MyWifi.h"
#include "MyActuator.h"
#include "MyCtrlLogic.h" // 我是: 唱跳Rap篮球高手
#include "MySensors.h"

// 线程任务声明
// 用户交互线程
Ritos taskEncoder;
Ritos taskCheckEncoder; 
Ritos taskButton;
Ritos taskHomeButton;
// 执行器线程
Ritos taskLCD;
Ritos taskFan;
// 获取数据的线程
Ritos taskTimer;
// Ritos taskDHT22;

void setup() {
  Serial.begin(115200);

  /* Initialize Threads for user interaction*/

  // Initialize the pin for encoder
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  pinMode(encoderPinBtn, INPUT_PULLUP);
  // Initialize the pin for HomeBtn
  pinMode(homeBtnPin, INPUT_PULLUP);

  /* Initialize Threads for user interaction*/
  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  // Initialize the Pin of the Fan(NMOS)

  /* Initialize Threads for grabbing datas*/
  // Initilize the sensors
  // dht22.begin();
  // Initilize the WiFi
  InitilizeWiFiNTP();

  delay(100);

  // Create threads

  // Threads for Interaction
  taskEncoder.task(encoderThread);
  taskCheckEncoder.task(CheckEncoderThread);
  taskButton.task(buttonThread);
  taskHomeButton.task(homeBtnThread);
  // Threads for Actuators
  taskLCD.task(LCDThread);
  taskFan.task(FanThread);
  // Threads for grab datas
  taskTimer.task(WorldTimerThread);
  // taskDHT22.task(DHT22Thread);
}

void loop() {
  // Empty, all logic is executed in the thread
}
