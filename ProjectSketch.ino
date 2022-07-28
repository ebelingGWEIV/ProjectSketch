/**
 * @File ProjectSketch.ini
 * @Author George Ebeling
 * @Summary Project for CIS617 - Forensics of an Arduino Uno. Writes a message to flash, EEPROM, and the console. 
 */

#include <EEPROM.h>

/**
 * @Summary Write a string to the EEPROM starting at the location of the offset
 * @param offset The starting location within the EEPROM
 * @param str The string to write to EEPROM
 */
void EEPROM_Write(int offset, const String &str)
{
  byte len = str.length();
  EEPROM.write(offset, len);

  for(int i = 0; i < len; i++)
  {
    EEPROM.write(offset + 1 + i, str[i]);
  }
}

/**
 * @Summary Read from EEPROM and return the first string found
 * @param offset The location for which to begin searching for the string
 * @return The string found wtihin EEPROM
 */
String EEPROM_Read(int offset)
{
  int foundLen = EEPROM.read(offset);
  char str[foundLen + 1];

  for(int i = 0; i < foundLen; i++)
  {
    str[i] = EEPROM.read(offset + 1 + i);
  }
  str[foundLen] = '\0';

  return String(str); //Make a String out of str
}

void setup() {
  // Enable printing to console
  Serial.begin(115200);

  int offset = 0;

  // Write the message to EEPROM
  EEPROM_Write(offset, "The cake is a lie");

  // Read a message from EEPROM
  String message = EEPROM_Read(offset);

  // Show message in console
  Serial.print("Message found: ");
  Serial.println(message);
  
}

void loop() {
  
}
