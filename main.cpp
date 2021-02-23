#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include "class.h"

using namespace std;

int main(int argc, char* argv[])
{

    // 2 1 2 3 6

    int CL = atoi(argv[1]);
    int Lj = atoi(argv[2]);
    int Ls = atoi(argv[3]);
    int Lt = atoi(argv[4]);
    int N = atoi(argv[5]);

    Student** st;
    Teacher** tchr;

    st = STdata(CL); // reading students' info
    if (st == NULL)
    {
        cout << "ERROR OCCURED!" << endl;
        return -1;
    }

    tchr = TCHRdata(); // reading teachers' info
    if (tchr == NULL)
    {
        cout << "ERROR OCCURED!" << endl;
        return -1;
    }

    School school(CL);

    long now;
	now=time(NULL); // now is current time
	srand((unsigned int)now); // definition of rand() -> gave here current time as seed

    int choose;
	int guess;
	int all=0;

    while(all!=(CL+1)*18)
	{
		choose = rand()%2;
		if(choose==0) // students
		{
			choose = rand()%(CL*18);
			if(st[choose]->getAT()!="OFF")
				continue;
			else
			{
				school.enter(st[choose]);
				++all;
			}
		}
		else // teachers
		{
			choose = rand()%18;
			if(tchr[choose]->getFLAG()==1)
				continue;
			else
			{
					school.place(tchr[choose]);
					++all;
			}

		}
	}

    school.operate(N,Lj,Ls,Lt);

    school.print();

    for(int i=0 ; i<(CL*18) ; ++i)
        delete st[i];
    delete st;

    for(int i=0; i<18 ; ++i)
        delete tchr[i];
    delete tchr;

    cout << endl;
}
