#pragma once
namespace Inteligencia {

	class Command {

	private:
		//fields:
		bool _force_kick, _force_dribble, _old;
		double _wheel_speed[4], _kick_speed, _dribble_speed;

	public:
		//Command(Command command);
		Command(double speed[4]);
		Command(double, double, double, double);
		Command();
		~Command();

		//methods:
		//setters:
		void kick_speed(double);
		void dribble_speed(double);
		void wheel_speed(double speed[4]);
		void force_kick(bool);
		void force_dribble(bool);
		//getters:
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