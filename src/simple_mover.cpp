#include "ros/ros.h"
#include "std_msgs/Float64.h"

class JointAnglesPublisher
{
  public:

  JointAnglesPublisher()
  {
    // Create a publisher that can publish a std_msgs::Float64 message on the /simple_arm/joint_1_position_controller/command topic
    mJoint1Pub = mNode.advertise<std_msgs::Float64>("/simple_arm/joint_1_position_controller/command", 10);
    
    // Create a publisher that can publish a std_msgs::Float64 message on the /simple_arm/joint_2_position_controller/command topic
    mJoint2Pub = mNode.advertise<std_msgs::Float64>("/simple_arm/joint_2_position_controller/command", 10);
  }

  void PublishJointAngles(const std_msgs::Float64& joint1_angle, const std_msgs::Float64& joint2_angle)
  {
    mJoint1Pub.publish(joint1_angle);
    mJoint2Pub.publish(joint2_angle);
  }

  private:

  ros::NodeHandle mNode; 
  ros::Publisher  mJoint1Pub;
  ros::Publisher  mJoint2Pub;

};//End of class JointAnglesPublisher


int main(int argc, char** argv)
{
    // Itinialize the arm_mover node
    ros::init(argc, argv, "arm_mover");

    // Initialize object of JointAnglesPublisher class
    JointAnglesPublisher jointAnglesPubObject;

    // Set loop frequency of 10 Hz
    ros::Rate loop_rate(10);

    int start_time, elapsed;

    // Get ROS start time
    while (not start_time) {
        start_time = ros::Time::now().toSec();
    }

    while (ros::ok()) {
        // Get ROS elapsed time
        elapsed = ros::Time::now().toSec() - start_time;

        // Set the arm joint angles
        std_msgs::Float64 joint1_angle, joint2_angle;
        joint1_angle.data = sin(2 * M_PI * 0.1 * elapsed) * (M_PI / 2);
        joint2_angle.data = sin(2 * M_PI * 0.1 * elapsed) * (M_PI / 2);

        // Publish the arm joint angles
        jointAnglesPubObject.PublishJointAngles(joint1_angle, joint2_angle);

        // Sleep for the time remaining until 10 Hz is reached
        loop_rate.sleep();
    }

    return 0;

}
