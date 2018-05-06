#pragma once
#ifndef VISU_H
#define VISU_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <fstream>
#include <opencv2\features2d\features2d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <cmath>


using namespace cv;
using namespace std;


class VisuStrain {


private:
	int counter = 0;
	ofstream writeOut;

public:
	Mat imageToBinary(Mat);
	vector<vector<Point>> getContours(Mat);
	vector<Point2f> getMassCenters(vector<vector<Point>>);
	void printMassCenters(vector<Point2f>, vector<vector<Point>>);
	//float getStrain(float, vector<Point2f>);
	Mat run(Mat, int, int, float&);

	void setAndOpenOutFile(String);
	void closeOutFile();





};




#endif // !VISU_H

