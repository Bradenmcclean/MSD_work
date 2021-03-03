//
//  arithmetic.cpp
//  MSDscript_Command_Line
//
//  Created by Braden McClean on 1/21/21.
//  Copyright © 2021 Braden McClean. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "arithmetic.h"
#include "Catch.h"
#include <stdexcept>
#include <sstream>
#include "Val.hpp"
std::string Expr::to_String ()
{
    std::stringstream out(" ");
    
    this->print(out);
    
    return out.str();
}
std::string Expr::to_String_pretty ()
{
    std::stringstream out(" ");
    
    this->pretty_print(out);
    
    return out.str();
}

bool BoolExpr::equals(Expr *o)
{
    BoolExpr *c = dynamic_cast<BoolExpr*>(o);
       if (c==NULL)
       {
           return false;
       }
       else
           return (this->rep==c->rep);
}
Val* BoolExpr::interp()
{
     return new BoolVal(rep);
}
bool BoolExpr::has_variable()
{
    return false;
}
Expr*  BoolExpr::subst (std::string var,Expr* o)
{
     return this;
}
void BoolExpr::print (std::ostream& stream)
{
    if (this->rep)
        stream<<"_true";
    else
        stream<<"_false";
}
void BoolExpr::pretty_print_at(std::ostream& stream,print_mode_t printmode)
{
    if (this->rep)
        stream<<"_true";
    else
        stream<<"_false";
}

