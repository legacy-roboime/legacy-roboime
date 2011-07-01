#include <cmath>
#include "_Skills.h"
#include "NxPhysics.h"

namespace Inteligencia {
	namespace Skills {
		void move(Robot* robot, double speed_x, double speed_y, double ang_speed){
			double teta = robot->angle();

			NxMat33 omni1;//CUSTOM:
			omni1.setRow(0, NxVec3(-0.5446f,  0.8387f,  1.0000f));
			omni1.setRow(1, NxVec3(-0.5446f, -0.8387f,  1.0000f));
			omni1.setRow(2, NxVec3( 0.7071f, -0.7071f,  1.0000f));

			NxMat33 omni2;//CUSTOM:
			omni2.setRow(0, NxVec3( 0.7071f,  0.7071f,  1.0000f));

			NxMat33 control;
			control.zero();

			//NOTE: precision loss due to NxReal casting, you've been warned
			control.setColumn(0, NxVec3((NxReal)(speed_x * NxMath::cos(-teta) + speed_y * NxMath::sin(teta)),
				(NxReal)(speed_x * NxMath::sin(-teta) + speed_y * NxMath::cos(teta)),
				(NxReal)(ang_speed * robot->body->radius())));
			omni1 *= control;
			omni2 *= control;

			NxVec3 speed_ax1 = omni1.getColumn(0);
			NxVec3 speed_ax2 = omni2.getColumn(0);

			//limite da volocidade deve ser implementado no envio, nao aqui
			robot->command(speed_ax1.x, speed_ax1.y, speed_ax1.z, speed_ax2.x);

			//double speed[4];

			//for(int i=0; i<4; i++) {
				//NxReal angPosWheel = ((NxWheel2*)nxRobot->getWheel(i))->angWheelRelRobot;

				//speeds[i] = -NxMath::sin(angPosWheel) * ( speedX * NxMath::cos( -angRobo ) + speedY * NxMath::sin( angRobo ) ) +
				//	NxMath::cos(angPosWheel) * ( speedX * NxMath::sin( -angRobo ) + speedY * NxMath::cos( angRobo ) ) +
				//	speedAng * nxRobot->bodyRadius;
			//}

			//robot->command(speed[0], speed[1], speed[2], speed[3]);
		}
	}
}