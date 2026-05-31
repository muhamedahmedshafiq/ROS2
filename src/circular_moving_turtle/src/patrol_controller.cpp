#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "std_srvs/srv/empty.hpp"

using namespace std::chrono_literals;

class PatrolController : public rclcpp::Node
{
public:
    PatrolController() : Node("patrol_controller")
    {
        this->declare_parameter<double>("linear_speed", 1.5);
        this->declare_parameter<double>("angular_speed", 1.0);

        publisher_ =create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel",10);

        timer_ =create_wall_timer(100ms,std::bind(&PatrolController::publish_cmd,this));

        stop_srv_ =create_service<std_srvs::srv::Empty>("/stop",
                std::bind(&PatrolController::stop_callback,this,std::placeholders::_1,std::placeholders::_2));

        continue_srv_ =create_service<std_srvs::srv::Empty>("/continue",
            std::bind(&PatrolController::continue_callback,this,std::placeholders::_1,std::placeholders::_2));
    }

private:
    void publish_cmd()
    {
        auto msg = geometry_msgs::msg::Twist();

        if(running_)
        {
            double linear =get_parameter("linear_speed").as_double();
            double angular =get_parameter("angular_speed").as_double();
            msg.linear.x = linear;
            msg.angular.z = angular;
        }

        publisher_->publish(msg);
    }

    void stop_callback(const std::shared_ptr<std_srvs::srv::Empty::Request>,std::shared_ptr<std_srvs::srv::Empty::Response>)
    {
        running_ = false;
    }

    void continue_callback(const std::shared_ptr<std_srvs::srv::Empty::Request>,std::shared_ptr<std_srvs::srv::Empty::Response>)
    {
        running_ = true;
    }

    bool running_ = true;

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;

    rclcpp::Service<std_srvs::srv::Empty>::SharedPtr stop_srv_;
    rclcpp::Service<std_srvs::srv::Empty>::SharedPtr continue_srv_;
};

int main(int argc,char **argv)
{
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<PatrolController>());
    rclcpp::shutdown();
    return 0;
}