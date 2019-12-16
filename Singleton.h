//
// Created by magshimim on 13.12.2019.
//

//**Dont work!**

#ifndef UNTITLED11_SINGLETON_H
#define UNTITLED11_SINGLETON_H
template <class T> class Singleton {
    static Singleton<T> *instance;
    T data;

    // Private constructor so that no objects can be created.
    Singleton() {
        data = 0;
    }

public:
    static Singleton<T> *getInstance() {
        if (!instance)
            instance = new Singleton;
        return instance;
    }

    T getData() {
        return this -> data;
    }

    void setData(T* data) {
        this -> data = data;
    }
};

#endif //UNTITLED11_SINGLETON_H
