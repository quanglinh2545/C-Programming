Skip to content
Search or jump to…

Pull requests
Issues
Marketplace
Explore
 
@quanglinh2545 
Learn Git and GitHub without any code!
Using the Hello World guide, you’ll start a branch, write comments, and open a pull request.


midori-hust
/
test_repo
1
06
Code
Issues
Pull requests
Actions
Projects
Wiki
Security
Insights
test_repo/chuongtrinhdich/w6/day4/incompleted/semantics.c
@midori-hust
midori-hust Second init :D
Latest commit 19d93ec on Sep 8, 2014
 History
 1 contributor
160 lines (133 sloc)  3.91 KB
 
/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdlib.h>
#include <string.h>
#include "semantics.h"
#include "error.h"

extern SymTab* symtab;
extern Token* currentToken;

Object* lookupObject(char *name) {
  Scope* scope = symtab->currentScope;
  Object* obj;

  while (scope != NULL) {
    obj = findObject(scope->objList, name);
    if (obj != NULL) return obj;
    scope = scope->outer;
  }
  obj = findObject(symtab->globalObjectList, name);
  if (obj != NULL) return obj;
  return NULL;
}

void checkFreshIdent(char *name) {
  if (findObject(symtab->currentScope->objList, name) != NULL)
    error(ERR_DUPLICATE_IDENT, currentToken->lineNo, currentToken->colNo);
}

Object* checkDeclaredIdent(char* name) {
  Object* obj = lookupObject(name);
  if (obj == NULL) {
    error(ERR_UNDECLARED_IDENT,currentToken->lineNo, currentToken->colNo);
  }
  return obj;
}

Object* checkDeclaredConstant(char* name) {
  Object* obj = lookupObject(name);
  if (obj == NULL)
    error(ERR_UNDECLARED_CONSTANT,currentToken->lineNo, currentToken->colNo);
  if (obj->kind != OBJ_CONSTANT)
    error(ERR_INVALID_CONSTANT,currentToken->lineNo, currentToken->colNo);

  return obj;
}

Object* checkDeclaredType(char* name) {
  Object* obj = lookupObject(name);
  if (obj == NULL)
    error(ERR_UNDECLARED_TYPE,currentToken->lineNo, currentToken->colNo);
  if (obj->kind != OBJ_TYPE)
    error(ERR_INVALID_TYPE,currentToken->lineNo, currentToken->colNo);

  return obj;
}

Object* checkDeclaredVariable(char* name) {
  Object* obj = lookupObject(name);
  if (obj == NULL)
    error(ERR_UNDECLARED_VARIABLE,currentToken->lineNo, currentToken->colNo);
  if (obj->kind != OBJ_VARIABLE)
    error(ERR_INVALID_VARIABLE,currentToken->lineNo, currentToken->colNo);

  return obj;
}

Object* checkDeclaredFunction(char* name) {
  Object* obj = lookupObject(name);
  if (obj == NULL)
    error(ERR_UNDECLARED_FUNCTION,currentToken->lineNo, currentToken->colNo);
  if (obj->kind != OBJ_FUNCTION)
    error(ERR_INVALID_FUNCTION,currentToken->lineNo, currentToken->colNo);

  return obj;
}

Object* checkDeclaredProcedure(char* name) {
  Object* obj = lookupObject(name);
  if (obj == NULL)
    error(ERR_UNDECLARED_PROCEDURE,currentToken->lineNo, currentToken->colNo);
  if (obj->kind != OBJ_PROCEDURE)
    error(ERR_INVALID_PROCEDURE,currentToken->lineNo, currentToken->colNo);

  return obj;
}

Object* checkDeclaredLValueIdent(char* name) {
  Object* obj = lookupObject(name);
  if (obj == NULL)
    error(ERR_UNDECLARED_IDENT,currentToken->lineNo, currentToken->colNo);

  switch (obj->kind) {
  case OBJ_VARIABLE:
  case OBJ_PARAMETER:
    break;
  case OBJ_FUNCTION:
    if (obj != symtab->currentScope->owner) 
      error(ERR_INVALID_IDENT,currentToken->lineNo, currentToken->colNo);
    break;
  default:
    error(ERR_INVALID_IDENT,currentToken->lineNo, currentToken->colNo);
  }

  return obj;
}


void checkIntType(Type* type) {
  // TODO
  if (type != NULL && type->typeClass == TP_INT) {
    return;
  }
  else { 
    error(ERR_TYPE_INCONSISTENCY, currentToken->lineNo, currentToken->colNo);
  }
}

void checkCharType(Type* type) {
  // TODO
  if (type != NULL && type->typeClass == TP_CHAR) {
    return;
  }
  else { 
    error(ERR_TYPE_INCONSISTENCY, currentToken->lineNo, currentToken->colNo);
  }
}

void checkBasicType(Type* type) {
  // TODO
   if (type != NULL && (type->typeClass == TP_INT || type->typeClass == TP_CHAR)) {
    return;
  }
   else { 
    error(ERR_TYPE_INCONSISTENCY, currentToken->lineNo, currentToken->colNo);
  }
}

void checkArrayType(Type* type) {
  // TODO
  if (type != NULL && type->typeClass == TP_ARRAY) {
    return;
  }
  else { 
    error(ERR_TYPE_INCONSISTENCY, currentToken->lineNo, currentToken->colNo);
  }
}

void checkTypeEquality(Type* type1, Type* type2) {
  // TODO
  if (compareType(type1, type2) == 0) {
    error(ERR_TYPE_INCONSISTENCY, currentToken->lineNo, currentToken->colNo);
  }
}


© 2020 GitHub, Inc.
Terms
Privacy
Security
Status
Help
Contact GitHub