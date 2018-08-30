#pragma once
#include "pch.h"
#include "range.h"
#include <opencv2/opencv.hpp>

using namespace cv;

class CGrabber {
public:
	void getHSV(cv::Mat pFrame);
	void initVideo(int widthFrame, int heightFrame);
	void release();
	void initStats();
	void stopStats();

	CGrabber();  // This is the constructor
private:
	std::tuple<cv::Mat, cv::Mat> drawColorScalar(std::vector<range>::iterator pIt);


	VideoWriter videoThreshold;
	VideoWriter videoContour;

	int frame_width;
	int frame_height;

	std::vector<range> colorToDetect;
	std::vector<range>::iterator it;

	cv::Mat initFrame;
	cv::Mat hsvFrame;

	int iLowH;
	int iHighH;

	int iLowS;
	int iHighS;

	int iLowV;
	int iHighV;
};
