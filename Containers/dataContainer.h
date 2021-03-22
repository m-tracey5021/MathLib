# pragma once

template<typename t>

class DataContainer {

    private:

        t value;

    public:

        DataContainer(){}

        DataContainer(t value): value(value){}

        void set(t v){value = v;}

        t get(){return value;}

};