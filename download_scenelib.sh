#!/bin/bash
# Download SceneLib2 library and add missing header

if [ -d SceneLib2 ]; then
    echo "SceneLib2 is already present! Delete to reinstall. Exiting..."
    exit 0
fi

git clone git://github.com/hanmekim/SceneLib2.git SceneLib2
cd SceneLib2/scenelib2/framegrabber
sed -i '42i #include <opencv2/imgproc/types_c.h>' usbcamgrabber.h
