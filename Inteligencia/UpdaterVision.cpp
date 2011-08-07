#include "UpdaterVision.h"
#include "Update.h"
#include "UpdateBall.h"
#include "UpdateRobot.h"

using namespace std;
namespace Inteligencia {

	UpdaterVision::UpdaterVision() : Updater() {
		_stop = false;
	}

	UpdaterVision::UpdaterVision(string address, int port) : Updater() {
		//TODO: implement
	}

	UpdaterVision::~UpdaterVision() {}

	void UpdaterVision::run() {
		_client.open(true);
		SSL_WrapperPacket packet;
		while(true) {
			if(_client.receive(packet)) _packet.push_back(packet);
			QMutexLocker locker(&_mutex);
			if(_stop) return;
		}
	}

	void UpdaterVision::receive() {
		if(!isRunning()) start();
	}

	void UpdaterVision::prepare() {
		while(!_packet.empty()){
			QMutexLocker locker(&_mutex);
			SSL_WrapperPacket packet = _packet.front();
			if (packet.has_detection()) {
                SSL_DetectionFrame detection = packet.detection();
				//TODO: implement UpdateStage
				//double t_now = GetTimeSec();
                //printf("Camera ID=%d FRAME=%d T_CAPTURE=%.4f\n",detection.camera_id(),detection.frame_number(),detection.t_capture());
                //printf("SSL-Vision Processing Latency                   %7.3fms\n",(detection.t_sent()-detection.t_capture())*1000.0);
                //printf("Network Latency (assuming synched system clock) %7.3fms\n",(t_now-detection.t_sent())*1000.0);
                //printf("Total Latency   (assuming synched system clock) %7.3fms\n",(t_now-detection.t_capture())*1000.0);
				double t_capture = detection.t_capture();
				double t_sent = detection.t_sent();
				//balls:
                for (int i = 0; i < detection.balls_size(); i++) {
                    SSL_DetectionBall ball = detection.balls(i);
					//TODO: implement ball z
                    //if (ball.has_z()) ;
					_update.push_back(new UpdateBall(ball.x(),ball.y(),ball.confidence(),t_sent,t_capture));
                }
                //blue robots:
                for (int i = 0; i < detection.robots_blue_size(); i++) {
                    SSL_DetectionRobot robot = detection.robots_blue(i);
					_update.push_back(new UpdateRobot(robot.robot_id()+1,robot.x(),robot.y(),
						robot.orientation(),robot.confidence(),t_sent,t_capture));
                }
                //yellow robots:
                for (int i = 0; i < detection.robots_yellow_size(); i++) {
                    SSL_DetectionRobot robot = detection.robots_yellow(i);
                    _update.push_back(new UpdateRobot(robot.robot_id()+1,robot.x(),robot.y(),
						robot.orientation(),robot.confidence(),t_sent,t_capture));
                }

            }
			_packet.pop_front();
		}
	}
}