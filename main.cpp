#include "ip_filter.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> split(const std::string &str, char d) {
    std::vector<std::string> r;

    size_t start = 0;
    size_t stop = str.find_first_of(d);
    while (stop != std::string::npos) {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

int main(int, char**) {
    try
    {
        std::vector<IPv4Addr> ip_pool;

        for (std::string line; std::getline(std::cin, line);) {
            std::vector<std::string> v = split(line, '\t');
            IPv4Addr ip;
            if (parse_ip_from_string(v.at(0), ip)) {
                ip_pool.push_back(ip);
            }
        }

        // reverse lexicographically sort
        std::sort(ip_pool.begin(), ip_pool.end(), [](const IPv4Addr &ip1, const IPv4Addr &ip2) {
            return ip1 > ip2;
        });
        std::cout << ip_pool;

        // filter by first byte and output
        {
            auto filtered_ips = filter(ip_pool, 1);
            std::cout << filtered_ips;
        }

        // filter by first and second bytes and output
        {
            auto filtered_ips = filter(ip_pool, 46, 70);
            std::cout << filtered_ips;
        }

        // filter by any byte and output
        {
            auto filtered_ips = filter_any(ip_pool, 46);
            std::cout << filtered_ips;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}
