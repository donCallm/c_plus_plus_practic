#include "test.hpp"
#include <cmath>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <random>
#include <regex>

namespace task_test {
    template<typename T>
    void print_vector(vector<T> vec) {
        for (const T& to_show : vec)
            cout << to_show << ' ';
        cout << endl;
    }

    void sum(int first, int second) {
        cout << first + second << endl;
    }

    void find_str(const string& str) {
        string min = "";
        string current = "";
       
        for(char ch : str) {
            if (ch != ' ') {
                current += ch;
            }
            else {
                if (min == "")
                    min = current;
                else if ( min > current)
                    min = current;
                current = "";
            }
        }

        cout << min << endl;
    }

    void quadratic_equation(int a, int b, int c) {
        if (a == 0 && b == 0 && c == 0) {
            cout << "error" << endl;
        }
        else if (a == 0) {
            cout << (-(double(c)) / (double(b))) << endl;
        }
        else {
            double d = pow(b, 2) - (4 * (a * c));
            cout <<  "d = " << d << endl;
            if (d < 0) {
                cout << "error" << endl;
                return;
            }

            double x1 = (-b + sqrt(d))/(2 * a);
            double x2 = (-b - sqrt(d))/(2 * a);

            if (x1 == x2)
                cout << x1 << endl;
            else    
                cout << x1 << ' ' << x2 << endl;            
        }
    }

    void division(int a, int b) {
        if (a == 0 || b == 0)
            cout << "error" << endl;
        else
            cout << a/b << endl;
    }

    void find_cost(double n, double a, double b, double x, double y) {
        if (n > b)
            n = n - n / 100 * y;
        else if (n > a)
            n = n - n / 100 * x;
        cout << n << endl;
    }

    void find_even(int a, int b) {
        for (size_t i = a; i <= b; ++i) {
            if (i % 2 == 0)
                cout << i << ' ';
        }
        cout << endl;
    }
    
    void find_second_f(const string& str) {
        int index = -2;
        for (size_t i = 0; i < str.size(); i++) {
            if (str[i] == 'f') {
                if (index == -1) {
                    index = i;
                    break;
                }
                ++index;
            }
        }
        cout << index << endl;
    }

    int find_max_divider(int a, int b) {
        for (size_t i = (a > b) ? abs(a) : abs(b); i >= 1; --i) {
            if (abs(a) % i == 0 && abs(b) % i == 0) {
                return i;
            }
        }
        return 1;
    }

    void find_bin(int num) {
        string res = "";
        while (num != 0) {
            if (num % 2 != 0)
                res += '1';
            else
                res += '0';
            num = num / 2;
        }

        for (int i = res.size() - 1; i >= 0; --i) {
            cout << res[i];
        }
        
        cout << endl;
    }

    void first_weak() {
        cout << "--------------------" << endl;
        cout << "|----FIRST WEAK----|" << endl;
        cout << "--------------------\n" << endl;

        cout << "--First task:" << endl;
        cout << "-input: 2, 3 output: "; sum(2, 3);
        cout << "-input: -4, -9 output: "; sum(-4, -9);
        cout << "-input: -1, 2 output: "; sum(-1, 2);

        cout << "\n--Second task" << endl;
        cout << "-input: \"milk milkshake month\" output: "; find_str("milk milkshake month");
        cout << "-input: \"c a b\" output: "; find_str("c a b");
        cout << "-input: \"fire fog wood\" output: "; find_str("fire fog wood");

        cout << "\n--Third task:" << endl;
        cout << "-input: 2 5 2 output: "; quadratic_equation(2, 5, 2);
        cout << "-input: 2 4 2 output: "; quadratic_equation(2, 4, 2);
        cout << "-input: 2 1 2 output: "; quadratic_equation(2, 1, 2);
        cout << "-input: 0 4 10 output: "; quadratic_equation(0, 4, 10);

        cout << "\n--Fourth tast:" << endl;
        cout << "-input: 10 2 output: "; division(10, 2);
        cout << "-input: 3 5 output: "; division(3, 5);
        cout << "-input: 11 0 output: "; division(11, 0);

        cout << "\n--Fifth task:" << endl;
        cout << "-input: 100 110 120 5 10 output: "; find_cost(100, 110, 120, 5, 10);
        cout << "-input: 115 110 120 5 10 output: "; find_cost(115, 110, 120, 5, 10);
        cout << "-input: 150 110 120 5 12.5 output: "; find_cost(150, 110, 120, 5, 12.5);

        cout << "\n--Sixth task:" << endl;
        cout << "-input: 1 10 output: "; find_even(1, 10);
        cout << "-input: 2 3 output: "; find_even(2, 3);
        cout << "-input: 9 11 output: "; find_even(9, 11);

        cout << "\n--Seventh task:" << endl;
        cout << "-input: comfort output: "; find_second_f("comfort");
        cout << "-input: coffee output: "; find_second_f("coffee");
        cout << "-input: car output: "; find_second_f("car");

        cout << "\n--Eihth task:" << endl;
        cout << "-input: 25 27 output: " << find_max_divider(25, 27) << endl;
        cout << "-input: 12 16 output: " << find_max_divider(12, 16) << endl;
        cout << "-input: 13 13 output: " << find_max_divider(13, 13) << endl;

        cout << "\n--Ninth task:" << endl;
        cout << "-input: 5 output: "; find_bin(5);
        cout << "-input: 32 output: "; find_bin(32);
        cout << "-input: 1 output: "; find_bin(1);
    }

    int factorial(int num) {
        if (num > 10)
            return 0;
        if (num < 0)
            return 1;
        
        int res = 1;
        for (size_t i = 2; i <= num; ++i)
            res = res * i;
        
        return res;
    }

    bool is_palindrom(const string& str) {
        if (str.size() == 0)
            return false;

        string test = "";
        for (int i = str.size() - 1; i >= 0; --i)
            test += str[i];
        
        if (test == str)
            return true;
        return false;
    }

    vector<string> palindrom_filter(vector<string> words, int min_lenght) {
        vector<string> res;
        
        for (const string& temp : words) {
            if (temp.size() >= min_lenght && is_palindrom(temp))
                res.push_back(temp);
        }

        return res;
    }

    void update_if_greater(int a, int& b) {
        if (a > b)
            b = a;
    }

    void move_strings(vector<string>& source, vector<string>& destination) {
        if (source.size() == 0 || destination.size() == 0) return;

        for (const string to_move : source)
            destination.push_back(to_move);
        
        source.clear();
    }

    void reverse(vector<int>& nums) {
        if (nums.size() == 0) return;

        size_t size = nums.size();
        for (int i = size -1 ; i >= 0 ; --i)
            nums.push_back(nums[i]);
        
        nums.erase(nums.begin(), nums.begin() + size);        
    }

