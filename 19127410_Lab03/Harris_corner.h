#pragma once
#include"Lib.h"
#include"Utils.h"

int gaussianBlur(const Mat& src, Mat& dst, int size, float sigma);
pair<Mat, Mat> computeGradients(const Mat& src);

Mat detectHarris(const Mat& src, float k, float thres);
Mat computeReponseMatrix(const Mat& src, pair<Mat, Mat> gradients, float k, float thres);
vector<pair<int, int>> coordOfLocalMaxima(const Mat& reponseMatrix, float thres);
Mat mapCornerToImage(const Mat& src, vector<pair<int, int>> cornerCoord);
