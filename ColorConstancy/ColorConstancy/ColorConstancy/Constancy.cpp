// Constancy.cpp : Defines the entry point for the console application.
//
#pragma once
#include <cstring>
#include "ColorConstancy.h"

using namespace std;

int main()
{
	VideoCapture refCap("DSCF0037.mov");
	VideoCapture srcCap("DSCF0038.mov");
	int srcFrames = srcCap.get(CAP_PROP_FRAME_COUNT);

	Mat ref, src, dst;

	//refCap >> ref;
	//srcCap >> src;
	for (int i = 0; i < srcFrames / 50; ++i) {
		if (refCap.read(ref)) imwrite("DSCF0037_" + to_string(i) + ".jpg", ref);
		for (int n = 50; n ; n--) if (!refCap.read(ref)) break;
		if (srcCap.read(src)) imwrite("DSCF0038_" + to_string(srcFrames / 50 - i) + ".jpg", src);
		for (int n = 50; n ; n--) if (!srcCap.read(src)) break;
		dst = ColorConstancy::Operate(ref, src);
	}
	imwrite("final.jpg", dst);
    return 0;
}

