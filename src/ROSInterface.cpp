
#include <opencv_hw/ROSInterface.h>
#include <string.h>
#include <iostream>

using namespace cv;
using namespace std;

  ROSInterface::ROSInterface() : _it(_nh) {
    _sub = _it.subscribe("/kinect2/hd/image_color", 1, &ROSInterface::imageCb, this);
    _red = _it.advertise("red", 1);
    _blue = _it.advertise("blue", 1);
    _green = _it.advertise("green", 1);
    _bgr = _it.advertise("bgr", 1);


  ROSInterface::~ROSInterface() {}

  void ROSInterface::imageCb(const sensor_msgs::ImageConstPtr& msg) {
    cv_bridge::CvImagePtr cv_ptr;
    cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    _cf.processImage(cv_ptr->image);
      
    // publishes red image
    sensor_msgs::ImagePtr _msg =
        cv_bridge::CvImage(std_msgs::Header(), "bgr8", _cf.getRedImage()).toImageMsg();
    _red.publish(_msg);
    
    
    // publishes blue image
    _msg =
        cv_bridge::CvImage(std_msgs::Header(), "bgr8", _cf.getBlueImage()).toImageMsg();
    _blue.publish(_msg);

    // publishes green image
    _msg =
        cv_bridge::CvImage(std_msgs::Header(), "bgr8", _cf.getGreenImage()).toImageMsg();
    _green.publish(_msg);
    //printf("what is this doing");

    // publishes bgr image
   _msg =
        cv_bridge::CvImage(std_msgs::Header(), "bgr8", _cf.getBGRImage()).toImageMsg();
    _bgr.publish(_msg);

  }

