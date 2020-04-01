#ifndef MOILVIEW_H
#define MOILVIEW_H
#include <stdio.h>
#include <string.h>
#include <opencv2/opencv.hpp>
#include <sstream>
#include <string>
#include <time.h>
#include <iostream>
#include <fstream>
#include <termios.h>  
#include <unistd.h> 

#include "moildev.h"
using namespace std;
using namespace cv;

namespace Ui {
class Car6view;
class Panorama;
}

class Car6view 
{

public:
    Car6view();
    void Show();
    ~Car6view();


private:

    Moildev *md ;
    Mat image_input, image_input_s;
    Mat image_display[6];
    Mat mapX[6], mapY[6];
    double m_ratio;
    int x_base = 80;
    int y_base = 30;
    int fix_width = 2592;
    int fix_height = 1944;
    int currCh = 0, prevCh = 0;
    int currPara = 0;
    int currAlpha = 0;
    int currBeta = 0;
    int currInc = 10;    
    double currZoom = 4;
    double defaultZoom = 4;

    const double minZoom = 1;
    const double maxZoom = 12;
    int width_split = (1920-100)/3 ;
    int height_split = width_split*3/4 ;

    enum class MediaType {NONE, IMAGE_FILE, CAMERA, VIDEO_FILE };
    MediaType mediaType = MediaType::NONE;

    void DisplayCh(int Ch);
    void Rotate(Mat& src, Mat& dst, double angle);
    void MatWrite(const string& filename, const Mat& mat);
    Mat MatRead(const string& filename);
    void freeMemory();

};

class Panorama
{

public:
    Panorama();
    void Show();
    ~Panorama();


private:

    Moildev *md ;
    Mat image_input, image_input_s;
    Mat image_display[0];
    Mat mapX[1], mapY[1];
    double m_ratio;
    int x_base = 80;
    int y_base = 30;
    int fix_width = 2592;
    int fix_height = 1944;
    int currCh = 0, prevCh = 0;
    int currPara = 0;
    int currAlpha = 0;
    int currBeta = 0;
    int currInc = 10;
    double currZoom = 4;
    double defaultZoom = 4;

    const double minZoom = 1;
    const double maxZoom = 12;
    int width_split = (1920-100)/3 ;
    int height_split = width_split*3/4 ;

    enum class MediaType {NONE, IMAGE_FILE, CAMERA, VIDEO_FILE };
    MediaType mediaType = MediaType::NONE;
    void DisplayCh(int Ch);
    void Rotate(Mat& src, Mat& dst, double angle);
    void MatWrite(const string& filename, const Mat& mat);
    Mat MatRead(const string& filename);
    void freeMemory();

};

#endif 