void Expr::pretty_print(std::ostream& stream)
{
    print_mode_t printmode=print_group_none;
    this->pretty_print_at(stream, printmode);
}
bool IfExpr::equals(Expr *o)
{
    IfExpr *c = dynamic_cast<IfExpr*>(o);
    if (c==NULL)
    {
        return false;
    }
    else
    {
        return ((this->_if->equals(c->_if))&&(this->_then->equals(c->_then))&&(this->_else->equals(c->_else)));
    }
}
Val *IfExpr::interp()
{
    if (_if->interp()->is_true())
    return _then->interp();
    else
    return _else->interp();
}
bool IfExpr::has_variable()
{
    return (_if->has_variable()|_then->has_variable()|_else->has_variable());
}
Expr* IfExpr::subst (std::string var,Expr* o)
{
    Expr* ifNew=_if->subst(var, o);
    Expr* thenNew=_then->subst(var, o);
    Expr* elseNew=_else->subst(var, o);
    return new IfExpr(ifNew,thenNew,elseNew);
    
}
void IfExpr::print (std::ostream& stream)
{
        stream.put('(');
        stream<<"_if ";
        _if->print(stream);
        stream<<" _then ";
        _then->print(stream);
        stream<<" _else ";
        _else->print(stream);
        stream.put(')');
}
void IfExpr::pretty_print_at(std::ostream& stream,print_mode_t printmode)
{
     long long pos=stream.tellp();
        if (printmode==print_group_none)
          {
              print_mode_t print=print_group_let;
              print_mode_t print1=print_group_none;
              
              stream<<"_if  ";
              _if->pretty_print_at(stream,print1);
              stream<<"\n";
              for (int i=0;i<pos;i++)
              {
                stream.put(' ');
              }
              stream<<"_then ";
              _then->pretty_print_at(stream,print);
               stream<<"\n";
              for (int i=0;i<pos;i++)
              {
                stream.put(' ');
              }
              stream<<"_else ";
              _else->pretty_print_at(stream,print);
              
          }
        else if(printmode==print_group_let)
        {
            print_mode_t print=print_group_let;
            print_mode_t print1=print_group_none;
            stream.put('(');
            stream<<"_if  ";
            _if->pretty_print_at(stream,print1);
            stream<<"\n";
            for (int i=0;i<7;i++)
            {
              stream.put(' ');
            }
            stream<<"_then ";
            _then->pretty_print_at(stream,print);
             stream<<"\n";
            for (int i=0;i<7;i++)
            {
              stream.put(' ');
            }
            stream<<"_else ";
            _else->pretty_print_at(stream,print);
            stream.put(')');
            
        }
        else
          {
               print_mode_t print=print_group_let;
               print_mode_t print1=print_group_none;
               stream.put('(');
              stream<<"_if  ";
               _if->pretty_print_at(stream,print1);
              stream<<"\n";
               for (int i=0;i<pos;i++)
               {
                 stream.put(' ');
               }
               stream<<"_then ";
               _then->pretty_print_at(stream,print);
                stream<<"\n";
               for (int i=0;i<pos;i++)
               {
                 stream.put(' ');
               }
               stream<<"_else ";
               _else->pretty_print_at(stream,print);
               stream.put(')');
          }
}
bool _letExpr::equals(Expr *o)
{
    _letExpr *c = dynamic_cast<_letExpr*>(o);
       if (c==NULL)
       {
           return false;
       }
       else
       {
           return ((this->lhs->equals(c->lhs))&&(this->rhs->equals(c->rhs))&&(this->body->equals(c->body)));
       }
    
}
bool _letExpr::has_variable()
{
    return (rhs->has_variable()|body->has_variable());
}
Val *_letExpr::interp()
{
 Val *rhs_val = rhs->interp();
 return body->subst(lhs->val, rhs_val->to_expr())->interp();
}
 Expr* _letExpr::subst (std::string var,Expr* o)
{
    Expr* rhsNew=rhs->subst(var, o);
    Expr* bodyNew=body->subst(var, o);
    if (var==this->lhs->val)
    {
        return new _letExpr(this->lhs,rhsNew,this->body);
    }
    return new _letExpr(this->lhs,rhsNew,bodyNew);
        
};
void _letExpr::print (std::ostream& stream)
{
    stream.put('(');
    stream.put('_');
    stream.put('l');
    stream.put('e');
    stream.put('t');
    stream.put(' ');
    lhs->print(stream);
    stream.put('=');
    rhs->print(stream);
    stream.put(' ');
    stream.put('_');
    stream.put('i');
    stream.put('n');
    stream.put(' ');
    body->print(stream);
    stream.put(')');
    
};
void _letExpr::pretty_print_at(std::ostream& stream,print_mode_t printmode)
{
    long long pos=stream.tellp();
     if (printmode==print_group_none)
       {
           print_mode_t print=print_group_let;
           print_mode_t print1=print_group_none;
           
           stream<<"_let ";
           lhs->pretty_print_at(stream,print1);
           stream<<" = ";
           rhs->pretty_print_at(stream,print1);
            stream<<"\n";
           for (int i=0;i<pos;i++)
           {
             stream.put(' ');
           }
           stream.put('_');
           stream.put('i');
           stream.put('n');
           stream.put(' ');
           stream.put(' ');
           body->pretty_print_at(stream,print);
           
       }
     else if(printmode==print_group_let)
     {
         print_mode_t print=print_group_let;
         print_mode_t print1=print_group_none;
         stream.put('(');
         stream<<"_let ";
         lhs->pretty_print_at(stream,print1);
         stream<<" = ";
         rhs->pretty_print_at(stream,print1);
          stream<<"\n";
         for (int i=0;i<6;i++)
         {
         stream.put(' ');
         }
         stream.put('_');
         stream.put('i');
         stream.put('n');
         stream.put(' ');
         stream.put(' ');
         body->pretty_print_at(stream,print);
         stream.put(')');
         
     }
     else
       {
            print_mode_t print=print_group_let;
            print_mode_t print1=print_group_none;
            stream.put('(');
            stream<<"_let ";
            lhs->pretty_print_at(stream,print1);
            stream<<" = ";
            rhs->pretty_print_at(stream,print1);
             stream<<"\n";
            for (int i=0;i<pos+1;i++)
            {
            stream.put(' ');
            }
            stream.put('_');
            stream.put('i');
            stream.put('n');
            stream.put(' ');
            stream.put(' ');
            body->pretty_print_at(stream,print);
            stream.put(')');
       }

};
bool NumExpr::equals(Expr *o)
{
    NumExpr *c = dynamic_cast<NumExpr*>(o);
    if (c==NULL)
    {
        return false;
    }
    else
        return (this->rep==c->rep);
};
Val * NumExpr::interp()
{
    return new NumVal(rep);
}
bool NumExpr::has_variable()
{
   return false;
}
Expr* NumExpr::subst (std::string var,Expr* o)
{
    return this;
}

