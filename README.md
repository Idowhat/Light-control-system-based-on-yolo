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
