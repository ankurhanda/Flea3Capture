//=============================================================================
// Copyright © 2008 Point Grey Research, Inc. All Rights Reserved.
//
// This software is the confidential and proprietary information of Point
// Grey Research, Inc. ("Confidential Information").  You shall not
// disclose such Confidential Information and shall use it only in
// accordance with the terms of the license agreement you entered into
// with PGR.
//
// PGR MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE, OR NON-INFRINGEMENT. PGR SHALL NOT BE LIABLE FOR ANY DAMAGES
// SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING
// THIS SOFTWARE OR ITS DERIVATIVES.
//=============================================================================
//=============================================================================
// $Id: FlyCapture2Test.cpp,v 1.19 2010-03-11 22:58:37 soowei Exp $
//=============================================================================

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include "FlyCapture2.h"

#include <iostream>

#include <pangolin/pangolin.h>
#include <pangolin/simple_math.h>
#include <opencv2/opencv.hpp>
#include <boost/timer/timer.hpp>
#include <pangolin/glcuda.h>


#include "grabber/flea3_grabber.h"

//using namespace FlyCapture2;
using namespace std;
using namespace pangolin;

//void PrintBuildInfo()
//{
//    FC2Version fc2Version;
//    Utilities::GetLibraryVersion( &fc2Version );

//    ostringstream version;
//    version << "FlyCapture2 library version: " << fc2Version.major << "." << fc2Version.minor << "." << fc2Version.type << "." << fc2Version.build;
//    cout << version.str() << endl;

//    ostringstream timeStamp;
//    timeStamp <<"Application build date: " << __DATE__ << " " << __TIME__;
//    cout << timeStamp.str() << endl << endl;
//}

//void PrintCameraInfo( CameraInfo* pCamInfo )
//{
//    cout << endl;
//    cout << "*** CAMERA INFORMATION ***" << endl;
//    cout << "Serial number -" << pCamInfo->serialNumber << endl;
//    cout << "Camera model - " << pCamInfo->modelName << endl;
//    cout << "Camera vendor - " << pCamInfo->vendorName << endl;
//    cout << "Sensor - " << pCamInfo->sensorInfo << endl;
//    cout << "Resolution - " << pCamInfo->sensorResolution << endl;
//    cout << "Firmware version - " << pCamInfo->firmwareVersion << endl;
//    cout << "Firmware build time - " << pCamInfo->firmwareBuildTime << endl << endl;

//}

//void PrintError( Error error )
//{
//    error.PrintErrorTrace();
//}

//int RunSingleCamera( PGRGuid guid )
//{
//    const int k_numImages = 10;

//    Error error;
//    Camera cam;

//    // Connect to a camera
//    error = cam.Connect(&guid);
//    if (error != PGRERROR_OK)
//    {
//        PrintError( error );
//        return -1;
//    }

//    // Get the camera information
//    CameraInfo camInfo;
//    error = cam.GetCameraInfo(&camInfo);
//    if (error != PGRERROR_OK)
//    {
//        PrintError( error );
//        return -1;
//    }

//    PrintCameraInfo(&camInfo);

//    // Start capturing images
//    error = cam.StartCapture();
//    if (error != PGRERROR_OK)
//    {
//        PrintError( error );
//        return -1;
//    }

//    Image rawImage;
//    for ( int imageCnt=0; imageCnt < k_numImages; imageCnt++ )
//    {
//        // Retrieve an image
//        error = cam.RetrieveBuffer( &rawImage );
//        if (error != PGRERROR_OK)
//        {
//            PrintError( error );
//            continue;
//        }

//        cout << "Grabbed image " << imageCnt << endl;

//        // Create a converted image
//        Image convertedImage;

//        // Convert the raw image
//        error = rawImage.Convert( PIXEL_FORMAT_MONO8, &convertedImage );
//        if (error != PGRERROR_OK)
//        {
//            PrintError( error );
//            return -1;
//        }

//        // Create a unique filename

//        ostringstream filename;
//        filename << "FlyCapture2Test-" << camInfo.serialNumber << "-" << imageCnt << ".pgm";

