#include <ros/ros.h>
#include <iostream>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Image.h>
#include "opencv_apps/RotatedRectStamped.h"
using namespace std;
class SubandPub
{
private:
   ros::NodeHandle n;
   ros::Subscriber pos_sub;
   ros::Publisher vel_pub;
public:
   SubandPub()
   {
      pos_sub = n.subscribe("/camshift/track_box", 1000, &SubandPub::callback,this);
      vel_pub = n.advertise<geometry_msgs::Twist>("cmd_vel_mux/input/navi", 1000);
   }
   void callback(const opencv_apps::RotatedRectStamped::ConstPtr& msg)
   {
        int mark_size;
	int width =500;  
	int height=300; 
	int pos_x= 0;
	double control_speed= 0.0;
	double control_turn= 0.0;
	cout<<"In callback"<<endl;
      mark_size = msg->rect.size.width * msg->rect.size.height;
      if(mark_size <1000 or mark_size >60000)
      {
       cout<<"In if"<<endl;
	control_speed = 0.0;
       control_turn = 0.0;
      }
       else
      {
	cout<<"In else";
        pos_x = msg->rect.center.x;
        int size=width*height;
        double a=(double)mark_size/(double)size;
        cout<<mark_size<<endl;
        cout<<a<<endl;
        control_speed = 0.6 *a;
        control_turn = 0.3 *(width/2 - pos_x)/width;
        cout<<control_speed<<endl;
        cout<<control_turn<<endl;
      }
	geometry_msgs::Twist twist; 
	twist.linear.x = control_speed;
	twist.linear.y = 0.0;
	twist.linear.z = 0.0;
	twist.angular.x = 0.0;
	twist.angular.y = 0.0;
	twist.angular.z = control_turn; 
	vel_pub.publish(twist);
   }

};


int main(int argc, char **argv)
{
   ros::init(argc, argv, "follow");
 
  
   SubandPub object;   
   ros::spin();

  return 0;
}
  










