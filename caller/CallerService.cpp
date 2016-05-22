/*  Copyright (2016) by Alexander Diemand
 *  MIT License; see file "LICENSE"
 */

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/chrono.hpp>
#include <boost/format.hpp>
#include <boost/thread.hpp>
#include <array>
#include <algorithm>

using boost::asio::ip::tcp;
using clk = boost::chrono::high_resolution_clock;

class Caller
{
    public:
        Caller(boost::asio::io_service& io_service, std::string host, std::string port, long sleep_ms, int nrep)
            : io_service_(io_service)
            , _host(host)
            , _port(port)
            , _sleep_ms(sleep_ms)
            , _nrep(nrep)
    {
        if (nrep > 1000000) {
            throw "too many repetitions!"; }

        run();

    } // ctor

    private:
    void run() {

        std::array<long,1000000> _tm_array;

        enum { max_length = 1024 };
        char _data[max_length];
        tcp::resolver resolver(io_service_);
        tcp::resolver::iterator endpoint_it = resolver.resolve({ _host, _port });

        clk::time_point _talpha, _tomega;
        _talpha = clk::now();

        boost::system::error_code error;
        tcp::socket _socket(io_service_);
        boost::asio::connect(_socket, endpoint_it, error);
        if (error) {
            std::clog << "some error on connect" << std::endl;
            return; }

        clk::time_point _t0, _t1;
        //clk::time_point _t2, _t3;

        long nrep = _nrep;

        while (nrep > 0) {
                _t0 = clk::now();
                _tm_array[_nrep - nrep] = 999L;

                // write to external server
                double d0 = 33.14938713+7*nrep; // this is a floating point number
                snprintf(_data, max_length, "%f\n\0\0", d0);
                int rlen = strlen(_data);
                _socket.write_some(boost::asio::buffer(_data, rlen), error);
                if (error == boost::asio::error::eof) {break;}

/*                _t2 = clk::now();
                boost::this_thread::sleep_for(boost::chrono::milliseconds(_sleep_ms));
                _t3 = clk::now(); */

                // read from external server
                memset(_data, '\0', max_length);
                size_t len1 = _socket.read_some(boost::asio::buffer(_data, max_length), error);
                if (len1 > 0 || error == boost::asio::error::eof) {
                    int i=0;
                    while (len1 > 1 && _data[i]=='\0') { i++; len1--; }
                    double d1 = std::atof(_data+i);
                    // the return value must be within a certain tolerance
                    if (fabs(d1 - (d0 * 2.0 + 1.0)) < 0.000001) {
                        _t1 = clk::now();
                        _tm_array[_nrep - nrep] = boost::chrono::round<boost::chrono::microseconds>(_t1 - _t0).count();
                    } else {
                        std::clog << (boost::format("   received: %s != %.4f (%.4f * 2.0 + 1.0) len=%d") % (_data+i) % (d0 * 2 + 1.0) % d0 % len1).str() << std::endl;
                    }
                }
                nrep--;
        } // while

        _socket.close();

        _tomega = clk::now();
        std::clog << boost::format("overall time used: %ld us (10^-6 seconds)\n") % (boost::chrono::round<boost::chrono::microseconds>(_tomega - _talpha).count());

        std::sort(_tm_array.begin(), _tm_array.begin()+_nrep);

        if (_nrep < 100) {
            for (int i=0; i<_nrep; i++) {
                long ll=_tm_array[i] / 10;
                std::clog << std::endl << (boost::format("   %02d  ") % i ).str();
                for (int j=0; j<ll; j++) { std::clog.put('#'); }
            }
            std::clog << std::endl;
        }
        if (_nrep > 10) {
            long _min = 1000L; 
            for (int i=9; i<_nrep; i++) { if (_tm_array[i] < _min) { _min=_tm_array[i]; }; }
            long _max = 0L; 
            for (int i=9; i<_nrep; i++) { if (_tm_array[i] > _max) { _max=_tm_array[i]; }; }
            long _sum = 0L; 
            for (int i=9; i<_nrep; i++) { _sum += _tm_array[i]; }
            long _mean = _sum / (_nrep-10);

            std::clog << (boost::format("after %d repetitions: %ld < %ld < %ld us (10^-6 seconds)") % _nrep % _min % _mean % _max) << std::endl;
        }
        if (_nrep > 10) {
            long _min = 1000L; 
            for (int i=0; i<_nrep; i++) { if (_tm_array[i] < _min) { _min=_tm_array[i]; }; }
            long _max = 0L; 
            for (int i=0; i<_nrep; i++) { if (_tm_array[i] > _max) { _max=_tm_array[i]; }; }
            long _q1 = _tm_array[_nrep/4];
            long _median = _tm_array[_nrep/2];
            long _q3 = _tm_array[_nrep*3/4];
            std::clog << (boost::format("after %d repetitions: min: %ld q1[%ld]: %ld median[%ld]: %ld q3[%ld]: %ld max: %ld us (10^-6 seconds)") % _nrep % _min % (_nrep/4) % _q1 % (_nrep/2) % _median % (_nrep*3/4) % _q3 % _max) << std::endl;
        }
        if (_nrep > 10) {
            std::ofstream ofs;
            ofs.open((boost::format("%s_%d_%d.dat") % _host % _port % _nrep).str());
            for (int i=0; i<_nrep; i++) {
                ofs << boost::format("%d %ld\n") % i % _tm_array[i];
            }
            ofs.close();
        }

    } // run()

    private:
    boost::asio::io_service& io_service_;
    const std::string _host;
    const std::string _port;
    const long _sleep_ms;
    const int _nrep;
};



int main(int argc, char* argv[])
{
    try
    {
        if (argc != 5)
        {
            std::cerr << (boost::format("Usage: %s <host> <port> <slep ms> <repetitions>")%argv[0]).str() << std::endl;
            return 1;
        }

        boost::asio::io_service io_service;

        Caller s(io_service, argv[1], argv[2], std::atoi(argv[3]), std::atoi(argv[4]));

        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}

