import sys

import cv2
import numpy as np

fixed_width = 640
fixed_height = 480


def green_color_thresholding(image):
    green_lower = (40, 50, 50)  # Hue, Saturation, Value (looser range)
    green_upper = (80, 255, 255)  # Hue, Saturation, Value (tighter range)
    mask = cv2.inRange(image, green_lower, green_upper)
    result = cv2.bitwise_and(image, image, mask=mask)



    return result


def mean_green_intensity(hsv_image):
    pixel_count_in_image = 307200
    mean_average_green_value = np.round(np.count_nonzero(hsv_image) / pixel_count_in_image * 100, 2)
    return mean_average_green_value


def preprocess_image(image):
    resized_image = cv2.resize(image, (fixed_width, fixed_height))
    hsv_image = cv2.cvtColor(resized_image, cv2.COLOR_BGR2HSV)
    hsv_image = cv2.medianBlur(hsv_image, 5)
    return hsv_image


if __name__ == '__main__':
    # Define green color range (adjust values for better segmentation in your image)

    if len(sys.argv) < 3:
        print("Error: Please provide two mandatory arguments <img_1_path> <img_2_path>")
        sys.exit(1)

    img_1 = cv2.imread(sys.argv[1])
    img_2 = cv2.imread(sys.argv[2])

    img_1 = preprocess_image(img_1)
    img_2 = preprocess_image(img_2)

    segmented_img_1 = green_color_thresholding(img_1.copy())
    cv2.imwrite("resources/segmented_img_1.jpeg", cv2.cvtColor(segmented_img_1, cv2.COLOR_HSV2RGB))
    normalized_green_value_img_1 = mean_green_intensity(segmented_img_1)
    print("The detected percentage of green in the first image is %.2f" % normalized_green_value_img_1)

    segmented_img_2 = green_color_thresholding(img_2.copy())
    cv2.imwrite("resources/segmented_img_2.jpeg", cv2.cvtColor(segmented_img_2, cv2.COLOR_HSV2RGB))
    normalized_green_value_img_2 = mean_green_intensity(segmented_img_2)
    print("The detected percentage of green in the second image %.2f" % normalized_green_value_img_2)

    if normalized_green_value_img_2 > normalized_green_value_img_1:
        print("Your plant is growing!")
    else:
        print("Your plant is not growing as expected, please have a look at it.")

    # Create named window
    cv2.namedWindow("Original Image 1", cv2.WINDOW_NORMAL)  # Allow resizing
    cv2.namedWindow("Original Image 2", cv2.WINDOW_NORMAL)  # Allow resizing
    cv2.resizeWindow("Original Image 1", fixed_width, fixed_height)
    cv2.resizeWindow("Original Image 2", fixed_width, fixed_height)

    cv2.imshow("Original Image 1", cv2.cvtColor(img_1, cv2.COLOR_HSV2RGB))
    cv2.imshow("Original Image 2", cv2.cvtColor(img_2, cv2.COLOR_HSV2RGB))

    if len(sys.argv) > 3 and sys.argv[3] == 'True':
        cv2.namedWindow("Segmented Image 1 (Green)", cv2.WINDOW_NORMAL)
        cv2.namedWindow("Segmented Image 2 (Green)", cv2.WINDOW_NORMAL)
        cv2.resizeWindow("Segmented Image 1 (Green)", fixed_width, fixed_height)
        cv2.resizeWindow("Segmented Image 2 (Green)", fixed_width, fixed_height)
        cv2.imshow("Segmented Image 1 (Green)", cv2.cvtColor(segmented_img_1, cv2.COLOR_HSV2RGB))
        cv2.imshow("Segmented Image 2 (Green)", cv2.cvtColor(segmented_img_2, cv2.COLOR_HSV2RGB))
    cv2.waitKey(0)
    cv2.destroyAllWindows()
