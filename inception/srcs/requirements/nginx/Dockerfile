FROM debian:bullseye-20230411-slim

WORKDIR /

ENV WP \
    LOGIN_ID 

RUN apt update && \
    apt install -y nginx openssl

COPY tools/make_ssl.sh /tmp/setting.sh
COPY conf/nginx.conf /etc/nginx/sites-available/default

RUN chmod 700 /tmp/setting.sh && \
    sed -i "s/wordpress:9000/${WP}/g" /etc/nginx/nginx.conf

ENTRYPOINT ["/tmp/setting.sh"]
