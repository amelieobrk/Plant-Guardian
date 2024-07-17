int lightSensorPin = A0;
int soilSensorPin = A1; 
int waterSensorPin = A2;
int waterPumpPin = 8;
int ledPin = 9;


int lightSensorMinThreshold; //ggfs anpassen
int drySoilThreshold;
int goodSoilThreshold;

int lightSensorValue = 0;
int soilSensorValue = 0;
int waterSensorValue = 0;
int watertype = 0;

// Delay
unsigned long previousLightCheckTime = 0; // Stores the last time the light was checked
const long lightInterval = 10000; // Interval at which to check light (30 seconds)

unsigned long previousSoilCheckTime = 0; // Stores the last time the soil was checked
const long soilInterval = 50000; // Interval at which to check soil (5 minutes)

long normalizedSoilSensorValue = 0;

void setup() {
  pinMode(soilSensorPin, INPUT);
  pinMode(waterSensorPin, INPUT);
  pinMode(waterPumpPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  // Make sure the serial monitor is running at the same baud as the program, in this case, 9600
  Serial.begin(9600);

  // Initialize sensor checks to happen immediately on startup
  previousLightCheckTime = millis() - lightInterval; // Ensures immediate light check
  previousSoilCheckTime = millis() - soilInterval; // Ensures immediate soil and water level check

  Serial.println(" ");
  Serial.println("Please select your plant type:");
  Serial.println("1 - Cacti and Succulents");
  Serial.println("2 - Aromatic Plant");
  Serial.println("3 - Foliage Plants");
  Serial.println("4 - Flowering Plants");
  Serial.println("5 - Herbs");
  Serial.println("6 - Air Purifying Plants");
  Serial.println("7 - Edible Plants");

  while (Serial.available() == 0);
  int plantType = Serial.parseInt();

  switch (plantType) {
    case 1: // Cacti and Succulents
      lightSensorMinThreshold = 415;
      drySoilThreshold = 15; // 35 - 20
      goodSoilThreshold = 40;
      break;
    case 2: // Aromatic Plant
      lightSensorMinThreshold = 315;
      drySoilThreshold = 35; // 55 - 20
      goodSoilThreshold = 60;
      break;
    case 3: // Foliage Plants
      lightSensorMinThreshold = 265;
      drySoilThreshold = 40; // 60 - 20
      goodSoilThreshold = 65;
      break;
    case 4: // Flowering Plants
      lightSensorMinThreshold = 315;
      drySoilThreshold = 45; // 65 - 20
      goodSoilThreshold = 70;
      break;
    case 5: // Herbs
      lightSensorMinThreshold = 315;
      drySoilThreshold = 50; // 70 - 20
      goodSoilThreshold = 75;
      break;
    case 6: // Air Purifying Plants
      lightSensorMinThreshold = 265;
      drySoilThreshold = 40; // 60 - 20
      goodSoilThreshold = 65;
      break;
    case 7: // Edible Plants
      lightSensorMinThreshold = 615;
      drySoilThreshold = 50; // 70 - 20
      goodSoilThreshold = 75;
      break;
    default:
      Serial.println("Invalid selection. Default values will be used.");
      // Set default values or prompt for input again.
  }

  Serial.print("Plant type selected: ");
  Serial.println(plantType);
}

void loop() {
  unsigned long currentMillis = millis();

  // Check the light every 30 seconds
  if (currentMillis - previousLightCheckTime >= lightInterval) {
    // Save the last time you checked the light
    previousLightCheckTime = currentMillis;

    // Read the light sensor value [170, 520-600, 784] with 220 ohm resistor 
    // [no light inside a box, no light indirect, under the sun]
    lightSensorValue = analogRead(lightSensorPin);
    if (lightSensorValue < lightSensorMinThreshold) {
      Serial.println("The light exposure is too low: activating the lamp: " + String(lightSensorValue));
      digitalWrite(ledPin, HIGH);
    } else {
      Serial.println("The light exposure is above the optimal level!");
      digitalWrite(ledPin, LOW);
    }
  }

  // Check the soil and water level every 5 minutes
  // After the water was watered will give time for the soil to absorve the water
  // and if the water level gets bellow the sensor will give time for it to dry out
  if (currentMillis - previousSoilCheckTime >= soilInterval) {
    // Save the last time you checked the soil and water level
    previousSoilCheckTime = currentMillis;
    // Read the water level value (check if there's water in the tank before activate the) [0 - 350] 
    // If it's above 100, you can activate the pump safely
    waterSensorValue = analogRead(waterSensorPin);
    // Read the soil sensor value: [0 - 700]
    soilSensorValue = analogRead(soilSensorPin);
    // Normalize the value, check the soil moisture
    double normalizedSoilSensorValue = (soilSensorValue * 100.0) / 700.0;
    if (normalizedSoilSensorValue > 100) { normalizedSoilSensorValue = 100; }
    Serial.println("The soil moisture level is: " + String(normalizedSoilSensorValue));

    // Check soil moisture and water tank level as before
    if (normalizedSoilSensorValue < drySoilThreshold) {
      // Read the water level value (check if there's water in the tank before activate the) [0 - 350] 
      // If it's above 100, you can activate the pump safely
      if (waterSensorValue > 100) {
        Serial.println("Activating the water pump for 2s!");
        digitalWrite(waterPumpPin, HIGH);
        delay(5000); // Note: This delay is still blocking; consider an alternative approach for non-blocking behavior
        digitalWrite(waterPumpPin, LOW);
      } else {
        Serial.println("Warnning: the water sensor is revealing lack of water, fill it up!");
      }
    } else if (normalizedSoilSensorValue >= drySoilThreshold && normalizedSoilSensorValue < goodSoilThreshold) {
      if (waterSensorValue < 100) {Serial.println("Warnning: the water sensor is revealing lack of water, fill it up!");}
      Serial.println("The soil moisture is optimal, don't worry: " + String(normalizedSoilSensorValue));
    } else {
      if (waterSensorValue < 100) {Serial.println("Warnning: the water sensor is revealing lack of water, fill it up!");}
      Serial.println("The soil moisture is above optimal, the plant doesn't need water.");
    }
  }
}

  