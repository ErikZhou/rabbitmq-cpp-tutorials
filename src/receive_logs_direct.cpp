#include <algorithm>
#include <iostream>

#include "SimplePocoHandler.h"

int main(int argc, const char* argv[]) {
  if (argc == 1) {
    std::cout << "Usage: " << argv[0] << " [info] [warning] [error]"
              << std::endl;
    return 1;
  }
  SimplePocoHandler handler("localhost", 5672);

  AMQP::Connection connection(&handler, AMQP::Login("guest", "guest"), "/");

  AMQP::Channel channel(&connection);

  channel.declareExchange("direct_logs", AMQP::direct);

  auto receiveMessageCallback = [](const AMQP::Message& message,
                                   uint64_t deliveryTag, bool redelivered) {
    const char* data = message.body();
    int size = message.bodySize();
    std::string body(data, size);

    std::cout << " [x] " << message.routingkey() << ":" << body << std::endl;
  };

  AMQP::QueueCallback callback = [&](const std::string& name, int msgcount,
                                     int consumercount) {
    std::for_each(&argv[1], &argv[argc], [&](const char* severity) {
      channel.bindQueue("direct_logs", "", severity);
      channel.consume(name, AMQP::noack).onReceived(receiveMessageCallback);
    });
  };
  channel.declareQueue(AMQP::exclusive).onSuccess(callback);

  std::cout << " [*] Waiting for messages. To exit press CTRL-C\n";
  handler.loop();
  return 0;
}
