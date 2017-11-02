#pragma once
#include <opencv2\opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

class ColorConstancy {
public:
	static Mat MatchColor(const Mat& inFirstImage, const Mat& inSecondImage);
private:
	ColorConstancy(const Mat& inFirstImage, const Mat& inSecondImage);
	~ColorConstancy();
	void ApplyHistogram();
	void GetHistogram(const Mat& image, MatND& hist);
	void StretchHist(Mat& image, const MatND& refHist, const MatND& srcHist);
	void SetLookUpTable(Mat& lut, const MatND& refHist, const MatND& srcHist);
	void GetCumulatedHist(const int area, const MatND& hist, Mat& cumulatedHist);
	void GetHistImage(const MatND& hist, Mat& image, const int index);

	const int PARAM_LOW_COLOR_LIMIT = 0;
	const int PARAM_UP_COLOR_LIMIT = 256;

	vector<Mat> mFirstImage;
	vector<Mat> mSecondImage;
	vector<Mat> mSrcImage;
	Mat outImage;
};