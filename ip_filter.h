#pragma once

#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <vector>
#include <string_view>

using IPv4Addr = std::array<uint8_t, 4>;

std::ostream& operator<<(std::ostream &os, const IPv4Addr &ip);
std::ostream& operator<<(std::ostream &os, const std::vector<IPv4Addr> &ips);

bool parse_ip_from_string(std::string_view ip_str, IPv4Addr &ip_out);
std::vector<IPv4Addr> filter_any(const std::vector<IPv4Addr> &ip_pool, uint8_t value);

template <typename... Args>
std::vector<IPv4Addr> filter(const std::vector<IPv4Addr> &ip_pool, Args... args) {
    size_t count = sizeof...(args);
    uint8_t values[] = { static_cast<uint8_t>(args)... };
    std::vector<IPv4Addr> filtered_ips;
    std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(filtered_ips), [&](const auto &ip) {
        return std::equal(ip.begin(), ip.begin() + count, values);
    });

    return filtered_ips;
}
