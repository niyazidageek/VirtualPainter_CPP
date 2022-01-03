#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>


using namespace cv;
using namespace std;

class IVirtualPainter{
    
    vector<vector<int>> newPoints;

    vector<vector<int>> myColors;

    vector<Scalar> myColorValues;

    
public:
    
    virtual Point getContours(Mat image)=0;
    
    virtual vector<vector<int>> findColor(Mat img)=0;
    
    virtual void drawOnCanvas(vector<vector<int>> newPoints, vector<Scalar> myColorValues)=0;
    
 
};
