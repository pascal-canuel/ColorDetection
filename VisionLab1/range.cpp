#include "pch.h"
#include "range.h"

range::range(cv::Scalar pMinScalar, cv::Scalar pMaxScalar, cv::Scalar pBgrScalar, std::string pNameColor) {
	minScalar = pMinScalar;
	maxScalar = pMaxScalar;
	bgrScalar = pBgrScalar;
	nameColor = pNameColor;
}
