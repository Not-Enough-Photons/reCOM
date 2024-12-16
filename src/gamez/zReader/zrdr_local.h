#pragma once
#include "zrdr.h"

class CRdrEditor
{
public:
	CRdrEditor();
	~CRdrEditor();
public:
	int push(const char* str);
	int pop();

	int addint(const char* tag, int value);
	int addintnode(const char* tag, int value);
	int addSTRING(const char* tag, const char* value);
};

int CRdrEditor::addint(const char* tag, int value)
{

}

int CRdrEditor::addSTRING(const char* tag, const char* value)
{

}