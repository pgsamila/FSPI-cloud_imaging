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


	vcap.open("http://192.168.42.129:8080/video"); // ip address of the video stream

	if (!vcap.isOpened())// if video streaming does not catched
	{
		cout << "Cannot open the video" << endl;
		return -1;
	}

	double d_width = vcap.get(CV_CAP_PROP_FRAME_WIDTH);
	double d_height = vcap.get(CV_CAP_PROP_FRAME_HEIGHT);

	cout << "Frame size got!" << endl;

	
	///////////////////COLOR SEPERATION///////////////////////////
	int iLowH = 0;
	int iHighH = 179;

	int iLowS = 0;
	int iHighS = 255;

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
		bool b_video_play = vcap.read(first_frame);
		
		b_video_play = vcap.read(frame);
		if (!b_video_play)
		{
			cout << "Cannot Read a frame" << endl;
			break;
		}
		
		//flip(frame, frame, 1);
		imshow("original_video", frame);

		//Canny(frame, contour, 500, 1000, 5, true);
		//imshow("negative_video", contour);

		/// Up to now, the streaming video frames are recived.
		
		//Mat img_frame1 = frame;
		//Mat img_frame2 = first_frame;
		Mat img_original = frame;
		//Mat img_defference;
		//Mat img_treshold;
		//cvtColor(img_frame1, img_frame1, CV_BGR2GRAY);
		//cvtColor(img_frame2, img_frame2, CV_BGR2GRAY);
		//imshow("GrayScale",img_frame1);
		//GaussianBlur(img_frame1, img_frame1, Size(5, 5), 0);
		//GaussianBlur(img_frame2, img_frame2, Size(5, 5), 0);
		//imshow("GaussianBlur", img_frame1);
		//absdiff(img_frame1, img_frame2, img_defference);
		//imshow("Defference", img_defference); 

		//threshold(img_defference, img_treshold, 50, 255.0, CV_THRESH_BINARY);

		//threshold(img_defference, img_treshold, 50, 255.0, CV_THRESH_BINARY);
		//threshold(img_frame2, img_treshold, 150, 255.0, CV_THRESH_BINARY);
		//imshow("Threshold", img_treshold);
		
		//Mat structuringElement3x3 = getStructuringElement(MORPH_RECT, Size(3, 3));
		//Mat structuringElement5x5 = getStructuringElement(MORPH_RECT, Size(5, 5));
		//Mat structuringElement7x7 = getStructuringElement(MORPH_RECT, Size(7, 7));
		//Mat structuringElement9x9 = getStructuringElement(MORPH_RECT, Size(9, 9));

		//dilate(img_treshold, img_treshold, structuringElement5x5);
		//dilate(img_treshold, img_treshold, structuringElement5x5);
		//erode(img_treshold, img_treshold, structuringElement5x5);

		//Mat img_treshold_copy = img_treshold.clone();

		//vector<vector<Point> > contours;

		//findContours(img_treshold_copy, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

		//Mat img_contours(img_treshold_copy.size(), CV_8UC3, SCALAR_BLACK);

		//drawContours(img_contours, contours, -1, SCALAR_WHITE, -1);

		//imshow("Contours", img_contours);


		//imshow("thresh", img_treshold);

////////////////////////////////////////////////////////////////////////////////////
		
		Mat imgHSV;
		
		cvtColor(img_original, imgHSV, COLOR_BGR2HSV);
		//imshow("HSV imga", imgHSV);
		Mat img_TresholdHSV;

		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), img_TresholdHSV);

		//imshow("Threshold img", img_TresholdHSV);

		erode(img_TresholdHSV, img_TresholdHSV, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(img_TresholdHSV, img_TresholdHSV, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		//imshow("Threshold img", img_TresholdHSV);

		
		//for (int row = 0; row < 160; row++) {
			//for (int cols = 0; cols < 240; cols++) {
				//Vec3b oldOne = imgHSV.at<Vec3b>(row, cols);
				//for (int z = 0; z < 255; z++) {
					//if (imgHSV.at<Vec3b>(row, cols) == Vec3b(0, 0, 200)) {
						//Vec3b newOne = Vec3b(0, 0, 0);
						//imgHSV.at<Vec3b>(row, cols) = Vec3b(0, 0, 0);// = '0';
					//}
				//}
			//}
		//}
		cvtColor(imgHSV, imgHSV, CV_BGR2GRAY);

		imshow("HSV imga", imgHSV);
		if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}
}