#include "qrcode.h"

namespace qrcode {

std::size_t version_select(const std::string& s)
{
    // this is for error correcting level Q (25%)
    std::vector<int> ch_cap = {0, 11, 20, 32, 46, 60, 74, 86, 108, 130};
    for (auto i = 0; i < ch_cap.size(); i++) {
        if (s.size() <= ch_cap[i]) { return i; }
    }
    return 0;
}

std::bitset<4> mode_indicator(char c)
{
    switch (c) {
    case 'n' : return {1};
    case 'a' : return {2};
    case 'b' : return {4};
    case 'k' : return {8};
    default  : return {4};
    }
}

std::bitset<8> ch_count_indicator(const std::string& s) { return {s.size()}; }

std::vector<std::bitset<8>> string_to_0b(const std::string& s)
{
    std::vector<std::bitset<8>> v;
    v.reserve(s.size());
    for (const auto& c : s) { v.emplace_back(static_cast<int>(c)); }
    return v;
}

void termination_zeros(std::vector<int>& v)
{
    std::size_t r = v.size() % 8;
    r <= 4 ? v.insert(v.end(), r, 0) : v.insert(v.end(), 4, 0);
}

std::vector<std::bitset<8>> bit_string(std::vector<int>& v)
{
    std::vector<std::bitset<8>> _bit_string;
    _bit_string.reserve(v.size() / 8);

    std::bitset<8> temp;
    for (auto i = 0; i < v.size() / 8; i++) {
        for (auto j = 0; j < 8; j++) { temp[7 - j] = v[(8 * i) + j]; }
        _bit_string.push_back(temp);
    }

    return _bit_string;
}

void padding_bytes(std::vector<std::bitset<8>>& v, size_t version)
{
    // this is for error correcting level Q (25%)
    std::vector<int> codeword_count = {0, 13, 22, 34, 48, 62, 76, 88, 110, 132};
    while (v.size() < codeword_count[version]) {
        v.emplace_back(236);
        v.size() < codeword_count[version] ? void(v.emplace_back(17)) : void();
    }
}

std::vector<std::bitset<8>> encode(const std::string& s)
{
    if (s.empty()) { return {}; }

    std::vector<int> int_v = integer_vector
            (
                    mode_indicator('b'),
                    ch_count_indicator(s),
                    string_to_0b(s)
            );
    termination_zeros(int_v);

    std::vector<std::bitset<8>> byte_v = bit_string(int_v);
    padding_bytes(byte_v, version_select(s));

    return byte_v;
}

std::vector<int> get_message_polynomial(const std::vector<std::bitset<8>>& message)
{
    std::vector<int> v;
    v.reserve(message.size());
    for (const auto& byte : message) { v.emplace_back(static_cast<int>(byte.to_ulong())); }
    std::reverse(v.begin(), v.end());
    return v;
}

std::vector<int> get_generator_polynomial(size_t codewordSize)
{
    std::vector<int> codeword_count = {0, 13, 22, 34, 48, 62, 76, 88, 110, 132};
    // a vector where each element is the exponent of the alpha notation coefficient, and the indices are equal to the
    // degree of x.
    switch (codewordSize) {
    case 13: return {78, 140, 206, 218, 130, 104, 106, 100, 86, 100, 176, 152, 74, 0};
    default: return {78, 140, 206, 218, 130, 104, 106, 100, 86, 100, 176, 152, 74, 0};
    }
}

int antilog(int x)
{
    if (x >= 0 && x < 8) { return static_cast<int>(std::pow(2, x)); }

    int _antilog = static_cast<int>(std::pow(2, 7));

    for (auto i = (x - 7); i > 0; i--) {
        _antilog *= 2;
        if (_antilog > 255) { _antilog = _antilog ^ 285; }
    }
    return _antilog;
}

int log(int x) { for (int i = 1; i < 256; i++) { if (antilog(i) == x) return i; }}     ///< LOL

std::vector<int> error_correction_codewords(const std::vector<int>& generator, const std::vector<int>& message)
{
    std::vector<int> v;

    // multiply the generator polynomial by the leading term of the message polynomial
    // would probably be easiest to do this with alpha notation ...

    return v;
}

}   // namespace qrcode



