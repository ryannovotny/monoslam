#!/bin/bash
# Download Pangolin library

if [ -d Pangolin ]; then
    echo "Pangolin/ directory already exists! Delete if you want to reinstall. Exiting..."
    exit 0
fi

git clone https://github.com/stevenlovegrove/Pangolin.git
wget https://gitlab.com/libeigen/eigen/-/archive/3.3.7/eigen-3.3.7.tar.bz2
tar jxvf eigen-3.3.7.tar.bz2
/bin/rm eigen-3.3.7.tar.bz2
mv eigen-3.3.7 Eigen
