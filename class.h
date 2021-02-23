#include <iostream>
#include <string>

using namespace std;

class Place;
class School;
class Floor;
class Class;
class Corridor;
class Schoolyard;
class Stairs;
class Person;
class Student;
class Teacher;


/* hyper-class for a person */
class Person{
    protected:
        string name; // name of person
        int fl,cl; // fl~floor | cl~class
        int fatigue; //
    public:
        Person(string nam, int f, int c) : name(nam) , fl(f) , cl(c) , fatigue(0)
        {/*cout << "A New Person has been created!" << endl << name << " -> Floor No." << fl << ", Class No. " << cl << endl;*/};
        ~Person() { /* cout << "A New Person has been created!" << endl << name << " -> Floor No." << fl << ", Class No. " << cl << endl; */ };
        virtual void print() = 0;
        void printNAME();
        void getF_CL(int &f, int &c);
        void setFATIGUE(int N, int L);
        int getFATIGUE();
};

/* sub-class of Person for STUDENT */
class Student : public Person {
    private:
        string at; // indicates where he is at the moment
        string type; // indicates if he is "junior" or "senior"
    public:
        Student(string nam, int f, int c) : Person(nam,f,c)
        {
            this->at = "OFF"; // indicates that students if OFF class
            if(c<=3)
                this->type = "Junior";
            else
                this->type = "Senior";
            cout << "A New Student has been created!" << endl << name << " -> Floor No." << fl << ", Class No. " << cl << endl;
            cout << at << " -> " << type << endl << endl;
        };
        ~Student() { cout << "A Student to be destroyed!" << endl << name << endl; };
        virtual void print();
        //void printNAME();
        string getAT();
        //void getF_CL(int &f, int &c);
        void setAT(string there);
        //void setFATIGUE(int N, int L);
        //int getFATIGUE();
};

/* sub-class of Person for TEACHER */
class Teacher : public Person {
    private:
        int flag; // indicates if he is in/out his class
    public:
        Teacher(string nam, int f, int c) : Person(nam,f,c) , flag(0)
        {cout << "A New Teacher has been created!" << endl << name << " -> Floor No." << fl << ", Class No. " << cl << endl << endl;};
        ~Teacher() {cout << "A Teacher to be destroyed!" << endl << name << endl;};
        virtual void print();
        //void printNAME();
        int getFLAG();
        void setFLAG();
        //void getF_CL(int &f, int &c);
        //void setFATIGUE(int N, int L);
        //int getFATIGUE();
};


/* hyper-class for a place */
class Place {
    protected:
        //int ppl; // how many people are in this place
        //Student* st;
    public:
        Place() { /*cout << "Created a Place" << endl;*/ };
        ~Place() { /*cout << "Place Destroyed" << endl;*/ };
};

/* sub-class of Place for Schoolyard */
class Schoolyard : public Place {
    //private:
    public:
        Schoolyard() { /*cout << "Schoolyard created" << endl;*/ };
        ~Schoolyard() { /*cout << "Schoolyard destroyed" << endl;*/ };
        void enter(Student* st);
        void exit(Student* st);
};

/* sub-class of Place for Stairs */
class Stairs : public Place {
    //private:
    public:
        Stairs() { /*cout << "Stairs created" << endl;*/ };
        ~Stairs() { /*cout << "Stairs destroyed" << endl;*/ };
        void enter(Student* st);
        void exit(Student* st);
};

/* sub-class of Place for Corridor */
class Corridor : public Place {
    //private:
    public:
        Corridor() {/*cout << "A Corridor is created" << endl;*/ };
        ~Corridor() {/*cout << "A Corridor is destroyed" << endl;*/ };
        void enter(Student* st);
        void exit(Student* st);
};

/* sub-class of Place for Class */
class Class : public Place {
    private:
        int ppl;
        int capacity; // capacity of students in class
        Student** list; // list of students in class
        Teacher* teacher; // teacher of class
    public:
        Class(int cap) : capacity(cap), ppl(0)
        {
            //cout << "A Class is created" << endl;
            //list = (Student**)malloc(sizeof(Student*)*cap);
            list = new Student*[cap];
            teacher = NULL;
        }
        ~Class()
        {
            for(int i=0 ; i<capacity ; ++i)
                delete list[i];
            delete list;
            delete teacher;
        }
        void print(); // print function
        void enter(Student* st, int c);
        void place(Teacher* tchr);
        void operate(int N, int L, int Lt);
};

/* class for Floor */
class Floor {
    private:
        Class** cl; // array of pointers to classes
        Corridor* corr;
    public:
        Floor(int CL)
        {
            //cout << "A Floor is created!" << endl;
	        corr = new Corridor();
            //cl = (Class**)malloc(sizeof(Class*)*6);
            cl = new Class*[6];
            for (int i=0 ; i<6 ; ++i)
                cl[i] = new Class(CL);
        }
        ~Floor()
        {
            delete corr;
            /*for(int i=0; i<6 ; ++i)
                delete cl[i];*/
            delete cl;
        }
        void print(); // print function
        void enter(Student* st, int f, int c);
        void place(Teacher* tchr, int c);
        void operate(int N, int Lj, int Ls, int Lt);
};

/* class for School */
class School {
    private:
        int STppl; // sum of students
        int TCHRppl; // sum of teachers
        Schoolyard* yard; // pointer to schoolyard
        Stairs* stair; // pointers to stairs
        Floor** fl; // array of pointers of floors
    public:
        School(int CL)
        {
            cout << "A School has been created!" << endl << endl;
            STppl = 0;
            TCHRppl = 0;
            yard = new Schoolyard();
            stair = new Stairs();
            //fl = (Floor**)malloc(sizeof(Floor*)*3);
            fl = new Floor*[3];
            for(int i=0 ; i<3 ; ++i)
                fl[i] = new Floor(CL);
        }
        ~School()
        {
            cout << "A School to be destroyed!" << endl;
            delete yard;
            delete stair;
            /*for(int i=0 ; i<3 ; i++)
                delete fl[i];*/
            delete fl;
        }
        void print(); // print function
        void enter(Student* st);
        void place(Teacher* tchr);
        void operate(int N, int Lj, int Ls, int Lt);
};

Student** STdata(int CL); // function which returns students' info
Teacher** TCHRdata(); // function which returns teachers' info
