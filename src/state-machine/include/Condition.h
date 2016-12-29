#ifndef CONDITION_H
#define CONDITION_H


class Condition
{
public:

    virtual ~Condition() { }

    virtual bool accepts(char input) const = 0;
    virtual Condition* clone() const = 0;

    static Condition* createAlphabet();
    static Condition* createDigit();
    static Condition* createAlphanumerical();
    static Condition* createWhitespace();
    static Condition* createLinefeed();
    static Condition* createWhitespaceWithoutLinefeed();
};



class CharCondition : public Condition
{
public:
    explicit CharCondition(char allowed) : _allowed(allowed)
    {
    }

    bool accepts(char input) const override
    {
        return input == _allowed;
    }

    Condition* clone() const override
    {
        return new CharCondition(_allowed);
    }

private:
    const char _allowed;
};


class AnyOfCondition : public Condition
{
public:
    explicit AnyOfCondition(const char* allowed) : _chars(allowed)
    {
    }

    bool accepts(char input) const override
    {
        int i = -1;
        while (_chars[++i] != '\0')
            if (input == _chars[i])
                return true;

        return false;
    }

    Condition* clone() const override
    {
        return new AnyOfCondition(_chars);
    }

private:
    const char* _chars;
};

class NotCondition : public Condition
{
public:
    explicit NotCondition(const Condition* unallowed) : _condition(unallowed)
    {
    };

    ~NotCondition()
    {
        delete _condition;
        _condition = nullptr;
    }

    bool accepts(char input) const override
    {
        return !_condition->accepts(input);
    }

    Condition* clone() const override
    {
        return new NotCondition(_condition->clone());
    }

private:
    const Condition* _condition;
};


class CharRangeCondition : public Condition
{
public:
    CharRangeCondition(char from, char to) : _from(from), _to(to)
    {
    };

    bool accepts(char input) const override
    {
        return input >= _from && input <= _to;
    }

    Condition* clone() const override
    {
        return new CharRangeCondition(_from, _to);
    }

private:
    char _from;
    char _to;
};


class TrueCondition : public Condition
{
public:
    TrueCondition()
    {
    }

    bool accepts(char input) const override
    {
        return true;
    }

    Condition* clone() const override
    {
        return new TrueCondition;
    }
};


class OrCondition : public Condition
{
public:
    OrCondition(Condition* c) : OrCondition(new Condition*[1] {c}, 1)
    {
    }

    OrCondition(Condition* c1, Condition* c2) : OrCondition(new Condition*[2] {c1, c2}, 2)
    {
    }

    OrCondition(Condition* c1, Condition* c2, Condition* c3) : OrCondition(new Condition*[3] {c1, c2, c3}, 3)
    {
    }

    OrCondition(Condition** conditions, int count)
    {
        _conditions = conditions;
        _count = count;
    }

    ~OrCondition()
    {
        for (int i = 0; i < _count; i++)
            delete _conditions[i];
        delete[] _conditions;
    }

    bool accepts(char input) const override
    {
        for (int i = 0; i < _count; i++)
            if (_conditions[i]->accepts(input))
                return true;

        return false;
    }

    Condition* clone() const override
    {
        Condition** clones = new Condition*[_count];
        for (int i = 0; i < _count; i++)
            clones[i] = _conditions[i]->clone();

        return new OrCondition(clones, _count);
    }

private:
    Condition** _conditions;
    int _count;
};

class AndCondition : public Condition
{
public:
    AndCondition(Condition* c) : AndCondition(new Condition*[1] {c}, 1)
    {
    }

    AndCondition(Condition* c1, Condition* c2) : AndCondition(new Condition*[2] {c1, c2}, 2)
    {
    }

    AndCondition(Condition* c1, Condition* c2, Condition* c3) : AndCondition(new Condition*[3] {c1, c2, c3}, 3)
    {
    }

    AndCondition(Condition** conditions, int count)
    {
        _conditions = conditions;
        _count = count;
    }

    ~AndCondition()
    {
        for (int i = 0; i < _count; i++)
            delete _conditions[i];
        delete[] _conditions;
    }

    bool accepts(char input) const override
    {
        for (int i = 0; i < _count; i++)
            if (!_conditions[i]->accepts(input))
                return false;

        return true;
    }

    Condition* clone() const override
    {
        Condition** clones = new Condition*[_count];
        for (int i = 0; i < _count; i++)
            clones[i] = _conditions[i]->clone();

        return new AndCondition(clones, _count);
    }

private:
    Condition** _conditions;
    int _count;
};



inline Condition* Condition::createAlphabet()
{
    return new OrCondition(new CharRangeCondition('a', 'z'), new CharRangeCondition('A', 'Z'));
}

inline Condition* Condition::createDigit()
{
    return new CharRangeCondition('0', '9');
}

inline Condition* Condition::createAlphanumerical()
{
    return new OrCondition(new CharRangeCondition('0', '9'), new CharRangeCondition('a', 'z'), new CharRangeCondition('A', 'Z'));
}

inline Condition* Condition::createWhitespace()
{
    return new AnyOfCondition(" \t\r\n");
}

inline Condition* Condition::createLinefeed()
{
    return new AnyOfCondition("\r\n");
}

inline Condition* Condition::createWhitespaceWithoutLinefeed()
{
    return new AnyOfCondition(" \t");
}

#endif
