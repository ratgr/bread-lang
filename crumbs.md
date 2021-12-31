# Types


uint, int  ∈ Integral
i8, u8     ∈ Integral
i16, u16   ∈ Integral
i64, u64   ∈ Integral


# Instructions

    typeCreator(name? : string) : Builder<Type>

    
# Example

```
    create_struct("Add")
    create_function("")

    function("name")
        

```
# function

### NOP

Opcode 

Opcode | param 1| param 2 | result
--   | --   |--    | --    | --
0x58 | ptrA    | Integral |  ptrA
0x58 | Numeric | Numeric |  ptrA

### ADD
Opcode | param 1| param 2 | result
--   | --   |--    | --    | --
0x58 | ptrA    | Integral |  ptrA
0x58 | Numeric | Numeric |  ptrA

### AND
Opcode | param 1| param 2 | result
--   | --    |--       | --   
0x5F | ptrA  | Numeric |  ptrA

