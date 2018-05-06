#include <bits/stdc++.h>

using namespace std;


/*struct MyTuple*/
template <typename T, typename... Oth>
struct MyTuple {
    T memory;
    MyTuple<Oth...> next;

    MyTuple():
            memory(),
            next()
    { }

    MyTuple(T first, Oth... args):
            memory(first),
            next(args...)
    { }

    bool operator==(const MyTuple<T, Oth...>& oth) const {
        return memory == oth.memory && (next == oth.next);
    }

    bool operator<(const MyTuple<T, Oth...>& oth) const {
        if (memory == oth.memory)
            return next < oth.next;
        return memory < oth.memory;
    }

    bool operator<=(const MyTuple<T, Oth...>& oth) const {
        return *this == oth || *this < oth;
    }

    bool operator>=(const MyTuple<T, Oth...>& oth) const {
        return !(*this < oth);
    }

    bool operator >(const MyTuple<T, Oth...>& oth) const {
        return !(*this <= oth);
    }

    MyTuple& operator=(const MyTuple<T, Oth...>& oth) {
        memory = oth.memory;
        next = oth.next;
        return *this;
    }
};

template <typename T>
struct MyTuple<T> {
    T memory;

    MyTuple():
            memory()
    { }

    MyTuple(T first):
            memory(first)
    { }

    bool operator==(const MyTuple<T>& oth) const {
        return memory == oth.memory;
    }

    bool operator<(const MyTuple<T>& oth) const {
        return memory < oth.memory;
    }

    bool operator<=(const MyTuple<T>& oth) const {
        return *this == oth || *this < oth;
    }

    bool operator>=(const MyTuple<T>& oth) const {
        return !(*this < oth);
    }

    bool operator >(const MyTuple<T>& oth) const {
        return !(*this <= oth);
    }

    MyTuple& operator=(const MyTuple<T>& oth) {
        memory = oth.memory;
        return *this;
    }
};
/**/

template <int M>
struct MyTupleInterface {
    /*Helping struct Get <N,T,Args..> for function get(MyTuple<...>)*/
    template <int N, typename T, typename... Args>
    struct Get {
        static auto& getElemTuple(MyTuple<T, Args...>& mt) {
            return Get <N - 1, Args...>::getElemTuple(mt.next);
        }
    };

    template <typename T, typename... Args>
    struct Get <0, T, Args...> {
        static auto& getElemTuple(MyTuple<T, Args...>& mt)  {
            return mt.memory;
        }
    };
    /**/

    template <typename T, typename... Args>
    static auto& get(MyTuple<T, Args...>& mt) {
        return Get <M, T, Args...>::getElemTuple(mt);
    }
};

template<int N, typename T, typename... Args>
auto & getElem(MyTuple<T, Args...>& mt) {
    return MyTupleInterface<N> :: get(mt);
}

template <typename T, typename... Args>
auto makeMyTuple(T&& first, Args&&... args) {
    return MyTuple<T, Args...>(first, args...);
}

int main() {
    MyTuple<char, vector<int>, int> mt1('c', {2, 3}, 23);
    MyTuple<char, vector<int>, int> mt2 = makeMyTuple('c', vector<int>(2, 3), 24);

    // MyTuple<char, string, int> mt2 = makeMyTuple('c', "std", 24) -- not working, BAD
    // auto mt3 = makeMyTuple() -- not working, OK
    // tuple<char, string, int> t = make_tuple('c', "std", 24); - working

    cout << getElem<2>(mt1) << " " << getElem<2>(mt2) <<'\n';

    if (mt1 < mt2)
        cout << "Yes" << '\n';
    else
        cout << "No" << '\n';

    getElem<2>(mt1) += 1;

    if (mt1 <= mt2)
        cout << "Yes" << '\n';
    else
        cout << "No" << '\n';

    return 0;
}