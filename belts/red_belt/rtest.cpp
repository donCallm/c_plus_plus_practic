#include "rtest.hpp"

namespace rbelt {    
    template<typename func>
    void run_test::run(func f, const string& test_name) {
        try {
            f();
            cout << test_name << ':' << "ok" << endl;
        } catch(const std::exception& e) {
            cerr << test_name << ':' << "bad" << endl;
            ++err_count;
        }
    }

    run_test::~run_test() {
        if (err_count != 0)
            terminate();
    }
    
    void Logger::Log(const string& message) {
        if (log_file && !log_line) {
            os << file_name << " " << message << endl;
        } else if (!log_file && log_line) {
            os << "Line" << ' ' << to_string(line) << ' ' << message << endl;
        } else if (log_file && log_line) {
            os << file_name << ':' << to_string(line) << ' ' << message << endl;
        } else {
            os << message << endl;
        }
    }

    bool operator<(const Date& l, const Date&r) {
        if (l.year < r.year ||
            l.month < r.month ||
            l.day < r.day)
            return true;
        return false;
    }

        ostream& operator<<(ostream& os, const Time& t) {
        os << "Hours: " << t.hours << endl;
        os << "Minutes: " << t.minutes << endl;
        return os;
    }

    ostream& operator<<(ostream& os, const Date& d) {
        os << "Year: " << d.year << endl;
        os << "Month: " << d.month << endl;
        os << "Day: " << d.day << endl;
        return os;
    }

    ostream& operator<<(ostream& os, const AirlineTicket& a) {
        os << "From: " << a.from << endl;
        os << "To: " << a.to << endl;
        os << "Airline: " <<a.airline << endl;
        os << "Depart date: " << a.departure_date << endl;
        os << "Depart time: " << a.departure_time << endl;
        os << "Arriv date: " << a.arrival_date << endl;
        os << "Arriv time: " << a.arrival_time << endl;
        os << "Price: " <<a.price << endl;
        return os;
    }

    bool operator==(const Time& l, const Time& r) {
        if (r.hours == l.hours &&
            r.minutes == l.minutes)
            return true;
        return false;
    }

    bool operator==(const Date& l, const Date& r) {
        if (l.day == r.day &&
            l.month == r.month&&
            l.year == r.year)
            return true;
        return false;
    }

        bool operator==(const AirlineTicket& l, const AirlineTicket& r) {
        if (l.to == r.to && l.price == r.price &&
            l.airline == r.airline && l.from == r.from &&
            l.departure_date == r.departure_date &&
            l.departure_time == r.departure_time &&
            l.arrival_date == r.arrival_date &&
            l.arrival_time == l.arrival_time)
            return true;
        return false;
    }

    bool operator!=(const Date& l, const Date& r) {
        return !(l == r);
    }

    bool operator!=(const AirlineTicket& l, const AirlineTicket& r) {
        return !(l == r);
    }

    istream& operator>>(istream& is, Date& d) {
        is.ignore(6);
        is >> d.year;
        is.ignore(7);
        is >> d.month;
        is.ignore(5);
        is >> d.day;

        return is;
    }

    istream& operator>>(istream& is, Time& t) {
        is.ignore(7);
        is >> t.hours;
        is.ignore(9);
        is >> t.minutes;

        return is;
    }

    template<typename T1, typename T2>
    ostream& operator<<(ostream& os, const pair<T1, T2>& p) {
        os << "First: " << p.first << " Second: " << p.second;
        return os;
    }

    template<typename T>
    ostream& operator<<(ostream& os, const vector<T>& v) {
        for (auto& item : v)
            os << item << ' ';
        return os;
    }

    template<typename ItType>
    ostream& operator<<(ostream& os, Page<ItType> page) {
        os << "Page: ";
        for (auto& item : page)
            os << item << ' ';
        return os;
    }

    template<typename ItType>
    ostream& operator<<(ostream& os, Paginator<ItType> paginator) {
        os << "Paginator:";
        for (auto& page : paginator)
            os << endl << page;
        return os;
    }

    bool Student::operator<(const Student& other) const {
        return GetName() < other.GetName();
    }

    bool Student::Less(const Student& other) const {
        return rating > other.rating;
    }

    string Student::GetName() const {
        return first_name + " " + last_name;
    }

    bool Compare(const Student& first, const Student& second) {
        return first.Less(second);
    }

    void TestSortBy() {
        vector<AirlineTicket> tixs = {
            {"VKO", "AER", "Utair",     {2018, 2, 28}, {17, 40}, {2018, 2, 28}, {20,  0}, 1200},
            {"AER", "VKO", "Utair",     {2018, 3,  5}, {14, 15}, {2018, 3,  5}, {16, 30}, 1700},
            {"AER", "SVO", "Aeroflot",  {2018, 3,  5}, {18, 30}, {2018, 3,  5}, {20, 30}, 2300},
            {"PMI", "DME", "Iberia",    {2018, 2,  8}, {23, 00}, {2018, 2,  9}, { 3, 30}, 9000},
            {"CDG", "SVO", "AirFrance", {2018, 3,  1}, {13, 00}, {2018, 3,  1}, {17, 30}, 8000},
        };

        sort(begin(tixs), end(tixs), SORT_BY(price));
        assert<int>(tixs.front().price, 1200);
        assert<int>(tixs.back().price, 9000);

        sort(begin(tixs), end(tixs), SORT_BY(from));
        assert<string>(tixs.front().from, "AER");
        assert<string>(tixs.back().from, "VKO");

        sort(begin(tixs), end(tixs), SORT_BY(arrival_date));
        assert(tixs.front().arrival_date, (Date{2018, 2, 9}));
        assert(tixs.back().arrival_date, (Date{2018, 3, 5}));
    }   

    void UpdateTicket(AirlineTicket& ticket, const map<string, string>& updates) {
        std::map<std::string, string>::const_iterator it;
        UPDATE_FIELD(ticket, from, updates);
        UPDATE_FIELD(ticket, to, updates);
        UPDATE_FIELD(ticket, airline, updates);
        UPDATE_FIELD(ticket, departure_date, updates);
        UPDATE_FIELD(ticket, departure_time, updates);
        UPDATE_FIELD(ticket, arrival_date, updates);
        UPDATE_FIELD(ticket, arrival_time, updates);
        UPDATE_FIELD(ticket, price, updates);
    }

    void test_log() {
        ostringstream logs;
        Logger l(logs);
        LOG(l, "hello");

        l.SetLogFile(true);
        LOG(l, "hello");

        l.SetLogLine(true);
        LOG(l, "hello");

        l.SetLogFile(false);
        LOG(l, "hello");

        string expected = "hello\n";
        expected += "/home/egor/Documents/code/alghoritms/belts/red_belt/rtest.cpp hello\n";
        expected += "/home/egor/Documents/code/alghoritms/belts/red_belt/rtest.cpp:51 hello\n";
        expected += "Line 54 hello\n";
        assert(logs.str(), expected);
    }

