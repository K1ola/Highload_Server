FROM ubuntu:18.10

RUN apt-get update && apt-get install -y --no-install-recommends apt-utils
RUN apt-get -y install g++
RUN apt-get -y install libboost-all-dev

ADD ./ ./
#RUN apt-get install -y git cmake gcc-8 g++-8 libboost-all-dev; \
#    update-alternatives --remove-all gcc; \
#    update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-8 80 --slave /usr/bin/g++ g++ /usr/bin/g++-8;
COPY ./httptest /var/www/html/httptest

RUN g++ *.cpp -pthread -lboost_thread -lboost_filesystem -std=c++11 -lboost_system -o Highload_DZ1

EXPOSE 80

CMD ./Highload_DZ1