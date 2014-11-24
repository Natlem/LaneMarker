#include "csvOut.hh"

void parseDir(std::string dirStr, std::string dstFile)
{
    DIR* imageDir = NULL;
    std::ofstream outFile;
    outFile.open(std::move(dstFile), std::fstream::out | std::fstream::trunc);
    if (outFile.is_open())
    {
        if ((imageDir = opendir(dirStr.c_str())) != nullptr)
        {
            struct dirent *file;
            while ((file = readdir(imageDir)) != nullptr)
            {
                if (file->d_name[0] != '.')
                {
                    std::string filename(file->d_name);
                    writeLine(filename, getLanes(dirStr + filename), outFile);
                }
            }
        }
    }
}

std::pair<double, double> getLanes(std::string str)
{
    cv::Mat input = cv::imread(str.c_str(), CV_LOAD_IMAGE_COLOR);
    cv::Mat dst = input;
    rgb2Ycbcr(input, dst);
    sobelDetect(dst, dst);
    thresholding(dst, 50);
    std::vector<cv::Vec4i> v = houghT(dst,dst, 100);
    return std::pair<double, double>(lowestPts(v[0]).x, lowestPts(v[1]).x);
}

void writeLine(std::string& str, std::pair<double, double> pair, std::ofstream& out)
{
    std::string line;
    line = str;
    line.push_back(',');
    line.append(std::to_string(pair.first));
    line.push_back(',');
    line.append(std::to_string(pair.second));
    out << line << std::endl;
}
