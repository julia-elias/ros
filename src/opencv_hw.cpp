#include <image_transport/image_transport.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "opencv");
  ColorFilter newColors = new ColorFilter();
  RosInterface  ic(newColors);
  ros::spin();
  return 0;
}