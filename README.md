# C++ code for RabbitMQ tutorials

## Requirements

* C++11 compiler support
* [POCO C++ Libraries](http://pocoproject.org)
* [CMake](http://www.cmake.org/)

  
On Debian/Ubuntu:

    sudo apt-get install cmake libpoco-dev

On Windows:
   vcpkg install amqpcpp, boost-asio
   amqpcpp:x64-windows                                4.3.15#1         AMQP-CPP is a C++ library for communicating with
   boost-asio:x64-windows                             1.78.0           Boost asio module

## Build
    
    git clone https://github.com/RPG-18/rabbitmq-cpp-tutorials.git
    cd rabbitmq-cpp-tutorials
    mkdir build
    cd build
    cmake ..
    make
  
## Code

[Tutorial one: "Hello World!"](http://www.rabbitmq.com/tutorial-one-python.html):

    send
    receive


[Tutorial two: Work Queues](http://www.rabbitmq.com/tutorial-two-python.html):

    new_task "A very hard task which takes two seconds.."
    worker


[Tutorial three: Publish/Subscribe](http://www.rabbitmq.com/tutorial-three-python.html):

    receive_logs
    emit_log "info: This is the log message"


[Tutorial four: Routing](http://www.rabbitmq.com/tutorial-four-python.html):

    receive_logs_direct info
    emit_log_direct info "The message"


[Tutorial five: Topics](http://www.rabbitmq.com/tutorial-five-python.html):

    receive_logs_topic "*.rabbit"
    emit_log_topic red.rabbit Hello


[Tutorial six: RPC](http://www.rabbitmq.com/tutorial-six-python.html):

    rpc_server
    rpc_client
