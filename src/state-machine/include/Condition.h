#ifndef CONDITION_H
#define CONDITION_H

//#include "../../utils/include/vector.h"
#include "vector"

using namespace std;

class Condition
{
public:
	Condition() {}
	virtual ~Condition() {}

	virtual bool accepts(char input) const = 0;
};


class CharCondition : public Condition
{
public:
	explicit CharCondition(char allowed) : _allowed(allowed) {}

	bool accepts(char input) const override 
	{
		return input == _allowed;
	}

private:
	const char _allowed;
};


class AnyOfCondition : public Condition
{
public:
    explicit AnyOfCondition(const char* allowed) : _chars(allowed) {}

	bool accepts(char input) const override
	{
		int i = -1;
        while (_chars[++i] != '\0')        
            if (input == _chars[i])
                return true;
        
		return false;
	}

private:
	const char* _chars;
};

class NotCondition : public Condition
{
public:
    explicit NotCondition(const Condition* unallowed) : _condition(unallowed) {};

    ~NotCondition()
    {
        delete _condition;
        _condition = nullptr;
    }

	bool accepts(char input) const override
	{
        return !_condition->accepts(input);
	}

private:
	const Condition* _condition;
};


class CharRangeCondition : public Condition
{
public:
    CharRangeCondition(char from, char to) : _from(from), _to(to) {};

	bool accepts(char input) const override
	{
        return input >= _from && input <= _to;
	}

private:
	char _from;
    char _to;
};


class TrueCondition : public Condition
{
public:
    TrueCondition() {}

    bool accepts(char input) const override
    {
        return true;
    }
};


class OrCondition : public Condition
{
public:
    OrCondition(Condition* c) 
    {
        _conditions.push_back(c);
    } 

    OrCondition(Condition* c1,  Condition* c2)
    {
        _conditions.push_back(c1);
        _conditions.push_back(c2);
    }

    OrCondition(Condition* c1,  Condition* c2,  Condition* c3)
    {
        _conditions.push_back(c1);
        _conditions.push_back(c2);
        _conditions.push_back(c3);
    }

    ~OrCondition()
    {
        for (int i = 0; i < _conditions.size(); i++)
        {
            delete _conditions[i];
            _conditions[i] = nullptr;
        }
    }

    bool accepts(char input) const override
    {
        for (int i = 0; i < _conditions.size(); i++)            
            if (_conditions[i]->accepts(input))
                return true;

        return false;
    }

private:
    vector<Condition*> _conditions;
};

class AndCondition : public Condition
{
public:
    AndCondition(Condition* c)
    {
        _conditions.push_back(c);
    } 

    AndCondition(Condition* c1,  Condition* c2)
    {
        _conditions.push_back(c1);
        _conditions.push_back(c2);
    }

    AndCondition(Condition* c1,  Condition* c2,  Condition* c3)
    {
        _conditions.push_back(c1);
        _conditions.push_back(c2);
        _conditions.push_back(c3);
    }

    ~AndCondition()
    {
        for (int i = 0; i < _conditions.size(); i++)
        {
            delete _conditions[i];
            _conditions[i] = nullptr;
        }
    }

    bool accepts(char input) const override
    {
        for (int i = 0; i < _conditions.size(); i++)            
            if (!_conditions[i]->accepts(input))
                return false;

        return true;
    }

private:
    vector<Condition*> _conditions;
};



#endif