    void test_update_tickets() {
        AirlineTicket t;
        t.price = 5000;
        t.from = "DME";
        t.to = "AER";

        const map<string, string> updates = {
            {"price", "3500"},
            {"from", "VKO"}
        };

        UpdateTicket(t, updates);

        assert(t.from, string("VKO"));
        assert(t.to, string("AER"));
        assert(t.price, 3500);
    }

    void test_cout_def() {
        ostringstream os;
        string expected = "test1\ntest1\n0\n0\n1\n1\n2\n2\n3\n3\n4\n4\n";

        PRINT_VALUES(os, "test1", "test1")

        for (size_t i = 0; i < 5; ++i)
            PRINT_VALUES(os, i, i)
        
        assert(os.str(), expected);
    }

    void test_uniq_id_def() {
        int UNIQ_ID = 5;
        string UNIQ_ID = "hello!";
        int UNIQ_ID = 5; string UNIQ_ID = "hello";
    }

    void test_table() {
        Table<int> t(3, 3);
        auto size = t.Size();
        assert(size, {3, 3});
        for (size_t i = 0; i < size.first; ++i) {
             for (size_t j = 0; j < size.second; ++j) {
                t[i][j] = j;
             }
        }

        vector<int> expected1 = {0, 1, 2};
        assert(t[0], expected1);

        t.Resize(2, 2);
        size = t.Size();
        assert(size, {2, 2});

        vector<int> expected2 = {0, 1};
        assert(t[0], expected2);
    }

    void test_deque() {
        Deque<int> d;
        int new_elem = 2;
        d.PushFront(new_elem);
        new_elem = 1;
        d.PushFront(new_elem);
        new_elem = 3;
        d.PushBack(new_elem);
        new_elem = 4;
        d.PushBack(new_elem);
        int expected = 1;
        assert(d.Front(), expected);
        expected = 4;
        assert(d.Back(), expected);
        int size = d.Size();
        assert(size, expected);
    }

    void test_paginator() {
        vector<int> v(40, 1);
        auto res = Paginate<vector<int>>(v, 5);
        cout << res << endl;

        vector<int> v1(39, 1);
        auto res1 = Paginate<vector<int>>(v1, 5);
        cout << res1 << endl;
    }

    void first_weak() {
        cout << "______First weak______" << endl;
        run_test rt;
        cout << "---------------------" << endl << "1." << endl;
        //rt.run(test_log, "test_log");
        cout << "Done" << endl;
        cout << "---------------------" << endl << "2." << endl;
        rt.run(TestSortBy, "test_sort_by");
        cout << "---------------------" << endl << "3." << endl;
        rt.run(test_update_tickets, "test_update_tickets");
        cout << "---------------------" << endl << "4." << endl;
        rt.run(test_cout_def, "test_cout_def");
        cout << "---------------------" << endl << "5." << endl;
        rt.run(test_uniq_id_def, "test_uniq_id_def");
        cout << "---------------------" << endl << "6." << endl;
        rt.run(test_table, "test_table");
        cout << "---------------------" << endl << "7." << endl;
        rt.run(test_deque, "test_deque");
        cout << "---------------------" << endl << "8." << endl;
        rt.run(test_paginator, "test_paginator");
    }
    
    int Learner::Learn(const vector<string>& words) {
        int old_size = dict.size();
        for (const auto& word : words)
            dict.emplace(word);

        
        int res = dict.size() - old_size; 
        return res;
    }

    set<string>& Learner::KnownWords() { return dict; }

    void test_lerner() {
        {
            LogDuration log("lern");
            Learner l;
            vector<string> words = {"q","w","e","r","t","y",
                "u","i","o","p","a","s", "d","f","g","h","j","k"
                "l","z","x","c","v","b"};
            l.Learn(words);
        }

        {
            Learner l;
            vector<string> words = {"q","w","e","r","t","y",
                "u","i","o","p","a","s", "d","f","g","h","j","k"
                "l","z","x","c","v","b"};
            l.Learn(words);
            LogDuration log("read");
            auto res = l.KnownWords();
        }
    }

    void RouteManager::AddRoute(int start, int finish) {
        reachable_lists_[start].insert(finish);
        reachable_lists_[finish].insert(start);
    }

    int RouteManager::FindNearestFinish(int start, int finish) const {
        int result = abs(start - finish);
        if (reachable_lists_.count(start) < 1) {
            return result;
        }
        const set<int>& reachable_stations = reachable_lists_.at(start);

        auto finish_pos = reachable_stations.lower_bound(finish);
        if (finish_pos != reachable_stations.end()) {
            result = min(result, abs(finish - *finish_pos));
        }
        if (finish_pos != reachable_stations.begin()) {
            result = min(result, abs(finish - *prev(finish_pos)));
        }
        return result;
    }

    void test_route() {
        vector<stringstream> input;
        input.emplace_back("ADD -2 5");
        input.emplace_back("ADD 10 4");
        input.emplace_back("ADD 5 8");
        input.emplace_back("GO 4 10");
        input.emplace_back("GO 4 -2");
        input.emplace_back("GO 5 0");
        input.emplace_back("GO 5 100");
        for (size_t i = 7; i < 100000; ++i)
            input.emplace_back("GO 5 100");
        RouteManager routes;

        LogDuration log("route_manager");
        for (int query_id = 0; query_id < 100000; ++query_id) {
            string query_type;
            input[query_id] >> query_type;
            input[query_id].ignore(1);
            int start, finish;
            input[query_id] >> start;
            input[query_id].ignore(1);
            input[query_id] >> finish;
            if (query_type == "ADD") {
                routes.AddRoute(start, finish);
            } else if (query_type == "GO") {
                routes.FindNearestFinish(start, finish);
            }
        }
    }

    void test_students() {
        Student newbie
        {
            "Ivan", "Ivanov", 
                {
                    {"c++", 1.0},
                    {"algorithms", 3.0}
                }, 
            2.0
        };

        Student cpp_expert
        {
            "Petr", "Petrov", 
        {
            {"c++", 9.5},
            {"algorithms", 6.0}
        },
            7.75
        };

        Student guru
        {
            "Sidor", "Sidorov", 
        {
            {"c++", 10.0},
            {"algorithms", 10.0}
        },
            10.0
        };
        bool expected = true;
        assert(Compare(guru, newbie), expected, "1");
        assert(Compare(guru, cpp_expert), expected, "2");
        assert(!Compare(newbie, cpp_expert), expected, "3");

        {
            LogDuration log("log students");
            std::vector<Student> students
            {
                {"Sidor", "Sidorov", {{"maths", 2.}}, 2.},
                {"Semen", "Semenov", {{"maths", 4.}}, 4.},
                {"Ivan", "Ivanov", {{"maths", 5.}}, 5.},
                {"Petr", "Petrov", {{"maths", 3.}}, 3.},
                {"Alexander", "Alexandrov", {{"maths", 1.}}, 1.}};
    
            std::sort(students.begin(), students.end(), Compare);
            string expected1 = "Ivan";
            assert(students.begin()->first_name, expected1);
        }
    }

