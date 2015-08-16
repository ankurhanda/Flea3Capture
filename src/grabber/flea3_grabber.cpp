#include "flea3_grabber.h"
#include <stdlib.h>
#include <stdio.h>

flea3_grabber::flea3_grabber()
{

    PrintBuildInfo();

    BusManager busMgr;
    unsigned int numCameras;
    error = busMgr.GetNumOfCameras(&numCameras);
    if (error != PGRERROR_OK)
    {
        PrintError( error );
//        return -1;
        exit(1);
    }


    error = busMgr.GetCameraFromIndex(0, &guid);

    // Connect to a camera
    error = cam.Connect(&guid);
    if (error != PGRERROR_OK)
    {
        PrintError( error );
//        return -1;
         exit(1);
    }

    // Get the camera information
    CameraInfo camInfo;
    error = cam.GetCameraInfo(&camInfo);
    if (error != PGRERROR_OK)
    {
        PrintError( error );
//        return -1;
                exit(1);
    }

    PrintCameraInfo(&camInfo);

    // Start capturing images
    error = cam.StartCapture();
    if (error != PGRERROR_OK)
    {
        PrintError( error );
//        return -1;
        exit(1);
    }

}

int flea3_grabber::grabFrame(float* grabbed_frame, const unsigned int width,
                             const unsigned int height)
{
    Image rawImage;

    static int imgcount = 0;
//    for ( int imageCnt=0; imageCnt < k_numImages; imageCnt++ )
    {
        // Retrieve an image
        error = cam.RetrieveBuffer( &rawImage );
        if (error != PGRERROR_OK)
        {
            PrintError( error );
        }

        cout << "Grabbed image " << endl;

        // Create a converted image
        Image convertedImage;

        // Convert the raw image
        error = rawImage.Convert( PIXEL_FORMAT_MONO8, &convertedImage );
//        error = rawImage.Convert( PIXEL_FORMAT_MONO8, &convertedImage );


        if (error != PGRERROR_OK)
        {
            PrintError( error );
            return -1;
        }

//        // Create a unique filename

//        ostringstream filename;
//        filename << "FlyCapture2Test-" << imgcount++ << ".pgm";

        char fileName[100];
        sprintf(fileName,"FlyCapture_%07d.png",imgcount++);

        // Save the image. If a file format is not passed in, then the file
        // extension is parsed to attempt to determine the file format.
        error = convertedImage.Save( fileName) ; //filename.str().c_str() );
        if (error != PGRERROR_OK)
        {
            PrintError( error );
            return -1;
        }

        unsigned char* thisFrame = rawImage.GetData();

#pragma omp parallel
        for(int yy = 0; yy < height; yy++)
        {
            for(int xx = 0; xx < width; xx++)
            {
                grabbed_frame[xx+yy*width] = (float)thisFrame[yy*width+xx]/255.0f;
            }
        }

        return 1;
    }

}


void flea3_grabber::closeall()
{
    // Stop capturing images
    error = cam.StopCapture();
    if (error != PGRERROR_OK)
    {
        PrintError( error );
//        return -1;
        exit(1);
    }

    // Disconnect the camera
    error = cam.Disconnect();
    if (error != PGRERROR_OK)
    {
        PrintError( error );
//        return -1;
        exit(1);
    }
}

flea3_grabber::~flea3_grabber()
{
    // Stop capturing images
    error = cam.StopCapture();
    if (error != PGRERROR_OK)
    {
        PrintError( error );
//        return -1;
        exit(1);
    }

    // Disconnect the camera
    error = cam.Disconnect();
    if (error != PGRERROR_OK)
    {
        PrintError( error );
//        return -1;
        exit(1);
    }

}
