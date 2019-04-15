#include "ros/ros.h"
#include "turtlebot_msgs/SetFollowState.h"
#include <cstdlib>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "start");
  if (argc != 1)
  {
    ROS_INFO("usage: use number");
    return 1;
  }

  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<turtlebot_msgs::SetFollowState>("/turtlebot_follower/change_state");
  turtlebot_msgs::SetFollowState srv;
  
  
  
  srv.request.state =srv.request.FOLLOW;
  
  
  if (client.call(srv))
  {
    ROS_INFO("Sum: %ld", (long int)srv.response.result);
  }
  else
  {
    ROS_ERROR("Failed to call service ");
    return 1;
  }

  return 0;
}
