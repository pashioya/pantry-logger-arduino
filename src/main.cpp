#include <Arduino.h>
#include <TempHum.h>
#include <Brightness.h>
 
void setup(){
 
  Serial.begin(9600);
  delay(500);//Delay to let system boot
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  delay(1000);//Wait before accessing Sensor
 
}//end "setup()"
 
void loop(){
  //Start of Program 

  readPin();
    
  Serial.print("Current humidity = ");
  Serial.print(readHum());
  Serial.print("%  ");
  Serial.print("temperature = ");
  Serial.print(readTemp()); 
  Serial.println("C  ");

  
  Serial.print("Brightness = ");
	Serial.println(readBright()); // light intensity
								// high values for bright environment
								// low values for dark environment
  
  delay(5000);//Wait 5 seconds before accessing sensor again.
 
  //Fastest should be once every two seconds.
 
}// end loop(