#include <iostream>
#include <opencv2/opencv.hpp>
#include "colorConversion.h"
#include "segmentation.h"
using namespace std;
using namespace cv;
using namespace colorconversion;
using namespace segmentation;


int main()
{

	
	
	cv::Mat ihls_image;
	cv::Mat input_image = imread("bienbao.jpg");
	colorconversion::convert_rgb_to_ihls(input_image, ihls_image);
	
	std::vector< cv::Mat > log_image;
	colorconversion::rgb_to_log_rb(input_image, log_image);
	int nhs_mode = 0; // nhs_mode == 0 -> red segmentation / nhs_mode == 1 -> blue segmentation
	cv::Mat nhs_image_seg_red;
	segmentation::seg_norm_hue(ihls_image, nhs_image_seg_red, nhs_mode);
	
	nhs_mode = 1; // nhs_mode == 0 -> red segmentation / nhs_mode == 1 -> blue segmentation
	
	cv::Mat nhs_image_seg_blue = nhs_image_seg_red.clone();
	segmentation::seg_norm_hue(ihls_image, nhs_image_seg_blue, nhs_mode);
	
	cv::Mat log_image_seg;
	segmentation::seg_log_chromatic(log_image, log_image_seg);
		
	cv::Mat merge_image_seg_with_red = nhs_image_seg_red.clone();
    cv::Mat merge_image_seg = nhs_image_seg_blue.clone();
    cv::bitwise_or(nhs_image_seg_red, log_image_seg, merge_image_seg_with_red);
    cv::bitwise_or(nhs_image_seg_blue, merge_image_seg_with_red, merge_image_seg);
	//imshow("result",merge_image_seg) ;
	waitKey(0);
return  0;
}


