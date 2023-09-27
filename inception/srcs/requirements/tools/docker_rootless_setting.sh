#!/bin/bash

sudo apt install -y dbus-user-session fuse-overlayfs uidmap
dockerd-rootless-setuptool.sh install

systemctl --user start docker
systemctl --user enable docker
sudo loginctl enable-linger $(whoami)

export DOCKER_HOST=unix://$XDG_RUNTIME_DIR/docker.sock
docker context use rootless

echo "net.ipv4.ip_unprivileged_port_start=443" | sudo tee -a /etc/sysctl.conf

echo "\n-------------------------------"
echo "|this system will reboot [y/n]|"
echo "\n-------------------------------"

while [ 1 ]
do
	read yn
	if [ "$yn" == "y" ]
	then
		sudo reboot
	elif [ "$yn" == "n" ]
	then
		echo "you will need to reboot for open port 443"
		break
	fi
done
