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
		void set_kick_speed(double);
		void set_dribble_speed(double);
		void set_wheel_speed(double speed[4]);
		double get_kick_speed();
		double get_dribble_speed();
		double*get_wheel_speed();
		void wheels(double speed[4]);//set the 4 wheels speed
		void wheels(double, double, double, double);//set the 4 wheels speed
		void kick(double);//kicks with the given speed
		//void kick();//kicks with the last speed
		void force_kick(double);//kicks even without the ball with the given speed (front end to the setter)
		void force_kick();//kicks even without the ball with the last speed set
		void dribble(double);//dribbles with the given speed (front end to the setter)
		//void dribble();//dribbles with the last speed
		void force_dribble(double);//dribbles even without the ball with the given speed
		void force_dribble();//dribbles even without the ball with the last speed set
		void reset();//resets the command to its null state

	};
}