// VisionLab1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
// Lab 1 Vision par ordinateur
// Par Pascal Canuel et Justin Roberge-Lavoie

#include "pch.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "CGrabber.h"

using namespace std;
using namespace cv;

int main()
{
	CGrabber grab;
	VideoCapture cap(0);
	if (!cap.isOpened())
	{
		cout << "The camera is not opened" << endl;
		return -1;
	}

	Mat frame;
	namedWindow("CamView", WINDOW_NORMAL);
	resizeWindow("CamView", 700, 500);
	
	while (true)
	{
		cap >> frame;
		if (frame.empty())
		{
			break;
		}
	
		imshow("CamView", frame);

		//	Detect only the two biggest forms of a given colors for performance purpose
		grab.getHSV(frame);
		if (waitKey(30) >= 0) break; // Quit if key entered		
	}

	cap.release();

	//	Closes all the windows
	destroyAllWindows();
	return 0;
}

