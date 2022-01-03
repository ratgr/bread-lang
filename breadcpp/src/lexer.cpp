#include "./lexer.hpp"
#include <iostream>
#include <cassert>


namespace bread {
	
	void Lexer::lex(std::string string) {
		auto cstring = string.c_str();

		begin = cstring;

		context.push(std::make_unique<EndContext>(*this, cstring, Location{}));
		context.push(std::make_unique<GeneralScopeContext>(*this, cstring, Location{}, 0));
		do {
			auto ptr = std::move(context.top());
			context.pop();
			
			std::cout << std::format("POP lexer ({}): {}\n", context.size(), ptr->name());
			std::cout << std::format("\t{}\n", escape_char(cstring));
			std::cout << std::format("\t{}\n", pointee_escaped(cstring, ptr->it));

			ptr->lex();
		} while (!context.empty());
	}


	void LexerContext::consume() {
		it++;
		if (isNewLine(*it)) {
			loc.line++;
			loc.column = 0;
		}
		else {
			loc.column++;
		}
	}
	void LexerContext::add(Token&& token) { lexer->tokens.push_back(token); }
	void LexerContext::commit() {
		update();
		
		lexer->context.top()->loc = loc;
		lexer->context.top()->it = it;

		//std::cout << std::format("TOP after \n\t{}\n", std::to_string(*lexer->context.top().get()));
	}
	void LexerContext::update() {
		currentTokenLoc = loc;
		currentTokenIt = it;
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

		for (auto c = peek(); c != 0; c = peek(), update()) {
			
			if (c == endRune) {
				consume();
				add < TokenType{ '}' } > ();
				commit();
				//finished
				return;
			
			}


			if (c == '"') {
				auto begin = it;
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
				add < TokenType::StringLiteral > (begin);
				continue;
			}

			if (c == '{') {
				consume();
				add<TokenType{ '{' }> ();
				addContext<GeneralScopeContext>('}');
				//Open new scope
				return;
			}

			if (c == '=') {
				consume();
				c = peek();
				if (c == '=') {
					consume();
					add < TokenType::OpEquals > ();
					continue;
				}
				add < TokenType::OpEquals >();   
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

				add < TokenType::OpDivide >();
				continue;
			}


			//identifier
			if (isalpha(c) || c == '_') {
				auto begin = it;
				consume();
				for (c = peek(); isalpha(c) || c == '_'; c = peek()) { consume(); }
				add <TokenType::Identifier>(begin);
				continue;
			}

			//probablemente lanzar un error
			consume();
		
		}

		if (peek() == endRune) {
			assert(endRune == 0);
			commit();
			//finished
			return;

		}


		return;

	}

	void CommentContext::lex() {

		for (auto c = peek(); c != 0; c = peek()) {
			if (c == '/') {
				consume();
				c = peek();
				if (c == '*') {
					consume();
					addContext<CommentContext>();
					return;
				}
			
			}

			if (c == '*') {
				consume();
				c = peek();
				if (c == '/') {
					consume();
					commit();
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