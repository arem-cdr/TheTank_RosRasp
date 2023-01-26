#include <ros/ros.h>

#include <dynamic_reconfigure/server.h>
#include <robot_dynamic_param/paramConfig.h>
#include <std_msgs/Bool.h>

ros::NodeHandle* nh_glob;
ros::Publisher* pub_glob;
std_msgs::Bool msg;

void callback(robot_dynamic_param::paramConfig &config, uint32_t level) {
   
  msg.data = !msg.data;
  pub_glob->publish(msg);

}

int main(int argc, char **argv) {
  ros::init(argc, argv, "robot_dynamic_param");
  ros::NodeHandle nh;  
  nh_glob = &nh;
  ros::Publisher pub = nh.advertise<std_msgs::Bool>("parameter_update",20);
  msg.data = false;
  pub_glob = &pub;
  dynamic_reconfigure::Server<robot_dynamic_param::paramConfig> server;
  dynamic_reconfigure::Server<robot_dynamic_param::paramConfig>::CallbackType f;

  f = boost::bind(&callback, _1, _2);
  server.setCallback(f);

  
  ros::spin();
  return 0;
}
