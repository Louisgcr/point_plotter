# point_plotter
The point plotter package is to help user to add points and convert it to 2d goal nav message
for the purpose of route following. It will open a map and the user can double click on the map
to add points that you want the robot to follow. It will then link the points up using a curve
fitting algorithm and send the goal location to the robot.

##Prerequisites
Install [Qt5] (https://www.qt.io/download)
Install [cornucopia-lib](https://github.com/matieum/cornucopia-lib)

Not needed but useful:
Install [Qtcreator-ros plugin]( https://ros-industrial.github.io/ros_qtc_plugin/_source/How-to-Install-Users.html)

##Instruction
###To install cornucopia-lib
'''
git clone https://github.com/matieum/cornucopia-lib
cd cornucopia-lib
mkdir build
cd build
cmake ..
make
sudo make install
'''

###To compile program
1. clone repo into catkin workspace
2. run 'catkin_make'

###Run Program
1. source workspace
2. run 'rosrun point_plotter point_plotter'

##Built With
C++
[ROS](http://www.ros.org/) -- Framework in use
[Qt](https://www.qt.io/) -- UI Design
[Cornucopia-lib](https://github.com/matieum/cornucopia-lib) -- Curve drawing

##Authors
Louis Goh

##License
This project is licensed under the MIT License - see the [LICENSE.md](https://github.com/Louisgcr/point_plotter/blob/master/LICENSE) file for details

##Acknowledgments
matieum for Cornucopia-lib
