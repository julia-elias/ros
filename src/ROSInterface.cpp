#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

class ROSInterface {
  ros::NodeHandle _nh;
  //image_transport::ImageTransport _it;
  //image_transport::Publisher _blue;
  //image_transport::Publisher _red;
  //image_transport::Publisher _blue;
  //image_transport::Publisher _green;
  image_transport::Publisher _pub;


  image_transport::Subscriber _sub;
  ColorFilter object;

public:
  ROSInterface(ColorFilter obj) : _it(_nh)  {
    _sub = _it.subscribe("/kinect2/hd/image_color", 1, &ImageConverter::imageCb, this);
    object = obj;
    //_blue = it.advertise("blue cup", 1);
    //_green = it.advertise("green cup", 1);
    //_red = it.advertise("red cup", 1);
    _pub = it.advertise("all cups", 4);
    cv::namedWindow("IMAGE");

  }

  ~ROSInterface() {
    cv::destroyWindow("IMAGE");

  }

  void imageCb(const sensor_msgs::ImageConstPtr& msg) {
    cv_bridge::CvImagePtr cv_ptr;
    cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);

    object.processImage(cv_ptr->image);
    Mat frame = object.getGreenImage();
    cap >> frame;

    while (!frame.empty()) {
        sensor_msgs::ImagePtr msg =
        cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
        pub.publish(msg);
        //imshow("color", frame);

        waitKey(10);
        cap >> frame;
    }

    frame = object.getBlueImage();
    cap >> frame;

    while (!frame.empty()) {
        sensor_msgs::ImagePtr msg =
        cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
        pub.publish(msg);
        //imshow("color", frame);

        waitKey(10);
        cap >> frame;
    }

    frame = object.getRedImage();
    cap >> frame;

    while (!frame.empty()) {
        sensor_msgs::ImagePtr msg =
        cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
        pub.publish(msg);
        //imshow("color", frame);

        waitKey(10);
        cap >> frame;
    }


    frame = object.getBGRImage();
    cap >> frame;

    while (!frame.empty()) {
        sensor_msgs::ImagePtr msg =
        cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
        pub.publish(msg);
        //imshow("color", frame);

        waitKey(10);
        cap >> frame;
    }




  }
};
