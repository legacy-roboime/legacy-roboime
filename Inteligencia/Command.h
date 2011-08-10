#pragma once
#include <vector>
using namespace std;
namespace Inteligencia {

	class Command {
		friend class Commander;

	private:
		//fields:
		int _i, _timestamp;//TODO: implement timestamping
		bool _force_kick, _force_dribble, _old;//TODO: implement these
		double _wheel_speed[4], _kick_speed, _dribble_speed;//self explanatory
		///methods:
		void _init();

	public:
		Command(Command* command);//FIXME: is this really useful?
		Command(int, double*, double dribble=0.0, double kick=0.0);//index, 4wheels, dribbler, kicker
		Command(int, double w0=0.0, double w1=0.0, double w2=0.0, double w3=0.0, double dribble=0.0, double kick=0.0);//index, wheel1, ..., wheel4, dribbler, kicker
		Command();//index will be -1 if not set, and thus won't be dispatched
		~Command();

		//setters:
		void i(int);
		void kick_speed(double);
		void dribble_speed(double);
		void wheel_speed(double speed[4]);
		void force_kick(bool);
		void force_dribble(bool);
		//getters:
		int i();
		double kick_speed();
		double dribble_speed();
		double* wheel_speed();
		bool force_kick();
		bool force_dribble();
		//useful shrothands:
		void wheels(double speed[4]);//set the 4 wheels speed
		void wheels(double, double, double, double);//set the 4 wheels speed
		void kick(double);//kicks with the given speed
		void force_kick(double);//kicks even without the ball with the given speed (front end to the setter)
		void dribble(double);//dribbles with the given speed (front end to the setter)
		void force_dribble(double);//dribbles even without the ball with the given speed
		void reset();//resets the command to its null state

	};
}