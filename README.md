# point_plotter
The point plotter package is to help user to add points and convert it to 2d goal nav message
for the purpose of route following. It will open a map and the user can double click on the map
to add points that you want the robot to follow. It will then link the points up using a curve
fitting algorithm and send the goal location to the robot.

## Prerequisites
Install [Qt5](https://www.qt.io/download) <br/>
Install [cornucopia-lib](https://github.com/matieum/cornucopia-lib)<br/>
<br/>
Not needed but useful:<br/>
Install [Qtcreator-ros plugin]( https://ros-industrial.github.io/ros_qtc_plugin/_source/How-to-Install-Users.html)<br/>

## Instruction
### Install cornucopia-lib
```
git clone https://github.com/matieum/cornucopia-lib
cd cornucopia-lib
mkdir build
cd build
cmake ..
make
sudo make install
```

### Compile program
1. clone repo into catkin workspace
2. `catkin_make`

### Run Program
1. source workspace
2. `rosrun point_plotter point_plotter`  <br/>
![Screenshot](https://raw.githubusercontent.com/Louisgcr/point_plotter/master/resources/images/PointPlotter.png)

## Built With
C++ <br/>
[ROS](http://www.ros.org/) -- Framework in use <br/>
[Qt](https://www.qt.io/) -- UI Design <br/>
[Cornucopia-lib](https://github.com/matieum/cornucopia-lib) -- Curve drawing <br/>

## Authors
Louis Goh

## License
This project is licensed under the MIT License - see the [LICENSE.md](https://github.com/Louisgcr/point_plotter/blob/master/LICENSE) file for details

## Acknowledgments
matieum for Cornucopia-lib
