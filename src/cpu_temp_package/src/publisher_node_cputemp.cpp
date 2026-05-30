#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <fstream>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

//allows to write 500ms instead of std::chrono::milliseconds(500)
using namespace std::chrono_literals;

class MinimalPublisher : public rclcpp::Node {
public:
  MinimalPublisher() : Node("minimal_publisherr") {
    // Create the publisher with topic name "topic" and queue size 10
    publisher_ = this->create_publisher<std_msgs::msg::String>("cpu_temp", 10);
    // Create a timer that executes the timer_callback every 500ms
    timer_ = this->create_wall_timer(
      500ms, std::bind(&MinimalPublisher::timer_callback, this));
  }

private:
  void timer_callback() {
    std::ifstream temp_file("/sys/class/thermal/thermal_zone0/temp");
    float temp_raw = 0;

    if (temp_file.is_open()) {
      temp_file >> temp_raw;
      temp_file.close();
    }

    float temp_c = temp_raw / 1000.0;

    auto message = std_msgs::msg::String();
    message.data ="CPU Temperature: " + std::to_string(temp_c) + " C";

    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    publisher_->publish(message);
  }

  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
};

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
