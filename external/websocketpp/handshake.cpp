#include "handshake.h"
#include <iostream>
#include <boost/asio.hpp>
#include "client.hpp"
#include "websocketpp.hpp"

std::string handshake(const std::string& url/*, std::string socketIoResource = "/socket.io"*/) {
	 // Log currently not accessible from this function, outputting to std::cout
   std::cout<<"Parsing websocket uri..."<<std::endl;
   std::string str = url;
   if(strstr(str.c_str(), "http"))
		str.replace(str.begin(),str.begin()+4,"ws");
   websocketpp::uri uo(str);

   // Declare boost io_service
   boost::asio::io_service io_service;

   std::cout<<"Connecting to Server..." <<std::endl;

   // Resolve query
   tcp::resolver r(io_service);
   tcp::resolver::query q(uo.get_host(), uo.get_port_str());
   tcp::socket socket(io_service);
   boost::asio::connect(socket, r.resolve(q));

   // Form initial post request.
   boost::asio::streambuf request;
   std::ostream reqstream(&request);

   reqstream << "POST " << "/socket.io" << "/1/ HTTP/1.0\r\n";
   reqstream << "Host: " << uo.get_host() << "\r\n";
   reqstream << "Accept: */*\r\n";
   reqstream << "Connection: close\r\n\r\n";

   std::cout<<"Sending Handshake Post Request..."<<std::endl;

   // Write request.
   boost::asio::write(socket, request);

   // Receive response
   boost::asio::streambuf response;
   boost::asio::read_until(socket, response, "\r\n");

   // Parse response
   std::istream resp_stream(&response);

   // Extract HTTP version, status, and message.
   std::string httpver;
   unsigned int status;
   std::string status_msg;

   resp_stream >> httpver >> status;
   std::getline(resp_stream, status_msg);

   // Log response
   std::cout<<"Received Response:"<<std::endl;
   std::cout<<httpver << " " << status << std::endl;
   std::cout<<status_msg << std::endl;

   // Read response headers. Terminated with double newline.
   boost::asio::read_until(socket, response, "\r\n\r\n");

   // Log headers.
   std::string header;

   while (std::getline(resp_stream, header) && header[0] != '\r')
   {
      std::cout<<header << std::endl;
   }

   // Handle errors
   if (!resp_stream || httpver.substr(0, 5) != "HTTP/")
   {
      std::cerr << "Invalid HTTP protocol: " << httpver << std::endl;
      throw websocketpp::exception("Socket.IO Handshake: Invalid HTTP protocol: " + httpver, websocketpp::error::GENERIC);
   }
   switch (status)
   {
   case(200):
      std::cout<<"Server accepted connection." << std::endl;
      break;
   case(401):
   case(503):
      std::cerr << "Server rejected client connection" << std::endl;
      throw websocketpp::exception("Socket.IO Handshake: Server rejected connection with code " + status, websocketpp::error::GENERIC);
      break;
   default:
      std::cerr << "Server returned unknown status code: " << status << std::endl;
      throw websocketpp::exception("Socket.IO Handshake: Server responded with unknown code " + status, websocketpp::error::GENERIC);
      break;
   }

   // Get the body components.
   std::string body;

   std::getline(resp_stream, body, '\0');
	 return body;
}