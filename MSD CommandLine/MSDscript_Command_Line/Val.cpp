//
//  Val.cpp
//  MSDscript_Command_Line
//
//  Created by Braden McClean on 2/24/21.
//  Copyright © 2021 Braden McClean. All rights reserved.
//

#include "Val.hpp"
#include "arithmetic.h"
bool NumVal::equals(Val *o)
{
    NumVal *c = dynamic_cast<NumVal*>(o);
    if (c==NULL)
    {
        return false;
    }
    else
        return (this->num==c->num);
};
Val *NumVal::add_to(Val *other_val)
{
 NumVal *other_num = dynamic_cast<NumVal*>(other_val);
 if (other_num == NULL)
 {
     throw std::runtime_error("add of non-number");
 }
 return new NumVal(num + other_num->num);
}
Val *NumVal::mult_to(Val *other_val)
{
 NumVal *other_num = dynamic_cast<NumVal*>(other_val);
 if (other_num == NULL)
 {
     throw std::runtime_error("mult of non-number");
 }
 return new NumVal(num * other_num->num);
}
Expr *NumVal::to_expr()
{
    return new NumExpr(num);
}

 bool NumVal::is_true()
{
    throw std::runtime_error("If of a Non Boolean Statement");
}

 bool BoolVal::is_true()
{
    return this->booly;
}

Val *BoolVal::add_to(Val *other_val)
{
 throw std::runtime_error("add of non-number");
}
Val *BoolVal::mult_to(Val *other_val)
{
 throw std::runtime_error("mult of non-number");
}
 bool BoolVal::equals(Val *o)
{
    BoolVal *c = dynamic_cast<BoolVal*>(o);
    if (c==NULL)
    {
        return false;
    }
    else
        return (this->booly==c->booly);
}
 Expr *BoolVal::to_expr()
{
    return new BoolExpr(this->booly);
}
