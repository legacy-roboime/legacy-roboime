#include "minimax.h"

static Boolean max_is_root = FALSE;

static SoccerAction best_red_action;
static SoccerAction best_blue_action;

static int red_robot = 0;
static int blue_robot = 0;


static void adjust_move_tables( void );


void minimax_init( SoccerState *s )
{
 int i;
 best_red_action.prune = TRUE;
 best_blue_action.prune = TRUE; 
 best_red_action.type = null_action;
 best_blue_action.type = null_action;

 for( i = 0; i < NPLAYERS; i++ ){
   best_red_action.move[i] = s->red[i];
   best_blue_action.move[i] = s->blue[i];
   set_red_move_table( i, s->red[i] );
   set_blue_move_table( i, s->blue[i] );
 }

 best_red_action.ball_owner = s->red_ball_owner;
 best_blue_action.ball_owner = s->blue_ball_owner;
}


void minimax_use_next_red_robot(void)
{
 red_robot = (red_robot+1)%NPLAYERS;
}


void minimax_use_next_blue_robot(void)
{
 blue_robot = (blue_robot+1)%NPLAYERS;
}

SoccerAction* minimax_get_best_red_action( void )
{
 return &best_red_action;       
}


SoccerAction* minimax_get_best_blue_action( void )
{
 return &best_blue_action;       
}


void  minimax_play( SoccerState *s, int depth )
{
 s->red_time_stamp = 0;
 s->blue_time_stamp = 0; 
 minimax_use_next_red_robot();
 blue_robot = (int)(DRAND()*NPLAYERS);

 //if(  sstate_min_red_dist(s, s->ball ) < 
 //     sstate_min_blue_dist(s, s->ball ))
   minimax_playMax( s, depth );
 //else
 //  minimax_playMin( s, depth );

 adjust_move_tables();
}


void adjust_move_tables( void )
{
 int i;

 for( i=0; i < NPLAYERS; i++ ){
   if( v2_norm( v2_sub( best_red_action.move[i], 
                 best_red_action.pos[i] ) ) > EPS )
        set_red_move_table( i, best_red_action.move[i] );
   if( v2_norm( v2_sub( best_blue_action.move[i], 
                 best_blue_action.pos[i] ) ) > EPS )
        set_blue_move_table( i, best_blue_action.move[i] ); 
 }
}


void  minimax_playMax( SoccerState *s, int depth )
{
 //float evaluate = 0;//SA: Unused, due to dead store bellow
 float debug[3] = {0, 0, 0};
 max_is_root = TRUE; 
 /*evaluate = //SA: Dead store*/minimax_getMaxValue( *s, MINIMAX_MAX_LEVEL, MAX_FLOAT, -MAX_FLOAT, MAX_FLOAT, debug );

#ifdef EVALUATE_BEST_RED_ACTION
 printf("RED evaluate=%f \nred_time_weight=%f \nred_dist_weight=%f\n\n", debug[0], debug[1], debug[2]);
#endif
}


void  minimax_playMin( SoccerState *s, int depth )
{
 //float evaluate = 0;//SA: Unused, due to dead store bellow
 float debug[3] = {0, 0, 0};
 max_is_root = FALSE; 
 /*evaluate = //SA: Dead store*/minimax_getMinValue( *s, MINIMAX_MAX_LEVEL, MAX_FLOAT, -MAX_FLOAT, MAX_FLOAT, debug );

#ifdef EVALUATE_BEST_BLUE_ACTION
 printf("BLUE evaluate=%f \nred_time_weight=%f \nred_dist_weight=%f\n\n", debug[0], debug[1], debug[2]);
#endif
}


