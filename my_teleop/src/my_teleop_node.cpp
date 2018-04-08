#include "ros/ros.h"  // rosで必要はヘッダーファイル
#include <geometry_msgs/Twist.h> // ロボットを動かすために必要
using namespace std;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "my_teleop_node");
    // initでROSを初期化し、my_teleop_nodeという名前をノードにつける
    // 同じ名前のノードが複数あるとだめなので、ユニークな名前をつける

    ros::NodeHandle nh;
    // ノードハンドラの作成。ハンドラは必要時に起動される。

    ros::Publisher  pub;
    // パブリッシャの作成。トピックに対してデータを送信。

    ros::Rate rate(10);
    // ループの頻度を設定するためのオブジェクトを作成。この場合は10Hz、1秒間に10回数、1ループ100ms。

    geometry_msgs::Twist vel;
    // geometry_msgs::Twist　この型は並進速度と回転速度(vector3:3次元ベクトル) を合わせたもので、速度指令によく使われる

    pub= nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
    // マスターにgeometry_msgs::Twist型のデータを送ることを伝える
    // マスターは/cmd_velトピック(1番目の引数）を購読する
    // 全てのノードにトピックができたことを知らせる(advertise)。
    // 2番目の引数はデータのバッファサイズ

    cout << "f: forward, b: backward, r: right, l:left" << endl;

    while (ros::ok()) { // このノードが使える間は無限ループする
        char key;  // 入力キーの値

        cin >> key; // 標準入力からキーを読み込む
        cout << key << endl; // 読み込んだキーの値を標準出力へ出力

        switch (key) {
        case 'f': // fキーが押されていたら
            vel.linear.x  =  0.5;
            break;
        case 'b':
            vel.linear.x  = -0.5;
            break;
        case 'l':
            vel.angular.z =  1.0;
            break;
        case 'r':
            vel.angular.z = -1.0;
            break;
            // linear.xは前後方向の並進速度(m/s)。前方向が正。
            // angular.zは回転速度(rad/s)。反時計回りが正。
        }

        pub.publish(vel);    // 速度指令メッセージをパブリッシュ（送信）
        ros::spinOnce();     // １回だけコールバック関数を呼び出す
        vel.linear.x  = 0.0; // 並進速度の初期化
        vel.angular.z = 0.0; // 回転速度の初期化
        rate.sleep();        // 指定した周期でループするよう寝て待つ

    }

    return 0;
}
