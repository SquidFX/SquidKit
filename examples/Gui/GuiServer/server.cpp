#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/URI.h>
#include <Poco/Path.h>
#include <Poco/FileStream.h>
#include <Poco/StreamCopier.h>
#include <iostream>
#include <fstream>
#include <Poco/Net/ServerSocket.h>
#include <Poco/File.h>

class XMLRequestHandler : public Poco::Net::HTTPRequestHandler {
public:
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
        if (request.getMethod() == "GET" && Poco::Path(request.getURI()).getExtension() == "xml") {
            // Open the XML file and read its contents
            std::string filename = Poco::Path(request.getURI()).getFileName();
            Poco::File file(filename);
            if (file.exists() && file.isFile()) {
                std::ifstream f(filename, std::ios::binary);
                response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
                response.setContentType("text/xml");
                response.setContentLength(file.getSize());
                Poco::StreamCopier::copyStream(f, response.send());
            }
            else {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
                response.setContentType("text/plain");
                response.send() << "File Not Found: " << filename;
            }
        }
        else {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            response.setContentType("text/plain");
            response.send() << "Bad Request: " << request.getURI();
        }
    }
};

class XMLRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {
public:
    Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request) {
        return new XMLRequestHandler();
    }
};

int main() {
    Poco::Net::ServerSocket socket(8000);
    Poco::Net::HTTPServerParams* params = new Poco::Net::HTTPServerParams;
    params->setMaxThreads(4);
    Poco::Net::HTTPServer server(new XMLRequestHandlerFactory, socket, params);
    server.start();
    std::cout << "Starting server on port 8000..." << std::endl;
    while (true);
    server.stop();
    return 0;
}

