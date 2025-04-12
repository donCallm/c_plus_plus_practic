#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <utility>

using namespace std;

namespace task_test {
    //first weak
    void sum(int first, int second);
    void find_str(const string& str);
    void quadratic_equation(int a, int b, int c);
    void division(int a, int b);
    void find_cost(double n, double a, double b, double x, double y);
    void find_even(int a, int b);
    void find_second_f(const string& str);
    int find_max_divider(int a, int b);
    
    //second weak
    enum pstate {
        quiet = 0,
        worry = 1
    };

    enum p_que_comm {
        с_quiet = 0, 
        с_worry = 1,
        come = 2,
        worry_count = 3
    };

    enum todo_comm {
        add = 0,
        next = 1,
        todo_dump = 2
    };

    enum cptls_drct_comm {
        change_capital = 0,
        rename = 1,
        capit_dump = 2,
        about = 3   
    };

    enum bus_comm {
        new_bus = 0,
        buses_for_stop = 1,
        stops_for_bus = 2,
        all_buses = 3
    };

    enum syn_comm {
        add_word = 0,
        count = 1,
        check = 3
    };

    int factorial(int num);
    bool is_palindrom(const string& str);
    vector<string> palindrom_filter(vector<string> words,
        int min_lenght);
    void update_if_greater(int a, int& b);
    void move_strings(vector<string>& source,
        vector<string>& destination);
    void reverse(vector<int>& nums);
    vector<int> reverse__to_copy(const vector<int>& nums);
    vector<int> search_days_by_temp(const vector<int>& temps);
    void people_queue(vector<p_que_comm> comms,
    vector<int> params);
    void todo_list(vector<todo_comm> comms,
        vector<pair<int, string>>& params);
    void anagram_test(vector<pair<string, string>>& input);
    void capitals_directory(vector<cptls_drct_comm> comms,
        vector<pair<string, string>>& params);
    void bus_stop1(vector<bus_comm> comms,
        vector<vector<string>>& params);
    void bus_stop2(vector<vector<string>>& params);
    void word_count(vector<string> params);
    set<string> build_map_values_set(const map<int,
        string>& map);
    void synonyms(vector<syn_comm> comms,
        vector<pair<string, string>>& params);
    void bus_stop3(vector<vector<string>>& params);

    //third weak
    vector<int> sort_by_module(string& input);

    class sorted_strings {
        public:
            void add_str(const string& s);
            vector<string> get_sorted_strings();
        private:
            vector<string> strings;
    };

    class Person1 {
        public:
            void ChangeFirstName(int year, const string& first_name);
            void ChangeLastName(int year, const string& last_name);
            string GetFullName(int year);
            string GetFullNameWithHistory(int year);
        private:
            uint64_t get_last_change(uint64_t year);
            vector<uint64_t> get_date_history(uint64_t year);
            pair<vector<string>,
                vector<string>> get_names_history (
                vector<uint64_t> full_history);
        private:
            map<uint64_t, pair<string, string>> history;
    };

    class ReversibleString {
        public:
            explicit ReversibleString(const string& str = "") : _str(str) {}

            string ToString() const;
            void Reverse();
        private:
            string _str;
    };

    class Person2 {
        public:
            Person2(const string& f_name, const string& s_name,
                    uint64_t b_year);

            void ChangeFirstName(int year, const string& first_name);
            void ChangeLastName(int year, const string& last_name);
            string GetFullName(int year);
            string GetFullNameWithHistory(int year);
        private:
            uint64_t get_last_change(uint64_t year);
            vector<uint64_t> get_date_history(uint64_t year);
            pair<vector<string>,
            vector<string>> get_names_history (
            vector<uint64_t> full_history);
        private:
            uint64_t birthday_year;
            map<uint64_t, pair<string, string>> history;
    };

    class Incognizable {
        public:
            Incognizable(int a_ = 0, int b_ = 0) : a(a_), b(b_) {}
        private:
            int a;
            int b;
    };

    //weak four
    struct Specialization {
        Specialization(const string& name_) : name(name_) {}
        string name;
    };

    struct Course  {
        Course(const string& name_) : name(name_) {}
        string name;
    };
    
    struct Week {
        Week(const string& number_) : number(number_) {}
        string number;
    };

    struct LectureTitle {
        explicit LectureTitle(const Specialization& sp_, const Course& crs_, const Week& wk_) : 
            sp(sp_), crs(crs_), wk(wk_) {}
        Specialization sp;
        Course crs;
        Week wk;
    };

    struct Image {
        double quality;
        double freshness;
        double rating;
    };

    struct Params {
        double a;
        double b;
        double c;
    };

    struct FunctionPart {
        char operation;
        double value;
    };
    
    class Function {
        public:
            void AddPart(const char& operation, double value);
            void Invert();
            double Apply(double operand);
        private:
            vector<FunctionPart> parts;
    };

    struct Student {
        string name;
        string sername;
        uint64_t b_day;
        uint64_t b_month;
        uint64_t b_year;
    };

    class Rational {
        public:
            Rational(int numerator_ = 0, int denominator_ = 1);

            bool operator==(const Rational& other);
            Rational operator+(const Rational& other);
            Rational operator-(const Rational& other);
            Rational operator*(const Rational& other);
            Rational operator/(const Rational& other);
            friend ostream& operator<<(ostream& stream, const Rational& rt);
            friend istream& operator>>(istream& stream, Rational& rt);

            int Numerator() const   { return numerator; }
            int Denominator() const { return denominator; }

            void Print(const string& msg) const;
        private:
            int numerator;
            int denominator;
    };

    class TimeServer {
        public:
            TimeServer(const string& time = "00:00:00") : LastFetchedTime(time) {}

            string GetCurrentTime();
        private:
            string LastFetchedTime;
    };

    enum db_comms {
        db_comms_add = 0,
        db_comms_del = 1,
        db_comms_find = 2,
        db_comms_print = 3
    };

    struct event {
        event(const string& date_ = "", const string& name_ = "") :
            date(date_), name(name_) {}
        string date;
        string name;
    };

    class database {
        public:
            void add(pair<string, string>& params);
            string del(const pair<string, string>& params);
            vector<string> find(string& date) const;
            vector<pair<string, set<string>>> get_all() const;
        private:
            map<string, set<string>> events;
    };

    class work_with_db {
        public:
            void run(istream& input);
        private:
            string validate_date(string& date);
            void executing(pair<string, string>& params,
                        db_comms comm);
            void set_comm_date(const string& input,
                        pair<string, string>& params, db_comms& comm);
        private:
            database db;
    };

    void test();
}