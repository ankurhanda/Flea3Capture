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
