%{
int section = 0;
%}
Decimal  [0-9]+
ProperFraction  {Decimal}\/{Decimal}
measurement cup|tablespoon|teaspoon
measurements cups|tablespoons|teaspoons
Dir  Directions
space [ \r\t\n\f]
tools  ({Decimal}{space}({measurement}|{measurements})|{ProperFraction}{space}({measurement}|{measurements})|{Decimal}{space}{ProperFraction}{space}({measurement}|{measurements}))
%%
{tools}  { if(section == 0 ) printf("%s\n" , yytext );
           else if(section==2) printf("# %s\n" , yytext );}
{Dir}  {section = 2;}
\n  {;}
.  {;}
%%
int main(int argc, char *argv[]) {
	yylex();
	return(0);
}