#pragma once
#ifndef STEER_H
#define STEER_H

#include "LibIntelligence.h"
#include "Move.h"

namespace LibIntelligence
{
	namespace Skills
	{
		class Steer : public Move
		{
			Q_OBJECT

		public:
			Steer(QObject* parent, Robot* slave, qreal speedX=0.0, qreal speedY=0.0, qreal orientation=0.0);
			Steer(QObject* parent, Robot* slave, qreal speedX, qreal speedY, qreal dX, qreal dY);

			void step();
			void setAll(qreal speedX, qreal speedY, qreal orientation);
			void setAll(qreal speedX, qreal speedY, qreal dX, qreal dY);
			void setOrientation(qreal orientation);
			void setOrientation(qreal dX, qreal dY);
			void setRate(qreal);

		protected:
			qreal orientation, rate;
		};
	}
}

#endif // STEER_H