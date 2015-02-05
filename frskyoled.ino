#include <FrSky.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

FrSky frsky;

void setup() {
  
  Serial.begin(9600);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Keine ");
  display.setCursor(0,22);
  display.println("FrSky");
  display.setCursor(0,44);
  display.println("Daten!");
  display.display();
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    if (frsky.update(c)) { // frsky_update() returns 1 if a complete packet was successfully decoded, otherwise 0
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(WHITE);
      
      display.setCursor(0,0);
      display.println("TX:");
      display.setCursor(40,0);
      display.println(frsky.getLink_up());
      
      display.setCursor(0,18);
      display.println("RX:");
      display.setCursor(40,18);
      display.println(frsky.getLink_dn());
      
      display.setTextSize(1);
      
      display.setCursor(0,40);
      display.println("A1 Spannung:");
      display.setCursor(72,40);
      display.println(frsky.getRX_a1()*0.0517647058824);
      
      display.setCursor(0,55);
      display.println("A2 Spannung:");
      display.setCursor(72,55);
      display.println(frsky.getRX_a2()*0.0129411764706);
      display.display();
 /* 
      Debug:
      Serial.print("TXRSSI: ");
      Serial.println(frsky.getLink_up());
      Serial.print("Telemetry RSSI: ");
      Serial.println(frsky.getLink_dn());
      Serial.print("RX Voltage: ");
      Serial.println(frsky.getRX_a1()*0.0517647058824); // The internal sensor has a 4:1 divider, so the value is 0-13,2V in 255 steps or 0,052V per step
      Serial.print("A2 Voltage: ");
      Serial.println(frsky.getRX_a2()*0.0129411764706); // A2 without divider is 0-3,3V in 255 steps or 0,013V per step
 */   
  
    }
  }
}
  
