#include "moilview.h"
#define MAP_CACHE_ENABLED true

char getch(void);
int main(int argc, char *argv[])
{
                
  // while(1) 
{

    int opt;

    cout << endl << "----------------------------" << endl;
    cout << endl << "      MainMoil Menu   " << endl;
    cout << endl << "      1. Car - 6 channel views  " << endl;
    cout << endl << "      2. Panorama  " << endl;
    cout << endl << "      Esc to Exit    " << endl;
    cout << endl << "----------------------------" << endl;

    char c;
    // while(1){ 
    c = getch();
    cout << c << endl;
    switch (c) 
    {
        case '1':
            Car6view *w;
            w = new Car6view();
            w->Show();  
            delete w ;          
            break;
        case '2':
            Panorama *p;
            p = new Panorama();
            p->Show();
            delete p ;
            break;
        case 27:
            exit(1);
            break;
        default:
            break;
    }

    // }
}
}
char getch (void)
{
    int ch;
    struct termios oldt, newt;
 
    tcgetattr(STDIN_FILENO, &oldt);
    memcpy(&newt, &oldt, sizeof(newt));
    newt.c_lflag &= ~( ECHO | ICANON | ECHOE | ECHOK |
                       ECHONL | ECHOPRT | ECHOKE | ICRNL);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
 
    return ch;
}

Car6view::Car6view(){
    md = new Moildev();
}

Panorama::Panorama()
{
    md = new Moildev();
}

void Car6view::Show() {
// repo220_T2

//cout << "test" << endl;
//return ;

    md->Config("car", 1.4, 1.4,
        1320.0, 1017.0, 1.048,
        2592, 1944, 4.05,
        0, 0, 0, 0, -47.96, 222.86
        );
    double calibrationWidth = md->getImageWidth();
    double iCy = md->getiCy();
    ConfigData *cd = md->getcd();
    image_input = imread( "image.jpg", IMREAD_COLOR);
    MediaType mediaType = MediaType::IMAGE_FILE;
    double w = image_input.cols;
    double h = image_input.rows;

    for (uint i=0;i<6;i++) {
         mapX[i] = Mat(h, w, CV_32F);
         mapY[i] = Mat(h, w, CV_32F);
    }

    Mat image_result(h, w, CV_32F);
    Mat image_resultv(w, h, CV_32F);
    m_ratio = w / calibrationWidth;
    clock_t tStart = clock();
    char str_x[12], str_y[12];
    int i = 0;
    if ( MAP_CACHE_ENABLED ) {

        bool map_exist = true ;

        while (map_exist && (i < 7)) {
            sprintf(str_x, "matX%d", i);sprintf(str_y, "matY%d", i);
            if ( !fopen(str_x, "r") || !fopen(str_y, "r"))
                map_exist = false ;
            i++;
        }
        if ( map_exist ) {
            for (i=0;i<6;i++) {
                sprintf(str_x, "matX%d", i);sprintf(str_y, "matY%d", i);
                mapX[i] = MatRead(str_x);
                mapY[i] = MatRead(str_y);
            }
        }
        else {
            md->AnyPointM((float *)mapX[0].data, (float *)mapY[0].data, mapX[0].cols, mapX[0].rows, 0, 0, 4, m_ratio);       // front view
            md->AnyPointM((float *)mapX[1].data, (float *)mapY[1].data, mapX[1].cols, mapX[1].rows, 70, 270, 4, m_ratio);   // left view, rotate 90
            md->AnyPointM((float *)mapX[2].data, (float *)mapY[2].data, mapX[2].cols, mapX[2].rows, 70, 90, 4, m_ratio);    // right view, rotate -90
            md->AnyPointM((float *)mapX[3].data, (float *)mapY[3].data, mapX[3].cols, mapX[3].rows, -70, 0, 4, m_ratio);      // Down view ( zoom: 2/4 )
            md->AnyPointM((float *)mapX[4].data, (float *)mapY[4].data, mapX[4].cols, mapX[4].rows, 70, 225, 4, m_ratio);   // left-lower view, rotate 180
            md->AnyPointM((float *)mapX[5].data, (float *)mapY[5].data, mapX[5].cols, mapX[5].rows, 70, 135, 4, m_ratio);   // right-lower view, rotate 180
            for (i=0;i<6;i++) {
                sprintf(str_x, "matX%d", i);sprintf(str_y, "matY%d", i);
                MatWrite(str_x,mapX[i]);
                MatWrite(str_y,mapY[i]);
            }
        }
    }
    else {
        md->AnyPointM((float *)mapX[0].data, (float *)mapY[0].data, mapX[0].cols, mapX[0].rows, 0, 0, 4, m_ratio);       // front view
        md->AnyPointM((float *)mapX[1].data, (float *)mapY[1].data, mapX[1].cols, mapX[1].rows, 70, 270, 4, m_ratio);   // left view, rotate 90
        md->AnyPointM((float *)mapX[2].data, (float *)mapY[2].data, mapX[2].cols, mapX[2].rows, 70, 90, 4, m_ratio);    // right view, rotate -90
        md->AnyPointM((float *)mapX[3].data, (float *)mapY[3].data, mapX[3].cols, mapX[3].rows, -70, 0, 4, m_ratio);      // Down view ( zoom: 2/4 )
        md->AnyPointM((float *)mapX[4].data, (float *)mapY[4].data, mapX[4].cols, mapX[4].rows, 70, 225, 4, m_ratio);   // left-lower view, rotate 180
        md->AnyPointM((float *)mapX[5].data, (float *)mapY[5].data, mapX[5].cols, mapX[5].rows, 70, 135, 4, m_ratio);   // right-lower view, rotate 180
    }

    double time_clock = (double)(clock() - tStart)/CLOCKS_PER_SEC ;
    cout << "time: " << time_clock << endl ;
    Vec3b p(0,0,0) ;
    image_input.at<Vec3b>(0, 0) = p;

    DisplayCh(0);
    char c;
    while(1){
         c = waitKey( 100 );
         if(c == 27) break;
    }
    cvDestroyWindow("image_input");
    cvDestroyWindow("Front");
    cvDestroyWindow("Left");
    cvDestroyWindow("Right");
    cvDestroyWindow("Down");
    cvDestroyWindow("Lower left");
    cvDestroyWindow("Lower right");     
    image_result.release();
    image_resultv.release();
}

