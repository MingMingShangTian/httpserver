#include <iostream>
#include <brpc/server.h>
#include "http_server.h"

int main(int argc, char* argv[]) {
    // Generally you only need one Server.
    brpc::Server server;

    HttpServiceImpl http_svc;
    
    // Add services into server. Notice the second parameter, because the
    // service is put on stack, we don't want server to delete it, otherwise
    // use brpc::SERVER_OWNS_SERVICE.
    if (server.AddService(&http_svc, brpc::SERVER_DOESNT_OWN_SERVICE) != 0) {
        //todo
        std::cout << "Fail to add http_svc \n";
        return -1;
    }

    // Start the server.
    brpc::ServerOptions options;
    options.idle_timeout_sec = 100;
    if (server.Start(8000, &options) != 0) {
        //todo log
        std::cout << "Fail to start HttpServer";
        return -1;
    }

    // Wait until Ctrl-C is pressed, then Stop() and Join() the server.
    server.RunUntilAskedToQuit();
    return 0;
}
