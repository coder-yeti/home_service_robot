#!/bin/sh
path_catkin_ws="/home/workspace/catkin_ws"
xterm -e " cd ${path_catkin_ws}; source devel/setup.bash; roscore " &
sleep 5

xterm -e " cd ${path_catkin_ws}; source devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 5

xterm -e " cd ${path_catkin_ws}; source devel/setup.bash; roslaunch turtlebot_gazebo gmapping_demo.launch" &
sleep 5

xterm -e " cd ${path_catkin_ws}; source devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5

xterm -e " cd ${path_catkin_ws}; source devel/setup.bash; roslaunch turtlebot_teleop keyboard_teleop.launch"
