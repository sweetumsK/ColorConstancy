#include"ColorConstancyGetParameters.h"

ParametersList ColorConstancyParameters::Operate(const cv::Mat inRefImage, const cv::Mat inSrcImage) {
	ColorConstancyParameters colorConstancyParameters(inRefImage, inSrcImage);
	colorConstancyParameters.CalculateParameters();
	return colorConstancyParameters.GetParametersList();
}

ColorConstancyParameters::ColorConstancyParameters(const cv::Mat inRefImage, const cv::Mat inSrcImage) 
	: mRefImage(inRefImage), mSrcImage(inSrcImage), parametersList(3,0) {
	if (mRefImage.channels() == 4) cv::cvtColor(inRefImage, mRefImage, CV_RGBA2RGB);
	if (mSrcImage.channels() == 4) cv::cvtColor(inSrcImage, mRefImage, CV_RGBA2RGB);
}

ColorConstancyParameters::~ColorConstancyParameters() {}

void ColorConstancyParameters::CalculateParameters() {
	cv::Mat mRefYCrCb, mSrcYCrCb;
	std::vector<cv::Mat> refChannels, srcChannels;
	std::vector<double> refChannelAvg(3), srcChannelAvg(3);

	cv::cvtColor(mRefImage, mRefYCrCb, CV_RGB2YCrCb);
	cv::cvtColor(mSrcImage, mSrcYCrCb, CV_RGB2YCrCb);

	cv::split(mRefYCrCb, refChannels);
	cv::split(mSrcYCrCb, srcChannels);

	for (int index = 0; index < 3; ++index) {
		refChannelAvg[index] = mean(refChannels[index])[0];
		srcChannelAvg[index] = mean(srcChannels[index])[0];
		parametersList[index] = refChannelAvg[index] / srcChannelAvg[index];
	}
}

ParametersList ColorConstancyParameters::GetParametersList() { return parametersList; }