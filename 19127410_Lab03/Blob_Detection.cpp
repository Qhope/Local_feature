#include"Blob_Detection.h"

pair<uchar, Point> localMax(vector<pair<uchar, Point>> source)
{
	pair<uchar, Point> max = source[0];
	for (int i = 1; i < source.size(); i++)
	{
		if (source[i].first > max.first)
		{
			max = source[i];
		}
	}
	return max;
}

Mat detectBlob(const Mat& img)
{
	if (!img.data) {
		return Mat();
	}
	Mat img_gray;
	cvtColor(img, img_gray, COLOR_BGR2GRAY);

	vector<Mat> scaleSpace;
	Mat scaleImg, normImg;
	double k = 1.414;
	double sigma = 1.0;

	for (int i = 0; i <= 9; i++)
	{
		Laplacian(img_gray, scaleImg, CV_16S, 3, pow(k, i) * sigma);
		normalize(scaleImg, normImg, 0, 255, NORM_MINMAX, CV_8UC1);
		scaleSpace.push_back(normImg);
	}
	//Scale - Space size of 5x5

	int width = img_gray.cols;
	int height = img_gray.rows;
	int widthStep = img_gray.step[0];
	int nChannel = img_gray.step[1];

	vector<Vec3d> blobPoint;
	for (int y = 1; y < height - 2; y += 2)
	{
		for (int x = 1; x < width - 2; x += 2)
		{
			double max = 0.0;
			int maxIndex = 0;
			double localMax;
			Point maxLocate, localMaxLocate;

			for (int i = 0; i < scaleSpace.size(); i++)
			{

				minMaxLoc(scaleSpace[i](Range(y - 1, y + 2), Range(x - 1, x + 2)), NULL, &localMax, NULL, &localMaxLocate);
				if (localMax > max)
				{
					max = localMax;
					maxIndex = i;
					maxLocate = localMaxLocate;
				}
				//cout << x << " " << y << endl;
			}

			if (max > 200)
			{
				blobPoint.push_back({ (double)x + maxLocate.x,(double)y + maxLocate.y,pow(k,maxIndex * sigma) });
			}

		}
	}

	Mat dst = img.clone();
	for (int i = 0; i < blobPoint.size(); i++)
	{
		Point p;
		p.y = blobPoint[i][1];
		p.x = blobPoint[i][0];
		circle(dst, p, blobPoint[i][2] * 1.414, Scalar(0, 0, 255), 0);
	}


	return dst;
}

Mat detectDOG(const Mat& img)
{
	Mat img_gray;
	cvtColor(img, img_gray, COLOR_BGR2GRAY);

	double k = 1.2;
	double sigma = 1.2;
	int scaleNumber = 10;
	vector<Mat> dogSpace;
	Mat currentGauss, previousGauss;
	double gaussSigma = pow(k, 0);
	GaussianBlur(img_gray, previousGauss, Size(0, 0), gaussSigma, gaussSigma);
	int width = img_gray.cols;
	int height = img_gray.rows;

	for (int i = 1; i < scaleNumber; i++)
	{
		Mat dog;
		gaussSigma = pow(k, i);
		GaussianBlur(img_gray, currentGauss, Size(0, 0), gaussSigma, gaussSigma);

		double min, max;
		cv::minMaxLoc(currentGauss, &min, &max);

		dog = currentGauss - previousGauss;
		cv::minMaxLoc(dog, &min, &max);

		dog = dog.mul(dog);
		cv::minMaxLoc(dog, &min, &max);

		dogSpace.push_back(dog);

		previousGauss.release();
		previousGauss = currentGauss;
		currentGauss.release();

	}

	vector<Vec3d> blobPoints;
	//height 991
	//width 1600
	for (int y = 1; y < height - 2; y += 2) {
		for (int x = 1; x < width - 2; x += 2) {
			double max = 0.0;
			int maxIndex = 0;
			double localMax;
			Point maxLocate, localMaxLocate;

			for (int i = 0; i < dogSpace.size(); i++)
			{

				minMaxLoc(dogSpace[i](Range(y - 1, y + 2), Range(x - 1, x + 2)), NULL, &localMax, NULL, &localMaxLocate);
				if (localMax > max)
				{
					max = localMax;
					maxIndex = i;
					maxLocate = localMaxLocate;
				}
				//cout << x << " " << y << endl;
			}
			/*if (max > 1) {
				cout << "max" << max << endl;
			}*/
			if (max > 100)
			{
				blobPoints.push_back({ (double)x + maxLocate.x,(double)y + maxLocate.y,pow(k,(maxIndex + 1) * sigma) });
			}
		}
	}

	Mat dst = img.clone();

	for (int i = 0; i < blobPoints.size(); i++)
	{
		Point p;
		p.y = blobPoints[i][1];
		p.x = blobPoints[i][0];
		circle(dst, p, blobPoints[i][2] * 1.414, Scalar(0, 0, 255), 0);
	}

	/*imshow("Dog", dst);
	waitKey(0);*/

	return dst;
}


