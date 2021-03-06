#include "pch.h"
#include "CGrabber.h"
#include "range.h"
#include <map>
#include <iostream>
#include <fstream>

RNG rng(12345);

CGrabber::CGrabber() {
	iLowH = 0;
	iHighH = 179;

	iLowS = 0;
	iHighS = 255;

	iLowV = 0;
	iHighV = 255;

	it = colorToDetect.begin();
	it = colorToDetect.insert(it, range(Scalar(0, 150, 60), Scalar(10, 255, 255), Scalar(0, 0, 255), "Light Red"));	//	Red
	it = colorToDetect.insert(it, range(Scalar(170, 150, 60), Scalar(178, 255, 255), Scalar(0, 0, 255), "Red"));	//	Red
	it = colorToDetect.insert(it, range(Scalar(22, 70, 50), Scalar(37, 255, 255), Scalar(0, 255, 255), "Yellow"));	//	Yellow
	it = colorToDetect.insert(it, range(Scalar(38, 70, 50), Scalar(95, 255, 255), Scalar(0, 255, 0), "Green"));		//	Green
	it = colorToDetect.insert(it, range(Scalar(96, 70, 50), Scalar(130, 255, 255), Scalar(255, 0, 0), "Blue"));		//	Blue

	std::cout << "Loaded" << std::endl;
}

//	Hue values range 
//	Orange  0 - 22
//	Yellow 22 - 38
//	Green 38 - 75
//	Blue 75 - 130
//	Violet 130 - 160
//	Red 160 - 179
void CGrabber::getHSV(Mat pColor) {
	initFrame = pColor;
	cvtColor(initFrame, hsvFrame, COLOR_BGR2HSV);

	Mat result, drawingResult;
	for (it = colorToDetect.begin(); it < colorToDetect.end(); it++) {
	
		Mat binary;
		Mat colored;
		std::tie(binary, colored) = drawColorScalar(it);
		if (it == colorToDetect.begin())
		{
			result = binary;
			drawingResult = colored;
		}
		else
		{
			result = result | binary;
			drawingResult = drawingResult | colored;
		}
	}

	namedWindow("Threshed", WINDOW_NORMAL);
	resizeWindow("Threshed", 700, 500);
	imshow("Threshed", result);
	
	namedWindow("Contours");
	imshow("Contours", drawingResult);
}

std::tuple<cv::Mat, cv::Mat> CGrabber::drawColorScalar(std::vector<range>::iterator pIt)
{
	double init = (double)cv::getTickCount();

	Mat currentFrame;
	inRange(hsvFrame, pIt->minScalar, pIt->maxScalar, currentFrame);

	std::vector<Vec4i> hierarchy;
	std::vector<std::vector<Point> > contours;
	findContours(currentFrame, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	Mat drawing = Mat::zeros(currentFrame.size(), CV_8UC3);
	int largestIndex = 0;
	int largestContour = 0;
	int secondLargestIndex = 0;
	int secondLargestContour = 0;

	for (int i = 0; i < contours.size(); i++)
	{
		if (contours[i].size() > largestContour) {
			secondLargestContour = largestContour;
			secondLargestIndex = largestIndex;
			largestContour = contours[i].size();
			largestIndex = i;
		}
		else if (contours[i].size() > secondLargestContour) {
			secondLargestContour = contours[i].size();
			secondLargestIndex = i;
		}
	}

	drawContours(drawing, contours, largestIndex, pIt->bgrScalar, 2, 8, hierarchy, 0, Point());
	drawContours(drawing, contours, secondLargestIndex, pIt->bgrScalar, 2, 8, hierarchy, 0, Point());

	double sec = ((double)cv::getTickCount() - init) / cv::getTickFrequency();
	std::cout << pIt->nameColor << " " << sec << " sec" << std::endl;

	return std::pair<Mat, Mat>(currentFrame, drawing);
}