    vector<int> reverse__to_copy(const vector<int>& nums) {
        vector<int> copy;

        for (int i = nums.size() -1 ; i >= 0 ; --i)
            copy.push_back(nums[i]);
        
        return copy;
    }

    vector<int> search_days_by_temp(const vector<int>& temps) {
        vector<int> res;

        int avg_temp = 0;

        for (size_t i = 0; i < temps.size(); ++i)
            avg_temp += temps[i];
        avg_temp = avg_temp / temps.size();
        for (size_t i = 0; i < temps.size(); ++i) {
            if (temps[i] > avg_temp)
                res.push_back(i);
        }
        
        return res;
    }

    void people_queue(vector<p_que_comm> comms, vector<int> params) {
        vector<int> qu;
        
        for(size_t i = 0; i < comms.size(); ++i) {
            switch (comms[i])
            {
                case p_que_comm::с_worry: {
                    qu[params[i]] = pstate::worry;
                    break;
                    }
                case p_que_comm::с_quiet : {
                    qu[params[i]] = pstate::quiet;
                    break;
                    }
                case p_que_comm::come : {
                    if (params[i] > 0) {
                        for (size_t i = 0; i < 5; ++i)
                            qu.push_back(pstate::quiet);
                    }
                    else {
                        qu.erase(qu.end() + params[i], qu.end());
                    }
                    break;
                    }
                case p_que_comm::worry_count : {
                    uint64_t count = 0;
                    for (const int& item : qu)
                        if (item == worry) ++count;
                    cout << count << endl;
                    break;
                    }      
                default:
                    break;
            }
        }
    }

    void todo_list(vector<todo_comm> comms,
        vector<pair<int, string>>& params) {
        vector<int> days_in_month = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int current_month = 0;

        vector<vector<string>> task_in_month(days_in_month[current_month]);
        for (size_t i = 0; i < comms.size(); ++i) {
            switch (comms[i])
            {
                case todo_comm::add: {
                    task_in_month[params[i].first - 1].push_back(params[i].second);
                    break;}
                case todo_comm::next: {
                    if (current_month + 1 > days_in_month.size() - 1)
                        current_month = 0;
                    else
                        ++current_month;
                    int days_in_new_month = days_in_month[current_month];
                    if (task_in_month.size() > days_in_month[current_month]) {
                        for (int j = task_in_month.size() - 1; j > days_in_new_month - 1; --j) {
                            for (size_t k = 0; k < task_in_month[j].size(); ++k) {
                                task_in_month[days_in_new_month - 1].push_back(task_in_month[j][k]);
                            }
                        }
                    }
                    else {
                        task_in_month.clear();
                    }
                    task_in_month.resize(days_in_month[current_month]);
                    break;
                }
                case todo_comm::todo_dump: {
                    cout << task_in_month[params[i].first - 1].size() << ' ';
                    print_vector<string>(task_in_month[params[i].first - 1]);
                    break;
                }
                default:
                    break;
            }
        }
    }

    void anagram_test(vector<pair<string, string>>& input) {
        if (input.size() == 0) return;

        for (const auto& item : input) {
            if (item.first.size() != item.second.size()) {
                cout << "NO" << endl;
                continue;
            }
            int first_sum = 0;
            int second_sum = 0;
            for (size_t i = 0; i < item.first.size(); ++i) {
                first_sum += item.first[i];
                second_sum += item.second[i];
            }
            if (first_sum == second_sum)
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
        }
    }

    void capitals_directory(vector<cptls_drct_comm> comms,
        vector<pair<string, string>>& params) {
        if (comms.size() == 0 || params.size() == 0 || comms.size() != params.size()) return;

        map<string, vector<string>> countries;
        for (size_t i = 0; i < comms.size(); ++i) {
            switch (comms[i]) {
                case cptls_drct_comm::change_capital: { //params: name_country new_capital_name
                    cout << "capital_change: ";
                    auto& country = countries[params[i].first];
                    if (country.size() == 0) {
                        country.push_back(params[i].second);
                        cout << "Introduce new country " << params[i].first <<
                            " with capital " << params[i].second << endl;
                    }
                    else if (country[country.size() - 1] == params[i].second) {
                        cout << "Country " << params[i].first << 
                            " hasn't changed its capital" << endl;
                    }
                    else {
                        string old_name = country[country.size() - 1];
                        country.push_back(params[i].second);
                        cout << "Country " <<  params[i].first <<  " has changed its capital from "
                        << old_name << " to " << params[i].second << endl;
                    }
                    break;
                }
                case cptls_drct_comm::rename: { //params: name_country new_country_name
                    cout << "rename: ";
                    if (countries.find(params[i].first) == countries.end() ||
                        params[i].first == params[i].second) {
                        cout << "Incorrect rename, skip" << endl;
                        break;
                    }
                    auto& new_name_country = countries[params[i].second];
                    auto& old_name_country = countries[params[i].first];
                    countries[params[i].second] = move(countries[params[i].first]);
                    countries.erase(params[i].first);
                    cout << "Country " << params[i].first << " with capital "
                        << new_name_country[new_name_country.size() - 1] <<
                        " has been renamed to " << params[i].second << endl;
                    break;
                }                   
                case cptls_drct_comm::about: { //params name_country ""
                    cout << "about: ";
                    if (countries.find(params[i].first) == countries.end()) {
                        cout << "Country " << params[i].first << " doesn't exist" << endl;
                        break;
                    }
                    auto& country = countries[params[i].first];
                    cout << "Country " << params[i].first << " has capital "
                        << country[country.size() - 1] << endl;
                    break;
                }
                case cptls_drct_comm::capit_dump: { //params: "" ""
                    cout << "dump: ";
                    if (countries.size() == 0) {
                        cout << "There are no countries in the world" << endl;
                        break;
                    }
                    for (const auto& item : countries)
                        cout << item.first << '/' << item.second[item.second.size() - 1] << endl;
                    break;
                }
                default:
                    break;
            }
        }
    }

