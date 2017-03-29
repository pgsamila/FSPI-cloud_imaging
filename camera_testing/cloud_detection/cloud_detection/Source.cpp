#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>


using namespace cv;
using namespace std;

int main (int argc, char* argv[])
{
	VideoCapture vcap;

	vcap.open("http://172.16.98.112:8080/video");
	if (!vcap.isOpened())// if not success
	{
		cout << "Cannot open the video" << endl;
		return -1;
	}

	double d_width = vcap.get(CV_CAP_PROP_FRAME_WIDTH);
	double d_height = vcap.get(CV_CAP_PROP_FRAME_HEIGHT);

	cout << "Frame size got!" << endl;

	namedWindow("original_video", CV_WINDOW_AUTOSIZE); // Create widow
	namedWindow("negative_video", CV_WINDOW_AUTOSIZE);

	while(1)
	{
		Mat frame;
		Mat contours;

		bool b_video_play = vcap.read(frame); // read a new frame from video

		if (!b_video_play)
		{
			cout << "Cannot Read a frame" << endl;
			break;
		}

		flip(frame, frame, 1);
		imshow("original_video", frame);

		Canny(frame, contours, 500, 1000, 5, true);
		imshow("negative_video", contours);
















		if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}
}