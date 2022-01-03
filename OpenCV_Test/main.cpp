#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include "VirtualPainter.cpp"

using namespace cv;
using namespace std;


VideoCapture cap(0);


int main(){
    
    Mat img;
    
    VirtualPainter *vp = new VirtualPainter(img);

    while (true) {

        
    cap.read(img);
        
    vector<vector<int>> newPoints = vp->getNewPoints();
        
    newPoints = vp->findColor(img);
        
    vp->drawOnCanvas(newPoints, vp->getMyColorValues());

    imshow("Image", vp->getImg());
        
    waitKey(1);
        
    }
    
    free(vp);
}
