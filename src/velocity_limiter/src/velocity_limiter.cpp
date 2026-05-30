#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"

using std::placeholders::_1;

class CmdVelLimiter : public rclcpp::Node
{
public:
    CmdVelLimiter() : Node("cmd_vel_limiter")
    {
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>(
            "/cmd_vel_limited",
            10);

        subscription_ = this->create_subscription<geometry_msgs::msg::Twist>(
            "/cmd_vel",
            10,
            std::bind(&CmdVelLimiter::cmd_callback, this, _1));
    }

private:
    void cmd_callback(const geometry_msgs::msg::Twist & msg)
    {
        auto limited_msg = geometry_msgs::msg::Twist();

        limited_msg.linear.x = msg.linear.x;
        limited_msg.angular.z = msg.angular.z;

        if (limited_msg.linear.x > 1.0)
        {
            RCLCPP_WARN(this->get_logger(),
                        "Limiting linear speed to 1.0");

            limited_msg.linear.x = 1.0;
        }

        if (limited_msg.angular.z > 1.5)
        {
            RCLCPP_WARN(this->get_logger(),
                        "Limiting angular speed to 1.5");

            limited_msg.angular.z = 1.5;
        }

        publisher_->publish(limited_msg);
    }

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;

    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);

    rclcpp::spin(std::make_shared<CmdVelLimiter>());

    rclcpp::shutdown();

    return 0;
}