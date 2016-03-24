#include <iostream>
#include <string>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

string readLine(int fd)
{
  string line;
  int count; // how many bytes are read
  char buffer[1];
  bool cont = true;
  do{
    // count = 0 means end of file, less means error
    if ( (count=read(fd, &buffer, sizeof(char))) <= 0 ){
      cont = false;
    }else{
      if( buffer[0] != '\n')
        line.push_back(buffer[0]); // appends it to a string
      else cont = false;
    }
  }while(cont);
  
  return line;
}

int main (int argc, char *argv[])
{
  if(argc != 3){
    cout << "dime los archivos de preguntas y respuestas, en este orden" <<endl;
    return 0;
  }
  int fd1, fd2, estado;
  fd1 = open(argv[1] ,O_RDONLY);
  fd2 = open(argv[2] ,O_RDONLY);
  string lin1, lin2;
  lin1 = readLine(fd1);
  lin2 = readLine(fd2);
  cout << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
  cout << "<aiml version=\"2.0\">" << endl;
  for(int i = 1; !lin1.empty() || !lin2.empty(); i++){
    cout << "<!-- Pregunta número: "<< i <<"-->"<<endl;
    cout << "<category>" << endl;
    cout << "\t<pattern>"<< lin1 <<"</pattern>" << endl;
    cout << "\t<template>" << lin2 <<"</template>" << endl;
    cout << "</category>" << endl;
    cout << endl ;
    lin1 = readLine(fd1);
    lin2 = readLine(fd2);
  }
  cout << "</aiml>";
  return 0; 
}         

