/* 
 * Project Argon-to-Lora
 * Author: Nathan Rosenberger
 * Date: 12/11/2023
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 *
 * copy and paste in lmic node in initialize sensors your recieve and transmit pins may be different
 *    Serial.begin(115200);
 *    Serial2.begin(115200, SERIAL_8N1, 2, 15);//recieve and transmit pins respectively
 *
 *Copy and paste code above processwork function. call function in process work Function
 *  uint16_t getSensorvalue(int write)
 *  {
 *   uint16_t HumidityPercentage;
 *   Serial2.write(char(write));
 *   Serial2.flush();
 *   if(Serial2.available()>0){
 *       HumidityPercentage=Serial2.read();
 *   }
 *   delay(1);
 *    return HumidityPercentage;
 *  }
 *
 */

// Include Particle Device OS APIss
#include "Particle.h"
// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(AUTOMATIC);

// Run the application and system concurrently in separate threads
SYSTEM_THREAD(ENABLED);

// Show system, cloud connectivity, and application logs over USB
// View logs with CLI using 'particle serial monitor --follow'
SerialLogHandler logHandler(LOG_LEVEL_INFO);
  const int wet=1100;// lowest analog value
  const int dry=2900;//highest analog value
  const int m=100;
void setup()
{
  Serial1.begin(115200);//
  Serial.begin(115200);//

}
void loop()
{
  u_int16_t battVoltage;
  u_int16_t HumidityPercent[m];
  int AveragePercent;
  u_int16_t sum=0;
 // Serial1.begin(115200);

  if(Serial1.available()>0)
  {
    for(int i=0;i<m;i++){
      battVoltage = analogRead(A0);
      HumidityPercent[i] = map(battVoltage, wet, dry, 100, 0);//returns a percentage in between 0 and 100 based on the humidity
      sum=sum+HumidityPercent[i];
    }
    AveragePercent=sum/m;//averages the data

    Serial1.write(char(AveragePercent));
    Serial1.flush();

  } 
//Serial1.flush();
  delay(19800);// syncs it to Lmic node i.e. if time set is 20 secs in LMic node delay argon by 20 seconds
  
}
