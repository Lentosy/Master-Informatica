int foo[10]; 
int a = 0;
int b = 9;
int c = 10;
foo[a] = 1;
echo(foo[a]);
foo[b] = 1;
echo(foo[b]);
foo[c] = 1; // error here
echo(foo[c]);