    void ReadingManager::Read(int user_id, int page_count) {
        User target(user_id, page_count);
        if (_users.find(target) == _users.end()) {
            AddUser(target);
            return;
        }
        auto user = *_users.find(target);
        user = target;
    }

    double ReadingManager::Cheer(int user_id) const {
        if (_pages.find(user_id) == _pages.end())
            return 0;
        User target(user_id, _pages.at(user_id));
        auto pos = _users.find(target);
        if (pos == _users.end()) {
            return 0;
        }

        const int user_count = GetUserCount();
        if(user_count == 1)
            return 1;

        int dist = distance(_users.begin(), pos);
        if (dist == 0)
            return 0;

        return dist * 1.0 / (user_count - 1);
    }

    void ReadingManager::AddUser(User usr) {
        if (GetUserCount() < MAX_USER_COUNT_ - 1) {
            _users.insert(usr);
            _pages.insert({usr.id, usr.page_count});
        }
    }

    void test_reading_manager() {
        vector<stringstream> input;
        input.emplace_back("CHEER 5");
        input.emplace_back("READ 1 10");
        input.emplace_back("READ 2 5");
        input.emplace_back("READ 3 7");
        input.emplace_back("READ 4 6");
        input.emplace_back("READ 5 9");
        input.emplace_back("READ 6 108");
        input.emplace_back("READ 7 106");
        input.emplace_back("READ 9 1");
        input.emplace_back("READ 12 10");
        input.emplace_back("READ 14 111");
        input.emplace_back("CHEER 1");
        input.emplace_back("CHEER 12");
        input.emplace_back("CHEER 13");
        input.emplace_back("READ 8 199");
        input.emplace_back("CHEER 11");
        input.emplace_back("CHEER 1");
        input.emplace_back("CHEER 2");
        input.emplace_back("READ 13 102");
        input.emplace_back("CHEER 3");
        input.emplace_back("CHEER 4");
        input.emplace_back("READ 11 1033");
        input.emplace_back("CHEER 2");
        input.emplace_back("CHEER 5");
        input.emplace_back("READ 3 11");
        input.emplace_back("READ 3 10");
        input.emplace_back("CHEER 5");
        input.emplace_back("CHEER 5");
        input.emplace_back("CHEER 5");
        input.emplace_back("READ 19 105");

        for (size_t i = input.size(); i < 10000; ++i) {
            string id = "2" + to_string(i);
            string lines = "1" + to_string(i);
            string all = "READ " + id + " " + lines;
            input.emplace_back("READ");
        }
        

        for (size_t i = input.size(); i < 20000; ++i) {
            input.emplace_back("CHEER 1");
            input.emplace_back("CHEER 5");
            input.emplace_back("CHEER 13");
        }

        ReadingManager manager;
        LogDuration log("reading_manager");
        for (int query_id = 0; query_id < input.size(); ++query_id) {
            string query_type;
            input[query_id] >> query_type;
            int user_id;
            input[query_id].ignore(1);
            input[query_id] >> user_id;

            if (query_type == "READ") {
                int page_count;
                input[query_id].ignore(1);
                input[query_id] >> page_count;
                manager.Read(user_id, page_count);
            } else if (query_type == "CHEER") {
                cout << setprecision(6) << manager.Cheer(user_id) << "\n";
            }
        }
    }

    void booking_manager::book(uint64_t time, const string& hotel_name,
        uint64_t client_id, uint64_t room_count) {
        hotel& current_hotel = _hotels[hotel_name];

        client& current_client = current_hotel.clients[client_id]; 
        current_client.rooms[time] += room_count;
        
        last_time = time;

        auto temp = current_client.rooms.lower_bound((last_time - one_day));
        current_client.rooms.erase(current_client.rooms.begin(), prev(temp));
    }

    void test_booking_manager() {
        booking_manager bm;
        vector<stringstream> input;
        input.emplace_back("1 Marriott");
        input.emplace_back("2 Marriott");
        input.emplace_back("0 10 FourSeasons 1 2");
        input.emplace_back("0 10 Marriott 1 1");
        input.emplace_back("0 86409 FourSeasons 2 1");
        input.emplace_back("1 FourSeasons");
        input.emplace_back("2 FourSeasons");
        input.emplace_back("1 Marriott");
        input.emplace_back("0 86410 Marriott 2 10");
        input.emplace_back("2 FourSeasons");
        input.emplace_back("2 Marriott");
        
        input.emplace_back("0 864011 FourSeasons 3 1");
        input.emplace_back("0 86412 FourSeasons 4 1");
        input.emplace_back("0 86412 FourSeasons 5 1");
        input.emplace_back("0 86412 FourSeasons 6 1");
        input.emplace_back("0 86412 FourSeasons 7 1");
        input.emplace_back("0 86412 FourSeasons 8 1");
        input.emplace_back("0 86412 FourSeasons 9 1");
        input.emplace_back("0 86412 FourSeasons 10 1");
        input.emplace_back("0 86412 FourSeasons 11 1");
        input.emplace_back("0 86412 FourSeasons 12 1");

        for (size_t i = input.size(); i < 40000; ++i) {
            input.emplace_back("1 FourSeasons");            
            input.emplace_back("2 FourSeasons");
        }
        
        LogDuration log("booking_maneger");
        for (size_t i = 0; i < input.size(); ++i) {
            string comm;
            input[i] >> comm;
            input[i].ignore(1);
            switch (stoull(comm)) {
                case booking_manager::comms::BOOK: {
                    string time, hotel_name, client_id, room_count;;
                    input[i] >> time;
                    input[i].ignore(1);
                    input[i] >> hotel_name;
                    input[i].ignore(1);
                    input[i] >> client_id;
                    input[i].ignore(1);
                    input[i] >> room_count;
                    bm.book(stoull(time), hotel_name,
                        stoull(client_id), stoull(room_count));
                    break;
                }
                case booking_manager::comms::CLIENTS: {
                    string hotel_name;
                    input[i] >> hotel_name;
                    cout << bm.clients_count(hotel_name) << '\n';
                    break;
                }
                case booking_manager::comms::ROOMS: {
                    string hotel_name;
                    input[i] >> hotel_name;
                    cout << bm.rooms(hotel_name) << '\n';
                    break;
                }
                default:
                    break;
            }
        }
    }