    void bus_stop1(vector<bus_comm> comms,
        vector<vector<string>>& params) {
        if (comms.size() == 0 || params.size() == 0 || comms.size() != params.size()) return;

        map<string, vector<string>> bus_stops;
        map<string, vector<string>> buses;
        for (size_t i = 0; i < comms.size(); ++i) {
            switch (comms[i])
            {
                case bus_comm::new_bus: {
                    int name_bus_id = 0;
                    
                    for (size_t j = 2; j < params[i].size(); ++j)
                        bus_stops[params[i][j]].push_back(params[i][name_bus_id]);
                    
                    for (size_t j = 2; j < params[i].size(); ++j)
                        buses[params[i][name_bus_id]].push_back(params[i][j]);
                    break;
                }
                case bus_comm::buses_for_stop: {
                    int stop_id = 0;
                    if (bus_stops.find(params[i][stop_id]) == bus_stops.end()) {
                        cout << "No stop" << endl;
                        break;
                    }
                    const auto& stop = bus_stops.find(params[i][stop_id]);
                    print_vector<string>(stop->second);
                    break;
                }
                case bus_comm::stops_for_bus: {
                    int bus_id = 0;
                    if (buses.find(params[i][bus_id]) == buses.end()) {
                        cout << "No bus" << endl;
                        break;
                    }
                    const auto& bus = buses.find(params[i][bus_id]);
                    for (size_t j = 0; j < bus->second.size(); ++j) {
                        cout << "Stop " << bus->second[j] << ": ";
                        for (size_t k = 0; k < bus_stops[bus->second[j]].size(); ++k) {
                            if (bus->first != bus_stops[bus->second[j]][k])
                                cout << bus_stops[bus->second[j]][k] << ' ';
                        }
                        cout << endl;
                    }
                    break;
                }
                case bus_comm::all_buses: {
                    if (buses.size() == 0) {
                        cout << "No buses" << endl;
                        break;
                    }
                    
                    for (const auto& item : buses){
                        cout << "Bus " << item.first << ": ";
                        print_vector<string>(item.second);
                    }
                    break;
                }
                default:
                    break;
            }
        }
    }

    void bus_stop2(vector<vector<string>>& params) {
        if (params.size() == 0) return;
        uint64_t last_bus_id = 0;
        map<vector<string>, uint64_t> buses;
        for (const auto& item : params) {
            if (buses.find(item) != buses.end()) {
                cout << "Already exists for " << buses[item] << endl;
                continue;
            }
            buses[item] =  ++last_bus_id;
            cout << "New bus " << last_bus_id << endl;
        }
    }

    void word_count(vector<string> params) {
        set<string> words;
        for (const auto& item : params)
            words.insert(item);
        cout << words.size() << endl;
    }

    set<string> build_map_values_set(const map<int, string>& map) {
        set<string> values;
        for (const auto& item : map)
            values.insert(item.second);
        return values;  
    }

    void synonyms(vector<syn_comm> comms,
        vector<pair<string, string>>& params) {
        if (comms.size() != params.size()) return;
        
        map<string, set<string>> words;

        for (size_t i = 0; i < comms.size(); ++i) {
            switch (comms[i])
            {
                case syn_comm::add_word: {
                    words[params[i].first].insert(params[i].second);
                    words[params[i].second].insert(params[i].first);
                    break;
                }
                case syn_comm::count: {
                    cout << words[params[i].first].size() << endl;
                    break;
                }
                case syn_comm::check: {
                    if (words[params[i].first].find(params[i].second) !=
                        words[params[i].first].end()) cout << "Yes";
                    else cout << "No";
                    cout << endl;
                    break;
                }
                default:
                    break;
            }
        }
    }

    void bus_stop3(vector<vector<string>>& params) {
        map<set<string>, uint64_t> buses;
        uint64_t last_id = 0;
        for (size_t i = 0; i < params.size(); ++i) {
            set<string> new_bus;
            for (const auto& item : params[i])
                new_bus.insert(item);
            if (buses.find(new_bus) != buses.end()) {
                cout << "Already exists for " << buses[new_bus] << endl;
            }
            else {
                buses[new_bus] = ++last_id;
                cout << "New bus " << last_id << endl;
            }
        }
    }


