/*
THE COMPUTER CODE CONTAINED HEREIN IS THE SOLE PROPERTY OF PARALLAX
SOFTWARE CORPORATION ("PARALLAX").  PARALLAX, IN DISTRIBUTING THE CODE TO
END-USERS, AND SUBJECT TO ALL OF THE TERMS AND CONDITIONS HEREIN, GRANTS A
ROYALTY-FREE, PERPETUAL LICENSE TO SUCH END-USERS FOR USE BY SUCH END-USERS
IN USING, DISPLAYING,  AND CREATING DERIVATIVE WORKS THEREOF, SO LONG AS
SUCH USE, DISPLAY OR CREATION IS FOR NON-COMMERCIAL, ROYALTY OR REVENUE
FREE PURPOSES.  IN NO EVENT SHALL THE END-USER USE THE COMPUTER CODE
CONTAINED HEREIN FOR REVENUE-BEARING PURPOSES.  THE END-USER UNDERSTANDS
AND AGREES TO THE TERMS HEREIN AND ACCEPTS THE SAME BY USE OF THIS FILE.
COPYRIGHT 1993-1999 PARALLAX SOFTWARE CORPORATION.  ALL RIGHTS RESERVED.
*/

/*
 *
 * Header file for AI system.
 *
 */

#ifndef _AI_H
#define _AI_H

#include "dxxsconf.h"
#include "fmtcheck.h"
#if defined(DXX_BUILD_DESCENT_II)
#include "fvi.h"
#include "compiler-array.h"
#endif

#define	PARALLAX	0		//	If !0, then special debugging info for Parallax eyes only enabled.

#ifdef __cplusplus
#include "countarray.h"

struct object;
struct point_seg;

#define PLAYER_AWARENESS_INITIAL_TIME   (3*F1_0)
#define MAX_PATH_LENGTH                 30          // Maximum length of path in ai path following.
#define MAX_DEPTH_TO_SEARCH_FOR_PLAYER  10
#define BOSS_GATE_MATCEN_NUM            -1
#define MAX_BOSS_TELEPORT_SEGS          100

#define ROBOT_BRAIN 7
#define ROBOT_BOSS1 17

#define ROBOT_FIRE_AGITATION 94

#if defined(DXX_BUILD_DESCENT_I) || defined(DXX_BUILD_DESCENT_II)
#if defined(DXX_BUILD_DESCENT_I)
extern	int	Boss_hit_this_frame;
#elif defined(DXX_BUILD_DESCENT_II)
#define BOSS_D2     21 // Minimum D2 boss value.
#define BOSS_COOL   21
#define BOSS_WATER  22
#define BOSS_FIRE   23
#define BOSS_ICE    24
#define BOSS_ALIEN1 25
#define BOSS_ALIEN2 26

#define NUM_D2_BOSSES 8

extern const ubyte Boss_teleports[NUM_D2_BOSSES];     // Set byte if this boss can teleport
extern const ubyte Boss_spew_more[NUM_D2_BOSSES];     // Set byte if this boss can teleport
//extern ubyte Boss_cloaks[NUM_D2_BOSSES];        // Set byte if this boss can cloak
extern const ubyte Boss_spews_bots_energy[NUM_D2_BOSSES];     // Set byte if boss spews bots when hit by energy weapon.
extern const ubyte Boss_spews_bots_matter[NUM_D2_BOSSES];     // Set byte if boss spews bots when hit by matter weapon.
extern const ubyte Boss_invulnerable_energy[NUM_D2_BOSSES];   // Set byte if boss is invulnerable to energy weapons.
extern const ubyte Boss_invulnerable_matter[NUM_D2_BOSSES];   // Set byte if boss is invulnerable to matter weapons.
extern const ubyte Boss_invulnerable_spot[NUM_D2_BOSSES];     // Set byte if boss is invulnerable in all but a certain spot.  (Dot product fvec|vec_to_collision < BOSS_INVULNERABLE_DOT)
extern int Believed_player_seg;
extern int Ai_last_missile_camera;
#endif

extern void create_awareness_event(object *objp, enum player_awareness_type_t type);         // object *objp can create awareness of player, amount based on "type"
#endif

struct boss_special_segment_array_t : public count_array_t<short, MAX_BOSS_TELEPORT_SEGS> {};
struct boss_teleport_segment_array_t : public boss_special_segment_array_t {};
struct boss_gate_segment_array_t : public boss_special_segment_array_t {};

extern fix64 Boss_cloak_start_time, Boss_cloak_end_time;
extern boss_teleport_segment_array_t Boss_teleport_segs;
extern fix64 Last_teleport_time;
extern fix Boss_cloak_duration;
extern int Boss_dying;