//        // Save the image. If a file format is not passed in, then the file
//        // extension is parsed to attempt to determine the file format.
//        error = convertedImage.Save( filename.str().c_str() );
//        if (error != PGRERROR_OK)
//        {
//            PrintError( error );
//            return -1;
//        }
//    }

//    // Stop capturing images
//    error = cam.StopCapture();
//    if (error != PGRERROR_OK)
//    {
//        PrintError( error );
//        return -1;
//    }

//    // Disconnect the camera
//    error = cam.Disconnect();
//    if (error != PGRERROR_OK)
//    {
//        PrintError( error );
//        return -1;
//    }

//    return 0;
//}

int main(int /*argc*/, char** /*argv*/)
{
    int w_width = 800;
    int w_height = 600;

    int width = w_width;
    int height = w_height;

    int UI_WIDTH = 150;

    pangolin::CreateGlutWindowAndBind("GUISandbox",w_width+UI_WIDTH,w_height);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glewInit();

    /// Create a Panel
    pangolin::View& d_panel = pangolin::CreatePanel("ui")
            .SetBounds(1.0, 0.0, 0, pangolin::Attach::Pix(150));

//    pangolin::GlBufferCudaPtr* pbo_float_0 = new pangolin::GlBufferCudaPtr(pangolin::GlPixelUnpackBuffer,
//                                                               width*height*sizeof(float),
//                                                               cudaGraphicsMapFlagsNone,
//                                                               GL_STREAM_DRAW);

//    pangolin::GlBufferCudaPtr* pbo_float4_0 = new pangolin::GlBufferCudaPtr(pangolin::GlPixelUnpackBuffer,
//                                                               width*height*sizeof(float4),
//                                                               cudaGraphicsMapFlagsNone,
//                                                               GL_STREAM_DRAW);


//    pangolin::GlTexture* tex_show_char4_0   = new pangolin::GlTexture(width,
//                                                                      height,
//                                                                      GL_RGBA);

//    pangolin::GlTexture* tex_show_char_0   = new pangolin::GlTexture(width,
//                                                                 height,
//                                                                 GL_LUMINANCE);


    // Create viewport for video with fixed aspect
    View& vVideo0 = Display("Video")
            .SetBounds(0.0, 1.0, Attach::Pix(UI_WIDTH), Attach::Pix(UI_WIDTH+640),640.0f/480.0f);
//    View& vVideo1 = Display("Video1")
//            .SetBounds(0.0, 1.0, Attach::Pix(UI_WIDTH+640), 1.0,640.0f/490.0f);


    // OpenGl Texture for video frame
//    GlTexture texVideo(width,height,GL_LUMINANCE8);
//    GlTexture texVideo2(640,490,GL_RGBA8);


    flea3_grabber fl3Grabber;

    float * imageArray = new float[width*height];
    GlTexture imageTexture(width,height,GL_LUMINANCE32F_ARB);

    while( !pangolin::ShouldQuit() )
    {
        static Var<float> end_pt("ui.end_pt",0.1,0,10);
        static Var<float> line_width("ui.line_width",2,0,100);

        fl3Grabber.grabFrame(imageArray, width, height);
        imageTexture.Upload(imageArray,GL_LUMINANCE,GL_FLOAT);

        // Activate video viewport and render texture
        vVideo0.Activate();
        glColor3f(1.0,1.0,1.0);
        imageTexture.RenderToViewportFlipY();

        d_panel.Render();
        pangolin::FinishGlutFrame();
    }

    fl3Grabber.closeall();

//    for (unsigned int i=0; i < numCameras; i++)
//    {
//        PGRGuid guid;
//        error = busMgr.GetCameraFromIndex(i, &guid);
//        if (error != PGRERROR_OK)
//        {
//            PrintError( error );
//            return -1;
//        }

//        RunSingleCamera( guid );
//    }

//    cout << "Done! Press Enter to exit..." << endl;
//    cin.ignore();




    return 0;
}
