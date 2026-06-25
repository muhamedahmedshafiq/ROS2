from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare

def generate_launch_description():
    return LaunchDescription([
    
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            arguments=[
                '--x', '0.0',
                '--y', '0.0',
                '--z', '0.05',
                '--roll', '0.0',
                '--pitch', '0.0',
                '--yaw', '0.0',
                '--frame-id', 'base_footprint',
                '--child-frame-id', 'base_link'
            ]
        ),
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            arguments=[
                '--x', '0.5',
                '--y', '-0.10',
                '--z', '0.10',
                '--roll', '0.0',
                '--pitch', '0.0',
                '--yaw', '0.0',
                '--frame-id', 'base_link',
                '--child-frame-id', 'imu_link'
            ]
        
        ),
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            arguments=[
                '--x', '0.2',
                '--y', '0.0',
                '--z', '0.25',
                '--roll', '0.0',
                '--pitch', '0.0',
                '--yaw', '0.0',
                '--frame-id', 'base_link',
                '--child-frame-id', 'gps_link'
            ]
        
        ),
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            arguments=[
                '--x', '0.5',
                '--y', '0.15',
                '--z', '0.1',
                '--roll', '0.0',
                '--pitch', '0.0',
                '--yaw', '0.7854',  # 45 degrees in radians
                '--frame-id', 'base_link',
                '--child-frame-id', 'ultrasonic1_link'
            ]
        ),
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            arguments=[
                '--x', '0.5',
                '--y', '0.0',
                '--z', '0.1',
                '--roll', '0.0',
                '--pitch', '0.0',
                '--yaw', '0.0',
                '--frame-id', 'base_link',
                '--child-frame-id', 'ultrasonic2_link'
            ]
        ),
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            arguments=[
                '--x', '0.5',
                '--y', '-0.15',
                '--z', '0.1',
                '--roll', '0.0',
                '--pitch', '0.0',
                '--yaw', '-0.7854',  # -45 degrees in radians
                '--frame-id', 'base_link',
                '--child-frame-id', 'ultrasonic3_link'
            ]
        ),
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            arguments=[
                '--x', '-0.1',
                '--y', '0.15',
                '--z', '0.1',
                '--roll', '0.0',
                '--pitch', '0.0',
                '--yaw', '2.3562',  # 135 degrees in radians
                '--frame-id', 'base_link',
                '--child-frame-id', 'ultrasonic4_link'
            ]
        ),
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            arguments=[
                '--x', '-0.1',
                '--y', '0.0',
                '--z', '0.1',
                '--roll', '0.0',
                '--pitch', '0.0',
                '--yaw', '3.1416',  # 180 degrees in radians
                '--frame-id', 'base_link',
                '--child-frame-id', 'ultrasonic5_link'
            ]
        ),
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            arguments=[
                '--x', '-0.1',
                '--y', '-0.15',
                '--z', '0.1',
                '--roll', '0.0',
                '--pitch', '0.0',
                '--yaw', '-2.3562',  # -135 degrees in radians
                '--frame-id', 'base_link',
                '--child-frame-id', 'ultrasonic6_link'
            ]
        ),
        # RViz
        Node(
            package='rviz2',
            executable='rviz2',
            name='rviz2',
            output='screen'
        ),

        Node(
            package='robot_localization',
            executable='ekf_node',
            name='ekf_filter_node_odom',
            parameters=[PathJoinSubstitution([
                FindPackageShare('tf_localization'),
        'config',
        'ekf.yaml'
    ])],
)
    ])