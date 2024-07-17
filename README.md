# PlantGuardian Eco-Watering System

##Authors

Filipe Tendeiro 
Amelie Helen Oberkirch 
Salvatore Starace


## Project Overview

Our code is designed for an automated plant care system that we developed to monitor and adjust the environment for different types of plants based on their specific needs. It utilizes sensors to measure light, soil moisture, and water level in a tank, and controls a water pump and an LED light to manage the plant's watering and lighting requirements. We allow users to select the type of plant they are growing, and the system adjusts its thresholds for light and soil moisture accordingly.

## Brief Overview

### Platforms
Our code is likely designed for an Arduino or similar microcontroller platform, given its use of pins and the setup() and loop() structure.

### Components
We employ sensors for light (connected to A0), soil moisture (A1), and water level (A2), along with a water pump (pin 8) and an LED (pin 9) for actuation based on the sensor inputs.

### Software
The code snippet is written in C/C++ specifically for Arduino IDE, which we use to upload the program to the microcontroller.

## Setup Instructions

### Hardware Assembly
- Connect the light sensor to pin A0, the soil moisture sensor to pin A1, and the water level sensor to pin A2.
- Attach the water pump's control input to digital pin 8 and the LED to digital pin 9.
- Ensure that each component is correctly powered, paying attention to the voltage requirements to avoid damage.

### Software Preparation
- Install the Arduino IDE from the official Arduino website.
- Open the Arduino IDE, paste the provided code into a new sketch, and select the correct board and port under the Tools menu.

### Customization for Plant Type
- Our system allows the selection of plant type via serial input to customize care parameters. We might need to adjust the thresholds (`lightSensorMinThreshold`, `drySoilThreshold`, `goodSoilThreshold`) based on the specific needs of our plant, which could involve some trial and error or further research on optimal conditions for our plant type.

### Operation
- After setting up and powering the microcontroller, open the Serial Monitor in the Arduino IDE to select the plant type as instructed by the serial outputs.
- Our system automatically checks light and soil moisture at predefined intervals, adjusting the LED light and activating the water pump as needed based on the sensor readings and selected plant type.

## In-Depth Explanation

For a more detailed guide, including troubleshooting tips and advanced customization, consider the following aspects:

### Sensor Calibration
Learn how to calibrate each sensor for accurate readings, considering the specific environmental conditions and the sensor's placement relative to the plant.

### Non-blocking Code
Investigate techniques to avoid the use of `delay()` for the water pump, which could block other sensor readings. This might involve using `millis()` for timing or exploring interrupt-based sensor readings for more responsive plant care.

### Energy Efficiency
Explore ways to optimize the system for energy efficiency, such as adjusting the frequency of sensor readings based on the plant's life cycle or using low-power modes on the microcontroller.

## Plant’s Image Processing

Using image processing techniques, we can convert plant images, captured from the camera, into quantitative data for growth analysis. This approach is one of the few non-invasive monitoring techniques but can be tricky due to changes in light and shadows in the images.

For our scenario, we considered a simple example of a well-exposed basil plant. The idea behind the growth monitoring is to grab a pair of images in a relevant timespan of the same plant and measure the amount of green pixels in the image. The computation involves the following steps:
1. Crop the images to a fixed size of 640x480px to simulate the images grabbed from the camera.
2. Convert the images to HSL color space, since it has a clear separation between the representation of the color information (hue) from illumination variations (lightness).
3. Apply median filtering with a kernel size of 5 to reduce noise.
4. Segment the image by applying a mask defined on lower and upper range of green color.
5. Compute the average amount of green pixels in the right color channel.

Taking pictures of an aromatic plant over a few days is enough to see an increase in the level of green. The image processing developments have been developed in Python and are available in the subfolder Image Processing, which contains:

- `requirements.txt`: A list of the packages to be installed to run the main script.
- `main.py`: Script to run in order to compute the amount of green levels in the pair of images passed as input.
- `resources`: Folder used to store sample images and conduct tests on green segmentation.

### Running the Script
1. Install the packages, preferably in a virtual environment, using the command:
   ```bash
   pip install -r requirements.txt
2. Run the script in the console, passing two mandatory arguments that represent the first and second images of the plant, and optionally a third one to display the segmented images. The script will compute the segmented green areas and store them in the resources folder, printing the mean value of green pixels for both images in the console.


###Future Work
In future work, we aim to refine our automated plant care system by incorporating the capability for the system to adjust the volume of water delivered to the plant based on the soil moisture level readings rather than ambient humidity. This approach will consider both the measured moisture level in the soil and the optimal moisture level for the specific plant type, as well as the size of the plant's pot.

**Calculation for Optimal Water Delivery**
To calculate the optimal amount of water needed:
	1	Measure the current moisture level in the soil using the soil moisture sensor.
	2	Compare this reading to the predefined optimal moisture level for the selected plant type.
	3	Based on the difference and considering the size of the plant's pot, calculate the exact amount of water needed to reach the optimal soil moisture level.


**Adjusting Water Pump Activation Time**
Determine the duration for which the water pump should be activated, taking into account the flow rate of the pump. For example, if the pump has a flow rate of 100 mL/min and 200 mL of water is needed, activate the pump for 2 minutes.


