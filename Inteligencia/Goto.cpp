#include "Simulation.h"
#include "_Skills.h"
namespace Inteligencia {
	namespace Skills {

		Goto::Goto(){}
		Goto::~Goto(){}

		//TODO: traduzir controle
		void Goto::Pose(Robot robot, double x, double y, double angle){/*
			//Controle proporcional
			//Velocidades Maximas
			NxReal maxSpeedAng = 6;
			NxReal maxLinearSpeed = 6000;

			//Controle de angulo
			NxReal distanceAngle = (NxReal)angle - getAngle2DFromRobot( indexRobot, indexScene ); //TODO: remover redundância de getAngle2DFromRobot tanto em goToThisPose quanto em calcWheelSpeedFromRobotSpeed
			NxReal speedAng;
			if(NxMath::abs(distanceAngle) > NxPi / 72.) speedAng = distanceAngle / NxPi * maxSpeedAng;
			else speedAng = 0;

			//Controle de posicao
			NxVec3 position = getRobotGlobalPos( indexRobot, indexScene );
			NxReal distanceX = (NxReal)x - position.x;
			NxReal distanceY = (NxReal)y - position.y;
			NxReal distance = calcDistanceVec2D( position.x, position.y, (NxReal)x, (NxReal)y);
			NxReal distanceThreshold = 2000.;
			NxReal speedX;
			NxReal speedY;
			NxReal speed;
			if(NxMath::abs(distance) > 10.)
			{
				if( distance > distanceThreshold ) 
					if( distance > 0 ) speed = maxLinearSpeed;
					else speed = - maxLinearSpeed;
				else 
					speed = distance / distanceThreshold * maxLinearSpeed;

				speedX = speed * NxMath::cos( NxMath::atan2( distanceY, distanceX ) );
				speedY = speed * NxMath::sin( NxMath::atan2( distanceY, distanceX ) );
			}
			else
			{
				speedX = 0;
				speedY = 0;
			}

			//TODO: Mandar comandos
			/*
			//Controle proporcional
			//Velocidades Maximas
			NxReal maxSpeedAng = 6;
			NxReal maxLinearSpeed = 6000;

			//Controle de angulo
			NxReal distanceAngle = angle - getAngle2DFromRobot( indexRobot, indexScene ); //TODO: remover redundância de getAngle2DFromRobot tanto em goToThisPose quanto em calcWheelSpeedFromRobotSpeed
			NxReal speedAng;
			if(NxMath::abs(distanceAngle) > NxPi / 72.) speedAng = distanceAngle / NxPi * maxSpeedAng;
			else speedAng = 0;

			//Controle de posicao
			NxVec3 position = getRobotGlobalPos( indexRobot, indexScene );
			NxReal distanceX = x - position.x;
			NxReal distanceY = y - position.y;
			NxReal distance = calcDistanceVec2D( position.x, position.y, x, y);
			NxReal distanceThreshold = 2000.;
			NxReal speedX;
			NxReal speedY;
			NxReal speed;
			if(NxMath::abs(distance) > 10.)
			{
				if( distance > distanceThreshold ) 
					if( distance > 0 ) speed = maxLinearSpeed;
					else speed = - maxLinearSpeed;
				else 
					speed = distance / distanceThreshold * maxLinearSpeed;

				speedX = speed * NxMath::cos( NxMath::atan2( distanceY, distanceX ) );
				speedY = speed * NxMath::sin( NxMath::atan2( distanceY, distanceX ) );
			}
			else
			{
				speedX = 0;
				speedY = 0;
			}

			controlRobot(speedX, speedY, speedAng, 0, 0, indexRobot, indexScene);*/
		}

	}
}