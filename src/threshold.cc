#include "threshold.hh"

void thresholding(cv::Mat& input, int threshold)
{
    for (auto i = 0; i < input.rows; ++i)
        for (auto j = 0; j < input.cols; ++j)
        {
            if (input.at<cv::Vec3b>(i,j)[0] < threshold)
            {
                input.at<cv::Vec3b>(i,j)[0] = 0;
                input.at<cv::Vec3b>(i,j)[1] = 0;
                input.at<cv::Vec3b>(i,j)[2] = 0;
            }
        }
}
