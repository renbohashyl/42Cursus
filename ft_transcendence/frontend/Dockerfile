FROM debian:bullseye-20230411-slim

WORKDIR /

ENV SRCDIR \
    NODEJSVERSION

COPY tools/install_nodejs.sh /tmp/run.sh

RUN apt update && apt install -y curl wget gnupg2 lsb-release procps && \
	chmod +x /tmp/run.sh

ENTRYPOINT ["/tmp/run.sh"]