void NumExpr::print (std::ostream& stream)
{
    stream<<this->rep;
}
void NumExpr::pretty_print_at(std::ostream& stream,print_mode_t printmode)
{
     stream<<this->rep;
}
bool EqExpr::equals(Expr *o)
{
    EqExpr *c = dynamic_cast<EqExpr*>(o);
      if (c==NULL)
      {
          return false;
      }
      else
      {
          return ((this->lhs->equals(c->lhs))&&(this->rhs->equals(c->rhs)));
      }
}
  Val* EqExpr::interp()
{
    return new BoolVal(lhs->interp()
     ->equals(rhs->interp()));
    
}
  bool EqExpr::has_variable()
{
    if (lhs->has_variable()|rhs->has_variable())
    {
      return true;
    }else
    {
      return false;
    }
};
  Expr*  EqExpr::subst (std::string var,Expr* o)
{
    Expr* lhsNew=lhs->subst(var, o);
    Expr* rhsNew=rhs->subst(var, o);
    return new EqExpr(lhsNew,rhsNew);
};
  void EqExpr::print (std::ostream& stream)
{
        stream<<"(";
        lhs->print(stream);
        stream<<"==";
        rhs->print(stream);
        stream<<")";
};
  void EqExpr::pretty_print_at(std::ostream& stream,print_mode_t printmode)
{
    if (printmode==print_group_none|printmode==print_group_let)
    {
        print_mode_t print=print_group_add;
        print_mode_t print1=print_group_none;
        lhs->pretty_print_at(stream,print);
        stream.put(' ');
        stream.put('=');
        stream.put('=');
        stream.put(' ');
        rhs->pretty_print_at(stream,print1);
        
    }else
    {
        print_mode_t print=print_group_add;
        print_mode_t print1=print_group_none;
        stream.put('(');
        lhs->pretty_print_at(stream,print);
        stream.put(' ');
        stream.put('=');
        stream.put('=');
        stream.put(' ');
        rhs->pretty_print_at(stream,print1);
        stream.put(')');
    }
}
bool AddExpr::equals(Expr *o)
{
    AddExpr *c = dynamic_cast<AddExpr*>(o);
    if (c==NULL)
    {
        return false;
    }
    else
    {
        return ((this->lhs->equals(c->lhs))&&(this->rhs->equals(c->rhs)));
    }
        
};
Val *AddExpr::interp()
{
 return lhs->interp()
 ->add_to(rhs->interp());
}
bool AddExpr::has_variable()
{
    if (lhs->has_variable()|rhs->has_variable())
   {
       return true;
   }else
   {
       return false;
   }
};
 Expr* AddExpr::subst (std::string var,Expr* o)
{
     Expr* lhsNew=lhs->subst(var, o);
           
 
     Expr* rhsNew=rhs->subst(var, o);
  
    return new AddExpr(lhsNew,rhsNew);
       
    
}
void AddExpr::print (std::ostream& stream)
{
    stream.put('(');
    lhs->print(stream);
    stream.put('+');
    rhs->print(stream);
    stream.put(')');
    
}
//typedef enum {
//  print_group_none,
//  print_group_add,
//  print_group_mult
//print_group_let
//} print_mode_t;
void AddExpr::pretty_print_at(std::ostream& stream,print_mode_t printmode)
{
    if (printmode==print_group_none|printmode==print_group_let)
    {
        print_mode_t print=print_group_add;
        print_mode_t print1=print_group_none;
        lhs->pretty_print_at(stream,print);
        stream.put(' ');
        stream.put('+');
        stream.put(' ');
        rhs->pretty_print_at(stream,print1);
        
    }else
    {
        print_mode_t print=print_group_add;
        print_mode_t print1=print_group_none;
        stream.put('(');
        lhs->pretty_print_at(stream,print);
        stream.put(' ');
        stream.put('+');
        stream.put(' ');
        rhs->pretty_print_at(stream,print1);
        stream.put(')');
    }
    
}