    void second_weak() {
        run_test rt;
        cout << "______Second weak______" << endl;
        cout << "---------------------" << endl << "1." << endl;
        rt.run(test_students, "test_students");
        cout << "---------------------" << endl << "2." << endl;
        rt.run(test_lerner, "test_lerner");
        cout << "---------------------" << endl << "3." << endl;
        rt.run(test_route, "test_route");
        cout << "---------------------" << endl << "4." << endl;
        //rt.run(test_reading_manager, "test_reading_manager");
        cout << "Done" << endl;
        cout << "---------------------" << endl << "5." << endl;
        rt.run(test_booking_manager, "test_booking_manager");
         
    }

    template<class T>
    void set_queue<T>::push(T* val) {
        auto it = _to_check.lower_bound(val);
        if (it != _to_check.end())
            return;
        
        _to_check.insert(val);
        _elems.push_back(val);
    }

    template<class T>
    void set_queue<T>::pop() {
        if (_elems.empty())
            return;

        _to_check.erase(_elems.front());
        _elems.pop_front();
    }

    template<class T>
    void set_queue<T>::delete_by_elem(T* elem) {
        auto d_it = find(_elems.begin(), _elems.end(), elem);
        
        _to_check.erase(elem);
        _elems.erase(d_it);
    }

    template<class T>
    bool set_queue<T>::exist(T* val) {
        auto it = _to_check.lower_bound(val);
        if (it != _to_check.end())
            return true;
        return false;
    }

    template<class T>
    T* ObjectPool<T>::Allocate() {
        T* res = nullptr;

        if (_liberated.empty()) {
            res = new T;
        } else {
            res = _liberated.front();
            _liberated.pop();
        }

        _dedicated.push(res);
        return res;
    }

    template<class T>
    T* ObjectPool<T>::TryAllocate() {
        if (_liberated.empty())
            return nullptr;

        T* res = _liberated.front();
        _liberated.pop();
        _dedicated.push(res);
        return res;
    }

    template<class T>
    void ObjectPool<T>::Deallocate(T* object) {
        if (!_dedicated.exist(object))
            throw invalid_argument("");
        _dedicated.delete_by_elem(object);
        _liberated.push(object);
    }

    void test_object_pool() {
        ObjectPool<string> op;
        string obj("xui");
        string* res = op.Allocate();
        *res = obj;
        cout << *res << endl;
        op.Deallocate(res);
    }

    template<typename T> 
    void Swap(T* first, T* second) {
        T temp = *first;
        *first = *second;
        *second = temp;
    }

    template<typename T>
    void SortPointers(vector<T*>& pointers) {
        for (size_t i = 0; i < pointers.size(); ++i) {
            for (size_t j = 0; j < pointers.size() - 1; ++j) {
                if (*pointers[j] > *pointers[j + 1]) {
                    Swap(pointers[j], pointers[j + 1]);
                }
            }
        }
    }

    template<typename T>
    void ReversedCopy(T* src, size_t count, T* dst) {
        for (size_t i = 0; i < count; ++i) {
            if (src != dst) {
                *(dst + i) = *(src + ((count - 1) - i));
            }
        }
    }

    void test_swap_sort_copy() {
        int i = 10;
        vector<int*> v1(i);
        for (auto& item : v1)
            item = new int(--i);
        
        SortPointers(v1);
        for (auto& item : v1)
            cout << *item << ' ';
        cout << endl;

        int* arr1 = new int[10];
        for (size_t i = 0; i < 10; ++i)
            arr1[i] = i;

        int* arr2 = new int[5];
        ReversedCopy(arr1, 5, arr2);

        for (int i = v1.size() - 1; i >= 0; --i)
            delete v1[i];

        for (int i = 0; i < 10; ++i)
            cout << arr1[i] << ' ';
        cout << endl;
        for (int i = 0; i < 5; ++i)
            cout << arr2[i] << ' ';
        cout << endl;

        delete[] arr1;
        delete[] arr2;
    }

    template<typename T>
    SimpleVector<T>:: SimpleVector(size_t size) 
        : _capacity(size),
        _size(size) {
        _begin = new T[_capacity];
    }

    template<typename T>
    void SimpleVector<T>::PushBack(T value) {
        try_realloc();
        *(_begin + _size++) = move(value);
    }

    // template<typename T>
    // void SimpleVector<T>::PushBack(T&& value) {
        // try_realloc();
        // *(_begin + _size++) = move(value);        
    // }

    template<typename T>
    void SimpleVector<T>::try_realloc() {
        if (_capacity == 0) {
            _begin = new T[++_capacity];
        } else if (_size == _capacity) {
            _capacity *= 2;
            T* buffer = new T[_capacity];
            for(size_t i = 0; i < _size; ++i)
                buffer[i] = move(_begin[i]);
            delete[] _begin;
            _begin = buffer;
        }
    }

    void test_simpe_vector() {
        SimpleVector<int> v;
        size_t expected = 0;
        assert(v.Size(), expected);

        size_t n = 10;
        for (size_t i = 0; i < n; ++i)
            v.PushBack(i);
        
        for (size_t i = 0; i < n; ++i)
            cout << v[i] << ' ';
        cout << endl;
    }

    template<typename T>
    void LinkedList<T>::RemoveAfter(Node* node) {
        Node* after = node->next;
        node->next = after->next;
        delete after;
    }

    template<typename T>
    void LinkedList<T>::PopFront() {
        Node* second = head->next;
        delete head;
        head = second;
    }

    template<typename T>
    void LinkedList<T>::insert(Node* node, const T& value) {
        if (head == nullptr) {
            head = new Node;
            head->value = value;
        } else {
            Node* nxt = head;
            while (nxt->next != nullptr)
                nxt = nxt->next;
            nxt->next = new Node;
            nxt->next->value = value;
        }
    }

    void test_list() {
        LinkedList<int> list;
        for (size_t i = 0; i < 10; ++i)
            list.PushFront(i);
        
        auto head = list.GetHead();
        while(head != nullptr) {
            cout << head->value << ' ';
            head = head->next;
        }
        cout << endl;

        list.PopFront();
        auto head1 = list.GetHead();
        while(head1 != nullptr) {
            cout << head1->value << ' ';
            head1 = head1->next;
        }
        cout << endl;
    }
    
    void third_weak() {
        run_test rt;
        cout << "______Third weak______" << endl;
        cout << "---------------------" << endl << "1." << endl;
        rt.run(test_object_pool, "test_object_pool");
        cout << "---------------------" << endl << "2." << endl;
        rt.run(test_swap_sort_copy, "test_swap_sort_copy");
        cout << "---------------------" << endl << "3." << endl;
        rt.run(test_simpe_vector, "test_simpe_vector");
        cout << "---------------------" << endl << "4." << endl;
        rt.run(test_list, "test_list");
    }

