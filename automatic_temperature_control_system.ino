#include <OneWire.h>

#include <DallasTemperature.h>

#include <Servo.h>

 

// Data wire is connected to digital pin 2

#define ONE_WIRE_BUS 2

#define RELAY_PIN 3  // Pin connected to the relay

#define SERVO_PIN 4  // Pin connected to the servo

 

// Setup a oneWire instance to communicate with any OneWire devices

OneWire oneWire(ONE_WIRE_BUS);

 

// Pass our oneWire reference to DallasTemperature library

DallasTemperature sensors(&oneWire);

 

Servo servoMotor;

 

bool circuitActive = true;  // Flag to track if the circuit is active

 

void setup() {

  Serial.begin(9600);

  sensors.begin();

 

  pinMode(RELAY_PIN, OUTPUT); // Set the relay pin as an output

  digitalWrite(RELAY_PIN, LOW); // Initialize the relay in OFF state

 

  servoMotor.attach(SERVO_PIN);  // Attach the servo to the specified pin

}

 

void loop() {

  if (circuitActive) {

  

    sensors.requestTemperatures(); // Send the command to get temperatures

 

    // Read temperature in Celsius

    float temperatureC = sensors.getTempCByIndex(0);

 

    // Read temperature in Fahrenheit

    float temperatureF = sensors.toFahrenheit(temperatureC);

     

    // Print temperature readings

    Serial.print("Temperature: ");

    Serial.print(temperatureC);

    Serial.print("°C   ");

    Serial.print(temperatureF);

    Serial.println("°F");

    servoMotor.write(0);

    // Control the relay based on temperature

    if (temperatureC <= 52.50) { // Example threshold temperature

      digitalWrite(RELAY_PIN, HIGH); // Turn ON the relay

      Serial.println("Relay ON");

 

      // Control the servo motor based on temperature

      // You can adjust the servo angles based on your requirements

     // servoMotor.write(180); // Set the servo to a specific angle (e.g., 90 degrees)

 

      // Perform actions before shutting down

      circuitActive = true;  // Deactivate the circuit

      // Additional shutdown actions can be added here

    } else {

      digitalWrite(RELAY_PIN, LOW); // Turn OFF the relay

      Serial.println("Relay OFF");

      servoMotor.write(0); // Set the servo to another angle (e.g., 0 degrees)

      circuitActive = false;

    }

  }

  // If the circuit is not active, put the microcontroller in sleep mode

  if (!circuitActive) {

    sensors.requestTemperatures(); // Send the command to get temperatures

 

    // Read temperature in Celsius

    float temperatureC = sensors.getTempCByIndex(0);

    Serial.print("Temperature: ");

    Serial.print(temperatureC);

    Serial.print("°C   ");

      servoMotor.write(180);

    if (temperatureC < 50) {

      circuitActive = true;

    }

    Serial.println("Circuit deactivated. Entering sleep mode.");

    delay(1000); // Give some time for printing before sleep

    // Enter sleep mode here, the exact method depends on your microcontroller

    // For Arduino, you might use: sleep_mode();

  }

}