#include "ytest.hpp"
#include <tuple>
#include <set>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <iomanip>
#include "bus_manager.cpp"

using namespace bmanager;
using namespace query;

namespace ybelt {
    void avg_temp(vector<int> temps) {
        int sum = 0;
        for (size_t i = 0; i < temps.size(); ++i)
            sum += temps[i];
        int avg = sum / int(temps.size());
        for (size_t i = 0; i < temps.size(); ++i) {
            if (temps[i] >= avg)
                cout << i << ' ';
        }
        cout << endl;
    }

    void weight_blocks(uint16_t count, uint32_t density, vector<vector<uint32_t>> params) {
        if (count != params.size()) return;
        vector<uint32_t> all_weights;
        for (size_t i = 0; i < count; ++i) {
            if (params[i].size() != 3) continue;
            all_weights.push_back((density * params[i][0] * params[i][1] * params[i][2]));
        }
        uint64_t sum = 0;
        for (int item : all_weights)
            sum += item;
        cout << sum << endl;
    }

    void FindMaxRepetitionCount(const vector<Region>& regions) {
        set<tuple<const string&, const string&,
            const map<Lang, string>&, const int64_t&>> tmp;
        for (const auto& r : regions)
            tmp.insert(tie(r.std_name, r.parent_std_name, r.names, r.population));
        uint16_t count_copy = 0;
        if (regions.size() == tmp.size()) count_copy = 1;
        else count_copy = regions.size() - tmp.size();
        cout << count_copy << endl;
    }
    
    void TeamTasks::AddNewPerson(const string& person) {
        persons[person][TaskStatus::NEW];
        persons[person][TaskStatus::IN_PROGRESS];
        persons[person][TaskStatus::TESTING];
        persons[person][TaskStatus::DONE];
    }

    const TasksInfo& TeamTasks::GetPersonTasksInfo(const string& person) const {
        if (persons.find(person) != persons.end())
            return persons.at(person);
        return TasksInfo();
    }
        
    void TeamTasks::AddNewTask(const string& person) {
        if (persons.find(person) == persons.end())
            AddNewPerson(person);
        persons[person][TaskStatus::NEW] += 1;
    }
        
    pair<TasksInfo, TasksInfo> TeamTasks::PerformPersonTasks(
        const string& person, int task_count) {
        pair<TasksInfo, TasksInfo> res;

        if (persons.find(person) == persons.end())
            return res;
        
        TasksInfo& person_info = persons.at(person);

        int count_new_tasks = 0;
        for(auto& item : person_info) {
            item.second += count_new_tasks;
            if (item.second - task_count >= 0) {
                int old = item.second - count_new_tasks - task_count;
                if (old > 0) {
                    res.second[item.first] = old;
                }
                if (count_new_tasks != 0) {
                    int new_tasks = item.second - old - task_count;
                    if (new_tasks > 0)
                        res.first[item.first] = new_tasks;
                }
                item.second -= task_count;
                count_new_tasks = task_count;
                task_count = 0;
            }
            else {
                count_new_tasks = item.second;
                task_count -= item.second;
                item.second = 0;
            }
        }

        return res;
    }

    void PrintTasksInfo(TasksInfo tasks_info) {
        cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
            ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
            ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
            ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
    }

    template<typename first, typename second>
    pair<first, second> operator*(const pair<first, second>& p1,
        const pair<first, second>& p2) {
        first fres = p1.first * p2.first;
        second sres = p1.second * p2.second;
        return {fres, sres};
    }

    template<typename key, typename value>
    map<key, value> operator*(const map<key, value>& m1,
        const map<key, value>& m2) {
        map<key, value> res;
        for (const auto& item : m1)
            res[item.first] = item.second * m2.at(item.first);
        return res;
    }

    template<typename T>
    vector<T> operator*(const vector<T>& v1, const vector<T>& v2) {
        vector<T> res;
        for (size_t i = 0; i < v1.size(); ++i)
            res.push_back(v1[i] * v2[i]);
        return res;
    }

    template<typename T>
    T Sqr(T x) {
        return x * x;
    }

    template<typename key, typename value>
    value& GetRefStrict(map<key, value>& m, const key& k) {
        if (m.find(k) == m.end())
            throw runtime_error("cant find elem");
        return m.at(k);
    }

