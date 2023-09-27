#!/bin/bash

sed -i 's/127.0.0.1/0.0.0.0/g' /etc/mysql/mariadb.conf.d/50-server.cnf
sed -i -r -e "/basedir/i\port			= 3306" /etc/mysql/mariadb.conf.d/50-server.cnf
