// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: minify.proto

#include "minify.pb.h"
#include "minify.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace minify {

static const char* Minifier_method_names[] = {
  "/minify.Minifier/Minify",
};

std::unique_ptr< Minifier::Stub> Minifier::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< Minifier::Stub> stub(new Minifier::Stub(channel));
  return stub;
}

Minifier::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_Minify_(Minifier_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status Minifier::Stub::Minify(::grpc::ClientContext* context, const ::minify::MinifyRequest& request, ::minify::MinifyReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_Minify_, context, request, response);
}

void Minifier::Stub::experimental_async::Minify(::grpc::ClientContext* context, const ::minify::MinifyRequest* request, ::minify::MinifyReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_Minify_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::minify::MinifyReply>* Minifier::Stub::AsyncMinifyRaw(::grpc::ClientContext* context, const ::minify::MinifyRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::minify::MinifyReply>::Create(channel_.get(), cq, rpcmethod_Minify_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::minify::MinifyReply>* Minifier::Stub::PrepareAsyncMinifyRaw(::grpc::ClientContext* context, const ::minify::MinifyRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::minify::MinifyReply>::Create(channel_.get(), cq, rpcmethod_Minify_, context, request, false);
}

Minifier::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Minifier_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Minifier::Service, ::minify::MinifyRequest, ::minify::MinifyReply>(
          std::mem_fn(&Minifier::Service::Minify), this)));
}

Minifier::Service::~Service() {
}

::grpc::Status Minifier::Service::Minify(::grpc::ServerContext* context, const ::minify::MinifyRequest* request, ::minify::MinifyReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace minify
