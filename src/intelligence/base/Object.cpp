#include "Object.h"
#include <qvector.h>
#include <qlist.h>

using namespace LibIntelligence;

Object::Object(qreal x, qreal y, qreal z, qreal sx, qreal sy, qreal sz, qreal orien, qreal asz)
	: x_(x),
	y_(y),
	z_(z),
	orientation_(orien),
	speedX_(sx),
	speedY_(sy),
	speedZ_(sz),
	angSpeedZ_(asz),

	linearRegressionVx(new LinearRegression()),
	linearRegressionVy(new LinearRegression()),
	linearRegressionVang(new LinearRegression()),
	xOld(x),
	yOld(y),
	orientationOld(orien),
	timeOld(0)
{}

Object::Object(const Object& object)
{
	this->x_ = object.x();
	this->y_ = object.y();
	this->z_ = object.z();
	this->orientation_ = object.orientation();
	this->angSpeedZ_ = object.angSpeedZ();
	this->speedX_ = object.speedX();
	this->speedY_ = object.speedY();
	this->speedZ_ = object.speedZ();
	linearRegressionVx = new LinearRegression(*(object.linearRegressionVx));
	linearRegressionVy = new LinearRegression(*(object.linearRegressionVy));
	linearRegressionVang = new LinearRegression(*(object.linearRegressionVang));
}

Object::~Object()
{
	if(linearRegressionVx)
		delete linearRegressionVx;
	if(linearRegressionVy)
		delete linearRegressionVy;
	if(linearRegressionVang)
		delete linearRegressionVang;
}


void Object::setX(qreal x)
{
	x_ = x;
}

qreal Object::x() const
{
	return x_;
}

void Object::setY(qreal y)
{
	y_ = y;
}

void Object::setY(qreal y, qreal time_capture)
{
	static qreal last_time_capture;

	//TODO: tirar daqui e colocar o estimador de velocidade no tracker
	qreal diffTime = time_capture - last_time_capture;
	qreal speed = (y - y_)/(diffTime);
	
	if(abs(speed) < 10000 && diffTime>0){ //margem limiar para velocidade maxima dos objetos
		speedY_ = (speedY_ + 2.*speed)/3.;
		//printf("SPEEDY: %f\n",speed);
	}
	
	y_ = y;
	last_time_capture = time_capture;
}

qreal Object::y() const
{
	return y_;
}

void Object::setZ(qreal z)
{
	z_ = z;
}

qreal Object::z() const
{
	return z_;
}

qreal Object::orientation() const
{
	return orientation_;
}

void Object::setSpeedX(qreal sx)
{
	speedX_ = sx;
}

qreal Object::speedX() const
{
	return speedX_;
}

void Object::setSpeedY(qreal sy)
{
	speedY_ = sy;
}

qreal Object::speedY() const
{
	return speedY_;
}

void Object::setSpeedZ(qreal sz)
{
	speedZ_ = sz;
}

qreal Object::speedZ() const
{
	return speedZ_;
}

void Object::setAngSpeedZ(qreal asz)
{
	angSpeedZ_ = asz;
}

qreal Object::angSpeedZ() const
{
	return angSpeedZ_;
}

void Object::setXY(qreal x, qreal y)
{
	setX(x);
	setY(y);
}

void Object::setXYZ(qreal x, qreal y, qreal z)
{
	setX(x);
	setY(y);
	setZ(z);
}

void Object::setSpeedXY(qreal sx, qreal sy)
{
	setSpeedX(sx);
	setSpeedY(sy);
}

void Object::setSpeedXYZ(qreal sx, qreal sy, qreal sz)
{
	setSpeedX(sx);
	setSpeedY(sy);
	setSpeedZ(sz);
}

Object& Object::operator=(const Object& object)
{
	this->x_ = object.x();
	this->y_ = object.y();
	this->z_ = object.z();
	this->speedX_ = object.speedX();
	this->speedY_ = object.speedY();
	this->speedZ_ = object.speedZ();
	return *this;
}

void Object::setOrientation(qreal o)
{
	orientation_ = o;
}


void Object::updateSpeed(double time) {
	double velocity;
	double deltaTime = (time - this->timeOld);
	if(deltaTime != 0){
		this->timeOld = time;
		QPointF oldPoint;

		//regress�o speedX
		double deltaX = this->x() - xOld;
		xOld = this->x();
		velocity = deltaX/deltaTime;
		QPointF vX(time,velocity);
		linearRegressionVx->addPoint(vX);
		speedX_ = linearRegressionVx->estimateY(time);
		//cout << "Velocidade X: " << speedX_ << endl;

		//regress�o speedY
		double deltaY = this->y() - yOld;
		yOld = this->y();
		velocity = deltaY/deltaTime;
		QPointF vY(time,velocity);
		linearRegressionVy->addPoint(vY);
		speedY_ = linearRegressionVy->estimateY(time);
		//cout << "Velocidade Y: " << speedY_ << endl;


		//regress�o speed
		double deltaOrientation = this->orientation() - orientationOld;
		orientationOld = this->orientation();
		if(abs(deltaOrientation) <  1){		//GAMBIARRA PARA SOLUCIONAR O PROBLEMA DE TRANSI��O DE 2PI PARA 0
			velocity = deltaOrientation/deltaTime;
			QPointF vAng(time,velocity);
			linearRegressionVang->addPoint(vAng);
			angSpeedZ_ = linearRegressionVang->estimateY(time);
			//OBS: SE ATIVAR O COUT VAI RETARDAR O PROGRAMA DAI O ENVIO DE MSG PARA O SIMULADOR FICA PREJUDICADO
			//cout << "Delta Orientation " << deltaOrientation << endl;
			//cout << "Velocidade Estimada Ang: " << angSpeedZ_ << " " << "Velocidade Real: " << velocity << endl;
		}
	} 
}

Object Object::distance(const Object* object2) const
{
	return Object(object2->x() - x_, object2->y() - y_, object2->z() - z_);
}

qreal Object::module() const
{
	return sqrt(x_ * x_ + y_ * y_);
}