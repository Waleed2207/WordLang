
#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHILDS 3
#define MAX_STR_LINE 150

//Types of Nodes
typedef enum {DeclK,AssignK,IdK,ConstIntK,ConstCharK,ConstWordK,ConstSenteK,IndexK,ConcatK,OperK,IfK,WhileK,LoopK,OperRelK,InputK,OutputK} NodeKind;

//Datatype
typedef enum {INT_TYPE, CHAR_TYPE, WORD_TYPE, SENTE_TYPE} Datatype;

//Struct for Variable information
typedef struct {
	int isOk;
	Datatype type;
	char *valStr;
	int valInt;
} InfoVar;

//Struct for Tree Nodes
typedef struct treeNode {
	struct treeNode *child[MAXCHILDS];
	struct treeNode *sibling;
	NodeKind nodekind;
	char *id;
	InfoVar info;
} StTreeNode;

//Struct for Scope List
typedef struct scopeList {
	struct scopeList *next;
	char *id;
	int scope;
	InfoVar info;
} StScopeList;


StTreeNode* newNodeKind(NodeKind kind, char *strId, StTreeNode *child1, StTreeNode *child2, StTreeNode *child3);
StTreeNode* joinNode(StTreeNode *tree, StTreeNode *nodeNew);
void printSpaces(FILE *out, int indentNro);
char* strJoin(const char *str1, const char *str2);
char* getStrSpaces(int numSpaces);
int varContainsChars(InfoVar *info);
int numberWords(char *str);
char* returnWord(char *sentence, int index);
char* splitStr(char *str1, char *str2);
void printTree(FILE *out, StTreeNode *tree, int indentNro);
void clearTree(StTreeNode **tree);
void executeTree(StTreeNode *tree, int scopeNro, StScopeList **list);
char* getTreeStr(StTreeNode *tree, int indentNro);
void generateCFile(FILE *out, StTreeNode *tree);

void insertIdScopeList(StScopeList **list, char *strType, char *strId, int scopeNro);
void deleteIdScopeList(StScopeList **list, int scopeNro);
int existIdScopeList(StScopeList *list, char *strId, InfoVar *infoVars);
int updateIdScopeList(StScopeList **list, char *strId, InfoVar infoVars);
void showScopeList(StScopeList *list);

#endif
