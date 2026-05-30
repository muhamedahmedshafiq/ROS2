from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([

        Node(
            package='cpu_temp_package',
            executable='publisher_node',
            name='minimal_publisher',
            output='screen',
        ),

        Node(
            package='cpu_temp_package',
            executable='subscriber_node',
            name='minimal_subscriber',
            output='screen',
        ),

    ])