#include<iostream>
#include<string> 
#include<stdio.h>
#include<stdlib.h>

using namespace std;



int main()
{
	int a,b,c,d,e,f,g,h,v;
	int i;
	int erreur=0;
	
	
	string convert;
	
	string maChaine;
	
	while(( maChaine.size()==0)||(maChaine.size()==1)||(maChaine.size()==2)||(maChaine.size()==3)||(maChaine.size()==4)||(maChaine.size()==6)||(maChaine.size()==7))
	{	
		cout<<"entrez votre commande /n ";  // size = 0  
		getline(cin, maChaine);
	}
	
	switch(maChaine[0]){
		case'a':maChaine[0]='8';
		case'b':maChaine[0]='7';
		case'c':maChaine[0]='6';
		case'd':maChaine[0]='5';
		case'e':maChaine[0]='4';
		case'f':maChaine[0]='3';
		case'g':maChaine[0]='2';
		case'h':maChaine[0]='1';
		default: erreur=1;
	}
	
	switch(maChaine[3]){
		case'a':maChaine[3]='8';
		case'b':maChaine[3]='7';
		case'c':maChaine[3]='6';
		case'd':maChaine[3]='5';
		case'e':maChaine[3]='4';
		case'f':maChaine[3]='3';
		case'g':maChaine[3]='2';
		case'h':maChaine[3]='1';
	}
	
	switch(maChaine[6]){
		case'a':maChaine[6]='8';
		case'b':maChaine[6]='7';
		case'c':maChaine[6]='6';
		case'd':maChaine[6]='5';
		case'e':maChaine[6]='4';
		case'f':maChaine[6]='3';
		case'g':maChaine[6]='2';
		case'h':maChaine[6]='1';
	}

	cout<<maChaine<<endl;
	convert=maChaine;
	cout<<convert<<endl;
	return 0;
}






























