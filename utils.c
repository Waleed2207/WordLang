

#include "utils.h"

StTreeNode* newNodeKind(NodeKind kind, char *strId, StTreeNode *child1, StTreeNode *child2, StTreeNode *child3)
{
	StTreeNode *t = (StTreeNode*) malloc(sizeof(StTreeNode));

	if (t != NULL) {
		t->nodekind = kind;
		t->sibling = NULL;
		
		t->id = strId;
		
		t->child[0] = child1;
		t->child[1] = child2;
		t->child[2] = child3;
		
		t->info.valStr = NULL;

	} else {
	    printf("Out of memory error\n");
		exit(0);
	}
	return t;
}

StTreeNode* joinNode(StTreeNode *tree, StTreeNode *nodeNew)
{
	StTreeNode *ptrAux, *ptrRet;

	ptrAux = tree;
	if (ptrAux != NULL) {
		while (ptrAux->sibling != NULL) {
			ptrAux = ptrAux->sibling;
		}                            
		ptrAux->sibling = nodeNew;
		ptrRet = tree;
	} else {
		ptrRet = nodeNew;
	}

	return(ptrRet);
}

void printSpaces(FILE *out, int indentNro) {
	int i;
	for (i=0; i<indentNro; i++)
		fprintf(out," ");
}

char* strJoin(const char *str1, const char *str2) {
	char *strRet = malloc(sizeof(char) * (strlen(str1) + strlen(str2)) + 1);

	strRet[0] = '\0';

	strcat(strRet, str1);
	strcat(strRet, str2);

	return strRet;
}

char* getStrSpaces(int numSpaces) {
	char *str = (char*) malloc(sizeof(char) * (numSpaces + 1));
	int i;

	if(str != NULL) {
		for (i=0; i<numSpaces; i++) {
			str[i] = ' ';
		}
		str[numSpaces] = '\0';
	} else {
		printf("Error: Memory allocation.\n");
	}
	return str;
}

int varContainsChars(InfoVar *info)
{
	int result = 0;

	if(info->valStr != NULL) {
		result = 1;
	}
	
	return result;
}

int numberWords(char *str)
{
	char *ptr;
	int count = 0;

	/*ptr = strtok(str, " ");
	if(ptr != NULL) {
		count++;
	}

	while((ptr = strtok(NULL, " ")) != NULL) {
		count++;
	}*/
	
	if((str != NULL) && (str[0] != '\0')) {
		count = 1;
		ptr = str;
		while((ptr = strchr(ptr, ' ')) != NULL) {
			ptr++;
			if(ptr[0] != ' ') {
				count++;
			}
		}
	}
	
	return count;
}

char* returnWord(char *sentence, int index)
{
	char *ptr, *strRet = NULL;
	int lenthEnd, lenthStart, lenthTok;
		
	if((sentence != NULL) && (sentence[0] != '\0')) {
		lenthEnd = strlen(sentence);
		lenthStart = 0;
		ptr = sentence;
		
		while(((ptr = strchr(ptr, ' ')) != NULL) && (index >= 0)) {
			ptr++;
			if(ptr[0] != ' ') {
				lenthTok = lenthEnd - strlen(ptr);

				if(strRet != NULL) {
					free(strRet);
					strRet = NULL;
				}
				
				strRet = malloc(sizeof(char) * lenthTok);
				strncpy(strRet, sentence + lenthStart, lenthTok - 1);
				strRet[lenthTok - 1] = '\0';

				index--;
				lenthStart = lenthStart + lenthTok;
				lenthEnd = lenthEnd - lenthTok ;
			}
		}
		
		if(index >= 0) {
			lenthTok = lenthEnd + 1;
			if(strRet != NULL) {
				free(strRet);
				strRet = NULL;
			}
			
			strRet = malloc(sizeof(char) * lenthTok);
			strncpy(strRet, sentence + lenthStart, lenthTok - 1);
			strRet[lenthTok - 1] = '\0';
		}
	}

	if(strRet == NULL) {
		strRet = strJoin("", "");
	}
	
	return strRet;
}

char* splitStr(char *str1, char *str2)
{
	int lenthTok, i, contSpacExt = 0, j;
	char *strAux = NULL, *strPrev = NULL;
	char *strRet = NULL;

	if(strstr(str1, str2) != NULL) {
		lenthTok = strlen(str1) - strlen(strstr(str1, str2)) + 1;
		
		strPrev = malloc(sizeof(char) * lenthTok);
		strncpy(strPrev, str1, lenthTok - 1);
		strPrev[lenthTok - 1] = '\0';

		lenthTok =  strlen(str2) + (lenthTok - 1);
		strRet = strJoin(strPrev, str1 + lenthTok);

		if(strPrev != NULL) {
			free(strPrev);
			strPrev = NULL;
		}
		
		if(strRet[0] == ' ') {
			contSpacExt++;
		}
		
		if(strRet[strlen(strRet)-1] == ' ') {
			contSpacExt++;
		}
		
		strAux = strRet;
		while((strAux = strstr(strAux, "  ")) != NULL) {
			strAux++;
			contSpacExt++;
		}
		
		if(contSpacExt > 0) {
			strAux = malloc(sizeof(char) * (strlen(strRet) - contSpacExt + 1));
			j = 0;
			for(i = 0; i < strlen(strRet); i++) {
				if(((i != 0) || (strRet[i] != ' ')) && ((i == 0) || (strRet[i] != ' ') || ((strRet[i+1] != ' ') && (strRet[i+1] != '\0')))) {
					strAux[j] = strRet[i];
					j++;
				}
			}
			strAux[j] = '\0';
			
			if(strRet != NULL) {
				free(strRet);
				strRet = NULL;
			}
			strRet = strAux;
		}
	} else {
		strRet = strJoin("", "");
	}
	
	return strRet;
}

void printTree(FILE *out, StTreeNode *tree, int indentNro)
{
	int i;

	//Macro to Indent
	indentNro += 2;

	//Loop while tree is not null (No Children)
	while(tree != NULL) {

		printSpaces(out, indentNro);

		//Output based on Node Type
		switch(tree->nodekind) {
			case IdK:
				fprintf(out, "[Identifier \"%s\"]\n", tree->id);
				break;
			case ConstIntK:
				fprintf(out, "[Literal constant (int): (%s)]\n", tree->id);
				break;
			case ConstCharK:
				fprintf(out, "[Literal constant (char): \'%s\']\n", tree->id);
				break;
			case ConstWordK:
				fprintf(out, "[Literal constant (word): \"%s\"]\n", tree->id);
				break;
			case ConstSenteK:
				fprintf(out, "[Literal constant (sentence): ^%s^]\n", tree->id);
				break;
			case DeclK:
				fprintf(out, "[Declaration type (%s)]\n", tree->id);
				break;
			case AssignK:
				fprintf(out, "[Assignment: \"%s\"]\n", tree->id);
				//fprintf(out, "[Assignment]\n");
				break;
			case IndexK:
				//fprintf(out, "[Indexing: \"%s\"]\n", tree->id);
				fprintf(out, "[Indexing]\n");
				break;
			case ConcatK:
				fprintf(out, "[Concatenate]\n");
				break;
			case OperK:
				fprintf(out, "[Operator: \"%s\"]\n", tree->id);
				break;
			case IfK:
				fprintf(out, "[Conditional IF]\n");
				break;
			case WhileK:
				fprintf(out, "[Bucle WHILE]\n");
				break;
			case LoopK:
				fprintf(out, "[Bucle LOOP]\n");
				break;
			case OperRelK:
				fprintf(out, "[Operator Relat: \"%s\"]\n", tree->id);
				break;
			case InputK:
				fprintf(out, "[Input: \"%s\"]\n", tree->id);
				break;
			case OutputK:
				fprintf(out, "[Output]\n");
				break;
			default:
				fprintf(out, "<<<unknown node kind>>>\n");
		}

		for(i=0; i<MAXCHILDS; ++i)
			printTree(out, tree->child[i], indentNro);
		
		tree = tree->sibling;
	}

	indentNro -= 2;
}

