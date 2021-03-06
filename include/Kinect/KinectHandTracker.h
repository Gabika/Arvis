#ifndef KINECTHANDTRACKER_H
#define KINECTHANDTRACKER_H

#include "Kinect/HistoryBuffer.h"
#include "OpenNI.h"
#include "NiTE.h"
#include <map>

#define NUM_HANDS 2

namespace Vwr{
class MouseControl;
}

namespace Kinect{
class KinectRecognition;


/**
 * @author Patrik Hlavac
 * @brief The KinectHandTracker class
 * @brief Class for recognition of Hands
 */
class KinectHandTracker{

public:
	/**
	 * @brief KinectHandTracker
	 * @param device device for recognition
	 * @param m_depth Videostream
	 */
	KinectHandTracker(openni::Device *device,openni::VideoStream  *m_depth);
	~KinectHandTracker();

	//const nite::Array<nite::GestureData>& gestures;
	//const nite::Array<nite::GestureData>& hands;

	float handZ[2];

	// both hands position
	float getArrayHands[NUM_HANDS][NUM_HANDS];
	bool isTwoHands;

	float slidingHand_x;
	float slidingHand_y;
	float slidingHand_z;
	char * slidingHand_type;

	/**
	 * @brief getAllGestures
	 * @brief searching all define gestures in Nite2
	 * actual is using checking for Click gesture (Wave,..)
	 */
	void getAllGestures();

	/**
	 * @brief getAllHands
	 * @brief searching in Frame for all hands and processing them
	 */
	void getAllHands();

	/**
	 * @brief getRotatingMove
	 * @brief checking History Buffer for own define Gesture
	 */
	void getRotatingMove();

	/**
	 * @brief setCursorMovement
	 * @brief enable moving cursor mouse based on Hand
	 * @param set if true mouse is moving, other is not connected
	 */
	void setCursorMovement(bool set);

	/**
	 * @brief setSpeedMovement
	 * @param set number of speed movement. based is 1.0
	 */
	void setSpeedMovement(double set);

	// Hand Tracker
	nite::HandTracker m_pHandTracker;

	// history buffer of position of hand
	std::map<int, HistoryBuffer<20> *> g_histories;

	// frame getting from Hand Tracker
	nite::HandTrackerFrameRef handTrackerFrame;

private:

	/**
	 * @brief is Mouse pressed
	 */
	bool isClick;

	/**
	 * @brief is mouse cursor movement enable
	 */
	bool isCursorMovementEnable;


	/**
	 * @brief class for controlling mouse
	 */
	Vwr::MouseControl *mouse;

	/**
	 * @brief save videostream - get points
	 */
	openni::VideoStream  *mDepth;

	/**
	 * @brief convertor between Kinect 3D coordinates to real word coordinates
	 */
	openni::CoordinateConverter coordinateConverter;

	/**
	 * @brief real coordinate X
	 */
	float mDepthX;


	/**
	 * @brief real coordinate Y
	 */
	float mDepthY;


	/**
	 * @brief real coordinate Z
	 */
	float mDepthZ;

	/**
	 * @brief speed of movemenent
	 */
	double mSpeed;

};
}
#endif // KINECTHANDTRACKER_H