    void second_weak() {
        cout << "\n--------------------" << endl;
        cout << "|---SECOND WEAK----|" << endl;
        cout << "--------------------\n" << endl;

        cout << "--First task:" << endl;
        cout << "-input: 1 output: " << factorial(1) << endl;
        cout << "-input: -2 output: " << factorial(-2) << endl;
        cout << "-input: 4 output: " << factorial(4) << endl;

        cout << "\n--Second task:" << endl;
        cout << "-input: \"madam\" output: " << is_palindrom("madam") << endl;
        cout << "-input: \"gentleman\" output: " << is_palindrom("gentleman") << endl;

        cout << "--Third task:" << endl;

        cout << "-input: \"abacaba, aba\" 5 output: ";
        vector<string> str_input = {"abacaba", "aba"};
        vector<string> str_res = palindrom_filter(str_input, 5);
        print_vector<string>(str_res);
        str_input.clear();
        str_res.clear();

        cout << "\n-input: \"abacaba, aba\" 2 output: ";
        str_input = {"abacaba", "aba"};
        str_res.clear();

        cout << "\n-input: \"weew, bro, code\" 4 output: ";
        str_input = {"weew", "bro", "code"};
        str_res = palindrom_filter(str_input, 4);
        print_vector<string>(str_res);
        str_input.clear();
        str_res.clear();
        cout << endl;

        cout << "--Fourth task:" << endl;

        int b = 2;
        cout << "-input: " << b;

        update_if_greater(4, b);
        cout << " output: " << b << endl;

        cout << "--Fifth task:" << endl;
        vector<string> source = {"a", "b", "c"};
        vector<string> destination = {"z"};

        cout << "destination befor: ";
        print_vector<string>(destination);

        move_strings(source, destination);

        cout << "after: ";
        print_vector<string>(destination);

        source.clear();
        destination.clear();
        cout << endl;

        cout << "\n--Sixth task:" << endl;
        vector<int> int_input = {1, 5, 3, 4, 2};
        cout << "numbers befor: ";
        print_vector<int>(int_input);
        reverse(int_input);
        cout << "after: ";
        print_vector<int>(int_input);
        cout << endl;
        int_input.clear();

        cout << "\n--Seventh task:" << endl;
        int_input = {1, 5, 3, 4, 2};
        cout << "input vector: ";
        print_vector<int>(int_input);
        vector<int> int_res = reverse__to_copy(int_input);
        cout << "res: ";
        print_vector<int>(int_res);
        cout << endl;
        int_input.clear();
        int_res.clear();

        cout << "\n--Eighth task:" << endl;
        int_input = {7, 6, 3, 0, 9};
        cout << "input: ";
        print_vector<int>(int_input);
        int_res = search_days_by_temp(int_input);
        cout << "output: " << int_res.size() << ' ';
        print_vector<int>(int_res);
        int_input.clear();
        int_res.clear();

        cout << "\n--Ninth task:" << endl;
        vector<p_que_comm> input_comm = {p_que_comm::come, p_que_comm::с_worry, p_que_comm::с_worry, p_que_comm::come,
            p_que_comm::worry_count, p_que_comm::come, p_que_comm::с_worry, p_que_comm::worry_count};
        vector<int> input_params = {5, 1, 4, -2, 0, 3, 3, 0};
        cout << "input: " << endl;
        for (size_t i = 0; i < input_comm.size(); ++i)
            cout << input_comm[i] << ": " << input_params[i] << endl;
        cout << "output: ";
        people_queue(input_comm, input_params);

        cout << "\n--Tenth task:" << endl;
        vector<todo_comm> todo_input = {todo_comm::add, todo_comm::add, todo_comm::add,
            todo_comm::next, todo_comm::todo_dump, todo_comm::todo_dump, todo_comm::next,
            todo_comm::todo_dump, todo_comm::todo_dump, todo_comm::todo_dump, todo_comm::add, todo_comm::todo_dump};
        vector<pair<int, string>> todo_params = {{5, "Salary"},
            {31, "Walk"}, {30,"WalkPreparations"}, {0, ""},
            {5, ""}, {28, ""}, {0, ""},
            {31, ""}, {30, ""}, {28, ""},
            {28, "Payment"}, {28, ""}};
        cout << "input: ";
        for (size_t i = 0; i < todo_input.size(); ++i)
            cout << todo_input[i] << " " << todo_params[i].first << ' ' <<todo_params[i].second << endl;
        cout << "output: " << endl;
        todo_list(todo_input, todo_params);        

        cout << "\n--Eleventh task:" << endl;
        vector<pair<string, string>> anagram_input =
            {{"eat", "tea"}, {"find", "search"}, {"master", "stream"}};
        cout << "input: " << endl;
        for (const auto& item : anagram_input)
            cout << item.first << ' ' << item.second << endl;
        cout << "output: " << endl;
        anagram_test(anagram_input);

        cout << "\n--Twelfth task:" << endl;
        vector<cptls_drct_comm> capit_input = {cptls_drct_comm::change_capital,
            cptls_drct_comm::rename, cptls_drct_comm::about, cptls_drct_comm::rename,
            cptls_drct_comm::change_capital, cptls_drct_comm::capit_dump}; 
        vector<pair<string, string>> capit_params = {{"RussianEmpire", "Petrograd"},
            {"RussianEmpire", "RussianRepublic"}, {"RussianRepublic", ""},
            {"RussianRepublic", "USSR"}, {"USSR", "Moscow"}, {"", ""}};

        cout << "input: " << endl;
        for (size_t i = 0; i < capit_input.size(); ++i) {
            cout << "comm: " << capit_input[i] << ' ' << "params: "
                << capit_params[i].first << ' ' << capit_params[i].second << endl;
        }

        capitals_directory(capit_input, capit_params);
        
        cout << "\n--Thirteenth task:" << endl;
        vector<bus_comm> bus_comms = {bus_comm::all_buses, bus_comm::buses_for_stop,
            bus_comm::stops_for_bus, bus_comm::new_bus, bus_comm::new_bus,
            bus_comm::buses_for_stop, bus_comm::new_bus, bus_comm::new_bus,
            bus_comm::stops_for_bus, bus_comm::all_buses};
        vector<vector<string>> bus_params = {{""}, {"Marushkino"},
            {"32K"}, {"32", "3", "Tolstopaltsevo", "Marushkino", "Vnukovo"},
            {"32K", "6", "Tolstopaltsevo", "Marushkino", "Vnukovo", "Peredelkino", "Solntsevo", "Skolkovo"},
            {"Vnukovo"}, {"950", "6", "Kokoshkino", "Marushkino", "Vnukovo", "Peredelkino", "Solntsevo", "Troparyovo"},
            {"272", "4", "Vnukovo", "Moskovsky", "Rumyantsevo", "Troparyovo"}, {"272"}, {""}};

        cout << "input: " << endl;
        for (size_t i = 0; i < bus_comms.size(); ++i) {
            cout << bus_comms[i] << ": ";
            print_vector<string>(bus_params[i]);
        }
        
        cout << "output: " << endl;
        bus_stop1(bus_comms, bus_params);

        cout << "\n--Fourteenth task:" << endl;
        vector<vector<string>> bus_input = 
            {{"Marushkino", "Kokoshkino"}, {"Kokoshkino"},
            {"Marushkino", "Kokoshkino"}, {"Kokoshkino", "Marushkino"}};
        cout << "output: " << endl;
        bus_stop2(bus_input);

        cout << "\n--Fifteenth task:" << endl;
        vector<string> word_input =
            {"first", "second", "first", "third", "second", "second"};
        cout << "output: "; word_count(word_input);

        cout << "\n--Sixteenth task:" << endl;
        cout << "output: " << endl;
        set<string> values = build_map_values_set({
            {1, "odd"}, {2, "even"}, {3, "odd"},
            {4, "even"}, {5, "odd"}});

        for (const string& value : values)
            cout << value << endl;

        cout << "\n--Seventeenth task:" << endl;
        vector<syn_comm> syn_comms =
            {syn_comm::add_word, syn_comm::count, syn_comm::add_word,
            syn_comm::count, syn_comm::count, syn_comm::check,
            syn_comm::check, syn_comm::check};
        vector<pair<string, string>> syn_params =
            {{"program", "code"}, {"cipher", ""}, {"code", "cipher"}, {"code", ""},
            {"program", ""}, {"code", "program"}, {"program", "cipher"}, {"cpp", "java"}};
        cout << "output: " << endl;
        synonyms(syn_comms, syn_params);

        cout << "\n--Eighteenth task" << endl;
        vector<vector<string>> bus3_params =
            {{"Marushkino", "Kokoshkino"}, {"Kokoshkino"}, {"Marushkino", "Kokoshkino"},
            {"Kokoshkino", "Marushkino"}, {"Kokoshkino", "Kokoshkino"}};
        cout << "output: " << endl;
        bus_stop3(bus3_params);

    }

    vector<int> sort_by_module(string& input) {
        vector<int> nums;

        int i = 2;
        string current_num = "";
        while (i != input.size()) {
            if (input[i] == ' ') {
                nums.push_back(stoi(current_num));
                current_num = "";
            } else {
                current_num += input[i];
            }
            ++i;
        }
        if (current_num != "") nums.push_back(stoi(current_num));
        sort(nums.begin(), nums.end(), [](int a, int b) {
            return abs(a) < abs(b);});

        return nums;
    }

    vector<char> sort_by_asc(string& input) {
        vector<char> symbols;

        for (size_t i = 2; i < input.size(); ++i) {
            if (input[i] != ' ')
                symbols.push_back(input[i]);
        }

        sort(symbols.begin(), symbols.end(), [](char a, char b) {
            return tolower(a) < tolower(b);});

        return symbols;
    }

    void sorted_strings::add_str(const string& s) {
        strings.push_back(s);
        sort(strings.begin(), strings.end(),
            [](string a, string b) {
                return a < b;});
    }
    
