#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/objdetect.hpp"
#include <vector>
#include <iostream>
#include <string>

std::string folderPath = "C:/Users/HL2020/Downloads/30x45/*.jpg";
using namespace cv;
using namespace std;

void inspection(std::string imagePath)
{
	std::cout << "inspection: " << imagePath << std::endl;
	cv::Mat image = cv::imread(imagePath, cv::IMREAD_ANYCOLOR );

	// Load the classifier
    CascadeClassifier faceCascade, eyeCascade;
    faceCascade.load("D:/Projects/Github/passport_photo/src/haarcascade_frontalface_default.xml");
    eyeCascade.load("D:/Projects/Github/passport_photo/src/haarcascade_eye.xml");

    // Convert the image to grayscale
    Mat grayImage;
    cvtColor(image, grayImage, COLOR_BGR2GRAY);
    cv::resize(image,image, cv::Size(image.cols * 0.75,image.rows * 0.75), 0, 0, cv::INTER_LINEAR);
    // Detect faces in the image
    vector<Rect> faces;
    faceCascade.detectMultiScale(grayImage, faces, 1.1, 4);

    // Draw rectangles around the detected faces
    for (size_t i = 0; i < faces.size(); i++)
    {
        cv::Mat faceImg = grayImage(faces[i]);

        rectangle(image, faces[i], Scalar(0, 255, 0), 2);
    }

	cv::namedWindow("test", cv::WINDOW_KEEPRATIO);
	cv::imshow("test", image);
	cv::waitKey(0);
}

int main()
{
    std::vector<std::string> filenames;
	cv::glob(folderPath, filenames);

	for (size_t i=0; i<filenames.size(); i++)
	{
		inspection(filenames[i]);
	}
    return 0;
}