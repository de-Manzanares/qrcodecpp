#include "catch2/catch_all.hpp"
#include "qrcode.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>

std::string create_string_of_length(size_t size)
{
    std::string s;
    s.reserve(32);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(32, 126);
    for (auto i = 0; i < size; i++) { s.push_back(static_cast<char>(dis(gen))); }
    return s;
}

void setup(const std::string& s, std::vector<std::bitset<8>>& b) { b = qrcode::encode(s); }

void print(const std::vector<std::bitset<8>>& v) { for (const auto& byte : v) { std::cout << byte << " "; }}

TEST_CASE("encoding")
{
    std::string s;
    std::vector<std::bitset<8>> code;
    SECTION("Empty string") {
        setup("", code);
        print(code);
        CHECK(code.empty());
    }SECTION("Version 1 Error Correction Q") {
        for (int i = 1; i <= 11; i++) {
            setup(create_string_of_length(i), code);
            std::cout << "v 1 c " << std::setw(3) << i << " : ";
            print(code);
            std::cout << std::endl;
            CHECK(code.size() == 13);
        }
    }SECTION("Version 2 Error Correction Q") {
        for (int i = 12; i <= 20; i++) {
            setup(create_string_of_length(i), code);
            std::cout << "v 2 c " << std::setw(3) << i << " : ";
            print(code);
            std::cout << std::endl;
            CHECK(code.size() == 22);
        }
    }SECTION("Version 3 Error Correction Q") {
        for (int i = 21; i <= 32; i++) {
            setup(create_string_of_length(i), code);
            std::cout << "v 3 c " << std::setw(3) << i << " : ";
            print(code);
            std::cout << std::endl;
            CHECK(code.size() == 34);
        }
    }SECTION("Version 4 Error Correction Q") {
        for (int i = 33; i <= 46; i++) {
            setup(create_string_of_length(i), code);
            std::cout << "v 4 c " << std::setw(3) << i << " : ";
            print(code);
            std::cout << std::endl;
            CHECK(code.size() == 48);
        }
    }SECTION("Version 5 Error Correction Q") {
        for (int i = 47; i <= 60; i++) {
            setup(create_string_of_length(i), code);
            std::cout << "v 5 c " << std::setw(3) << i << " : ";
            print(code);
            std::cout << std::endl;
            CHECK(code.size() == 62);
        }
    }SECTION("Version 6 Error Correction Q") {
        for (int i = 61; i <= 74; i++) {
            setup(create_string_of_length(i), code);
            std::cout << "v 6 c " << std::setw(3) << i << " : ";
            print(code);
            std::cout << std::endl;
            CHECK(code.size() == 76);
        }
    }SECTION("Version 7 Error Correction Q") {
        for (int i = 75; i <= 86; i++) {
            setup(create_string_of_length(i), code);
            std::cout << "v 7 c " << std::setw(3) << i << " : ";
            print(code);
            std::cout << std::endl;
            CHECK(code.size() == 88);
        }
    }SECTION("Version 8 Error Correction Q") {
        for (int i = 87; i <= 108; i++) {
            setup(create_string_of_length(i), code);
            std::cout << "v 8 c " << std::setw(3) << i << " : ";
            print(code);
            std::cout << std::endl;
            CHECK(code.size() == 110);
        }
    }SECTION("Version 9 Error Correction Q") {
        for (int i = 109; i <= 130; i++) {
            setup(create_string_of_length(i), code);
            std::cout << "v 9 c " << std::setw(3) << i << " : ";
            print(code);
            std::cout << std::endl;
            CHECK(code.size() == 132);
        }
    }
}