    vector<string> sorted_strings::get_sorted_strings() {
        return strings;
    }

    uint64_t Person1::get_last_change(uint64_t year) {
        uint64_t current_change = 0;
        for (const auto item : history) {
            if (item.first > year)
                break;
            current_change = item.first;
        }
        return current_change;
    }

    void Person1::ChangeFirstName(int year, const string& first_name) {
        uint64_t current_change = get_last_change(year);
        history[year].first = first_name;
        if (current_change == 0)
            history[year].second = "";
        else
            history[year].second = history[current_change].second;
    }

    void Person1::ChangeLastName(int year, const string& last_name) {
        uint64_t current_change = get_last_change(year);
        if (current_change == 0)
            history[year].first = "";
        else
            history[year].first = history[current_change].first;
        history[year].second = last_name;
    }

    string Person1::GetFullName(int year) {
        string res = "";
        uint64_t current_change = get_last_change(year);

        if (current_change == 0) {
            res = "Incognito";
        }
        else if (history[current_change].second == "" && history[current_change].first != "")
            res = history[current_change].first + " with unknown last name";
        else if (history[current_change].first == "" && history[current_change].second != "")
            res = history[current_change].second + " with unknown first namev";
        else
            res = history[current_change].first + ' ' + history[current_change].second;
        return res;
    }

    vector<uint64_t> Person1::get_date_history(uint64_t year) {
        vector<uint64_t> full_history;
        for (const auto item : history) {
            if (item.first > year)
                break;
            full_history.push_back(item.first);
        }
        return full_history;
    }

    pair<vector<string>,
        vector<string>> Person1::get_names_history (
        vector<uint64_t> full_history) {
        pair<vector<string>,
            vector<string>> past_names;
        string last_f_change = "";
        string last_s_change = "";
        for (const auto& item : full_history) {
            if (history[item].first != last_f_change)
                past_names.first.push_back(history[item].first);
            if (history[item].second != last_s_change)
                past_names.second.push_back(history[item].second);
            last_f_change = history[item].first;
            last_s_change = history[item].second;
        }
        return past_names;
    }

    string Person1::GetFullNameWithHistory(int year) {
        uint64_t current_change = get_last_change(year);
        if (current_change == 0) {
            return "Incognito";
        }

        vector<uint64_t> full_history = get_date_history(year);
        pair<vector<string>,
            vector<string>> past_names =
            get_names_history(full_history);

        uint64_t f_size = past_names.first.size();
        uint64_t s_size = past_names.second.size();

        string f_names = "";
        string s_names = "";

        if (f_size != 0) {
            f_names = past_names.first[--f_size];
            if (f_size != 0) {
                f_names += " (";
                for (int i = f_size - 1; i >= 0; --i)
                    f_names += past_names.first[i] + ',';
                f_names[f_names.size() - 1] = ')';
            }
        }
        if (s_size != 0) {
            s_names = past_names.second[--s_size];
            if (s_size != 0) {
                s_names += " (";
                for (int i = s_size - 1; i >= 0; --i)
                    s_names += past_names.second[i] + ',';
                s_names[s_names.size() - 1] = ')';
            }
        }

        if (f_names == "")
            return s_names + " with unknown first name";
        if (s_names == "")
            return f_names + " with unknown last name";
        return f_names + ' ' + s_names;
    }

    string ReversibleString::ToString() const {
        return _str;
    }
    void ReversibleString::Reverse() {
        if (_str.size() == 0) return;
        int i = 0;
        int j = _str.size() - 1;
        while (i < j && i != j) {
            char temp = _str[i];
            _str[i] = _str[j];
            _str[j] = temp;
            ++i;
            --j;
        }
    }

    Person2::Person2(const string& f_name, const string& s_name,
            uint64_t b_year) :
        birthday_year(b_year) {
        history[b_year].first = f_name;
        history[b_year].second = s_name;
    }

    uint64_t Person2::get_last_change(uint64_t year) {
        uint64_t current_change = 0;
        for (const auto item : history) {
            if (item.first > year)
                break;
            current_change = item.first;
        }
        return current_change;
    }

    void Person2::ChangeFirstName(int year, const string& first_name) {
        if (year < birthday_year) return;

        uint64_t current_change = get_last_change(year);
        history[year].first = first_name;
        if (current_change == 0)
            history[year].second = "";
        else
            history[year].second = history[current_change].second;
    }

    void Person2::ChangeLastName(int year, const string& last_name) {
        if (year < birthday_year) return;
        
        uint64_t current_change = get_last_change(year);
        if (current_change == 0)
            history[year].first = "";
        else
            history[year].first = history[current_change].first;
        history[year].second = last_name;
    }

    string Person2::GetFullName(int year) {
        if (year < birthday_year) {
            return "No person";
        }

        string res = "";
        uint64_t current_change = get_last_change(year);

        if (current_change == 0) {
            res = "Incognito";
        }
        else if (history[current_change].second == "" && history[current_change].first != "")
            res = history[current_change].first + " with unknown last name";
        else if (history[current_change].first == "" && history[current_change].second != "")
            res = history[current_change].second + " with unknown first namev";
        else
            res = history[current_change].first + ' ' + history[current_change].second;
        return res;
    }

    vector<uint64_t> Person2::get_date_history(uint64_t year) {
        vector<uint64_t> full_history;
        for (const auto item : history) {
            if (item.first > year)
                break;
            full_history.push_back(item.first);
        }
        return full_history;
    }

    pair<vector<string>,
        vector<string>> Person2::get_names_history (
        vector<uint64_t> full_history) {
        pair<vector<string>,
            vector<string>> past_names;
        string last_f_change = "";
        string last_s_change = "";
        for (const auto& item : full_history) {
            if (history[item].first != last_f_change)
                past_names.first.push_back(history[item].first);
            if (history[item].second != last_s_change)
                past_names.second.push_back(history[item].second);
            last_f_change = history[item].first;
            last_s_change = history[item].second;
        }
        return past_names;
    }

    string Person2::GetFullNameWithHistory(int year) {
        if (year < birthday_year) {
            return "No person";
        }

        uint64_t current_change = get_last_change(year);
        if (current_change == 0) {
            return "Incognito";
        }

        vector<uint64_t> full_history = get_date_history(year);
        pair<vector<string>,
            vector<string>> past_names =
            get_names_history(full_history);

        uint64_t f_size = past_names.first.size();
        uint64_t s_size = past_names.second.size();

        string f_names = "";
        string s_names = "";

        if (f_size != 0) {
            f_names = past_names.first[--f_size];
            if (f_size != 0) {
                f_names += " (";
                for (int i = f_size - 1; i >= 0; --i)
                    f_names += past_names.first[i] + ',';
                f_names[f_names.size() - 1] = ')';
            }
        }
        if (s_size != 0) {
            s_names = past_names.second[--s_size];
            if (s_size != 0) {
                s_names += " (";
                for (int i = s_size - 1; i >= 0; --i)
                    s_names += past_names.second[i] + ',';
                s_names[s_names.size() - 1] = ')';
            }
        }

        if (f_names == "")
            return s_names + " with unknown first name";
        if (s_names == "")
            return f_names + " with unknown last name";
        return f_names + ' ' + s_names;
    }

