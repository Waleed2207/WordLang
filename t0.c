
#include <stdio.h>
#include "utils.h"

int main()
{
StScopeList *listVars = NULL;
StTreeNode *tree = joinNode(
  newNodeKind(OutputK, NULL, 
    newNodeKind(ConstWordK, "Hello", NULL, NULL, NULL)
, NULL, NULL)
, 
joinNode(
  newNodeKind(OutputK, NULL, 
    newNodeKind(ConstWordK, "World", NULL, NULL, NULL)
, NULL, NULL)
, 
joinNode(
  newNodeKind(OutputK, NULL, 
    newNodeKind(ConcatK, NULL, 
      newNodeKind(ConstWordK, "Hello", NULL, NULL, NULL)
, 
      newNodeKind(ConstWordK, "World", NULL, NULL, NULL)
, NULL)
, NULL, NULL)
, 
joinNode(
  newNodeKind(OutputK, NULL, 
    newNodeKind(ConcatK, NULL, 
      newNodeKind(ConstSenteK, "Hello", NULL, NULL, NULL)
, 
      newNodeKind(ConstWordK, "World", NULL, NULL, NULL)
, NULL)
, NULL, NULL)
, 
joinNode(
  newNodeKind(OutputK, NULL, 
    newNodeKind(ConcatK, NULL, 
      newNodeKind(ConstWordK, "Hello", NULL, NULL, NULL)
, 
      newNodeKind(IndexK, NULL, 
        newNodeKind(ConstWordK, "World", NULL, NULL, NULL)
, 
        newNodeKind(ConstIntK, "1", NULL, NULL, NULL)
, NULL)
, NULL)
, NULL, NULL)
, 
joinNode(
  newNodeKind(OutputK, NULL, 
    newNodeKind(IndexK, NULL, 
      newNodeKind(ConcatK, NULL, 
        newNodeKind(ConstWordK, "Hello", NULL, NULL, NULL)
, 
        newNodeKind(ConstWordK, "World", NULL, NULL, NULL)
, NULL)
, 
      newNodeKind(ConstIntK, "7", NULL, NULL, NULL)
, NULL)
, NULL, NULL)
, 
joinNode(
  newNodeKind(OutputK, NULL, 
    newNodeKind(IndexK, NULL, 
      newNodeKind(ConcatK, NULL, 
        newNodeKind(ConstWordK, "Hello", NULL, NULL, NULL)
, 
        newNodeKind(ConstWordK, "World", NULL, NULL, NULL)
, NULL)
, 
      newNodeKind(ConstIntK, "-1", NULL, NULL, NULL)
, NULL)
, NULL, NULL)
, 
joinNode(
  newNodeKind(OutputK, NULL, 
    newNodeKind(IndexK, NULL, 
      newNodeKind(ConcatK, NULL, 
        newNodeKind(ConstSenteK, "Hello", NULL, NULL, NULL)
, 
        newNodeKind(ConstWordK, "World", NULL, NULL, NULL)
, NULL)
, 
      newNodeKind(ConstIntK, "1", NULL, NULL, NULL)
, NULL)
, NULL, NULL)
, 
joinNode(
  newNodeKind(OutputK, NULL, 
    newNodeKind(OperK, "-", 
      newNodeKind(ConcatK, NULL, 
        newNodeKind(ConstWordK, "Hello", NULL, NULL, NULL)
, 
        newNodeKind(ConstWordK, "World", NULL, NULL, NULL)
, NULL)
, 
      newNodeKind(ConstCharK, "l", NULL, NULL, NULL)
, NULL)
, NULL, NULL)
, 
joinNode(
  newNodeKind(OutputK, NULL, 
    newNodeKind(ConcatK, NULL, 
      newNodeKind(ConstWordK, "Hello", NULL, NULL, NULL)
, 
      newNodeKind(OperK, "-", 
        newNodeKind(ConstWordK, "World", NULL, NULL, NULL)
, 
        newNodeKind(ConstCharK, "l", NULL, NULL, NULL)
, NULL)
, NULL)
, NULL, NULL)
, 
joinNode(
  newNodeKind(DeclK, "sentence", 
    newNodeKind(IdK, "s1", NULL, NULL, NULL)
, NULL, NULL)
, 
joinNode(
  newNodeKind(AssignK, "s1", 
    newNodeKind(ConstSenteK, "We live in a", NULL, NULL, NULL)
, NULL, NULL)
, 
joinNode(
  newNodeKind(OutputK, NULL, 
    newNodeKind(ConcatK, NULL, 
      newNodeKind(IdK, "s1", NULL, NULL, NULL)
, 
      newNodeKind(ConstSenteK, "World", NULL, NULL, NULL)
, NULL)
, NULL, NULL)
, 
joinNode(
  newNodeKind(AssignK, "s1", 
    newNodeKind(ConcatK, NULL, 
      newNodeKind(ConcatK, NULL, 
        newNodeKind(ConcatK, NULL, 
          newNodeKind(IdK, "s1", NULL, NULL, NULL)
, 
          newNodeKind(ConstWordK, "wonderful", NULL, NULL, NULL)
, NULL)
, 
        newNodeKind(ConstWordK, "world", NULL, NULL, NULL)
, NULL)
, 
      newNodeKind(ConstCharK, "!", NULL, NULL, NULL)
, NULL)
, NULL, NULL)
, 
joinNode(
  newNodeKind(OutputK, NULL, 
    newNodeKind(IdK, "s1", NULL, NULL, NULL)
, NULL, NULL)
, 
joinNode(
  newNodeKind(OutputK, NULL, 
    newNodeKind(OperK, "-", 
      newNodeKind(IdK, "s1", NULL, NULL, NULL)
, 
      newNodeKind(ConstWordK, "wonderful", NULL, NULL, NULL)
, NULL)
, NULL, NULL)
, 
  newNodeKind(OutputK, NULL, 
    newNodeKind(OperK, "-", 
      newNodeKind(IdK, "s1", NULL, NULL, NULL)
, 
      newNodeKind(ConstCharK, "w", NULL, NULL, NULL)
, NULL)
, NULL, NULL)
))))))))))))))));

executeTree(tree, 0, &listVars);
deleteIdScopeList(&listVars, 0);

return 0;
}
