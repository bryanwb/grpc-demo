# Description 

This is a minimal implementation of the single-threaded RPC server using gRPC.

I used C++ as gRPC does not have first class support for C.

The client is very dumb and simply opens `paraglider.jpg` via a hardcoded reference and asks the server to minify it via an RPC call.


## Installation

I installed gRPC's dependencies on Fedora Linux with the following commands

```
sudo dnf install -y grpc-cli grpc-devel grpc-plugins
```

## references

* [Protocol Buffers version 3](https://developers.google.com/protocol-buffers/docs/proto3)
* [gRPC C++ tutorial](https://grpc.io/docs/quickstart/cpp.html)

## Author

Bryan W. Berry, GIOS spring 2019