    void third_weak() {
        cout << "\n--------------------" << endl;
        cout << "|-----THIRD WEAK-----|" << endl;
        cout << "--------------------\n" << endl;

        cout << "--First task:" << endl;
        string input = "2 -4 3";
        cout << "output: " << endl;
        vector<int> int_res = sort_by_module(input);
        print_vector(int_res);
        input = "3 1 -3 2";
        int_res = sort_by_module(input);
        print_vector(int_res);

        cout << "\n--Second task" << endl;
        cout << "output: " << endl;
        input = "2 q A";
        vector<char> char_res = sort_by_asc(input);
        print_vector(char_res);
        input = "3 a C b";
        char_res = sort_by_asc(input);
        print_vector(char_res);
        
        cout << "\n--Third task:" << endl;
        cout << "output: " << endl;
        sorted_strings strings;
  
        strings.add_str("first");
        strings.add_str("third");
        strings.add_str("second");
        print_vector(strings.get_sorted_strings());
        
        strings.add_str("second");
        print_vector(strings.get_sorted_strings());

        cout << "\n--Fourth tast:" << endl;
        Person1 f_person;
  
        f_person.ChangeFirstName(1965, "Polina");
        f_person.ChangeLastName(1967, "Sergeeva");
        for (int year : {1900, 1965, 1990})
            cout << f_person.GetFullName(year) << endl;
        
        f_person.ChangeFirstName(1970, "Appolinaria");
        for (int year : {1969, 1970})
            cout << f_person.GetFullName(year) << endl;
        
        f_person.ChangeLastName(1968, "Volkova");
        for (int year : {1969, 1970})
            cout << f_person.GetFullName(year) << endl;

        cout << "\n--Fifth task:" << endl;
        Person1 s_person;
  
        s_person.ChangeFirstName(1965, "Polina");
        s_person.ChangeLastName(1967, "Sergeeva");
        for (int year : {1900, 1965, 1990})
            cout << s_person.GetFullNameWithHistory(year) << endl;
        
        s_person.ChangeFirstName(1970, "Appolinaria");
        for (int year : {1969, 1970})
            cout << s_person.GetFullNameWithHistory(year) << endl;
        
        s_person.ChangeLastName(1968, "Volkova");
        for (int year : {1969, 1970})
            cout << s_person.GetFullNameWithHistory(year) << endl;
        
        s_person.ChangeFirstName(1990, "Polina");
        s_person.ChangeLastName(1990, "Volkova-Sergeeva");
        cout << s_person.GetFullNameWithHistory(1990) << endl;
        
        s_person.ChangeFirstName(1966, "Pauline");
        cout << s_person.GetFullNameWithHistory(1966) << endl;
        
        s_person.ChangeLastName(1960, "Sergeeva");
        for (int year : {1960, 1967})
            cout << s_person.GetFullNameWithHistory(year) << endl;
        
        s_person.ChangeLastName(1961, "Ivanova");
        cout << s_person.GetFullNameWithHistory(1967) << endl;

        cout << "\n--Sixth task:" << endl;
        ReversibleString s("live");
        s.Reverse();
        cout << s.ToString() << endl;
        
        s.Reverse();
        const ReversibleString& s_ref = s;
        string tmp = s_ref.ToString();
        cout << tmp << endl;
        
        ReversibleString empty;
        cout << '"' << empty.ToString() << '"' << endl;

        cout << "\n--Seventh task:" << endl;
        Person2 person("Polina", "Sergeeva", 1960);
        for (int year : {1959, 1960})
            cout << person.GetFullNameWithHistory(year) << endl;
        
        person.ChangeFirstName(1965, "Appolinaria");
        person.ChangeLastName(1967, "Ivanova");
        for (int year : {1965, 1967})
            cout << person.GetFullNameWithHistory(year) << endl;

        cout << "\n--Eighth task:" << endl;
        Incognizable a;
        Incognizable b = {};
        Incognizable c = {0};
        Incognizable d = {0, 1};
        cout << "done";
    }

    void Function::AddPart(const char& operation, double value) {
        parts.push_back({operation, value});
    }

    void Function::Invert() {
        uint64_t parts_size = parts.size();
        if (parts_size != 0) {
            for (int i = parts_size - 1; i >= 0; --i) {
                switch (parts[i].operation)
                {
                case '+': {
                    parts[i].operation = '-';
                    break;
                }
                case '-': {
                    parts[i].operation = '+';
                    break;
                }
                case '*': {
                    parts[i].operation = '/';
                    break;
                }
                case '/': {
                    parts[i].operation = '*';
                    break;
                }
                default:
                    break;
                }
                parts.push_back(parts[i]);
            }
            parts.erase(parts.begin(), parts.begin() + parts_size);
        }
    }

    double Function::Apply(double operand) {
        for (const auto& item : parts) {
            switch (item.operation)
            {
            case '+': {
                operand += item.value;
                break;
            }
            case '-': {
                operand -= item.value;
                break;
            }
            case '*': {
                operand *= item.value;
                break;
            }
            case '/': {
                operand /= item.value;
                break;
            }
            default:
                break;
            }
        }
        return operand;
    }

    Function MakeWeightFunction(const Params& params,
                            const Image& image) {
        Function function;
        function.AddPart('-', image.freshness * params.a + params.b);
        function.AddPart('+', image.rating * params.c);
        return function;
    }

    double ComputeImageWeight(const Params& params, const Image& image) {
        Function function = MakeWeightFunction(params, image);
        return function.Apply(image.quality);
    }

    double ComputeQualityByWeight(const Params& params,
                                const Image& image,
                                double weight) {
        Function function = MakeWeightFunction(params, image);
        function.Invert();
        return function.Apply(weight);
    }

    Function MakeWeightFunction2 (const Params& params,
                            const Image& image) {
        Function function;
        function.AddPart('*', params.a);
        function.AddPart('-', image.freshness * params.b);
        function.AddPart('+', image.rating * params.c);
        return function;
    }

    double ComputeImageWeight2 (const Params& params, const Image& image) {
        Function function = MakeWeightFunction2(params, image);
        return function.Apply(image.quality);
    }

