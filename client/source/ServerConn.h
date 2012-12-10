#ifndef SERVER_CONN_H_
#define SERVER_CONN_H_

#include <string>
#include "Types.h"


#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>


namespace revel
{

boost::asio::streambuf buffer;

// void handler(const boost::system::error_code& e, std::size_t size)
// {
// 	if (!e)
// 	{
// 	      	std::istream is(&buffer);
//       		std::string xmlframe;
//     		std::getline(is, xmlframe);
// 	      	std::cout << xmlframe << std::endl;
// 	}
// }

class ClientSocket
{
	std::shared_ptr<boost::asio::io_service> m_pIOService;
	std::shared_ptr<boost::asio::ip::tcp::socket> m_pSocket;

	boost::asio::streambuf buffer;

public:
	ClientSocket(const std::shared_ptr<boost::asio::io_service> io)
		: m_pIOService(io)
	{

	}

	void open(const std::string& ip, u32 port)
	{
		m_pSocket = std::make_shared<boost::asio::ip::tcp::socket>(*m_pIOService);

		boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(ip), port);
		m_pSocket->connect(endpoint);
	}

	std::string read_frame_data()
	{
		boost::system::error_code error;

		boost::asio::read_until(*m_pSocket, buffer, '\n');

      	std::istream is(&buffer);
  		std::string xmlframe;
		std::getline(is, xmlframe);
      	return xmlframe;
	}

};

/*
class ServerConn
	: public std::enable_shared_from_this<ServerConn>
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

		while(true)
	    {
	      	boost::asio::async_read_until(m_Socket, buffer, '\n', handler);
	   	}
	}

	// void exec()
	// {
	// 	m_IOService.
	// }	
};
*/
	
}

#endif //