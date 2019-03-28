#include "ros/ros.h"
#include<iostream>
#include<string>
#include <sound_play/sound_play.h>
using namespace std;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "sound_talker");

    ros::NodeHandle n;

    ros::Publisher input_pub = n.advertise<sound_play::SoundRequest>("robotsound", 1000);
    //ros::Rate loop_rate(0.5);
    
    
    while(ros::ok())
    {

      sound_play::SoundRequest msg;
      
      ROS_INFO("Ready to play sound:");
      
      msg.sound=-3;
      msg.command=2;
      msg.volume=0.6;
      getline(cin,msg.arg);

      input_pub.publish(msg);

      ros::spinOnce();

      //loop_rate.sleep();

    }


  return 0;
}