    double ComputeQualityByWeight2 (const Params& params,
                                const Image& image,
                                double weight) {
        Function function = MakeWeightFunction2(params, image);
        function.Invert();
        return function.Apply(weight);
    }

    vector<string> read_input(const string& path) {
        vector<string> res;
        ifstream input(path);
        if (input) {
            string line;
            while (getline(input, line)) {
                res.push_back(line);
            }
        }
        return res;
    }

    void write_otput(const string& path) {
        ofstream output(path, ios::app);
        vector<string> input = read_input("/home/egor/Documents/code/alghoritms/white_belt/input.txt");
        for (const auto& item : input)
            output << item << endl; 
    }

    void read_double(const string& path) {
        ifstream input(path);
        if (input) {
            string value;
            cout << fixed << setprecision(3);
            while (getline(input, value)) {
                cout << stod(value) << endl;
            }
        }
    }

    void read_in_table(const string& path) {
        ifstream input(path);
        if (input) {
            string full;
            string value;
            while (getline(input, value)) {
                full += value + ' ';
            }
            string number;
            set<int> nums;
            for (const char& ch : full) {
                if (ch != ',' && ch != ' ') {
                    number += ch;
                }
                else {
                    nums.insert(stoi(number));
                    number = ""; 
                }
            }
            size_t i = 0;
            for (const int& item : nums) {
                cout << setw(10) << item;
                if (++i%3 == 0)
                    cout << endl;
            }
        }
    }

    void student_info(vector<Student>& stds, 
                    vector<pair<string, int>>& comms) {
        for (const auto& item : comms) {
            if(item.first == "name") {
                if (item.second >! stds.size()) {
                    Student student_ = stds[item.second - 1];
                    cout << student_.name << ' ' << student_.sername << endl;
                }
            }
            else if (item.first == "date") {
                if (item.second >! stds.size()) {
                    Student student_ = stds[item.second - 1];
                    cout << student_.b_day << '.' << student_.b_month
                        << '.' << student_.b_year << endl;
                }
            }
            else {
                cout << "bad request" << endl;
            }
        }
    }

