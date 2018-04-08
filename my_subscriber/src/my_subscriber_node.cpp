#include <ros/ros.h>  // rosで必要はヘッダーファイル                             
#include <geometry_msgs/Twist.h> // ロボットを動かすために必要                   
#include <iostream>
using namespace std;

// コールバック関数。並進、回転速度の表示。                                      
void callback(const geometry_msgs::Twist::ConstPtr& vel) {
  cout << "Linear :" << vel->linear.x << endl;
  cout << "Angular:" << vel->angular.z << endl;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "my_subscriber_node");
  ros::NodeHandle nh;

  //subscriberの作成。トピック/cmd_velを購読する。バッファ数は10。               
  ros::Subscriber sub = nh.subscribe("/cmd_vel", 10, callback);

  // コールバック関数を繰り返し呼び出す。whileループが必要な場合はspinOnce()を使う。                                                                             
  ros::spin();

  return 0;
}
