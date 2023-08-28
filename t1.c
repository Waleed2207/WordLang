
#include <stdio.h>
#include "utils.h"

int main()
{
StScopeList *listVars = NULL;
StTreeNode *tree = joinNode(
  newNodeKind(DeclK, "word", 
    newNodeKind(IdK, "w1", NULL, NULL, NULL)
, NULL, NULL)
, 
joinNode(
  newNodeKind(DeclK, "sentence", 
joinNode(
    newNodeKind(IdK, "s1", NULL, NULL, NULL)
, 
    newNodeKind(IdK, "adverb", NULL, NULL, NULL)
), NULL, NULL)
, 
joinNode(
  newNodeKind(LoopK, NULL, 
    newNodeKind(ConstIntK, "3", NULL, NULL, NULL)
, 
    newNodeKind(AssignK, "adverb", 
      newNodeKind(ConcatK, NULL, 
        newNodeKind(IdK, "adverb", NULL, NULL, NULL)
, 
        newNodeKind(ConstWordK, "very", NULL, NULL, NULL)
, NULL)
, NULL, NULL)
, NULL)
, 
joinNode(
  newNodeKind(AssignK, "w1", 
    newNodeKind(ConstWordK, "interesting", NULL, NULL, NULL)
, NULL, NULL)
, 
joinNode(
  newNodeKind(AssignK, "s1", 
    newNodeKind(ConcatK, NULL, 
      newNodeKind(ConcatK, NULL, 
        newNodeKind(ConstSenteK, "Compilers are a", NULL, NULL, NULL)
, 
        newNodeKind(IdK, "adverb", NULL, NULL, NULL)
, NULL)
, 
      newNodeKind(IdK, "w1", NULL, NULL, NULL)
, NULL)
, NULL, NULL)
, 
joinNode(
  newNodeKind(OutputK, NULL, 
    newNodeKind(ConcatK, NULL, 
      newNodeKind(IdK, "s1", NULL, NULL, NULL)
, 
      newNodeKind(ConstWordK, "topic", NULL, NULL, NULL)
, NULL)
, NULL, NULL)
, 
joinNode(
  newNodeKind(DeclK, "word", 
joinNode(
    newNodeKind(IdK, "object", NULL, NULL, NULL)
, 
    newNodeKind(IdK, "article", NULL, NULL, NULL)
), NULL, NULL)
, 
joinNode(
  newNodeKind(DeclK, "char", 
    newNodeKind(IdK, "notVowel", NULL, NULL, NULL)
, NULL, NULL)
, 
joinNode(
  newNodeKind(InputK, "object", 
    newNodeKind(ConstSenteK, "What are you holding?", NULL, NULL, NULL)
, NULL, NULL)
, 
joinNode(
  newNodeKind(AssignK, "notVowel", 
    newNodeKind(IndexK, NULL, 
      newNodeKind(IdK, "object", NULL, NULL, NULL)
, 
      newNodeKind(ConstIntK, "0", NULL, NULL, NULL)
, NULL)
, NULL, NULL)
, 
joinNode(
  newNodeKind(AssignK, "notVowel", 
    newNodeKind(OperK, "-", 
      newNodeKind(OperK, "-", 
        newNodeKind(OperK, "-", 
          newNodeKind(OperK, "-", 
            newNodeKind(OperK, "-", 
              newNodeKind(IdK, "notVowel", NULL, NULL, NULL)
, 
              newNodeKind(ConstCharK, "a", NULL, NULL, NULL)
, NULL)
, 
            newNodeKind(ConstCharK, "e", NULL, NULL, NULL)
, NULL)
, 
          newNodeKind(ConstCharK, "i", NULL, NULL, NULL)
, NULL)
, 
        newNodeKind(ConstCharK, "o", NULL, NULL, NULL)
, NULL)
, 
      newNodeKind(ConstCharK, "u", NULL, NULL, NULL)
, NULL)
, NULL, NULL)
, 
joinNode(
  newNodeKind(AssignK, "s1", 
    newNodeKind(ConstSenteK, "You are holding", NULL, NULL, NULL)
, NULL, NULL)
, 
joinNode(
  newNodeKind(IfK, NULL, 
    newNodeKind(OperRelK, "eval", 
      newNodeKind(IdK, "notVowel", NULL, NULL, NULL)
, 
 NULL, NULL)
, 
    newNodeKind(AssignK, "article", 
      newNodeKind(ConstWordK, "a", NULL, NULL, NULL)
, NULL, NULL)
, 
    newNodeKind(AssignK, "article", 
      newNodeKind(ConstWordK, "an", NULL, NULL, NULL)
, NULL, NULL)
)
, 
joinNode(
  newNodeKind(OutputK, NULL, 
    newNodeKind(ConcatK, NULL, 
      newNodeKind(ConcatK, NULL, 
        newNodeKind(IdK, "s1", NULL, NULL, NULL)
, 
        newNodeKind(IdK, "article", NULL, NULL, NULL)
, NULL)
, 
      newNodeKind(IdK, "object", NULL, NULL, NULL)
, NULL)
, NULL, NULL)
, 
joinNode(
  newNodeKind(DeclK, "word", 
    newNodeKind(IdK, "last", NULL, NULL, NULL)
, NULL, NULL)
, 
joinNode(
  newNodeKind(AssignK, "last", 
    newNodeKind(IndexK, NULL, 
      newNodeKind(IdK, "s1", NULL, NULL, NULL)
, 
      newNodeKind(ConstIntK, "-1", NULL, NULL, NULL)
, NULL)
, NULL, NULL)
, 
joinNode(
  newNodeKind(WhileK, NULL, 
    newNodeKind(OperRelK, "!=", 
      newNodeKind(IndexK, NULL, 
        newNodeKind(IdK, "s1", NULL, NULL, NULL)
, 
        newNodeKind(ConstIntK, "0", NULL, NULL, NULL)
, NULL)
, 
      newNodeKind(IdK, "last", NULL, NULL, NULL)
, NULL)
, 
joinNode(
    newNodeKind(AssignK, "w1", 
      newNodeKind(IndexK, NULL, 
        newNodeKind(IdK, "s1", NULL, NULL, NULL)
, 
        newNodeKind(ConstIntK, "0", NULL, NULL, NULL)
, NULL)
, NULL, NULL)
, 
    newNodeKind(AssignK, "s1", 
      newNodeKind(ConcatK, NULL, 
        newNodeKind(OperK, "-", 
          newNodeKind(IdK, "s1", NULL, NULL, NULL)
, 
          newNodeKind(IdK, "w1", NULL, NULL, NULL)
, NULL)
, 
        newNodeKind(IdK, "w1", NULL, NULL, NULL)
, NULL)
, NULL, NULL)
), NULL)
, 
joinNode(
  newNodeKind(OutputK, NULL, 
    newNodeKind(IdK, "s1", NULL, NULL, NULL)
, NULL, NULL)
, 
joinNode(
  newNodeKind(DeclK, "char", 
joinNode(
    newNodeKind(IdK, "b", NULL, NULL, NULL)
, 
joinNode(
    newNodeKind(IdK, "e", NULL, NULL, NULL)
, 
    newNodeKind(IdK, "palindrome", NULL, NULL, NULL)
)), NULL, NULL)
, 
joinNode(
  newNodeKind(DeclK, "word", 
    newNodeKind(IdK, "savWord", NULL, NULL, NULL)
, NULL, NULL)
, 
joinNode(
  newNodeKind(AssignK, "palindrome", 
    newNodeKind(ConstCharK, "Y", NULL, NULL, NULL)
, NULL, NULL)
, 
joinNode(
  newNodeKind(InputK, "w1", 
    newNodeKind(ConstSenteK, "Enter a word:", NULL, NULL, NULL)
, NULL, NULL)
, 
joinNode(
  newNodeKind(AssignK, "savWord", 
    newNodeKind(IdK, "w1", NULL, NULL, NULL)
, NULL, NULL)
, 
joinNode(
  newNodeKind(WhileK, NULL, 
    newNodeKind(OperRelK, "eval", 
      newNodeKind(IdK, "w1", NULL, NULL, NULL)
, 
 NULL, NULL)
, 
joinNode(
    newNodeKind(AssignK, "b", 
      newNodeKind(IndexK, NULL, 
        newNodeKind(IdK, "w1", NULL, NULL, NULL)
, 
        newNodeKind(ConstIntK, "0", NULL, NULL, NULL)
, NULL)
, NULL, NULL)
, 
joinNode(
    newNodeKind(AssignK, "e", 
      newNodeKind(IndexK, NULL, 
        newNodeKind(IdK, "w1", NULL, NULL, NULL)
, 
        newNodeKind(ConstIntK, "-1", NULL, NULL, NULL)
, NULL)
, NULL, NULL)
, 
joinNode(
    newNodeKind(IfK, NULL, 
      newNodeKind(OperRelK, "==", 
        newNodeKind(IdK, "palindrome", NULL, NULL, NULL)
, 
        newNodeKind(ConstCharK, "Y", NULL, NULL, NULL)
, NULL)
, 
      newNodeKind(IfK, NULL, 
        newNodeKind(OperRelK, "!=", 
          newNodeKind(IdK, "e", NULL, NULL, NULL)
, 
          newNodeKind(IdK, "b", NULL, NULL, NULL)
, NULL)
, 
        newNodeKind(AssignK, "palindrome", 
          newNodeKind(ConstCharK, "N", NULL, NULL, NULL)
, NULL, NULL)
, 
 NULL)
, 
 NULL)
, 
    newNodeKind(AssignK, "w1", 
      newNodeKind(OperK, "-", 
        newNodeKind(OperK, "-", 
          newNodeKind(IdK, "w1", NULL, NULL, NULL)
, 
          newNodeKind(IdK, "b", NULL, NULL, NULL)
, NULL)
, 
        newNodeKind(IdK, "e", NULL, NULL, NULL)
, NULL)
, NULL, NULL)
))), NULL)
, 
joinNode(
  newNodeKind(IfK, NULL, 
    newNodeKind(OperRelK, "==", 
      newNodeKind(IdK, "palindrome", NULL, NULL, NULL)
, 
      newNodeKind(ConstCharK, "Y", NULL, NULL, NULL)
, NULL)
, 
    newNodeKind(OutputK, NULL, 
      newNodeKind(ConcatK, NULL, 
        newNodeKind(IdK, "savWord", NULL, NULL, NULL)
, 
        newNodeKind(ConstSenteK, "is a palindrome word", NULL, NULL, NULL)
, NULL)
, NULL, NULL)
, 
    newNodeKind(OutputK, NULL, 
      newNodeKind(ConcatK, NULL, 
        newNodeKind(IdK, "savWord", NULL, NULL, NULL)
, 
        newNodeKind(ConstSenteK, "is not a palindrome", NULL, NULL, NULL)
, NULL)
, NULL, NULL)
)
, 
joinNode(
  newNodeKind(AssignK, "s1", 
    newNodeKind(ConstSenteK, "apple an holding are you", NULL, NULL, NULL)
, NULL, NULL)
, 
joinNode(
  newNodeKind(DeclK, "int", 
joinNode(
    newNodeKind(IdK, "i", NULL, NULL, NULL)
, 
joinNode(
    newNodeKind(IdK, "j", NULL, NULL, NULL)
, 
    newNodeKind(IdK, "count", NULL, NULL, NULL)
)), NULL, NULL)
, 
joinNode(
  newNodeKind(AssignK, "count", 
    newNodeKind(ConstIntK, "0", NULL, NULL, NULL)
, NULL, NULL)
, 
joinNode(
  newNodeKind(WhileK, NULL, 
    newNodeKind(OperRelK, "eval", 
      newNodeKind(IndexK, NULL, 
        newNodeKind(IdK, "s1", NULL, NULL, NULL)
, 
        newNodeKind(IdK, "count", NULL, NULL, NULL)
, NULL)
, 
 NULL, NULL)
, 
    newNodeKind(AssignK, "count", 
      newNodeKind(OperK, "+", 
        newNodeKind(IdK, "count", NULL, NULL, NULL)
, 
        newNodeKind(ConstIntK, "1", NULL, NULL, NULL)
, NULL)
, NULL, NULL)
, NULL)
, 
joinNode(
  newNodeKind(DeclK, "sentence", 
    newNodeKind(IdK, "s", NULL, NULL, NULL)
, NULL, NULL)
, 
joinNode(
  newNodeKind(WhileK, NULL, 
    newNodeKind(OperRelK, ">", 
      newNodeKind(IdK, "count", NULL, NULL, NULL)
, 
      newNodeKind(ConstIntK, "1", NULL, NULL, NULL)
, NULL)
, 
joinNode(
    newNodeKind(AssignK, "i", 
      newNodeKind(ConstIntK, "0", NULL, NULL, NULL)
, NULL, NULL)
, 
joinNode(
    newNodeKind(LoopK, NULL, 
      newNodeKind(OperK, "-", 
        newNodeKind(IdK, "count", NULL, NULL, NULL)
, 
        newNodeKind(ConstIntK, "1", NULL, NULL, NULL)
, NULL)
, 
joinNode(
      newNodeKind(IfK, NULL, 
        newNodeKind(OperRelK, ">", 
          newNodeKind(IndexK, NULL, 
            newNodeKind(IdK, "s1", NULL, NULL, NULL)
, 
            newNodeKind(IdK, "i", NULL, NULL, NULL)
, NULL)
, 
          newNodeKind(IndexK, NULL, 
            newNodeKind(IdK, "s1", NULL, NULL, NULL)
, 
            newNodeKind(OperK, "+", 
              newNodeKind(IdK, "i", NULL, NULL, NULL)
, 
              newNodeKind(ConstIntK, "1", NULL, NULL, NULL)
, NULL)
, NULL)
, NULL)
, 
joinNode(
        newNodeKind(AssignK, "s", 
          newNodeKind(ConstSenteK, "", NULL, NULL, NULL)
, NULL, NULL)
, 
joinNode(
        newNodeKind(AssignK, "j", 
          newNodeKind(ConstIntK, "0", NULL, NULL, NULL)
, NULL, NULL)
, 
joinNode(
        newNodeKind(LoopK, NULL, 
          newNodeKind(IdK, "i", NULL, NULL, NULL)
, 
joinNode(
          newNodeKind(AssignK, "s", 
            newNodeKind(ConcatK, NULL, 
              newNodeKind(IdK, "s", NULL, NULL, NULL)
, 
              newNodeKind(IndexK, NULL, 
                newNodeKind(IdK, "s1", NULL, NULL, NULL)
, 
                newNodeKind(IdK, "j", NULL, NULL, NULL)
, NULL)
, NULL)
, NULL, NULL)
, 
          newNodeKind(AssignK, "j", 
            newNodeKind(OperK, "+", 
              newNodeKind(IdK, "j", NULL, NULL, NULL)
, 
              newNodeKind(ConstIntK, "1", NULL, NULL, NULL)
, NULL)
, NULL, NULL)
), NULL)
, 
joinNode(
        newNodeKind(AssignK, "s", 
          newNodeKind(ConcatK, NULL, 
            newNodeKind(IdK, "s", NULL, NULL, NULL)
, 
            newNodeKind(IndexK, NULL, 
              newNodeKind(IdK, "s1", NULL, NULL, NULL)
, 
              newNodeKind(OperK, "+", 
                newNodeKind(IdK, "i", NULL, NULL, NULL)
, 
                newNodeKind(ConstIntK, "1", NULL, NULL, NULL)
, NULL)
, NULL)
, NULL)
, NULL, NULL)
, 
joinNode(
        newNodeKind(AssignK, "s", 
          newNodeKind(ConcatK, NULL, 
            newNodeKind(IdK, "s", NULL, NULL, NULL)
, 
            newNodeKind(IndexK, NULL, 
              newNodeKind(IdK, "s1", NULL, NULL, NULL)
, 
              newNodeKind(IdK, "i", NULL, NULL, NULL)
, NULL)
, NULL)
, NULL, NULL)
, 
joinNode(
        newNodeKind(AssignK, "j", 
          newNodeKind(OperK, "+", 
            newNodeKind(IdK, "j", NULL, NULL, NULL)
, 
            newNodeKind(ConstIntK, "2", NULL, NULL, NULL)
, NULL)
, NULL, NULL)
, 
joinNode(
        newNodeKind(LoopK, NULL, 
          newNodeKind(OperK, "-", 
            newNodeKind(IdK, "count", NULL, NULL, NULL)
, 
            newNodeKind(IdK, "j", NULL, NULL, NULL)
, NULL)
, 
joinNode(
          newNodeKind(AssignK, "s", 
            newNodeKind(ConcatK, NULL, 
              newNodeKind(IdK, "s", NULL, NULL, NULL)
, 
              newNodeKind(IndexK, NULL, 
                newNodeKind(IdK, "s1", NULL, NULL, NULL)
, 
                newNodeKind(IdK, "j", NULL, NULL, NULL)
, NULL)
, NULL)
, NULL, NULL)
, 
          newNodeKind(AssignK, "j", 
            newNodeKind(OperK, "+", 
              newNodeKind(IdK, "j", NULL, NULL, NULL)
, 
              newNodeKind(ConstIntK, "1", NULL, NULL, NULL)
, NULL)
, NULL, NULL)
), NULL)
, 
        newNodeKind(AssignK, "s1", 
          newNodeKind(IdK, "s", NULL, NULL, NULL)
, NULL, NULL)
))))))), 
 NULL)
, 
      newNodeKind(AssignK, "i", 
        newNodeKind(OperK, "+", 
          newNodeKind(IdK, "i", NULL, NULL, NULL)
, 
          newNodeKind(ConstIntK, "1", NULL, NULL, NULL)
, NULL)
, NULL, NULL)
), NULL)
, 
    newNodeKind(AssignK, "count", 
      newNodeKind(OperK, "-", 
        newNodeKind(IdK, "count", NULL, NULL, NULL)
, 
        newNodeKind(ConstIntK, "1", NULL, NULL, NULL)
, NULL)
, NULL, NULL)
)), NULL)
, 
  newNodeKind(OutputK, NULL, 
    newNodeKind(IdK, "s1", NULL, NULL, NULL)
, NULL, NULL)
)))))))))))))))))))))))))))))));

executeTree(tree, 0, &listVars);
deleteIdScopeList(&listVars, 0);

return 0;
}
