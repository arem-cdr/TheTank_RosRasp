#include <ros/ros.h>

#include <dynamic_reconfigure/server.h>
#include <robot_dynamic_param/paramConfig.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Bool.h>

ros::NodeHandle* nh_glob;

ros::Publisher* pub_reset_odo;
ros::Publisher* pub_robot_geometry;

typedef enum _msg
{
  wheelRadius_mm,
  L1pL2_mm,
  reset_odo,
 

}msg;


std_msgs::Float32MultiArray msg_robot_geometry;
std_msgs::Bool msg_reset_odo;




void callback(robot_dynamic_param::paramConfig &config, uint32_t level) {
  
  msg msg_level = (msg) level;
  switch (msg_level)
  {
	  case wheelRadius_mm:
	    msg_robot_geometry.data[0] = config.wheelRadius_mm;
	    msg_robot_geometry.data[1] = config.L1pL2_mm;
	    pub_robot_geometry->publish(msg_robot_geometry);
	    break;
	  case L1pL2_mm:
	    msg_robot_geometry.data[0] = config.wheelRadius_mm;
	    msg_robot_geometry.data[1] = config.L1pL2_mm;
	    pub_robot_geometry->publish(msg_robot_geometry);
	    break;

	  case reset_odo:
	    msg_reset_odo.data = config.reset_odo;
	    pub_reset_odo->publish(msg_reset_odo);
	    break;

	  
	  default:
	    break;
  }


}

int main(int argc, char **argv) {
  ros::init(argc, argv, "robot_dynamic_param");
  ros::NodeHandle nh;  
  nh_glob = &nh;
  
  msg_robot_geometry.data.assign(2,0.0);

  ros::Publisher pub_reset_odo_local = nh.advertise<std_msgs::Bool>("reset_odo",20);
  ros::Publisher pub_robot_geometry_local = nh.advertise<std_msgs::Float32MultiArray>("robot_geometry",20);
  
  pub_reset_odo = &pub_reset_odo_local;
  pub_robot_geometry = &pub_robot_geometry_local;



  dynamic_reconfigure::Server<robot_dynamic_param::paramConfig> server;
  dynamic_reconfigure::Server<robot_dynamic_param::paramConfig>::CallbackType f;

  f = boost::bind(&callback, _1, _2);
  server.setCallback(f);

  
  ros::spin();
  return 0;
}
