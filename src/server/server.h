//
// Created by Andon Tchechmedjiev on 08/06/2017.
//

#ifndef RECOGNIZER_SERVER_H
#define RECOGNIZER_SERVER_H

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include "asio.hpp"

#include "../unitex/Unitex.h"


using asio::ip::tcp;

class session
        : public std::enable_shared_from_this<session> {

private:
    tcp::socket socket;
    asio::streambuf buffer;

public:
    explicit session(tcp::socket socket)
            : socket(std::move(socket)) {
    }

    void start() {
        process_request();
    }

private:
    void process_request() {
        auto self(shared_from_this());
        asio::async_read_until(socket, buffer, '\n',
                               [this, self](std::error_code ec, std::size_t length) {

                                   std::istream is(&buffer);
                                   std::string result_line;
                                   std::getline(is, result_line);

                                   if (result_line.at(0) == 'A' && !ec) {
                                       bool replace = false;
                                       bool longest_only = false;
                                       if (result_line.at(1) == 'Y') {
                                           longest_only = true;
                                       }
                                       if (result_line.at(2) == 'Y') {
                                           replace = true;
                                       }

                                       std::string text = result_line.substr(4);

                                       if (text.length() > 0) {
                                           Unitex uni = Unitex(text, "French", replace, longest_only);

                                           uni.preprocessing();
                                           uni.locatePattern();

                                           std::vector<Annotation> annotations = uni.getAnnotations();
                                           std::string annotation = uni.getAnnotations(annotations);

                                           do_write(annotation);

                                       } else {
                                           do_write("");
                                       }
                                   } else {
                                       do_write("");
                                   }
                                   socket.close();

                               });
    }

    void do_write(std::string const & value) {
        auto self(shared_from_this());
        asio::async_write(socket, asio::buffer(value.data(), value.length()),
                          [this, self](std::error_code ec, std::size_t /*length*/){});
    }

};

class server {
public:
    server(asio::io_service &io_service, unsigned short port)
            : acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
              socket_(io_service) {
        do_accept();
    }

private:
    void do_accept() {
        acceptor_.async_accept(socket_,
                               [this](std::error_code ec) {
                                   if (!ec) {
                                       std::make_shared<session>(std::move(socket_))->start();
                                   }

                                   do_accept();
                               });
    }

    tcp::acceptor acceptor_;
    tcp::socket socket_;
};


#endif //RECOGNIZER_SERVER_H