void clearTree(StTreeNode **tree)
{
	int i;
	StTreeNode *auxNode = *tree, *oldNode;

	if(auxNode != NULL) {
		oldNode = auxNode;
		auxNode = auxNode->sibling;
		
		for(i=0; i<MAXCHILDS; ++i)
			clearTree(&(oldNode->child[i]));
		
		free(oldNode->id);
		if(oldNode->info.valStr != NULL) {
			free(oldNode->info.valStr);
			oldNode->info.valStr = NULL;
		}
		free(oldNode);
	}
	*tree = NULL;
}

void executeTree(StTreeNode *tree, int scopeNro, StScopeList **list)
{
	StTreeNode *t_aux;
	int i, maxElem;
	char *auxStr = NULL, input[MAX_STR_LINE];
	InfoVar infoVarsAux[3];

	scopeNro++;

	while(tree != NULL) {
		//Output based on Node Type
		switch(tree->nodekind) {
			case IdK:
				tree->info.isOk = 0;
				if(existIdScopeList(*list, tree->id, &(infoVarsAux[0]))) {
					tree->info = infoVarsAux[0];
					
					if(varContainsChars(&(tree->info))) {
						auxStr = tree->info.valStr;
						tree->info.valStr = strJoin(auxStr, "");
						tree->info.isOk = 1;
					}
				}
				break;
			case ConstIntK:
				tree->info.type = INT_TYPE;
				tree->info.valStr = NULL;
				tree->info.valInt = atoi(tree->id);
				tree->info.isOk = 1;
				break;
			case ConstCharK:
				tree->info.type = CHAR_TYPE;
				tree->info.valStr = NULL;
				tree->info.valInt = (tree->id)[0];
				tree->info.isOk = 1;
				break;
			case ConstWordK:
				tree->info.type = WORD_TYPE;
				tree->info.valStr = strJoin(tree->id, "");
				tree->info.valInt = strlen(tree->id);
				tree->info.isOk = 1;
				break;
			case ConstSenteK:
				tree->info.type = SENTE_TYPE;
				tree->info.valStr = strJoin(tree->id, "");
				tree->info.valInt = numberWords(tree->id);
				tree->info.isOk = 1;
				break;
			case DeclK:
				t_aux = tree->child[0];
				while(t_aux != NULL) {
					insertIdScopeList(list, tree->id, t_aux->id, scopeNro);
					t_aux = t_aux->sibling;
				}
				break;
			case AssignK:
				tree->info.isOk = 0;
				if(existIdScopeList(*list, tree->id, &(infoVarsAux[0]))) {
					executeTree(tree->child[0], scopeNro-1, list);
					t_aux = tree->child[0];
					infoVarsAux[1] = t_aux->info;
					
					if(infoVarsAux[0].type == infoVarsAux[1].type) {
						if((infoVarsAux[1].isOk == 1) && (updateIdScopeList(list, tree->id, infoVarsAux[1]))) {
							if(varContainsChars(&(tree->info))) {
								if(tree->info.valStr != NULL) {
									free(tree->info.valStr);
								}
								tree->info.valStr = NULL;
							}
							tree->info = infoVarsAux[1];

							if(varContainsChars(&(tree->info))) {
								auxStr = tree->info.valStr;
								tree->info.valStr = strJoin(auxStr, "");
								tree->info.isOk = 1;
							}
						}
					}
				}
				break;
			case IndexK:
				tree->info.isOk = 0;
				executeTree(tree->child[0], scopeNro-1, list);
				t_aux = tree->child[0];
				infoVarsAux[0] = t_aux->info;
				
				if((infoVarsAux[0].type != INT_TYPE) && (infoVarsAux[0].isOk == 1)) {
					executeTree(tree->child[1], scopeNro-1, list);
					t_aux = tree->child[1];
					infoVarsAux[1] = t_aux->info;
					
					switch(infoVarsAux[0].type) {
						case SENTE_TYPE:
							tree->info.type = WORD_TYPE;
							if((infoVarsAux[1].valInt >= 0) && (infoVarsAux[1].valInt < infoVarsAux[0].valInt)) {
								tree->info.valStr = returnWord(infoVarsAux[0].valStr, infoVarsAux[1].valInt);
							} else if((infoVarsAux[1].valInt < 0) && ((-1 * infoVarsAux[1].valInt) <= infoVarsAux[0].valInt)) {
								tree->info.valStr = returnWord(infoVarsAux[0].valStr, (infoVarsAux[0].valInt + infoVarsAux[1].valInt));
							} else {
								tree->info.valStr = strJoin("", "");
							}
							tree->info.valInt = strlen(tree->info.valStr);
							tree->info.isOk = 1;
							break;
						case WORD_TYPE:
							tree->info.type = CHAR_TYPE;
							tree->info.valStr = NULL;
							tree->info.valInt = 0;
							if((infoVarsAux[1].valInt >= 0) && (infoVarsAux[1].valInt < infoVarsAux[0].valInt)) {
								tree->info.valInt = (infoVarsAux[0].valStr)[infoVarsAux[1].valInt];
							} else if((infoVarsAux[1].valInt < 0) && ((-1 * infoVarsAux[1].valInt) <= infoVarsAux[0].valInt)) {
								tree->info.valInt = (infoVarsAux[0].valStr)[(infoVarsAux[0].valInt + infoVarsAux[1].valInt)];
							}
							tree->info.isOk = 1;
							break;
						case CHAR_TYPE:
							tree->info.type = CHAR_TYPE;
							tree->info.valStr = NULL;
							tree->info.valInt = ((infoVarsAux[1].valInt == 0) || (infoVarsAux[1].valInt == -1)) ? infoVarsAux[0].valInt : 0;
							tree->info.isOk = 1;
							break;
					}
				}
				break;
			case ConcatK:
				tree->info.isOk = 0;
				executeTree(tree->child[0], scopeNro-1, list);
				t_aux = tree->child[0];
				infoVarsAux[0] = t_aux->info;
				
				executeTree(tree->child[1], scopeNro-1, list);
				t_aux = tree->child[1];
				infoVarsAux[1] = t_aux->info;
				
				if((infoVarsAux[0].isOk == 1) && (infoVarsAux[1].isOk == 1) && (infoVarsAux[0].type != INT_TYPE) && (infoVarsAux[1].type != INT_TYPE)) {
					
					if((infoVarsAux[0].type == SENTE_TYPE) || (infoVarsAux[1].type == SENTE_TYPE)) {
						infoVarsAux[2].type = SENTE_TYPE;
						if(infoVarsAux[0].type == SENTE_TYPE) {
							//auxStr = strJoin(infoVarsAux[0].valStr, "");
							infoVarsAux[2].valInt = infoVarsAux[0].valInt;
							
							if(infoVarsAux[1].valInt > 0) {
								//auxStr = strJoin(infoVarsAux[0].valStr, " ");
								switch(infoVarsAux[1].type) {
									case SENTE_TYPE:
										if(infoVarsAux[0].valInt > 0) {
											auxStr = strJoin(infoVarsAux[0].valStr, " ");
										} else {
											auxStr = strJoin(infoVarsAux[0].valStr, "");
										}
										infoVarsAux[2].valStr = strJoin(auxStr, infoVarsAux[1].valStr);
										infoVarsAux[2].valInt += infoVarsAux[1].valInt;
										break;
									case WORD_TYPE:
										if(infoVarsAux[0].valInt > 0) {
											auxStr = strJoin(infoVarsAux[0].valStr, " ");
										} else {
											auxStr = strJoin(infoVarsAux[0].valStr, "");
										}
										infoVarsAux[2].valStr = strJoin(auxStr, infoVarsAux[1].valStr);
										infoVarsAux[2].valInt += 1;
										break;
									case CHAR_TYPE:
										auxStr = strJoin(infoVarsAux[0].valStr, " ");
										auxStr[strlen(auxStr)-1] = infoVarsAux[1].valInt;
										infoVarsAux[2].valStr = auxStr;
										break;
								}
							} else {
								infoVarsAux[2].valStr = strJoin(infoVarsAux[0].valStr, "");
							}
						} else {
							infoVarsAux[2].valInt = infoVarsAux[1].valInt;
							
							if(infoVarsAux[0].valInt > 0) {								
								switch(infoVarsAux[0].type) {
									case WORD_TYPE:
										if(infoVarsAux[1].valInt > 0) {
											auxStr = strJoin(infoVarsAux[0].valStr, " ");
											infoVarsAux[2].valStr = strJoin(auxStr, infoVarsAux[1].valStr);
										} else {
											infoVarsAux[2].valStr = strJoin(infoVarsAux[0].valStr, "");
										}
										infoVarsAux[2].valInt += 1;
										break;
									case CHAR_TYPE:
										auxStr = strJoin(" ", "");
										auxStr[0] = infoVarsAux[0].valInt;
										if(infoVarsAux[1].valInt > 0) {
											infoVarsAux[2].valStr = strJoin(auxStr, infoVarsAux[1].valStr);
										} else {
											infoVarsAux[2].valStr = auxStr;
											infoVarsAux[2].valInt += 1;
										}
										break;
								}
							} else {
								infoVarsAux[2].valStr = strJoin(infoVarsAux[1].valStr, "");
							}
						}
					} else if((infoVarsAux[0].type == WORD_TYPE) || (infoVarsAux[1].type == WORD_TYPE)) {
						infoVarsAux[2].type = WORD_TYPE;
						if(infoVarsAux[0].type == WORD_TYPE) {
							infoVarsAux[2].valInt = infoVarsAux[0].valInt;
							
							if(infoVarsAux[1].valInt > 0) {								
								switch(infoVarsAux[1].type) {
									case WORD_TYPE:
										if(infoVarsAux[0].valInt > 0) {
											auxStr = strJoin(infoVarsAux[0].valStr, "");
											infoVarsAux[2].valStr = strJoin(auxStr, infoVarsAux[1].valStr);
										} else {
											infoVarsAux[2].valStr = strJoin(infoVarsAux[1].valStr, "");
										}
										infoVarsAux[2].valInt += infoVarsAux[1].valInt;
										break;
									case CHAR_TYPE:
										if(infoVarsAux[0].valInt > 0) {
											auxStr = strJoin(infoVarsAux[0].valStr, " ");
											auxStr[strlen(auxStr)-1] = infoVarsAux[1].valInt;
											infoVarsAux[2].valStr = auxStr;
										} else {
											auxStr = strJoin(" ", "");
											auxStr[0] = infoVarsAux[1].valInt;
											infoVarsAux[2].valStr = auxStr;
										}
										infoVarsAux[2].valInt += 1;
										break;
								}
							} else {
								infoVarsAux[2].valStr = strJoin(infoVarsAux[0].valStr, "");
							}
						} else {
							infoVarsAux[2].valInt = infoVarsAux[1].valInt;
							
							if(infoVarsAux[0].valInt > 0) {		
								auxStr = strJoin(" ", "");
								auxStr[0] = infoVarsAux[0].valInt;						
								if(infoVarsAux[1].valInt > 0) {
									infoVarsAux[2].valStr = strJoin(auxStr, infoVarsAux[1].valStr);
								} else {
									infoVarsAux[2].valStr = auxStr;
								}
								infoVarsAux[2].valInt += 1;
							} else {
								infoVarsAux[2].valStr = strJoin(infoVarsAux[1].valStr, "");
							}
						}
					} else {
						infoVarsAux[2].type = WORD_TYPE;
						infoVarsAux[2].valInt = 0;

						if(infoVarsAux[0].valInt > 0) {		
							auxStr = strJoin(" ", "");
							auxStr[0] = infoVarsAux[0].valInt;
							infoVarsAux[2].valInt += 1;				
							if(infoVarsAux[1].valInt > 0) {
								infoVarsAux[2].valStr = strJoin(auxStr, " ");
								infoVarsAux[2].valStr[1] = infoVarsAux[1].valInt;
								infoVarsAux[2].valInt += 1;
							} else {
								infoVarsAux[2].valStr = auxStr;
							}
						} else {				
							if(infoVarsAux[1].valInt > 0) {
								infoVarsAux[2].valStr = strJoin(" ", "");
								infoVarsAux[2].valStr[0] = infoVarsAux[1].valInt;
								infoVarsAux[2].valInt += 1;
							} else {
								infoVarsAux[2].valStr = strJoin("", "");
							}
						}
					}
					infoVarsAux[2].isOk = 1;

					if(varContainsChars(&(infoVarsAux[2]))) {
						auxStr = infoVarsAux[2].valStr;
						infoVarsAux[2].valStr = strJoin(auxStr, "");
						free(auxStr);
					}
					
					if(infoVarsAux[2].isOk == 1) {
						tree->info = infoVarsAux[2];
						//printf("\tType=(%d) ValInt=(%d) ValStr=(%s)\n", infoVarsAux[2].type, infoVarsAux[2].valInt, infoVarsAux[2].valStr);FSILVA0026
					}
					tree->info.isOk = 1;
				}
				break;
			case OperK:
				tree->info.isOk = 0;
				executeTree(tree->child[0], scopeNro-1, list);
				t_aux = tree->child[0];
				infoVarsAux[0] = t_aux->info;
				
				executeTree(tree->child[1], scopeNro-1, list);
				t_aux = tree->child[1];
				infoVarsAux[1] = t_aux->info;
				
				if((infoVarsAux[0].isOk == 1) && (infoVarsAux[1].isOk == 1)) {
					if(strcmp(tree->id, "-") == 0) {
						if((infoVarsAux[0].type == INT_TYPE) && (infoVarsAux[1].type == INT_TYPE)) {
							infoVarsAux[2] = infoVarsAux[0];
							infoVarsAux[2].valInt -= infoVarsAux[1].valInt;
							infoVarsAux[2].isOk = 1;
						} else if((infoVarsAux[0].type != INT_TYPE) && (infoVarsAux[1].type != INT_TYPE)) {
							infoVarsAux[2] = infoVarsAux[0];
							if((infoVarsAux[0].valInt > 0) && (infoVarsAux[1].valInt > 0)) {
								switch(infoVarsAux[0].type) {
									case SENTE_TYPE:
										if(infoVarsAux[1].type != CHAR_TYPE) {
											infoVarsAux[2].valStr = splitStr(infoVarsAux[0].valStr, infoVarsAux[1].valStr);
										} else {
											auxStr = strJoin(" ", "");
											auxStr[0] = infoVarsAux[1].valInt;
											infoVarsAux[2].valStr = splitStr(infoVarsAux[0].valStr, auxStr);	
										}
										infoVarsAux[2].valInt = numberWords(infoVarsAux[2].valStr);
										break;
									case WORD_TYPE:
										if(infoVarsAux[1].type != CHAR_TYPE) {
											infoVarsAux[2].valStr = splitStr(infoVarsAux[0].valStr, infoVarsAux[1].valStr);
										} else {
											auxStr = strJoin(" ", "");
											auxStr[0] = infoVarsAux[1].valInt;
											infoVarsAux[2].valStr = splitStr(infoVarsAux[0].valStr, auxStr);	
										}
										infoVarsAux[2].valInt = strlen(infoVarsAux[2].valStr);
										break;
									case CHAR_TYPE:
										if(infoVarsAux[1].type != CHAR_TYPE) {
											auxStr = infoVarsAux[1].valStr;
											if(auxStr[0] == infoVarsAux[0].valInt) {
												infoVarsAux[2].valInt = 0;
											}
										} else {
											if(infoVarsAux[0].valInt == infoVarsAux[1].valInt) {
												infoVarsAux[2].valInt = 0;
											}	
										}
										break;
								}
								infoVarsAux[2].isOk = 1;
							}
						}
					} else {
						if((infoVarsAux[0].type == INT_TYPE) && (infoVarsAux[1].type == INT_TYPE)) {
							infoVarsAux[2] = infoVarsAux[0];
							infoVarsAux[2].valInt += infoVarsAux[1].valInt;
							infoVarsAux[2].isOk = 1;
						}
					}

					if(varContainsChars(&(infoVarsAux[2]))) {
						auxStr = infoVarsAux[2].valStr;
						infoVarsAux[2].valStr = strJoin(auxStr, "");
						free(auxStr);
					}
					
					if(infoVarsAux[2].isOk == 1) {
						tree->info = infoVarsAux[2];
					}
				}
				break;
			case IfK:
				executeTree(tree->child[0], scopeNro, list);
				t_aux = tree->child[0];

				if(t_aux->info.isOk == 1) {
					if(t_aux->info.valInt == 1) {
						executeTree(tree->child[1], scopeNro, list);
					} else {
						executeTree(tree->child[2], scopeNro, list);
					}
				}
				break;
			case WhileK:
				executeTree(tree->child[0], scopeNro, list);
				t_aux = tree->child[0];

				if(t_aux->info.isOk == 1) {
					while(t_aux->info.valInt == 1) {
						executeTree(tree->child[1], scopeNro, list);
						deleteIdScopeList(list, scopeNro);

						executeTree(tree->child[0], scopeNro, list);
						t_aux = tree->child[0];
					}
				}
				break;
			case LoopK:
				executeTree(tree->child[0], scopeNro, list);
				t_aux = tree->child[0];
				if((t_aux->info.isOk == 1) && (t_aux->info.type == INT_TYPE)) {
					maxElem = t_aux->info.valInt;
					for(i = 1; i <= maxElem; i++) {
						executeTree(tree->child[1], scopeNro, list);
						deleteIdScopeList(list, scopeNro);
					}
				}
				break;
			case OperRelK:
				tree->info.isOk = 0;
				executeTree(tree->child[0], scopeNro-1, list);
				t_aux = tree->child[0];
				infoVarsAux[0] = t_aux->info;
				
				if((strcmp(tree->id, "!") != 0) && (strcmp(tree->id, "eval") != 0)) {
					executeTree(tree->child[1], scopeNro-1, list);
					t_aux = tree->child[1];
					infoVarsAux[1] = t_aux->info;
				} else {
					infoVarsAux[1].isOk = 1;
				}

				if((infoVarsAux[0].isOk == 1) && (infoVarsAux[1].isOk == 1)) {
					if(strcmp(tree->id, "<") == 0) {
						if(((infoVarsAux[0].type == INT_TYPE) || (infoVarsAux[0].type == CHAR_TYPE)) &&
						  ((infoVarsAux[1].type == INT_TYPE) || (infoVarsAux[1].type == CHAR_TYPE))) {
							infoVarsAux[2].valInt = (infoVarsAux[0].valInt < infoVarsAux[1].valInt);
							infoVarsAux[2].isOk = 1;
						} else if((infoVarsAux[0].type == CHAR_TYPE) &&
						  ((infoVarsAux[1].type == WORD_TYPE) || (infoVarsAux[1].type == SENTE_TYPE))) {
							auxStr = strJoin(" ", "");
							auxStr[0] = infoVarsAux[0].valInt;

							infoVarsAux[2].valInt = (strcmp(auxStr, infoVarsAux[1].valStr) < 0);
							infoVarsAux[2].isOk = 1;
						} else if((infoVarsAux[1].type == CHAR_TYPE) &&
						  ((infoVarsAux[0].type == WORD_TYPE) || (infoVarsAux[0].type == SENTE_TYPE))) {
							auxStr = strJoin(" ", "");
							auxStr[0] = infoVarsAux[1].valInt;

							infoVarsAux[2].valInt = (strcmp(infoVarsAux[0].valStr, auxStr) < 0);
							infoVarsAux[2].isOk = 1;
						} else if(((infoVarsAux[0].type == WORD_TYPE) || (infoVarsAux[0].type == SENTE_TYPE)) &&
						  ((infoVarsAux[1].type == WORD_TYPE) || (infoVarsAux[1].type == SENTE_TYPE))) {
							infoVarsAux[2].valInt = (strcmp(infoVarsAux[0].valStr, infoVarsAux[1].valStr) < 0);
							infoVarsAux[2].isOk = 1;
						}
					} else if(strcmp(tree->id, ">") == 0) {
						if(((infoVarsAux[0].type == INT_TYPE) || (infoVarsAux[0].type == CHAR_TYPE)) &&
						  ((infoVarsAux[1].type == INT_TYPE) || (infoVarsAux[1].type == CHAR_TYPE))) {
							infoVarsAux[2].valInt = (infoVarsAux[0].valInt > infoVarsAux[1].valInt);
							infoVarsAux[2].isOk = 1;
						} else if((infoVarsAux[0].type == CHAR_TYPE) &&
						  ((infoVarsAux[1].type == WORD_TYPE) || (infoVarsAux[1].type == SENTE_TYPE))) {
							auxStr = strJoin(" ", "");
							auxStr[0] = infoVarsAux[0].valInt;

							infoVarsAux[2].valInt = (strcmp(auxStr, infoVarsAux[1].valStr) > 0);
							infoVarsAux[2].isOk = 1;
						} else if((infoVarsAux[1].type == CHAR_TYPE) &&
						  ((infoVarsAux[0].type == WORD_TYPE) || (infoVarsAux[0].type == SENTE_TYPE))) {
							auxStr = strJoin(" ", "");
							auxStr[0] = infoVarsAux[1].valInt;

							infoVarsAux[2].valInt = (strcmp(infoVarsAux[0].valStr, auxStr) > 0);
							infoVarsAux[2].isOk = 1;
						} else if(((infoVarsAux[0].type == WORD_TYPE) || (infoVarsAux[0].type == SENTE_TYPE)) &&
						  ((infoVarsAux[1].type == WORD_TYPE) || (infoVarsAux[1].type == SENTE_TYPE))) {
							infoVarsAux[2].valInt = (strcmp(infoVarsAux[0].valStr, infoVarsAux[1].valStr) > 0);
							infoVarsAux[2].isOk = 1;
						}
					} else if(strcmp(tree->id, "==") == 0) {
						if(((infoVarsAux[0].type == INT_TYPE) || (infoVarsAux[0].type == CHAR_TYPE)) &&
						  ((infoVarsAux[1].type == INT_TYPE) || (infoVarsAux[1].type == CHAR_TYPE))) {
							infoVarsAux[2].valInt = (infoVarsAux[0].valInt == infoVarsAux[1].valInt);
							infoVarsAux[2].isOk = 1;
						} else if((infoVarsAux[0].type == CHAR_TYPE) &&
						  ((infoVarsAux[1].type == WORD_TYPE) || (infoVarsAux[1].type == SENTE_TYPE))) {
							auxStr = strJoin(" ", "");
							auxStr[0] = infoVarsAux[0].valInt;

							infoVarsAux[2].valInt = (strcmp(auxStr, infoVarsAux[1].valStr) == 0);
							infoVarsAux[2].isOk = 1;
						} else if((infoVarsAux[1].type == CHAR_TYPE) &&
						  ((infoVarsAux[0].type == WORD_TYPE) || (infoVarsAux[0].type == SENTE_TYPE))) {
							auxStr = strJoin(" ", "");
							auxStr[0] = infoVarsAux[1].valInt;

							infoVarsAux[2].valInt = (strcmp(infoVarsAux[0].valStr, auxStr) == 0);
							infoVarsAux[2].isOk = 1;
						} else if(((infoVarsAux[0].type == WORD_TYPE) || (infoVarsAux[0].type == SENTE_TYPE)) &&
						  ((infoVarsAux[1].type == WORD_TYPE) || (infoVarsAux[1].type == SENTE_TYPE))) {
							infoVarsAux[2].valInt = (strcmp(infoVarsAux[0].valStr, infoVarsAux[1].valStr) == 0);
							infoVarsAux[2].isOk = 1;
						}
					} else if(strcmp(tree->id, "!=") == 0) {
						if(((infoVarsAux[0].type == INT_TYPE) || (infoVarsAux[0].type == CHAR_TYPE)) &&
						  ((infoVarsAux[1].type == INT_TYPE) || (infoVarsAux[1].type == CHAR_TYPE))) {
							infoVarsAux[2].valInt = (infoVarsAux[0].valInt != infoVarsAux[1].valInt);
							infoVarsAux[2].isOk = 1;
						} else if((infoVarsAux[0].type == CHAR_TYPE) &&
						  ((infoVarsAux[1].type == WORD_TYPE) || (infoVarsAux[1].type == SENTE_TYPE))) {
							auxStr = strJoin(" ", "");
							auxStr[0] = infoVarsAux[0].valInt;

							infoVarsAux[2].valInt = (strcmp(auxStr, infoVarsAux[1].valStr) != 0);
							infoVarsAux[2].isOk = 1;
						} else if((infoVarsAux[1].type == CHAR_TYPE) &&
						  ((infoVarsAux[0].type == WORD_TYPE) || (infoVarsAux[0].type == SENTE_TYPE))) {
							auxStr = strJoin(" ", "");
							auxStr[0] = infoVarsAux[1].valInt;

							infoVarsAux[2].valInt = (strcmp(infoVarsAux[0].valStr, auxStr) != 0);
							infoVarsAux[2].isOk = 1;
						} else if(((infoVarsAux[0].type == WORD_TYPE) || (infoVarsAux[0].type == SENTE_TYPE)) &&
						  ((infoVarsAux[1].type == WORD_TYPE) || (infoVarsAux[1].type == SENTE_TYPE))) {
							infoVarsAux[2].valInt = (strcmp(infoVarsAux[0].valStr, infoVarsAux[1].valStr) != 0);
							infoVarsAux[2].isOk = 1;
						}
					} else if(strcmp(tree->id, "<=") == 0) {
						if(((infoVarsAux[0].type == INT_TYPE) || (infoVarsAux[0].type == CHAR_TYPE)) &&
						  ((infoVarsAux[1].type == INT_TYPE) || (infoVarsAux[1].type == CHAR_TYPE))) {
							infoVarsAux[2].valInt = (infoVarsAux[0].valInt <= infoVarsAux[1].valInt);
							infoVarsAux[2].isOk = 1;
						} else if((infoVarsAux[0].type == CHAR_TYPE) &&
						  ((infoVarsAux[1].type == WORD_TYPE) || (infoVarsAux[1].type == SENTE_TYPE))) {
							auxStr = strJoin(" ", "");
							auxStr[0] = infoVarsAux[0].valInt;

							infoVarsAux[2].valInt = (strcmp(auxStr, infoVarsAux[1].valStr) <= 0);
							infoVarsAux[2].isOk = 1;
						} else if((infoVarsAux[1].type == CHAR_TYPE) &&
						  ((infoVarsAux[0].type == WORD_TYPE) || (infoVarsAux[0].type == SENTE_TYPE))) {
							auxStr = strJoin(" ", "");
							auxStr[0] = infoVarsAux[1].valInt;

							infoVarsAux[2].valInt = (strcmp(infoVarsAux[0].valStr, auxStr) <= 0);
							infoVarsAux[2].isOk = 1;
						} else if(((infoVarsAux[0].type == WORD_TYPE) || (infoVarsAux[0].type == SENTE_TYPE)) &&
						  ((infoVarsAux[1].type == WORD_TYPE) || (infoVarsAux[1].type == SENTE_TYPE))) {
							infoVarsAux[2].valInt = (strcmp(infoVarsAux[0].valStr, infoVarsAux[1].valStr) <= 0);
							infoVarsAux[2].isOk = 1;
						}
					} else if(strcmp(tree->id, ">=") == 0) {
						if(((infoVarsAux[0].type == INT_TYPE) || (infoVarsAux[0].type == CHAR_TYPE)) &&
						  ((infoVarsAux[1].type == INT_TYPE) || (infoVarsAux[1].type == CHAR_TYPE))) {
							infoVarsAux[2].valInt = (infoVarsAux[0].valInt >= infoVarsAux[1].valInt);
							infoVarsAux[2].isOk = 1;
						} else if((infoVarsAux[0].type == CHAR_TYPE) &&
						  ((infoVarsAux[1].type == WORD_TYPE) || (infoVarsAux[1].type == SENTE_TYPE))) {
							auxStr = strJoin(" ", "");
							auxStr[0] = infoVarsAux[0].valInt;

							infoVarsAux[2].valInt = (strcmp(auxStr, infoVarsAux[1].valStr) >= 0);
							infoVarsAux[2].isOk = 1;
						} else if((infoVarsAux[1].type == CHAR_TYPE) &&
						  ((infoVarsAux[0].type == WORD_TYPE) || (infoVarsAux[0].type == SENTE_TYPE))) {
							auxStr = strJoin(" ", "");
							auxStr[0] = infoVarsAux[1].valInt;

							infoVarsAux[2].valInt = (strcmp(infoVarsAux[0].valStr, auxStr) >= 0);
							infoVarsAux[2].isOk = 1;
						} else if(((infoVarsAux[0].type == WORD_TYPE) || (infoVarsAux[0].type == SENTE_TYPE)) &&
						  ((infoVarsAux[1].type == WORD_TYPE) || (infoVarsAux[1].type == SENTE_TYPE))) {
							infoVarsAux[2].valInt = (strcmp(infoVarsAux[0].valStr, infoVarsAux[1].valStr) >= 0);
							infoVarsAux[2].isOk = 1;
						}
					} else if(strcmp(tree->id, "!") == 0) {
						if((infoVarsAux[0].type == INT_TYPE) || (infoVarsAux[0].type == CHAR_TYPE) ||
						  (infoVarsAux[0].type == WORD_TYPE) || (infoVarsAux[0].type == SENTE_TYPE)) {
							infoVarsAux[2].valInt = !(infoVarsAux[0].valInt);
							infoVarsAux[2].isOk = 1;
						}
					} else if(strcmp(tree->id, "eval") == 0) {
						if((infoVarsAux[0].type == INT_TYPE) || (infoVarsAux[0].type == CHAR_TYPE) ||
						  (infoVarsAux[0].type == WORD_TYPE) || (infoVarsAux[0].type == SENTE_TYPE)) {
							infoVarsAux[2].valInt = (infoVarsAux[0].valInt != 0);
							infoVarsAux[2].isOk = 1;
						}
					}
					
					if(infoVarsAux[2].isOk == 1) {
						infoVarsAux[2].type = INT_TYPE;
						infoVarsAux[2].valStr = NULL;
						tree->info = infoVarsAux[2];
					}
				}
				break;
			case InputK:
				tree->info.isOk = 0;
				if(existIdScopeList(*list, tree->id, &(infoVarsAux[0]))) {
					executeTree(tree->child[0], scopeNro-1, list);
					t_aux = tree->child[0];
					infoVarsAux[1] = t_aux->info;
					
					if(infoVarsAux[1].isOk == 1) {
						switch(infoVarsAux[1].type) {
							case INT_TYPE:
								printf("%d ", infoVarsAux[1].valInt);
								break;
							case CHAR_TYPE:
								printf("%c ", infoVarsAux[1].valInt);
								break;
							case WORD_TYPE:
							case SENTE_TYPE:
								printf("%s ", infoVarsAux[1].valStr);
								break;
						}

						if(fgets(input, MAX_STR_LINE, stdin) != NULL) {
							input[strlen(input)-1]='\0';
							switch(infoVarsAux[0].type) {
								case INT_TYPE:
									infoVarsAux[0].valInt = atoi(input);
									infoVarsAux[0].isOk = 1;
									break;
								case CHAR_TYPE:
									infoVarsAux[0].valInt = input[0];
									infoVarsAux[0].isOk = 1;
									break;
								case WORD_TYPE:
									infoVarsAux[0].valStr = strJoin(input, "");
									infoVarsAux[0].valInt = strlen(input);
									infoVarsAux[0].isOk = 1;
									break;
								case SENTE_TYPE:
									infoVarsAux[0].valStr = strJoin(input, "");
									infoVarsAux[0].valInt = numberWords(input);
									infoVarsAux[0].isOk = 1;
									break;
							}

							if(updateIdScopeList(list, tree->id, infoVarsAux[0])) {
								if(varContainsChars(&(tree->info))) {
									if(tree->info.valStr != NULL) {
										free(tree->info.valStr);
									}
									tree->info.valStr = NULL;
								}
								tree->info = infoVarsAux[0];

								if(varContainsChars(&(tree->info))) {
									auxStr = tree->info.valStr;
									tree->info.valStr = strJoin(auxStr, "");
									tree->info.isOk = 1;
								}
							}
						}
					}
				}
				//tree->info.isOk = 1;
				break;
			case OutputK:
				tree->info.isOk = 0;
				executeTree(tree->child[0], scopeNro-1, list);
				t_aux = tree->child[0];
				infoVarsAux[0] = t_aux->info;
				
				if(infoVarsAux[0].isOk == 1) {
					switch(infoVarsAux[0].type) {
						case INT_TYPE:
							printf("%d ", infoVarsAux[0].valInt);
							break;
						case CHAR_TYPE:
							printf("%c ", infoVarsAux[0].valInt);
							break;
						case WORD_TYPE:
						case SENTE_TYPE:
							printf("%s ", infoVarsAux[0].valStr);
							break;
					}
				}
				printf("\n");
				tree->info.isOk = 1;
				break;
		}
		
		tree = tree->sibling;
	}

	scopeNro--;
}

