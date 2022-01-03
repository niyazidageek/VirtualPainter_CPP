#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include "IVirtualPainter.cpp"
#include <iostream>

using namespace cv;
using namespace std;

class VirtualPainter: public IVirtualPainter{
    
    Mat img;
    
    vector<vector<int>> newPoints;

    vector<vector<int>> myColors;

    vector<Scalar> myColorValues;
    
private:
    Point getContours(Mat image) override{
        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;

        findContours(image, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        drawContours(this->img, contours, -1, Scalar(255, 0, 255), 2);

        vector<vector<Point>> conPoly(contours.size());
        vector<Rect> boundRect(contours.size());

        Point myPoint(0,0);

        for (int i=0; i<contours.size(); i++) {
            int area = contourArea(contours[i]);

            string objectType;

            if(area>1000){
                float peri = arcLength(contours[i], true);
                approxPolyDP(contours[i], conPoly[i], 0.02*peri, true);
                boundRect[i] = boundingRect(conPoly[i]);
                myPoint.x = boundRect[i].x + boundRect[i].width/2;
                myPoint.y = boundRect[i].y;

                drawContours(this->img, conPoly, i, Scalar(255, 0, 255), 2);
                rectangle(this->img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
            }
        }
        return myPoint;
    }
    
public:
    
    VirtualPainter(Mat img){
        this->myColors = {
            {124, 48, 117, 143, 170, 255},
            {68, 72, 156, 102, 126, 255}
        };
        
        this->myColorValues = {
            {255, 0, 255},
            {0,255,0}
        };
        
        this->img = img;
    }
    
    vector<vector<int>> getNewPoints() {return newPoints;};
    
    vector<vector<int>> getMyColors() {return  myColors;};
    
    vector<Scalar> getMyColorValues() {return myColorValues;};
    
    Mat getImg() {return img;};
    
    vector<vector<int>> findColor(Mat img) override{
        this->img = img;
        Mat imgHSV;
        cvtColor(this->img, imgHSV, COLOR_BGR2HSV);

        for (int i=0; i<myColors.size(); i++) {
            Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
            Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);
            Mat mask;
            inRange(imgHSV, lower, upper ,mask);

            Point myPoint = getContours(mask);

            if(myPoint.x !=0){
                newPoints.push_back({myPoint.x, myPoint.y, i});
            }
        }

        return newPoints;
    }
    
    void drawOnCanvas(vector<vector<int>> newPoints, vector<Scalar> myColorValues) override{
        for (int i=0; i<newPoints.size(); i++) {
            circle(this->img, Point(newPoints[i][0], newPoints[i][1]), 10, myColorValues[newPoints[i][2]], FILLED);
        }
    }
};
