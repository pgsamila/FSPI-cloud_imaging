#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include<conio.h>   


using namespace cv;
using namespace std;

vector<CvPoint> black_pixels;

//globle variables
const Scalar SCALAR_BLACK = Scalar(0.0, 0.0, 0.0);
const Scalar SCALAR_WHITE = Scalar(255.0, 255.0, 255.0);
const Scalar SCALAR_BLUE = Scalar(255.0, 0.0, 0.0);
const Scalar SCALAR_GREEN = Scalar(0.0, 200.0, 0.0);
const Scalar SCALAR_RED = Scalar(0.0, 0.0, 255.0);

int main (void)
{
	VideoCapture vcap;


	vcap.open("http://192.168.43.1:8080/video"); // ip address of the video stream

	if (!vcap.isOpened())// if video streaming does not catched
	{
		cout << "Cannot open the video" << endl;
		return -1;
	}

	int d_width = vcap.get(CV_CAP_PROP_FRAME_WIDTH);
	int d_height = vcap.get(CV_CAP_PROP_FRAME_HEIGHT);
	
	cout << "Frame size got!" << endl;

	
	///////////////////COLOR SEPERATION///////////////////////////
	int iLowH = 0;
	int iHighH = 200;

	int iLowS = 0;
	int iHighS = 10;

	int iLowV = 0;
	int iHighV = 255;

	createTrackbar("LowH", "Control", &iLowH, 179);
	createTrackbar("LowS", "Control", &iHighH, 179);

	createTrackbar("LowS", "Control", &iLowS, 255);

	createTrackbar("HighS", "Control", &iHighS, 255);

	createTrackbar("LowV", "Control", &iLowV, 255);
	createTrackbar("HighV", "Control", &iHighV, 255);

	//////////////////////////////////////////////

	//local variables

	bool took_first_frame = false;
	Mat frame;
	Mat contour;
	Mat first_frame;
	while(1)
	{
		bool b_video_play = vcap.read(frame);
		
		if (!b_video_play)
		{
			cout << "Cannot Read a frame" << endl;
			break;
		}
		
////////////////////////////////////////////////////////////////////////////////////
		
		Mat imgHSV;
		
		cvtColor(frame, imgHSV, COLOR_BGR2HSV);
		//imshow("HSV imga", imgHSV);
		Mat img_TresholdHSV;

		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), img_TresholdHSV);

		//imshow("Threshold img", img_TresholdHSV);

		erode(img_TresholdHSV, img_TresholdHSV, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(img_TresholdHSV, img_TresholdHSV, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		//imshow("Threshold img", img_TresholdHSV);

		dilate(img_TresholdHSV, img_TresholdHSV, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		erode(img_TresholdHSV, img_TresholdHSV, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		imshow("HSV image", imgHSV);
		imshow("Thresholded Image", img_TresholdHSV); // show tresholded image
		imshow("Original", frame); // show original image
		//cvtColor(imgHSV, imgHSV, CV_BGR2GRAY);

		int img_size = img_TresholdHSV.rows * img_TresholdHSV.cols;
		img_size = img_size / 100;
		int pixe = countNonZero(img_TresholdHSV);// / img_size;

		double presntage_clouds = pixe / img_size;
		cout << pixe << "    " << img_size << "    " << presntage_clouds << "%" << endl;

		//imshow("HSV imga", imgHSV);
		if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}
}