char* getTreeStr(StTreeNode *tree, int indentNro)
{
	char *valRet, *valNode, auxArr[MAX_STR_LINE];
	char *auxStr1, *auxStr2, *auxStr3, *auxStr4, *auxStr5;
	char *strSpaces;

	//Macro to Indent
	indentNro += 2;

	//If tree is not null (No Children)
	if(tree != NULL) {

		//printSpaces(out, indentNro);
		strSpaces = getStrSpaces(indentNro);

		//Output based on Node Type
		switch(tree->nodekind) {
			case IdK:
				//fprintf(out, " \"newNodeKind(IdK, %s, NULL, NULL, NULL);\" \n", tree->id);
				sprintf(auxArr, "%snewNodeKind(IdK, \"%s\", NULL, NULL, NULL)\n", strSpaces, tree->id);
				valNode = strJoin("", auxArr);
				break;
			case ConstIntK:
				//fprintf(out, " \"newNodeKind(ConstIntK, %s, NULL, NULL, NULL);\" \n", tree->id);
				sprintf(auxArr, "%snewNodeKind(ConstIntK, \"%s\", NULL, NULL, NULL)\n", strSpaces, tree->id);
				valNode = strJoin("", auxArr);
				break;
			case ConstCharK:
				//fprintf(out, " \"newNodeKind(ConstCharK, %s, NULL, NULL, NULL);\" \n", tree->id);
				sprintf(auxArr, "%snewNodeKind(ConstCharK, \"%s\", NULL, NULL, NULL)\n", strSpaces, tree->id);
				valNode = strJoin("", auxArr);
				break;
			case ConstWordK:
				//fprintf(out, " \"newNodeKind(ConstWordK, %s, NULL, NULL, NULL);\" \n", tree->id);
				sprintf(auxArr, "%snewNodeKind(ConstWordK, \"%s\", NULL, NULL, NULL)\n", strSpaces, tree->id);
				valNode = strJoin("", auxArr);
				break;
			case ConstSenteK:
				//fprintf(out, " \"newNodeKind(ConstSenteK, %s, NULL, NULL, NULL);\" \n", tree->id);
				sprintf(auxArr, "%snewNodeKind(ConstSenteK, \"%s\", NULL, NULL, NULL)\n", strSpaces, tree->id);
				valNode = strJoin("", auxArr);
				break;
			case DeclK:
				//fprintf(out, "[Declaration]\n");
				//fprintf(out, " \"newNodeKind(DeclK, %s, NULL, NULL, NULL);\" \n", tree->id);
				sprintf(auxArr, "%snewNodeKind(DeclK, \"%s\", \n", strSpaces, tree->id);
				auxStr1 = strJoin(auxArr, getTreeStr(tree->child[0], indentNro));
				valNode = strJoin(auxStr1, ", NULL, NULL)\n");
				if(auxStr1 != NULL) {
					free(auxStr1);
					auxStr1 = NULL;
				}
				break;
			case AssignK:
				//fprintf(out, "[Assignation: \"%s\"]\n", tree->id);
				//fprintf(out, "[Assignation]\n");
				//fprintf(out, " \"newNodeKind(AssignK, \"%s\", NULL, NULL);\" \n", tree->id);
				sprintf(auxArr, "%snewNodeKind(AssignK, \"%s\", \n", strSpaces, tree->id);
				auxStr1 = strJoin(auxArr, getTreeStr(tree->child[0], indentNro));
				valNode = strJoin(auxStr1, ", NULL, NULL)\n");
				if(auxStr1 != NULL) {
					free(auxStr1);
					auxStr1 = NULL;
				}
				break;
			case IndexK:
				//fprintf(out, "[Indexation]\n");
				//fprintf(out, " \"newNodeKind(IndexK, NULL, NULL, NULL, NULL);\" \n");
				sprintf(auxArr, "%snewNodeKind(IndexK, NULL, \n", strSpaces);
				auxStr1 = strJoin(auxArr, getTreeStr(tree->child[0], indentNro));
				auxStr2 = strJoin(auxStr1, ", \n");
				auxStr3 = strJoin(auxStr2, getTreeStr(tree->child[1], indentNro));
				valNode = strJoin(auxStr3, ", NULL)\n");
				if(auxStr1 != NULL) {
					free(auxStr1);
					auxStr1 = NULL;
				}
				if(auxStr2 != NULL) {
					free(auxStr2);
					auxStr2 = NULL;
				}
				if(auxStr3 != NULL) {
					free(auxStr3);
					auxStr3 = NULL;
				}
				break;
			case ConcatK:
				//fprintf(out, "[Concatenate]\n");
				//fprintf(out, " \"newNodeKind(ConcatK, NULL, NULL, NULL);\" \n");
				sprintf(auxArr, "%snewNodeKind(ConcatK, NULL, \n", strSpaces);
				auxStr1 = strJoin(auxArr, getTreeStr(tree->child[0], indentNro));
				auxStr2 = strJoin(auxStr1, ", \n");
				auxStr3 = strJoin(auxStr2, getTreeStr(tree->child[1], indentNro));
				valNode = strJoin(auxStr3, ", NULL)\n");
				if(auxStr1 != NULL) {
					free(auxStr1);
					auxStr1 = NULL;
				}
				if(auxStr2 != NULL) {
					free(auxStr2);
					auxStr2 = NULL;
				}
				if(auxStr3 != NULL) {
					free(auxStr3);
					auxStr3 = NULL;
				}
				break;
			case OperK:
				//printf(out, "[Operator: \"%s\"]\n", tree->id);
				//fprintf(out, " \"newNodeKind(OperK, %s, NULL, NULL, NULL);\" \n", tree->id);
				sprintf(auxArr, "%snewNodeKind(OperK, \"%s\", \n", strSpaces, tree->id);
				auxStr1 = strJoin(auxArr, getTreeStr(tree->child[0], indentNro));
				auxStr2 = strJoin(auxStr1, ", \n");
				auxStr3 = strJoin(auxStr2, getTreeStr(tree->child[1], indentNro));
				valNode = strJoin(auxStr3, ", NULL)\n");
				if(auxStr1 != NULL) {
					free(auxStr1);
					auxStr1 = NULL;
				}
				if(auxStr2 != NULL) {
					free(auxStr2);
					auxStr2 = NULL;
				}
				if(auxStr3 != NULL) {
					free(auxStr3);
					auxStr3 = NULL;
				}
				break;
			case IfK:
				//fprintf(out, "[Conditional IF]\n");
				//fprintf(out, " \"newNodeKind(IfK, NULL, NULL, NULL, NULL);\" \n");
				sprintf(auxArr, "%snewNodeKind(IfK, NULL, \n", strSpaces);
				auxStr1 = strJoin(auxArr, getTreeStr(tree->child[0], indentNro));
				auxStr2 = strJoin(auxStr1, ", \n");
				auxStr3 = strJoin(auxStr2, getTreeStr(tree->child[1], indentNro));
				auxStr4 = strJoin(auxStr3, ", \n");

				if(tree->child[2] != NULL) {
					auxStr5 = strJoin(auxStr4, getTreeStr(tree->child[2], indentNro));
					valNode = strJoin(auxStr5, ")\n");
					if(auxStr5 != NULL) {
						free(auxStr5);
						auxStr5 = NULL;
					}
				} else {
					valNode = strJoin(auxStr4, " NULL)\n");
				}

				if(auxStr1 != NULL) {
					free(auxStr1);
					auxStr1 = NULL;
				}
				if(auxStr2 != NULL) {
					free(auxStr2);
					auxStr2 = NULL;
				}
				if(auxStr3 != NULL) {
					free(auxStr3);
					auxStr3 = NULL;
				}
				if(auxStr4 != NULL) {
					free(auxStr4);
					auxStr4 = NULL;
				}
				break;
			case WhileK:
				//fprintf(out, "[Bucle WHILE]\n");
				//fprintf(out, " \"newNodeKind(WhileK, NULL, NULL, NULL, NULL);\" \n");
				sprintf(auxArr, "%snewNodeKind(WhileK, NULL, \n", strSpaces);
				auxStr1 = strJoin(auxArr, getTreeStr(tree->child[0], indentNro));
				auxStr2 = strJoin(auxStr1, ", \n");
				auxStr3 = strJoin(auxStr2, getTreeStr(tree->child[1], indentNro));
				valNode = strJoin(auxStr3, ", NULL)\n");
				if(auxStr1 != NULL) {
					free(auxStr1);
					auxStr1 = NULL;
				}
				if(auxStr2 != NULL) {
					free(auxStr2);
					auxStr2 = NULL;
				}
				if(auxStr3 != NULL) {
					free(auxStr3);
					auxStr3 = NULL;
				}
				break;
			case LoopK:
				//fprintf(out, "[Bucle LOOP]\n");
				//fprintf(out, " \"newNodeKind(LoopK, NULL, NULL, NULL, NULL);\" \n");
				sprintf(auxArr, "%snewNodeKind(LoopK, NULL, \n", strSpaces);
				auxStr1 = strJoin(auxArr, getTreeStr(tree->child[0], indentNro));
				auxStr2 = strJoin(auxStr1, ", \n");
				auxStr3 = strJoin(auxStr2, getTreeStr(tree->child[1], indentNro));
				valNode = strJoin(auxStr3, ", NULL)\n");
				if(auxStr1 != NULL) {
					free(auxStr1);
					auxStr1 = NULL;
				}
				if(auxStr2 != NULL) {
					free(auxStr2);
					auxStr2 = NULL;
				}
				if(auxStr3 != NULL) {
					free(auxStr3);
					auxStr3 = NULL;
				}
				break;
			case OperRelK:
				//fprintf(out, "[Operator Relat: \"%s\"]\n", tree->id);
				//fprintf(out, " \"newNodeKind(OperRelK, %s, NULL, NULL, NULL);\" \n", tree->id);
				sprintf(auxArr, "%snewNodeKind(OperRelK, \"%s\", \n", strSpaces, tree->id);
				auxStr1 = strJoin(auxArr, getTreeStr(tree->child[0], indentNro));
				auxStr2 = strJoin(auxStr1, ", \n");
				
				if((strcmp(tree->id, "!") != 0) && (strcmp(tree->id, "eval") != 0)) {
					auxStr3 = strJoin(auxStr2, getTreeStr(tree->child[1], indentNro));
					valNode = strJoin(auxStr3, ", NULL)\n");
					if(auxStr3 != NULL) {
						free(auxStr3);
						auxStr3 = NULL;
					}
				} else {
					valNode = strJoin(auxStr2, " NULL, NULL)\n");
				}
				
				if(auxStr1 != NULL) {
					free(auxStr1);
					auxStr1 = NULL;
				}
				if(auxStr2 != NULL) {
					free(auxStr2);
					auxStr2 = NULL;
				}
				break;
			case InputK:
				//fprintf(out, "[Output]\n");
				//fprintf(out, " \"newNodeKind(InputK, NULL, NULL, NULL, NULL);\" \n");
				sprintf(auxArr, "%snewNodeKind(InputK, \"%s\", \n", strSpaces, tree->id);
				auxStr1 = strJoin(auxArr, getTreeStr(tree->child[0], indentNro));
				valNode = strJoin(auxStr1, ", NULL, NULL)\n");
				if(auxStr1 != NULL) {
					free(auxStr1);
					auxStr1 = NULL;
				}
				break;
			case OutputK:
				//fprintf(out, "[Output]\n");
				//fprintf(out, " \"newNodeKind(OutputK, NULL, NULL, NULL, NULL);\" \n");
				sprintf(auxArr, "%snewNodeKind(OutputK, NULL, \n", strSpaces);
				auxStr1 = strJoin(auxArr, getTreeStr(tree->child[0], indentNro));
				valNode = strJoin(auxStr1, ", NULL, NULL)\n");
				if(auxStr1 != NULL) {
					free(auxStr1);
					auxStr1 = NULL;
				}
				break;
		}
		
		//tree = tree->sibling;
		//getTreeStr(tree->sibling, indentNro - 2);
		if(tree->sibling != NULL) {
			auxStr1 = strJoin("joinNode(\n", valNode);
			auxStr2 = strJoin(auxStr1, ", \n");
			auxStr3 = strJoin(auxStr2, getTreeStr(tree->sibling, indentNro - 2));
			valRet = strJoin(auxStr3, ")");
			if(auxStr1 != NULL) {
				free(auxStr1);
				auxStr1 = NULL;
			}
			if(auxStr2 != NULL) {
				free(auxStr2);
				auxStr2 = NULL;
			}
			if(auxStr3 != NULL) {
				free(auxStr3);
				auxStr3 = NULL;
			}
		} else {
			valRet = strJoin("", valNode);
		}

		if(valNode != NULL) {
			free(valNode);
			valNode = NULL;
		}
	}

	indentNro -= 2;
	
	return(valRet);
}

