//
//  shelpers.cpp
//  Shell project
//
//  Created by Braden McClean on 2/23/21.
//  Copyright © 2021 Braden McClean. All rights reserved.
//

#include "shelpers.hpp"

/*
  text handling functions
 */

bool splitOnSymbol(std::vector<std::string>& words, int i, char c){
  if(words[i].size() < 2){ return false; }
  int pos;
  if((pos = words[i].find(c)) != std::string::npos){
    if(pos == 0){
      //starts with symbol
      words.insert(words.begin() + i + 1, words[i].substr(1, words[i].size() -1));
      words[i] = words[i].substr(0,1);
    } else {
      //symbol in middle or end
      words.insert(words.begin() + i + 1, std::string{c});
      std::string after = words[i].substr(pos + 1, words[i].size() - pos - 1);
      if(!after.empty()){
        words.insert(words.begin() + i + 2, after);
      }
      words[i] = words[i].substr(0, pos);
    }
    return true;
  } else {
    return false;
  }

}

std::vector<std::string> tokenize(const std::string& s){

  std::vector<std::string> ret;
  int pos = 0;
  int space;
  //split on spaces
  while((space = s.find(' ', pos)) != std::string::npos){
    std::string word = s.substr(pos, space - pos);
    if(!word.empty()){
      ret.push_back(word);
    }
    pos = space + 1;
  }

  std::string lastWord = s.substr(pos, s.size() - pos);
  if(!lastWord.empty()){
    ret.push_back(lastWord);
  }

  for(int i = 0; i < ret.size(); ++i){
    for(auto c : {'&', '<', '>', '|'}){
      if(splitOnSymbol(ret, i, c)){
        --i;
        break;
      }
    }
  }
  
  return ret;
  
}


std::ostream& operator<<(std::ostream& outs, const Command& c)
{
  outs << c.exec << " argv: ";
  for(const auto& arg : c.argv)
  { if(arg)
  {outs << arg << ' ';
  }}
  outs << "fds: " << c.fdStdin << ' ' << c.fdStdout << ' ' << (c.background ? "background" : "");
  return outs;
}


std::vector<Command> getCommands(const std::vector<std::string>& tokens){
  std::vector<Command> ret(std::count(tokens.begin(), tokens.end(), "|") + 1);  //1 + num |'s commands

  int first = 0;
  int last = std::find(tokens.begin(), tokens.end(), "|") - tokens.begin();
  bool error = false;
  for(int i = 0; i < ret.size(); ++i)
  {
    if((tokens[first] == "&") || (tokens[first] == "<") ||
        (tokens[first] == ">") || (tokens[first] == "|")){
      error = true;
      break;
    }

    ret[i].exec = tokens[first];
    ret[i].argv.push_back(tokens[first].c_str()); //argv0 = program name
    std::cout << "exec start: " << ret[i].exec << std::endl;
    ret[i].fdStdin = 0;
    ret[i].fdStdout = 1;
    ret[i].background = false;
    
    for(int j = first + 1; j < last; ++j)
    {
      if(tokens[j] == ">" || tokens[j] == "<" )
      {
        //I/O redirection
        if(j+1>=last)
        {
            error=true;
            break;
        }
        if (tokens[j]=="<")
        {
            if (i!=0)
            {
                error=true;
               
                break;
            }
            ret[i].fdStdin=open(tokens[j+1].c_str(),O_RDONLY);
            if (ret[i].fdStdin==-1)
            {
                perror("Input Redirection Error");
                error=true;
                break;
            }
        }else
        {
            if (i!=ret.size()-1)
            {
                error=true;
                break;
            }
            ret[i].fdStdout=open(tokens[j+1].c_str(),O_CREAT);
            if(ret[i].fdStdout==-1)
            {
                perror("Output Redirection Error");
                error=true;
                break;
            }
        }
    
      }else if(tokens[j] == "&")
      {
          //for background usuage
          ret[i].background=true;
          if (i!=ret.size()-1)
          {
              error=true;
              break;
          }
          
      } else
      {
        ret[i].argv.push_back(tokens[j].c_str());
      }
      
    }
    if(i > 0)
    {
        //for making pipes
        int myPipe[2];
        if (pipe(myPipe)<0)
        {
            perror("Error PipeMaking");
            error=true;
            break;
        }
        ret[i].fdStdin=myPipe[0];

        ret[i-1].fdStdout=myPipe[1];

    }
    ret[i].argv.push_back(nullptr);

    first = last + 1;
    if(first < tokens.size())
    {
      last = std::find(tokens.begin() + first, tokens.end(), "|") - tokens.begin();
    }
  }

  if(error)
  {
      //close all the pipes in ret if there is a error
      for (int i=0; i<ret.size();i++)
      {
        if(close(ret[i].fdStdin)==-1)
        {
            perror("close of fdStdin in Ret");
        }
        if(close(ret[i].fdStdout)==-1)
        {
          perror("close of fdStdin in Ret");
        }
      }
      //closes program
    assert(false);
    
  }
  
  return ret;
}
