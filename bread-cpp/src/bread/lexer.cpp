#include "./lexer.hpp"
#include "../debug.hpp"
#include <iostream>
#include <cassert>


namespace bread {


	void Lexer::consume() {
		it++;
		if (isNewLine(*it)) {
			loc.line++;
			loc.column = 0;
		}
		else {
			loc.column++;
		}
	}
	void Lexer::pushContext(std::unique_ptr<LexerContext>&& lexerContext){
		context.emplace(std::move(lexerContext));

		if constexpr (false) {
			std::cout << std::format("PUSH lexer ({}): {}\n", context.size(), lexerContext->name());
			std::cout << std::format("\t{}\n", escape_char(begin));
			std::cout << std::format("\t{}\n", pointee_escaped(begin, it));
		}

	}
	void Lexer::lex(std::string string) {
		auto cstring = string.c_str();

		begin = cstring;
		it = begin;

		context.push(std::make_unique<EndContext>(*this));
		context.push(std::make_unique<GeneralScopeContext>(*this,0));
		do {
			auto ptr = std::move(context.top());
			context.pop();
			
			std::cout << std::format("POP lexer ({}): {}\n", context.size(), ptr->name());
			std::cout << std::format("\t{}\n", escape_char(cstring));
			std::cout << std::format("\t{}\n", pointee_escaped(cstring, it));

			ptr->lex();
		} while (!context.empty());
	}

	void LexerContext::add(Token&& token) { 
		lexer->tokens.push_back(token); 
	}

	std::string LexerContext::name()
	{
		auto k = typeid(*this).name();
		
		while (*k != ':') {
			k++;
		}
		k++;
		k++;

		return k;
	}

	void GeneralScopeContext::lex() {
		auto c = peek();
		
		while(c != 0) {
			c = peek();
			auto [loc, begin] = lexer->getCurrent();
			
			if (c == endRune) {
				consume();
				if (endRune == '}') {
					add(makeToken < TokenType{ '}' } > (loc));
				}
				//finished
				return;
			
			}


			if (c == '"') {
				consume();
				c = peek();
				for (c = peek(); !(c == '"' || c == 0); c = peek()) {
					if (c == '\\') {
						consume();
						c = peek();
						if (c == '"') {
							consume();
							continue;
						};
					}

					consume();
					
				}
				consume();
				add(makeToken< TokenType::StringLiteral >(loc, begin));
				continue;
			}

			if (c == '{') {
				consume();
				add(makeToken < TokenType{ '{' } > (loc));
				addContext<GeneralScopeContext>('}');
				//Open new scope
				return;
			}

			if (c == '=') {
				consume();
				c = peek();
				if (c == '=') {
					consume();
					add(makeToken < TokenType::OpEquals > (loc));
					continue;
				}
				add(makeToken < TokenType::OpAssign >(loc));
				continue;
			}

			if (c == '/') {
				consume();
				c = peek();
				if (c == '/') {
					consume();
					for (c = peek(); !(c == '\n' || c == endRune); c = peek()) { consume(); }
					continue;
				}
				// el simbolo es '/*' 
				if (c == '*') {
					consume();
					addContext<CommentContext>();
					return;
				}

				add(makeToken < TokenType::OpDivide >(loc));
				continue;
			}


			//identifier
			if (isalpha(c) || c == '_') {
				consume();
				for (c = peek(); isalpha(c) || c == '_'; c = peek()) { consume(); }
				add(makeToken < TokenType::Identifier >(loc, begin));
				continue;
			}

			//probablemente lanzar un error
			consume();
		
		}


		return;

	}

	void CommentContext::lex() {

		for (auto c = peek(); c != 0; c = peek()) {
			if (c == '/') {
				consume();
				c = peek();
				if (c == '*') {
					addContext<CommentContext>();
					return;
				}
			
			}

			if (c == '*') {
				consume();
				c = peek();
				if (c == '/') {
					consume();
					//Finished
					return;
				}
			}

			consume();
		}

	}


}

auto example = R"(

	const auto bb == cc {

	//Desaparece
	/* Esto tambien /* desaparece */ */
		make User sadas "other {} "
	}

)";


auto example2 = R"(

	{ a { b } e }

)";


auto example3 = R"(

	{ a }

)";
//std::ostream& operator<<(std::ostream& os, const bread::Token& token)
//{
//	os << bread::name(token.type);
//	if(token.str.size() > 0 )
//		os << " {" << token.str << "}";
//	return os;
//}

int main() {
	auto lexer = bread::Lexer();
	lexer.lex(example);

	for (auto m : lexer.tokens)
	{
		std::cout << std::to_string(m) << std::endl;
	}

}