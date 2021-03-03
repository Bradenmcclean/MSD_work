//
//  Val.hpp
//  MSDscript_Command_Line
//
//  Created by Braden McClean on 2/24/21.
//  Copyright © 2021 Braden McClean. All rights reserved.
//

#ifndef Val_hpp
#define Val_hpp
class Expr;
class Val
{
public:
    virtual Val* add_to(Val *other_val)=0;
    virtual Val* mult_to(Val *other_val)=0;
    virtual Expr *to_expr() = 0;
    virtual bool equals(Val *o)=0;
    virtual bool is_true() = 0;
};
class NumVal:public Val
{
    public:
    int num;
    NumVal(int num)
    {
          this->num = num;
    }
    Val *add_to(Val *other_val);
    Expr *to_expr();
    Val* mult_to(Val *other_val);
    bool equals(Val *o);
    bool is_true();
};
class BoolVal:public Val
{
    public:
    bool booly;
    BoolVal(bool booly)
    {
          this->booly = booly;
    }
    Val *add_to(Val *other_val);
    Expr *to_expr();
    Val* mult_to(Val *other_val);
    bool equals(Val *o);
     bool is_true();
};
#include <stdio.h>

#endif /* Val_hpp */
