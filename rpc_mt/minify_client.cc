#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include "minify.grpc.pb.h"


using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using minify::MinifyRequest;
using minify::MinifyReply;
using minify::Minifier;

class MinifierClient {
 public:
  MinifierClient(std::shared_ptr<Channel> channel)
      : stub_(Minifier::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  int Minify(const std::string& filepath) {
    // Data we are sending to the server.
    std::ifstream f(filepath, std::ios::in|std::ios::binary|std::ios::ate);
    char* inblock;
    
    std::streampos size;
    size = f.tellg();

    inblock = new char[size];
    f.seekg(0, std::ios::beg);
    f.read(inblock, size);
    std::cout << "Original file size is " << size << std::endl;
    MinifyRequest request;

    request.set_data_in(inblock, size);
    request.set_data_in_len(size);


    MinifyReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->Minify(&context, request, &reply);

    // delete[] inblock;
    // Act upon its status.
    if (status.ok()) {
      std::ofstream f("paraglider_small.jpg", std::ios::out|std::ios::binary);
      std::cout << "returned file size is " << reply.data_out().length() << std::endl;
      f.write(reply.data_out().c_str(), reply.data_out_len());
      f.close();
      return reply.data_out().length();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return -1;
    }
  }

 private:
  std::unique_ptr<Minifier::Stub> stub_;
};

int main(int argc, char** argv) {
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint (in this case,
  // localhost at port 50051). We indicate that the channel isn't authenticated
  // (use of InsecureChannelCredentials()).
  MinifierClient minifier(grpc::CreateChannel(
      "localhost:50051", grpc::InsecureChannelCredentials()));
  int reply = minifier.Minify("paraglider.jpg");
  std::cout << "Minifier received: " << reply << std::endl;

  return 0;
}
