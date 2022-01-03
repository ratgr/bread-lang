#pragma once

#include "token.hpp"
#include <stack>
#include <memory>
#include <vector>
#include <iostream>
#include "utils.hpp"




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
        /*debug*/
        TokenIterator begin;


        void lex(std::string string);


    };


    struct LexerContext {

        Lexer* lexer;
        TokenIterator it;
        // TokenIterator begin;
        TokenIterator currentTokenIt;

        Location beginLoc;
        Location loc;
        Location currentTokenLoc;

        LexerContext(Lexer& lexer, TokenIterator begin, Location beginLoc) :
            lexer{ &lexer }, /*begin{begin},*/ it{begin}, currentTokenIt{begin},
            beginLoc{ beginLoc }, loc{ beginLoc }, currentTokenLoc{ beginLoc }
        {
            
        }

        virtual ~LexerContext() {}
        
        virtual void push_self() = 0;
        virtual void lex() = 0;
        
        Rune peek() { 
            return *it; 
        }
        
        void consume();
        void add(Token&& token);

        template<TokenType T>
        void add() { add(Token{ T, currentTokenLoc, it - currentTokenIt }); }

        template<TokenType T>
        void add(TokenIterator begin) { add(Token{ T, currentTokenLoc, it - begin, std::string(begin, it - begin)}); }


        template<typename T, class... args>
        void addContext(args&&... context);
        
        void commit();

        void update();;

        virtual std::string name();

    };

    template<class CRTP>
    struct ParentLexerContext : LexerContext {
        
        using LexerContext::LexerContext;

        void push_self() override {

            CRTP copy = *((CRTP*)(this));
            lexer->context.emplace(std::make_unique<CRTP>(copy));
        }

    };

    struct GeneralScopeContext : ParentLexerContext<GeneralScopeContext> {

        Rune endRune;

        GeneralScopeContext(Lexer& lexer, TokenIterator begin, Location beginLoc, Rune endRune) :
            ParentLexerContext{ lexer, begin, beginLoc }, endRune{ endRune } {}
        
        GeneralScopeContext(GeneralScopeContext& other) :
            ParentLexerContext{other}, endRune{ other.endRune }   {}

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

        std::cout << std::format("\t{}\n", escape_char(lexer->begin));
        std::cout << std::format("\t{}\n", pointee_escaped(lexer->begin, it-1));
       
       /* std::cout << "PUSH self: \n\t";
        lexer->print();
        std::cout << "\n";*/

        lexer->context.emplace(std::make_unique<T>( *lexer, it, loc, std::forward<args>(context)...));
        std::cout << std::format("PUSH lexer ({}): {}\n", lexer->context.size(),  lexer->context.top()->name());
    }

#pragma endregion
}

