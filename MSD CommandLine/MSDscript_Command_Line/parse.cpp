//
//  parse.cpp
//  MSDscript_Command_Line
//
//  Created by Braden McClean on 2/14/21.
//  Copyright © 2021 Braden McClean. All rights reserved.
//

#include "parse.hpp"
#include "Catch.h"
#include <sstream>

 void consume(std::istream& stream, int expect)
{
    int c=stream.get();
    if(c!=expect)
    {
        throw std::runtime_error("Consume Mismatch");
    }
    
};
 void skip_whitespace(std::istream &in)
{
    while (1)
    {
        int c = in.peek();
        if (!isspace(c))
        {
            break;
        }
        consume(in, c);
    }
};
Expr *parse_str(std::string s)
{
    std::istringstream is(s);

    Expr*e= parse_expr(is);
    return e;
}
Expr *parse_addend(std::istream &in)
{
    Expr *e;
 
    e = parse_multicand(in);
    skip_whitespace(in);
    int c = in.peek();
    if (c == '*')
    {
    consume(in, '*');
    Expr *rhs = parse_addend(in);
    return new MultExpr(e, rhs);
    }
    else
    {
        return e;
    }
 
}
VarExpr *parse_var(std::istream &in)
{
    std::string temp;
      while (1)
      {
          char c = in.peek();
          if (isalpha(c))
          {
              consume(in, c);
              temp=c;

          } else
          {
              break;
          }
      }
//    std::cout<<temp;
//    std::cout<<"\n";
      return new VarExpr(temp);
    
}
Expr *parse_multicand(std::istream &in)
{
    skip_whitespace(in);
    
     int c = in.peek();
     if ((c == '-') || isdigit(c))
     {
         return parse_num(in);
     }
     else if (c == '(')
     {
         consume(in, '(');
         Expr *e = parse_expr(in);
         skip_whitespace(in);
         c = in.get();
         if (c != ')')
         {
             throw std::runtime_error("missing close parenthesis");
         }
     return e;
     }
    else if (isalpha(c))
    {
        return parse_var(in);
    }
    else if (c=='_')
    {
        consume(in, '_');
         c = in.peek();
        if (c=='l')
        {
        consume(in, 'l');
        consume(in, 'e');
        consume(in, 't');
        
        return parse_let(in);
        }else if (c=='t')
        {
            consume(in, 't');
            consume(in, 'r');
            consume(in, 'u');
            consume(in, 'e');
            return new BoolExpr(true);
        }else if (c=='f')
        {   consume(in, 'f');
            consume(in, 'a');
            consume(in, 'l');
            consume(in, 's');
            consume(in, 'e');
            return new BoolExpr(false);
        }else
        {
            consume(in, 'i');
            consume(in, 'f');
            return parse_if(in);
        }
    }
    else
     {
     consume(in, c);
     throw std::runtime_error("invalid input");
     }
}
Expr *parse_if(std::istream &in)
{
    Expr *_if;
    Expr *_then;
    Expr *_else;
   
    skip_whitespace(in);
    _if=parse_var(in);
    skip_whitespace(in);
   int c=in.peek();
    if (c == '_')
    {
        consume(in, '_');
        consume(in, 't');
        consume(in, 'h');
        consume(in, 'e');
        consume(in, 'n');
        _then = parse_expr(in);
    }else
    {
        throw std::runtime_error("invalid _then");
    }
    c=in.peek();
    if(c == '_')
    {
       consume(in, '_');
       consume(in, 'e');
       consume(in, 'l');
       consume(in, 's');
       consume(in, 'e');
        _else=parse_expr(in);
    }else
    {
        throw std::runtime_error("invalid _else");
    }
    return new IfExpr(_if,_then,_else);
}
Expr *parse_let(std::istream &in)
{
    VarExpr *e;
    Expr *rhs;
    Expr *body;
    skip_whitespace(in);
    e=parse_var(in);
    skip_whitespace(in);
    int c=in.peek();
    if (c == '=')
    {
        consume(in, '=');
        rhs = parse_expr(in);
    }else
    {
        throw std::runtime_error("invalid equals");
    }
    c=in.peek();
    if(c == '_')
    {
       consume(in, '_');
        consume(in, 'i');
        consume(in, 'n');
        body=parse_expr(in);
    }else
    {
        throw std::runtime_error("invalid _In");
    }
    return new _letExpr(e,rhs,body);
}
Expr *parse_num(std::istream &in)
{
    int n = 0;
    bool negative = false;
     if (in.peek() == '-')
     {
     negative = true;
     consume(in, '-');
     }

    while (1)
    {
        int c = in.peek();
        if (isdigit(c))
        {
            consume(in, c);
            n = n*10 + (c - '0');
        } else
        {
            break;
        }
    }
    if (negative)
    {
        n = -n;
    }
    return new NumExpr(n);
};
Expr *parse_comparg(std::istream &in)
{
    Expr *e;

    e = parse_addend(in);
    skip_whitespace(in);
    int c = in.peek();
    if (c == '+')
    {
    consume(in, '+');
    Expr *rhs = parse_comparg(in);
    return new AddExpr(e, rhs);
    }
    else
    {
        return e;
    }
};
Expr *parse_expr(std::istream &in)
{
    Expr *e;

    e = parse_comparg(in);
    skip_whitespace(in);
    int c = in.peek();
    if (c == '=')
    {
    consume(in, '=');
    consume(in, '=');
    Expr *rhs = parse_expr(in);
    return new EqExpr(e, rhs);
    }
    else
    {
        return e;
    }
};


TEST_CASE("Parse")
{
    std::string test1="(2+3)";
    Expr* a=new AddExpr(new NumExpr(2),new NumExpr(3));
    CHECK(a->equals(parse_str(test1)));
    std::string test2="((2+3)*2)";
    Expr* b=new MultExpr(new AddExpr(new NumExpr(2),new NumExpr(3)),new NumExpr(2));
    CHECK(b->equals(parse_str(test2)));
    std::string test3="((-2+3)*2)";
       Expr* c=new MultExpr(new AddExpr(new NumExpr(-2),new NumExpr(3)),new NumExpr(2));
    CHECK(c->equals(parse_str(test3)));
     std::string test4="_let x = 5 _in(x+3)";
    Expr* d=new _letExpr(new VarExpr("x"),new NumExpr(5),new AddExpr(new VarExpr ("x"), new NumExpr(3)));
    CHECK(d->equals(parse_str(test4)));
    std::string test5="_if x _then 5 _else (x+3)";
    Expr* e=new IfExpr(new VarExpr("x"),new NumExpr(5),new AddExpr(new VarExpr ("x"), new NumExpr(3)));
    CHECK(e->equals(parse_str(test5)));
    std::string test6="_true == _false";
    Expr* f=new EqExpr(new BoolExpr(true),new BoolExpr(false));
    CHECK(f->equals(parse_str(test6)));
//     std::string test5="@#@#@$#@";
//     CHECK_THROWS_WITH( (parse_str(test5)), "invalid input");
//    std::string test6="_let x ? 5 _in(x+3)";
//    CHECK_THROWS_WITH( (parse_str(test6)), "invalid equals");
//    std::string test7="_let x = 5 in(x+3)";
//    CHECK_THROWS_WITH( (parse_str(test7)), "invalid _In");
//    std::string test8="(3+2+3";
//    CHECK_THROWS_WITH( (parse_str(test8)), "missing close parenthesis");
//    std::string test9="_let x = 5 __in(x+3)";
//       CHECK_THROWS_WITH( (parse_str(test9)), "Consume Mismatch");
}


