#pragma once
#include <opencv2\opencv.hpp>

using namespace cv;

class ColorConstancy {
public:
	static Mat Operate(Mat inRefImage, Mat inSrcImage);
private:
	ColorConstancy(Mat inRefImage, Mat inSrcImage);
	~ColorConstancy();
	void UniformColor();
	void UniformColorHSV();
	Mat getImage();

	Mat mRefImage;
	Mat mSrcImage;
	Mat mDstImage;
	int mWidth;
	int mHeight;
};