bool MultExpr::equals(Expr* o)
{
    MultExpr *c = dynamic_cast<MultExpr*>(o);
    if (c==NULL)
    {
        return false;
    }
    else
    {
        return((this->lhs->equals(c->lhs))&&(this->rhs->equals(c->rhs)));
    }
};
Val *MultExpr::interp()
{
 return lhs->interp()
 ->mult_to(rhs->interp());
}
bool MultExpr::has_variable()
{
    if (lhs->has_variable()|rhs->has_variable())
   {
       return true;
   }else
   {
       return false;
   }
};
 Expr* MultExpr::subst (std::string var,Expr* o)
{
        Expr* lhsNew=lhs->subst(var, o);
              
    
        Expr* rhsNew=rhs->subst(var, o);
     
       return new MultExpr(lhsNew,rhsNew);
    
    
}
void MultExpr::print (std::ostream& stream)
{
        stream.put('(');
        lhs->print(stream);
        stream.put('*');
        rhs->print(stream);
        stream.put(')');
    
};
void MultExpr::pretty_print_at(std::ostream& stream,print_mode_t printmode)
{
    if (printmode==print_group_none|printmode==print_group_let)
    {
        print_mode_t print=print_group_mult;
        print_mode_t print1=print_group_none;
        lhs->pretty_print_at(stream,print);
        stream.put(' ');
        stream.put('*');
        stream.put(' ');
        rhs->pretty_print_at(stream,print1);
        
    }else if(printmode==print_group_add)
    {
        print_mode_t print=print_group_mult;
        print_mode_t print1=print_group_none;
        stream.put('(');
        lhs->pretty_print_at(stream,print);
        stream.put(' ');
        stream.put('*');
        stream.put(' ');
        rhs->pretty_print_at(stream,print1);
        stream.put(')');
    }else
    {
        print_mode_t print=print_group_mult;
        print_mode_t print1=print_group_none;
        stream.put('(');
        lhs->pretty_print_at(stream,print);
        stream.put(' ');
        stream.put('*');
        stream.put(' ');
        rhs->pretty_print_at(stream,print1);
        stream.put(')');
    }
}
bool VarExpr::equals(Expr *o)
{
    VarExpr *c = dynamic_cast<VarExpr*>(o);
    if (c==NULL)
    {
        return false;
    }
    else
        return (this->val==c->val);
};
Val* VarExpr::interp()
{
    throw std::runtime_error("Var can not be interperated");
};
bool VarExpr::has_variable()
{
    return true;
};
Expr* VarExpr::subst (std::string var,Expr* o)
{
    if (var==this->val)
    {
        return o;
    }else
    {
        return this;
    }
};
void VarExpr::print (std::ostream& stream)
{
    stream<<this->val;
};
void VarExpr::pretty_print_at(std::ostream& stream,print_mode_t printmode)
{
    stream<<this->val;
}