    void first_weak() {
        cout << "------FIRST WEAK-------" << endl;
        cout << "1." << endl;
        vector<int> temps = {5, 4, 1, -2, 7};
        avg_temp(temps);
        cout << "------------------------" << endl;
        cout << "2." << endl;
        uint16_t count = 2;
        uint32_t density = 14;
        vector<vector<uint32_t>> params =
            {{1, 2, 3}, {30, 40, 50}};
        weight_blocks(count, density, params);
        cout << "------------------------" << endl;
        cout << "3." << endl;
        FindMaxRepetitionCount({
            {"Moscow", "Russia", {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}}, 89},
            {"Russia", "Eurasia", {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}}, 89},
            {"Moscow", "Russia", {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}}, 89}, 
            {"Moscow", "Russia", {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}}, 89},
            {"Russia", "Eurasia", {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}}, 89},});
        
        FindMaxRepetitionCount({
            {"Moscow", "Russia", {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}}, 89},
            {"Russia", "Eurasia", {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}}, 89}, 
            {"Moscow", "Russia", {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}}, 89}, 
            {"Moscow", "Toulouse", {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}}, 89}, 
            {"Moscow", "Russia", {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}}, 31}});
        cout << "------------------------" << endl;
        cout << "4." << endl;
        TeamTasks tasks;
        tasks.AddNewTask("Ilia");
        for (int i = 0; i < 3; ++i) {
            tasks.AddNewTask("Ivan");
        }
        cout << "Ilia's tasks: ";
        PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
        cout << "Ivan's tasks: ";
        PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
        
        TasksInfo updated_tasks, untouched_tasks;
        
        tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Ivan", 2);
        cout << "Updated Ivan's tasks: ";
        PrintTasksInfo(updated_tasks);
        cout << "Untouched Ivan's tasks: ";
        PrintTasksInfo(untouched_tasks);
        
        tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Ivan", 2);
        cout << "Updated Ivan's tasks: ";
        PrintTasksInfo(updated_tasks);
        cout << "Untouched Ivan's tasks: ";
        PrintTasksInfo(untouched_tasks);
        cout << "------------------------" << endl;
        cout << "5." << endl;
        vector<int> v = {1, 2, 3};
        cout << "vector:";
        for (int x : Sqr(v))
            cout << ' ' << x;
        cout << endl;

        map<int, pair<int, int>> map_of_pairs = {
                                    {4, {2, 2}},
                                    {7, {4, 3}}};
        cout << "map of pairs:" << endl;
        for (const auto& x : Sqr(map_of_pairs))
            cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;       
        cout << "------------------------" << endl;
        cout << "6." << endl;
        map<int, string> m = {{0, "value"}};
        string& item = GetRefStrict(m, 0);
        item = "newvalue";
        cout << m[0] << endl;
    }

    template <class T>
    ostream& operator<<(ostream& os, const vector<T>& s) {
        os << "{";
        bool first = true;
        for (const auto& x : s) {
            if (!first)
                os << ", ";
            first = false;
            os << x;
        }
        return os << "}";
    }

    template <class T>
    ostream& operator<<(ostream& os, const set<T>& s) {
        os << "{";
        bool first = true;
        for (const auto& x : s) {
            if (!first)
                os << ", ";
            first = false;
            os << x;
        }
        return os << "}";
    }

    template <class K, class V>
    ostream& operator<<(ostream& os, const map<K, V>& m) {
        os << "{";
        bool first = true;
        for (const auto& kv : m) {
            if (!first)
                os << ", ";
            first = false;
            os << kv.first << ": " << kv.second;
        }
        return os << "}";
    }

    template<class T, class U>
    void AssertEqual(const T& t, const U& u, const string& hint = {}) {
        ostringstream os;
        if (t != u) {
            os << "Assertion failed: " << t << " != " << u;
            if (!hint.empty())
                os << " hint: " << hint;
            throw runtime_error(os.str());
        }
        if (hint != "")
            os << hint;
        os << "Done" << endl;
    }

    template<typename T>
    void Assert(const T& a, const T& b, const string& hint) {
        AssertEqual(a, b, hint);
    }

    int GetDistinctRealRootCount(double a = 0, double b = 0, double c = 0) {
        size_t count = 0;
        if (a == 0) {
            count = 1;
        }
        else {
            double d = pow(b, 2) - (4 * (a * c));
            if (d < 0)
                return count;

            double x1 = (-b + sqrt(d))/(2 * a);
            double x2 = (-b - sqrt(d))/(2 * a);

            if (x1 == x2)
                count = 1;
            else    
                count = 2;            
        }
        return count;
    }

    template <class TestFunc>
    void TestRunner::RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cout << test_name << " OK" << endl;
        } catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        } catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    TestRunner::~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

    void test_quadric() {
        int res = 0;
        int expected = 0;

        expected = 2;
        res = GetDistinctRealRootCount(1, 5, 6);
        Assert(res, expected,  "1, 5, 6: ");

        expected = 1;
        res = GetDistinctRealRootCount(1, 4, 4);
        Assert(res, expected,  "1, 4, 4: "); 

        expected = 2;
        res = GetDistinctRealRootCount(1, -3, -4);
        Assert(res, expected,  "1, -3, -4: ");

        expected = 2;
        res = GetDistinctRealRootCount(2, 3, -2);
        Assert(res, expected,  "2, 3, -2: ");

        expected = 1;
        res = GetDistinctRealRootCount(0, 3, -2);
        Assert(res, expected,  "0, 3, -2: ");

        expected = 2;
        res = GetDistinctRealRootCount(2, 1, -2);
        Assert(res, expected,  "2, 1, -2: ");

        expected = 0;
        res = GetDistinctRealRootCount(2, 1, 6);
        Assert(res, expected,  "2, 1, 6: ");
    }

    void Person::ChangeFirstName(int year, const string& first_name) {
        if (f_name_history.find(year) != f_name_history.end())
            return;
        f_name_history[year] = first_name;
    }

    void Person::ChangeLastName(int year, const string& last_name) {
        if (s_name_history.find(year) != s_name_history.end())
            return;
        s_name_history[year] = last_name;
    }

    int Person::find_last_year(bool id_hs, int year) const {
        int last_year = 0;
        history hs;

        if (id_hs == 0) hs = f_name_history;
        else hs = s_name_history;
        
        for (const auto& item : hs) {
            if (item.first >= year) {
                break;
            }
            last_year = item.first;
        }
        return last_year;
    }

    string Person::GetFirstName(int year) const {
        if (f_name_history.find(year) != f_name_history.end())
            return f_name_history.at(year);
        int last_year = find_last_year(0, year);
        if (last_year)
            return f_name_history.at(last_year);
        return "";
    }

    string Person::GetSecondName(int year) const {
        if (s_name_history.find(year) != s_name_history.end())
            return s_name_history.at(year);
        int last_year = find_last_year(1, year);
        if (last_year)
            return s_name_history.at(last_year);
        return "";
    }

    string Person::GetFullName(int year) const {
        string f_name = GetFirstName(year);
        string s_name = GetSecondName(year);

        if (f_name == "" && s_name == "")
            return "Incognito";
        else if (f_name == "")
            return s_name + " with unknown first name";
        else if (s_name == "")
            return f_name + " with unknown second name";
        return f_name + ' ' + s_name;
    }

    void test_person() {
        string expected = "";
        string res = "";
        Person p;

        p.ChangeFirstName(1000, "egor");
        expected = "egor with unknown second name";
        res = p.GetFullName(1000);
        Assert(res, expected, "1");

        p.ChangeLastName(999, "seleznev");
        expected = "seleznev with unknown first name";
        res = p.GetFullName(999);
        Assert(res, expected, "2");

        expected = "egor seleznev";
        res = p.GetFullName(1000);
        Assert(res, expected, "2");

        expected = "egor seleznev";
        res = p.GetFullName(1001);
        Assert(res, expected, "3");

        expected = "Incognito";
        res = p.GetFullName(100);
        Assert(res, expected, "4");

        p.ChangeFirstName(1001, "Egor");
        expected = "Egor seleznev";
        res = p.GetFullName(1001);
        Assert(res, expected, "5");

        p.ChangeLastName(1002, "Seleznev");
        expected = "Egor Seleznev";
        res = p.GetFullName(1002);
        Assert(res, expected, "6");

        p.ChangeLastName(1002, "xui");
        expected = "Egor Seleznev";
        res = p.GetFullName(1002);
        Assert(res, expected, "7");

        p.ChangeFirstName(1001, "xui");
        expected = "Egor seleznev";
        res = p.GetFullName(1001);
        Assert(res, expected, "8");
    }

    int find_max_divider(int a, int b) {
        for (size_t i = (a > b) ? abs(a) : abs(b); i >= 1; --i) {
            if (abs(a) % i == 0 && abs(b) % i == 0) {
                return i;
            }
        }
        return 1;
    }
    
    Rational::Rational(int numerator_, int denominator_) {
        if (denominator_ == 0)
            throw runtime_error("invalid_argument");
        numerator = numerator_;
        denominator = denominator_; 
        if (numerator == 0) {
            denominator = 1;
        }
        if (denominator < 0) {
            numerator *= -1;
            denominator *= -1;
        }
        if (numerator != 0) {
            uint64_t max_divider = find_max_divider(numerator_, denominator_);
            numerator /= max_divider;
            denominator /=  max_divider;
        }
    }

    bool Rational::operator==(const Rational& other) {
        return (numerator * other.Denominator()) ==
            (denominator * other.Numerator());
    }
    
    Rational Rational::operator+(const Rational& other) {
        int general_den = denominator * other.Denominator();
        int general_num = numerator * other.Denominator() +
            other.Numerator() * denominator;
        if (general_num == 0)
            return {0, 1};
        int max_divider = find_max_divider(general_den, general_num);
        return {(general_num / max_divider), (general_den / max_divider)};
    }

    Rational Rational::operator-(const Rational& other) {
        int general_den = denominator * other.Denominator();
        int general_num = numerator * other.Denominator() -
            other.Numerator() * denominator;
        if (general_num == 0)
            return {0, 1};
        int max_divider = find_max_divider(general_den, general_num);
        return {(general_num / max_divider), (general_den / max_divider)};
    }

    Rational Rational::operator*(const Rational& other) {
        int new_num = numerator * other.Numerator();
        int new_den = denominator * other.Denominator();
        int divider = find_max_divider(new_num, new_den);
        return {(new_num / divider), (new_den / divider)};
    }

    Rational Rational::operator/(const Rational& other) {
        if (other.Numerator() == 0)
            throw runtime_error("domain_error");
        int new_num = numerator * other.Denominator();
        int new_den = denominator * other.Numerator();
        int divider = find_max_divider(new_num, new_den);
        return {(new_num / divider), (new_den / divider)};
    }

    ostream& operator<<(ostream& stream, const Rational& rt) {
        stream << rt.Numerator() << '/' << rt.Denominator();
        return stream;
    }

    istream& operator>>(istream& stream, Rational& rt) {
        stream >> rt.numerator;
        stream.ignore(1);
        stream >> rt.denominator;
        return stream;
    }

    string Rational::ToString() {
        return to_string(numerator) + '/' + to_string(denominator);
    }

    void Rational::Print(const string& msg) const {
        cout << msg << ": " << endl;
        cout << numerator << '/' << denominator << endl;
    }

    void test_rational() {
        string expected;
        Rational test;
        
        expected = "0/1";
        Assert(test.ToString(), expected, "1");

        expected = "-2/3";
        test = {-2, 3};
        Assert(test.ToString(), expected, "2");

        test = {2, -3};
        expected = "-2/3";
        Assert(test.ToString(), expected, "3");

        test = {-2, -3};
        expected = "2/3";
        Assert(test.ToString(), expected, "4");

        test = {2, 2};
        expected = "1/1";
        Assert(test.ToString(), expected, "5");

        test = Rational{2, 3} + Rational{2, 3};
        expected = "4/3";
        Assert(test.ToString(), expected, "6");

        test = Rational{-2, 3} + Rational{2, 3};
        expected = "0/1";
        Assert(test.ToString(), expected, "7");

        test = Rational{-2, 3} + Rational{2, 3};
        expected = "0/1";
        Assert(test.ToString(), expected, "8");

        test = Rational{2, 3} - Rational{2, 3};
        expected = "0/1";
        Assert(test.ToString(), expected, "9");

        test = Rational{-2, 3} - Rational{2, 3};
        expected = "-4/3";
        Assert(test.ToString(), expected, "10");

        test = Rational{1, 3} * Rational{2, 3};
        expected = "2/9";
        Assert(test.ToString(), expected, "11");

        test = Rational{-1, 3} * Rational{2, 3};
        expected = "-2/9";
        Assert(test.ToString(), expected, "12");

        test = Rational{2, 3} / Rational{2, 3};
        expected = "1/1";
        Assert(test.ToString(), expected, "13");
        
        test = Rational{-1, 3} / Rational{2, 3};
        expected = "-1/2";
        Assert(test.ToString(), expected, "14");
    }

    bool is_palindrom(const string& str) {
        if (str.size() == 0 || str.size() == 1)
            return true;

        string test = "";
        for (int i = str.size() - 1; i >= 0; --i)
            test += str[i];
        
        if (test == str)
            return true;
        return false;
    }

    void test_is_palindrom() {
        bool expected;
        bool res;

        expected = true;
        res = is_palindrom("");
        Assert(res, expected, "1");

        expected = true;
        res = is_palindrom("1");
        Assert(res, expected, "2");

        expected = false;
        res = is_palindrom("xui");
        Assert(res, expected, "3");

        expected = true;
        res = is_palindrom("iui");
        Assert(res, expected, "4");

        expected = true;
        res = is_palindrom("i i i");
        Assert(res, expected, "5");

        expected = false;
        res = is_palindrom("i i i ");
        Assert(res, expected, "6");
    }

    void second_weak() {
        cout << endl << "------SECOND WEAK-------" << endl;
        cout << "1." << endl;
        Query query;

        vector<string> input = {
            "ALL_BUSES", "BUSES_FOR_STOP Marushkino",
            "STOPS_FOR_BUS 32K", "NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo",
            "NEW_BUS 32K 6 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo",
            "BUSES_FOR_STOP Vnukovo",
            "NEW_BUS 950 6 Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo Troparyovo",
            "NEW_BUS 272 4 Vnukovo Moskovsky Rumyantsevo Troparyovo",
            "STOPS_FOR_BUS 272", "ALL_BUSES"};

        BusManager bm;
        for (const auto& item : input) {
            stringstream buf(item);
            buf >> query;
            switch (query.type) {
            case QueryType::NewBus:
            bm.AddBus(query.bus, query.stops);
            break;
            case QueryType::BusesForStop:
            cout << bm.GetBusesForStop(query.stop) << endl;
            break;
            case QueryType::StopsForBus:
            cout << bm.GetStopsForBus(query.bus) << endl;
            break;
            case QueryType::AllBuses:
            cout << bm.GetAllBuses() << endl;
            break;
            }
        }
        cout << "------------------------" << endl;
        cout << "2." << endl;
        TestRunner tr;
        tr.RunTest(test_quadric, "Test_quadric");
        cout << "------------------------" << endl;
        cout << "3." << endl;
        tr.RunTest(test_person, "Test_person");
        cout << "------------------------" << endl;
        cout << "4." << endl;
        tr.RunTest(test_rational, "Test_rational");
        cout << "------------------------" << endl;
        cout << "5." << endl;
        tr.RunTest(test_is_palindrom, "Test_is_palindrom");
    }

    PhoneNumber::PhoneNumber(const string& international_number) {
        if (international_number.size() < 6 ||
            international_number[0] != '+')
            throw invalid_argument("");
        size_t to_next = 0;
        for (size_t i = 0; i < international_number.size(); ++i) {
            if (international_number[i] == '-')
                ++to_next;
            if(to_next == 0)
                _country_code += international_number[i];
            else if (to_next == 1)
                _city_code += international_number[i];
            else
                _local_number += international_number[i];
        }
        if (_country_code == "" || _city_code == "" || _local_number == "")
            throw invalid_argument("");
    }

    string PhoneNumber::GetCountryCode() const {
        return _country_code;
    }

    string PhoneNumber::GetCityCode() const {
        return _city_code;
    }

    string PhoneNumber::GetLocalNumber() const {
        return _local_number;
    }

    string PhoneNumber::GetInternationalNumber() const {
        return _country_code + _city_code + _local_number;
    }

    void test_phoen_number() {
        string expected;
        PhoneNumber pn;

        pn = PhoneNumber("+7-495-111-22-33");
        expected = "+7-495-111-22-33";
        Assert(pn.GetInternationalNumber(), expected, "1");

        pn = PhoneNumber("+7-495-1112233");
        expected = "+7-495-1112233";
        Assert(pn.GetInternationalNumber(), expected, "2");

        pn = PhoneNumber("+323-22-460002");
        expected = "+323-22-460002";
        Assert(pn.GetInternationalNumber(), expected, "3");

        pn = PhoneNumber("+1-2-coursera-cpp");
        expected = "+1-2-coursera-cpp";
        Assert(pn.GetInternationalNumber(), expected, "4");
        try {
            pn = PhoneNumber("+7-1233");
        }
        catch(const exception& e) {
            cerr << e.what() << '\n';
        }
        
        try {
            pn = PhoneNumber("1-2-333");
        }
        catch(const exception& e) {
            cerr << e.what() << '\n';
        }
    }

    void test_rectangle() {
        Rectangle r(10, 10);
        Assert(r.GetArea(), 100, "1");
        Assert(r.GetPerimeter(), 40, "2");
        Assert(r.GetWidth(), 10, "3");
        Assert(r.GetHeight(), 10, "4");
    }

    void third_weak() {
        cout << endl << "-------THIRD WEAK-------" << endl;
        TestRunner tr;
        cout << "1." << endl;
        cout << "Done" << endl;
        cout << "------------------------" << endl;
        cout << "2." << endl;
        tr.RunTest(test_phoen_number, "Test_phoen_number");
        cout << "------------------------" << endl;
        cout << "3." << endl;
        tr.RunTest(test_rectangle, "Test_rectangle");
        cout << "------------------------" << endl;
        cout << "4." << endl;
        cout << "Done" << endl;
    }

    void PrintVectorPart(const vector<int>& numbers) {
        auto f_negative = find_if(numbers.begin(), numbers.end(),
            [](int num) { return num < 0; });
        int i = 0;
        while (f_negative != numbers.begin())
            cout << *(--f_negative) << ' ';
        cout << endl;
    }

    template <typename T>
    vector<T> FindGreaterElements(const set<T>& elements, const T& border) {
        vector<T> res;
        auto it = elements.find(border);
        if (it != elements.end()) {
            while (++it != elements.cend())
                res.push_back(*it);
        }
        return res;
    }

    vector<string> SplitIntoWords(const string& s) {
        vector<string> res;
        auto first_char = begin(s);
        for (auto it = begin(s); it != end(s); ++it) {
            if (*it == *find(it, end(s), ' ')) {
                res.push_back({first_char, it});
                first_char = ++it;
            }
        }
        res.push_back({first_char, end(s)});
        return res;
    }

    template <typename T>
    void RemoveDuplicates(vector<T>& elements) {
        sort(elements.begin(), elements.end());
        auto it = unique(elements.begin(), elements.end());
        elements.erase(it, elements.end());
    }

    template<typename T>
    void print_range(T begin, T end) {
        while (begin != end)
            cout << *(begin++) << ' ';
        cout << endl;
    }

    void enumeration_permutations(int num) {
        vector<int> numbers(num);
         
        iota(numbers.begin(), numbers.end(), 1);
        int i = numbers.size();
        while (i > 0) {
            vector<int> temp;
            copy_if(numbers.begin(), numbers.end(), back_inserter(temp),
            [i](int n) { return n != i; });
            cout << i << ' ';
            print_range(temp.begin(), temp.end());
            cout << i << ' ';
            print_range(temp.rbegin(), temp.rend());
            --i;
        }
    }
    
    template <typename InputIt>
    int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
        if (range_begin == range_end) {
            return 0;
        }
        vector<typename InputIt::value_type> range_copy(range_begin, range_end);
        auto middle = begin(range_copy) + range_copy.size() / 2;
        nth_element(
            begin(range_copy), middle, end(range_copy),
            [](const Person2& lhs, const Person2& rhs) {
                return lhs.age < rhs.age;
            }
        );
        return middle->age;
    }

    void PrintStats(vector<Person2> persons) {
        cout << "Median age = " << ComputeMedianAge(persons.begin(), persons.end()) << endl;

        auto it = partition(begin(persons), end(persons),
            [](const Person2& p) { return p.gender == Gender::FEMALE; });
        cout << "Median age for females = " << ComputeMedianAge(persons.begin(), it) << endl;
        
        it = partition(begin(persons), end(persons),
            [](const Person2& p) { return p.gender == Gender::MALE; });
        cout << "Median age for males = " << ComputeMedianAge(persons.begin(), it) << endl;

        it = partition(begin(persons), end(persons),
            [](const Person2& p) { return (p.gender == Gender::FEMALE && !p.is_employed); });
        cout << "Median age for unemployed females = " << ComputeMedianAge(persons.begin(), it) << endl;

        it = partition(begin(persons), end(persons),
            [](const Person2& p) { return p.gender == Gender::FEMALE && p.is_employed; });
        cout << "Median age for employed femalesle = " << ComputeMedianAge(persons.begin(), it) << endl;

        it = partition(begin(persons), end(persons),
            [](const Person2& p) { return p.gender == Gender::MALE && !p.is_employed; });
        cout << "Median age for unemployed males = " << ComputeMedianAge(persons.begin(), it) << endl;

        it = partition(begin(persons), end(persons),
            [](const Person2& p) { return p.gender == Gender::MALE && p.is_employed; });
        cout << "Median age for employed males = " << ComputeMedianAge(persons.begin(), it) << endl;
    }

    template <typename RandomIt>
    void swap_iter_value(RandomIt f, RandomIt s) {
        typename RandomIt::value_type temp = *f;
        *f = *s;
        *s = temp;
    }

    template <typename RandomIt>
    void merge(RandomIt begin, int size, int midle) {
        int i = 0;
        int j = midle;

        while (i < midle && j < size) {
            if (*(begin + i) > *(begin + j)) {
                swap_iter_value(begin + i, begin + j);
            }
            ++i;
            ++j;
        }
    }

    template <typename RandomIt>
    void MergeSort(RandomIt range_begin, RandomIt range_end) {
        int size = distance(range_begin, range_end);
        if (size == 0 || size == 1) {
            return;
        }
        if (size == 2) {
            if (*range_begin > *(range_end - 1)) {
                swap_iter_value(range_begin, (range_end - 1));
            }
            return;
        }

        vector<typename RandomIt::value_type> elements(range_begin, range_end);
        int midle = elements.size() / 2;
        MergeSort(range_begin, range_begin + midle);
        MergeSort(range_begin + midle, range_end);

        merge(range_begin, size, midle);
    }

    set<int>::const_iterator FindNearestElement(
        const set<int>& numbers,
        int border) {
        if (numbers.size() == 0)
            return numbers.end();
        if (numbers.find(border) != numbers.end())
            return numbers.find(border);

        auto max_it = find_if(numbers.begin(), numbers.end(),
            [border](int x) { return x > border; });
        auto min_it = find_if(numbers.begin(), numbers.end(),
            [border](int x) { return x < border; });
        
        if (min_it == numbers.end())
            return numbers.begin();
        if (max_it == numbers.end())
            return prev(numbers.end());
        else {
            auto pre_max = prev(max_it);
            if (border - *pre_max == *max_it - border)
                return pre_max;
            else if(border - *pre_max > *max_it - border)
                return max_it;
            else
                return pre_max;
        }
    }

    string find_by_year(map<int, string>& map, int year) {
        string name;
        auto it = map.upper_bound(year);
        if (it != map.begin())
            name = (--it)->second;
        return name;
    }

    void Person3::ChangeFirstName(int year, const string& first_name) {
        _f_name_history[year] = first_name;
    }

    void Person3::ChangeLastName(int year, const string& last_name) {
        _s_name_history[year] = last_name;
    }

    string Person3::GetFullName(int year) {
        string f_name = find_by_year(_f_name_history, year);
        string s_name = find_by_year(_s_name_history, year);

        if (f_name == "" && s_name == "")
            return "Incognito";
        else if (s_name == "")
            return f_name + " with unknown first name";
        else if (f_name == "")
            return s_name + " with unknown second name";
        else
            return f_name + ' ' + s_name;
    }
    
    template <typename RandomIt>
    pair<RandomIt, RandomIt> FindStartsWith(
        RandomIt range_begin, RandomIt range_end,
        char prefix) {
        auto res = equal_range(range_begin, range_end, string(1, prefix),
            [](const string& s1, const string& s2){ return s1[0] < s2[0]; });
        return res;
    }

    bool comparator(const string& str1, const string& str2) {
        bool bool_res = (str1 <= str2);
        return bool_res;
    }

    template <typename RandomIt>
    pair<RandomIt, RandomIt> FindStartsWith(
        RandomIt range_begin, RandomIt range_end,
        const string& prefix) {
        auto temp1 = lower_bound(range_begin, range_end, prefix,
            [](const string& s1, const string& s2) {
                string s2_full = s2 + string(s1.begin() + s2.size(), s1.end());
                bool bool_res = s1 < s2_full;
                return bool_res; });

        auto temp2 = upper_bound(range_begin, range_end, prefix,
            [](const string& s1, const string& s2) {
                string s1_full = s1 + string(s2.begin() + s1.size(), s2.end());
                bool bool_res = s1_full < s2;
                return bool_res; });

        auto res = make_pair(temp1, temp2);
        return res;
    }

    string build_expressions() {
        string res;

        string operation_count;
        getline(cin, res);
        getline(cin, operation_count);
        string new_operation;

        for (size_t i = 0; i < stoi(operation_count); ++i) {
            getline(cin, new_operation);
            char operation = new_operation[0];

            if (operation == '/' || operation == '*') {
                if (i != 0) {
                    res = '(' + res + ')';
                }
            }
            res += ' ' + string(1, operation) +
                string(new_operation.begin() + 1, new_operation.end());
        }

        return res;
    }

    void fourth_weak() {
        cout << endl << "-------FOURTH WEAK--------" << endl;
        TestRunner tr;
        cout << "1." << endl;
        PrintVectorPart({6, 1, 8, -5, 4});
        PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
        PrintVectorPart({6, 1, 8, 5, 4});
        cout << "------------------------" << endl;
        cout << "2." << endl;
        for (int x : FindGreaterElements(set<int>{1, 5, 7, 8}, 5)) {
            cout << x << " ";
        }
        cout << endl;
        
        string to_find = "Python";
        cout << FindGreaterElements(set<string>{"C", "C++"}, to_find).size() << endl;
        cout << "------------------------" << endl;
        cout << "3." << endl;
        string s = "C Cpp Java Python";

        vector<string> words = SplitIntoWords(s);
        cout << words.size() << " ";
        for (auto it = begin(words); it != end(words); ++it) {
            if (it != begin(words)) {
            cout << "/";
            }
            cout << *it;
        }
        cout << endl;
        cout << "------------------------" << endl;
        cout << "4." << endl;
        vector<int> v1 = {6, 4, 7, 6, 4, 4, 0, 1};
        RemoveDuplicates(v1);
        for (int x : v1)
            cout << x << " ";
        cout << endl;
        
        vector<string> v2 = {"C", "C++", "C++", "C", "C++"};
        RemoveDuplicates(v2);
        for (const string& s : v2)
            cout << s << " ";
        cout << endl;
        cout << "------------------------" << endl;
        cout << "5." << endl;
        enumeration_permutations(3);
        cout << "------------------------" << endl;
        cout << "6." << endl;
        vector<Person2> persons = {
            {31, Gender::MALE, false},
            {40, Gender::FEMALE, true},
            {24, Gender::MALE, true},
            {20, Gender::FEMALE, true},
            {80, Gender::FEMALE, false},
            {78, Gender::MALE, false},
            {10, Gender::FEMALE, false},
            {55, Gender::MALE, true},
        };
        PrintStats(persons);
        cout << "------------------------" << endl;
        cout << "7." << endl;
        vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
        MergeSort(begin(v), end(v));
        for (int x : v)
            cout << x << " ";
        cout << endl;
        cout << "------------------------" << endl;
        cout << "8." << endl;
        set<int> numbers = {1, 4, 6};
        cout <<
            *FindNearestElement(numbers, 0) << " " <<
            *FindNearestElement(numbers, 3) << " " <<
            *FindNearestElement(numbers, 5) << " " <<
            *FindNearestElement(numbers, 6) << " " <<
            *FindNearestElement(numbers, 100) << endl;
            
        set<int> empty_set;
        cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
        cout << "------------------------" << endl;
        cout << "9." << endl;
        Person3 person;
  
        person.ChangeFirstName(1965, "Polina");
        person.ChangeLastName(1967, "Sergeeva");
        for (int year : {1900, 1965, 1990}) {
            cout << person.GetFullName(year) << endl;
        }
        
        person.ChangeFirstName(1970, "Appolinaria");
        for (int year : {1969, 1970}) {
            cout << person.GetFullName(year) << endl;
        }
        
        person.ChangeLastName(1968, "Volkova");
        for (int year : {1969, 1970}) {
            cout << person.GetFullName(year) << endl;
        }
        cout << "------------------------" << endl;
        cout << "10." << endl;

        const vector<string> sorted_strings = {"moscow", "murmansk", "vologda"};
  
        const auto m_result =
            FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
        for (auto it = m_result.first; it != m_result.second; ++it) {
            cout << *it << " ";
        }
        cout << endl;
        
        const auto p_result =
            FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
        cout << (p_result.first - begin(sorted_strings)) << " " <<
            (p_result.second - begin(sorted_strings)) << endl;
        
        const auto z_result =
            FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
        cout << (z_result.first - begin(sorted_strings)) << " " <<
            (z_result.second - begin(sorted_strings)) << endl;

        const vector<string> sorted_strings1 = {"moscow", "motovilikha", "murmansk"};
  
        const auto mo_result =
            FindStartsWith(begin(sorted_strings1), end(sorted_strings1), "mo");
        for (auto it = mo_result.first; it != mo_result.second; ++it) {
            cout << *it << " ";
        }
        cout << endl;
        
        const auto mt_result =
            FindStartsWith(begin(sorted_strings1), end(sorted_strings1), "mt");
        cout << (mt_result.first - begin(sorted_strings1)) << " " <<
            (mt_result.second - begin(sorted_strings1)) << endl;
        
        const auto na_result =
            FindStartsWith(begin(sorted_strings1), end(sorted_strings1), "na");
        cout << (na_result.first - begin(sorted_strings1)) << " " <<
            (na_result.second - begin(sorted_strings1)) << endl;

        cout << "------------------------" << endl;
        cout << "11." << endl;
        //cout << build_expressions() << endl;
        cout << "Done" << endl;
        
    }

    void SmsNotifier::Notify(const string& msg) {
        cout << "Send '" << msg << "' to number " << _number << endl;
    }

    void EmailNotifier::Notify(const string& msg) {
        cout << "Send '" << msg << "' to e-mail "  << _email << endl;
    }

    Triangle::Triangle(const string& params, const string& name)
        : Figure(name) {
        size_t i = 0;
        size_t count = 0;
        string num;

        while (count <= 2) {
            if (params[i] == ' ') {
                if (count == 0) {
                    _first_side = stoi(num);
                }
                else if (count == 1) {
                    _second_side = stoi(num);
                }
                else {
                    _third_side = stoi(num);
                    break;
                }
                ++count;
                num = "";
            }
            else {
                num += params[i];
            }
            ++i;
        }
    }

    Rect::Rect(const string& params, const string& name)
        : Figure(name) {
        size_t i = 0;
        size_t count = 0;
        string num;

        while (count <= 1) {
            if (params[i] == ' ') {
                if (count == 0) {
                    _width = stoi(num);
                }
                else {
                    _hight = stoi(num);
                    break;
                }
                ++count;
                num = "";
            }
            else {
                num += params[i];
            }
            ++i;
        }
    }

    Circle::Circle(const string& radius, const string& name)
        : Figure(name) {
        _radius = stoi(radius);
    }


    double Triangle::Perimeter() {
        double res = _first_side + _second_side + _third_side;
        return res;
    }

    double Triangle::Area() {
        double s = (_first_side + _second_side + _third_side) / 2;
        double a = sqrt(s * (s - _first_side) * (s - _second_side) * (s - _third_side));
        return a;
    }

    double Rect::Perimeter() {
        double res = (_width + _hight) * 2;
        return res;
    }

    double Rect::Area() {
        double res = _width * _hight;
        return res;
    }

    double Circle::Area() {
        return 3.14 * pow(_radius, 2);
    }

    double Circle::Perimeter() {
        return 2 * (3.14 * _radius); 
    }

    shared_ptr<Figure> CreateFigure(istringstream& is) {
        is.ignore(1);
        string f_name;
        is >> f_name;
        is.ignore(1);
        string params = is.str();
        shared_ptr<Figure> res; 
        if (f_name == "TRIANGLE")
            res = make_shared<Triangle>(string(params.begin() + 13, params.end()));
        else if (f_name == "RECT")
            res = make_shared<Rect>(string(params.begin() + 9, params.end()));
        else if (f_name == "CIRCLE")
            res = make_shared<Circle>(string(params.begin() + 11, params.end()));
        else
            throw invalid_argument(f_name);
        return res;
    }

    void fifth_weak() {
        cout << endl << "-------FIFTH WEAK--------" << endl;
        cout << "1." << endl;
        Dog d;
        d.Bark();
        cout << "------------------------" << endl;
        cout << "2." << endl;
        SmsNotifier sms{"+7-495-777-77-77"};
        EmailNotifier email{"na-derevnyu@dedushke.ru"};

        sms.Notify("penis");
        email.Notify("xui");
        cout << "------------------------" << endl;
        cout << "3." << endl;
        vector<shared_ptr<Figure>> figures;
        for (string line; getline(cin, line); ) {
            istringstream is(line);

            string command;
            is >> command;
            if (command == "ADD") {
                figures.push_back(CreateFigure(is));
            } else if (command == "PRINT") {
                for (const auto& current_figure : figures) {
                    cout << fixed << setprecision(3)
                        << current_figure->Name() << " "
                        << current_figure->Perimeter() << " "
                        << current_figure->Area() << endl;
                }
            }
        }
        cout << "------------------------" << endl;
        cout << "4." << endl;
        Teacher t("Jim", "Math");
        Student s("Ann", "We will rock you");
        Policeman p("Bob");

        VisitPlaces(t, {"Moscow", "London"});
        p.Check(s);
        VisitPlaces(s, {"Moscow", "London"});
    }


    void test() {
        first_weak();
        second_weak();
        third_weak();
        fourth_weak();
        fifth_weak();
    }
}