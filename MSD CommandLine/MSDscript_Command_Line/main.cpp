//
//  main.cpp
//  MSDscript_Command_Line
//
//  Created by Braden McClean on 1/20/21.
//  Copyright © 2021 Braden McClean. All rights reserved.
//

#include <iostream>
#include "functions.hpp"
#include "Catch.h"
#include "arithmetic.h"
#include "parse.hpp"
int main(int argc,char**argv)
{
//  while (1)
//  {
//    Expr *e = parse_expr(std::cin);
//    e->pretty_print(std::cout);
//    std::cout << "\n";
//    skip_whitespace(std::cin);
//    if (std::cin.eof())
//    break;
//    }
    try {
     use_arguments(argc, argv);
      return 0;
    } catch (std::runtime_error exn)
    {
      std::cerr << exn.what() << "\n";
      return 1;
    }
    
    return 0;
}
