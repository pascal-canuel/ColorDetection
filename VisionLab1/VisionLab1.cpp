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

	// Show camera https://docs.opencv.org/3.0-beta/modules/videoio/doc/reading_and_writing_video.html
	
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
	
	// Default resolution of the frame is obtained.The default resolution is system dependent. 
	int frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	int frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

	VideoWriter video("../video/outCamera.avi", CV_FOURCC('M', 'J', 'P', 'G'), 10, Size(frame_width, frame_height));

	grab.initVideo(frame_width, frame_height);
	while (true)
	{
		cap >> frame;

		if (frame.empty())
		{
			break;
		}
	
		imshow("CamView", frame);
		video.write(frame);

		grab.getHSV(frame);
		if (waitKey(30) >= 0) break; // Quit if key entered		
	}

	//When everything done, release the video capture and write object
	cap.release();
	video.release();
	grab.release();

	grab.stopStats();

	//	Closes all the windows
	destroyAllWindows();
	return 0;
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Conseils pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