void generateCFile(FILE *out, StTreeNode *tree)
{
	fprintf(out, "\n#include <stdio.h>\n");
	fprintf(out, "#include \"utils.h\"\n\n");
	fprintf(out, "int main()\n");
	fprintf(out, "{\n");
	fprintf(out, "StScopeList *listVars = NULL;\n");
	fprintf(out, "StTreeNode *tree = %s;\n\n", getTreeStr(tree, 0));
	fprintf(out, "executeTree(tree, 0, &listVars);\n");
	fprintf(out, "deleteIdScopeList(&listVars, 0);\n\n");
	fprintf(out, "return 0;\n");
	fprintf(out, "}\n");
}

void insertIdScopeList(StScopeList **list, char *strType, char *strId, int intScope)
{
	StScopeList *sl = (StScopeList*) malloc(sizeof(StScopeList));

	if(sl != NULL) {
		sl->id = strJoin(strId, "");
		sl->info.isOk = 1;
		sl->info.valInt = 0;
		sl->info.valStr = NULL;
		
		if(strcmp(strType, "int") == 0) {
			sl->info.type = INT_TYPE;
		} else if(strcmp(strType, "char") == 0) {
			sl->info.type = CHAR_TYPE;
		} else {
			sl->info.valStr = strJoin("", "");
			if(strcmp(strType, "sentence") == 0) {
				sl->info.type = SENTE_TYPE;
			} else {
				sl->info.type = WORD_TYPE;
			}
		}
		
		sl->scope = intScope;
		sl->next = *list;
		*list = sl;
	} else {
	    printf("Out of memory error\n");
		exit(0);
	}
}

