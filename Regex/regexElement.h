#pragma once

#include <string>

class RegexElement{
    private:
        
    protected:
        int index;
        int repititions;
        RegexElement* next;
        RegexElement* prev;
        RegexElement* child;
        RegexElement* parent;
    public:
        RegexElement();
        RegexElement(int i, int r);
        int getIndex();
        int getRepititions();
        RegexElement* getNext();
        RegexElement* getPrev();
        RegexElement* getChild();
        RegexElement* getParent();

        void setIndex(int i);
        void setRepititions(int r);
        void setNext(RegexElement* n);
        void setPrev(RegexElement* p);
        void setChild(RegexElement* c);
        void setParent(RegexElement* p);

        virtual std::string toString();


};