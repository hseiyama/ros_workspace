#include "ros/ros.h"
#include "my_service/Wheel.h"  // 自動的に作られる                                         

int main(int argc, char **argv)
{
  // 初期化　wheel_clientノード                                                            
  ros::init(argc, argv, "wheel_client");

  ros::NodeHandle nh;
  // サービスクライアントの設定                                                            
  ros::ServiceClient client = nh.serviceClient<my_service::Wheel>("wheel");

  my_service::Wheel srv;

  std::cout << "Input target linear  velocity:";
  std::cin >> srv.request.target_linear_velocity;
  std::cout << "Input target angular velocity:";
  std::cin >> srv.request.target_angular_velocity;

 // サービスを呼ぶ                                                                        
  if (client.call(srv)) {
    // 成功したらサーバーからのレスポンスを表示                                            
    ROS_INFO("Current linear_vel=%f  angular_vel=%f",
             (double) srv.response.current_linear_velocity,
             (double) srv.response.current_angular_velocity);
  }
  else {
    // 失敗したらエラー表示                                                                
    ROS_ERROR("Faild to call service wheel");
    return 1;
  }
  return 0;
}