void deleteIdScopeList(StScopeList **list, int intScope)
{
	StScopeList *sl = *list;
	int exist = 0;

	while((sl != NULL) && (exist == 0)) {
		if(sl->scope > intScope) {
			*list = (*list)->next;
			sl->next = NULL;
			free(sl);
			sl = *list;
		} else {
			exist = 1;
		}
		sl = *list;
	}
}

int existIdScopeList(StScopeList *list, char *strId, InfoVar *infoVars)
{
	StScopeList *sl = list;
	int exist = 0;

	while((sl != NULL) && (exist == 0)) {
		if(strcmp(sl->id, strId) == 0) {
			*infoVars = sl->info;
			exist = 1;
		}
		sl = sl->next;
	}

	return(exist);
}

int updateIdScopeList(StScopeList **list, char *strId, InfoVar infoVars)
{
	StScopeList *sl = *list;
	int exist = 0;
	char *auxStr;

	while((sl != NULL) && (exist == 0)) {
		if(strcmp(sl->id, strId) == 0) {
			if(varContainsChars(&(sl->info))) {
				free(sl->info.valStr);
				sl->info.valStr = NULL;
			}
			sl->info = infoVars;
			
			if(varContainsChars(&(sl->info))) {
				auxStr = sl->info.valStr;
				sl->info.valStr = strJoin(auxStr, "");
				sl->info.isOk = 1;
			}
			exist = 1;
		}
		sl = sl->next;
	}

	return(exist);
}

void showScopeList(StScopeList *list)
{
	StScopeList *sl = list;
	
	printf("List Start\n");
	while(sl != NULL) {
		printf("\tSTR_ID: %s, Scope: %d, Type %d, ", sl->id, sl->scope, sl->info.type);

		switch(sl->info.type) {
			case INT_TYPE:
				printf("Value (int): [%d]\n", sl->info.valInt);
				break;
			case CHAR_TYPE:
				printf("Value (char): [%c]\n", sl->info.valInt);
				break;
			default:
				printf("Value (str): [%s]\n", sl->info.valStr);
				break;
		}

		sl = sl->next;
	}
	printf("List End\n");
}

