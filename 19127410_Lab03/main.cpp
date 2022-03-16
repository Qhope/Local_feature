

#include"Utils.h"
#include"Harris_corner.h"
Mat src, src_gray;
int thresh = 200;
int max_thresh = 255;
const char* source_window = "Source image";
const char* corners_window = "Corners detected";
void cornerHarris_demo(int, void*);

void cornerHarris_demo(int, void*)
{
	int blockSize = 2;
	int apertureSize = 3;
	double k = 0.04;
	Mat dst = Mat::zeros(src.size(), CV_32FC1);
	cornerHarris(src_gray, dst, blockSize, apertureSize, k);
	Mat dst_norm, dst_norm_scaled;
	normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	convertScaleAbs(dst_norm, dst_norm_scaled);
	for (int i = 0; i < dst_norm.rows; i++)
	{
		for (int j = 0; j < dst_norm.cols; j++)
		{
			if ((int)dst_norm.at<float>(i, j) > thresh)
			{
				circle(dst_norm_scaled, Point(j, i), 5, Scalar(0), 2, 8, 0);
			}
		}
	}
	namedWindow(corners_window);
	imshow(corners_window, dst_norm_scaled);
}

int main() {
	Mat src = imread("06.jpg", IMREAD_ANYCOLOR);
	cvtColor(src, src_gray, COLOR_BGR2GRAY);


	namedWindow(source_window);
	createTrackbar("Threshold: ", source_window, &thresh, max_thresh, cornerHarris_demo);
	imshow(source_window, src);
	cornerHarris_demo(0, 0);

	//waitKey();
	//return 0;

	Mat src1 = imread("06.jpg", IMREAD_ANYCOLOR);
	Mat dst, gaussCV;
	//GaussianBlur(src, gaussCV, Size(5, 5), 1.0);

	//gaussianBlur(src, dst, 5, 1.0);
	//imshow("gaussCV", gaussCV);
	//imshow("my gauss", dst);
	dst = detectHarris(src1, 0.05, 100);
	waitKey(0);
}