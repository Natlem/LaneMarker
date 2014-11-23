#include "convert.hh"

void rgb2Ycbcr(cv::Mat& inputImg, cv::Mat& outputImg)
{
    for (unsigned int i = 0; i < inputImg.rows; ++i)
        for (unsigned int j = 0; j < inputImg.cols; ++j)
        {
            outputImg.at<cv::Vec3b>(i,j)[0] = (65.481 * inputImg.at<cv::Vec3b>(i,j)[2] + 128.553*inputImg.at<cv::Vec3b>(i,j)[1] + 24.966 * inputImg.at<cv::Vec3b>(i,j)[0]) + 16;
            outputImg.at<cv::Vec3b>(i,j)[0] = (-37.797 * inputImg.at<cv::Vec3b>(i,j)[2] - 74.203*inputImg.at<cv::Vec3b>(i,j)[1] + 112.0 * inputImg.at<cv::Vec3b>(i,j)[0]) + 128;
            outputImg.at<cv::Vec3b>(i,j)[0] = (112.0 * inputImg.at<cv::Vec3b>(i,j)[2] - 93.786*inputImg.at<cv::Vec3b>(i,j)[1] - 18.214 * inputImg.at<cv::Vec3b>(i,j)[0]) + 128;
        }
}

void rgb2Ycbcr2(cv::Mat& inputImg, cv::Mat& outputImg)
{
    cvtColor(inputImg, outputImg, CV_BGR2YCrCb);
}

void ycbcr2BGR(cv::Mat& inputimg, cv::Mat& outputImg)
{
    cvtColor(inputimg, outputImg,CV_YCrCb2BGR);
}