    void football_players(vector<istringstream>& input) {
        list<int> players;
        for (auto& item : input) {
            string first, second;
            item >> first;
            item.ignore(1);
            item >> second;
            auto it = find(players.begin(), players.end(), stoi(second));
            if (it == players.end())
                players.push_back(stoi(first));
            else
                players.insert(it, stoi(first));
        }

        for (auto iter = players.begin(); iter != players.end(); ++iter)
            cout << *iter << ' ';
        cout << endl;
    }

    void test_football_players() {
        vector<istringstream> input;
        input.emplace_back("42 0 ");
        input.emplace_back("17 42");
        input.emplace_back("13 0");
        input.emplace_back("123 42");
        input.emplace_back("5 13");

        football_players(input);
    }

    void test_stack_vector() {
        StackVector<int, 5> v;
        v.PushBack(5);
        v.PushBack(5);
        v.PushBack(5);
        v.PushBack(5);
        v.PushBack(5);

        size_t expected = 5;
        assert(v.Size(), expected);
        
        auto it = v.begin();
        cout << *it << endl;    

        for (size_t i = 0; i < v.Capacity(); ++i)
            cout << v.PopBack() << ' ';
        cout << endl;

        expected = 0;
        assert(v.Size(), expected);
    }

    void Translator::Add(string_view source, string_view target) {
        string f(source);
        string s(target);

        auto f_it = _words.find(f);
        if (f_it != _words.end())
            return;
        auto s_it = _words.find(s);
        if (s_it != _words.end())
            return;
        
        _translate_eng_ru[f] = s;
        _translate_ru_eng[s] = f;
    }

    string_view Translator::TranslateForward(string_view source) const {
        string str(source);
        if(_translate_eng_ru.find(str) != _translate_eng_ru.end())
            return _translate_eng_ru.at(string(source));
        return "";
    }

    string_view Translator::TranslateBackward(string_view target) const {
        string str(target);
        if(_translate_ru_eng.find(str) != _translate_eng_ru.end())
            return _translate_ru_eng.at(string(target));
        return "";
    }

    void test_translator() {
        Translator ts;
        ts.Add("penis", "пенис");
        auto word = ts.TranslateBackward("пенис");
        cout << word << endl;
        word = ts.TranslateForward("penis");
        cout << word << endl;
        ts.Add("penis", "пенис");
    }

    void TestMoscow() {
        enum class MoscowAirport {
            VKO,
            SVO,
            DME,
            ZIA,
            Last_
        };

        const vector<MoscowAirport> airports = {
            MoscowAirport::SVO,
            MoscowAirport::VKO,
            MoscowAirport::ZIA,
            MoscowAirport::SVO,
        };
        AirportCounter<MoscowAirport> airport_counter(begin(airports), end(airports));

        assert<size_t>(airport_counter.Get(MoscowAirport::VKO), 1);
        assert<size_t>(airport_counter.Get(MoscowAirport::SVO), 2);
        assert<size_t>(airport_counter.Get(MoscowAirport::DME), 0);
        assert<size_t>(airport_counter.Get(MoscowAirport::ZIA), 1);

        using Item = AirportCounter<MoscowAirport>::Item; //Item ==  pair<MoscowAirport, size_t>
        vector<Item> items;
        for (const auto& item : airport_counter.GetItems()) {
            items.push_back(item);
        }
        assert<size_t>(items.size(), 4);

        #define ASSERT_EQUAL_ITEM(idx, expected_enum, expected_count) \
        do { \
            assert(static_cast<size_t>(items[idx].first), static_cast<size_t>(MoscowAirport::expected_enum)); \
            assert<size_t>(items[idx].second, expected_count); \
        } while (false)

        // ASSERT_EQUAL_ITEM(0, VKO, 1);
        assert(static_cast<size_t>(items[0].first), static_cast<size_t>(MoscowAirport::VKO)); \
            assert<size_t>(items[0].second, 1);
        // ASSERT_EQUAL_ITEM(1, SVO, 2);
        assert(static_cast<size_t>(items[1].first), static_cast<size_t>(MoscowAirport::SVO)); \
            assert<size_t>(items[1].second, 2);
        // ASSERT_EQUAL_ITEM(2, DME, 0);
        assert(static_cast<size_t>(items[2].first), static_cast<size_t>(MoscowAirport::DME)); \
            assert<size_t>(items[2].second, 0);
        // ASSERT_EQUAL_ITEM(3, ZIA, 1);
        assert(static_cast<size_t>(items[3].first), static_cast<size_t>(MoscowAirport::ZIA)); \
            assert<size_t>(items[3].second, 1);

        airport_counter.Insert(MoscowAirport::VKO);
        assert<size_t>(airport_counter.Get(MoscowAirport::VKO), 2);

        airport_counter.EraseOne(MoscowAirport::SVO);
        assert<size_t>(airport_counter.Get(MoscowAirport::SVO), 1);

        airport_counter.EraseAll(MoscowAirport::VKO);
        assert<size_t>(airport_counter.Get(MoscowAirport::VKO), 0);
    }

    enum class SmallCountryAirports {
        Airport_1,
        Airport_2,
        Airport_3,
        Airport_4,
        Airport_5,
        Airport_6,
        Airport_7,
        Airport_8,
        Airport_9,
        Airport_10,
        Airport_11,
        Airport_12,
        Airport_13,
        Airport_14,
        Airport_15,
        Last_
    };

    void TestManyConstructions() {
        default_random_engine rnd(20180623);
        uniform_int_distribution<size_t> gen_airport(
            0, static_cast<size_t>(SmallCountryAirports::Last_) - 1
        );

        array<SmallCountryAirports, 2> airports;
        for (auto& x : airports) {
            x = static_cast<SmallCountryAirports>(gen_airport(rnd));
        }

        uint64_t total = 0;
        for (int step = 0; step < 100'000'000; ++step) {
            AirportCounter<SmallCountryAirports> counter(begin(airports), airports.end());
            total += counter.Get(airports[0]);
        }
        if (total < 1000)
            throw runtime_error("here");
    }

    enum class SmallTownAirports {
        Airport_1,
        Airport_2,
        Last_
    };

    void TestManyGetItems() {
        default_random_engine rnd(20180701);
        uniform_int_distribution<size_t> gen_airport(
            0, static_cast<size_t>(SmallTownAirports::Last_) - 1
        );

        array<SmallTownAirports, 2> airports;
        for (auto& x : airports) {
            x = static_cast<SmallTownAirports>(gen_airport(rnd));
        }

        uint64_t total = 0;
        for (int step = 0; step < 100'000'000; ++step) {
            AirportCounter<SmallTownAirports> counter(begin(airports), end(airports));
            total += counter.Get(SmallTownAirports::Airport_1);
            for (const auto [airport, count] : counter.GetItems()) {
                total += count;
            }
        }
    }

