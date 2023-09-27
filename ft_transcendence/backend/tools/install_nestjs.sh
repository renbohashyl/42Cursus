#!/bin/bash

KEYRING=/usr/share/keyrings/nodesource.gpg
curl -fsSL https://deb.nodesource.com/gpgkey/nodesource.gpg.key | gpg --dearmor | tee "$KEYRING" >/dev/null
gpg --no-default-keyring --keyring "$KEYRING" --list-keys
KEYRING=/usr/share/keyrings/nodesource.gpg
DISTRO="$(lsb_release -s -c)"
echo "deb [signed-by=$KEYRING] https://deb.nodesource.com/$NODEJSVERSION $DISTRO main" |  tee /etc/apt/sources.list.d/nodesource.list
echo "deb-src [signed-by=$KEYRING] https://deb.nodesource.com/$NODEJSVERSION $DISTRO main" |  tee -a /etc/apt/sources.list.d/nodesource.list

apt update && apt upgrade -y
apt install -y nodejs

cd $SRCDIR

npm update -g
npm install
npm install -g @nestjs/cli
npm update
npm run start:dev