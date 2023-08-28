
output "Hello";
output "World";

output "Hello"#"World";
output ^Hello^#"World";
output "Hello"#"World":1;
output ("Hello"#"World"):7;
output ("Hello"#"World"):-1;
output (^Hello^#"World"):1;
output "Hello"#"World"-'l';
output "Hello"#("World"-'l');

sentence s1;

s1 = ^We live in a^;
output s1#^World^;
s1 = s1#"wonderful"#"world"#'!';
output s1;
output s1-"wonderful";
output s1-'w';
