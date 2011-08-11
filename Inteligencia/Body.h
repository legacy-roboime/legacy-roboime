#pragma once
#include "Inteligencia.h"
#include "Component.h"

namespace Inteligencia {

	class Body : Component {
		friend class Robot;

	private:
		//fields:
		real _height, _radius;//does this has any use?

	public:
		Body(void);
		Body(real height, real radius);
		~Body(void);

		//methods:
		void height(real);
		real height();
		void radius(real);
		real radius();

	};
}