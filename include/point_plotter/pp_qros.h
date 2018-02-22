#ifndef PP_QROS_HPP_
#define PP_QROS_HPP_

#include <ros/ros.h>
#include <string>
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

};

}

#endif