    Rational::Rational(int numerator_, int denominator_) {
        if (denominator_ == 0)
            throw runtime_error("invalid_argument");
        uint64_t max_divider = find_max_divider(numerator_, denominator_);
        numerator = numerator_ / max_divider;
        denominator = denominator_ / max_divider;
        if (numerator == 0) {
            denominator = 1;
        }
        if (denominator < 0) {
            numerator *= -1;
            denominator *= -1;
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
        int max_divider = find_max_divider(general_den, general_num);
        return {(general_num / max_divider), (general_den / max_divider)};
    }

    Rational Rational::operator-(const Rational& other) {
        int general_den = denominator * other.Denominator();
        int general_num = numerator * other.Denominator() -
            other.Numerator() * denominator;
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

    void Rational::Print(const string& msg) const {
        cout << msg << ": " << endl;
        cout << numerator << '/' << denominator << endl;
    }

    void EnsureEqual(const string& left, const string& right) {
        if (left != right)
            throw runtime_error("!=");
    }

    void rational_calculator(vector<stringstream>& input) {
        for (size_t i = 0; i < input.size(); ++i) {
            try {
                Rational rt1;
                Rational rt2;
                char operation;
                input[i] >> rt1;
                input[i].ignore(1);
                input[i] >> operation;
                input[i].ignore(1);
                input[i] >> rt2;

                if (operation == '+')
                    cout << rt1 + rt2 << endl;
                else if (operation == '-')
                    cout << rt1 - rt2 << endl;
                else if (operation == '/')
                    cout << rt1 / rt2 << endl;
                else
                    cout << rt1 * rt2 << endl;
            }
            catch(const exception& e) {
                cerr << e.what() << '\n';
            }
        }
    }

    string connect_and_gettime() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dis(0, 2);
        uint8_t rand_num = dis(gen);
        string current_time_str;
        if (rand_num == 0) {
            throw system_error();
        }
        else if (rand_num == 1) {
            throw runtime_error("xz");
        }
        else {
            auto current_time = chrono::system_clock::now();
            time_t current_time_t = chrono::system_clock::to_time_t(current_time);
            current_time_str = ctime(&current_time_t);
        }
        return current_time_str;
    }

    string AskTimeServer() {
        return connect_and_gettime();
    }

    string TimeServer::GetCurrentTime() {
        try {
            return AskTimeServer();
        }
        catch(const system_error& e) {
            cerr << e.what() << '\n';
            return LastFetchedTime;
        }
    }

    void fourth_weak() {
        cout << "\n--------------------" << endl;
        cout << "|----FOURHT WEAK-----|" << endl;
        cout << "--------------------\n" << endl;

        cout << "--First task:" << endl;
        LectureTitle title(
            Specialization("C++"),
            Course("White belt"),
            Week("4th")
        );
        cout << "done" << endl;
        
        cout << "\n--Second task" << endl;;
        Image image = {10, 2, 6};
        Params params = {4, 2, 6};
        cout << ComputeImageWeight(params, image) << endl;
        cout << ComputeQualityByWeight(params, image, 46) << endl;

        cout << "\n--Third task:" << endl;
        cout << ComputeImageWeight2(params, image) << endl;
        cout << ComputeQualityByWeight2(params, image, 52) << endl;

        cout << "\n--Fourth tast:" << endl;
        vector<string> res = read_input("/home/egor/Documents/code/alghoritms/white_belt/input.txt");
        for (const auto& item : res)
            cout << item << endl;
        write_otput("/home/egor/Documents/code/alghoritms/white_belt/output.txt");

        cout << "\n--Fifth task:" << endl;
        read_double("/home/egor/Documents/code/alghoritms/white_belt/input.txt");

        cout << "\n--Sixth task:" << endl;
        read_in_table("/home/egor/Documents/code/alghoritms/white_belt/input.txt");

        cout << "\n--Seventh task:" << endl;
        vector<Student> stds = {
            {"Ivan", "Ivanov", 1, 1, 1901}, 
            {"Petr", "Petrox", 2, 2, 1902},
            {"Alexander", "Sidorov", 3, 3, 1903}};
        vector<pair<string, int>> comms = {
            {"name", 1}, {"date", 3}, {"mark", 5}};
        student_info(stds, comms);        

        cout << "\n--Eighth task:" << endl;
        stringstream str_input("2, 3");
        Rational rt0;
        str_input >> rt0;
        cout << rt0 << endl;
        Rational rt1{2, 3};
        rt1.Print("rt1");
        Rational rt2{-2, 3};
        rt2.Print("rt2");
        Rational rt3{2, -3};
        rt3.Print("rt3");
        Rational rt4{-2, -3};
        rt4.Print("rt4");
        Rational rt5{2, 2};
        rt5.Print("rt5");
        if (rt2 == rt3) cout << "rt2 == rt3" << endl;
        else cout << "rt2 != rt3" << endl;
        if (rt4 == rt5) cout << "rt4 == rt5" << endl;
        else cout << "rt4 != rt5" << endl;
        Rational rt6 = rt4 + rt5;
        rt6.Print("plus1");
        rt6 = rt2 + rt3;
        rt6.Print("plus2");
        rt6 = Rational(10, 15) - Rational(20, 5);
        rt6.Print("minus1");
        rt6 = Rational(-3, 4) / Rational(3, 4);
        rt6.Print("devide1");
        rt6 = Rational(4, 7) / Rational(2, 5);
        rt6.Print("devide2");
        rt6 = Rational(2, 5) * Rational(3, 4);
        rt6.Print("mlt1");
        rt6 = Rational(-2, 5) * Rational(-3, 4);
        rt6.Print("mlt2");
        map<Rational, string> name;

        cout << "\n--Ninth task:" << endl;
        try {
            EnsureEqual("test1", "test2");
        }
        catch(const exception& e) {
            cerr << "error: " << e.what() << endl;
        }

        cout << "\n--Tenth task:" << endl;
        try {
            Rational rt7 = {0, 0};
        }
        catch(const exception& e) {
            cout << "error: " << e.what() << endl;
        }

        try {
            Rational rt8 = Rational{1, 5} / Rational{0, 1};
        }
        catch(const exception& e) {
            cerr << e.what() << '\n';
        }

        cout << "\n--Eleventh task:" << endl;
        vector<stringstream> input;
        input.emplace_back("1/2 + 1/3");
        input.emplace_back("1/2 + 5/0");
        input.emplace_back("4/5 / 0/8");

        rational_calculator(input);

        cout << "\n--Twelfth task:" << endl;
        TimeServer ts;
        try {
            cout << ts.GetCurrentTime() << endl;
        }
        catch(const exception& e) {
            cerr << e.what() << '\n';
        }
        
    }

    void database::add(pair<string, string>& params) {
        events[params.first].insert(move(params.second));
    }

    string database::del(const pair<string, string>& params) {
        if (params.second != "") {
            auto iter = events[params.first].find(params.second);
            if (iter == events[params.first].end())
                return "event not found";
            events[params.first].erase(iter);
            return "deleted successfully";
        }
        else {
            uint64_t size = events[params.first].size();
            events[params.first].clear();
            return "deleted " + to_string(size) + " events";
        }
    }

    vector<string> database::find(string& date) const {
        vector<string> res;
        auto elem = events.find(date);
        if (elem != events.end()) {
            for (const auto& item : elem->second)
                res.push_back(item);
        }
        return res;
    }

    vector<pair<string, set<string>>> database::get_all() const {
        vector<pair<string, set<string>>> res;
        for (const auto& item : events) {
            if (item.second.size() > 0) {
                res.emplace_back(pair(item.first, item.second));
            }
        }
        return res;
    }

    string work_with_db::validate_date(string& date) {
        int year = 0;
        int month = 0;
        int day = 0;

        uint64_t check = 0;
        string word;
        for (size_t i = 0; i <= date.size(); ++i) {
            if (i == date.size() || date[i] == '-') {
                if (check == 0) {
                    year = stoi(word);
                }
                else if (check == 1) {
                    month = stoi(word);
                }
                else if (check == 2) {
                    day = stoi(word);
                    break;
                }
                word = "";
                ++check;
            }
            else {
                word += date[i];
            }
        }

        if (month < 1 || month > 12)
            return "month value is invalid: " + to_string(month);
        else if (day < 1 || day > 31)
            return "day value is invalid: " + to_string(day);
        return "ok";
    }

    void work_with_db::set_comm_date(const string& input,
        pair<string, string>& params, db_comms& comm) {
        string word;
        vector<string> temp;
        for (size_t i = 0; i <= input.size(); ++i) {
            if (i == input.size() || input[i] == ' ') {
                temp.push_back(word);
                word = "";
            }
            else {
                word += input[i];
            }
        }

        if (temp[0] == "add")
            comm = db_comms::db_comms_add;
        else if(temp[0] == "del")
            comm = db_comms::db_comms_del;
        else if (temp[0] == "find")
            comm = db_comms::db_comms_find;
        else if (temp[0] == "print")
            comm = db_comms::db_comms_print;
        else
            throw runtime_error("uncknow_comm");

        if (comm != db_comms::db_comms_print) {
            regex pattern("\\b[0-9]+-[0-9]+-[0-9]+\\b");
            if (!regex_match(temp[1], pattern)) {
                throw runtime_error("Wrong date format: " + temp[1]);
            }
            else {
                string validate_res = validate_date(temp[1]);
                if(validate_res == "ok")
                    params.first = temp[1];
                else
                    throw runtime_error(validate_res);
            }
            if (comm == db_comms::db_comms_add) {
                params.second = temp[2];
            }
        }
    }

    void work_with_db::executing(pair<string, string>& params,
                                db_comms comm) {
        switch (comm) {
            case db_comms::db_comms_add: {
                db.add(params);
                break;
            }
            case db_comms::db_comms_del: {
                string res = db.del(params);
                cout << res << endl;
                break;
            }
            case db_comms::db_comms_find: {
                vector<string> res = db.find(params.first);
                print_vector<string>(res);
                break;
            }
            case db_comms::db_comms_print: {
                vector<pair<string, set<string>>> res = db.get_all();
                for (const auto& event : res) {
                    cout << "date: " << event.first << " events: ";
                    for (const auto& name : event.second) {
                        cout << name << ' ';
                    }
                    cout << endl;
                }
                break;
            }
            default:
                break;
        }
    }

    void work_with_db::run(istream& input) {
        pair<string, string> params;
        db_comms comm;
        try {
            string str;
            getline(input, str);
            set_comm_date(str, params, comm);
            executing(params, comm);
        }
        catch(const exception& e) {
            cerr << e.what() << '\n';
        }
    }

    void fifth_weak() {
        cout << "\n--------------------" << endl;
        cout << "|-----FIFTH WEAK-----|" << endl;
        cout << "--------------------\n" << endl;

        cout << "--First task:" << endl;
        work_with_db wwdb;
        vector<stringstream> input;
        input.emplace_back("add 0-1-2 event1");
        input.emplace_back("add 1-2-3 event2");
        input.emplace_back("find 0-1-2");
        input.emplace_back("del 0-1-2");
        input.emplace_back("print");
        input.emplace_back("add 0-13-32 event1");

        for (auto& item : input)
            wwdb.run(item);
    }

    void test()
    {
        first_weak();
        second_weak();
        third_weak();
        fourth_weak();
        fifth_weak();
    }
}