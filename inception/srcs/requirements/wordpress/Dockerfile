FROM debian:bullseye-20230411-slim

WORKDIR /

ARG MYSQL_USER \
    MYSQL_PASSWORD \
    MYSQL_DATABASE \
	DB_HOST \
    LOGIN_ID \
    LOGIN_EMAIL \
    WP_USER_ID \
	WP_USER_EMAIL \
	WP_USER_PASS \
	WP_USER_ROLE

COPY tools/init_wordpress.sh /tmp/run.sh
ADD https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar /usr/local/bin/wp

RUN apt update && \
	apt install -y php7.4 php-fpm php-mysql mariadb-client curl && \
	mkdir -p /var/www/html && \
	chmod +x /usr/local/bin/wp && \
	chmod 700 /tmp/run.sh

ENTRYPOINT ["/tmp/run.sh"]
