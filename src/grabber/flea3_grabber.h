/* Copyright (c) 2015 Ankur Handa
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */



#pragma once


#include <iostream>
#include <string>
#include <sstream>

#include <cvd/image.h>
#include <cvd/image_io.h>
#include <cvd/rgb8.h>
#include <cvd/byte.h>

#include "FlyCapture2.h"


using namespace FlyCapture2;
using namespace std;


class flea3_grabber{

public:

    flea3_grabber();

    int grabFrame(float *grabbed_frame, const unsigned int width, const unsigned int height);

    ~flea3_grabber();

    void inline PrintCameraInfo( CameraInfo* pCamInfo )
    {
        cout << endl;
        cout << "*** CAMERA INFORMATION ***" << endl;
        cout << "Serial number -" << pCamInfo->serialNumber << endl;
        cout << "Camera model - " << pCamInfo->modelName << endl;
        cout << "Camera vendor - " << pCamInfo->vendorName << endl;
        cout << "Sensor - " << pCamInfo->sensorInfo << endl;
        cout << "Resolution - " << pCamInfo->sensorResolution << endl;
        cout << "Firmware version - " << pCamInfo->firmwareVersion << endl;
        cout << "Firmware build time - " << pCamInfo->firmwareBuildTime << endl << endl;

    }

    void inline PrintBuildInfo()
    {
        FC2Version fc2Version;
        Utilities::GetLibraryVersion( &fc2Version );

        ostringstream version;
        version << "FlyCapture2 library version: " << fc2Version.major << "." << fc2Version.minor << "." << fc2Version.type << "." << fc2Version.build;
        cout << version.str() << endl;

        ostringstream timeStamp;
        timeStamp <<"Application build date: " << __DATE__ << " " << __TIME__;
        cout << timeStamp.str() << endl << endl;
    }

    void PrintError( Error error )
    {
        error.PrintErrorTrace();
    }

    void closeall();


    PGRGuid guid;
    Error error;
    Camera cam;
};
