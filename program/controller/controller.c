
#include "controller.h"

void PID_rc_pass_command(attitude_stablizer_pid_t* PID_roll,attitude_stablizer_pid_t* PID_pitch,attitude_stablizer_pid_t* PID_yaw,vertical_pid_t* PID_Z,vertical_pid_t* PID_Zd,radio_controller_t* rc_command){

	PID_roll -> setpoint = rc_command -> roll_control_input;
	PID_pitch -> setpoint = rc_command -> pitch_control_input;
	PID_yaw -> setpoint = rc_command -> yaw_rate_control_input;

	if((rc_command -> mode) == MODE_3){

		PID_Z -> controller_status = CONTROLLER_ENABLE ;
		PID_Zd -> controller_status = CONTROLLER_ENABLE ;

	}else if((rc_command -> mode) == MODE_2){

		PID_Z -> controller_status = CONTROLLER_ENABLE ;
		PID_Zd -> controller_status = CONTROLLER_ENABLE ;

	}else{ // MODE_1

		PID_Z -> controller_status = CONTROLLER_DISABLE ;
		PID_Zd -> controller_status = CONTROLLER_DISABLE ;

	}

}


void PID_init(attitude_stablizer_pid_t* PID_roll,attitude_stablizer_pid_t* PID_pitch,attitude_stablizer_pid_t* PID_yaw,vertical_pid_t* PID_Z,vertical_pid_t* PID_Zd){


	PID_roll -> kp =0.20f;
	PID_roll -> kd =0.07f;
	PID_roll -> ki =0.0;
	PID_roll -> setpoint =0.0;

	PID_pitch -> kp =0.20f;
	PID_pitch -> kd =0.07f;
	PID_pitch -> ki =0.0;
	PID_pitch -> setpoint =0.0;

	PID_yaw -> kp =0.0;
	PID_yaw -> kd =1.7f;
	PID_yaw -> ki =0.0;
	PID_yaw -> setpoint =0.0;

	PID_Zd -> kp =0.35f;
	PID_Zd -> kd =0.0;
	PID_Zd -> ki =0.0;
	PID_Zd -> out_max = +30.0f;
	PID_Zd -> out_min = -30.0f;
	PID_Zd -> setpoint =0.0;

	PID_Z -> kp =0.0f;
	PID_Z -> kd =0.0;
	PID_Z -> ki =0.0;
	PID_Z -> out_max = +50.0f;
	PID_Z -> out_min = -50.0f;
	PID_Z -> setpoint =0.0;

}

void PID_output(radio_controller_t* rc_command,attitude_stablizer_pid_t* PID_roll,attitude_stablizer_pid_t* PID_pitch,attitude_stablizer_pid_t* PID_yaw,vertical_pid_t* PID_Zd){

motor_output_t motor;

	motor. m1 =0.0;
	motor. m2 =0.0;
	motor. m3 =0.0;
	motor. m4 =0.0;
	motor. m5 =0.0;
	motor. m6 =0.0;
	motor. m7 =0.0;
	motor. m8 =0.0;
	motor. m9 =0.0;
	motor. m10 =0.0;
	motor. m11 =0.0;
	motor. m12 =0.0;
	if( rc_command -> safety == ENGINE_ON) {

	motor . m1 = -10.0f + (rc_command->throttle_control_input) - (PID_roll->output) + (PID_pitch -> output) - (PID_yaw -> output) + (PID_Zd -> output);
	motor . m2 = -10.0f + (rc_command->throttle_control_input) + (PID_roll->output) + (PID_pitch -> output) + (PID_yaw -> output) + (PID_Zd -> output);
	motor . m3 = -10.0f + (rc_command->throttle_control_input) + (PID_roll->output) - (PID_pitch -> output) - (PID_yaw -> output) + (PID_Zd -> output);
	motor . m4 = -10.0f + (rc_command->throttle_control_input) - (PID_roll->output) - (PID_pitch -> output) + (PID_yaw -> output) + (PID_Zd -> output);
	set_pwm_motor(&motor);

	}else{

	motor. m1 =0.0;
	motor. m2 =0.0;
	motor. m3 =0.0;
	motor. m4 =0.0;
	set_pwm_motor(&motor);
	}
}