#pragma once
#include "ColorConstancy.h"

Mat ColorConstancy::Operate(const cv::Mat inRefImage,const cv::Mat inSrcImage) {
	ColorConstancy colorConstancy(inRefImage, inSrcImage);
	colorConstancy.UniformColorHSV();
	colorConstancy.UniformColor();
	return colorConstancy.getImage();
}

ColorConstancy::ColorConstancy(const cv::Mat inRefImage,const cv::Mat inSrcImage)
	: mRefImage(inRefImage),
	  mSrcImage(inSrcImage),
	  mWidth(inRefImage.cols), 
	  mHeight(inRefImage.rows) {
	mDstImage.create(mHeight, mWidth, inRefImage.type());
}

ColorConstancy::~ColorConstancy() {}

void ColorConstancy::UniformColorHSV() {
	cv::Mat mRefHSV, mSrcHSV;
	std::vector<cv::Mat> refChannels, srcChannels;
	std::vector<double> refChannelAvg(3), srcChannelAvg(3), refK(4, 0), srcK(4, 0);

	cv::cvtColor(mRefImage, mRefHSV, CV_RGB2YCrCb);
	cv::cvtColor(mSrcImage, mSrcHSV, CV_RGB2YCrCb);

	cv::split(mRefHSV, refChannels);
	cv::split(mSrcHSV, srcChannels);

	for (int index = 0; index < 3; ++index) {
 		refChannelAvg[index] = mean(refChannels[index])[0];
		srcChannelAvg[index] = mean(srcChannels[index])[0];
		cv::addWeighted(srcChannels[index], refChannelAvg[index] / srcChannelAvg[index], 0, 0, 0, srcChannels[index]);
	}
	cv::merge(srcChannels, mSrcHSV);
	cv::cvtColor(mSrcHSV, mSrcImage, CV_YCrCb2RGB);
}

void ColorConstancy::UniformColor() {
	std::vector<cv::Mat> refChannels, srcChannels; 
	std::vector<double> refChannelAvg(3), srcChannelAvg(3), refK(4, 0), srcK(4, 0);
	cv::Mat temp;
	
	cv::split(mRefImage, refChannels);
	cv::split(mSrcImage, srcChannels);

	for (int index = 0; index < 3; ++index) {
		refChannelAvg[index] = mean(refChannels[index])[0];
		srcChannelAvg[index] = mean(srcChannels[index])[0];
		refK[3] = refK[3] + refChannelAvg[index];
		srcK[3] = srcK[3] + srcChannelAvg[index];
	}

	for (int index = 0; index < 3; ++index) {
		refK[index] = refK[3] / refChannelAvg[index];
		srcK[index] = srcK[3] / srcChannelAvg[index];
		//cv::addWeighted(srcChannels[index], refK[index] / srcK[index], 0, 0, 0, srcChannels[index]);
	}

	cv::merge(srcChannels, temp);
	cv::cvtColor(temp, mDstImage, CV_BGR2BGRA);
}

Mat ColorConstancy::getImage() { return mDstImage; }