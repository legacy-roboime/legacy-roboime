#include "soccer.h"

static void is_blue_kick_scored( SoccerState *s, Vector2 goal );


void sstate_blue_get_ball( SoccerState *s )
{
 float t;
 int closest_red, closest_blue=-1;

 if( (s->red_ball_owner < 0) && (s->blue_ball_owner < 0) ){
   if( (t =  sstate_time_to_blue_get_ball( s, &closest_blue )) <
       sstate_time_to_red_get_ball( s, &closest_red ) && ( t > 0 ) ){
          DEBUG("blue get ball\n");  
        s->ball = v2_add( s->ball, v2_scale( t, s->ball_vel ) );
        s->ball_vel = v2_make(0,0);
        s->blue[closest_blue] = s->ball;
        s->blue_ball_owner = closest_blue;  
   }
 }
} 


void sstate_blue_receive_ball( SoccerState *s, int recv )
{
 float t, time_to_red_block, time_to_receive;
 int closest_red;

 if( (s->red_ball_owner < 0) && (s->blue_ball_owner < 0) ){ 
   time_to_red_block = sstate_time_to_blue_get_ball( s, &closest_red ); 
   time_to_receive = time_to_intersect( s->ball, s->ball_vel, s->blue[recv], 
									    v2_norm( s->ball_vel ), soccer_env()->blue_speed );

   if( (time_to_receive > 0 ) && (time_to_red_block > time_to_receive) ){
       t = DRAND()*( time_to_red_block - time_to_receive ) + time_to_receive;
       s->ball = v2_add( s->ball, v2_scale( t, s->ball_vel ) );  
       s->ball_vel = v2_make(0,0);
       s->blue[recv] = s->ball;
       s->blue_ball_owner = recv;  
   }
 }
}


void sstate_blue_kick_to_goal( SoccerState *s )
{
 int i;
 float k;
 Vector2 p;

 if( (s->blue_ball_owner >= 0) && (s->red_ball_owner < 0) ){
   for( k = -.5*soccer_env()->goal_size; k < .5*soccer_env()->goal_size; k += soccer_env()->robot_radius ){ 
	 if(soccer_env()->left_red_side)
       p =  v2_make( - soccer_env()->field_w * .5, k );
	 else
       p =  v2_make( + soccer_env()->field_w * .5, k );
     is_blue_kick_scored(s, p );
     if( s->goal_received )
       DEBUG( "goal received :(\n" );
   }
 }
}


static void is_blue_kick_scored( SoccerState *s, Vector2 goal )
{
 int i;
 float dotprod;
 Vector2  goal_direction, friend_relpos, proj;

 s->goal_received = TRUE;
 for( i = 0; i < NPLAYERS; i++ ){
       goal_direction = v2_unit( v2_sub( goal, s->blue[s->blue_ball_owner] ) );
       friend_relpos = v2_sub( s->red[i], s->blue[s->blue_ball_owner ] );
       proj = v2_scale( dotprod = v2_dot( friend_relpos, goal_direction ), 
                      goal_direction );
       if( (dotprod > 0 ) && 
          v2_norm( v2_sub( friend_relpos, proj )) < soccer_env()->robot_radius )
          s->goal_received = FALSE;  /* if a friend robot blocks it */
     } 
}


void sstate_blue_pass( SoccerState *s, int recv, float recv_radius )
{
 double t;
 Vector2 p, new_recv_pos;

 if( (s->blue_ball_owner >= 0) && (s->blue_ball_owner != recv ) &&
     (s->red_ball_owner < 0 )){
         p = v2_make(recv_radius*DRAND()*cos(2*PI*DRAND()),
                     recv_radius*DRAND()*sin(2*PI*DRAND()) );
         new_recv_pos = v2_add( s->blue[recv], p );
         if( (t = sstate_possible_blue_pass( s, recv, new_recv_pos )) > 0 ){
             DEBUG2( "blue pass: %i -> %i\n", s->blue_ball_owner , recv );
             s->blue_ball_owner = recv;
             s->blue[recv] = new_recv_pos;
             s->ball = new_recv_pos;
         }
 } 
}


