# gstreamer_in_c_on_ubuntu_22
control gstreamer with C on ubuntu 22

## If just want to run execution file
Ubuntu 22 comes with gstreamer, so run the file of .run directly. <br>

![pic](pic/1.png)<br>
![pic](pic/2.png)<br>

## if want to compile c file
sudo apt-get update  <br>
sudo apt-get update \build-essential \ <br>
libgstreamer1.0-dev \ <br>
libgstreamer-plugins-base1.0-dev <br>
<br>
gcc play_videotest.c -o play_videotest.out \`pkg-config --cflags --libs gstreamer-1.0\` <br>
<br>
gcc usbcam_640x480_mjpg.c -o usbcam_640x480_mjpg.out \`pkg-config --cflags --libs gstreamer-1.0\` <br>
<br>
### If the document help you, how about buy street cats a fish can ?<br>
