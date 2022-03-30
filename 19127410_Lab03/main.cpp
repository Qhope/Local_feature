

#include"Utils.h"
#include"Harris_corner.h"
#include"Blob_Detection.h"
#include"Sift.h"
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
	Mat src1 = imread(".\\training_set\\training_images\\01_1.jpg", IMREAD_ANYCOLOR);
	Mat src2 = imread(".\\training_set\\training_images\\01_2.jpg", IMREAD_ANYCOLOR);


	imshow("src1", src1);

	imshow("src2", src2);

	matchBySIFT(src1, src2, 1);

	//cvtColor(src, src_gray, COLOR_BGR2GRAY);
	//imshow("src", src);
	//Mat src1 = imread("06.jpg", IMREAD_ANYCOLOR);
	Mat dst, gaussCV;
	//dst = detectHarris(src1, 0.05, 100);
	//dst = detectBlob(src);
	//dst = detectDOG(src);
	//imshow("Blob", dst);
	waitKey(0);
}