cmake_minimum_required(VERSION 3.13)
project(aeop C)

set(CMAKE_C_STANDARD 11)

add_executable(aeop aeop.c php_aeop.h)
#定义php源码路径，这里根据自己的真实路径来更改
set(PHP_SOURCE ~/c/php-src/)

#引入php需要的扩展源码
include_directories(.)
include_directories(${PHP_SOURCE}/main)
include_directories(${PHP_SOURCE}/Zend)
include_directories(${PHP_SOURCE}/sapi)
include_directories(${PHP_SOURCE}/pear)
include_directories(${PHP_SOURCE})

add_custom_target(makefile COMMAND make && sudo make install WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})