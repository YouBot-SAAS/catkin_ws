#include "../include/pos_controller.h"

PositionController::PositionController() : nh("") {
	pos_sub = nh.subscribe("youbot/ground_pose", 10, &PositionController::positionCallback, this);
	vel_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 10);

	pidx.set_params(1, 0, 0);
	pidy.set_params(1, 0, 0);
	pidth.set_params(1, 0, 0);
}

void PositionController::positionCallback(const geometry_msgs::Pose2D::ConstPtr &msg)
{
	x = msg->x;
	y = msg->y;
	theta = msg->theta;
}

void PositionController::loop()
{
	ros::Rate rate(10);
	while(nh.ok())
	{
		float nx = pidx.update(0-x);
		float ny = pidy.update(0-y);
		float nth = pidth.update(0-theta);

		geometry_msgs::Twist msg;
		msg.linear.x = nx;
		msg.linear.y = ny;
		msg.angular.z = nth;
		vel_pub.publish(msg);

		rate.sleep();
	}
}

int main(int argc, char** argv) {
	ros::init(argc, argv, "joy_teleop");
	PositionController pc;
	return 0;
}
