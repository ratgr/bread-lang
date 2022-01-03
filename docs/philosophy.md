
## Title

1) Should allow migration from a c++ code base file by file-
2) Not forcing the programmer to do things your way
3) Same code should be possible to run @ compile time as runtime


## Consequences



# Scope



minimal scope:

<table class="compare">
<tr><th>scope</th><th>longer</th><th>longer</th></tr>
<tr><td>

``` cpp
my_lambda := { 
    lamda-body
}
```
</td><td>

``` cpp

my_lambda := {
    lamda-body
}[capture-list]

```

</td><td>

``` cpp
la := (args-list) -> {
    lamda-body
}[capture-list]

```

</td></tr>
</table>




<table class="compare2">
<col/><col/>
<tr><th markdown="1">shorthand</th> <th>longer</th></tr>
<tr><td>

``` cpp
A :: ns { 

}
```
</td><td>

``` bread 
A :: #static #default_public {

}
```
</td></tr>
</table>


var a = {  

}


main :: () -> { 


}