TEST_CASE("equals")
{
   
    Expr* a=new NumExpr(1);
    Expr* b=new NumExpr(1);
    Expr* c=new NumExpr(2);
    CHECK(a->equals(b));
    CHECK(!(a->equals(c)));
    Expr* e=new AddExpr(new NumExpr(1),new NumExpr(2));
    Expr* f=new AddExpr(new NumExpr(1),new NumExpr(1));
    Expr* g=new AddExpr(new NumExpr(1),new NumExpr(1));
    CHECK(!(a->equals(e)));
    CHECK(f->equals(g));
    CHECK(!(e->equals(f)));
    Expr* h=new MultExpr(new NumExpr(1),new NumExpr(4));
    Expr* i=new MultExpr(new NumExpr(3),new NumExpr(4));
    Expr* j=new MultExpr(new NumExpr(1),new NumExpr(4));
    CHECK(!(e->equals(h)));
    CHECK(!(h->equals(e)));
    CHECK(h->equals(j));
    CHECK(!(i->equals(j)));
    Expr* k=new VarExpr("a");
    Expr* l=new VarExpr("a");
    Expr* m=new VarExpr("d");
    CHECK(!(k->equals(e)));
    CHECK(k->equals(l));
    CHECK(!(k->equals(m)));
    Expr* n=new _letExpr(new VarExpr("x"),new NumExpr(5),new AddExpr(new VarExpr ("x"), new NumExpr(3)));
    Expr* o=new _letExpr(new VarExpr("x"),new NumExpr(5),new AddExpr(new VarExpr ("x"), new NumExpr(3)));
    Expr* p=new _letExpr(new VarExpr("y"),new NumExpr(5),new AddExpr(new VarExpr ("x"), new NumExpr(3)));
    CHECK(o->equals(n));
    CHECK(!(o->equals(p)));
    CHECK(!(p->equals(e)));
    Expr* q=new IfExpr(new VarExpr("x"),new NumExpr(5),new AddExpr(new VarExpr ("x"), new NumExpr(3)));
    Expr* r=new IfExpr(new VarExpr("x"),new NumExpr(5),new AddExpr(new VarExpr ("x"), new NumExpr(3)));
    Expr* s=new IfExpr(new VarExpr("y"),new NumExpr(5),new AddExpr(new VarExpr ("x"), new NumExpr(3)));
    CHECK(q->equals(r));
    CHECK(!(r->equals(s)));
    CHECK(!(s->equals(r)));
    Expr* t=new EqExpr(new NumExpr(5),new NumExpr(1));
    Expr* u=new EqExpr(new BoolExpr(false),new BoolExpr(true));
    Expr* v=new EqExpr(new NumExpr(5),new NumExpr(1));
    CHECK(!(t->equals(u)));
    CHECK(t->equals(v));
    CHECK(!(u->equals(v)));
    Expr* w=new BoolExpr(false);
    Expr* x=new BoolExpr(true);
    Expr* y=new BoolExpr(true);
    CHECK(x->equals(y));
    CHECK(!(w->equals(x)));
}
TEST_CASE("VarBool")
{
    Expr* a=new NumExpr(1);
    CHECK(!(a->has_variable()));
    Expr* x=new VarExpr("a");
    CHECK((x->has_variable()));
    Expr* h=new MultExpr(new NumExpr(1),new NumExpr(4));
    Expr* i=new MultExpr(new VarExpr("a"),new NumExpr(4));
    Expr* j=new MultExpr((new AddExpr(new VarExpr("A"),new NumExpr(4))),new NumExpr(4));
    CHECK(!(h->has_variable()));
    CHECK((i->has_variable()));
    CHECK((j->has_variable()));
    Expr* k=new AddExpr(new NumExpr(1),new NumExpr(4));
    Expr* l=new AddExpr(new VarExpr("a"),new NumExpr(4));
    Expr* m=new AddExpr((new AddExpr(new VarExpr("A"),new NumExpr(4))),new NumExpr(4));
    CHECK(!(k->has_variable()));
    CHECK((l->has_variable()));
    CHECK((m->has_variable()));
    Expr* n=new _letExpr(new VarExpr("x"),new NumExpr(5),new AddExpr(new VarExpr ("x"), new NumExpr(3)));
    Expr* o=new _letExpr(new VarExpr("x"),new NumExpr(5),new AddExpr(new NumExpr(3), new NumExpr(3)));
    Expr* p=new _letExpr(new VarExpr("y"),new NumExpr(5),new AddExpr(new VarExpr ("x"), new NumExpr(3)));
    CHECK((n->has_variable()));
    CHECK(!(o->has_variable()));
    CHECK((p->has_variable()));
    Expr* t=new EqExpr(new VarExpr("c"),new NumExpr(1));
    Expr* u=new EqExpr(new BoolExpr(false),new BoolExpr(true));
    Expr* v=new EqExpr(new NumExpr(5),new NumExpr(1));
    CHECK((t->has_variable()));
    CHECK(!(u->has_variable()));
    CHECK(!(v->has_variable()));
    Expr* w=new BoolExpr(false);
    Expr* y=new BoolExpr(true);
    CHECK(!(w->has_variable()));
    CHECK(!(y->has_variable()));
    
    
}
TEST_CASE("Interp")
{
    Expr* a=new NumExpr(1);
    CHECK(a->interp()->equals(new NumVal(1)));
    Expr* e=new AddExpr(new NumExpr(1),new NumExpr(2));
    Expr* f=new AddExpr(new NumExpr(1),new NumExpr(1));
    CHECK(e->interp()->equals(new NumVal(3)));
    CHECK((f->interp()->equals(new NumVal(2))));
    Expr* h=new MultExpr(new NumExpr(1),new NumExpr(4));
    Expr* i=new MultExpr(new NumExpr(3),new NumExpr(4));
    Expr* j=new MultExpr(new NumExpr(1),new NumExpr(4));
    CHECK(h->interp()->equals(new NumVal(4)));
    CHECK((i->interp()->equals(new NumVal(12))));
    CHECK(!(j->interp()->equals(new NumVal(7))));
    Expr* t=new EqExpr(new NumExpr(1),new NumExpr(1));
    Expr* u=new EqExpr(new BoolExpr(false),new BoolExpr(true));
    Expr* v=new EqExpr(new NumExpr(5),new NumExpr(5));
    CHECK((t->interp()->equals(new BoolVal(true))));
    CHECK((u->interp()->equals(new BoolVal(false))));
    CHECK((v->interp()->equals(new BoolVal(true))));
    CHECK_THROWS_WITH( (new VarExpr("x"))->interp(), "Var can not be interperated" );
    Expr* n=new _letExpr(new VarExpr("x"),new NumExpr(5),new AddExpr(new VarExpr ("x"), new NumExpr(3)));
    Expr* o=new _letExpr(new VarExpr("x"),new NumExpr(5),new AddExpr(new NumExpr(3), new NumExpr(3)));
    Expr* p=new _letExpr(new VarExpr("y"),new NumExpr(5),new AddExpr(new VarExpr ("x"), new NumExpr(3)));
    Expr* q=new _letExpr(new VarExpr("x"),new MultExpr(new NumExpr (3),new NumExpr(5)),new AddExpr(new VarExpr ("x"), new NumExpr(3)));
    Expr* r=new _letExpr(new VarExpr("x"),new MultExpr(new NumExpr (3),new NumExpr(5)),new _letExpr(new VarExpr ("x"), new NumExpr(3),new AddExpr(new VarExpr("x"),new NumExpr(2))));
    CHECK((n->interp()->equals(new NumVal(8))));
    CHECK((o->interp()->equals(new NumVal(6))));
    CHECK((q->interp()->equals(new NumVal(18))));
    CHECK((r->interp()->equals(new NumVal(5))));
    CHECK_THROWS_WITH( p->interp(), "Var can not be interperated" );
    Expr* k=new IfExpr(new EqExpr(new NumExpr(2),new NumExpr(1)),new NumExpr(5),new AddExpr(new NumExpr(3), new NumExpr(3)));
    Expr* l=new IfExpr(new VarExpr("x"),new VarExpr("x"),new AddExpr(new NumExpr(3), new NumExpr(3)));
    Expr* m=new IfExpr(new EqExpr(new BoolExpr(true),new BoolExpr(true)),new NumExpr(5),new AddExpr(new BoolExpr(true), new NumExpr(3)));
    Expr* aa=new IfExpr(new NumExpr(2),new NumExpr(5),new AddExpr(new BoolExpr(true), new NumExpr(3)));
    CHECK((k->interp()->equals(new NumVal(6))));
    CHECK_THROWS_WITH( l->interp(), "Var can not be interperated");
    CHECK_THROWS_WITH( aa->interp(), "If of a Non Boolean Statement");
    CHECK((m->interp()->equals(new NumVal(5))));
}
TEST_CASE("subtr")
{
    CHECK( (new AddExpr(new VarExpr("x"), new NumExpr(7)))
    ->subst("x", new VarExpr("y"))
    ->equals(new AddExpr(new VarExpr("y"), new NumExpr(7))) );
    CHECK( (new AddExpr(new VarExpr("x"), new VarExpr("y")))
       ->subst("x", new VarExpr("y"))
          ->equals(new AddExpr(new VarExpr("y"), new VarExpr("y"))) );
    CHECK( (new MultExpr(new VarExpr("x"), new NumExpr(7)))
    ->subst("x", new VarExpr("y"))
    ->equals(new MultExpr(new VarExpr("y"), new NumExpr(7))) );
    CHECK( (new MultExpr(new MultExpr(new VarExpr("x"),new NumExpr(8)), new NumExpr(7)))
    ->subst("x", new VarExpr("y"))
    ->equals(new MultExpr(new MultExpr(new VarExpr("y"),new NumExpr(8)), new NumExpr(7))) );
    CHECK( (new EqExpr(new MultExpr(new VarExpr("x"),new NumExpr(8)), new NumExpr(7)))
    ->subst("x", new VarExpr("y"))
    ->equals(new EqExpr(new MultExpr(new VarExpr("y"),new NumExpr(8)), new NumExpr(7))) );
    CHECK( (new _letExpr(new VarExpr("x"),new NumExpr(8),new AddExpr(new VarExpr("x"),new NumExpr(2))))
    ->subst("x", new VarExpr("y"))
    ->equals(new _letExpr(new VarExpr("x"),new NumExpr(8),new AddExpr(new VarExpr("x"),new NumExpr(2)))));
    CHECK( (new _letExpr(new VarExpr("x"),new NumExpr(8),new AddExpr(new VarExpr("y"),new NumExpr(2))))
    ->subst("y", new AddExpr(new VarExpr("x"),new NumExpr(2)))
    ->equals(new _letExpr(new VarExpr("x"),new NumExpr(8),new AddExpr(new AddExpr(new VarExpr("x"),new NumExpr(2)),new NumExpr(2)))));
    CHECK( (new IfExpr(new BoolExpr(true),new NumExpr(8),new AddExpr(new VarExpr("y"),new NumExpr(2))))
    ->subst("y", new AddExpr(new VarExpr("x"),new NumExpr(2)))
    ->equals(new IfExpr(new BoolExpr(true),new NumExpr(8),new AddExpr(new AddExpr(new VarExpr("x"),new NumExpr(2)),new NumExpr(2)))));
    
    
        
}
TEST_CASE("print")
{

    Expr* a=new AddExpr(new NumExpr(5),new MultExpr(new VarExpr ("c"),new NumExpr(2)));
    std::string test1="(5+(c*2))";
    CHECK(a->to_String()==test1);
    Expr* b=new AddExpr(new AddExpr(new NumExpr(2),new NumExpr(3)),new MultExpr(new VarExpr ("c"),new NumExpr(2)));
       std::string test2="((2+3)+(c*2))";
    CHECK(b->to_String()==test2);
    Expr* c=new AddExpr(new NumExpr(5),new VarExpr("a"));
    std::string test3="(5+a)";
    CHECK(c->to_String()==test3);
    Expr* d=new MultExpr(new NumExpr(5),new VarExpr("a"));
    std::string test4="(5*a)";
    CHECK(d->to_String()==test4);
    std::string test5="(_let x=5 _in ((_let y=3 _in (y+2))+x))";
    Expr* e=new _letExpr(new VarExpr("x"),new NumExpr(5),new AddExpr(new _letExpr(new VarExpr("y"),new NumExpr(3),new AddExpr(new VarExpr("y"),new NumExpr(2))),new VarExpr("x")));
    CHECK(e->to_String()==test5);
    std::string test6="(_if _true _then 8 _else (x+2))";
    CHECK( (new IfExpr(new BoolExpr(true),new NumExpr(8),new AddExpr(new VarExpr("x"),new NumExpr(2))))
       ->to_String()==test6);
     std::string test7="(x==y)";
    CHECK( (new EqExpr(new VarExpr("x"),new VarExpr("y")))
          ->to_String()==test7);
    
}
TEST_CASE("printPretty")
{
    Expr* a=new AddExpr(new NumExpr(5),new MultExpr(new VarExpr ("c"),new NumExpr(2)));
    std::string test1="5 + c * 2";
    CHECK(a->to_String_pretty()==test1);
    Expr* b=new AddExpr(new AddExpr(new NumExpr(2),new NumExpr(3)),new MultExpr(new VarExpr ("c"),new NumExpr(2)));
    std::string test2="(2 + 3) + c * 2";
    CHECK(b->to_String_pretty()==test2);
    Expr* c=new AddExpr(new NumExpr(5),new VarExpr("a"));
    std::string test3="5 + a";
    CHECK(c->to_String_pretty()==test3);
    Expr* d=new MultExpr(new NumExpr(5),new VarExpr("a"));
    std::string test4="5 * a";
    CHECK(d->to_String_pretty()==test4);
    Expr* e=new MultExpr(new AddExpr(new NumExpr(2),new NumExpr(3)),new MultExpr(new VarExpr ("c"),new NumExpr(2)));
    std::string test5="(2 + 3) * c * 2";
    CHECK(e->to_String_pretty()==test5);
    Expr* f=new MultExpr(new NumExpr(2),new MultExpr(new NumExpr (3),new NumExpr(4)));
    std::string test6="2 * 3 * 4";
    CHECK(f->to_String_pretty()==test6);
    Expr* g=new MultExpr(new MultExpr(new NumExpr (2),new NumExpr(3)),new NumExpr(4));
    std::string test7="(2 * 3) * 4";
    CHECK(g->to_String_pretty()==test7);
    std::string test8=("5 * (_let x = 5\n     _in  x) + 1");
    Expr* h=new MultExpr(new NumExpr(5),new AddExpr(new _letExpr(new VarExpr("x"),new NumExpr(5),new VarExpr("x")),new NumExpr(1)));
    CHECK(h->to_String_pretty()==test8);
    std::string test9=("5 * _let x = 5\n    _in  x + 1");
    Expr* i=new MultExpr(new NumExpr(5),new _letExpr(new VarExpr("x"),new NumExpr(5),new AddExpr(new VarExpr("x"),new NumExpr(1))));
    CHECK(i->to_String_pretty()==test9);
    std::string test10=("_if  _false == _true\n_then 2 + d\n_else 3 * 9");
    Expr* j=new IfExpr(new EqExpr(new BoolExpr(false),new BoolExpr(true)),new AddExpr(new NumExpr(2), new VarExpr("d")),new MultExpr(new NumExpr(3),new NumExpr(9)));
    CHECK(j->to_String_pretty()==test10);
}

