#include "ip_filter.h"

#include <algorithm>
#include <charconv>

std::ostream& operator<<(std::ostream &os, const IPv4Addr &ip) {
    os << +ip[0] << "." << +ip[1] << "." << +ip[2] << "." << +ip[3];
    return os;
}

std::ostream& operator<<(std::ostream &os, const std::vector<IPv4Addr> &ips) {
    for (auto it = ips.cbegin(); it != ips.cend(); ++it) {
        os << *it << std::endl;
    }
    return os;
}

bool parse_ip_from_string(std::string_view ip_str, IPv4Addr &ip_out) {
    const char *start = ip_str.data();
    const char *end = ip_str.data() + ip_str.size();

    for (int i = 0; i < 4; ++i) {
        auto [ptr, ec] = std::from_chars(start, end, ip_out[i]);

        if (ec != std::errc()) {
            return false;
        }

        start = ptr;
        if (*start == '.') {
            ++start;
        }
    }

    return true;
}

std::vector<IPv4Addr> filter_any(const std::vector<IPv4Addr> &ip_pool, uint8_t value) {
    std::vector<IPv4Addr> filtered_ips;
    filtered_ips.reserve(ip_pool.size());
    std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(filtered_ips), [&](const auto &ip) {
        return std::find(ip.begin(), ip.end(), value) != ip.end();
    });

    return filtered_ips;
}