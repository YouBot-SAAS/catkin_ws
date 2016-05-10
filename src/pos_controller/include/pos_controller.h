#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose2D.h>
#include "../PID/PID.h"

class PositionController
{
public:
	PositionController();
	void loop();
private:
	void positionCallback(const geometry_msgs::Pose2D::ConstPtr &msg);
	ros::Subscriber pos_sub;
	ros::Publisher vel_pub;
	ros::NodeHandle nh;
	PID pidx, pidy, pidth;

	float x, y, theta;
};
