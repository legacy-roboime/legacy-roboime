//#include "Simulation.h"
//#include "SSLServer.h"
////#define NOMINMAX
////#include "TimePosix.h"
//
////namespace LibSimulation {
//	
//	void SSLServer::run() {
//		while(true) {
//			prepare();
//			send();
//			Sleep(1000/80);
//		}
//	}
//
//	SSLServer::SSLServer() {
//		withDetection = true;
//		withGeometry = false;
//		server.open();
//	}
//
//	SSLServer::SSLServer(string address, int port) {
//		//TODO: implement
//	}
//
//	SSLServer::~SSLServer() {}
//
//	void SSLServer::refresh() {
//		//TODO: implemenr
//	}
//	
//	void SSLServer::prepare() {
//		static unsigned long int frameNumber = 0;
//		
//		timeval tv;
//		TimePosix::gettimeofday(&tv,NULL);
//		double time = (double)tv.tv_sec + tv.tv_usec*(1.0E-6);
//
//		QMutexLocker locker(&mutex);
//
//		if(withDetection)//withDetection
//		{
//			NxScene1* baseScene = Simulation::gScenes[Simulation::gBaseScene];
//
//			SSL_DetectionFrame detectionFrame = SSL_DetectionFrame();
//
//			detectionFrame.set_frame_number(frameNumber);
//			detectionFrame.set_camera_id(0);
//			detectionFrame.set_t_capture(time);
//			detectionFrame.set_t_sent(time);
//
//			NxVec3 ballGlobalPos = Simulation::allBalls.getBallByScene(Simulation::gBaseScene).ball->getGlobalPosition();
//			SSL_DetectionBall* detectionBall = detectionFrame.add_balls();
//			detectionBall->set_area(1);
//			detectionBall->set_confidence(1);
//			detectionBall->set_pixel_x(0);
//			detectionBall->set_pixel_y(0);
//			detectionBall->set_x(ballGlobalPos.x);
//			detectionBall->set_y(ballGlobalPos.y);
//			detectionBall->set_z(1);
//
//			NxArray<NxRobot*> allRobots = Simulation::allRobots.getRobotsByScene(Simulation::gBaseScene);
//			for(int i=0; i<allRobots.size(); i++)
//			{
//				NxRobot* robot = allRobots[i];
//				NxReal angulo = Simulation::getAngle2DFromRobot(4, 0);
//				NxVec3 robotPos = robot->getBodyPos();
//				SSL_DetectionRobot* detectionRobot;
//				
//				if (robot->getIdTeam()==1)
//					detectionRobot = detectionFrame.add_robots_blue();
//				else //if (robot->getIdTeam()==0)
//					detectionRobot = detectionFrame.add_robots_yellow();
//				
//				detectionRobot->set_confidence(1);
//				detectionRobot->set_height(150);
//				detectionRobot->set_orientation(robot->getAngle2DFromVehicle());
//				detectionRobot->set_pixel_x(0);
//				detectionRobot->set_pixel_y(0);
//				detectionRobot->set_robot_id(robot->getId()-1); //FOI SUBTRAIDO 1 PQ NO TEAMBOTS OS INDICES DOS ROBOS VAI DE 0 A 4
//				detectionRobot->set_x(robotPos.x);
//				detectionRobot->set_y(robotPos.y);
//			}
//
//			SSL_DetectionFrame * nframe = wrapperPacket.mutable_detection();
//			nframe->CopyFrom(detectionFrame);
//		}
//		if(withGeometry)//withGeometry)
//		{
//			SSL_GeometryData geometryData = SSL_GeometryData();
//
//			SSL_GeometryFieldSize* geometryFieldSize = geometryData.mutable_field();
//			geometryFieldSize->set_boundary_width(0);
//			geometryFieldSize->set_center_circle_radius(0);
//			geometryFieldSize->set_defense_radius(0);
//			geometryFieldSize->set_defense_stretch(0);
//			geometryFieldSize->set_field_length(0);
//			geometryFieldSize->set_field_width(0);
//			geometryFieldSize->set_free_kick_from_defense_dist(0);
//			geometryFieldSize->set_goal_depth(0);
//			geometryFieldSize->set_goal_wall_width(0);
//			geometryFieldSize->set_goal_width(0);
//			geometryFieldSize->set_line_width(0);
//			geometryFieldSize->set_penalty_line_from_spot_dist(0);
//			geometryFieldSize->set_penalty_spot_from_field_line_dist(0);
//			geometryFieldSize->set_referee_width(0);
//
//			SSL_GeometryCameraCalibration* geometryCameraCalibration = geometryData.add_calib();
//			geometryCameraCalibration->set_camera_id(0);
//			geometryCameraCalibration->set_derived_camera_world_tx(0);
//			geometryCameraCalibration->set_derived_camera_world_ty(0);
//			geometryCameraCalibration->set_distortion(0);
//			geometryCameraCalibration->set_focal_length(0);
//			geometryCameraCalibration->set_principal_point_x(0);
//			geometryCameraCalibration->set_principal_point_y(0);
//			geometryCameraCalibration->set_q0(0);
//			geometryCameraCalibration->set_q1(0);
//			geometryCameraCalibration->set_q2(0);
//			geometryCameraCalibration->set_q3(0);
//			geometryCameraCalibration->set_tx(0);
//			geometryCameraCalibration->set_ty(0);
//			geometryCameraCalibration->set_tz(0);
//
//			SSL_GeometryData * gdata = wrapperPacket.mutable_geometry();
//			gdata->CopyFrom(geometryData);
//		}
//
//	}
//
//	void SSLServer::send() {
//		server.send(wrapperPacket);
//	}
//
////}