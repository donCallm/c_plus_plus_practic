#pragma once

#include <iostream>
#include <random>
#include <iomanip>
#include <list>
#include <set>
#include <chrono>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>
#include <thread>
#include <queue>
#include <cstring>
#include <future>
#include <numeric>
#include <mutex>
#include <functional>
#include <memory>

using namespace std;

namespace rbelt {
    template<typename T>
    void assert(const T& value, const T& expected, const string &msg = "") {
        if (value != expected) {
            if (msg.size() != 0)
                cerr << msg << ": ";
            cerr << value << " != " << expected << std::endl;
            throw runtime_error("");
        }
    }

    inline void assert(bool val, const string &msg = "") {
        if (!val) {
            throw runtime_error("");
        }
    }

    class run_test {
        public  :
            template<typename func>
            void run(func f, const string& test_name);

            ~run_test();
        private:
            size_t err_count = 0;
    };

    class LogDuration {
        public  :
            LogDuration(const std::string& msg)
                : _msg(msg), _start(std::chrono::steady_clock::now()) {}

            ~LogDuration() {
                auto finish = std::chrono::steady_clock::now();
                auto duration = finish - _start;
                std::cerr << _msg    << ": "
                        << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count()
                        << "ms" << std::endl;
            }

        private:
            std::chrono::steady_clock::time_point _start;
            std::string _msg;
    };

    void first_weak();

    #define LOG(logger, message)  \
        logger.SetLine(__LINE__); \
        logger.SetFile(__FILE__); \
        logger.Log(message)

    class Logger {
        public  :
            explicit Logger(ostream& output_stream) : os(output_stream) {}

            void SetLogLine(bool value) { log_line = value; }
            void SetLogFile(bool value) { log_file = value; }
            void SetLine(int value)     { line = value; }
            void SetFile(string value)  { file_name = value; }

            void Log(const string& message);
        private:
            ostream& os;
            bool log_line = false;
            bool log_file = false;
            int line;
            string file_name;
    };

    #define SORT_BY(some)                                        \
        [](const AirlineTicket& lhs, const AirlineTicket& rhs) { \
        return lhs.some < rhs.some;}

    struct Date {
        int year, month, day;
    };

    struct Time {
        int hours, minutes;
    };

    struct AirlineTicket {
        string from;
        string to;
        string airline;
        Date departure_date;
        Time departure_time;
        Date arrival_date;
        Time arrival_time;
        int price;
    };

    bool operator<(const Date& l, const Date&r);
    ostream& operator<<(ostream& os, const Time& t);
    ostream& operator<<(ostream& os, const Date& d);
    ostream& operator<<(ostream& os, const AirlineTicket& a);
    bool operator==(const Time& l, const Time& r);
    bool operator==(const Date& l, const Date& r);
    bool operator==(const AirlineTicket& l, const AirlineTicket& r);
    bool operator!=(const Date& l, const Date& r);
    bool operator!=(const AirlineTicket& l, const AirlineTicket& r);
        
