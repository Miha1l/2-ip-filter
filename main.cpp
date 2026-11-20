#include "ip_filter.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

std::vector<IPv4Addr> read(std::istream &in) {
    std::vector<IPv4Addr> ip_pool;

    for (std::string line; std::getline(in, line);) {
        auto tab_pos = line.find('\t');
        std::string_view ip_str = std::string_view(line).substr(0, tab_pos);
        IPv4Addr ip;
        if (parse_ip_from_string(ip_str, ip)) {
            ip_pool.push_back(ip);
        }
    }

    return ip_pool;
}

int main(int, char**) {
    try
    {
        std::vector<IPv4Addr> ip_pool = read(std::cin);

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
