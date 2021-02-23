#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
//#include <ctime>
//#include <cstdlib>
#include "class.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////

Student** STdata(int CL) {

    //Student** st = (Student**)malloc(sizeof(Student*)*(CL*18));
    Student** st = new Student*[CL*18];

    ifstream inputFile;

    inputFile.open("studentsFULL.txt");
	if (!inputFile)
	{
		cout << "Cannot find input file" << endl;
		return NULL;
	}

    int infoF,infoC,j=0;

    int i=0;
    string s;
	string token,nam;
	string delimiter = "-";
	string info;

    while( getline (inputFile,s))
	{
		size_t pos = 0;
		size_t last = 0;
		size_t next = 0;
		j=0;
		while ((next = s.find(delimiter, last)) != string::npos)
		{
			if (j==0)
			{
				info = s.substr(last, next-last);
				//cout << info << endl;
				last = next + 1;
				++j;
				nam = info;
			}
			else
			{
				info = s.substr(last, next-last);
				stringstream geek(info);
				infoF=0;
				geek >> infoF;
				//cout << test << endl;
				last = next + 1;
				++j;
			}
		}

		info = s.substr(last);
		stringstream geek(info);
		infoC=0;
		geek >> infoC;
		//cout << test << endl;


		st[i] = new Student(nam,infoF,infoC);
		++i;
	}
	inputFile.close();

    return st;

}

Teacher** TCHRdata()
{
    //Teacher** tchr = (Teacher**)malloc(sizeof(Teacher*)*18);
    Teacher** tchr = new Teacher*[18];

    ifstream inputFile;

    inputFile.open("teachersFULL.txt");
	if (!inputFile)
	{
		cout << "Cannot find input file" << endl;
		return NULL;
	}

    int infoF,infoC,j=0;

    int i=0;
    string s;
	string token,nam;
	string delimiter = "-";
	string info;

    while( getline (inputFile,s))
	{
		size_t pos = 0;
		size_t last = 0;
		size_t next = 0;
		j=0;
		while ((next = s.find(delimiter, last)) != string::npos)
		{
			if (j==0)
			{
				info = s.substr(last, next-last);
				//cout << info << endl;
				last = next + 1;
				++j;
				nam = info;
			}
			else
			{
				info = s.substr(last, next-last);
				stringstream geek(info);
				infoF=0;
				geek >> infoF;
				//cout << test << endl;
				last = next + 1;
				++j;
			}
		}

		info = s.substr(last);
		stringstream geek(info);
		infoC=0;
		geek >> infoC;
		//cout << test << endl;


		tchr[i] = new Teacher(nam,infoF,infoC);
		++i;
	}
	inputFile.close();

    return tchr;
}

/////////////////////////////////////////////////////////////////////////////

/* methods */

/////////////////////////////////////////////////////////////////////////////

void Student::print()
{ cout << "Student: " << name << " -> " << fl << " -> " << cl << endl; }

void Person::printNAME()
{ cout << name; }

/*void Student::printNAME()
{ cout << name; }*/

void Teacher::print()
{
	cout << "Teacher: " << name << " -> " << fl << " -> " << cl << endl;
}

/*void Teacher::printNAME()
{ cout << name; }*/

string Student::getAT() { return at; }

void Student::setAT(string there)
{ this->at = there; }


void Person::getF_CL(int &f, int &c)
{
	f = fl;
	c = cl;
}
/*void Student::getF_CL(int &f, int &c)
{
	f = fl;
	c = cl;
}*/

void Person::setFATIGUE(int N, int L)
{ fatigue = N*L; }

int Person::getFATIGUE()
{ return this->fatigue; }

/*void Student::setFATIGUE(int N, int L)
{
	fatigue = N*L;
}*/

/*int Student::getFATIGUE() { return this->fatigue; }*/

int Teacher::getFLAG() { return flag; }

void Teacher::setFLAG() { this->flag = 1; }

/*void Teacher::getF_CL(int &f, int &c)
{
	f = fl;
	c = cl;
}*/

/*void Teacher::setFATIGUE(int N, int L)
{
	fatigue = N*L;
}*/

/*int Teacher::getFATIGUE() { return this->fatigue; }*/


void School::enter(Student* st)
{
	st->printNAME();
	cout << " enters School" << endl;
	st->setAT("School");
	STppl++;
	yard->enter(st);
	yard->exit(st);
	stair->enter(st);
	stair->exit(st);
	int f,c;
	st->getF_CL(f,c);
	fl[f-1]->enter(st,f,c);
}

void Floor::enter(Student* st, int f, int c)
{
	st->printNAME();
	cout << " enters Floor No." << f << endl;
	st->setAT("Floor");
	corr->enter(st);
	corr->exit(st);
	cl[c-1]->enter(st,c);
}

void Schoolyard::enter(Student* st)
{
	st->printNAME();
	cout << " enters Schoolyard" << endl;
	st->setAT("Schoolyard");
}
void Schoolyard::exit(Student* st)
{
	st->printNAME();
	cout << " exits Schoolyard" << endl;
}

void Stairs::enter(Student* st)
{
	st->printNAME();
	cout << " enters Stairs" << endl;
	st->setAT("Stairs");
}
void Stairs::exit(Student* st)
{
	st->printNAME();
	cout << " exits Stairs" << endl;
}

void Corridor::enter(Student* st)
{
	st->printNAME();
	cout << " enters Corridor" << endl;
	st->setAT("Corridor");
}
void Corridor::exit(Student* st)
{
	st->printNAME();
	cout << " exits Corridor" << endl;
}

void Class::enter(Student* st, int c)
{
	st->printNAME();
	cout << " enters Class No." << c << endl;
	st->setAT("Class");
	list[ppl] = st;
	ppl++;
}


void School::place(Teacher* tchr)
{
	tchr->printNAME();
	cout << " is placed in his Class!" << endl;
	int f,c;
	tchr->getF_CL(f,c);
	fl[f-1]->place(tchr,c);
}
void Floor::place(Teacher* tchr, int c)
{
	cl[c-1]->place(tchr);
}
void Class::place(Teacher* tchr)
{
	teacher = tchr;
	tchr->setFLAG();
}


void School::operate(int N, int Lj, int Ls, int Lt)
{
	for(int i=0 ; i<3 ; ++i)
		fl[i]->operate(N,Lj,Ls,Lt);
}
void Floor::operate(int N, int Lj, int Ls, int Lt)
{
	for(int i=0 ; i<6 ; ++i)
	{
		if(i<3)
			cl[i]->operate(N,Lj,Lt);
		else
			cl[i]->operate(N,Ls,Lt);
	}
}
void Class::operate(int N, int L, int Lt)
{
	teacher->setFATIGUE(N,Lt);
	for(int i=0 ; i<capacity ; ++i)
		list[i]->setFATIGUE(N,L);
}


void School::print()
{
	cout << "School life consists of:" << endl << endl << endl;
	for(int i=0 ; i<3 ; ++i)
	{
		cout << "Floor No." << i+1 << " contains:" << endl << "---------------------" << endl;
		fl[i]->print();
		cout << endl << endl;
	}
}
void Floor::print()
{
	for(int i=0 ; i<6 ; ++i)
	{
		cout << "Class No." << i+1 << endl;
		cl[i]->print();
		cout << endl;
	}
}
void Class::print()
{
	cout << "The teacher is: ";
	teacher->printNAME();
	cout << " (" << teacher->getFATIGUE() << " fp)" << endl;
	for(int i=0 ; i<capacity ; ++i)
	{
		list[i]->printNAME();
		cout << " (" << list[i]->getFATIGUE() << " fp)" << endl;
	}
}
