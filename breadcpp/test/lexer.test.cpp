#include "gtest/gtest.h"
#include "bread/lexer.hpp"


auto BasicLexerTest = R"(

	const auto bb == cc {

	//Desaparece
	/* Esto tambien /* desaparece */ */
		make User sadas "other {} "
	}

)";

namespace bread {





	TEST(CanLexBread, BasicLexerTestIsValid) {


	}
}


TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}


