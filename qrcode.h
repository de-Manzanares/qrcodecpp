#ifndef QRCODE_H
#define QRCODE_H

#include <bitset>
#include <string>
#include <vector>
#include <map>

// todo polynomial long division LOL

namespace qrcode {

std::size_t version_select(const std::string& s);
std::bitset<4> mode_indicator(char c);
std::bitset<8> ch_count_indicator(const std::string& s);
std::vector<std::bitset<8>> string_to_0b(const std::string& s);

template<std::size_t T1, std::size_t T2>
std::vector<int>
integer_vector(const std::bitset<T1>& m, const std::bitset<T2>& l, const std::vector<std::bitset<8>>& data)
{
    std::vector<int> v;
    v.reserve(T1 + T2 + (8 * data.size()));

    for (std::size_t i = 0; i < T1; i++) { v.emplace_back(static_cast<int>(m[i])); }
    for (std::size_t i = 0; i < T2; i++) { v.emplace_back(static_cast<int>(l[i])); }
    for (const auto& byte : data) { for (std::size_t i = 0; i < 8; i++) { v.emplace_back(static_cast<int>(byte[i])); }}

    return v;
}

void termination_zeros(std::vector<int>& v);
std::vector<std::bitset<8>> bit_string(std::vector<int>& v);
void padding_bytes(std::vector<std::bitset<8>>& v, size_t size);
std::vector<std::bitset<8>> encode(const std::string& s);

} // namespace qrcode

#endif // QRCODE_H
