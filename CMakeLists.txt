cmake_minimum_required(VERSION 3.14)
project(Highload_DZ1)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost 1.62.0 REQUIRED system)

add_executable(Highload_DZ1 main.cpp Server.cpp Server.h Request.cpp Request.h Response.cpp Response.h Config.cpp Config.h ThreadPool.cpp ThreadPool.h Session.cpp Session.h)
target_link_libraries(Highload_DZ1 -pthread -lboost_thread -lboost_filesystem ${Boost_LIBRARIES})