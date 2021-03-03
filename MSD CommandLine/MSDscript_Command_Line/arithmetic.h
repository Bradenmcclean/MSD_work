//
//  arithmetic.h
//  MSDscript_Command_Line
//
//  Created by Braden McClean on 1/21/21.
//  Copyright © 2021 Braden McClean. All rights reserved.
//

#ifndef arithmetic_h
#define arithmetic_h
#include <iostream>

class Val;
class Expr
{
public:
    typedef enum
    {
    print_group_none,
    print_group_add,
    print_group_mult,
    print_group_let
    } print_mode_t;

    virtual bool equals(Expr *e)=0;
    virtual Val* interp()=0;
    virtual bool has_variable()=0;
    virtual  Expr*  subst (std::string var,Expr* o)=0;
    virtual void print (std::ostream& stream)=0;
   void pretty_print(std::ostream& stream);
    virtual void pretty_print_at(std::ostream& stream,print_mode_t printmode)=0;
    std::string to_String ();
    std::string to_String_pretty ();
};
class BoolExpr:public Expr
{
public:
    bool rep;
    BoolExpr(bool val)
    {
        this->rep=val;
    }
    bool equals(Expr *o);
    Val* interp();
    bool has_variable();
    Expr*  subst (std::string var,Expr* o);
    void print (std::ostream& stream);
    void pretty_print_at(std::ostream& stream,print_mode_t printmode);
    
};
class EqExpr:public Expr
{
public:
    Expr *lhs;
    Expr *rhs;
    EqExpr(Expr *lhs,Expr *rhs)
    {
        this->lhs=lhs;
        this->rhs=rhs;
    }
    bool equals(Expr *o);
    Val* interp();
    bool has_variable();
    Expr*  subst (std::string var,Expr* o);
    void print (std::ostream& stream);
    void pretty_print_at(std::ostream& stream,print_mode_t printmode);
    
};

class NumExpr:public Expr
{
public:
    int rep;
    NumExpr(int val)
    {
        this->rep=val;
    }
    bool equals(Expr *o);
    Val* interp();
    bool has_variable();
    Expr*  subst (std::string var,Expr* o);
    void print (std::ostream& stream);
    void pretty_print_at(std::ostream& stream,print_mode_t printmode);
    
};
class AddExpr:public Expr
{
public:
    Expr *lhs;
    Expr *rhs;
    AddExpr(Expr *lhs,Expr *rhs)
    {
        this->lhs=lhs;
        this->rhs=rhs;
    }
    bool equals(Expr *o);
    Val* interp();
    bool has_variable();
    Expr*  subst (std::string var,Expr* o);
    void print (std::ostream& stream);
    void pretty_print_at(std::ostream& stream,print_mode_t printmode);
    
};
class MultExpr:public Expr
{
public:
    Expr *lhs;
    Expr *rhs;
    MultExpr(Expr *lhs,Expr *rhs)
    {
        this->lhs=lhs;
        this->rhs=rhs;
    }
    bool equals(Expr *o);
    Val* interp();
    bool has_variable();
    Expr*  subst (std::string var,Expr* o);
    void print (std::ostream& stream);
    void pretty_print_at(std::ostream& stream,print_mode_t printmode);
    
};
class VarExpr:public Expr
{
public:
    std::string val;
    VarExpr(std::string val)
    {
        this->val=val;
    }
    bool equals(Expr *o);
    Val* interp();
    bool has_variable();
    Expr*  subst (std::string var,Expr* o);
    void print (std::ostream& stream);
    void pretty_print_at(std::ostream& stream,print_mode_t printmode);
};
class _letExpr:public Expr
{
    public:
    VarExpr *lhs;
    Expr *rhs;
    Expr *body;
    _letExpr(VarExpr *lhs,Expr *rhs,Expr *body)
    {
        this->lhs=lhs;
        this->rhs=rhs;
        this->body=body;
    }
    bool equals(Expr *o);
    Val* interp();
    bool has_variable();
    Expr*  subst (std::string var,Expr* o);
    void print (std::ostream& stream);
    void pretty_print_at(std::ostream& stream,print_mode_t printmode);
    
};
class IfExpr:public Expr
{
    public:
    Expr *_if;
    Expr *_then;
    Expr *_else;
    IfExpr(Expr *_if,Expr *_then,Expr *_else)
    {
        this->_if=_if;
        this->_then=_then;
        this->_else=_else;
    }
    bool equals(Expr *o);
    Val* interp();
    bool has_variable();
    Expr*  subst (std::string var,Expr* o);
    void print (std::ostream& stream);
    void pretty_print_at(std::ostream& stream,print_mode_t printmode);
    
};
#endif /* arithmetic_h */
