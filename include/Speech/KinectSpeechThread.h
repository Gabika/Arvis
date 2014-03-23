#ifndef KINECTSPEECHTHREAD_H
#define KINECTSPEECHTHREAD_H

#include <QThread>

namespace Speech

{
class KinectSpeechThread;

/**
	 * @brief Class KinectSpeechThread
	 * @author Autor: Marek Jakab
	 * @date 22.3.2014
	 */
class KinectSpeechThread : public QThread
{
	Q_OBJECT

public:
	KinectSpeechThread();
	~KinectSpeechThread(void);
	//SpeechSDK::SpeechSDKClass m_SpeechClass;

	/**
		 * @author Autor: Marek Jakab
		 * @brief run Starts thread
		 */
	void run();

};
}


#endif // KINECTSPEECHTHREAD_H