#!/bin/sh
path_catkin_ws="/home/workspace/catkin_ws"
xterm -e " cd ${path_catkin_ws} && source devel/setup.bash && roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=${path_catkin_ws}/src/turtlebot_simulator/turtlebot_gazebo/worlds/playground.world" &
sleep 5

xterm -e " cd ${path_catkin_ws} && source devel/setup.bash && roslaunch add_markers view_navigation.launch path:=${path_catkin_ws}/src/rviz/navigation.rviz" &
sleep 5

xterm -e " cd ${path_catkin_ws} && source devel/setup.bash && roslaunch turtlebot_gazebo amcl_demo.launch map_file:=${path_catkin_ws}/src/turtlebot_simulator/turtlebot_gazebo/maps/playground.yaml" &
sleep 5

xterm -e " cd ${path_catkin_ws} && source devel/setup.bash && rosrun add_markers add_markers" &
sleep 5

xterm -e " cd ${path_catkin_ws} && source devel/setup.bash && rosrun pick_objects pick_objects" &
