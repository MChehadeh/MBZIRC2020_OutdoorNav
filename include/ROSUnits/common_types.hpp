#pragma once
#include <stdint.h>


const struct tPacketProp{
	uint8_t pad_len = 3;
	uint8_t hdr_len = 2;
	uint8_t crc_len = 2;
	uint8_t pad_data[3] = { 0xFF, 0x00, 0xAA };
	uint8_t pad_EOH = 0xFF;
	uint8_t pad_EOP = 0xFF;
}PacketProp;

//Added FILTER_POINT in msg_type
enum class msg_type {VECTOR, FILTER_POINT, FIRE_LINE_DESC, DARKNET_ROS, SWITCHBLOCK, SWITCHOUT, TESTMSG, SERIALDATA, THREEAXISSENSORMSG, VELOCITY, ACCELERATION, THERMALIMAGE, optitrack, FLIGHTSCENARIO, POSITION, ATTITUDE, HEADING, NOZZLEMSG, UPDATECONTROLLER, RESETCONTROLLER, control_system, USERREFERENCE, controller, float_msg, BOOLEAN, INTEGER, switcher, VECTOR3D, external_reference, ack,internal_msg_start, ROS,OutdoorNavState,rtkposition,rtkvelocity,EMPTY,waypoint,POSE,FLOAT,POINTS,POSES,TAGGEDPOSES,VECTOR2D};
enum class msg_type_optitrack {position, attitude};
enum class msg_type_flight_scenario {USER, SET_PID};
enum class control_system {roll=3, pitch=4, yaw=5, x=0, y=1, z=2, pitch_rate = 6, yaw_rate = 7, null_type};
enum class block_id {PID_X=0, PID_Y=1, PID_Z=2, PID_ROLL=3, PID_PITCH=4, 
					PID_YAW=5, REF_X=6, REF_Y=7, REF_Z=8, REF_ROLL=9, REF_PITCH=10, 
					REF_YAW=11, PID_PITCH_RATE = 12, PID_YAW_RATE = 13,
					MRFT_X=14, MRFT_Y=15, MRFT_Z=16, MRFT_ROLL=17, MRFT_PITCH=18, 
					MRFT_YAW=19, NULL_ID=999};
enum class block_type {controller, provider, reference};
enum class switcher_type {controller, provider, reference, null_type};
enum class controller_type {pid, mrft};
enum class reference_type {process_variable_ref, restricted_process_variable_ref};
enum class internal_switcher_type {position_provider, attitude_provider, reference, controller};
enum class controller_msg_type {data, change_settings, command};
enum class control_system_msg_type {switch_in_out, add_block, change_PID_settings, to_system, PROVIDER, SETREFERENCE, UPDATECONTROLLER};
enum class ack_msg_type { raw_packet, payload, nozzle, obstacle, mission,ack,internal_msg_start,internal_ros };
enum class ros_msg_type {POSITION, ORIENTATION, X_PV, Y_PV, Z_PV, ROLL_PV, PITCH_PV, YAW_PV, CONTROLSYSTEM, ACTUATION};
enum class block_frequency {hz100 = 100, hz200 = 200, hhz200 = 201};
enum class msg_type_reference {X, Y, Z, YAW, NULL_TYPE};