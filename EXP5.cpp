#include <iostream>
using namespace std;
struct Employee
{
 int id;
 string name;
 string designation;
 float salary;
 int flag;
};
Employee emp[50];
int index_id[50];
int pos[50];
int n = 0;
void addEmployee()
{
 cout<<"Enter Employee ID: ";
 cin>>emp[n].id;
 cout<<"Enter Name: ";
 cin>>emp[n].name;
 cout<<"Enter Designation: ";
 cin>>emp[n].designation;
 cout<<"Enter Salary: ";
 cin>>emp[n].salary;
 emp[n].flag = 1;
 index_id[n] = emp[n].id;
 pos[n] = n;
 n++;
 cout<<"Employee Added Successfully\n";
}
void searchEmployee()
{
 int id, found = 0;
 cout<<"Enter Employee ID to search: ";
 cin>>id;
 for(int i=0;i<n;i++)
 {
 if(index_id[i] == id)
 {
 int p = pos[i];
 if(emp[p].flag == 1)
 {
 cout<<"\nEmployee Found\n";
 cout<<"ID: "<<emp[p].id<<endl;
 cout<<"Name: "<<emp[p].name<<endl;
 cout<<"Designation: "<<emp[p].designation<<endl;
 cout<<"Salary: "<<emp[p].salary<<endl;
 }
 else
 {
 cout<<"Employee record deleted\n";
 }
File: /home/student/Desktop/B4 Rusheel/exp5.cpp Page 2 of 2
 found = 1;
break;
 }
 }
 if(found == 0)
 cout<<"Employee does not exist\n";
}
void deleteEmployee()
{
 int id, found = 0;
 cout<<"Enter Employee ID to delete: ";
 cin>>id;
 for(int i=0;i<n;i++)
 {
 if(index_id[i] == id)
 {
 int p = pos[i];
 emp[p].flag = 0;
 cout<<"Employee Deleted\n";
 found = 1;
 break;
 }
 }
 if(found == 0)
 cout<<"Employee does not exist\n";
}
int main()
{
 int choice;
 do
 {
 cout<<"\n1. Add Employee\n";
 cout<<"2. Search Employee\n";
 cout<<"3. Delete Employee\n";
 cout<<"4. Exit\n";
 cout<<"Enter choice: ";
 cin>>choice;
 switch(choice)
 {
 case 1: addEmployee(); break;
 case 2: searchEmployee(); break;
 case 3: deleteEmployee(); break;
 }
 }while(choice != 4);
 return 0;
}
