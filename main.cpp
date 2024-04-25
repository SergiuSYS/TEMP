#include <Arduino.h>
#include <Wire.h>


// definirea adreselor 
#define SHT31_ADDRESS 0x44
#define HDC2080_ADDRESS 0x40

//chemarea functiilor pentru a le rula
void SHT31();
void HDC2080SENSOR();
void print(float Temperature, float Humidity);

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  while (!Serial);
}

void loop()
{
  SHT31();
  delay(2000);
  HDC2080SENSOR();
  delay(2000);
}


// primire temperaturi de la SHT31
void SHT31(){
  Wire.beginTransmission(SHT31_ADDRESS);
  Wire.write(0x2C);
  Wire.write(0x06);
  Wire.endTransmission();

  Wire.requestFrom(SHT31_ADDRESS, 6);
  byte sht31Data[6];
  for (int i = 0; i < 6; i++)
    sht31Data[i] = Wire.read();
  float temperature_sht31 = ((sht31Data[0] << 8) | sht31Data[1]) * 175.0f / 65535.0f - 45.0f;
  float humidity_sht31 = ((sht31Data[3] << 8) | sht31Data[4]) * 100.0f / 65535.0f;

  Serial.println("--------SHT31--------");
  print(temperature_sht31, humidity_sht31);
}


// primire temperaturi de la HDC2080
void HDC2080SENSOR()
{
  Wire.beginTransmission(HDC2080_ADDRESS);
  Wire.write(0x00);
  Wire.endTransmission();
 
  Wire.requestFrom(HDC2080_ADDRESS, 4);
  byte hdcData[4];
  for (int i = 0; i < 4; i++)
    hdcData[i] = Wire.read();

  float temperature_hdc = ((hdcData[1] << 8) | hdcData[0]) * 165.0f / 65535.0f - 40.0f;
  float humidity_hdc = ((hdcData[3] << 8) | hdcData[2]) / 65535.0f * 100.0f;

  Serial.println("--------HDC2080--------");
  print(temperature_hdc, humidity_hdc);
}


// printare temperaturi
void print(float Temperature, float Humidity)
{
  Serial.print(Temperature);
  Serial.println(" °C");
  Serial.print(Humidity);
  Serial.println(" %");
}