void sstate_blue_move( SoccerState *s, float radius )
{
 int i;
 float d;
 Vector2 p, new_pos;

 for( i = 0; i < NPLAYERS; i++ ){
   do{
     p = v2_make(radius*DRAND()*cos(2*PI*DRAND()),
                 radius*DRAND()*sin(2*PI*DRAND()) );
     if( i == s->blue_ball_owner )
        v2_scale( (soccer_env()->blue_dribble_speed/soccer_env()->blue_speed)*radius, p );
     d = v2_norm( p );
     new_pos = v2_add( s->blue[i], p ); 
   }while( (sstate_min_red_dist(s, new_pos) < d) ||
           (!sstate_is_inside_field( s, new_pos ) &&
            sstate_is_inside_field( s, s->blue[i] ) ) );
   DEBUG5( "blue move %i: (%f,%f) -> (%f,%f)", i,
           s->blue[i].x, s->blue[i].y , new_pos.x, new_pos.y ); 
   s->blue[i] = new_pos;
   if( i == s->blue_ball_owner ){
      s->ball = new_pos;
      DEBUG( "*");
   }
   DEBUG("\n");
 }
}


float sstate_min_blue_dist( SoccerState *s, Vector2 p )
{
 int i;
 float min_sqrdist = MAX_FLOAT; 

 for( i = 0; i < NPLAYERS; i++ )
    if( min_sqrdist > v2_sqrnorm( v2_sub(p, s->blue[i])) )
        min_sqrdist = v2_sqrnorm( v2_sub(p, s->blue[i]) );

 return sqrt( min_sqrdist );    
}


int sstate_closest_blue( SoccerState *s, Vector2 p )
{
 int i, closest;
 float min_sqrdist = MAX_FLOAT; 

 for( i = 0; i < NPLAYERS; i++ )
    if( min_sqrdist > v2_sqrnorm( v2_sub(p, s->blue[i])) ){
        min_sqrdist = v2_sqrnorm( v2_sub(p, s->blue[i]) );
        closest = i;
    }

 return closest;  
}


float sstate_time_to_blue_get_ball( SoccerState *s, int *closest )
{
 int i;
 float t, mint;

 mint = MAX_FLOAT;
 for( i = 0; i < NPLAYERS; i++ ){ 
   t = time_to_intersect( s->ball, s->ball_vel, s->blue[i],
                          v2_norm( s->ball_vel ), soccer_env()->blue_speed );
   if( t < mint ){
      mint = t;
      if( closest != NULL )
         *closest = i;
   } 
 }
 return mint;
}


float sstate_possible_blue_pass( SoccerState *s, int recv, Vector2 p )
{
 int i;
 float t1, t2, t_move, t_pass;
 Vector2 pass_dir, move_dir;

 if( !sstate_is_inside_field(s,p) )
   return -1;

 pass_dir = v2_sub(p,s->ball);
 move_dir = v2_sub(p,s->blue[recv]);
 t_move = v2_norm(v2_sub( s->blue[recv], p ))/soccer_env()->blue_speed;
 t_pass = v2_norm(v2_sub( s->blue[ s->blue_ball_owner ], p ))/
                  soccer_env()->blue_pass_speed;

 for( i = 0; i < NPLAYERS; i++ ){
    t1 = time_to_intersect( s->ball, pass_dir, s->red[i], 
                            soccer_env()->blue_pass_speed, soccer_env()->red_speed );
    t2 = time_to_intersect( s->blue[recv], move_dir, s->red[i],
                            soccer_env()->blue_speed, soccer_env()->red_speed );
    if( (( t1 > 0 ) && (t1 < t_pass)) ||  (( t2 > 0 ) && (t2 < t_move )))
       return -1;
 }

 if( t_move < t_pass )
    return t_pass;
 else
    return -1; 
}
