#pragma once
//**************************************
// cSymbolTable.h
//
// Defines a nested symbol table.
// Individual levels of the symbol table use a std::unordered_map from the STL
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
//

#include "cSymbol.h"
#include <string>
#include <iostream>
#include <unordered_map>
#include <list>
#include <utility>      // use pair

using std::string;
using std::unordered_map;
using std::list;
using std::pair;
using std::endl;
using std::cout;

typedef unordered_map<string, cSymbol *> symbolTable_t;

class cSymbolTable
{
    public:
         // Create a symbol table
        cSymbolTable()
	{
		IncreaseScope();
		Insert(new cSymbol("char", true));
		Insert(new cSymbol("int", true));
		Insert(new cSymbol("float", true));
	}

        // Increase the scope: add a level to the nested symbol table
        // Return value is the newly created scope
        symbolTable_t* IncreaseScope()
	{
		symbolTable_t *table = new symbolTable_t();
        	m_SymbolTable.push_front(table);
		return table;
	}

        // Decrease the scope: remove the outer-most scope.
        // Returned value is the outer-most scope AFTER the pop.
        //
        // NOTE: do NOT clean up memory after poping the table. Parts of the
        // AST will probably contain pointers to symbols in the popped table.
        symbolTable_t* DecreaseScope()
	{
        	m_SymbolTable.pop_front();
        	return m_SymbolTable.front();
	}

        // insert a symbol into the table
        // Assumes the symbol is not already in the table
        void Insert(cSymbol *sym)
	{
        	pair<string, cSymbol*> new_val(sym->GetName(), sym);
        	m_SymbolTable.front()->insert(new_val);
	}

        // Do a lookup in the nested table. 
        // Return the symbol for the outer-most match. 
        // Returns nullptr if no match is found.
        cSymbol* Find(string name)
	{
         	cSymbol *sym = nullptr;
         	list<symbolTable_t *>::iterator it = m_SymbolTable.begin();

       		while (it != m_SymbolTable.end())
       		{
       				symbolTable_t temp = **it;
       				for(pair<string, cSymbol*> thing : temp)
       				{
       					if(thing.first == name)
       					{
       						return thing.second;
       					}
       				}


                	it++;
            	}
            	return nullptr;
	}


        // Find a symbol in the outer-most scope.
        // NOTE: does not search nested scopes, only the outermost scope.
        // Return the symbol if found.
        // Returns nullptr if the symbol is not found.
        cSymbol* FindLocal(string name)
	{
		list<symbolTable_t *>::iterator it = m_SymbolTable.begin();
		       	for(pair<string, cSymbol*> thing : **it)
       			{
       				if(thing.first == name)
       				{
       					return thing.second;
       				}
       			}
	}
	protected:
        // list of symbol tables. The list contains the different levels
        // in the nested table.
        list<symbolTable_t *> m_SymbolTable;
};

// Declaration for the global symbol table.
// Definition is in main.cpp
extern cSymbolTable g_symbolTable;
