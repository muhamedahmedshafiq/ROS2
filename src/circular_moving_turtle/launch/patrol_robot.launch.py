from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():

    params = os.path.join(
        get_package_share_directory(
            'circular_moving_turtle'),
        'params',
        'patrol_params.yaml'
    )

    return LaunchDescription([

        Node(
            package='turtlesim',
            executable='turtlesim_node'
        ),

        Node(
            package='circular_moving_turtle',
            executable='status_publisher',
            parameters=[params]
        ),

        Node(
            package='circular_moving_turtle',
            executable='patrol_controller',
            parameters=[params]
        )
    ])