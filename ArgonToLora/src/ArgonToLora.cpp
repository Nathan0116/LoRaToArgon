/* 
 * Project myProject
 * Author: Your Name
 * Date: 
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
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
  const int wet=1100;
  const int dry=2900;

void setup()
{
  Serial1.begin(115200);//
  Serial.begin(115200);//

}
void loop()
{
  u_int16_t battVoltage;
  u_int16_t HumidityPercent[100];
  int AveragePercent;
  u_int16_t sum=0;
 // Serial1.begin(115200);

  if(Serial1.available()>0)
  {
    for(int i=0;i<100;i++){
      battVoltage = analogRead(A0);
      HumidityPercent[i] = map(battVoltage, wet, dry, 100, 0);
      sum=sum+HumidityPercent[i];
    }
    AveragePercent=sum/100;
  //  ch =Serial1.read();
  //  Serial.write(char(ch));
    Serial1.write(char(AveragePercent));
    Serial1.flush();
  //  Serial1.write(char(battVoltage));
 //   Serial1.end();
  } 
//Serial1.flush();
  delay(19800);
  
}