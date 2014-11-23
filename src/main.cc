#include "convert.hh"
#include "detectEdge.hh"

int main(int argc, char** argv)
{
    cv::Mat input = cv::imread(argv[1],CV_LOAD_IMAGE_COLOR);
    cv::Mat dst = input;
    rgb2Ycbcr2(input, dst);
    sobelDetect(dst,dst);
    //ycbcr2BGR(dst,dst);
    cv::imwrite("out.png",dst);
    return 0;
}
