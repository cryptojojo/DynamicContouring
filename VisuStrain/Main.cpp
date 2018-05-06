#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <fstream>
#include <opencv2\features2d\features2d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <cmath>
#include <iomanip>

#include "VisuStrain.h"

using namespace cv;
using namespace std;


int main()
{

	string numDigits(int number);
	VisuStrain visu;

	//writeOut.open("StrainOut.csv");

	visu.setAndOpenOutFile("Data/Run2_middle.csv");


	bool if_first = true;

	VideoCapture capture("C:/Users/Joe/Desktop/in.avi");
	int totalFrameNumber = capture.get(CV_CAP_PROP_FRAME_COUNT);
	Mat currentFrame;
	Mat runPic;
	vector<Mat> frame;
	float gage_length = 0;
	capture >> currentFrame;
	int picNum = 0;
	string picName;


	//run(currentFrame, 0, if_first, gage_length); // GETS THE FIRST ONE


	//visu.run(currentFrame, 0, if_first, gage_length);

	if_first = false;

	namedWindow("Contour", WINDOW_AUTOSIZE);

	for (int i = 0; i < 162658 + 1; i++)
	{
		//cout << setfill(0) << setw(4) << 23;


		picName = "C:/Users/Joe/Desktop/STA_18032/Run2/STA_10832_C538_80C_LTCP_1_save_2018-04-28-120011-";

		picName += numDigits(picNum);
		picName += to_string(picNum);
		picName += ".tif";


		picNum++;

		cout << endl << endl << picName << endl << endl;



		currentFrame = imread(picName);



		runPic = visu.run(currentFrame, i, if_first, gage_length);

		imshow("Contour", runPic);
		waitKey(10);
	}

	//cout << endl << endl << "total amount of frames: " << capture.get(CV_CAP_PROP_FRAME_COUNT) << endl << endl;

	return 0;
}


string numDigits(int number) {

	string retStr = "";
	int digits = 0;

	if (number == 0)
		return "000";

	if (number >= 1000)
		return "";

	while (number) {
		number /= 10;
		digits++;
	}

	for (int i = 0; i < 4 - digits; i++)
		retStr += '0';

	return retStr;
}