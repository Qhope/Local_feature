#pragma once
#include"Lib.h"
pair<uchar, Point> localMax(vector<pair<uchar, Point>> source);
Mat detectBlob(const Mat& img);

Mat detectDOG(const Mat& img);