#include "NxAllBalls.h"

NxAllBalls::NxAllBalls(void)
{
}

NxAllBalls::~NxAllBalls(void)
{
}

NxBall NxAllBalls::getBallByScene(int indexScene){
	for(int i=0; i<balls.size(); i++){
		if(balls[i].indexScene==indexScene)
			return balls[i];
	}
}
