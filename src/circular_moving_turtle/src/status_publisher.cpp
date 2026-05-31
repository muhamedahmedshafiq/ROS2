#include "rclcpp/rclcpp.hpp"
#include "turtlesim/msg/pose.hpp"
#include "geometry_msgs/msg/pose2_d.hpp"
#include "circular_moving_turtle/msg/robot_status.hpp"

using namespace std::chrono_literals;

class StatusPublisher : public rclcpp::Node
{
public:
    StatusPublisher(): Node("status_publisher")
    {
        this->declare_parameter<double>("status_rate",5.0);
        publisher_ =create_publisher<circular_moving_turtle::msg::RobotStatus>("/robot/status",10);

        pose_sub_ =create_subscription<turtlesim::msg::Pose>("/turtle1/pose",10,
                std::bind(&StatusPublisher::pose_callback,this,std::placeholders::_1));

        double rate =
            get_parameter("status_rate").as_double();

        timer_ =create_wall_timer(std::chrono::milliseconds((int)(1000.0/rate)),
                std::bind(&StatusPublisher::publish_status,this));
    }


private:
    void pose_callback(
        const turtlesim::msg::Pose::SharedPtr msg)
    {
        pose_ = *msg;

        float current_theta = msg->theta;

        if(last_theta_ > 3.0 &&
           current_theta < -3.0)
        {
            lap_count_++;
        }

        last_theta_ = current_theta;
    }

    void publish_status()
    {
        auto msg =
            circular_moving_turtle::msg::RobotStatus();

        msg.pose.x = pose_.x;
        msg.pose.y = pose_.y;
        msg.pose.theta = pose_.theta;

        msg.state = "running";

        msg.temperature =25.0 + std::abs(pose_.linear_velocity);

        msg.lap_count = lap_count_;

        publisher_->publish(msg);
    }

    turtlesim::msg::Pose pose_;

    float last_theta_ = 0.0;
    int lap_count_ = 0;

    rclcpp::Publisher<
        circular_moving_turtle::msg::RobotStatus>::SharedPtr publisher_;

    rclcpp::Subscription<
        turtlesim::msg::Pose>::SharedPtr pose_sub_;

    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc,char **argv)
{
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<StatusPublisher>());
    rclcpp::shutdown();
    return 0;

}