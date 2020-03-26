# MOIL SDK description
MOIL SDK is collection of functions support c++ developments for fisheye image applications, tested both on ubuntu 18.04 and Raspberry Pi( Raspbian Buster ), gcc/g++ and OpenCV are required in the development. Following examples are on ubuntu 18.04 .
One of MOIL's core technology is to calibrate a fisheye lens no matter the fisheye lens is cheap(not well-produced) or expensive(well-produced). After calibrating , MOIL will have a set of fisheye 
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
-----------------------------------------------------------------------------------------------------------------------------
3.API Reference
    3.1 Fisheye parameter Config : 
    
