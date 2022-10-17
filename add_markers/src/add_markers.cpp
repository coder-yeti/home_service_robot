#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>
#include <math.h>

//Globally define goal 1 and goal 2
float goal1_x = -2.0;
float goal1_y =  1.0;
float goal2_x =  1.0;
float goal2_y =  1.0;

bool picked_up = false;
bool dropped_off = false;

void callBack(const nav_msgs::Odometry::ConstPtr& msg){
	if(picked_up == false && dropped_off == false){
		//I have not taken exact distance through distance formula here to account for tolerance values and errors 
		if(abs(goal1_x - msg->pose.pose.position.x) == 0.0 && abs(goal1_y - msg->pose.pose.position.y) == 0.0) {
			ROS_INFO("Pickup if case is working");		
			picked_up = true;
		}
	}


	if(picked_up == true && dropped_off == false){	
		if(abs(goal2_x - msg->pose.pose.position.x) == 0.0 && abs(goal2_y - msg->pose.pose.position.y) == 0.0) {
			ROS_INFO("Drop off if case is working ");
			dropped_off = true;
		}
	}
	

}


int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber odom_sub = n.subscribe("odom",1000,callBack);

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

  while (ros::ok())
  {
    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

      // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

      // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = goal1_x;
    marker.pose.position.y = goal1_y;
    marker.pose.position.z = 0.0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

      // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.45;
    marker.scale.y = 0.45;
    marker.scale.z = 0.45;

      // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 0.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0f;

    marker.lifetime = ros::Duration();

    marker_pub.publish(marker); 
  

    while(picked_up == false){
      ros::spinOnce();
    }

    if(picked_up == true){
      ros::Duration(5).sleep();
      marker.action = visualization_msgs::Marker::DELETE;
      marker_pub.publish(marker);
      ROS_INFO("Agent 007 has taken the package");
    }

    while(dropped_off == false){
      ros::spinOnce();
    }
   
    if(dropped_off == true){
      marker.pose.position.x = goal2_x;
      marker.pose.position.y = goal2_y;
      marker.pose.orientation.w = 1.5;
      ros::Duration(5).sleep();
      marker.action = visualization_msgs::Marker::ADD;
      marker_pub.publish(marker);
      ROS_INFO("Package Received");
    }

    return 0;
    //r.sleep();
  }
}
