
# Declarations

|            |         |       |         |       |
| :--------: | :-----: | :---: | :-----: | :---: |
|     {}     | compile |       | runtime |       |
|     {}     |  read   | write |  read   | write |
|            |
|    var     |    ✅    |   ✅   |    ✅    |   ✅   | 1111 |
|    var!    |    ✅    |   ✅   |    ✅    |   ❌   | 1110 |
| \<invalid> |    ✅    |   ✅   |    ❌    |   ✅   | 1101 |
|  no code   |    ✅    |   ✅   |    ❌    |   ❌   | 1100 |
|  no code   |    ✅    |   ❌   |    ✅    |   ✅   | 1011 |
|   const    |    ✅    |   ❌   |    ✅    |   ❌   | 1010 |
| \<invalid> |    ✅    |   ❌   |    ❌    |   ✅   | 1001 |
|   const!   |    ✅    |   ❌   |    ❌    |   ❌   | 1000 |
| \<invalid> |    ❌    |   ✅   |    ?    |   ?   | 01?? |
|  const!!   |    ❌    |   ❌   |    ✅    |   ❌   | 0010 |
|   var!!    |    ❌    |   ❌   |    ✅    |   ✅   | 0011 |
|  no code   |    ❌    |   ❌   |    ❌    |   ✅   | 0001 |
|    null    |    ❌    |   ❌   |    ❌    |   ❌   | 0000 |


Table of valid declarations
|         |         |       |         |       |                         |
| :-----: | :-----: | :---: | :-----: | :---: | :---------------------: |
|   {}    | compile |       | runtime |       |         Comment         |
|    ^    |  read   | write |  read   | write |            ^            |
|         |         |       |         |       |            ^            |
|   var   |    ✅    |   ✅   |    ✅    |   ✅   |         &nbsp;          | 1111 |
|  var!   |    ✅    |   ✅   |    ✅    |   ❌   |         &nbsp;          | 1110 |
| no code |    ✅    |   ✅   |    ❌    |   ❌   | [*optimized](#optimize) | 1100 |
|  const  |    ✅    |   ❌   |    ✅    |   ❌   |         &nbsp;          | 1010 |
| const!  |    ✅    |   ❌   |    ❌    |   ❌   |         &nbsp;          | 1000 |
| const!! |    ❌    |   ❌   |    ✅    |   ❌   |         &nbsp;          | 0010 |
|  var!!  |    ❌    |   ❌   |    ✅    |   ✅   |         &nbsp;          | 0001 |



var a = 20;

const a = 30

a := 20
a :: 30


main :: (argv: char*, argc: i32) -> {

}


fn main (argv: char*, argc: i32) {
    
    var funcioncita = {30};

    var vectorcito : vector<Personas> = ...

    
    () -> {}
    sort(vectorcito, {} )


}


Table of valid declarations

|        |         |       |         |       |
| -----: | :-----: | :---: | :-----: | :---: |
|     {} | compile |       | runtime |       |
|      ^ |  read   | write |  read   | write |
|        |         |       |         |       |
|  a  := |    ✅    |   ✅   |    ✅    |   ✅   | 1111 |
|  a! := |    ✅    |   ✅   |    ✅    |   ❌   | 1110 |
| a!! := |    ❌    |   ❌   |    ✅    |   ✅   | 0001 |
|   a :: |    ✅    |   ❌   |    ✅    |   ❌   | 1010 |
|  a! :: |    ✅    |   ❌   |    ❌    |   ❌   | 1000 |
| a!! :: |    ❌    |   ❌   |    ✅    |   ❌   | 0010 |

{#optimize *Should be optimized away from any of the other options} 

# Calling conventions

 | Name     |                                       |
 | :------- | :------------------------------------ |
 | call()!  | Make call at compiletimes             |
 | call()!! | Call is always at runtime             |
 | call()   | Let the compiler deside               |
 | call!()  | Call this code on the AST (Macros)    |
 | !call()  | Call on the text and generates an AST |
 | !!call() | --- Invalid for now --                |


op ( a + b ) :: fn (a : Type, b : Typse) 