    void test_aiport_counter() {
        TestMoscow();
        TestManyConstructions();
        TestManyGetItems();
    }

    void test_editor() {
        Editor editor;
        const string text = "hello, world";
        for (char c : text) {
            editor.Insert(c);
        }
        // Текущее состояние редактора: `hello, world|`
        for (size_t i = 0; i < text.size(); ++i) {
            editor.Left();
        }
        // Текущее состояние редактора: `|hello, world`
        editor.Cut(7);
        // Текущее состояние редактора: `|world`
        // в буфере обмена находится текст `hello, `
        for (size_t i = 0; i < 5; ++i) {
            editor.Right();
        }
        // Текущее состояние редактора: `world|`
        editor.Insert(',');
        editor.Insert(' ');
        // Текущее состояние редактора: `world, |`
        editor.Paste();
        // Текущее состояние редактора: `world, hello, |`
        editor.Left();
        editor.Left();
        //Текущее состояние редактора: `world, hello|, `
        editor.Cut(3); // Будут вырезаны 2 символа
        // Текущее состояние редактора: `world, hello|`
        // cout << editor.GetText();
    }

    HttpRequest ParseRequest(string_view line) {
        vector<string_view> words;
        size_t last_pos = 0;
        size_t i = 0;

        while (true) {
            i = line.find(" ", last_pos);
            if (i == string_view::npos) {
                std::string_view temp = line.substr(last_pos, line.length());
                words.emplace_back(temp);
                break;
            }
            std::string_view temp = line.substr(last_pos, i);
            words.emplace_back(temp);
            last_pos = i + 1; 
        }

        return {words[0], words[1], words[2]};
    }

    Stats ServeRequests(istream& input) {
        Stats result;
        for (string line; getline(input, line); ) {
            const HttpRequest req = ParseRequest(line);
            result.AddUri(req.uri);
            result.AddMethod(req.method);
        }
        return result;
    }

    void test_web_stats() {
        istringstream input(R"(GET / HTTP/1.1
POST /order HTTP/1.1
POST /product HTTP/1.1
GET /order HTTP/1.1
PUT /product HTTP/1.1
GET /basket HTTP/1.1
DELETE /product HTTP/1.1
GET /help HTTP/1.1)");

        Stats s = ServeRequests(input);
        auto methods = s.GetMethodStats();
        auto uri = s.GetUriStats();
    }

    void fourt_weak() {
        run_test rt;
        cout << "______Fourth weak______" << endl;
        cout << "---------------------" << endl << "1." << endl;
        rt.run(test_football_players, "test_football_players");
        cout << "---------------------" << endl << "2." << endl;
        rt.run(test_stack_vector, "test_stack_vector");
        cout << "---------------------" << endl << "3." << endl;
        rt.run(test_translator, "test_translator");
        cout << "---------------------" << endl << "4." << endl;
        // rt.run(test_aiport_counter, "test_aiport_counter");
        cout << "done" << endl;
        cout << "---------------------" << endl << "5." << endl;
        rt.run(test_editor, "test_editor");
        cout << "---------------------" << endl << "6." << endl;
        rt.run(test_web_stats, "test_web_stats");
    }

    template <typename RandomIt>
    void swap_elem(const RandomIt& first, const RandomIt& second) {
        typename RandomIt::value_type temp = *first;
        *first = *second;
        *second = temp;
    }

    template <typename RandomIt>
    void MakeJosephusPermutation(RandomIt& first, RandomIt& last, uint32_t& step_size) {
        size_t pool_size(distance(first, last));
        size_t cur_pos = move(step_size) - 1;
        while (pool_size != 0) {
            swap_elem(first++, first + cur_pos);
            // *(first++) = move(*(fist + cur_pos));
            --pool_size;
            if (pool_size == 0) { 
                break;
            }
            cur_pos = (cur_pos + step_size - 1) % pool_size;
        }

    }

    void test_josephus_permitation() {
        vector<int> v;
        for (size_t i = 0; i < 100'000; ++i){
            v.push_back(i);
        }

        LogDuration l("first_task");
        auto begin = v.begin();
        auto end = v.end();
        uint32_t step_size = 100;
        MakeJosephusPermutation(begin, end, step_size);
    }
    
    void test_heavy_string() {
        {
            vector<string> strings = {"caab", "abc", "cccc", "bacc", "c"};
            auto groups = GroupHeavyStrings(strings);
            assert<size_t>(groups.size(), 2);
            sort(begin(groups), end(groups));  // Порядок групп не имеет значения
            assert(groups[0], vector<string>({"caab", "abc", "bacc"}));
            assert(groups[1], vector<string>({"cccc", "c"}));
        }

        {
            vector<string> strings = {"law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl"};
            auto groups = GroupHeavyStrings(strings);
            assert<size_t>(groups.size(), 4);
            sort(begin(groups), end(groups));  // Порядок групп не имеет значения
            assert(groups[0], vector<string>({"laptop", "paloalto"}));
            assert(groups[1], vector<string>({"law", "wall", "awl"}));
            assert(groups[2], vector<string>({"port"}));
            assert(groups[3], vector<string>({"top", "pot"}));
        }
    }

    void test_assigment_operator() {
        SimpleVector<int> numbers(10);
        iota(numbers.begin(), numbers.end(), 1);

        SimpleVector<int> dest;
        assert<size_t>(dest.Size(), 0u);

        dest = numbers;
        assert(dest.Size(), numbers.Size());
        assert(dest.Capacity() >= dest.Size());
        assert(equal(dest.begin(), dest.end(), numbers.begin()));  
    }

    template <typename Token>
    using Sentence = vector<Token>;

    // Класс Token имеет метод bool IsEndSentencePunctuation() const
    template <typename Token>
    vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
        vector<Sentence<Token>> res(1);

        size_t current_sentence = 0;
        for (size_t i = 0; i < tokens.size(); ++i) {
            if(tokens[i].IsEndSentencePunctuation() && i != (tokens.size() - 1)) {
                res.push_back(Sentence<Token>());
                res[current_sentence++].push_back(move(tokens[i]));
            } else {
                res[current_sentence].push_back(move(tokens[i]));
            }
        }
        
