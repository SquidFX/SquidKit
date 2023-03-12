#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/WebSocket.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/File.h"
#include "Poco/Path.h"
#include "Poco/StreamCopier.h"
#include <iostream>
#include <sstream>
#include <fstream> // added this header

using namespace Poco::Net;
using namespace Poco::Util;
using namespace Poco;
using namespace std;

class MyRequestHandler: public HTTPRequestHandler
{
public:
    void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
    {
        if (request.find("Upgrade") != request.end() && Poco::icompare(request["Upgrade"], "websocket") == 0)
        {
            WebSocket ws(request, response);
            char buffer[1024];
            int flags;
            int n;
            do
            {
                n = ws.receiveFrame(buffer, sizeof(buffer), flags);
                if (n > 0 && (flags & WebSocket::FRAME_OP_BITMASK) == WebSocket::FRAME_OP_TEXT)
                {
                    // Do something with the received text
                }
            } while (n > 0 && (flags & WebSocket::FRAME_OP_BITMASK) != WebSocket::FRAME_OP_CLOSE);
        }
        else
        {
            // Serve XML file
            string uri = request.getURI();
            Path path(uri.substr(1));
            File file(path);
            if (file.exists() && file.isFile() && path.getExtension() == ".xml")
            {
                response.setChunkedTransferEncoding(true);
                response.setContentType("application/xml");
                ostream& ostr = response.send();
                ifstream istr(path.toString(), ios::in | ios::binary);
                StreamCopier::copyStream(istr, ostr);
            }
            else
            {
                response.setStatusAndReason(HTTPResponse::HTTP_NOT_FOUND);
                response.send() << "Not found";
            }
        }
    }
};

class MyRequestHandlerFactory: public HTTPRequestHandlerFactory
{
public:
    HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request)
    {
        return new MyRequestHandler;
    }
};

class MyServerApp: public ServerApplication
{
protected:
    int main(const vector<string>& args)
    {
        HTTPServer server(new MyRequestHandlerFactory, ServerSocket(8080), new HTTPServerParams);
        server.start();
        waitForTerminationRequest();
        server.stop();
        return Application::EXIT_OK;
    }
};

int main(int argc, char** argv)
{
    MyServerApp app;
    return app.run(argc, argv);
}

