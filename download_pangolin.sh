#!/bin/bash
# Download Pangolin library

if [ -d Pangolin ]; then
    echo "Pangolin/ directory already exists! Delete if you want to reinstall. Exiting..."
    exit 0
fi

git clone https://github.com/stevenlovegrove/Pangolin.git
cd Pangolin
mkdir build
cd build
cmake -DBUILD_TESTS=OFF -DBUILD_EXAMPLES=OFF -DBUILD_PANGOLIN_PYTHON=OFF ..
cmake --build .
