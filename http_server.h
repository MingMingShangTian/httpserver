#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H
#include <brpc/server.h>
class HttpRequest {
public:
    int a;
    int b;
};

class HttpResponse {
public:
    int c;
};


// Service with static path.
class HttpServiceImpl {
public:
    HttpServiceImpl() {};
    virtual ~HttpServiceImpl() {};
    void Sum(google::protobuf::RpcController* cntl_base,
              const HttpRequest* req,
              HttpResponse* resp,
              google::protobuf::Closure* done) {
        // This object helps you to call done->Run() in RAII style. If you need
        // to process the request asynchronously, pass done_guard.release().
        brpc::ClosureGuard done_guard(done);
        
        brpc::Controller* cntl = static_cast<brpc::Controller*>(cntl_base);
        // Fill response.
        cntl->http_response().set_content_type("text/plain");

        resp-> c = req->a + req->b;
    }
};
#endif

