#pragma once
#include "Component.h"
namespace Inteligencia {

	class Body : Component {
		friend class Robot;

	private:
		//fields:
		double _height, _radius;//does this has any use?

	public:
		Body(void);
		Body(double height, double radius);
		~Body(void);

		//methods:
		void height(double);
		double height();
		void radius(double);
		double radius();

	};
}