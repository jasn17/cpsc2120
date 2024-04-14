/*
 * Name: Jason Lin 
 * Date Submitted:
 * Lab Section: 005
 * Assignment Name: Spell Checker Using a Hashtable
 */

#pragma once

#include <string>
#include <vector>
#include <list>
#include <functional> 
using namespace std;

//Stringset class, do not modify definitions for existing members
class Stringset
{
    private:
        vector<list<string>> table;
        int num_elems;
        int size;
    public:
        Stringset();
        vector<list<string>> getTable() const;
        int getNumElems() const;
        int getSize() const;
        void insert(string word);
        bool find(string word) const;
        void remove(string word);
	void doubleSize();
};
