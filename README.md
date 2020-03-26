# MOIL SDK description
MOIL SDK is collection of functions support c++ developments for fisheye image applications, tested both on ubuntu 18.04 and Raspberry Pi( Raspbian Buster ), gcc/g++ and OpenCV are required in the development. Following examples are on ubuntu 18.04 .
One of MOIL's core technology is to calibrate a fisheye lens no matter the fisheye lens is cheap(Not well-produced) or expensive(well-produced). After calibrating , MOIL will have a set of fisheye parameters and based on it to implement the fisheye image with the SDK functions. Below demo is with dedicated calibrated  fisheye lens , don't try to change the original image and parameters , it will lead to not perfect or uncertain output. 
-----------------------------------------------------------------------------------------------------------------------------
1. Development environment
If you already have Opencv installed, the following steps can be skipped. Opencv version 3.2.0 is recommented, it's the default version on both Ubuntu 18.04 and Raspbian Buster.
sudo apt update
sudo apt upgrade
sudo apt install build-essential cmake pkg-config
sudo apt install libjpeg-dev libpng-dev libtiff-dev
sudo apt install software-properties-common
sudo add-apt-repository "deb http://security.ubuntu.com/ubuntu xenial-security main"
sudo apt update
sudo apt install libjasper1 libjasper-dev
sudo apt update
sudo apt install libgtk-3-dev
sudo apt install libatlas-base-dev gfortran
sudo apt install libopencv-dev python-opencv
-----------------------------------------------------------------------------------------------------------------------------
2. Includes
#include "moildev.h"
  moildev.h is head file and inside is the definition of the function calls from moildev.a library.
#include "configdata.h"
  config.h is the definition of the calibrated parameters and function calls to access the parameter. 
#include "configdata.h"
  car6view.h is a standard c class definition. 
-----------------------------------------------------------------------------------------------------------------------------
3. Sample Image (the image is captured with dedicated fisheye. Different  )
A fisheye 180 degree image . To simulate car rear view of six view angle scenes .
-----------------------------------------------------------------------------------------------------------------------------
3. Sample code 
main.cpp
-----------------------------------------------------------------------------------------------------------------------------
4.API Reference
    4.1 Fisheye parameter Config : 
    Create a md object and feed the fisheye calibrated parameters . (the parameters is for dedicated fisheye )
   md->Config("car", 1.4, 1.4,
        1320.0, 1017.0, 1.048,
        2592, 1944, 4.05,
        0, 0, 0, 0, -47.96, 222.86
        );
