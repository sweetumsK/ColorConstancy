#pragma once
#include<opencv2\opencv.hpp>

using namespace cv;

class ColorMap {
public:
	static Mat GetColorMap(const Mat& inImage, const int inColorMapType);
private:
	ColorMap(const Mat& inImage, const int inColorMapType);
	~ColorMap();
	void ApplyColorMap();

	Mat mImage;
	Mat outImage;
	int mColorMapType;
};