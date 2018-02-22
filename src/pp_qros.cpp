#include <../include/point_plotter/pp_qros.h>
#include <thread>
#include <chrono>

namespace PP{

QROS::QROS(int argc, char** argv ) :
  init_argc(argc),
  init_argv(argv)
  {
    //TODO wait for rosmaster
    /*while(init() == false){
      std::this_thread::sleep_for (std::chrono::seconds(1));
    }
    */
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
  chatter_publisher = n.advertise<std_msgs::String>("chatter", 1000);
  start();
  return true;
}


void QROS::run() {

  ros::Rate loop_rate(1);
  int count = 0;
  while ( ros::ok() ) {
    //std_msgs::String msg;
    //std::stringstream ss;
    //ss << "hello world " << count;
    //msg.data = ss.str();
    //chatter_publisher.publish(msg);
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

}
