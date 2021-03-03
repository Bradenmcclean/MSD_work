//
//  randomTestGen.cpp
//  MSDscript_Command_Line
//
//  Created by Braden McClean on 2/21/21.
//  Copyright © 2021 Braden McClean. All rights reserved.
//
#include <iostream>
#include <stdlib.h>
#include "randomTestGen.hpp"
#include "exec.hpp"

std::string random_expr_string()
{
    
 if ((rand() % 10) < 9)
 {
     return std::to_string(rand());
 }else if ((rand() % 10) < 8)
 {
     return random_expr_string() + "==" + random_expr_string();;
 }
 else if ((rand() % 10) < 7)
{
    return "_false";
}
 else if ((rand() % 10) < 6)
 {
     return random_expr_string() + "*" + random_expr_string();;
 }else if ((rand() % 10) < 4)
 {
     return "_let"+random_expr_string() +"="+random_expr_string()+ "_in" + random_expr_string();;
 }else if ((rand() % 10) < 3)
 {
     return "_true";
 }else if ((rand() % 10) < 2)
 {  char s =rand();
     return std::to_string(s);
 }else if ((rand() % 10) < 10)
 {
     return "_if"+random_expr_string() +"_then"+random_expr_string()+ "_else" + random_expr_string();;
 }else
 {
 return random_expr_string() + "+" + random_expr_string();
 }
}

//int main(int argc, char **argv)
//{
// const char * const interp1_argv[] = { argv[1], "--interp" };
// const char * const interp2_argv[] = { argv[2], "--interp" };
// for (int i = 0; i < 100; i++) {
// std::string in = random_expr_string();
// std::cout << "Trying " << in << "\n";
// ExecResult interp1_result = exec_program(2, interp1_argv, in);
// ExecResult interp2_result = exec_program(2, interp2_argv, in);
//   std::cout << "result yours " << interp1_result.out << "\n";
//     std::cout << "result theirs " << interp2_result.out << "\n";
// if (interp1_result.out != interp2_result.out)
// throw std::runtime_error("different results");
// }
//const char * const interp3_argv[] = { argv[1], "--print" };
//const char * const interp4_argv[] = { argv[2], "--print" };
//for (int i = 0; i < 100; i++) {
//std::string in = random_expr_string();
//std::cout << "Trying " << in << "\n";
//ExecResult interp3_result = exec_program(2, interp3_argv, in);
//ExecResult interp4_result = exec_program(2, interp4_argv, in);
//std::cout << "result yours --" << interp3_result.out << "\n";
//std::cout << "result theirs " << interp4_result.out << "\n";
//if (interp3_result.out != interp4_result.out)
//throw std::runtime_error("different results");
//}
//const char * const interp5_argv[] = { argv[1], "--pretty-print" };
//const char * const interp6_argv[] = { argv[2], "--pretty-print" };
//for (int i = 0; i < 100; i++) {
//std::string in = random_expr_string();
//std::cout << "Trying " << in << "\n";
//ExecResult interp5_result = exec_program(2, interp5_argv, in);
//ExecResult interp6_result = exec_program(2, interp6_argv, in);
//std::cout << "result yours --" << interp5_result.out << "\n";
//std::cout << "result theirs " << interp6_result.out << "\n";
//if (interp5_result.out != interp6_result.out)
//throw std::runtime_error("different results");
//}
// return 0;
//}
