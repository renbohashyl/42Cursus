#!/bin/bash
#php-cli php-mbstring php-xml php-gd
mand_param="--allow-root --path=/var/www/html"

wp core download $mand_param
wp config create $mand_param --dbname="$MYSQL_DATABASE" --dbuser="$MYSQL_USER" --dbpass="$MYSQL_PASSWORD" --dbhost="$DB_HOST"
wp core install $mand_param --url="$LOGIN_ID.42.fr" --title="$LOGIN_ID" --admin_user="priv$LOGIN_ID" --admin_password="pr1v1l3g3d_$LOGIN_ID" --admin_email="$LOGIN_EMAIL" --skip-email
wp user create $mand_param $WP_USER_ID $WP_USER_EMAIL --role="$WP_USER_ROLE" --user_pass="$WP_USER_PASS"

sed -i 's/listen =/;listen =/g' /etc/php/7.4/fpm/pool.d/www.conf && \
sed -i 's/;clear_env/clear_env/g' /etc/php/7.4/fpm/pool.d/www.conf && \
sed -i -r -e "/;listen/i\listen = 0.0.0.0:9000" /etc/php/7.4/fpm/pool.d/www.conf

mkdir -p /run/php
chown www-data:www-data /run/php
chmod 755 /run/php 

exec php-fpm7.4 -F -R
