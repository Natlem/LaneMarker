#include "convert.hh"
#include "detectEdge.hh"
#include "threshold.hh"

int main(int argc, char** argv)
{
    cv::Mat input = cv::imread(argv[1],CV_LOAD_IMAGE_COLOR);
    cv::bitwise_not(input,input);
    cv::Mat dst = input;
    rgb2Ycbcr2(input, dst);
    sobelDetect(dst,dst);
    thresholding(dst, 50);
    //ycbcr2BGR(dst,dst);
    cv::imwrite("out.png",dst);
    return 0;
}