        return move(res);
    }

    struct TestToken {
        string data;
        bool is_end_sentence_punctuation = false;

        bool IsEndSentencePunctuation() const {
            return is_end_sentence_punctuation;
        }
        bool operator==(const TestToken& other) const {
            return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
        }
    };

    ostream& operator<<(ostream& stream, const TestToken& token) {
        return stream << token.data;
    }

    // Тест содержит копирования объектов класса TestToken.
    // Для проверки отсутствия копирований в функции SplitIntoSentences
    // необходимо написать отдельный тест.
    void test_splitting() {
        assert(
            SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
            vector<Sentence<TestToken>>({
                {{"Split"}, {"into"}, {"sentences"}, {"!"}}
            }),
            "first"
        );

        assert(
            SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
                    vector<Sentence<TestToken>>({{{"Split"}, {"into"}, {"sentences"}, {"!", true}}}),
            "second"
        );

        auto res = SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}}));
        auto expected = vector<Sentence<TestToken>>({{{"Split"}, {"into"}, {"sentences"}, {"!", true}}, {{"!", true}},{{"Without"}, {"copies"}, {".", true}}});
        assert(res, expected);
    }
    
    void test_move_push_back() {
        {
            SimpleVector<int> empty;
            assert<size_t>(empty.Size(), 0u);
            assert<size_t>(empty.Capacity(), 0u);
            assert(empty.begin() == empty.end());

            SimpleVector<string> five_strings(5);
            assert<size_t>(five_strings.Size(), 5u);
            assert(five_strings.Size() <= five_strings.Capacity());
            for (auto& item : five_strings) {
                assert(item.empty());
            }
            five_strings[2] = "Hello";
            assert<string>(five_strings[2], "Hello");
        }
        {
            SimpleVector<int> v;
            for (int i = 10; i >= 1; --i) {
                v.PushBack(i);
                assert(v.Size() <= v.Capacity());
            }
            sort(begin(v), end(v));

            const vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
            assert(equal(begin(v), end(v), begin(expected)));
        }
        {
            SimpleVector<StringNonCopyable> strings;
            static const int SIZE = 10;
            for (int i = 0; i < SIZE; ++i) {
                strings.PushBack(StringNonCopyable(to_string(i)));
            }

            for (int i = 0; i < SIZE; ++i) {
                assert<StringNonCopyable>(strings[i], to_string(i));
            }
        }
    }

    template<typename RandomIt>
    void MergeSort(RandomIt range_begin, RandomIt range_end) {
        size_t size = distance(range_begin, range_end);
        if (size < 2)
            return;
        
        vector<typename RandomIt::value_type> v(range_begin, range_end);
        size_t one_part = size / 3;

        MergeSort(v.begin(), (v.begin() + (one_part)));
        MergeSort(v.begin() + one_part, v.begin() + (one_part * 2));
        MergeSort(v.begin() + (one_part * 2), v.end());

        vector<typename RandomIt::value_type> temp_vec;
        merge(v.begin(), v.begin() + one_part,
            v.begin() + one_part, v.begin() + (one_part * 2),
            back_inserter(temp_vec));
        merge(temp_vec.begin(), temp_vec.end(),
            v.begin() + (one_part * 2), v.end(), range_begin);
    }

    void test_merge_sort() {
        vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
        MergeSort(begin(numbers), end(numbers));
        assert(is_sorted(begin(numbers), end(numbers)));
    }

    void test_priority_collection() {
        PriorityCollection<StringNonCopyable> strings;
        const auto white_id = strings.Add("white");
        const auto yellow_id = strings.Add("yellow");
        const auto red_id = strings.Add("red");

        strings.Promote(yellow_id);
        for (int i = 0; i < 2; ++i) {
            strings.Promote(red_id);
        }
        strings.Promote(yellow_id);
        {
            const auto item = strings.PopMax();
            assert<StringNonCopyable>(item.first, "red");
            assert<size_t>(item.second, 2);
        }
        {
            const auto item = strings.PopMax();
            assert<StringNonCopyable>(item.first, "yellow");
            assert<size_t>(item.second, 2);
        }
        {
            const auto item = strings.PopMax();
            assert<StringNonCopyable>(item.first, "white");
            assert<size_t>(item.second, 0);
        }
    }

    int64_t CalculateMatrixSum(const vector<vector<int64_t>>& matrix) {
        int64_t res = 0;

        vector<future<void>> futures;
        mutex m;
        size_t size = matrix.size();
        size_t i = 0;
        while (i < size) {
            futures.push_back(async([i, &m, &res, &matrix](){
                lock_guard<mutex> lock(m);
                res = accumulate(matrix[i].begin(), matrix[i].end(), res);
                }));
            ++i;   
        }

        for (auto& future : futures)
            future.get();

        return res;
    }

    void test_calculate_matrix_sum() {
    const vector<vector<int64_t>> matrix = {
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12},
            {13, 14, 15, 16}};
        assert<int64_t>(CalculateMatrixSum(matrix), 136);
    }

    void Stats2::operator+=(const Stats2& other) {
        for(const auto& item : other.word_frequences)
            word_frequences[item.first] += item.second;
    }

    Stats2 ExploreLine(const set<string>& key_words, const string& line) {
        Stats2 res;
        size_t last_pos = 0;
        for(size_t i = line.find(" ", last_pos); ;
            i = line.find(" ", last_pos)) {
            string word;
            if (i == string::npos) {
                word = string(line.begin() + last_pos, line.end());
            } else {
                word = string(line.begin() + last_pos, line.begin() + i);
            }
            if(key_words.find(word) != key_words.end())
                res.word_frequences[word] += 1;
            if(i == string::npos)
                break;
            last_pos = i + 1;
        }


        return move(res);
    }

    Stats2 ExploreKeyWordsSingleThread(
        const set<string>& key_words, istream& input
            ) {
        Stats2 result;
        for (string line; getline(input, line); ) {
            result += ExploreLine(key_words, line);
        }
        return result;
    }

    Stats2 ExploreKeyWords(const set<string>& key_words, istream& input) {
        Stats2 res;
        vector<future<Stats2>> futures;
        
        for (string line; getline(input, line); ) {
            futures.push_back(async([&key_words, line](){
                return ExploreLine(key_words, line); }
                ));
        }

        for(size_t i = 0; i < futures.size(); ++i) {
            res += futures[i].get();
        }
        
        return move(res);
    }

    ostream& operator<<(ostream& os, const map<string, int>& st) {
        for(const auto& item : st) {
            os << "first: " << item.first <<
                " second: " << item.second << "\n";
        }
        return os;
    }

    void test_basic() {
        const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

        stringstream ss;
        ss << "this new yangle service really rocks\n";
        ss << "It sucks when yangle isn't available\n";
        ss << "10 reasons why yangle is the best IT company\n";
        ss << "yangle rocks others suck\n";
        ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

        const auto stats = ExploreKeyWords(key_words, ss);
        const map<string, int> expected = {
            {"yangle", 6},
            {"rocks", 2},
            {"sucks", 1}
        };
        assert(stats.word_frequences, expected);
    }

    void TestConcurrentUpdate() {
        Synchronized<string> common_string;

        const size_t add_count = 50000;
        auto updater = [&common_string, add_count] {
            for (size_t i = 0; i < add_count; ++i) {
            auto access = common_string.GetAccess();
            access.ref_to_value += 'a';
            }
        };

        auto f1 = async(updater);
        auto f2 = async(updater);

        f1.get();
        f2.get();

        assert(common_string.GetAccess().ref_to_value.size(), 2 * add_count);
        }

        vector<int> Consume(Synchronized<deque<int>>& common_queue) {
        vector<int> got;

        for (;;) {
            deque<int> q;

            {
            // Мы специально заключили эти две строчки в операторные скобки, чтобы
            // уменьшить размер критической секции. Поток-потребитель захватывает
            // мьютекс, перемещает всё содержимое общей очереди в свою
            // локальную переменную и отпускает мьютекс. После этого он обрабатывает
            // объекты в очереди за пределами критической секции, позволяя
            // потоку-производителю параллельно помещать в очередь новые объекты.
            //
            // Размер критической секции существенно влияет на быстродействие
            // многопоточных программ.
            auto access = common_queue.GetAccess();
            q = move(access.ref_to_value);
            }

            for (int item : q) {
            if (item > 0) {
                got.push_back(item);
            } else {
                return got;
            }
            }
        }
    }

    void TestProducerConsumer() {
    Synchronized<deque<int>> common_queue;

    auto consumer = async(Consume, ref(common_queue));

    const size_t item_count = 100000;
    for (size_t i = 1; i <= item_count; ++i) {
        common_queue.GetAccess().ref_to_value.push_back(i);
    }
    common_queue.GetAccess().ref_to_value.push_back(-1);

    vector<int> expected(item_count);
    iota(begin(expected), end(expected), 1);
    assert(consumer.get(), expected);
    }

    void test_synchronized() {
        TestConcurrentUpdate();
        TestProducerConsumer();
    }

    void RunConcurrentUpdates(
    ConcurrentMap<int, int>& cm, size_t thread_count, int key_count
) {
  auto kernel = [&cm, key_count](int seed) {
    vector<int> updates(key_count);
    iota(begin(updates), end(updates), -key_count / 2);
    shuffle(begin(updates), end(updates), default_random_engine(seed));

    for (int i = 0; i < 2; ++i) {
      for (auto key : updates) {
        cm[key].ref_to_value++;
      }
    }
  };

  vector<future<void>> futures;
  for (size_t i = 0; i < thread_count; ++i) {
    futures.push_back(async(kernel, i));
  }
}

