from setuptools import find_packages, setup

package_name = 'tf_localization'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),

    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),

        # launch files
        ('share/' + package_name + '/launch',
            ['launch/localization.launch.py']),

        # config files
        ('share/' + package_name + '/config',
            ['config/ekf.yaml']),
    ],

    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='muhamed',
    maintainer_email='muhamed.ahmed.shafiq@gmail.com',
    description='TF + Robot Localization package',
    license='MIT',

    entry_points={
        'console_scripts': [
            'orientation_analysis = tf_localization.orientation_analysis:main',
        ],
    },
)