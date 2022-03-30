#pragma once
#include"Lib.h"
#include"Blob_Detection.h"
#include"Harris_corner.h"
double matchBySIFT(const Mat& img1, const Mat& img2, int detector);