#!/bin/sh
xterm -e " source /home/workspace/catkin_ws/devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/workspace/catkin_ws/src/turtlebot_simulator/turtlebot_gazebo/worlds/playground.world" &
sleep 5

xterm -e " source /home/workspace/catkin_ws/devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5

xterm -e " source /home/workspace/catkin_ws/devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch map_file:=/home/workspace/catkin_ws/src/turtlebot_simulator/turtlebot_gazebo/maps/playground.yaml" &
sleep 5

xterm -e " source /home/workspace/catkin_ws/devel/setup.bash; rosrun pick_objects pick_objects" &


