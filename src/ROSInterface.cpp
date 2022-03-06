#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

class ROSInterface {
  ros::NodeHandle _nh;
  image_transport::ImageTransport _it(_nh);
  
  image_transport::Publisher _red;
  image_transport::Publisher _blue;
  image_transport::Publisher _green;
  image_transport::Publisher _brg;


  image_transport::Subscriber _sub;
  ColorFilter object;

public:
  ROSInterface(ColorFilter obj) : _it(_nh)  {
    _sub = _it.subscribe("/kinect2/hd/image_color", 1, &ImageConverter::imageCb, this);
    object = obj;
    _blue = it.advertise("blue cup", 1);
    _green = it.advertise("green cup", 1);
    _red = it.advertise("red cup", 1);
    _bgr = it.advertise("all cups", 4);
    cv::namedWindow("IMAGE");

  }

  ~ROSInterface() {
    cv::destroyWindow("IMAGE");

  }

  void imageCb(const sensor_msgs::ImageConstPtr& msg) {
    VideoCapture cap("./three_cups.avi");

    cv_bridge::CvImagePtr cv_ptr;
    cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);

    object.processImage(cv_ptr->image);
    

    cv::imshow("IMAGE", cv_ptr->image);
    cv::waitKey(3);
    /*
    imshow("IMAGE", object.getBlueImage());
    waitKey(3);
    imshow("IMAGE", object.getGreenImage());
    waitKey(3);
    imshow("IMAGE", object.getRedImage());
    waitKey(3);
    imshow("IMAGE", object.getBGRImage());
    waitKey(3);
    */
    Mat frame = object.getGreenImage();
    cap >> frame;

    while (!frame.empty()) {
        msg =
        cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
        _green.publish(msg);
        //imshow("FRAME", frame);

        waitKey(10);
        cap >> frame;
    }
    
    Mat frame2 = object.getBlueImage();
    cap >> frame2;

    while (!frame2.empty()) {
        msg =
        cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame2).toImageMsg();
        _blue.publish(msg);
        //imshow("FRAME", frame);

        waitKey(10);
        cap >> frame2;
    }

    Mat frame3 = object.getRedImage();
    cap >> frame3;

    while (!frame3.empty()) {
        msg =
        cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame3).toImageMsg();
        _red.publish(msg);
        //imshow("IMAGE", frame);

        waitKey(10);
        cap >> frame3;
    }


    Mat frame4 = object.getBGRImage();
    cap >> frame4;

    while (!frame4.empty()) {
        msg =
        cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame4).toImageMsg();
        _bgr.publish(msg);
        //imshow("IMAGE", frame);

        waitKey(10);
        cap >> frame4;
    }


  }
};
