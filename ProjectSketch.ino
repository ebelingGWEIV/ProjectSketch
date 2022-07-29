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

/**
 * @Summary Serial.print all of the EEPROM as its hexidecimal value as a way of showing what currently resides in the EEPROM.
 * @Param offset The starting locatoin for where to begin reading from.
 */
void EEPROM_HexRead(int offset)
{
  byte spot;
  Serial.println("Hex reading of the EEPROM");
  for(int i = offset; i < EEPROM.length(); i++)
  {
    EEPROM.get(i, spot);
    Serial.print(spot, HEX);
    Serial.print(" ");
    if(i % 10 == 0)
      {
        Serial.println("");
      }
  }
}

void setup() {
  // Enable printing to console
  Serial.begin(115200);

  int offset = 0;
  
  // 1) Write the message to EEPROM
  Serial.println("Step 1:");
  Serial.println("Writing to EEPROM");
  delay(100);
  EEPROM_Write(offset, "The cake is a lie");

  // 2) Read a message from EEPROM
  Serial.println("Step 2:");
  String message = EEPROM_Read(offset);

  delay(100);
  
  // Show message in console
  Serial.print("Message found: ");
  Serial.println(message);
  delay(100);
  
  // 3) Display all contents of EEPROM
  Serial.println("Step 3:");
  delay(100);
  EEPROM_HexRead(offset);
}

void loop() { }
