#!/bin/sh
path_catkin_ws="/home/workspace/catkin_ws"
xterm -e " cd ${path_catkin_ws} && source devel/setup.bash && roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=${path_catkin_ws}/src/turtlebot_simulator/turtlebot_gazebo/worlds/playground.world" &
sleep 5

xterm -e " cd ${path_catkin_ws} && source devel/setup.bash && roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5

xterm -e " cd ${path_catkin_ws} && source devel/setup.bash && roslaunch turtlebot_gazebo amcl_demo.launch map_file:=${path_catkin_ws}/src/turtlebot_simulator/turtlebot_gazebo/maps/playground.yaml" &
sleep 5

xterm -e " cd ${path_catkin_ws} && source devel/setup.bash && rosrun add_markers add_markers" &

