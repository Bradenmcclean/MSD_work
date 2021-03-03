//
//  main.cpp
//  Shell project
//
//  Created by Braden McClean on 2/23/21.
//  Copyright © 2021 Braden McClean. All rights reserved.
//

#include <iostream>
#include "shelpers.hpp"
#include <map>
#include <readline/readline.h>
int main(int argc, const char * argv[]) {
//    std::string input =argv[1];
    std::string arg;
    std::map <std::string ,const char*> variableHolder;
    while(std::getline(std::cin,arg))
    {
    std::vector<std::string>  token =tokenize(arg);
    std::vector<Command>  commands =getCommands(token);
    std::vector <int> pinIDs;
    
    for(Command c:commands)
    {
        std::cout<<c<<std::endl;
    }
    for (int i=0;i<commands.size();i++)
    {
        Command com=commands[i];
        int pID=fork();
        if (pID==-1)
        {
            perror("fork error");
        }else if(pID==0)
        {
            if ((com.fdStdin)!=0)
            {
                if(dup2(com.fdStdin, 0)==-1)
                {
                    perror("Dup2 of stdin in child");
                }
            }
            if ((com.fdStdout)!=0)
            {
                if(dup2(com.fdStdout, 0)==-1)
                {
                    perror("Dup2 of fdStdout in child");
                }
            }
            //Stand in for CD
            if (com.exec=="cd")
            {
                if (com.argv[1]!=NULL)
                {
                    if (chdir(com.argv[1])==-1)
                    {
                        perror("chdir error with argument");
                    }
                }else
                {
                    if (chdir(getenv("HOME"))==-1)
                    {
                        perror("chdir error with $HOME");
                    }
                }
                
            //Stand in for setenv
            }else if(com.exec=="setenv")
            {
                
                if (com.argv[1]==NULL)
                {
                    std::map<std::string , const char*>::iterator it = variableHolder.begin();
                      while (it != variableHolder.end())
                      {
                          std::string  variable = it->first;
                          const char*  whatItReps = it->second;
                          std::cout << variable << " :: " << whatItReps << std::endl;
                          it++;
                      }
                }else
                {
                    std::string temp=com.argv[1];
                    variableHolder[temp] = com.argv[2];
                }
                //Stand in for bash
            }else if (com.exec=="bash")
            {
                variableHolder.clear();
                std::cout << "All Varibles Have been Deleted"<< std::endl;
            }else
            {
              //for variable switch if in the map
                std::string temp=com.argv[1];

                if (variableHolder.count(temp)==1)
                {
                    com.argv[1]=variableHolder[temp];
                }
                
                if (execvp(com.exec.c_str(), const_cast<char* const*> (com.argv.data()))==-1)
                {
                    perror("execvp failure in child");
                }
            }
            
        }else
        {
            if ((com.fdStdin)!=0)
            {
                if(close(com.fdStdin)==-1)
                {
                    perror("close of fdStdin Parent");
                }
            }
            if ((com.fdStdout)!=1)
            {
                if(close(com.fdStdout)==-1)
                {
                    perror("close of fdStdout Parent");
                }
            }
            if (i==commands.size()-1)
            {
                if (com.background)
                {
                    pinIDs.push_back(pID);
                }else
                {
                    std::cout<<pID<<" is still running"<<std::endl;
                    if(waitpid(pID, nullptr, 0)==-1)
                    {
                        perror("Waitpid Error");
                    }
                    
                }
            }
            
        }
        
        
    }
    }
    
    return 0;
}