void TestConcurrentUpdate2() {
  const size_t thread_count = 3;
  const size_t key_count = 50000;

  ConcurrentMap<int, int> cm(thread_count);
  RunConcurrentUpdates(cm, thread_count, key_count);

  const auto result = cm.BuildOrdinaryMap();
  assert(result.size(), key_count);
  for (auto& [k, v] : result) {
    assert(v, 6, "Key = " + to_string(k));
  }
}

void TestReadAndWrite() {
  ConcurrentMap<size_t, string> cm(5);

  auto updater = [&cm] {
    for (size_t i = 0; i < 50000; ++i) {
      cm[i].ref_to_value += 'a';
    }
  };
  auto reader = [&cm] {
    vector<string> result(50000);
    for (size_t i = 0; i < result.size(); ++i) {
      result[i] = cm[i].ref_to_value;
    }
    return result;
  };

  auto u1 = async(updater);
  auto r1 = async(reader);
  auto u2 = async(updater);
  auto r2 = async(reader);

  u1.get();
  u2.get();

  for (auto f : {&r1, &r2}) {
    auto result = f->get();
    assert(all_of(result.begin(), result.end(), [](const string& s) {
      return s.empty() || s == "a" || s == "aa";
    }));
  }
}

void TestSpeedup() {
  {
    ConcurrentMap<int, int> single_lock(1);

    LogDuration("Single lock");
    RunConcurrentUpdates(single_lock, 4, 50000);
  }
  {
    ConcurrentMap<int, int> many_locks(100);

    LogDuration("100 locks");
    RunConcurrentUpdates(many_locks, 4, 50000);
  }
}

    void test_in_one_thread() {
        ConcurrentMap<int, int> single_lock(3);
        for (size_t i = 0; i < 1000; ++i) {
            single_lock[i].ref_to_value = i;
        }
        assert<size_t>(single_lock.BuildOrdinaryMap().size(), 1000);
        
    }

    void test_in_two_thread() {
        ConcurrentMap<int, int> single_lock(3);
        std::thread t1([&]() {
            for (size_t i = 0; i < 1000; ++i) {
                single_lock[i].ref_to_value = i;
            }
        });

        std::thread t2([&]() {
            for (size_t i = 1000; i < 2000; ++i) {
                single_lock[i].ref_to_value = i;
            }
        });

        t1.join();
        t2.join();

        assert<size_t>(single_lock.BuildOrdinaryMap().size(), 2000);
    }

    void test_concurrent_map() {
        test_in_one_thread();
        test_in_two_thread();
        // TestConcurrentUpdeate2();
        // TestReadAndWrite();
        // TestSpeedup();
    }

    void fifth_weak() {
        cout << "______Fifth weak______" << endl;
        run_test rt;
        cout << "---------------------" << endl << "1." << endl;
        rt.run(test_josephus_permitation, "test_josephus_permitation");
        cout << "---------------------" << endl << "2." << endl;
        rt.run(test_heavy_string, "test_heavy_string");
        cout << "---------------------" << endl << "3." << endl;
        cout << "done" << endl;
        cout << "---------------------" << endl << "4." << endl;
        rt.run(test_splitting, "test_splitting");
        cout << "---------------------" << endl << "5." << endl;
        rt.run(test_move_push_back, "test_move_push_back");
        cout << "---------------------" << endl << "6." << endl;
        rt.run(test_merge_sort, "test_merge_sort");
        cout << "---------------------" << endl << "7." << endl;
        rt.run(test_priority_collection, "test_priority_collection");
        cout << "---------------------" << endl << "8." << endl;
        rt.run(test_calculate_matrix_sum, "test_calculate_matrix_sum");
        cout << "---------------------" << endl << "9." << endl;
        rt.run(test_basic, "test_basic");
        cout << "---------------------" << endl << "10." << endl;
        rt.run(test_synchronized, "test_synchronized");
        cout << "---------------------" << endl << "11." << endl;
        rt.run(test_concurrent_map, "test_concurrent_map");
    }

    void sixth_weak() {
        cout << "______Sixth weak______" << endl;
    }
    
    void test() {
        first_weak();
        second_weak();
        third_weak();
        fourt_weak();
        fifth_weak();
        sixth_weak();
    }
}