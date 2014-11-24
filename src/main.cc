#include "csvOut.hh"

int main(int argc, char** argv)
{
    if (argc == 2)
    {
        cv::Mat input = cv::imread(argv[1],CV_LOAD_IMAGE_COLOR);
        cv::Mat dst = input;
        rgb2Ycbcr2(input, dst);
        sobelDetect(dst,dst);
        thresholding(dst, 50);
        houghT(dst,dst,100, !true);
        cv::imwrite("out.png",dst);
    }
    if (argc == 3)
        parseDir(argv[1], argv[2]);
    //argv[1] == input directory
    //argv[2] == output csv
    return 0;
}
