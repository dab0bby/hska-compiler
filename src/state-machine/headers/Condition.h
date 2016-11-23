#ifndef CONDITION_H
#define CONDITION_H

#include "../../utils/header/vector.h"

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


class StringCondition : public Condition
{
public:
    explicit StringCondition(const char* allowed) : _chars(allowed) {}

	bool accepts(char input) const override
	{
		int i = 0;
		while (_chars[i] != '\0')
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
    explicit NotCondition(Condition& unallowed) : _condition(unallowed) {};

	bool accepts(char input) const override
	{
        return !_condition.accepts(input);
	}

private:
	Condition& _condition;
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


class EpsilonCondition : public Condition
{
public:
    EpsilonCondition() {}

    bool accepts(char input) const override
    {
        return true;
    }
};


class MultiCondition : public Condition
{
public:
    MultiCondition( Condition* c) 
    {
        _conditions.add(c);
    } 

    MultiCondition( Condition* c1,  Condition* c2)
    {
        _conditions.add(c1);
        _conditions.add(c2);
    }

    MultiCondition( Condition* c1,  Condition* c2,  Condition* c3)
    {
        _conditions.add(c1);
        _conditions.add(c2);
        _conditions.add(c3);
    }

    void add( Condition* condition)
    {
        _conditions.add(condition);
    }

    void remove( Condition* condition)
    {
        _conditions.remove(condition);
    }

    bool accepts(char input) const override
    {
        for (int i = 0; i < _conditions.size(); i++)            
            if (_conditions.get(i)->accepts(input))
                return true;

        return false;
    }

private:
    vector<Condition*> _conditions;
};



#endif