#include <iostream>
#include <Poco/Net/WebSocket.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/URI.h>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <url>" << std::endl;
        return 1;
    }

    try
    {
        // Parse URL
        Poco::URI uri(argv[1]);

        // Create WebSocket connection
        Poco::Net::HTTPClientSession cs(uri.getHost(), uri.getPort());
        Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, uri.getPathAndQuery(), Poco::Net::HTTPMessage::HTTP_1_1);
        Poco::Net::HTTPResponse response;
        Poco::Net::WebSocket ws(cs, request, response);

        // Send message
        ws.send("Hello, server!");

        // Receive message
        std::string message;
        int flags;
        ws.receiveFrame(message, flags);

        // Print received message
        std::cout << "Received message: " << message << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

