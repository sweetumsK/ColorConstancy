#include "ColorMap.h"

Mat ColorMap::GetColorMap(const Mat& inImage, const int inColorMapType) {
	ColorMap colorMap(inImage, inColorMapType);
	colorMap.ApplyColorMap();
	return colorMap.outImage;
}

ColorMap::ColorMap(const Mat& inImage, const int inColorMapType) 
	: mImage(inImage), mColorMapType(inColorMapType)
{
}

ColorMap::~ColorMap() {}

void ColorMap::ApplyColorMap() {
	applyColorMap(mImage, outImage, mColorMapType);
}