#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
using namespace std;

string Keyword[32]=
{
	"auto","break","case","char","const","continue","default","double",
	"do","else","enum","extern","float","for","goto","if","int","long",
	"register","return","short","signed","sizeof","static","struct",
	"switch","typedef","union","unsigned","void","volatile","while"
};

vector<int> Case_num;
int total_num = 0;
int switch_num = 0;
int case_num = 0;
int ifelse_num = 0;
int if_elseif_else_num = 0;
int stack[ 1000 ] = { 0 };
int top = -1;//Define the required variables

int match( string a , string b )
{
	int correspond( char str );
	int pos = a.find( b , 0 );
	int len = b.length();	
	if( pos != string::npos )
	{
		if( pos == 0 ) 
		{
			if(correspond( a[ pos + len ] ) == 0 )
			{
				return 1;
			}
			else 
			{
				return 0;  
			}  	
		}
		else
		{
			if(correspond( a[ pos + len] ) == 0 && correspond( a[ pos - 1] ) == 0 )
			{
				return 1;
			}
			else
			{
				return 0;
			}	
		}
	}
	return 0;
}

int correspond( char str )
{
	if( ( str <= 'z' && str >= 'a' ) || ( str <= 'Z' && str >= 'A' ) )
	{
		return 1;
	}
	else
	{
		return 0;	
	}	
}

void sort_1(string str)
{
	for(int i = 0; i < 32; i++ )
	{
		if(match( str , Keyword[i] ) == 1)
		{
			if( match( str , "switch" ) )
			{
				Case_num.push_back( case_num );
				switch_num++;
				case_num = 0;
			}
			if( match( str , "case" ))
			{
				case_num++;
			}
			total_num++;
			break;
		}
	}
}

void sort_2( string str )
{
	if( match( str , "else if" ) )
	{
		top++;
		stack[ top ] = 2;
	}	
	else
	{
		if( match( str , "else" ) )
		{
			if( stack[ top ] == 1 )
			{
				ifelse_num++;
				top--;
			}
			else
			{
				if( stack[ top ] == 2 )
				{
					if_elseif_else_num++;
					top--;
				}
			}
		}
		else
		{
			if(match( str ,"if" ) )
			{
				top++;
				stack[ top ] = 1;
			}
		}
	}
}

int main()
{
	int level;
	string file,temp;
	cout << "Enter the file path: " << endl;
	cin >> file;
	cout << "Enter the completion level: " << endl;
	cin >> level;
	ifstream File( file.c_str() );
	int correspond( string a,string b );
	int correspond( char str);
	void sort_1( string str );
	void sort_2( string str );
	while ( getline( File ,temp ))
	{
		istringstream istr ( temp );
		string str;
		if( level >= 3)
		{
			sort_2( temp );
		}
		while( istr >> str ) 
		{
			sort_1( str );
		}
	}
	if( level >= 1 ) 
	{
		cout << "total num: " << total_num << endl;
	}
	if( level >= 2 )
	{
		cout << "switch num: " << switch_num << endl;
		if( !Case_num.empty() )
		{
			Case_num.push_back(case_num);
		}
		else
		{
			Case_num.push_back(0);
		}
		cout << "case num: ";
		for ( int i = 1; i <= switch_num; i++)
		{
			cout<< Case_num[i] << " ";
		}
		cout << endl;
	}
	if( level >=3 )
	{
		cout << "if_else num: " << ifelse_num << endl;
	}
	if( level >=4 )
	{
		cout << "if_elseif_else num: " <<if_elseif_else_num << endl;
	}
}
