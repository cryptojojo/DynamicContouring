#include "VisuStrain.h"

Mat VisuStrain::imageToBinary(Mat start)
{
	Mat gray_image, thresh_image;
	cvtColor(start, gray_image, CV_BGR2GRAY);
	threshold(gray_image, thresh_image, 100, 255, THRESH_BINARY);

	medianBlur(thresh_image, thresh_image, 5);

	return thresh_image;
}



vector<vector<Point>> VisuStrain::getContours(Mat start)
{
	Mat dst = Mat::zeros(start.rows, start.cols, CV_8UC3);
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	start = start > 1;

	findContours(start, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

	return contours;
}


vector<Point2f> VisuStrain::getMassCenters(vector<vector<Point>> contours)
{
	vector<Moments> mu(contours.size());
	vector<Point2f> mc(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		mu[i] = moments(contours[i], false);
	}

	for (int i = 0; i < contours.size(); i++) {
		mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
	}

	return mc;
}


void VisuStrain::printMassCenters(vector<Point2f> mc, vector<vector<Point>> contours)
{
	cout << "Mass Centers:" << endl;


	float lowest = 0;


	for (int i = 0; i < contours.size(); i++)
	{
		//float lowest = 99999; // gets the lowest center (largest number)

		if (mc[i].y > lowest)
			lowest = mc[i].y;


		cout << mc[i] << endl;
	}

	cout << endl << "Lowest px : " << lowest << endl;
	cout << endl << "Lowest mm : " << lowest*.105833333 << endl;


	counter++;
	writeOut << counter << ", " << lowest*.105833333 << endl;



	//float distance = sqrt(pow(mc[0].x - mc[1].x, 2) + pow(mc[0].y - mc[1].y, 2));
	//writeOut << distance << "},";
}

/*
float VisuStrain::getStrain(float gage_length, vector<Point2f> two_points) {

	float diff = two_points[0].y - two_points[1].y;

	float answ = (diff / gage_length) - 1;

	return answ;
}
*/

Mat VisuStrain::run(Mat image, int count, int if_first, float& gage_length) {

	vector<Point2f> mc;
	vector<vector<Point>> contours;
	Mat original = image;

	// sub image
	Mat subImage(image, Rect(870, 0, 550, 700));
	image = subImage;
	original = subImage;
	//

	image = imageToBinary(image);

	contours = getContours(image);	// get the contours 

	mc = getMassCenters(contours);		// get the mass centers

	//writeOut << "{" << count << ", ";
	printMassCenters(mc, contours);		// print mass centers

	/*
	if (if_first)
	{
		gage_length = mc[0].y - mc[1].y;
		//cout << endl << endl << "GAGE LENGTH SET TO: " << gage_length << endl << endl;
	}
	*/
	//float strain = getStrain(gage_length, mc);
	//cout << "Strain:  " << strain << endl << endl;

	//waitKey(0);

	for (int i = 0; i < contours.size(); i++) {
		circle(original, mc[i], 1, CV_RGB(255, 0, 0), 3, 8, 0);
		circle(image, mc[i], 1, CV_RGB(255, 0, 0), 3, 8, 0);
	}

	// image shows thresh, originalk shows input image
	return original;
}

void VisuStrain::setAndOpenOutFile(String outFileName)
{
	writeOut.open(outFileName);
}

void VisuStrain::closeOutFile()
{
	writeOut.close();
}

