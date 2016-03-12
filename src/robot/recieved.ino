#include "misc.h"

void recieved_command(byte command, int args[])
{
	switch(command)
	{
		// Motors
		case CMD_SET_MOTOR_PINS: {
			recieved_command_set_motor_pins(args[0], args[1], args[2]);
		} break;
		case CMD_CONTROL_MOTOR: {
			recieved_control_motor(args[0], args[1]);
		} break;
		case CMD_SET_PWM_BOUNDS: {
			set_minimum_pwm(args[0]);
			set_maximum_pwm(args[1]);
			response_log_info("Set pwm bounds to ["+String(args[0])+","+String(args[1])+"]");
		} break;
		case CMD_SET_SAFETY_TIMEOUT: {
			set_safety_timeout(args[0] | ((args[1] & 0xFF) << 4));
		} break;
		// Steppers
		case CMD_SET_GRIPPER_PIN: {
			set_servo_pin(args[0]);
			response_log_info("Set gripper pin to "+args[0]);
		} break;
		case CMD_CONTROL_GRIPPER: {
			control_servo(args[0]);
		} break;
		// Sensors
		case CMD_SET_SENSOR_PIN: {
			response_log_info("Command has not been implemented");
		} break;
		case CMD_SENSOR_STATE: {
			response_log_info("Command has not been implemented");
		} break;
		// Cameras
		case CMD_SET_CAMERA_PINS: {
			set_camera_pins(args[0], args[1], args[2], args[3]);
		} break;
		case CMD_SWITCH_CAMERA: {
			switch_camera(args[0]);
		} break;
		// Misc
		case CMD_ECHO: {
			recieved_command_echo(args[0]);
		} break;
		default: {
			response_log_warning("Unimplemented command "+command);
		} break;
	}
}

void recieved_command_set_motor_pins(int byte_one, int pin_a, int pin_b)
{
	int motor_id = byte_one >> 4 & 0xF;
	int pin_pwm = byte_one & 0xF;

	response_log_info("Set motor "+String(motor_id)+" to A:"+String(pin_a)+", B:"+pin_b+", PWM:"+String(pin_pwm));

	set_motor_pins(motor_id, pin_a, pin_b, pin_pwm);
}

void recieved_control_motor(int motor_id_and_flags, int pwm)
{
	int motor_id = motor_id_and_flags >> 4 & 0xF;
	int flags = motor_id_and_flags & 0xF;
	bool a = flag(0x1, flags);
	bool b = flag(0x2, flags);
	set_motor(motor_id, a, b, pwm);
}

void recieved_command_echo(int byte)
{
	Serial.print((char)byte);
}