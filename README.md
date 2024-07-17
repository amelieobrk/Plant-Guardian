Our code is designed for an automated plant care system that we developed to monitor and adjust the environment for different types of plants based on their specific needs. It utilizes sensors to measure light, soil moisture, and water level in a tank, and controls a water pump and an LED light to manage the plant's watering and lighting requirements. We allow users to select the type of plant they are growing, and the system adjusts its thresholds for light and soil moisture accordingly.

**Brief Overview**
Platforms: Our code is likely designed for an Arduino or similar microcontroller platform, given its use of pins and the setup() and loop() structure.

Components: We employ sensors for light (connected to A0), soil moisture (A1), and water level (A2), along with a water pump (pin 8) and an LED (pin 9) for actuation based on the sensor inputs.

Software: The code snippet is written in C/C++ specifically for Arduino IDE, which we use to upload the program to the microcontroller.

**Setup Instructions**
Hardware Assembly:
●	Connect the light sensor to pin A0, the soil moisture sensor to pin A1, and the water level sensor to pin A2.
●	Attach the water pump's control input to digital pin 8 and the LED to digital pin 9.
●	Ensure that each component is correctly powered, paying attention to the voltage requirements to avoid damage.

**Software Preparation:**
●	Install the Arduino IDE from the official Arduino website.
●	Open the Arduino IDE, paste the provided code into a new sketch, and select the correct board and port under the Tools menu.

**Customization for Plant Type:**
●	Our system allows the selection of plant type via serial input to customize care parameters. We might need to adjust the thresholds (lightSensorMinThreshold, drySoilThreshold, goodSoilThreshold) based on the specific needs of our plant, which could involve some trial and error or further research on optimal conditions for our plant type.
Operation:
●	After setting up and powering the microcontroller, open the Serial Monitor in the Arduino IDE to select the plant type as instructed by the serial outputs.
●	Our system automatically checks light and soil moisture at predefined intervals, adjusting the LED light and activating the water pump as needed based on the sensor readings and selected plant type.

**In-Depth Explanation**
For a more detailed guide, including troubleshooting tips and advanced customization, we may consider the following aspects:

**Sensor Calibration:** We learn how to calibrate each sensor for accurate readings, considering the specific environmental conditions and the sensor's placement relative to the plant.
Non-blocking Code: We investigate techniques to avoid the use of delay() for the water pump, which could block other sensor readings. This might involve using millis() for timing or exploring interrupt-based sensor readings for more responsive plant care.
Energy Efficiency: We explore ways to optimize the system for energy efficiency, such as adjusting the frequency of sensor readings based on the plant's life cycle or using low-power modes on the microcontroller.

**Plant’s image processing **
Using image processing techniques, we can convert plant images, captured from the camera, into quantitative data for growth analysis. This approach is one of the few non-invasive monitoring techniques, but also it could be tricky due to the changes in the light and shadows in the images. 
For our scenario, we considered a simple example of a well exposed plant of basil.
The idea behind the growth’s monitoring of the plant is to grab a pair of images in a relevant timespan of the same plant and measure the amount of green pixels in the image.
The computation can be explained in a few steps:
1.	Crop the images to a fixed size of 640x480px to simulate the images grabbed from the camera
2.	Convert the images to HSL color space, since it has a clear separation between the representation of the color information (hue) from illumination variations (lightness).
3.	 Apply median filtering with a kernel size of 5 to reduce noise
4.	Segment the image applying a mask defined on lower and upper range of green color
5.	Compute the average amount of green pixels in the right color channel 


Taking pictures of an aromatic plant taken in a few days is enough to see an increment in the level of green. The image processing developments have  been developed in Python language and are available at the subfolder Image Processing. The latter contains:

-	requirements.txt: it has the list of the packages to be installed in order to run the main script
-	main.py: script to run in order to compute the amount of green levels in the pair of images passed in input
-	resources: folder used to store sample images and conduct tests on the green segmentation

To run it firstly we need to install the packages, it is suggested to do it in a venv environment with the command pip install -r requirements.txt.
After the packages’ installation, we can run the script in the console, passing two mandatory arguments that represent respectively the first image and the second image of the plant and optionally a third one to display the segmented images.
The script will compute the segmented green areas that was able to detect and store them in the resources folder, and it will print in the console the mean value of green of  both. We are expecting that the value of the second image is increasing, otherwise the plant would require some human check to verify that is not affected by diseases. 
To test that we are using some images stored in the filesystem under the path Image Processing/resources.


**Future work **
In our future work, we aim to refine our automated plant care system by incorporating the capability for the system to adjust the volume of water delivered to the plant, based on the soil moisture level readings rather than ambient humidity. This approach will take into account both the measured moisture level in the soil and the optimal moisture level for the specific plant type, as well as the size of the plant's pot. By doing so, we ensure a more tailored and efficient watering process that meets the precise needs of each plant.

Calculation for Optimal Water Delivery
To calculate the optimal amount of water needed, our system will first measure the current moisture level in the soil using the soil moisture sensor. It will then compare this reading to the predefined optimal moisture level for the selected plant type. Based on the difference between these two values and considering the size of the plant's pot, our system will calculate the exact amount of water needed to reach the optimal soil moisture level.

Adjusting Water Pump Activation Time
Based on the calculated water volume needed, our system will then determine the duration for which the water pump should be activated. This calculation will take into account the flow rate of the pump to ensure that the correct volume of water is delivered to the plant. For instance, if our pump has a flow rate of 100 mL/min and we need to deliver 200 mL of water to reach the optimal soil moisture level, our system will activate the pump for 2 minutes.

Implementation Plan

●	Enhanced Soil Moisture Monitoring: Integrate high-precision soil moisture sensors capable of delivering accurate moisture level readings.
●	Dynamic Watering Algorithm: Develop an algorithm that calculates the water volume needed based on current and optimal soil moisture levels and adjusts the pump activation time accordingly.
●	User Configuration Options: Implement features in our user interface that allow users to specify the size of their plant pot and to select from a list of common plants to ensure the system uses appropriate moisture thresholds.
●	Testing and Calibration: Conduct extensive field tests to calibrate the system's moisture sensing and water delivery mechanisms across a variety of soil types, plant species, and pot sizes.


Integration of  Web Application 
To further enhance the user-friendliness of our system, we plan to develop a comprehensive web application. This digital platform will serve as a central hub for users to interact with their automated plant care system remotely. Key features of the web application include:

●	Real-Time Monitoring: Users will be able to view current soil moisture levels 
●	Customizable Settings: The application will offer customization options, allowing users to input the specific dimensions of their plant pots, choose their plant types from an extensive database, and adjust the optimal moisture levels according to their preference.
●	Watering History and Insights: Users will have access to a detailed history of watering sessions showed by pictures over time, offering insights into  the efficiency of the system.
●	Remote Control: Beyond monitoring, the application will enable users to manually override the systems automated settings, offering the flexibility to adjust watering schedules.


