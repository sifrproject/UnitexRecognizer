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
#include <boost/bind.hpp>


#include "../unitex/Unitex.h"


using asio::ip::tcp;

class session
        : public std::enable_shared_from_this<session> {

private:
    tcp::socket socket_;
    asio::streambuf buffer;

public:
    explicit session(asio::io_service& io_service)
            : socket_(io_service) {
    }

    tcp::socket& socket()
    {
        return socket_;
    }

    void start() {
        asio::async_read_until(socket_, buffer, '\n',boost::bind(&session::handle_read, this,
                                                                 asio::placeholders::error,
                                                                 asio::placeholders::bytes_transferred));
    }

private:

    void handle_read(const asio::error_code& error,
                     size_t bytes_transferred){
        if(!error) {
            std::istream is(&buffer);
            std::string result_line;
            std::getline(is, result_line);
            if (result_line.length() >0 && result_line.at(0) == 'A') {
                bool replace = false;
                bool longest_only = false;
                if (result_line.at(1) == 'Y') {
                    longest_only = true;
                }
                if (result_line.at(2) == 'Y') {
                    replace = true;
                }

                std::string text = result_line.substr(4);
                if(text.at(text.length()-1)=='\r'){
                    text = text.substr(0,text.length()-1);
                }

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
            socket_.close();
        } else {
            delete(this);
        }
    }

    void do_write(std::string const & value) {
        asio::async_write(socket_, asio::buffer(value.data(), value.length()),
                          boost::bind(&session::handle_write, this,
                                      asio::placeholders::error));
    }

    void handle_write(const asio::error_code& error){
        if(error){
            delete this;
        }

    }

};

class server {
public:
    server(asio::io_service &io_service, unsigned short port)
            : acceptor(io_service, tcp::endpoint(tcp::v4(), port)),
              io_service(io_service) {
        do_accept();
    }

private:
    void do_accept() {
        auto* new_session = new session(io_service);
        acceptor.async_accept(new_session->socket(),
                               boost::bind(&server::handle_accept, this, new_session,
                                           asio::placeholders::error));
    }

    void handle_accept(session* new_session,
                       const asio::error_code& error)
    {
        if (!error)
        {
            new_session->start();
        }
        else
        {
            delete new_session;
        }

        do_accept();
    }


    tcp::acceptor acceptor;
    asio::io_service& io_service;
};


#endif //RECOGNIZER_SERVER_H
