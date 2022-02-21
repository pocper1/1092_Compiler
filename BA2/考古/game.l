%{

%}

up [w]
down [x]
left [a]
right [d]
attack [s]
jump [t]
defend [\`]
q_run {right}{right}|{left}{left}
eol \n

Soul_Punch  {q_run}{attack}
Uppercut {defend}{up}{attack}
Skull_blast {defend}{right}({attack})+
Mirror_Image {defend}{jump}{attack}({jump})+
Soul_Bomb {defend}{right}{jump}
Big_Bang {defend}{up}{jump}

%%

{Soul_Punch} {
    printf("Soul_Punch\n");
}

{Uppercut} {
    printf("Uppercut\n");
}

{Skull_blast} {
    printf("Skull_blast\n");
}

{Mirror_Image} {
    printf("Mirror_Image\n");
}

{Soul_Bomb} {
    printf("Soul_Bomb\n");
}

{Big_Bang} {
    printf("Big_Bang\n");
}

{eol} {

}
. {

}
%%
int main(int argc, char *argv[]){
  yylex();
  return(0);
}