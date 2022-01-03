#pragma once

#include "token.hpp"
#include <stack>
#include <memory>
#include <vector>
#include <iostream>
#include "../utils.hpp"


namespace bread {

    struct Lexer;
    struct LexerContext;
    struct GeneralScopeContext;
    struct EndContext;

    bool isNewLine(char c) {
        return c == '\n';
    }

    struct Lexer {

        std::stack<std::unique_ptr<LexerContext>> context{};
        std::vector<Token> tokens{};
        // Debug
        TokenIterator begin;

        TokenIterator it;
        Location loc;

    public:
        void consume();
        Rune peek()  { return *it; }
        Location getLocation() { return loc; };

        std::pair<Location, TokenIterator> getCurrent() { return {loc, it}; }

        void pushContext(std::unique_ptr<LexerContext>&& lexerContext);

        

        void lex(std::string string);




    };
    struct LexerContext {

        Lexer* lexer;

        LexerContext(Lexer& lexer) : lexer{ &lexer }
        {
            
        }

        virtual ~LexerContext() {}
        
        virtual void push_self() = 0;
        virtual void lex() = 0;
        
        Rune peek() { return lexer->peek(); }
        void consume() { lexer->consume(); }

        void add(Token&& token);

        /* Create content token*/
        template<TokenType TTokenType>
        Token makeToken(Location location, TokenIterator beginIter) {
            return Token{ TTokenType, location, lexer->it - beginIter, std::string(beginIter, lexer->it - beginIter) };
        }

        /* Create token without content*/
        template<TokenType TTokenType>
        Token makeToken(Location location) {
            return Token{ TTokenType, location, 0 };
        }

        template<typename T, class... args>
        void addContext(args&&... context);
  

        virtual std::string name();

    };

    template<class CRTP>
    struct ParentLexerContext : LexerContext {
        
        using LexerContext::LexerContext;

        void push_self() override {

            CRTP copy = *((CRTP*)(this));
            lexer->pushContext(std::make_unique<CRTP>(copy));
        }

    };

    struct GeneralScopeContext : ParentLexerContext<GeneralScopeContext> {

        Rune endRune;

        GeneralScopeContext(Lexer& lexer, Rune endRune) :
            ParentLexerContext{ lexer }, endRune{ endRune } {}
        
        GeneralScopeContext(GeneralScopeContext& other) :
            ParentLexerContext{other}, endRune{ other.endRune } {}

        void lex () override;

        std::string name() override {
            const char* k = endRune == '}' ? "{...}" : "...";
            return std::format("{} ({})", "GeneralScopeContext", k);
        }

    };

    struct CommentContext : ParentLexerContext<CommentContext> {
        using ParentLexerContext::ParentLexerContext;
        void lex() override;
    };

    struct EndContext : ParentLexerContext<EndContext> {
        using ParentLexerContext::ParentLexerContext;
        void lex() override {}
    };

#pragma region template implementation

    /* Template Implementation */
    template<typename T, class ...args>
    inline void LexerContext::addContext(args && ...context) {
        push_self();

        lexer->context.emplace(std::make_unique<T>( *lexer, std::forward<args>(context)...));
        
    }

#pragma endregion
}

