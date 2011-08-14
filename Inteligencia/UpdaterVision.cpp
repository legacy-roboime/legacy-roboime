#include "UpdaterVision.h"
#include <QMutexLocker>
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
		while(!_stop) {
			if(_client.receive(packet)) {
				//QMutexLocker locker(&_mutex);
				_mutex.lock();
				_packet.push_back(packet);
				_mutex.unlock();
			}
		}
	}

	void UpdaterVision::receive() {
		if(!isRunning()) {
			_stop = false;
			start();
		}
	}

	void UpdaterVision::prepare() {
		//QMutexLocker locker(&_mutex);
		bool do_loop;
		_mutex.lock();
		do_loop = !_packet.empty(); 
		_mutex.unlock();
		while(!_packet.empty()){
			_mutex.lock();
			SSL_WrapperPacket packet = _packet.front();
			_mutex.unlock();
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
				//NOTE: note de color code!!!
				//blue robots:
				for (int i = 0; i < detection.robots_blue_size(); i++) {
					SSL_DetectionRobot robot = detection.robots_blue(i);
					_update.push_back(new UpdateRobot(robot.robot_id(),(real)robot.x(),(real)robot.y(),
						(real)robot.orientation(),robot.confidence(),t_sent,t_capture));
				}
				//yellow robots:
				for (int i = 0; i < detection.robots_yellow_size(); i++) {
					SSL_DetectionRobot robot = detection.robots_yellow(i);
					_update.push_back(new UpdateRobot(robot.robot_id(),(real)robot.x(),(real)robot.y(),
						(real)robot.orientation(),robot.confidence(),t_sent,t_capture));
				}

			}
			_packet.pop_front();
			_mutex.lock();
			do_loop = !_packet.empty(); 
			_mutex.unlock();
		}
	}
}