void Car6view::DisplayCh(int ch)
{
    Mat image_result, image_resultv;
    if( image_input.empty()) return ;
    if ( currCh != prevCh ) {
        cvDestroyWindow("image_input");
        cvDestroyWindow("Front");
        cvDestroyWindow("Left");
        cvDestroyWindow("Right");
        cvDestroyWindow("Down");
        cvDestroyWindow("Lower left");
        cvDestroyWindow("Lower right");
    }
// original image
    switch (ch) {
        case 0:  // 2 x 3
        remap(image_input, image_result, mapX[0], mapY[0], INTER_CUBIC, BORDER_CONSTANT, Scalar(0, 0, 0));
        cv::resize(image_result, image_display[0], Size(width_split,height_split-y_base));
        imshow("Front", image_display[0]);
        moveWindow("Front", x_base+width_split, 0+y_base);

        remap(image_input, image_resultv, mapX[1], mapY[1], INTER_CUBIC, BORDER_CONSTANT, Scalar(0, 0, 0));
        Rotate(image_resultv, image_result, 90.0);
        cv::resize(image_result, image_display[1], Size(width_split,height_split-y_base));
        imshow("Left", image_display[1]);
        moveWindow("Left", x_base, 0+y_base);

        remap(image_input, image_resultv, mapX[2], mapY[2], INTER_CUBIC, BORDER_CONSTANT, Scalar(0, 0, 0));
        Rotate(image_resultv, image_result, -90.0);
        cv::resize(image_result, image_display[2], Size(width_split,height_split-y_base));
        imshow("Right", image_display[2]);
        moveWindow("Right", x_base+width_split*2, 0+y_base);

        remap(image_input, image_result, mapX[3], mapY[3], INTER_CUBIC, BORDER_CONSTANT, Scalar(0, 0, 0));
        cv::resize(image_result, image_display[3], Size(width_split,height_split-y_base));
        imshow("Down", image_display[3]);
        moveWindow("Down", x_base+width_split, height_split+y_base);

        remap(image_input, image_result, mapX[4], mapY[4], INTER_CUBIC, BORDER_CONSTANT, Scalar(0, 0, 0));
        Rotate(image_result, image_result, 180.0);
        cv::resize(image_result, image_display[4], Size(width_split,height_split-y_base));
        imshow("Lower left", image_display[4]);
        moveWindow("Lower left", x_base, height_split+y_base);

        remap(image_input, image_result, mapX[5], mapY[5], INTER_CUBIC, BORDER_CONSTANT, Scalar(0, 0, 0));
        Rotate(image_result, image_result, 180.0);
        cv::resize(image_result, image_display[5], Size(width_split,height_split-y_base));
        imshow("Lower right", image_display[5]);
        moveWindow("Lower right", x_base+width_split*2, height_split+y_base);
        break;
    case -1:
        cout << "test" << endl;
        break;
    }
    prevCh = currCh ; 
}



