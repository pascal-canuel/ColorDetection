#pragma once
#include <opencv2/opencv.hpp>

class range {
public:
	cv::Scalar minScalar;
	cv::Scalar maxScalar;
	cv::Scalar bgrScalar;
	std::string nameColor;
	double nbPixel;
	double execTime;
	
	range(cv::Scalar pMinScalar, cv::Scalar pMaxScalar, cv::Scalar pBgrScalar, std::string pNameColor);
};