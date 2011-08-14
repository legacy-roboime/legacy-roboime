#pragma once
#include "Inteligencia.h"
#include <vector>

using namespace std;

namespace Inteligencia {

	class Command {
		friend class Commander;

	private:
		//fields:
		int _id;
		double _timestamp;//TODO: implement timestamping
		bool _force_kick, _force_dribble, _old;//TODO: implement these
		real _wheel_speed[4], _kick_speed, _dribble_speed;//self explanatory
		///methods:
		void _init();

	public:
		Command(Command* command);//useful for threading the parser
		Command(int, real*, real dribble=0.0, real kick=0.0);//index, 4wheels, dribbler, kicker
		Command(int, real w0=0.0, real w1=0.0, real w2=0.0, real w3=0.0, real dribble=0.0, real kick=0.0);//index, wheel1, ..., wheel4, dribbler, kicker
		Command();//index will be -1 if not set, and thus won't be dispatched
		~Command();

		//setters:
		void id(int);
		void kick_speed(real);
		void dribble_speed(real);
		void wheel_speed(real speed[4]);
		void force_kick(bool);
		void force_dribble(bool);
		void timestamp_now();
		void timestamp(double);
		//getters:
		int id();
		real kick_speed();
		real dribble_speed();
		real* wheel_speed();
		bool force_kick();
		bool force_dribble();
		double timestamp();
		//useful shrothands:
		void wheels(real speed[4]);//set the 4 wheels speed
		void wheels(real, real, real, real);//set the 4 wheels speed
		void kick(real);//kicks with the given speed
		void force_kick(real);//kicks even without the ball with the given speed (front end to the setter)
		void dribble(real);//dribbles with the given speed (front end to the setter)
		void force_dribble(real);//dribbles even without the ball with the given speed
		void reset();//resets the command to its null state

	};
}