void Car6view::Rotate(Mat& src, Mat& dst, double angle)
{
    Point2f center((src.cols-1)/2.0, (src.rows-1)/2.0);
    Mat rot = cv::getRotationMatrix2D(center, angle, 1.0);
    Rect2f bbox = cv::RotatedRect(cv::Point2f(), src.size(), angle).boundingRect2f();
    rot.at<double>(0,2) += bbox.width/2.0 - src.cols/2.0;
    rot.at<double>(1,2) += bbox.height/2.0 - src.rows/2.0;
    warpAffine(src, dst, rot, bbox.size());
}

void Car6view::MatWrite(const string& filename, const Mat& mat)
{
    ofstream fs(filename, fstream::binary);

    // Header
    int type = mat.type();
    int channels = mat.channels();
    fs.write((char*)&mat.rows, sizeof(int));    // rows
    fs.write((char*)&mat.cols, sizeof(int));    // cols
    fs.write((char*)&type, sizeof(int));        // type
    fs.write((char*)&channels, sizeof(int));    // channels

    // Data
    if (mat.isContinuous())
    {
        fs.write(mat.ptr<char>(0), (mat.dataend - mat.datastart));
    }
    else
    {
        int rowsz = CV_ELEM_SIZE(type) * mat.cols;
        for (int r = 0; r < mat.rows; ++r)
        {
            fs.write(mat.ptr<char>(r), rowsz);
        }
    }
}

Mat Car6view::MatRead(const string& filename)
{
    ifstream fs(filename, fstream::binary);

    // Header
    int rows, cols, type, channels;
    fs.read((char*)&rows, sizeof(int));         // rows
    fs.read((char*)&cols, sizeof(int));         // cols
    fs.read((char*)&type, sizeof(int));         // type
    fs.read((char*)&channels, sizeof(int));     // channels

    // Data
    Mat mat(rows, cols, type);
    fs.read((char*)mat.data, CV_ELEM_SIZE(type) * rows * cols);

    return mat;
}

void Car6view::freeMemory()
{
    cout << "free memory" << endl;
    image_input.release();
    image_input_s.release();
    for(int i=0;i<7;i++) {
        image_display[i].release();
        mapX[i].release();
        mapY[i].release();
    }
}

Car6view::~Car6view()
{
    freeMemory();
    delete md;
}

