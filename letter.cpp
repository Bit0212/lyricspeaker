#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <filesystem>
#include <fstream>

int main(int argc, char* argv[]){
  namespace file = std::filesystem;
  std::string dummy{};
  int LineDuration{};
  std::cout<<"Please enter a duration between lines(milliseconds)\n";
  if (!(std::cin>>LineDuration) || LineDuration<0){
    std::cerr<<"fallo en lectura jeje\n";
  }
  if(LineDuration ==0){
goto rest;
  }
rest:
  if (argc>1){
dummy = argv[1];
file::path DirectoryFile = dummy;
std::ifstream FileOpener(DirectoryFile);
if(!FileOpener.is_open()){
  std::cerr<<"Something failed here hehe\n";
  return 1;
}
auto ExecutionLine = [&FileOpener](int duration){

std::string ActualLine{};
while(std::getline(FileOpener,ActualLine)){
  std::cout<<ActualLine<<"\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(duration));

}
return;
  };
ExecutionLine(LineDuration);


}

  else{
    std::cerr<<"this shouldn't have been here \n";
    return 1;

  }

return 0;
}