float minimax_getMaxValue(SoccerState s, int depth,
                          float parent_duration, float alpha, float beta, float* debug )
{
 int i;
 float aux; 
 SoccerState saux;
 SoccerAction action;


 if( (s.red_ball_owner < 0) && (s.blue_ball_owner < 0) )
     v2_add( s.ball, v2_scale( parent_duration, s.ball_vel ) );

 if( depth == 0 ){
      float value;
      saux = s;
      sstate_red_kick_to_goal(&saux);
      sstate_blue_kick_to_goal(&saux);
      //return sstate_evaluate(&saux)*minimax_red_time_weight_func(&s);
      value =  sstate_evaluate(&saux);
//SA: this syntax is wrong: #ifdef EVALUATE_BEST_RED_ACTION || EVALUATE_BEST_BLUE_ACTION
#if defined(EVALUATE_BEST_RED_ACTION) || defined(EVALUATE_BEST_BLUE_ACTION)
     debug[0] = value;
	  debug[1] = fabs(value)*(minimax_red_time_weight_func(&s));
	  debug[2] = fabs(value)*(-minimax_red_dist_weight_func());
      return debug[0] + debug[1] + debug[2];
#endif
      return value + fabs(value)*(minimax_red_time_weight_func(&s)
                                  /*-minimax_red_dist_weight_func()*/  );
 }

 for( i = 0; i < MAX_NPLAYS; i++ ){
     saux = s;
     action = minimax_expandMax( &saux, i, depth );
     if( !action.prune ){
       if( alpha < (aux = minimax_getMinValue( saux, depth-1, 
                    saction_red_elapsed_time( &action ), alpha, beta, debug )) ){
           alpha = aux;
           if( depth == ( max_is_root ? MINIMAX_MAX_LEVEL :
                          MINIMAX_MAX_LEVEL-1 ) )
             best_red_action = action;
       }
       if( beta <= alpha )
          break;
     }
 }
  return alpha;
}


float minimax_getMinValue(SoccerState s, int depth, 
                          float parent_duration, float alpha, float beta, float* debug )
{
 int i;
 float aux;
 SoccerState saux;
 SoccerAction action;


 if( (s.red_ball_owner < 0) && (s.blue_ball_owner < 0) )
     v2_add( s.ball, v2_scale( parent_duration, s.ball_vel ) );


 if( depth == 0 ){
     float value;
     saux = s;
     sstate_blue_kick_to_goal(&saux); 
     sstate_red_kick_to_goal(&saux); 
     //return sstate_evaluate(&saux)*minimax_blue_time_weight_func(&s);
     value =  sstate_evaluate(&saux);
//SA: this syntax is wrong: #ifdef EVALUATE_BEST_RED_ACTION || EVALUATE_BEST_BLUE_ACTION
#if defined(EVALUATE_BEST_RED_ACTION) || defined(EVALUATE_BEST_BLUE_ACTION)
	  debug[0] = value;
	  debug[1] = fabs(value)*(minimax_red_time_weight_func(&s));
	  debug[2] = fabs(value)*(-minimax_red_dist_weight_func());
      return debug[0] + debug[1] + debug[2];
#endif
     return value + fabs(value)*( minimax_blue_time_weight_func(&s)
                                 /*-minimax_red_dist_weight_func()*/ ) ;
 }

 for( i = 0; i < MIN_NPLAYS; i++ ){
      saux = s;
      action = minimax_expandMin( &saux, i, depth );
      if( !action.prune ){
          if( beta > (aux = minimax_getMaxValue( saux, depth-1, 
                      saction_blue_elapsed_time( &action ), alpha, beta, debug )) ){
              beta = aux;
              if( depth == ( max_is_root ? MINIMAX_MAX_LEVEL - 1:
                             MINIMAX_MAX_LEVEL ))
                 best_blue_action = action;
          } 
          if( beta <= alpha )
             break;
      }  
  }
  return beta;
}


float minimax_red_time_weight_func( SoccerState *s )
{
 if(fabs(-s->red_time_stamp + s->blue_time_stamp) <= 10)
	return .0001*( -s->red_time_stamp + s->blue_time_stamp);
 else if(-s->red_time_stamp + s->blue_time_stamp > 10)
	return MAX_FLOAT;
 else
	return -MAX_FLOAT;
}


