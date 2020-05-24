#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool file_exists(const char* name){
  ifstream read(name);
  return read.good();
}

int menu(){
  int number;cout<<endl;
  cout<<"   1->Adaugati o persoana in cartea de telefoane"<<endl;
  cout<<"   2->Cautati o persoana in cartea de telefoane"<<endl;
  cout<<"   3->Stergeti o persoana din cartea de telefoane"<<endl;
  cout<<"   4->Iesiti"<<endl;
  cout<<endl;
  cout<<"  Introduceti : ";cin>>number;
  return number;
}

void add(){
  system("clear");
  ofstream write;
  if(file_exists("phone.txt"))
    write.open("phone.txt",ios_base::app);
  else if(!file_exists("phone.txt"))
    write.open("phone.txt");
  string nume;
  string prenume;
  string telefon;
  string orasul;
  string virsta;
  cout<<"Introduceti numele : ";cin>>nume;
  cout<<"Introduceti prenumele : ";cin>>prenume;
  cout<<"Introduceti numarul de telefon : ";cin>>telefon;
  cout<<"Introduceti orasul in care locueste : ";cin>>orasul;
  cout<<"Introduceti virsta : ";cin>>virsta;
  write<<"Nume: "<<nume<<endl;
  write<<"Prenume: "<<prenume<<endl;
  write<<"Telefon: "<<telefon<<endl;
  write<<"Orasul: "<<orasul<<endl;
  write<<"Virsta: "<<virsta<<endl;
  write.close();
}

void search(){
  system("clear");
  ifstream read;
  read.open("phone.txt");

  string nume;
  cout<<endl;
  cout<<"Introduceti numele : ";cin>>nume;
  
  int i = 0;//5
  string tip_temp,date_temp;
  bool show = false;
  bool nothing = false;

  while(read>>tip_temp>>date_temp){
    if(date_temp==nume || show){
      show = true;
      nothing = true;
      if(i!=5){
        cout<<date_temp<<" ";
        i++;
        if(i==5){
          i=0;
          show=false;
          cout<<endl;
        }
      }
    }
  }

  if(!nothing)
    cout<<"In cartea de telefoane nu exista informatii despre "<<nume<<endl;
  read.close();

}

void remove(){
  system("clear");
  
  ifstream read;
  read.open("phone.txt");
  ofstream write;
  write.open("temp.txt");

  string temp_nume;
  string temp_prenume;
  string temp_telefon;
  string temp_oras;
  string temp_virsta;

  cout<<"Introduceti numele : ";cin>>temp_nume;
  cout<<"Introduceti prenumele : ";cin>>temp_prenume;

  string temp1,temp2;

  bool first_stage = false;
  bool second_stage = false;
  bool third_stage = false;

  int i = 0;

  int i_temp1; 
  int i_temp2; 
  int stop;

  while(read>>temp1>>temp2){
    if(temp2==temp_nume){
      i_temp1 = i;
      first_stage = true;
    }

    else if(temp2==temp_prenume && i==i_temp1+1){
      second_stage = true;
    }

    else if(first_stage && second_stage){
      third_stage = true;
      i_temp1 = i;
      stop = i_temp1 + 3;
      i_temp2 = i;
      first_stage = false;
      second_stage = false;
    }

    if(third_stage){
      if(i_temp1==stop)
        third_stage=false;
      if(i==i_temp2){
        temp_telefon = temp2;
        i_temp1++;
      }
      if(i==i_temp2+1){
        temp_oras = temp2;
        i_temp1++;
      }
      if(i==i_temp2+2){
        temp_virsta = temp2;
        i_temp1++;
      }
    }

    if(temp2!=temp_nume && temp2!=temp_prenume && !first_stage && !second_stage && !third_stage)
      write<<temp1<<" "<<temp2<<endl;

    i++;
  }

  read.close();
  write.close();

  remove("phone.txt");
  rename("temp.txt", "phone.txt");
}

void back(){
  char read;
  cout<<endl;
  cout<<"Pentru a te intoarce in meniu introduceti orice caracter : ";cin>>read;
}


int main(){
  while(true){
    system("clear");//Daca folositi windows schimbati in "cls"
    int choice = menu();
    if(choice==1){add();}
    else if(choice==2){search();back();}
    else if(choice==3){remove();}
    else if(choice==4){return 0;}
    else if(choice>4){cout<<"Erroare (Ati introdus un numar gresit!)"<<endl;}
  }
}
