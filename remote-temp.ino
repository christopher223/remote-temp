// This is a remote temperature monitor for a NCD Particle Photon module
// connected to a SI7020-A20 temperature/humidity mini module sensor.

// It requires the Temperature_Alarm library available here:
// https://github.com/ControlEverythingCom/Temperature_Alarm/tree/master/firmware

#include "Temperature_Alarm/Temperature_Alarm.h"

SI7020_A20 tempSensor;

/*SI7120 specs
    Temperature range -40 - +125C
    Sensor is 16 bit or 0-65535
*/

// Basic temperature settings and data
char scale[] = "F";             // Can be C or F
double temp;                    // The current temperature

// Alarm settings and data
String alarmState = "normal";   // Temperature state: "high", "low", "normal"
String alarmMode = "off";       // Can be "off", "low", "high", or "all"

double highLimit;               // High temperature limit
double lowLimit;                // Low temperature limit

// Event publishing settings
long lastPublish = 0;     // Keep track of publication timing
String pubMode = "all";    // Can be "off", "temp", "alarm", or "all"
int pubMinutes = 5;       // Temperature publishing interval in minutes


// Protoype functions
int setScale(String command);     // Set the temperature scale

int setAlarm(String command);     // Set alarm mode
int setPublish(String command);   // Set publishing mode
int setInterval(String command);  // Set publishing interval

int setHigh(String limit);        // Set high temperature limit
int setLow(String limit);         // Set low temperature limit

void setup() {
  // Expose variables to Particle Cloud
  Particle.variable("scale", scale);
  Particle.variable("temperature", temp);
  Particle.variable("alarm_state", alarmState);

  Particle.variable("alarm_mode", alarmMode);
  Particle.variable("high_limit", highLimit);
  Particle.variable("low_limit", lowLimit);

  Particle.variable("pub_mode", pubMode);
  Particle.variable("pub_minutes", pubMinutes);

  // Expose functions to Particle Cloud
  Particle.function("set_scale", setScale);

  Particle.function("set_alarm", setAlarm);
  Particle.function("set_publish", setPublish);
  Particle.function("set_interval", setInterval);

  Particle.function("set_high", setHigh);
  Particle.function("set_low", setLow);
}

void loop() {
  // Update the current temperature based on scale setting
  if(scale[0] == 'F') {
    temp = tempSensor.temperatureF();
  } else {
    temp = tempSensor.temperatureC();
  }

  // Check for high temperature condition if alarm is on
  if( (alarmMode == "high" || alarmMode == "all") && temp > highLimit) {
    if(alarmState != "high") {
      // Upate alarm state if there is a change
      alarmState = "high";
      // Publish alarm state change if publishing turned on
      if(pubMode == "alarm" || pubMode == "all") { publishAlarm(); }
    }
  // Check for low temperature condition if alarm is on
  } else if((alarmMode == "low" || alarmMode == "all") && temp < lowLimit) {
    if (alarmState != "low") {
      // Upate alarm state if there is a change
      alarmState = "low";
      // Publish alarm state change if publishing turned on
      if(pubMode == "alarm" || pubMode == "all") {publishAlarm();}
    }
  // Upate alarm state if temperature has returned to normal
  } else if(alarmState != "normal") {
    alarmState = "normal";
    // Publish alarm state change if publishing turned on
    if(pubMode == "alarm" || pubMode == "all") {publishAlarm();}
  }

  // Check if its time to publish a temperature update
  if(millis() - lastPublish > pubMinutes*60*1000){
    // Reset publication time
    lastPublish = millis();

    // Publish the temperature if turned on
    if(pubMode == "temp" || pubMode == "all") {
      Particle.publish("temp", String::format("%.2f", temp));
    }
  }
}

// Publish an alarm event
void publishAlarm() {
  Particle.publish("alarm", alarmState + String::format(": %.2f", temp));
}

// Set the high temperature limit
int setHigh(String limit){
  highLimit = limit.toFloat();
  return 1;
}

// Sets the low temperature limit
int setLow(String limit){
  lowLimit = limit.toFloat();
  return 1;
}

// Sets temperature scale. Returns 1 if input is "F" or "C",
// otherwise returns -1.
int setScale(String command){
  command.toUpperCase();

  if( command == "C" || command == "F" ) {
    command.toCharArray(scale, 2);
    return 1;
  } else {
    return -1;
  }
}

// Sets alarm mode. Returns 1 if input is "off", "low",
// "high", or "all"; otherwise returns -1.
int setAlarm(String command){
  command.toLowerCase();

  if( command == "off" ||
      command == "low" ||
      command == "high" ||
      command == "all" ) {
    alarmMode = command;
    return 1;
  } else {
    return -1;
  }
}

// Sets publishing mode. Returns 1 if input is "off", "temp",
// "alarm", or "all"; otherwise returns -1.
int setPublish(String command){
  command.toLowerCase();

  if( command == "off" ||
      command == "temp" ||
      command == "alarm" ||
      command == "all" ) {
    pubMode = command;
    return 1;
  } else {
    return -1;
  }
}

// Sets publishing interval. Returns 1 if input is a positive
// integer greater than 1; otherwise returns -1.
int setInterval(String command){
  if(command.toInt() > 0) {
    pubMinutes = command.toInt();
    return 1;
  } else {
    return -1;
  }
}
