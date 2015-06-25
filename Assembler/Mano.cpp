#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <ctype.h>
#include <bitset>
#include <math.h>
#include <iomanip>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <cstdio>
#include <stdio.h>
#include <list>
#include <functional>
#include <limits>
#include <limits.h>
#include <sstream>

using namespace std;
int i= -1 ; string LC = "0" ;
string s[7] = {"AND" ,"ADD","LDA","STA","BUN","BSA", "ISZ" };
vector <string> MInstruction (begin(s) , end(s));
string ss[18] = {"CLA","CLE","CMA","CME","CIR","CIL","INC","SPA","SNA","SZA","SZE","HLT","INP","OUT","SKL","SKO","ION","IOF"} ;
vector <string> notMInstruction (begin(ss) , end(ss));

vector < vector <string> > code ;
vector <string> BinaryCode ;

map <string  , string > Labels ;
map <string , string > Instruction ;
map <string , string > Memory ;

void Intionlization ()
{
	// Instructions 

	// Memory Instruction ::
	// 1) Direct :
	Instruction["AND"] = "0000" ;
	Instruction["ADD"] = "0001" ;
	Instruction["LDA"] = "0010" ;
	Instruction["STA"] = "0011" ;
	Instruction["BUN"] = "0100" ;
	Instruction["BSA"] = "0101" ;
	Instruction["ISZ"] = "0110" ;

	// 2) Indirect
	Instruction["IAND"] = "1000" ;
	Instruction["IADD"] = "1001" ;
	Instruction["ILDA"] = "1010" ;
	Instruction["ISTA"] = "1011" ;
	Instruction["IBUN"] = "1100" ;
	Instruction["IBSA"] = "1101" ;
	Instruction["IISZ"] = "1110" ;

	// Refrense Instruction ::
	Instruction["CLA"] = "0111 1000 0000 0000";
	Instruction["CLE"] = "0111 0100 0000 0000" ;
	Instruction["CMA"] = "0111 0010 0000 0000" ;
	Instruction["CME"] = "0111 0001 0000 0000" ;
	Instruction["CIR"] = "0111 0000 1000 0000" ;
	Instruction["CIL"] = "0111 0000 0100 0000" ;
	Instruction["INC"] = "0111 0000 0010 0000" ;
	Instruction["SPA"] = "0111 0000 0001 0000" ;
	Instruction["SNA"] = "0111 0000 0000 1000" ;
	Instruction["SZA"] = "0111 0000 0000 0100" ;
	Instruction["SZE"] = "0111 0000 0000 0010" ;
	Instruction["HLT"] = "0111 0000 0000 0001" ;

	// I/O Instraction ::
	Instruction["INP"] = "1111 1000 0000 0000" ;
	Instruction["OUT"] = "1111 0100 0000 0000" ;
	Instruction["SKL"] = "1111 0010 0000 0000" ;
	Instruction["SKO"] = "1111 0001 0000 0000" ;
	Instruction["ION"] = "1111 0000 1000 0000" ;
	Instruction["IOF"] = "1111 0000 0100 0000" ;
}
string HtoB3 (string x)
{
	string y = "" ;
	while(x.size() != 3 && x.size() != 4)
	{
		x.insert(0 , "0");
	}
	for (int j= 0 ; j< x.size() ; ++j)
	{
		y+= " ";
		if(x[j] == '0') y+= "0000" ;
		else if (x[j] == '1') y+= "0001" ;
		else if (x[j] == '2') y+= "0010" ;
		else if (x[j] == '3') y+= "0011" ;
		else if (x[j] == '4') y+= "0100" ;
		else if (x[j] == '5') y+= "0101" ;
		else if (x[j] == '6') y+= "0110" ;
		else if (x[j] == '7') y+= "0111" ;
		else if (x[j] == '8') y+= "1000" ;
		else if (x[j] == '9') y+= "1001" ;
		else if (x[j] == 'A') y+= "1010" ;
		else if (x[j] == 'B') y+= "1011" ;
		else if (x[j] == 'C') y+= "1100" ;
		else if (x[j] == 'D') y+= "1101" ;
		else if (x[j] == 'E') y+= "1110" ;
		else if (x[j] == 'F') y+= "1111" ;
	}

	return y;
}
string HtoB4 (string x)
{
	string y = "" ;
	while( x.size() != 4)
	{
		x.insert(0 , "0");
	}
	for (int j= 0 ; j< x.size() ; ++j)
	{
		if(x[j] == '0') y+= "0000" ;
		else if (x[j] == '1') y+= "0001" ;
		else if (x[j] == '2') y+= "0010" ;
		else if (x[j] == '3') y+= "0011" ;
		else if (x[j] == '4') y+= "0100" ;
		else if (x[j] == '5') y+= "0101" ;
		else if (x[j] == '6') y+= "0110" ;
		else if (x[j] == '7') y+= "0111" ;
		else if (x[j] == '8') y+= "1000" ;
		else if (x[j] == '9') y+= "1001" ;
		else if (x[j] == 'A') y+= "1010" ;
		else if (x[j] == 'B') y+= "1011" ;
		else if (x[j] == 'C') y+= "1100" ;
		else if (x[j] == 'D') y+= "1101" ;
		else if (x[j] == 'E') y+= "1110" ;
		else if (x[j] == 'F') y+= "1111" ;
		y+= " ";
	}

	return y;
}
string decimalToBinary(int decimal) {
	string binary;
	bool neg = decimal < 0 ? true : false;
	if (neg) decimal *= -1 ;
	while(decimal)  {
		binary.insert(0, 1, (decimal & 1) + '0');
		decimal >>= 1;
	}
	while(binary.size()<16)
	{
		binary.insert(binary.begin() , '0');
	}

	if (neg)
	{
		bool one = false ;
		for(int h=binary.size() -1  ; h> -1 ; --h)
		{
			if (one)
				if (binary[h] == '1') binary[h] = '0' ;
				else binary[h] = '1' ;
			else if (binary[h] == '1')
				one = true ;
		}
	}

	binary.insert(binary.begin()+4 , ' ');
	binary.insert(binary.begin()+9 , ' ');
	binary.insert(binary.begin()+14 , ' ');

	return binary;
}
int toint (string x)
{
	int y;
	stringstream Scin ;
	Scin << x ;
	Scin >> y;
	return  y;
}
void Inc(string &LC)
{
	int c = 1 , h=1 ;
	while (c && h <= LC.size() )
	{
		char x= LC[LC.size()-h] ; c= 0;
		if ( (x>= '0' && x < '9') || (x>= 'A' && x< 'F') )
			LC[LC.size()-h]= LC[LC.size()-h] + 1 ;
		else if (x== '9')
			LC[LC.size()-h] = 'A' ;
		else if (x== 'F')
		{LC[LC.size()-h] = '0' ; c=1 ; h++;}

	}
}
int main ()
{

	//freopen("ass.in", "r", stdin);

	Intionlization () ;
	// Get Code ::
	string trap , x , y;
	while (getline(cin , trap ))
	{	
		vector<string> temp ;
		stringstream stst ;
		stst << trap ;
		while (stst >> x)
		{
			temp.push_back(x);
		}
		code.push_back(temp);
		// Fist pass :
		++ i ;
		if (code[i][0] == "END")
		{
			break ;
			Inc(LC); //++ LC ;
		}// end of pass one
		else if (code[i][0] == "ORG")
			LC = code[i][1] ;
		else if (temp.size() != 1)
		{
			if (code[i][1] == "," )
			{
				Labels[code[i][0] ] = LC ;
				temp.erase(temp.begin()+1);
				code[i] = temp ;
			}
			else if ( code[i][0][code[i][0].size() -1] == ',')
			{
				code[i][0].erase((code[i][0].size() )-1 , 1);
				Labels[ code[i][0] ] = LC ;
				temp.erase(temp.begin());
				code[i]=temp;
			}
			Inc(LC); //++ LC ;
		}
		else
			Inc(LC); //	++ LC;

		// ---------
	}

	// second pass :
	LC = "0" ;
	int k=i ;
	for ( i=0 ; i<= k ; ++i)
	{
		//int codeisize = code[i].size();
		if (code[i][0] == "END")
			break ; // end of pass one
		else if (code[i][0] == "ORG")
		   { LC = code[i][1] ; continue ; }
		else if (code[i][0] == "HEX")
		   { BinaryCode.push_back(HtoB4(code[i][1])); continue ; }
		else if (code[i][0] == "DEC")
		{
			int m = toint(code[i][1]) ;
			BinaryCode.push_back(decimalToBinary(m)); continue ;
		}
		//------------

		if (find(notMInstruction.begin() , notMInstruction.end() ,code[i][0]) != notMInstruction.end())
		{
			if (Instruction.find(code[i][0])!= Instruction.end())
				BinaryCode.push_back( Instruction[code[i][0] ] );
			else
				cout <<"Error !!! :@\n";
		}
		else if (find(MInstruction.begin() , MInstruction.end() ,code[i][0]) != MInstruction.end())
		{
			if (code[i][code[i].size()-1]== "I")
				code[i][0].insert(0 , "I" );

			x= Instruction[code[i][0] ] ;
			// add address :
			if (Labels.find(code[i][1]) != Labels.end())
			{
				y = Labels[code[i][1] ] ;
			x += HtoB3(y);
			BinaryCode.push_back(x );
			}
			else
			{
				y= "Error not correct V" ;
				BinaryCode.push_back(y);
			}
		}
		Inc(LC); //++LC ;
		//	BinaryCode.pop_back(Instruction[code[i][0]]) ;
	}

	for(i=0 ; i<BinaryCode.size() ; ++i)
		cout << BinaryCode[i] << endl;
	return 0;
}