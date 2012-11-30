#ifndef SERVER_CONN_H_
#define SERVER_CONN_H_

#include <string>
#include "Types.h"

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>

namespace revel
{

class ServerConn
{
	std::string m_IP;
	u32 m_Port;

	boost::asio::io_service m_IOService;
	boost::asio::ip::tcp::endpoint m_EndPoint;
	boost::asio::ip::tcp::socket m_Socket;

public:
	ServerConn(const std::string& ip = "127.0.0.1", u32 port = 1234)
		: m_IP(ip)
		, m_Port(port)
		, m_IOService()
		, m_EndPoint(boost::asio::ip::address::from_string(ip), port)
		, m_Socket(m_IOService)
	{
	}

	void start()
	{
		m_Socket.connect(m_EndPoint);

		std::string xmlframe;

	    while(true)
	    {
	      	boost::asio::streambuf buffer;
	      	boost::system::error_code error;

	      	size_t len = boost::asio::read_until(m_Socket, buffer, "\n");
	      	
	      	std::istream is(&buffer);
    		std::getline(is, xmlframe);

	      	std::cout << xmlframe << std::endl;
	   }
	}
	
};
	
}

#endif //