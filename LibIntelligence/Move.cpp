#include "Move.h"
#include "Robot.h"
#include <cmath>
#include <QVector>
#include "PID.h"
#define MAX_RPS_BIWHEEL 4.0
#define WHEEL_INTERDISTANCE 
//#define REALROBOT

using namespace LibIntelligence;
using namespace Skills;

#define MIN(x,y) (x < y ? x : y)
#define MAX(x,y) (x > y ? x : y)
#define M_2PI	6.2831853071795865
#define M_PI	3.1415926535897932
#define __q(x)	((x) > M_PI ? (x) - M_2PI : -(x) > M_PI ? (x) + M_2PI : (x))
qreal __n(qreal ang) {return ang > M_PI ? __n(ang - M_2PI) : -ang > M_PI ? __n(ang + M_2PI) : ang;}



Move::Move(QObject* p, Robot* r, qreal sx, qreal sy, qreal sa)
	: Skill(p, r),
	speedX(sx),
	speedY(sy),
	speedAngular(sa),
	oldSpeedX(0.0), 
	oldSpeedY(0.0),
	oldTime(QTime::currentTime()),
	oldSpeedAngular(0.0)
{}

void Move::setAll(qreal sx, qreal sy, qreal sa)
{
	speedX = sx;
	speedY = sy;
	speedAngular = sa;
}

void Move::setSpeeds(qreal sx, qreal sy)
{
	speedX = sx;
	speedY = sy;
}

void Move::setSpeedAngular(qreal sa)
{
	//speedAngular = MIN(sa, spe
	speedAngular = sa;
}

bool Move::busy()
{
	return false;
}

void Move::step()
{
	static qreal theta, alpha;
	static QVector<qreal> speed;//(robot()->wheelsSize());
	speed.resize(robot()->wheelsSize());
	
	theta = robot()->orientation();

#ifdef REALROBOT
	QTime newTime=QTime::currentTime();
	int intervalo = oldTime.msecsTo(newTime);
	oldTime=newTime;

	qreal acelLin;
	qreal acelAng;
	if(false && robot()->id()==1){
		acelLin=300*intervalo/1000;
		acelAng=acelLin/robot()->body().radius();
	} else {
		acelLin=200*intervalo/1000;
		acelAng=acelLin/robot()->body().radius();
	}

	qreal diferenca=speedX-oldSpeedX;
	if(diferenca>0){
		if(diferenca>acelLin){
			oldSpeedX+=acelLin;
		} else {
			oldSpeedX+=diferenca;
		}
	} else {
		if(diferenca<-acelLin){
			oldSpeedX-=acelLin;
		} else {
			oldSpeedX+=diferenca;
		}
	}

	diferenca=speedY-oldSpeedY;
	if(diferenca>0){
		if(diferenca>acelLin){
			oldSpeedY+=acelLin;
		} else {
			oldSpeedY+=diferenca;
		}
	} else {
		if(diferenca<-acelLin){
			oldSpeedY-=acelLin;
		} else {
			oldSpeedY+=diferenca;
		}
	}

	diferenca=speedAngular-oldSpeedAngular;
	if(diferenca>0){
		if(diferenca>acelAng){
			oldSpeedAngular+=acelAng;
		} else {
			oldSpeedAngular+=diferenca;
		}
	} else {
		if(diferenca<-acelAng){
			oldSpeedAngular-=acelAng;
		} else {
			oldSpeedAngular+=diferenca;
		}
	}


	qreal speedAngularacel=speedAngular;
	speedAngular=oldSpeedAngular;

	qreal speedXacel=speedX;
	speedX=oldSpeedX;

	qreal speedYacel=speedY;
	speedY=oldSpeedY;
#endif

//	speedAngular = speedAngular < 6 ? speedAngular : 6;
	
	//check if the robot is biwheel or omniwheel
	qreal n = robot()->wheelsSize();
	if(n > 2) {//omniwheel
		for(int i = 0; i < n; i++) {
			alpha = robot()->wheels()[i].angle();
			speed[i] = cos(alpha) * (speedY * cos(theta) - speedX * sin(theta))
					 - sin(alpha) * (speedX * cos(theta) + speedY * sin(theta))
					 + speedAngular * robot()->wheels()[i].distance();
			//NOTE:
			speed[i] /= robot()->wheels()[i].radius();//this is so the speed is angular
			speed[i] /= M_2PI;
		}
	} else {//biwheel
		alpha = atan2(speed[1],speed[0]);
		
		if(abs(theta-alpha)>0.01) //guess 
		{
			CONTROLLER_S pid(2, 0, 0, 12, 2.0);//guess
			pid.entrada = __q(alpha-theta);
			pid.realimentacao = 0;
			pidService(pid);
			speed[0] = speed[1] = pid.saida;
	
			if(theta>alpha) // Clockwise rotation
			{
				speed[0] *= -1;
				//speed[1] = 1;
			}
			else
			{
				//speed[0] = 1;
				speed[1] *= -1;
			}
		}
		else
		{
			speed[0] = speed[1] = 20*sqrt(speedX*speedX + speedY*speedY);
		}
	}

	qreal biggestValue = abs(speed[0]);

	for(int i = 1; i < speed.size(); i++)
		biggestValue = biggestValue > abs(speed[i]) ? biggestValue : abs(speed[i]);

	qreal maxSpeed = 12.0;//TODO: limit is hardcoded, unhardcode it
	if(biggestValue > 0.001) {
		if(biggestValue > maxSpeed) {
			for(int i = 0; i < speed.size(); i++) {
				speed[i] = speed[i] * maxSpeed / biggestValue;
			}
		}
	} else {
		for(int i = 0; i < speed.size(); i++) speed[i] = 0.0;
	}
	robot()->setCommandWheels(speed);

#ifdef REALROBOT
	speedX=speedXacel;
	speedY=speedYacel;
	speedAngular=speedAngularacel;
#endif
}