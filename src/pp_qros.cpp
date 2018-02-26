#include <../include/point_plotter/pp_qros.h>
#include <thread>
#include <chrono>

namespace PP{

QROS::QROS(int argc, char** argv ) :
  init_argc(argc),
  init_argv(argv)
{
    init();
}

QROS::~QROS() {
    if(ros::isStarted()) {
      ros::shutdown(); // explicitly needed since we use ros::start();
      ros::waitForShutdown();
    }
 }

bool QROS::init() {
  ros::init(init_argc,init_argv,"PointPlotter_ROS");
  if ( ! ros::master::check() ) {
    std::cout << "No ROS Master" << std::endl;
    Q_EMIT noROSMaster();
    return false;
  }
  ros::start(); // explicitly needed since our nodehandle is going out of scope.
  ros::NodeHandle n;

  // Add your ros communications here.
  position_subscriber = n.subscribe("sim_car/T_car_world", 1, &QROS::currentPositionCB, this);
  goal_publisher = n.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal", 1000);

  start();
  return true;
}


void QROS::run() {

  ros::Rate loop_rate(1);
  int count = 0;
  while ( ros::ok() ) {

    ros::spinOnce();



    loop_rate.sleep();

  }
  std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
  Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}

void QROS::currentPositionCB(const geometry_msgs::Pose::ConstPtr& msg){
  currPos = *msg;
  return;
}

void QROS::tf_map2Image(void){

  currPos.position.x;
  currPos.position.y;

  return;
}


void QROS::tf_image2Map(void){

  return;
}

}
