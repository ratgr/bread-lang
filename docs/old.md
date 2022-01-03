| Full Table of posible declarations |||  |  |
|:---:  |:---:|:---:    |:---:|:---:    | 
{}      | read  |    | write |     |
{}      | comp | run | comp | run | 
|
var        | ✅ | ✅ | ✅ | ✅ | 
var!       | ✅ | ✅ | ✅ | ❌ | 
no code    | ✅ | ✅ | ❌ | ✅ | 1011
const      | ✅ | ✅ | ❌ | ❌ | 
invalid    | ✅ | ❌ | ❌ | ✅ |
const!     | ✅ | ❌ | ❌ | ❌ |
invalid    | ❌ | ✅ | ✅ | ✅ |
invalid    | ❌ | ✅ | ✅ | ❌ |
var!!      | ❌ | ✅ | ❌ | ✅ |
const!!    | ❌ | ✅ | ❌ | ❌ |
invalid    | ❌ | ❌ | ✅ | ✅ |
invalid    | ❌ | ❌ | ✅ | ❌ |
invalid    | ❌ | ❌ | ❌ | ✅ |
null       | ❌ | ❌ | ❌ | ❌ |

| Name  |         |     |  |  |
|:---:  |:---:|:---:    |:---:|:---:    | 
{}      | read  |    | write |     |
{}      | comp | run | comp | run | 
|
var        | ✅ | ✅ | ✅ | ✅ | 
var!       | ✅ | ✅ | ✅ | ❌ | 1110
codeless   | ✅ | ❌ | ✅ | ❌ | 
const      | ✅ | ✅ | ❌ | ❌ | 
const!     | ✅ | ❌ | ❌ | ❌ |
var!!      | ❌ | ✅ | ❌ | ✅ |
const!!    | ❌ | ✅ | ❌ | ❌ |