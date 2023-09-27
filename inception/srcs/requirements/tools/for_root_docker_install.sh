#!/bin/bash

sudo apt update && sudo apt install -y ca-certificates curl gnupg
sudo mkdir -m 0755 -p /etc/apt/keyrings
curl -4fsSL https://download.docker.com/linux/debian/gpg | sudo gpg --dearmor -o /etc/apt/keyrings/docker.gpg
echo \
  "deb [arch="$(dpkg --print-architecture)" signed-by=/etc/apt/keyrings/docker.gpg] https://download.docker.com/linux/debian \
  "$(. /etc/os-release && echo "$VERSION_CODENAME")" stable" | \
  sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
echo "nameserver 8.8.8.8" | sudo tee -a /etc/resolv.conf
sudo apt update && sudo apt install -y docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
sudo sed -i -r -e  "/localhost/i\127.0.0.1 $(whoami).42.fr" /etc/hosts
echo "nameserver 8.8.8.8" | sudo tee -a /etc/resolv.conf
