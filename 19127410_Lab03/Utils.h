#pragma once
#include"Lib.h"



vector<float> gaussKernel(int size, float sigma);
pair<vector<float>, vector<float>> sobelKernel();

float computeConvolution(vector<float>kernel, vector<uchar> data);



vector<uchar> createEmptyVector(int size, uchar value);

