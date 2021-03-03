//
//  functions.cpp
//  MSDscript_Command_Line
//
//  Created by Braden McClean on 1/20/21.
//  Copyright © 2021 Braden McClean. All rights reserved.
//

#include "functions.hpp"
#define CATCH_CONFIG_RUNNER
#include "Catch.h"
#include "arithmetic.h"
#include "parse.hpp"
void use_arguments (int argc,char* argv[])
{
   
  
    std::string argument=argv[1];
    if (argument=="--help")
    {
        std::cout<< "The Only Allowed Argument Is --test,--interp,--print,--pretty-print \n";
        exit(0);
    }
    else if (argument=="--test")
    {
     
        if (Catch::Session().run(1,argv)!=0)
        {
            exit(1);
        }else
        {
           exit(0);
        }
        
    }else if (argument=="--interp")
    {
     
      Expr *e = parse_expr(std::cin);
      std::cout <<e->interp();
        std::cout << "\n";
      exit(0);
        
    }else if (argument=="--print")
    {
     
      Expr *e = parse_expr(std::cin);
        
        std::cout<<e->to_String();
        std::cout << "\n";
      exit(0);
        
    }else if (argument=="--pretty-print")
    {
        
      Expr *e = parse_expr(std::cin);
        
        std::cout<<e->to_String_pretty();
        std::cout << "\n";
      exit(0);
        
    }else
    {
        std::cerr <<argument<<" Is An Improper Command \n";
        exit(1);
    }
}
   


