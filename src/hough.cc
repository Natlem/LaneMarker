#include "hough.hh"
#include <iostream>

std::vector<cv::Vec4i> houghT(cv::Mat& input, cv::Mat& output, int threshold, bool debug)
{
    std::vector<cv::Vec4i> tmp;
    cv::Mat dst, cdst;
    std::vector<cv::Vec4i> allLines;
    cv::Canny(input, dst, 50, 200, 3);
    cvtColor(dst, output, CV_GRAY2BGR);
    HoughLinesP(dst, allLines, 1, CV_PI/180, threshold, 20,10);
    if (!debug)
    {
        removeHorLine(allLines);
        tmp = getLanes(allLines, input.cols, input.rows);
        if (getIntersect(tmp[0], tmp[1]).y > 5.5 * (double) input.rows / 10)
            tmp = getLanesI(allLines, input.cols, input.rows);
        allLines = tmp;
        extendLines(allLines, input.rows);
    }
    if (false)
    {
        allLines.push_back(cv::Vec4i(input.cols / 2, 0, input.cols /2, input.rows));
    }
    for (size_t i = 0; i < allLines.size(); i++ )
    {
        cv::Vec4i l = allLines[i];
        cv::line( output, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0,0,255), 3, CV_AA);
    }
    return allLines;
}

void extendLines(std::vector<cv::Vec4i>& v, int height)
{
    cv::Point tmp;
    for (auto& c : v)
    {
        tmp = getIntersect(c, height);
        if (c[1] > c[3])
        {
            c[0] = tmp.x;
            c[1] = tmp.y;
        }
        else
        {
            c[2] = tmp.x;
            c[3] = tmp.y;
        }
    }
}

void removeHorLine(std::vector<cv::Vec4i>& v)
{
    auto isUnder = [] (cv::Vec4i& l) 
    { 
        double angle = abs(atan2(l[3] - l[1], l[2] - l[0]) * 180 / CV_PI); 
        if (abs(angle) >= 10) 
            return false; 
        else 
            return true;
    };

    v.erase(std::remove_if(v.begin(), v.end(), isUnder), v.end());
}

void removeShort(std::vector<cv::Vec4i>& lines)
{
    auto isShort = [] (cv::Vec4i& c) 
    { 
        if (sqrt(pow(c[2] - c[0],2) + pow(c[3] - c[1],2)) > 100) 
            return false; 
        else 
            return true;
    };
    lines.erase(std::remove_if(lines.begin(), lines.end(), isShort), lines.end());

}

std::vector<cv::Vec4i> getLanesI(std::vector<cv::Vec4i>& lines, int width, int height)
{
    cv::Point tmp;
    unsigned int i = 0;
    cv::Vec4i left;
    cv::Vec4i right;
    double minL = std::numeric_limits<double>::max();
    double minR = std::numeric_limits<double>::max();
    double currentDis = 0;
    cv::Point currentCen;
    cv::Point botC = cv::Point(width / 2, 7 * height / 10);
    cv::Point lowest;
    std::vector<cv::Vec4i> res;
    removeShort(lines);
    do
    {
        //Left
        for (i = 0; i < lines.size(); ++i)
        {
            currentCen = getCenter(lines[i]);
            lowest = lowestPts(lines[i]);
            currentDis = distance(currentCen, botC);

            if (lowest.x < width / 2 && currentDis < minL)
            {
                minL = currentDis;
                left = lines[i];
            }
        }
        if (lines.size() != 0)
            lines.erase(lines.begin() + i);
        //Right
        for (i = 0; i < lines.size(); ++i)
        {
            currentCen = getCenter(lines[i]);
            lowest = lowestPts(lines[i]);
            currentDis = distance(currentCen, botC);

            if (lowest.x > width / 2 && currentDis < minR) 
            {
                minR = currentDis;
                right = lines[i];
            }
        }
        if (lines.size() != 0)
            lines.erase(lines.begin() + i);
        minL = std::numeric_limits<double>::max();
        minR = std::numeric_limits<double>::max();
        tmp = getIntersect(left,right);
    } while(!lines.empty() && tmp.y > 8 *(double) height / 10);
    res.push_back(left);
    res.push_back(right);
    return res;
}

std::vector<cv::Vec4i> getLanes(std::vector<cv::Vec4i> lines, int width , int height)
{
    cv::Vec4i left;
    cv::Vec4i right;
    double minL = std::numeric_limits<double>::max();
    double minR = std::numeric_limits<double>::max();
    double currentDis = 0;
    cv::Point currentCen;
    cv::Point botC = cv::Point(width / 2, 9 * height / 10);
    cv::Point lowest;
    std::vector<cv::Vec4i> res;
    auto isShort = [] (cv::Vec4i& c) 
    { 
        if (sqrt(pow(c[2] - c[0],2) + pow(c[3] - c[1],2)) > 100) 
            return false; 
        else 
            return true;
    };
    lines.erase(std::remove_if(lines.begin(), lines.end(), isShort), lines.end());
    for (auto c : lines)
    {
        currentCen = getCenter(c);
        lowest = lowestPts(c);
        currentDis = distance(currentCen, botC);
        if (lowest.x < width / 2 && currentDis < minL)
        {
            minL = currentDis;
            left = c;
        }
        else if (lowest.x > width / 2 && currentDis < minR) 
        {
            minR = currentDis;
            right = c;
        }
    }
    res.push_back(left);
    res.push_back(right);
    return res; 
}

cv::Point lowestPts(cv::Vec4i& c)
{
    cv::Point res;
    if (c[1] > c[3])
    {
        res = cv::Point(c[0],c[1]);
        return res;
    }
    res = cv::Point(c[2],c[3]);
    return res;
}

cv::Point getCenter(cv::Vec4i& c)
{
    return cv::Point((c[0] + c[2]) / 2, (c[1] + c[3]) /2);
}

double distance(cv::Point& p1, cv::Point& p2)
{
    return cv::norm(p1-p2);
}
