#pragma once

#include <string>
#include <unordered_map>
#include <format>

#define BREAD_ENUM_STRING(name) { TokenType::name , #name }
namespace bread {

    using Rune = char;
    using TokenIterator = const char*;
    using StringType = std::string;

    enum class TokenType : int {
        Identifier = 256,
        StringLiteral,  // "string-literal"

        /* Assignment */
        OpAssign,    // [x] =
        OpType,      // [ ] :
        Op           // [ ]   

        /*Logic*/
        OpEquals,       // ==
        OpNotEquals,    // !=

        /*Aritmetic*/
        OpStar,         // *    
        OpPlus,         // +
        OpDivide,       // /

        /*Exclamation*/
        OpExclamation,  // !
        OpInterrogation,// ?

        Error

    };

    std::string name(TokenType type) {
        static const std::unordered_map<TokenType, const char*> names{
            BREAD_ENUM_STRING(Identifier),
            BREAD_ENUM_STRING(StringLiteral),


            /*Logic*/
            BREAD_ENUM_STRING(OpEquals),
            BREAD_ENUM_STRING(OpNotEquals),
            
            /*Aritmetic*/
            BREAD_ENUM_STRING(OpStar),
            BREAD_ENUM_STRING(OpPlus),
            BREAD_ENUM_STRING(OpDivide),

            /*Exclamation*/
            BREAD_ENUM_STRING(OpExclamation),
            BREAD_ENUM_STRING(OpInterrogation),


            BREAD_ENUM_STRING(Error),
        };

        if (names.contains(type))
            return names.at(type);
        else if((int)type < 255)
            return std::format("Token'{}'", (char) type);
        else 
            return std::format("Unknown {}", (int)type);
    }

    struct Location {
        StringType uri = "";
        int line = 0;
        int column = 0;
    };

    struct Token {
        TokenType type;
        Location begin;
        int64_t length;
        StringType str = "";
    };

}

namespace std {

    std::string to_string(bread::TokenType token) { return bread::name(token); }

    std::string to_string(bread::Token token) { 
        if (token.str.size() == 0) {
            return to_string(token.type);
        }
        else {
            return std::format("{} {{{}}}", to_string(token.type), token.str);
        }
    }

}