void Panorama::Show() {
// repo220_T2

//cout << "test" << endl;
//return ;
/*
    md->Config("car", 1.4, 1.4,
        1320.0, 1017.0, 1.048,
        2592, 1944, 4.05,
        0, 0, 0, 0, -47.96, 222.86
        );
*/
    md->Config("Pano", 1.14, 1.69,
        950.0, 744.0, 1.48,
        1920, 1440, 3.00,
        0, 0, 0, -15.92, 31.34, 140.48
        );
/*
    {
      "cameraName": "socionextCx3_main",
      "cameraSensorWidth": 1.14,
      "cameraSensorHeight": 1.69,
      "iCx": 950.0,
      "iCy": 744.0,
      "ratio": 1.48,
      "imageWidth": 1920.0,
      "imageHeight": 1440.0,
      "calibrationRatio": 3.0,
      "parameter0": 0,
      "parameter1": 0,
      "parameter2": 0,
      "parameter3": -15.921,
      "parameter4":  31.337,
      "parameter5": 140.48
    }
*/


    double calibrationWidth = md->getImageWidth();
    double iCy = md->getiCy();
    ConfigData *cd = md->getcd();
    image_input = imread( "image2.png", IMREAD_COLOR);
    MediaType mediaType = MediaType::IMAGE_FILE;
    double w = image_input.cols;
    double h = image_input.rows;
    mapX[0] = Mat(h, w, CV_32F);
    mapY[0] = Mat(h, w, CV_32F);
    Mat image_result(h, w, CV_32F);
    Mat image_resultv(w, h, CV_32F);
    m_ratio = w / calibrationWidth;
    clock_t tStart = clock();
    char str_x[12], str_y[12];
    int i = 0;
    if ( MAP_CACHE_ENABLED ) {

        bool map_exist = true ;

        while (map_exist && (i < 7)) {
            i=6;
            sprintf(str_x, "matX%d", i);sprintf(str_y, "matY%d", i);
            if ( !fopen(str_x, "r") || !fopen(str_y, "r"))
                map_exist = false ;
            i++;
        }
        if ( map_exist ) {
            int i =6;
            sprintf(str_x, "matX%d", i);sprintf(str_y, "matY%d", i);
            mapX[0] = MatRead(str_x);
            mapY[0] = MatRead(str_y);
        }
        else {
            md->PanoramaM((float *)mapX[0].data, (float *)mapY[0].data, mapX[0].cols, mapX[0].rows, m_ratio, 90 );   // panorama
            int i =6;
            sprintf(str_x, "matX%d", i);sprintf(str_y, "matY%d", i);
            MatWrite(str_x,mapX[0]);
            MatWrite(str_y,mapY[0]);
        }
    }
    else {
        md->PanoramaM((float *)mapX[0].data, (float *)mapY[0].data, mapX[0].cols, mapX[0].rows, m_ratio, 110);   // panorama
    }

    double time_clock = (double)(clock() - tStart)/CLOCKS_PER_SEC ;
    cout << "time: " << time_clock << endl ;
    Vec3b p(0,0,0) ;
    image_input.at<Vec3b>(0, 0) = p;

    DisplayCh(0);
    char c;
    while(1){
         c = waitKey( 100 );
         if(c == 27) break;
    }
    cvDestroyWindow("image_input");
    image_result.release();
    image_resultv.release();
}

void Panorama::DisplayCh(int ch)
{
    Mat image_result, image_resultv;
    if( image_input.empty()) return ;
    if ( currCh != prevCh ) {
        cvDestroyWindow("image_input");
    }

// original image
    switch (ch) {
        case 0:
            remap(image_input, image_result, mapX[0], mapY[0], INTER_CUBIC, BORDER_CONSTANT, Scalar(0, 0, 0));
            cv::resize(image_result, image_display[0], Size(width_split*3,height_split*2));
            imshow("Panorama", image_display[0]);
            moveWindow("Panorama", x_base, y_base);
            break;
        case -1:
            cout << "test" << endl;
            break;
    }
    prevCh = currCh ;
}

void Panorama::MatWrite(const string& filename, const Mat& mat)
{
    ofstream fs(filename, fstream::binary);

    // Header
    int type = mat.type();
    int channels = mat.channels();
    fs.write((char*)&mat.rows, sizeof(int));    // rows
    fs.write((char*)&mat.cols, sizeof(int));    // cols
    fs.write((char*)&type, sizeof(int));        // type
    fs.write((char*)&channels, sizeof(int));    // channels

    // Data
    if (mat.isContinuous())
    {
        fs.write(mat.ptr<char>(0), (mat.dataend - mat.datastart));
    }
    else
    {
        int rowsz = CV_ELEM_SIZE(type) * mat.cols;
        for (int r = 0; r < mat.rows; ++r)
        {
            fs.write(mat.ptr<char>(r), rowsz);
        }
    }
}

Mat Panorama::MatRead(const string& filename)
{
    ifstream fs(filename, fstream::binary);

    // Header
    int rows, cols, type, channels;
    fs.read((char*)&rows, sizeof(int));         // rows
    fs.read((char*)&cols, sizeof(int));         // cols
    fs.read((char*)&type, sizeof(int));         // type
    fs.read((char*)&channels, sizeof(int));     // channels

    // Data
    Mat mat(rows, cols, type);
    fs.read((char*)mat.data, CV_ELEM_SIZE(type) * rows * cols);

    return mat;
}

void Panorama::freeMemory()
{
    cout << "free memory" << endl;
    image_input.release();
    image_input_s.release();
    for(int i=0;i<7;i++) {
        image_display[i].release();
        mapX[i].release();
        mapY[i].release();
    }
}
Panorama::~Panorama()
{
    freeMemory();
    delete md;
}
