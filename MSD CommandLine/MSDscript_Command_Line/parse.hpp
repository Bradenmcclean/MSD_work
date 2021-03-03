//
//  parse.hpp
//  MSDscript_Command_Line
//
//  Created by Braden McClean on 2/14/21.
//  Copyright © 2021 Braden McClean. All rights reserved.
//

#ifndef parse_hpp
#define parse_hpp
#include "arithmetic.h"
#include <sstream>

#include <stdio.h>
Expr *parse_addend(std::istream &in);
Expr *parse_num(std::istream &in);
Expr *parse_expr(std::istream &in);
void skip_whitespace(std::istream &in);
Expr * parse_multicand(std::istream &in);
Expr *parse_let(std::istream &in);
Expr *parse_if(std::istream &in);
Expr *parse_comparg(std::istream &in);
#endif /* parse_hpp */
