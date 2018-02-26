#ifndef PP_QROS_HPP_
#define PP_QROS_HPP_

#include <ros/ros.h>
#include <ros/network.h>
#include <geometry_msgs/PoseStamped.h>
#include <string>
#include <std_msgs/String.h>
#include <sstream>
#include <QThread>
#include <QStringListModel>

/*****************************************************************************
 * ** Namespaces
 * *****************************************************************************/

namespace PP {

/*****************************************************************************
 * ** Classes
 * *****************************************************************************/

class QROS : public QThread {
	    Q_OBJECT
	public:
		QROS(int argc, char** argv );
		virtual ~QROS();
    bool init();
    void run();

    void currentPositionCB(const geometry_msgs::Pose::ConstPtr& msg);
    geometry_msgs::Pose currPos;

    void tf_map2Image(void);
    void tf_image2Map(void);

  private:
    int init_argc;
    char** init_argv;
    ros::Publisher goal_publisher;
    ros::Subscriber position_subscriber;

  Q_SIGNALS:
    void rosShutdown();
    void noROSMaster();
    void rosPubMessage();
};

}

#endif
