MOIL SDK description
============================================================================================================================

MOIL SDK is collection of functions support c++ developments for fisheye image applications, tested both on ubuntu 18.04 and Raspberry Pi( Raspbian Buster ), gcc/g++ and OpenCV are required in the development. Following examples are on ubuntu 18.04 . One of MOIL's core technology is to calibrate a fisheye lens no matter the fisheye lens is cheap(Not well-made) or expensive(Well-made). After calibrating , MOIL will have a set of fisheye parameters and based on it to implement the fisheye image with the SDK functions. (Warning : Changing the parameters or image will lead to uncertain output. )

![](https://user-images.githubusercontent.com/3524867/73999970-65850480-49a1-11ea-9e0b-6b88d1d49fb7.jpg)
![](https://user-images.githubusercontent.com/3524867/74001393-61a7b100-49a6-11ea-96a0-112dbdeb7b05.jpg)
-----------------------------------------------------------------------------------------------------------------------------
1. Development environment
   
If you already have Opencv installed, the following steps can be skipped. Opencv version 3.2.0 is recommented, it's the default version on Ubuntu 18.04.
```
sudo apt update
sudo apt upgrade
sudo apt install build-essential cmake pkg-config
sudo apt install libjpeg-dev libpng-dev libtiff-de
sudo apt install software-properties-common
sudo add-apt-repository "deb http://security.ubuntu.com/ubuntu xenial-security main"
sudo apt install libjasper1 libjasper-dev
sudo apt install libgtk-3-dev
sudo apt install libatlas-base-dev gfortran
sudo apt install libopencv-dev python-opencv
```
-----------------------------------------------------------------------------------------------------------------------------

2. Includes
```
"moildev.h" is the definition of the function calls from moildev.a library.
"configdata.h" is the definition of the calibrated parameters and function calls to access the parameter. 
"car6view.h" is a standard C++ class definition. 
```
-----------------------------------------------------------------------------------------------------------------------------

3. Sample Image (image.jpg)
```
A fisheye 180 degree image . To simulate car rear view and accordingly to output six view angle scenes .
```
-----------------------------------------------------------------------------------------------------------------------------

4. Sample code 
```
main.cpp
```
-----------------------------------------------------------------------------------------------------------------------------

5. API Reference

5.1 Disk Cache
```
MAP_CACHE_ENABLED
```
By default, MAP_CACHE_ENABLED is set as true for system performance consideration. Both xMaps and yMaps are generated by the calling of AnyPoint function will be store in files and read back next time. 

5.2 Fisheye parameter Config : 
```
md->Config("car", 1.4, 1.4,1320.0, 1017.0, 1.048, 2592, 1944, 4.05, 0, 0, 0, 0, -47.96, 222.86 );
```
This is to config the fisheye calibrated parameters at initial stage. Each fisheye camera can be calibrated and derives a set of parameters by MOIL laboratory, the configuration is necessary in the beginning of program.
    
5.3 AnypointM
```
C++ : double AnyPointM(float *mapX, float *mapY, int w, int h, double alphaOffset, double betaOffset,
double zoom, double magnification);

Parameters : 

. mapX : memory pointer of result X-Map   
. mapY : memory pointer of result Y-Map
. w : width of the Map (both mapX and mapY)
. h : height of the Map (both mapX and mapY)
. alphaOffset : alpha offset 
. betaOffset : beta offset
. zoom : zoom factor 
. manification : input image width / calibrationWidth, where calibrationWidth can get by calling getImageWidth(), manification is normally equal to 1. 
```
The function is in MOIL SDK. It is to generate a pair of X-Y Maps for the specified alpha, beta and zoom parameters, the result X-Y Maps can be used later to remap the original fisheye image to the target angle image. you could also find the sample code in "main.cpp" as below:
```
md->AnyPointM((float *)mapX[0].data, (float *)mapY[0].data, mapX[0].cols, mapX[0].rows, 0, 0, 4, m_ratio);       // front view
```
-----------------------------------------------------------------------------------------------------------------------------

6. Build abd Run
```
sudo chmod +x build
./build
./mainmoil
```

![](https://github.com/cjchng/mainmoil_6view/blob/master/images/screenshot.png?raw=true)
