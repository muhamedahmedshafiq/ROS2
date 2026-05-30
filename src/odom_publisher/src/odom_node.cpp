#include "rclcpp/rclcpp.hpp"
#include "nav_msgs/msg/odometry.hpp"

using namespace std::chrono_literals;

class OdomPublisher : public rclcpp::Node
{
public:
    OdomPublisher() : Node("odom_publisher"), x_(0.0)
    {
        publisher_ = this->create_publisher<nav_msgs::msg::Odometry>("/odom", 10);

        timer_ = this->create_wall_timer(
            100ms, std::bind(&OdomPublisher::timer_callback, this));

        RCLCPP_INFO(this->get_logger(), "Odometry Publisher Started");
    }

private:
    void timer_callback()
    {
        auto msg = nav_msgs::msg::Odometry();

        // ===== Header =====
        msg.header.stamp = this->get_clock()->now();
        msg.header.frame_id = "odom";
        msg.child_frame_id = "base_link";

        // ===== Position =====
        x_ += 0.1;

        msg.pose.pose.position.x = x_;
        msg.pose.pose.position.y = 0.0;
        msg.pose.pose.position.z = 0.0;

        // ===== Orientation (no rotation) =====
        msg.pose.pose.orientation.x = 0.0;
        msg.pose.pose.orientation.y = 0.0;
        msg.pose.pose.orientation.z = 0.0;
        msg.pose.pose.orientation.w = 1.0;

        // ===== Twist (velocity) =====
        msg.twist.twist.linear.x = 1.0;
        msg.twist.twist.linear.y = 0.0;
        msg.twist.twist.linear.z = 0.0;

        msg.twist.twist.angular.x = 0.0;
        msg.twist.twist.angular.y = 0.0;
        msg.twist.twist.angular.z = 0.0;

        publisher_->publish(msg);

        RCLCPP_INFO(this->get_logger(), "Published x = %.2f", x_);
    }

    rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    double x_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<OdomPublisher>());
    rclcpp::shutdown();
    return 0;
}