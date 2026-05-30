import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Imu

import csv
import os
from ament_index_python.packages import get_package_share_directory


class IMUCSVPlayer(Node):

    def __init__(self):
        super().__init__('imu_node')

        self.publisher_ = self.create_publisher(Imu, '/imu/data', 10)
        self.timer = self.create_timer(0.1, self.timer_callback)

        csv_path = os.path.join(
            get_package_share_directory('imu_csv_player'),
            'data',
            'imu_data.csv'
        )

        with open(csv_path, 'r') as file:
            reader = csv.DictReader(file)
            self.data = list(reader)

        self.index = 0
        self.get_logger().info("IMU CSV Player Started")

    def timer_callback(self):

        row = self.data[self.index]

        msg = Imu()

        # Header
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.header.frame_id = "imu_link"

        # Orientation (unknown)
        msg.orientation.x = 0.0
        msg.orientation.y = 0.0
        msg.orientation.z = 0.0
        msg.orientation.w = 1.0
        msg.orientation_covariance[0] = -1.0

        # Angular velocity
        msg.angular_velocity.x = float(row['angular_x'])
        msg.angular_velocity.y = float(row['angular_y'])
        msg.angular_velocity.z = float(row['angular_z'])

        # Linear acceleration
        msg.linear_acceleration.x = float(row['accel_x'])
        msg.linear_acceleration.y = float(row['accel_y'])
        msg.linear_acceleration.z = float(row['accel_z'])

        # Covariance unknown
        msg.angular_velocity_covariance[0] = -1.0
        msg.linear_acceleration_covariance[0] = -1.0

        self.publisher_.publish(msg)

        self.get_logger().info(f"Published IMU row {self.index}")

        self.index += 1
        if self.index >= len(self.data):
            self.index = 0


def main(args=None):
    rclpy.init(args=args)
    node = IMUCSVPlayer()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()