extern vms_vector Believed_player_pos;

extern void move_towards_segment_center(object *objp);
extern int gate_in_robot(int type, int segnum);
extern void do_ai_movement(object *objp);
extern void ai_move_to_new_segment( object * obj, short newseg, int first_time );
extern void ai_recover_from_wall_hit(object *obj, int segnum);
extern void ai_move_one(object *objp);
extern void do_ai_frame(object *objp);
extern void init_ai_object(object *objp, int initial_mode, int hide_segment);
extern void update_player_awareness(object *objp, fix new_awareness);
extern void do_ai_frame_all(void);
extern void reset_ai_states(object *objp);
extern int create_path_points(object *objp, int start_seg, int end_seg, point_seg *point_segs, short *num_points, int max_depth, int random_flag, int safety_flag, int avoid_seg);
extern void create_all_paths(void);
extern void create_path_to_station(object *objp, int max_length);
extern void ai_follow_path(object *objp, int player_visibility, vms_vector *vec_to_player);
extern void ai_turn_towards_vector(vms_vector *vec_to_player, object *obj, fix rate);
extern void ai_turn_towards_vel_vec(object *objp, fix rate);
extern void init_ai_objects(void);
extern void do_ai_robot_hit(object *robot, int type);
extern void create_n_segment_path(object *objp, int path_length, int avoid_seg);
extern void create_n_segment_path_to_door(object *objp, int path_length, int avoid_seg);
extern void make_random_vector(vms_vector *vec);
extern void init_robots_for_level(void);
extern int ai_behavior_to_mode(int behavior);
#if defined(DXX_BUILD_DESCENT_II)
extern void create_path_to_segment(object *objp, int goalseg, int max_length, int safety_flag);
extern int polish_path(object *objp, point_seg *psegs, int num_points);
extern void move_towards_player(object *objp, vms_vector *vec_to_player);
#endif

// max_length is maximum depth of path to create.
// If -1, use default: MAX_DEPTH_TO_SEARCH_FOR_PLAYER
extern void create_path_to_player(object *objp, int max_length, int safety_flag);
extern void attempt_to_resume_path(object *objp);

// When a robot and a player collide, some robots attack!
extern void do_ai_robot_hit_attack(object *robot, object *player, vms_vector *collision_point);
extern void ai_open_doors_in_segment(object *robot);
extern int ai_door_is_openable(object *objp, segment *segp, int sidenum);
extern int player_is_visible_from_object(object *objp, vms_vector *pos, fix field_of_view, vms_vector *vec_to_player);
extern void ai_reset_all_paths(void);   // Reset all paths.  Call at the start of a level.
extern int ai_multiplayer_awareness(object *objp, int awareness_level);

#if defined(DXX_BUILD_DESCENT_II)
// In escort.c
extern void do_escort_frame(object *objp, fix dist_to_player, int player_visibility);
extern void do_snipe_frame(object *objp, fix dist_to_player, int player_visibility, vms_vector *vec_to_player);
extern void do_thief_frame(object *objp, fix dist_to_player, int player_visibility, vms_vector *vec_to_player);
#endif

#if PARALLAX
extern void force_dump_ai_objects_all(const char *msg);
#else
static inline void force_dump_ai_objects_all(const char *msg)
{
	(void)msg;
}
#endif

extern void start_boss_death_sequence(object *objp);
extern void ai_init_boss_for_ship(void);
extern int Boss_been_hit;
extern fix AI_proc_time;

#if defined(DXX_BUILD_DESCENT_II)
extern fix Dist_to_last_fired_upon_player_pos;
extern vms_vector Last_fired_upon_player_pos;

#define ESCORT_GOAL_UNSPECIFIED -1

#define ESCORT_GOAL_UNSPECIFIED -1
#define ESCORT_GOAL_BLUE_KEY    1
#define ESCORT_GOAL_GOLD_KEY    2
#define ESCORT_GOAL_RED_KEY     3
#define ESCORT_GOAL_CONTROLCEN  4
#define ESCORT_GOAL_EXIT        5

