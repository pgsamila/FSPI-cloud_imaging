/**
*  @file    Source.cpp
*  @author  Pelaketigamage P.G.A.S.
*  @date    12/05/2017
*  @version 5.0
*
*  @brief Final Year Project -
*		  Electrical & Electronic Engineering Department
*		  Univeristy of Peradeniya
*
*  @section DESCRIPTION
*
*  This code will cluster the image and can group into 
*  color intensicy ranges of the image
*
*/
//#include <opencv2/highgui.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <cv.h>
#include "videoio.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	string filename = "test.avi";
	VideoCapture vcap;
	vcap.open("C:/test.avi");
	//VideoCapture vcap("C:/test.avi");

	if (!vcap.isOpened())
	{
		cout << "Error when reading test.avi" << endl;
		while (1);
	}
	const int MAX_CLUSTERS = 5;
	Scalar colorTab[] =
	{
		Scalar(0,0,255),
		Scalar(0,255,0),
		Scalar(255,100,100),
		Scalar(255,0,255),
		Scalar(0,255,255)
	};

	Mat blurImg,src;// (500, 500, CV_8UC3);
	RNG rng(12345);
	for (int i = 0; i < 1800; i++) {
		vcap.read(src);
		if (src.empty())
			break;
	}
	//time_t now_time;

	while (1)
	{
		//bool b_video_play = vcap.read(src);
		for (int i = 0; i < 30; i++) {
			vcap.read(src);
			if (src.empty())
				break;
		}
		Mat imageBGR, imageHSV, planeH, planeS, planeV;
		vcap.read(src);
		if (src.empty())
			break;
		//imageBGR = imread("fruits.jpg");
		vcap.read(src);
		imshow("original", src);
		//cvtColor(src, src, CV_BGR2GRAY);
		Mat samples(src.rows * src.cols, 3, CV_32F);
		for (int y = 0; y < src.rows; y++)
			for (int x = 0; x < src.cols; x++)
				for (int z = 0; z < 3; z++)
					samples.at<float>(y + x*src.rows, z) = src.at<Vec3b>(y, x)[z];

		int clusterCount = 5;
		Mat labels;
		int attempts = 5;
		Mat centers;
		kmeans(samples, clusterCount, labels, TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 10, 0.1), attempts, KMEANS_PP_CENTERS, centers);
		Mat img_TresholdHSV;

		Mat new_image(src.size(), src.type());
		for (int y = 0; y < src.rows; y++)
			for (int x = 0; x < src.cols; x++)
			{
				int cluster_idx = labels.at<int>(y + x*src.rows, 0);
				new_image.at<Vec3b>(y, x)[0] = centers.at<float>(cluster_idx, 0);
				new_image.at<Vec3b>(y, x)[1] = centers.at<float>(cluster_idx, 1);
				new_image.at<Vec3b>(y, x)[2] = centers.at<float>(cluster_idx, 2);
			}
		//cvtColor(new_image, new_image, COLOR_BGR2GRAY);
		//threshold(new_image, new_image, 100, 255, CV_THRESH_BINARY);
		imshow("clustered image", new_image);
		//imshow("HSV imga", imgHSV);
		if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}

	}
}