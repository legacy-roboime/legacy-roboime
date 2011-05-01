#include "stdio.h"
#include "stdlib.h"
#include <iostream>

#include "UDPServerThread.h"
#include "UDPClient.h"
#include "NxMat33.h"

void refreshDataFromSimulation()
{
	
}

NxF32 calcDistanceVec2D( NxF32 x1, NxF32 y1, NxF32 x2, NxF32 y2 )
{
	return NxMath::pow( NxMath::pow( x2 - x1, (NxF32)2 ) + NxMath::pow( y2 - y1, (NxF32)2 ), (NxF32)0.5 );
}

NxReal getBiggestAbsoluteValue(NxReal* values, int size)
{
	NxReal biggest = 0;
	int indexBiggest = 0;
	for( int i = 0; i < size; i++ )
	{
		if( NxMath::abs( values[i] ) > biggest ) 
		{
			biggest = NxMath::abs( values[i] );
			indexBiggest = i;
		}
	}
	return NxMath::abs( values[indexBiggest] );
}

NxVec3 getRobotGlobalPos(int indexRobot, int indexScene)
{
	return NxVec3(0,0,0);
}

NxReal getAngle2DFromRobot(int indexRobot, int indexScene )
{
	return 0;
}

/**
* Calcula a velocidade das 4 rodas de um determinado robo tendo como entrada as velocidades angular e linear do robo.
*/
NxReal* calcWheelSpeedFromRobotSpeed( NxReal speedAng, NxReal speedX, NxReal speedY, int indexRobot, int indexScene )
{
	NxReal* speeds;

	//Matriz de omnidirecionalidade
	//Leva em consideracao os angulos das rodas
	//-0.5446    0.8387    1.0000
	//-0.5446   -0.8387    1.0000
	//0.7071   -0.7071    1.0000
	//0.7071    0.7071    1.0000

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
							   speedAng*90 ) );

	omniMatrix1 *= controlRobot;
	omniMatrix2 *= controlRobot;

	NxVec3 speedAxleWheel1 = omniMatrix1.getColumn(0);
	NxVec3 speedAxleWheel2 = omniMatrix2.getColumn(0);

	speeds = new NxReal[4];
	speeds[0] = speedAxleWheel1.x;
	speeds[1] = speedAxleWheel1.y;
	speeds[2] = speedAxleWheel1.z;
	speeds[3] = speedAxleWheel2.x;

	//LIMITANTE DE VELOCIDADE
	NxReal biggestValue = getBiggestAbsoluteValue(speeds, 4);
	if(biggestValue > 0.001)
	{
		NxReal maxSpeed = 5;
		for( int i = 0; i < 4; i++ )
		{
				speeds[i] = speeds[i] / biggestValue * maxSpeed;
		}
	}

	return speeds;
}

void goToThisPose( NxReal x, NxReal y, NxReal angle, int indexRobot, int indexScene )
{
	//Controle proporcional
	//Velocidades Maximas
	NxReal maxSpeedAng = 1;
	NxReal maxLinearSpeed = 20;

	//Controle de angulo
	NxReal distanceAngle = angle - getAngle2DFromRobot( indexRobot, indexScene );
	NxReal speedAng;
	if(NxMath::abs(distanceAngle) > NxPi / 36.) speedAng = distanceAngle / NxPi * maxSpeedAng;
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
			else speed = -maxLinearSpeed;
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

	NxReal *speeds;
	speeds = calcWheelSpeedFromRobotSpeed( speedAng, speedX, speedY, indexRobot, indexScene );
}

void infinitePath(int indexRobot, int indexScene)
{
	static int i[10] = {0};//=0;
	//if( i>7 ) i=0;
	static bool flags[10][8] = { false };

	if(flags[indexRobot-1][7]==true) 
	{
		for(int j=0; j<8; j++)
		{
			flags[indexRobot-1][j] = false;
		}
	}

	for(int j=0; j<8; j++)
	{
		if(flags[indexRobot-1][j]==false)
		{
			i[indexRobot-1]=j;
			break;
		}
	}

	NxVec3 pontos[8];
	pontos[0].x = 1000;
	pontos[0].y = 1000;

	pontos[1].x = 2000;
	pontos[1].y = 1000;

	pontos[2].x = 2000;
	pontos[2].y = -1000;

	pontos[3].x = 1000;
	pontos[3].y = -1000;

	pontos[4].x = -1000;
	pontos[4].y = 1000;

	pontos[5].x = -2000;
	pontos[5].y = 1000;

	pontos[6].x = -2000;
	pontos[6].y = -1000;

	pontos[7].x = -1000;
	pontos[7].y = -1000;

	NxVec3 posRobot = getRobotGlobalPos(indexRobot, indexScene);
	NxReal distance = calcDistanceVec2D(pontos[i[indexRobot-1]].x, pontos[i[indexRobot-1]].y, posRobot.x, posRobot.y);
	if( distance < 100 ) 
	{
		flags[indexRobot-1][i[indexRobot-1]]=true;
	}

	goToThisPose( pontos[i[indexRobot-1]].x, pontos[i[indexRobot-1]].y, 3* NxPi / 2., indexRobot, 0);
}

int main(int argc, char **argv)
{
	printf("Modulo Inteligencia");

	//Simulation::function(1,argv);

	Thread* ut = new UDPServerThread("UDPServerThread-Inteligencia",9787, "127.0.0.1");		
	((UDPServerThread*)ut)->start();

	UDPClient* udpClient = new UDPClient("127.0.0.1", "1", 9786);
	udpClient->func1();

	infinitePath(1, 0);

	return 0;
}