#ifndef SOCCER_ENV_H
#define SOCCER_ENV_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "defs.h"
#include "vector.h"

#define LEFT 0
#define RIGHT 1

typedef struct SoccerEnvironment{
  float sample_period;            /* dt between two invoking minimax_play func */
  float red_speed;
  float blue_speed;
  float red_dribble_speed;
  float blue_dribble_speed;
  float red_pass_speed;
  float blue_pass_speed;
  float red_move_radius;
  float blue_move_radius;
  float red_recv_radius;
  float blue_recv_radius;
  float robot_radius;
  float goal_size;
  float max_red_kick_dist;
  float max_blue_kick_dist;
  float hfield_w;      /* half field width */
  float hfield_h;      /* half field height */
  Vector2 red_goal;
  Vector2 blue_goal;
  Boolean left_red_side;
} SoccerEnvironment;

void soccer_env_init( void );
void soccer_env_red_side( int side );
SoccerEnvironment* soccer_env(void);

#ifdef __cplusplus
}
#endif    

#endif