    #define UPDATE_FIELD(ticket, field, values) \
        it = values.find(#field);               \
        if (it != updates.end()) {              \
            istringstream is(it->second);       \
            is >> ticket.field;                 \
        }

    #define PRINT_VALUES(out, x, y) {out << (x) << endl; out << (y) << endl;}

    void UpdateTicket(AirlineTicket& ticket, const map<string, string>& updates);

    bool operator==(const AirlineTicket& l, const AirlineTicket& r);

    #define CONCAT(f, s) name ## f ## s
    #define GET_NAME(f, s) CONCAT(f, s)
    #define UNIQ_ID \
        GET_NAME(__LINE__, __COUNTER__)

    template<typename T>
    class Table {
        public  :
            Table(size_t lines_count, size_t columns_count)
                : _lines_count(lines_count),
                _columns_count(columns_count) {
                _values = vector<vector<T>>(lines_count);
                for (auto& item : _values)
                    item = vector<T>(columns_count);
            }

        void Resize(size_t new_l_count, size_t new_col_count) {
            _values.resize(new_l_count);
            for (auto& vec : _values)
                vec.resize(new_col_count);
            _lines_count = new_l_count;
            _columns_count = new_col_count;
        }

        pair<size_t, size_t> Size() const { return {_lines_count, _columns_count}; }

        vector<T>& operator[](size_t i) { return _values[i]; }
        const vector<T>& operator[](size_t i) const { return _values[i]; }
        private:
            size_t _lines_count;
            size_t _columns_count;
            vector<vector<T>> _values;
    };

    template<typename T>
    class Deque {
        public  :
            Deque() : _size(0) {}
        public  :
            bool Empty() const {
                if (_size == 0)
                    return true;
                return false;
            }
            size_t Size() { return _size; }

            T& operator[](size_t index) { return get_elem(index); }
            const T& operator[](size_t index) const { return get_elem(index); }

            const T& At(size_t index) const {
                if (index > _size)
                    throw out_of_range(string("size is: " + to_string(_size)));
                return get_elem(index);
            }
            T& At(size_t index) {
                if (index > _size)
                    throw out_of_range(string("size is: " + to_string(_size)));
                return get_elem(index);
            }
            
            T& Front() { return _front.back(); }
            T& Back() { return _back.back(); }
            void PushFront(T& new_elem) {
                _front.emplace_back(new_elem);
                ++_size;
            }
            void PushBack(T& new_elem) {
                _back.emplace_back(new_elem);
                ++_size;
            }
        private:
            T& get_elem(size_t index) {
                if (index < _front.size())
                    return _front[_front.size() - index];
                return _back[index - _front.size()];
            }
        private:
            size_t _size;
            vector<T> _front;
            vector<T> _back;
    };

    template<typename ItType>
    class Page {
        public  :
            Page(ItType begin, ItType end, size_t size)
                : _size(size),
                _begin(begin),
                _end(end) {}
        public  :
            size_t Size() const { return _size; }
        
            ItType begin() { return _begin; }
            ItType end() { return _end; }
        private:
            size_t _size;
            ItType _begin;
            ItType _end;
    };

    template<typename ItType>
    class Paginator {
        public  :
            Paginator(ItType begin, ItType end, size_t page_size)
                : _size(0) {
                while(begin != end) {
                    int dist = distance(begin, end);
                    if (dist >= page_size) {
                        _pages.emplace_back(begin, begin + page_size, page_size);
                        begin = begin + page_size;
                        ++_size;
                        continue;
                    }
                    _pages.emplace_back(begin, end, dist);
                    ++_size;
                    break;
                }
            }
        public  :
            size_t Size() const { return _size; }

            typename vector<Page<ItType>>::iterator begin() { return _pages.begin(); }
            typename vector<Page<ItType>>::iterator end() { return _pages.end(); }
        private:
            size_t _size;
            vector<Page<ItType>> _pages;
    };  

    template<typename T>
    Paginator<typename T::iterator> Paginate(T& container, size_t page_size) {
        return Paginator<typename T::iterator>(container.begin(), container.end(), page_size);
    }

    void second_weak();

    struct Student {
        string first_name;
        string last_name;
        map<string, double> marks;
        double rating;

        bool operator<(const Student& other) const;

        bool Less(const Student& other) const;

        string GetName() const;
    };

    bool Compare(const Student& first, const Student& second);

    class Learner {
        public  :
            int Learn(const vector<string>& words);
            set<string>& KnownWords();
        private:
            set<string> dict;
    };

    class RouteManager {
        public  :
            void AddRoute(int start, int finish);
            int FindNearestFinish(int start, int finish) const;
        private:
            map<int, set<int>> reachable_lists_;
    };

    struct User {
        User(int id_ = 0, int page_count_ = 0)
            : id(id_),
            page_count(page_count_) {}

        int id;
        int page_count;

        bool operator<(const User& other) const {
            return page_count < other.page_count;
        }

        bool operator==(const User& other) const {
            return id == other.id && page_count == other.page_count;  
        }

        User& operator=(const User& other) {
            id = other.id;
            page_count = other.page_count;
            return *this;
        }
    };
    

    class ReadingManager {
        public  :
            void Read(int user_id, int page_count);
            double Cheer(int user_id) const;
        private:
            int GetUserCount() const { return _users.size(); }
            void AddUser(User usr);
        private:
            static const int MAX_USER_COUNT_ = 100'000;
            
            set<User> _users;
            map<int, int> _pages;
    };

    const static uint64_t one_day = 86'400;
    static uint64_t last_time = 0;
    
    struct client {
        map<uint32_t, uint32_t> rooms;      //map<time, room_count>

        inline uint64_t room_count() const {
            uint64_t count = 0;
            for (const auto& r : rooms)
                count += r.second;
            return count;
        }
    };

    struct hotel {
        map<uint32_t, client> clients;
        uint32_t count;
    };

    class booking_manager {
        public:
            enum comms {
                BOOK = 0,
                CLIENTS = 1,
                ROOMS = 2
            };
        public:
            void book(uint64_t time, const string& hotel_name,
                uint64_t client_id, uint64_t room_count);
            inline uint64_t clients_count(const string& hotel_name) {
                uint64_t count = 0;

                for (const auto& cli : _hotels[hotel_name].clients) {
                    if (cli.second.rooms.size() > 0)
                        ++count;
                }

                return count;
            }

            inline uint64_t rooms(const string& hotel_name) {
                uint64_t room_count = 0;

                for ( auto& cli : _hotels[hotel_name].clients)
                    room_count += cli.second.room_count();

                return room_count;
            }
        private:
            map<string, hotel> _hotels;            //map<hotel_name, hotel>
    };

    void third_weak();

    template <class T>
    class set_queue {
        public:
            ~set_queue() { 
                for(auto& elem : _elems)
                    delete elem;
            }
        public:
            void push(T* val);
            T* front()  { return _elems.front(); }
            
            void pop();
            void delete_by_elem(T* elem);

            bool exist(T* val);
            bool empty() { return _elems.empty(); }
        private:
            set<T*> _to_check;
            deque<T*> _elems;
    };

    template <class T>
    class ObjectPool{
        public:
            T* Allocate();
            T* TryAllocate();
            void Deallocate(T* object);
        private:
           set_queue<T> _dedicated;
           set_queue<T> _liberated;
    };

    template <typename T>
    class SimpleVector {
        public:
            SimpleVector()
                : _capacity(0),
                _size(0),
                _begin(nullptr) {};
            explicit SimpleVector(size_t size);
            ~SimpleVector() {
                if (_capacity != 0 && _begin != nullptr) {
                    delete[] _begin; // Освобождаем массив элементов
                }
                _begin = nullptr;
            }

            T& operator[](size_t index) { return *(_begin + index); }
            void operator=(const SimpleVector<T>& other) {
                _size = other.Size();
                _capacity = other.Capacity();
                delete[] _begin;
                _begin = new T[other.Size()];
                
                for (size_t i = 0; i < _size; ++i) {
                    *(_begin + i) = *(other._begin + i);
                }
            }

            T* begin() { return _begin; }
            T* end() { return _begin + _size; }

            size_t Size() const { return _size; };
            size_t Capacity() const { return _capacity; };
            void PushBack(T value);
            // void PushBack(T&& value);

        private:
            void try_realloc();
        private:
            size_t _size;
            size_t _capacity;
            T* _begin;
    };

    template <typename T>
    class LinkedList     {
        public:
            struct Node {
                T value;
                Node* next = nullptr;
            };

            ~LinkedList() {
                Node* next = nullptr;
                while (head != nullptr) {
                    if (head->next != nullptr)
                        next = head->next;
                    else
                        next = nullptr;
                    delete head;
                    head = next;
                }
            }

            void PushFront(const T& value) { insert(this->head, value); }
            void InsertAfter(Node* node, const T& value) { insert(node, value); }
            void RemoveAfter(Node* node);
            void PopFront();

            Node* GetHead() { return head; }
            const Node* GetHead() const { return head; }
        private:
            void insert(Node* node, const T& value);
        private:
            Node* head = nullptr;
    };

    void fourt_weak();

    template<typename T, size_t N>
    class StackVector {
        public:
            explicit StackVector(size_t a_size = 0) {
                if (a_size >= N)
                    throw invalid_argument("");
                _size = a_size;
            }

            T& operator[](size_t index) { return _arr[index]; }
            const T& operator[](size_t index) const { return _arr[index]; };

            T* begin() { return _arr.data(); }
            T* end() { return (_arr.data() + (N - 1)); }
            T* begin() const { return _arr.data(); }
            T* end() const { return (_arr.data() + (N - 1)); }

            size_t Size() const { return _size; }
            size_t Capacity() const { return N; }

            void PushBack(const T& value) {
                if (_size == N)
                    throw overflow_error("");
                _arr[_size++] = value;
            }
            T PopBack() {
                if (_size == 0)
                    throw underflow_error("");
                T res = _arr[--_size];
                _arr[_size] = 0;
                return res;
            }
        public:
            size_t _size;
            array<T, N> _arr;
    };

    class Translator {
        public:
            void Add(string_view source, string_view target);       //eng, ru
            string_view TranslateForward(string_view source) const; //eng
            string_view TranslateBackward(string_view target) const;//ru

        private:
            map<string, string> _translate_eng_ru;
            map<string, string> _translate_ru_eng;
            set<string> _words;
    };

    enum TAirport {
        vitebsk = 0,
        minsk = 1,
        brest = 3
    };

    template <typename TAirport>
    class AirportCounter {
        public:
            // конструктор по умолчанию: список элементов пока пуст
            AirportCounter() {}

            // конструктор от диапазона элементов типа TAirport
            template <typename TIterator>
            AirportCounter(TIterator begin, TIterator end) {
                for (size_t i = 0; i <static_cast<size_t>(TAirport::Last_); ++i)
                    _counts[i].first = static_cast<TAirport>(i);
                while (begin != end) {
                    size_t index = static_cast<size_t>(*begin);
                    _counts[index].first = *begin; 
                    _counts[index].second += 1;
                    ++begin;
                }
            }

            // получить количество элементов, равных данному
            size_t Get(TAirport airport) const {
                return _counts[static_cast<size_t>(airport)].second;
            }

            // добавить данный элемент
            void Insert(TAirport airport) {
                _counts[static_cast<size_t>(airport)].second += 1;
            }

            // удалить одно вхождение данного элемента
            void EraseOne(TAirport airport) {
                if (_counts[static_cast<size_t>(airport)].second != 0)
                    _counts[static_cast<size_t>(airport)].second -= 1;
            }

            // удалить все вхождения данного элемента
            void EraseAll(TAirport airport) {
                _counts[static_cast<size_t>(airport)].second = 0;
            }

            using Item = pair<TAirport, size_t>;

            // получить некоторый объект, по которому можно проитерироваться,
            // получив набор объектов типа Item - пар (аэропорт, количество),
            // упорядоченных по аэропорту
            const array<Item, static_cast<size_t>(TAirport::Last_)> GetItems() const { 
                return _counts;
            }

        private:
            array<Item, static_cast<size_t>(TAirport::Last_)> _counts = {};
    };

    class Editor {
        public:
            Editor() : _copy_buf(""), _msg(""), _cursor_pos(0) {}
            void Left() {
                if (_cursor_pos != 0)
                    --_cursor_pos;
            }   // сдвинуть курсор влево
            void Right() {
                if (_cursor_pos < _msg.size())
                    ++_cursor_pos;
            }  // сдвинуть курсор вправо
            void Insert(char token) {
                _msg.insert(_cursor_pos++, 1, token);
            }   // вставить символ token
            void Copy(size_t tokens) {
                if (_msg.size() - _cursor_pos > tokens)
                    _copy_buf = string(_msg.begin() + _cursor_pos,
                        _msg.end());
                else
                    _copy_buf = string(_msg.begin() + _cursor_pos,
                        _msg.begin() + (_cursor_pos + tokens));
            }  // cкопировать
                                        // не более tokens символов,
                                        // начиная с текущей позиции курсора
            void Cut(size_t tokens) {
                if (_cursor_pos + tokens < _msg.size()) {
                    _copy_buf = string(_msg.begin() + _cursor_pos,
                        _msg.begin() + (_cursor_pos + tokens));
                    _msg.erase(_msg.begin() + _cursor_pos,
                        _msg.begin() + (_cursor_pos + tokens));
                } else {
                    _copy_buf = string(_msg.begin() + _cursor_pos,
                        _msg.end());
                    _msg.erase(_msg.begin() + _cursor_pos, _msg.end());
                }
            }  // вырезать не более tokens символов,
                                        // начиная с текущей позиции курсора
            void Paste() {
                _msg.insert(_cursor_pos, _copy_buf);
                _cursor_pos += _copy_buf.length();
            }  // вставить содержимое буфера
                            // в текущую позицию курсора
            string GetText() const { return _msg; }  // получить текущее содержимое
                                    // текстового редактора 
        private:
            string _copy_buf;
            string _msg;
            size_t _cursor_pos;
    };

    struct HttpRequest {
        string_view method, uri, protocol;
    };

    class Stats {
        public:
            void AddMethod(string_view method) {
                _method_count[method] += 1;
            }
            void AddUri(string_view uri) {
                _uri_count[uri] += 1;
            }
            const map<string_view, int>& GetMethodStats() const {
                return _method_count;
            }
            const map<string_view, int>& GetUriStats() const {
                return _uri_count;
            }
        private:
            map<string_view, int> _method_count;
            map<string_view, int> _uri_count;
    };

    template <typename String>
    using Group = vector<String>;

    template <typename String>
    using Char = typename String::value_type;

    template <typename String>
    vector<Group<String>> GroupHeavyStrings(vector<String>& strings) {
        vector<Group<String>> res;

        map<set<Char<String>>, Group<String>> temp;                 //set<type>, vector<string>
        set<Char<String>> subgroup;                                 // set<type>
        for (auto& str : strings) {
            subgroup = set<Char<String>>(str.begin(), str.end());
            temp[move(subgroup)].push_back(move(str));
        }

        for (auto& item : temp) {
            res.push_back(move(item.second));                       //vecto<vector<string>> => v[i].push_back(v1)
        }
    
        return move(res);
    }

    class StringNonCopyable : public string {
        public:
            using string::string;
            StringNonCopyable(string&& other) : string(move(other)) {}
            StringNonCopyable(const StringNonCopyable&) = delete;
            StringNonCopyable(StringNonCopyable&&) = default;
            StringNonCopyable& operator=(const StringNonCopyable&) = delete;
            StringNonCopyable& operator=(StringNonCopyable&&) = default;
    };

    template <typename T>
    class PriorityCollection {
        public:
            using Id = size_t;
            // Добавить объект с нулевым приоритетом
            // с помощью перемещения и вернуть его идентификатор
            Id Add(T object) {
                _id_elems[_last_id] = _elems.insert(make_pair(move(object), 0)).first;
                return _last_id++;
            }

            // Добавить все элементы диапазона [range_begin, range_end)
            // с помощью перемещения, записав выданные им идентификаторы
            // в диапазон [ids_begin, ...)
            template <typename ObjInputIt, typename IdOutputIt>
            void Add(ObjInputIt range_begin, ObjInputIt range_end,
                    IdOutputIt ids_begin) {
                while (range_begin != range_end)
                    *(ids_begin++) = Add(*(range_begin++));
            }

            // Определить, принадлежит ли идентификатор какому-либо
            // хранящемуся в контейнере объекту
            bool IsValid(Id id) const {
                auto elem = _id_elems.find(id);
                try {
                    if(elem != _id_elems.end() && elem.second == _elems.end()) {
                        return true;
                    }
                } catch (const exception& ex) {
                    return false;
                }
            }

            // Получить объект по идентификатору
            const T& Get(Id id) const {
                auto elem = _id_elems.find(id);
                try {
                    if(elem == _id_elems.end() && elem.second == _elems.end()) {
                        return {};
                    }
                    return elem->second.first;
                } catch (const exception& ex) {
                    return {};
                }
            }

            // Увеличить приоритет объекта на 1
            void Promote(Id id) {
                auto elem = _id_elems.find(id);
                try {
                    if(elem == _id_elems.end() && elem->second == _elems.end())
                        return;
                    pair<T, int> to_fix = get_and_del_by_iter(elem->second);
                    ++to_fix.second;
                    _id_elems.erase(id);
                    _id_elems[id] = _elems.insert(move(to_fix)).first;  
                } catch (const exception& ex) {
                    return;
                }
            }

            // Получить объект с максимальным приоритетом и его приоритет
            pair<const T&, int> GetMax() const {
                return prev(_elems.end());
            }

            // Аналогично GetMax, но удаляет элемент из контейнера
            pair<T, int> PopMax() {
                auto temp = get_and_del_by_iter(prev(_elems.end()));
                return move(temp);
            }
        private:
            pair<T, int> get_and_del_by_iter(const typename set<pair<T, int>>::iterator& it) {
                auto elem = _elems.extract(it);
                if(!elem.empty())
                    return move(elem.value());
                return {};
            }
            
        private:
            Id _last_id = 0;
            set<pair<T, int>> _elems;
            map<Id, typename set<pair<T, int>>::iterator> _id_elems;
    };

    template<typename T>
    bool operator<(const pair<T, int>& f, const pair<T, int>& s) {
        if(f.first != s.first) {
            if(!(f.second > s.second))
                return true; 
        }   
        return false;
    }

    struct Stats2 {
        map<string, int> word_frequences;

        void operator += (const Stats2& other);
    };

    template <typename T>
    class Synchronized {
        public:
            explicit Synchronized(T initial = T())
                : _value(initial) {}

            struct Access {
                Access(T& value, mutex& m)
                    : ref_to_value(value),
                    lock(m) {}

                T& ref_to_value;
                unique_lock<mutex> lock;
            };

            Access GetAccess() {
                return Access(_value, _m);
            }
        private:
            T _value;
            mutex _m;
    };

    template <typename K, typename V>
    class ConcurrentMap {
        public:
            using count = size_t;
            using max_elem = int;
        
            static_assert(is_integral_v<K>, "ConcurrentMap supports only integer keys");

            struct Access {
                Access(V& value, mutex& m)
                    : ref_to_value(value),
                    lock(m) {}

                V& ref_to_value;
                unique_lock<mutex> lock;
            };

            explicit ConcurrentMap(size_t bucket_count)
                :_mutexes(bucket_count),
                _ranges(bucket_count) {}

            Access operator[](const K& key) {
                unique_lock<mutex> lock(m);
                size_t index = find_chanck_index(key);

                if(_elems.find(key) != _elems.end())
                    return Access(_elems[key], _mutexes[index]);

                V& to_res = _elems.emplace(make_pair(key, V())).first->second;
                add_elem(index, key);
                return Access(to_res, _mutexes[index]);
            }

            map<K, V> BuildOrdinaryMap() {
                return _elems;
            }
        private:
            size_t find_chanck_index(const K& key) {
                for(size_t i = 0; i < _ranges.size(); ++i) {
                    if(_ranges[i].size() == 0
                        || *prev(_ranges[i].end()) <= key)
                        return i;
                }
                return _ranges.size() - 1;
            }
            void add_elem(size_t index, const K& key) {
                _ranges[index].insert(key);
                if(index != 0)
                    redistribute_elems(index);
            }
            void redistribute_elems(size_t index) {
                for(; index > 0; --index) {
                    if(_ranges[index].size() <= _ranges[index - 1].size() * 2)
                        return;
                    size_t count_to_move = _ranges[index].size();
                    size_t i = 0;
                    for(auto it = _ranges[index].begin();
                        it != _ranges[index].end() && i < count_to_move;
                        it = _ranges[index].begin(), ++i) {
                        _ranges[index - 1].insert(*it);
                        _ranges[index].erase(it);
                    }
                }
            }
        private:
            mutex m;
            vector<mutex> _mutexes;
            vector<set<K>> _ranges;
            map<K, V> _elems;
    };

    void fifth_weak();

    void sixth_weak();
    
    void test();
}