float minimax_red_dist_weight_func( void )
{
 float sum = 0, m1, m2;

 if(best_red_action.ball_owner > -1){
	 Vector2 robot_move_table = v2_sub( best_red_action.pos[best_red_action.ball_owner], 
										get_red_move_table(best_red_action.ball_owner) );
	 Vector2 robot_move = v2_sub( best_red_action.pos[best_red_action.ball_owner], 
								  best_red_action.move[best_red_action.ball_owner] );
	 sum = v2_dot( robot_move_table, robot_move );
	 m1 = v2_norm( robot_move_table );
	 m2 = v2_norm( robot_move );
	 if(m1>0 && m2>0){
		sum /= m1;
		sum /= m2;
		if(sum>1)
			sum = 1;
		sum = acos(sum);
		sum /= PI;
	 }
	 else
		sum = 0;
 }

 if(sum < MAX_FLOAT)
	return sum;
 else
	 return MAX_FLOAT;
}

float minimax_blue_time_weight_func( SoccerState *s )
{
 return minimax_red_time_weight_func(s);
// return 1 + .0001*( -s->red_time_stamp + s->blue_time_stamp);
}
 

SoccerAction minimax_expandMax( SoccerState *s, int i, int depth )
{
 float move_radius , recv_radius;
 SoccerAction action = saction_red_make(s);
 move_radius = soccer_env()->red_move_radius;
 recv_radius = soccer_env()->red_recv_radius; 

 if( s->red_ball_owner >= 0 ){
     if( i== 0 )
        action = sstate_red_kick_to_goal(s);
     if ( (i >= 2) && (i < 86) )
       action = sstate_red_pass(s, i%NPLAYERS, recv_radius ); 
 }
 else{
     if( i == 1 )
       action = sstate_red_get_ball(s); 
     if( (i >=2 ) && (i < 86) )
       action = sstate_red_receive_ball( s, i%NPLAYERS ); 
 } 
 if( (i >= 86) && (i < 147 ) )
     action = sstate_red_move(s, red_robot, move_radius );
 if( i == 147 )
     action = sstate_red_block(s, red_robot, s->ball); 
 if( i == 148 ){
     s->red[red_robot] = get_red_move_table(red_robot);
     action.move[red_robot] = get_red_move_table(red_robot);
     action.prune = FALSE;
 }   
 if( i == 149 )
   action.prune = FALSE; 

 s->red_time_stamp += saction_red_elapsed_time(&action); 
 return action;
}


SoccerAction minimax_expandMin( SoccerState *s, int i, int depth )
{
 float move_radius , recv_radius;
 SoccerAction action = saction_blue_make(s);
 move_radius = soccer_env()->blue_move_radius;
 recv_radius = soccer_env()->blue_recv_radius; 
 
 if( s->blue_ball_owner >= 0 ){
     if( i== 0 )
        action = sstate_blue_kick_to_goal(s);
     if ( (i >= 2) && (i < 86) )
       action = sstate_blue_pass(s, i%NPLAYERS, recv_radius ); 
 }
 else{
     if( i == 1 )
       action = sstate_blue_get_ball(s); 
     if( (i >=2 ) && (i < 86) )
       action = sstate_blue_receive_ball( s, i%NPLAYERS ); 
 }
 if( (i >= 86) && (i < 147 ) )
     action = sstate_blue_move(s, blue_robot, move_radius ); 
 if( i == 147 )
     action = sstate_blue_block(s, blue_robot, s->ball);
 if( i == 148 ){
     s->blue[blue_robot] = get_blue_move_table(blue_robot);
     action.move[blue_robot] = get_blue_move_table(blue_robot);
     action.prune = FALSE;
 }   
 if( i == 149 )
   action.prune = FALSE; 
 
 s->blue_time_stamp += saction_blue_elapsed_time(&action); 
 return action;
}

