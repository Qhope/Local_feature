#include"Sift.h"

double matchBySIFT(const Mat& img1, const Mat& img2, int detector)
{
	//Mat dog = detectDOG(img2);

	//Step 1: Detect the keypoints using SIFT Detector, compute the descriptors
	Ptr<SIFT> siftDetector = SIFT::create();

	vector<KeyPoint> keypoints1, keypoints2;
	Mat descriptors1, descriptors2;
	siftDetector->detectAndCompute(img1, noArray(), keypoints1, descriptors1);
	siftDetector->detectAndCompute(img2, noArray(), keypoints2, descriptors2);

	//Step 2: Matching descriptor with knn

	Ptr<DescriptorMatcher>matcher = DescriptorMatcher::create(DescriptorMatcher::FLANNBASED);
	vector< std::vector<DMatch> > knn_matches;
	matcher->knnMatch(descriptors1, descriptors2, knn_matches, 2);

	//-- Filter matches using the Lowe's ratio test
	const float ratio_thresh = 0.7f;
	std::vector<DMatch> good_matches;
	for (size_t i = 0; i < knn_matches.size(); i++)
	{
		if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance)
		{
			good_matches.push_back(knn_matches[i][0]);
		}
	}
	//-- Draw matches
	Mat img_matches;
	drawMatches(img1, keypoints1, img2, keypoints2, good_matches, img_matches, Scalar::all(-1),
		Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	//-- Show detected matches
	imshow("Good Matches", img_matches);
	waitKey();
	return 0;

}
