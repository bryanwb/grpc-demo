#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include "minify.grpc.pb.h"
extern "C"{
#include "magickminify.h"
}

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using minify::MinifyRequest;
using minify::MinifyReply;
using minify::Minifier;

// Logic and data behind the server's behavior.
class MinifierServiceImpl final : public Minifier::Service {
  Status Minify(ServerContext* context, const MinifyRequest* request,
                  MinifyReply* reply) override {

    ssize_t data_out_len;
    void *data_out;
    data_out = magickminify((void*)(request->data_in().data()),
                            request->data_in_len(), &data_out_len);
    reply->set_data_out(data_out, data_out_len);
    reply->set_data_out_len(data_out_len);
    return Status::OK;
  }
};

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  MinifierServiceImpl service;

  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}

int main(int argc, char** argv) {
  magickminify_init();  
  RunServer();

  return 0;
}
