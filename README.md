# 基于yoloV3的灯光控制系统
基于YOLOv3的智能灯光控制系统。通过调用教室摄像头获取图像，并将其输入YOLO网络进行处理。当检测到教室内有人时，系统会自动开启灯光；若在设定时间内未检测到人员，灯光则会自动关闭。

## 项目流程

教室的摄像头用于捕捉图像，YOLO网络对图像进行处理，判断教室内是否有人。服务器通过WiFi或Zigbee将结果发送到灯光控制终端。灯光控制系统接收开关灯的指令，同时保持墙上的实体电源开关可用。灯光可以通过自动控制或手动控制进行操作。

## 原理图与PCB展示

<p align="center">Schematic</p>
<p align = "center">
<img src="https://github.com/Idowhat/img_video/blob/main/img_Light_control/schematic.jpg?raw=true" width = "30%" height = "30%" />
</p>

<p align="center">Physical display</p>

<p align = "center">    
<img  src="https://github.com/Idowhat/img_video/blob/main/img_Light_control/concrete_figure.jpg?raw=true" hight="600" width="200" />
<img  src="https://github.com/Idowhat/img_video/blob/main/img_Light_control/Shell_object.jpg?raw=true"  hight="600" width="200" />
<img  src="https://github.com/Idowhat/img_video/blob/main/img_Light_control/Shell.jpg?raw=true"  hight="600" width="200" />
<img  src="https://github.com/Idowhat/img_video/blob/main/img_Light_control/PCB_2D.jpg?raw=true" hight="600" width="200" />
</p>




# Light-control-system-based-on-yolo
A smart light control system based on yolov3 calls the images captured by the classroom's cameras and feeds them into the yolo network. Lights are turned on when someone is there, and turned off when no one is there for a certain period of time.

## Project Flow

The classroom's camera is utilized to capture images, the yolo network processes the images to obtain occupied or unoccupied status, and the server room sends the results down to the light control terminal via wifi (or zigbee). The light control system receives the command to switch the light on and off. And keep the electrical switch on the wall. The lights can be controlled either automatically or manually.

## Schematic diagram and PCB display

<p align="center">Schematic</p>
<p align = "center">
<img src="https://github.com/Idowhat/img_video/blob/main/img_Light_control/schematic.jpg?raw=true" width = "30%" height = "30%" />
</p>

<p align="center">Physical display</p>

<p align = "center">    
<img  src="https://github.com/Idowhat/img_video/blob/main/img_Light_control/concrete_figure.jpg?raw=true" hight="600" width="200" />
<img  src="https://github.com/Idowhat/img_video/blob/main/img_Light_control/Shell_object.jpg?raw=true"  hight="600" width="200" />
<img  src="https://github.com/Idowhat/img_video/blob/main/img_Light_control/Shell.jpg?raw=true"  hight="600" width="200" />
<img  src="https://github.com/Idowhat/img_video/blob/main/img_Light_control/PCB_2D.jpg?raw=true" hight="600" width="200" />
</p>
