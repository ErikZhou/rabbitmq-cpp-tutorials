#include <iostream>
#include "SimplePocoHandler.h"

int main(void)
{
    SimplePocoHandler handler("localhost", 5672);

    AMQP::Connection connection(&handler, AMQP::Login("guest", "guest"), "/");

    AMQP::Channel channel(&connection);
    channel.declareQueue("hello");
    channel.consume("hello", AMQP::noack).onReceived(
            [](const AMQP::Message &message,
                       uint64_t deliveryTag,
                       bool redelivered)
            {

                //std::cout <<" [x] Received "<<message.message() << std::endl;
                const char* data = message.body();
                int size = message.bodySize();
                std::string body(data, size);
                std::cout << " [.] Received " << body << std::endl;
            });

    std::cout << " [*] Waiting for messages. To exit press CTRL-C\n";
    handler.loop();
    return 0;
}
