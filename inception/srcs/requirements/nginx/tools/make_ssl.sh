#!/bin/bash

SSL_PATH=/var/www/html/ca
DOMAIN_NAME=$LOGIN_ID.42.fr

mkdir -p $SSL_PATH
openssl genrsa -out $SSL_PATH/$DOMAIN_NAME.key 4096
openssl req -new \
		-key $SSL_PATH/$DOMAIN_NAME.key \
		-out $SSL_PATH/$DOMAIN_NAME.csr \
		-subj /C=KR/ST=Seoul/L=Seoul/O=42Seoul/OU=$LOGIN_ID/CN=$DOMAIN_NAME/emailAddress=$LOGIN_ID@42seoul.kr

openssl x509 -req \
        -days 365 \
        -in $SSL_PATH/$DOMAIN_NAME.csr \
        -signkey $SSL_PATH/$DOMAIN_NAME.key \
        -out $SSL_PATH/$DOMAIN_NAME.crt

sed -i "s/domain_here/"$DOMAIN_NAME"/g" /etc/nginx/sites-available/default

echo "127.0.0.1 $DOMAIN_NAME" >> /etc/hosts

exec nginx -g "daemon off;"
