#include <image_transport/image_transport.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_converter");
  ColorFilter newColors = new ColorFilter();
  ImageConverter ic;
  ros::spin();
  return 0;
}