#include <Arduino.h>

#include <HardwareSerial.h>
#define TINY_GSM_MODEM_SIM800
#include <TinyGsmClient.h>
int btn1 = 18;

// objeto de comunicação serial do SIM800L
HardwareSerial SerialGSM(1);

// objeto da bibliteca com as funções GSM
TinyGsm modemGSM(SerialGSM);

const int BAUD_RATE = 9600;

const int RX_PIN = 4, TX_PIN = 2;

//Access point name da Oi
const char *APN = "gprs.oi.com.br";
//Usuario, se não existir deixe em vazio
const char *USER = "oi";
//Password, se não existir deixe em vazio
const char *PASSWORD = "oi";

void setupGSM(){
  SerialGSM.begin(BAUD_RATE, SERIAL_8N1, RX_PIN, TX_PIN, false);
  delay(1000);
  Serial.println(modemGSM.getModemInfo());
  Serial.println("Caminhando");

 if (!modemGSM.restart()){  
  delay(10000);
  ESP.restart();
  return;
 }
}

void call(String number) {
  bool res = modemGSM.callNumber(number);
}

void setup() {
  Serial.begin(BAUD_RATE);
  Serial.println("Starting...");
  setupGSM();
}

void loop() {
  if (digitalRead(btn1) == HIGH){
    Serial.println("EM lIGACAO");
    call("990000000");
    modemGSM.sendSMS("990000000", "OLA ESP32");
  }
}
