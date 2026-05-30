import rclpy
from rclpy.node import Node

from std_msgs.msg import Float32
from std_msgs.msg import Bool


class MinimalSubscriber(Node):

    def __init__(self):

        super().__init__('minimal_subscriber')

        self.subscription = self.create_subscription(
            Float32,
            '/sensor/distance',
            self.listener_callback,
            10
        )

        self.publisher_ = self.create_publisher(
            Bool,
            '/cmd/stop',
            10
        )

    def listener_callback(self, msg):

        stop_msg = Bool()

        if msg.data < 2.0:
            stop_msg.data = True
        else:
            stop_msg.data = False

        self.publisher_.publish(stop_msg)

        self.get_logger().info(
            f'Distance: {msg.data:.2f} -> Stop: {stop_msg.data}'
        )


def main(args=None):

    rclpy.init(args=args)

    minimal_subscriber = MinimalSubscriber()

    rclpy.spin(minimal_subscriber)

    minimal_subscriber.destroy_node()

    rclpy.shutdown()


if __name__ == '__main__':
    main()