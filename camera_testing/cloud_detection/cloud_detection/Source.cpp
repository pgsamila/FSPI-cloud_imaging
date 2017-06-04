#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <conio.h>   
#include <ctime>
#include <fstream>


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
	VideoCapture vcap(0);

	time_t now_time;

	//vcap.open("http://192.168.43.1:8080/video"); // ip address of the video stream

	if (!vcap.isOpened())// if video streaming does not catched
	{
		cout << "Cannot open the video" << endl;
		while (true) {

		}
		return -1;
	}

	int d_width = vcap.get(CV_CAP_PROP_FRAME_WIDTH);
	int d_height = vcap.get(CV_CAP_PROP_FRAME_HEIGHT);
	
	cout << "Frame size got!" << endl;

	
	///////////////////COLOR SEPERATION///////////////////////////
	int iLowH = 10;
	int iHighH = 200;

	int iLowS = 0;
	int iHighS = 10;

	int iLowV = 10;
	int iHighV = 255;



	//////////////////////////////////////////////

	//local variables

	bool took_first_frame = false;
	Mat frame;
	Mat contour;
	Mat first_frame;
	//time(&now_time);
	ofstream myfile;
	myfile.open("tuesday_data_10.csv");
	//vcap.set(CV_CAP_PROP_FPS, 10);
	int counting = 0;
	long long loging = 0;

	int frame_width = vcap.get(CV_CAP_PROP_FRAME_WIDTH);
	int frame_height = vcap.get(CV_CAP_PROP_FRAME_HEIGHT);
	//VideoWriter video("saturday_video1.avi", CV_FOURCC('M', 'J', 'P', 'G'), 10, Size(frame_width, frame_height), true);
	//VideoWriter videoHSV("saturday_video_HSV1.avi", CV_FOURCC('M', 'J', 'P', 'G'), 10, Size(frame_width, frame_height), true);
	//VideoWriter videoTresh("saturday_video_Tresh.avi", CV_FOURCC('M', 'J', 'P', 'G'), 10, Size(frame_width, frame_height), true);



	while(1)
	{
		time(&now_time);
		bool b_video_play = vcap.read(frame);
		//video.write(frame);
		if (counting == 29) {
			loging++;
			if (!b_video_play)
			{
				cout << "Cannot Read a frame" << endl;
				myfile.close();
				break;
			}

			////////////////////////////////////////////////////////////////////////////////////

			Mat imgHSV;

			cvtColor(frame, imgHSV, COLOR_BGR2HSV);

			Mat img_TresholdHSV;

			/*********************************************************/
			iLowH = 0;
			iHighH = 250;

			iLowS = 0;
			iHighS = 10;

			iLowV = 0;
			iHighV = 255;
			createTrackbar("LowH", "Control", &iLowH, 179);
			createTrackbar("LowS", "Control", &iHighH, 179);

			createTrackbar("LowS", "Control", &iLowS, 255);

			createTrackbar("HighS", "Control", &iHighS, 255);

			createTrackbar("LowV", "Control", &iLowV, 255);
			createTrackbar("HighV", "Control", &iHighV, 255);

			inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), img_TresholdHSV);

			erode(img_TresholdHSV, img_TresholdHSV, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
			dilate(img_TresholdHSV, img_TresholdHSV, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

			dilate(img_TresholdHSV, img_TresholdHSV, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
			erode(img_TresholdHSV, img_TresholdHSV, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
			/**********************************************************/
			imshow("HSV image", imgHSV);
			imshow("Bright clouds", img_TresholdHSV); // show tresholded image
			imshow("Original", frame); // show original image
			//cvtColor(imgHSV, imgHSV, CV_BGR2GRAY);

			int img_size = img_TresholdHSV.rows * img_TresholdHSV.cols;
			img_size = img_size / 100;
			int pixe = countNonZero(img_TresholdHSV);// / img_size;
			double presntage_clouds_light = pixe / img_size;
			//videoTresh.write(img_TresholdHSV);
			/***********************************/

			cout << loging << "    " << ctime(&now_time) << "    " << presntage_clouds_light /*<< "," << presntage_clouds_havy*/ << "%" << endl;

			myfile << loging << "," << presntage_clouds_light << "," << ctime(&now_time);
			
			//videoHSV.write(imgHSV);
			
			//imshow("HSV imga", imgHSV);
			if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
			{
				cout << "esc key is pressed by user" << endl;
				myfile.close();
				break;
			}
			counting = 0;
		}
		else {

			if (!b_video_play)
			{
				cout << "Cannot Read a frame" << endl;
				myfile.close();
				break;
			}

			if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
			{
				cout << "esc key is pressed by user" << endl;
				myfile.close();
				break;
			}
			counting++;
		}
	}
	
}