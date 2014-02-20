#include "Aruco/arucocore.h"
#include "QDebug"


using namespace ArucoModul;

ArucoCore::ArucoCore(const QString markerDesFile)
{

	mMarkerSize = 0.06;
	try {
		cameraParameters(markerDesFile);
	}
	catch(std::exception &ex) {
		qDebug() << "Exception: " << QString::fromUtf8( ex.what());
	}
}



void ArucoCore::cameraParameters(const QString markerDesFile)
{
	if(markerDesFile.isEmpty()){
		qDebug() << "ArucoCore::cameraParameters(): markerDesFile name is empty";
	}
	//read camera paramters if passed
	mCamParam.readFromXMLFile( markerDesFile.toStdString() );
}

const QMatrix4x4 ArucoCore::getDetectedMatrix(cv::Mat inputImage){
	double modelViewMatrix[16];

	//this->updateImage( inputImage );
	mCamParam.resize(inputImage.size());
	mCamImage = inputImage;

	// get result model view matrix from imput image
	this->detectMarkers();
	this->getMatrix( modelViewMatrix );

	QMatrix4x4 matrix(modelViewMatrix);
	return matrix;
}

// tato funkcia je nepouzitelna
void ArucoCore::updateImage(cv::Mat inputImage)
{

	mCamParam.resize(inputImage.size());
	//mCamImage.create(inputImage.size(),CV_8UC3);

	//transform color that by default is BGR to RGB because windows systems do not allow reading BGR images with opengl properly
	// cv::cvtColor(inputImage,inputImage,CV_BGR2RGB);   // pri testovani praveze opacny efekt

	//remove distorion in image
		// nemoze byt ak je camera nastavena v konstruktore,
		// ma za nasledok neustalu postupnu zmenu parametrov kamary,
		// az sa stanu nepouzitelne a tym deformovanie obrazka do jeho rohu
	//cv::undistort(inputImage, mCamImage, mCamParam.CameraMatrix, mCamParam.Distorsion);


}
void ArucoCore::detectMarkers()
{
	//detect markers
	mMDetector.detect( mCamImage,
					   mMarkers,
					   mCamParam, //mCamParam.CameraMatrix,
					   //cv::Mat(),
					   mMarkerSize);

	showDetImage();
}

int ArucoCore::getMatrix(double *modelviewmatrix)
{
	if( mMarkers.size() > 0)
	{
		mMarkers[0].glGetModelViewMatrix(modelviewmatrix);
		return 0;
	}
	return -1;
}

void ArucoCore::showDetImage(){
	//for each marker, draw info and its boundaries in the image

	for (unsigned int i = 0; i < mMarkers.size(); i++) {
		mMarkers[i].draw( mCamImage, cv::Scalar(0,0,255), 2);

		//draw a 3d cube in each marker if there is 3d info
		if (  mCamParam.isValid() && mMarkerSize != -1 ){
			aruco::CvDrawingUtils::draw3dCube( mCamImage, mMarkers[i], mCamParam);
		}
	}

	//show input with augmented information
	cv::imshow("in", mCamImage);
	cv::waitKey(1);//wait for key to be pressed
}
