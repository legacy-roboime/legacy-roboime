#include "_Skills.h"
#include "NxPhysics.h"

namespace Inteligencia {
	namespace Skills {
		void move(Robot* robot, double speed_x, double speed_y, double ang_speed){
			double teta = robot->angle();

			NxMat33 omni1;//CUSTOM:
			omni1.setRow(0, NxVec3(-0.5446,  0.8387,  1.0000));
			omni1.setRow(1, NxVec3(-0.5446,	-0.8387,  1.0000));
			omni1.setRow(2, NxVec3( 0.7071, -0.7071,  1.0000));

			NxMat33 omni2;//CUSTOM:
			omni2.setRow(0, NxVec3( 0.7071,  0.7071,  1.0000));

			NxMat33 control;
			control.zero();

			control.setColumn(0, NxVec3(speed_x * NxMath::cos(-teta) + speed_y * NxMath::sin(teta),
										speed_x * NxMath::sin(-teta) + speed_y * NxMath::cos(teta),
										ang_speed * robot->body->radius()));
			omni1 *= control;
			omni2 *= control;

			NxVec3 speed_ax1 = omni1.getColumn(0);
			NxVec3 speed_ax2 = omni2.getColumn(0);

			//limite da volocidade deve ser implementado no envio, nao aqui
			//TODO: make a better syntax
			robot->command(speed_ax1.x, speed_ax1.y, speed_ax1.z, speed_ax2.x);
		}
	}
}