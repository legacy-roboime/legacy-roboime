#include "UDPMulticastSenderSSLVision.h"
#include "Simulation.h"

UDPMulticastSenderSSLVision::UDPMulticastSenderSSLVision(void)
{
}

UDPMulticastSenderSSLVision::~UDPMulticastSenderSSLVision(void)
{
}

void UDPMulticastSenderSSLVision::buildSendMessage()
{
	//Simulation::mutex.lock();
	QMutexLocker locker(&Simulation::mutex);

	// Verify that the version of the library that we linked against is
	// compatible with the version of the headers we compiled against.
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	SSL_WrapperPacket wrapperPacket;
	static unsigned long int frameNumber = 0;
	
	timeval tv;
	TimePosix::gettimeofday(&tv,NULL);
	double time = (double)tv.tv_sec + tv.tv_usec*(1.0E-6);

	if(true)//withDetection)
	{
		/////////////QMutexLocker locker(&Simulation::mutex);

		NxScene1* scene1 = Simulation::gScenes[Simulation::gBaseScene];

		SSL_DetectionFrame detectionFrame = SSL_DetectionFrame();

		detectionFrame.set_frame_number(frameNumber);
		detectionFrame.set_camera_id(0);
		detectionFrame.set_t_capture(time);
		detectionFrame.set_t_sent(time);

		NxVec3 ballGlobalPos = scene1->ball->ball->getGlobalPosition();
		SSL_DetectionBall* detectionBall = detectionFrame.add_balls();
		detectionBall->set_area(1);
		detectionBall->set_confidence(1);
		detectionBall->set_pixel_x(0);
		detectionBall->set_pixel_y(0);
		detectionBall->set_x(ballGlobalPos.x);
		detectionBall->set_y(ballGlobalPos.y);
		detectionBall->set_z(1);

		NxArray<NxRobot*> allRobots = scene1->allRobots->getRobots();
		for(int i=0; i<allRobots.size(); i++)
		{
			NxRobot* robot = allRobots[i];
			NxVec3 robotPos = robot->getPos();
			SSL_DetectionRobot* detectionRobot;
			
			if (robot->getIdTeam()==1)
				detectionRobot = detectionFrame.add_robots_blue();
			else //if (robot->getIdTeam()==0)
				detectionRobot = detectionFrame.add_robots_yellow();
			
			detectionRobot->set_confidence(1);
			detectionRobot->set_height(150);
			detectionRobot->set_orientation(robot->getAngle2DFromVehicle());
			detectionRobot->set_pixel_x(0);
			detectionRobot->set_pixel_y(0);
			detectionRobot->set_robot_id(robot->getId()/*-1*/); //FOI SUBTRAIDO 1 PQ NO TEAMBOTS OS INDICES DOS ROBOS VAI DE 0 A 4
			detectionRobot->set_x(robotPos.x);
			detectionRobot->set_y(robotPos.y);
		}

		SSL_DetectionFrame * nframe = wrapperPacket.mutable_detection();
		nframe->CopyFrom(detectionFrame);
	}
	if(true)//withGeometry)
	{
		///////////////////QMutexLocker locker(&Simulation::mutex);
		NxField* field = Simulation::gScenes[Simulation::gBaseScene]->field;

		SSL_GeometryData geometryData = SSL_GeometryData();

		SSL_GeometryFieldSize* geometryFieldSize = geometryData.mutable_field();
		geometryFieldSize->set_boundary_width(field->boundary_width);
		geometryFieldSize->set_center_circle_radius(field->center_circle_radius);
		geometryFieldSize->set_defense_radius(field->defense_radius);
		geometryFieldSize->set_defense_stretch(field->defense_stretch);
		geometryFieldSize->set_field_length(field->linesLength);
		geometryFieldSize->set_field_width(field->linesWidth);
		geometryFieldSize->set_free_kick_from_defense_dist(field->free_kick_from_defense_dist);
		geometryFieldSize->set_goal_depth(field->goalLength);
		geometryFieldSize->set_goal_wall_width(field->goal_wall_width);
		geometryFieldSize->set_goal_width(field->goalWidth);
		geometryFieldSize->set_line_width(field->line_width);
		geometryFieldSize->set_penalty_line_from_spot_dist(field->penalty_line_from_spot_dist);
		geometryFieldSize->set_penalty_spot_from_field_line_dist(field->penalty_spot_from_field_line_dist);
		geometryFieldSize->set_referee_width(field->referee_width);

		SSL_GeometryCameraCalibration* geometryCameraCalibration = geometryData.add_calib();
		geometryCameraCalibration->set_camera_id(0);
		geometryCameraCalibration->set_derived_camera_world_tx(0);
		geometryCameraCalibration->set_derived_camera_world_ty(0);
		geometryCameraCalibration->set_distortion(0);
		geometryCameraCalibration->set_focal_length(0);
		geometryCameraCalibration->set_principal_point_x(0);
		geometryCameraCalibration->set_principal_point_y(0);
		geometryCameraCalibration->set_q0(0);
		geometryCameraCalibration->set_q1(0);
		geometryCameraCalibration->set_q2(0);
		geometryCameraCalibration->set_q3(0);
		geometryCameraCalibration->set_tx(0);
		geometryCameraCalibration->set_ty(0);
		geometryCameraCalibration->set_tz(0);

		SSL_GeometryData * gdata = wrapperPacket.mutable_geometry();
		gdata->CopyFrom(geometryData);
	}

	string buffer;
	setBufLen(wrapperPacket.ByteSize());
	wrapperPacket.SerializePartialToArray(getSendBuffer(), getBufLen());

	SSL_WrapperPacket packet;
	packet.ParseFromString(buffer);

	frameNumber++;

	// Optional:  Delete all global objects allocated by libprotobuf.
	google::protobuf::ShutdownProtobufLibrary();

	//Simulation::mutex.unlock();
}
