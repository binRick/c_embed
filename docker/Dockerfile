FROM alpine:3.16 as c_embed

RUN apk upgrade
RUN apk add --no-cache gcc musl-dev
RUN apk add --no-cache  bash fish python3
RUN apk add --no-cache  zsh
RUN apk add --no-cache  meson vim
RUN apk add --no-cache automake autoconf
RUN apk add --no-cache make cmake 
RUN apk add --no-cache sed
RUN apk add --no-cache ninja
RUN apk add --no-cache git
RUN apk add --no-cache pkgconfig
RUN cp /bin/sed /bin/gsed
RUN git clone https://github.com/clarkwang/passh /repos/passh
RUN cd /repos/passh && gcc -o /bin/passh passh.c