// Custom escort goals.
#define ESCORT_GOAL_ENERGY      6
#define ESCORT_GOAL_ENERGYCEN   7
#define ESCORT_GOAL_SHIELD      8
#define ESCORT_GOAL_POWERUP     9
#define ESCORT_GOAL_ROBOT       10
#define ESCORT_GOAL_HOSTAGE     11
#define ESCORT_GOAL_PLAYER_SPEW 12
#define ESCORT_GOAL_SCRAM       13
#define ESCORT_GOAL_EXIT2       14
#define ESCORT_GOAL_BOSS        15
#define ESCORT_GOAL_MARKER1     16
#define ESCORT_GOAL_MARKER2     17
#define ESCORT_GOAL_MARKER3     18
#define ESCORT_GOAL_MARKER4     19
#define ESCORT_GOAL_MARKER5     20
#define ESCORT_GOAL_MARKER6     21
#define ESCORT_GOAL_MARKER7     22
#define ESCORT_GOAL_MARKER8     23
#define ESCORT_GOAL_MARKER9     24

#define MAX_ESCORT_GOALS        25

#define MAX_ESCORT_DISTANCE     (F1_0*80)
#define MIN_ESCORT_DISTANCE     (F1_0*40)

#define FUELCEN_CHECK           1000

extern fix64 Escort_last_path_created;
extern int Escort_goal_object, Escort_special_goal, Escort_goal_index;

#define GOAL_WIDTH 11

#define SNIPE_RETREAT_TIME  (F1_0*5)
#define SNIPE_ABORT_RETREAT_TIME (SNIPE_RETREAT_TIME/2) // Can abort a retreat with this amount of time left in retreat
#define SNIPE_ATTACK_TIME   (F1_0*10)
#define SNIPE_WAIT_TIME     (F1_0*5)
#define SNIPE_FIRE_TIME     (F1_0*2)

#define THIEF_PROBABILITY   16384   // 50% chance of stealing an item at each attempt
#define MAX_STOLEN_ITEMS    10      // Maximum number kept track of, will keep stealing, causes stolen weapons to be lost!

extern int   Max_escort_length;
extern int   Escort_kill_object;
struct stolen_items_t : public array<ubyte, MAX_STOLEN_ITEMS> {};
extern stolen_items_t Stolen_items;

extern void  create_buddy_bot(void);

int boss_spew_robot(struct object *objp, vms_vector *pos);
void init_ai_for_ship(void);

// Amount of time since the current robot was last processed for things such as movement.
// It is not valid to use FrameTime because robots do not get moved every frame.

// --------- John: These variables must be saved as part of gamesave. ---------
extern int              Ai_initialized;
extern int              Overall_agitation;
extern fix              Boss_teleport_interval;
extern fix              Boss_cloak_interval;        // Time between cloaks
extern fix64            Last_gate_time;
extern fix              Gate_interval;
extern fix64            Boss_dying_start_time;
extern sbyte            Boss_dying_sound_playing;
extern fix64            Boss_hit_time;
// -- extern int              Boss_been_hit;
// ------ John: End of variables which must be saved as part of gamesave. -----

// These globals are set by a call to find_vector_intersection, which is a slow routine,
// so we don't want to call it again (for this object) unless we have to.
extern vms_vector   Hit_pos;
extern int          Hit_type, Hit_seg;
extern fvi_info     Hit_data;

#ifndef NDEBUG
// Index into this array with ailp->mode

// Index into this array with aip->behavior

// Index into this array with aip->GOAL_STATE or aip->CURRENT_STATE

extern int Do_ai_flag;
extern short Break_on_object;

#endif //ifndef NDEBUG

extern int Stolen_item_index;   // Used in ai.c for controlling rate of Thief flare firing.

// -- unused, 08/07/95 -- extern void ai_turn_randomly(vms_vector *vec_to_player, object *obj, fix rate, int previous_visibility);
extern void init_ai_frame(void);

extern void create_bfs_list(int start_seg, short bfs_list[], int *length, int max_segs);
extern void init_thief_for_level();


extern int Buddy_objnum, Buddy_allowed_to_talk;

extern void start_robot_death_sequence(object *objp);
void buddy_message_str(const char * str) __attribute_nonnull();
void buddy_message(const char * format, ... ) __attribute_format_printf(1, 2);
#define buddy_message(F,...)	dxx_call_printf_checked(buddy_message,buddy_message_str,(),(F),##__VA_ARGS__)

#define SPECIAL_REACTOR_ROBOT   65
extern void special_reactor_stuff(void);
#endif

#if defined(DXX_BUILD_DESCENT_I) || defined(DXX_BUILD_DESCENT_II)
extern point_seg        Point_segs[MAX_POINT_SEGS];
#endif
extern point_seg        *Point_segs_free_ptr;

extern int ai_save_state(PHYSFS_file * fp);
extern int ai_restore_state(PHYSFS_file *fp, int version, int swap);

#ifdef EDITOR
void player_follow_path(struct object *objp);
void check_create_player_path(void);
#endif

#endif

#endif /* _AI_H */
