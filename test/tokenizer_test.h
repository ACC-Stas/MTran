#pragma once

#include <catch.hpp>
#include <lispp/tokenizer.h>
#include <lispp/exceptions.h>
#include <vector>
#include <iostream>

std::string enum_to_string(TokenType type) {
    switch (type) {
        case TokenType::UNKNOWN:
            return "UNKNOWN TOKEN";
        case TokenType::NUMBER:
            return "NUMBER TOKEN";
        case TokenType::BOOL:
            return "BOOL TOKEN";
        case TokenType::NAME:
            return "NAME TOKEN";
        case TokenType::QUOTE:
            return "QUOTE TOKEN";
        case TokenType::DOT:
            return "DOT TOKEN";
        case TokenType::LEFT_PARENTHESES:
            return "LEFT_PARENTHESES TOKEN";
        case TokenType::RIGHT_PARENTHESES:
            return "RIGHT_PARENTHESES TOKEN";
        case TokenType::END:
            return "END TOKEN";
    }
    return "";
}

struct TokenizerTest {

    std::stringstream in;
    Tokenizer tokenizer;

    TokenizerTest() : tokenizer(&in) {}


    void ExpectEq(std::string expression, std::vector<Token> tokens) {
        in.clear();
        in.str(expression);
        tokenizer.Consume();
        auto current_token = tokenizer.GetToken();
        size_t it = 0;
        std::cout << expression << '\n';
        while (!in.eof()){
            std::cout << current_token.GetString() << " IS ";
            std::cout << enum_to_string(current_token.GetType()) << '\n';
            CHECK(current_token.GetType() == tokens[it].GetType());
            CHECK(current_token.GetString() == tokens[it].GetString());
            ++it;
            tokenizer.Consume();
            current_token = tokenizer.GetToken();
        }
        CHECK(current_token.GetType() == tokens[it].GetType());
        CHECK(current_token.GetString() == tokens[it].GetString());
    }

    void ExpectNoError(std::string expression) {
        try {
            in.clear();
            in.str(expression);
            tokenizer.Consume();
            auto current_token = tokenizer.GetToken();
            while (!in.eof()) {
                tokenizer.Consume();
                std::cout << current_token.GetString() << " IS ";
                std::cout << enum_to_string(current_token.GetType()) << '\n';
                current_token = tokenizer.GetToken();
            }
        } catch (...){
            CHECK(false);
        }
    }

    void ExpectSyntaxError(std::string expression, std::string error_message) {
        try {
            in.clear();
            in.str(expression);
            tokenizer.Consume();
            tokenizer.GetToken();
            while (!in.eof()) {
                tokenizer.Consume();
                tokenizer.GetToken();
            }
            CHECK(false);
        } catch(const SyntaxError& err){
            std::cout << expression << '\n';
            std::cout << err.what() << '\n';
            CHECK(error_message.compare(err.what()) == 0);
        } catch (...){
            CHECK(false);
        }
    }
};
