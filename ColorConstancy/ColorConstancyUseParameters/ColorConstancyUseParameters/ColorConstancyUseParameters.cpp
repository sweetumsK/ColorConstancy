#pragma once

#include"ColorConstancyUseParameters.h"

cv::Mat ColorConstancy::Operate(const cv::Mat inImage, const ParametersList inParametersList) {
	ColorConstancy colorConstancy(inImage, inParametersList);
	colorConstancy.UseParameters();
	return colorConstancy.getDstImage();
}

ColorConstancy::ColorConstancy(const cv::Mat inImage, const ParametersList inParametersList) 
	: mImage(inImage), mParametersList(inParametersList) {
	if (mImage.channels() == 4) cv::cvtColor(mImage, mImage, CV_RGBA2RGB);
}
ColorConstancy::~ColorConstancy() {}

void ColorConstancy::UseParameters() {
	cv::Mat mYCrCb;
	std::vector<cv::Mat> mChannels;

	cv::cvtColor(mImage, mYCrCb, CV_RGB2YCrCb);
	cv::split(mYCrCb, mChannels);
	for (int index = 0; index < 3; ++index)
		cv::addWeighted(mChannels[index], mParametersList[index], 0, 0, 0, mChannels[index]);
	cv::merge(mChannels, mYCrCb);
	cv::cvtColor(mYCrCb, mImage, CV_YCrCb2RGB);
	cv::cvtColor(mImage, outImage, CV_RGB2RGBA);
}

cv::Mat ColorConstancy::getDstImage() {
	return outImage;
}