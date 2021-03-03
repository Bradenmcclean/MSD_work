//
//  exec.hpp
//  MSDscript_Command_Line
//
//  Created by Braden McClean on 2/21/21.
//  Copyright © 2021 Braden McClean. All rights reserved.
//

#ifndef exec_hpp
#define exec_hpp

#include <string>

class ExecResult {
public:
  int exit_code;
  std::string out;
  std::string err;
  ExecResult() {
    exit_code = 0;
    out = "";
    err = "";
  }
};

extern ExecResult exec_program(int argc, const char * const *argv, std::string input);

#endif /* exec_hpp */
