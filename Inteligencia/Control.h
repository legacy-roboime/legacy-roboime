//TODO: get rid of this:
NxReal* Simulation::calcWheelSpeedFromRobotSpeed( NxReal speedAng, NxReal speedX, NxReal speedY, int indexRobot, int indexScene )
{
	NxReal speeds[4];
	
	//Matriz de omnidirecionalidade
	//Leva em consideracao os angulos das rodas
	//  -0.5446    0.8387    1.0000
	//  -0.5446   -0.8387    1.0000
	//   0.7071   -0.7071    1.0000
	//   0.7071    0.7071    1.0000
	
	NxReal teta = getAngle2DFromRobot( indexRobot, indexScene );
	
	NxMat33 omniMatrix1;
	NxMat33 omniMatrix2;
	
	omniMatrix1.setRow(0, NxVec3(-0.5446,	0.8387,		1.0000));
	omniMatrix1.setRow(1, NxVec3(-0.5446,	-0.8387,	1.0000));
	omniMatrix1.setRow(2, NxVec3(0.7071,	-0.7071,	1.0000));
	
	omniMatrix2.setRow(0, NxVec3(0.7071,	0.7071,		1.0000));
	
	NxMat33 controlRobot;
	controlRobot.zero();
	
	controlRobot.setColumn( 0, NxVec3( speedX * NxMath::cos( -teta ) + speedY * NxMath::sin( teta ), 
							   speedX * NxMath::sin( -teta ) + speedY * NxMath::cos( teta ),
							   speedAng * Robot::robotRadius ) );
	
	omniMatrix1 *= controlRobot;
	omniMatrix2 *= controlRobot;
	
	NxVec3 speedAxleWheel1 = omniMatrix1.getColumn(0);
	NxVec3 speedAxleWheel2 = omniMatrix2.getColumn(0);
	
	speeds[0] = speedAxleWheel1.x;
	speeds[1] = speedAxleWheel1.y;
	speeds[2] = speedAxleWheel1.z;
	speeds[3] = speedAxleWheel2.x;

	//LIMITANTE DE VELOCIDADE
	NxReal biggestValue = getBiggestAbsoluteValue(speeds, 4);
	if(biggestValue > 0.0001)
	{
		NxReal maxSpeed = 21;
		for( int i = 0; i < 4; i++ )
		{
				speeds[i] = speeds[i] / biggestValue * maxSpeed;
		}
	}
	else
	{
		for( int i = 0; i < 4; i++ )
		{
				speeds[i] = 0;
		}
	}
	
	return speeds;
}
void Simulation::controlRobot(float speedX, float speedY, float speedAng, float dribblerSpeed, float kickerSpeed, int indexRobot, int indexScene)
{
	//Execute kicker
	executeKicker( kickerSpeed, indexRobot, indexScene );

	//Control dribbler
	controlDribbler( dribblerSpeed, indexRobot, indexScene );

	//Control wheels
	NxReal* wheelsSpeeds = calcWheelSpeedFromRobotSpeed(speedAng, speedX, speedY, indexRobot, indexScene); //omnidirecionalidade
	controlWheels( wheelsSpeeds, indexScene, indexRobot); 
}
void Simulation::goToThisPose( NxReal x, NxReal y, NxReal angle, int indexRobot, int indexScene )
{
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

	controlRobot(speedX, speedY, speedAng, 0, 0, indexRobot, indexScene);
}