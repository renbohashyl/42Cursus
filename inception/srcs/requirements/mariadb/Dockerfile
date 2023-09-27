FROM debian:bullseye-20230411-slim

WORKDIR /

ENV MYSQL_ROOT_PASSWORD \
    MYSQL_USER \
    MYSQL_PASSWORD \
    MYSQL_DATABASE

COPY tools/init_conf.sh /tmp/init_conf.sh
COPY tools/init_db_user.sh /tmp/run.sh

RUN apt update && \
	apt install -y mariadb-server && \
	mkdir -p /var/run/mysqld && \
	rm -rf /var/lib/mysql/* && \
	chmod +x /tmp/init_conf.sh && /tmp/init_conf.sh && rm -f /tmp/init_conf.sh && \
	chown -R mysql:mysql /tmp/run.sh /var/run/mysqld /var/lib/mysql && \
	chmod 777 /tmp/run.sh /var/run/mysqld

USER mysql

ENTRYPOINT ["/tmp/run.sh"]
