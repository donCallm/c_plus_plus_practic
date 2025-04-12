#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>

using namespace std;

namespace ybelt {
    void test();
    //first weak
    void first_weak();

    void avg_temp(vector<int> temps);

    enum class Lang {
        DE, FR, IT
    };

    struct Region {
        string std_name;
        string parent_std_name;
        map<Lang, string> names;
        int64_t population;
    };

    enum class TaskStatus {
        NEW,
        IN_PROGRESS,
        TESTING,
        DONE
    };

    using TasksInfo = map<TaskStatus, int>;

    class TeamTasks {
        public:
        const TasksInfo& GetPersonTasksInfo(const string& person) const;
        
        void AddNewTask(const string& person);
        
        pair<TasksInfo, TasksInfo> PerformPersonTasks(
            const string& person, int task_count);
        private:
            void AddNewPerson(const string& person);
        private:
            map<string, TasksInfo> persons;
    };

    //second weak
    void second_weak();

    class TestRunner {
        public:
        template <class TestFunc>
        void RunTest(TestFunc func, const string& test_name);

        ~TestRunner();

        private:
            int fail_count = 0;
    };

    using history = map<int, string>;

    class Person {
        public:
            void ChangeFirstName(int year, const string& first_name);
            void ChangeLastName(int year, const string& last_name);
            string GetFullName(int year) const;
            string GetSecondName(int year) const;
            string GetFirstName(int year) const;
        private:
            int find_last_year(bool id_hs, int year) const;
        private:
            history f_name_history;
            history s_name_history;
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
            string ToString();
        private:
            int numerator;
            int denominator;
    };

    //third weak
    void third_weak();

    class PhoneNumber {
        public:
            PhoneNumber() {}
            explicit PhoneNumber(const string &international_number);

            string GetCountryCode() const;
            string GetCityCode() const;
            string GetLocalNumber() const;
            string GetInternationalNumber() const;
        private:
                string _country_code;
                string _city_code;
                string _local_number;
    };

    class Rectangle {
        public:
            Rectangle(int width, int height) : width_(width), height_(height) {}

            int GetArea() const { return width_ * height_; }
            int GetPerimeter() const { return 2 * (width_ + height_); }
            int GetWidth() const { return width_; }
            int GetHeight() const { return height_; }
        private:
            int width_, height_;
    };

    //fourth weak
    void fourth_weak();

    void PrintVectorPart(const vector<int>& numbers);
    enum class Gender {
        FEMALE,
        MALE
    };

    struct Person2 {
        int age;  // возраст
        Gender gender;  // пол
        bool is_employed;  // имеет ли работу
    };

    using change_history = map<int, string>;

    class Person3 {
        public:
            void ChangeFirstName(int year, const string& first_name);
            void ChangeLastName(int year, const string& last_name);
            string GetFirstName(int year);
            string GetSecondName(int year);
            string GetFullName(int year);

        private:
            int find_last_fname_year(int year);
            int find_last_sname_year(int year);
        private:
            change_history _f_name_history;
            change_history _s_name_history;
    };

    //fifth weak
    void fifth_weak();

    class Animal {
        public:
            Animal(const string& name = "animal") : _name(name) {}
        public:
            const string _name;
    };


    class Dog : public Animal {
        public:
            Dog(const string& name = "dog") : Animal(name) {}
        void Bark() {
            cout << _name << " barks: woof!" << endl;
        }
    };

    class INotifier {
        public:
            void virtual Notify (const string& msg) = 0;
        private:
            
    };

    class SmsNotifier : INotifier {
        public:
            SmsNotifier(const string& number) : _number(number) {}

            void Notify (const string& msg) override;
        private:
            string _number;
    };

    class EmailNotifier : INotifier {
        public:
            EmailNotifier(const string& email) : _email(email) {}

            void Notify(const string& msg) override;
        private:
            string _email;
    };

    class Figure {
        public:
            Figure(const string& name)
                : _name(name) {}

            string Name() { return _name; };
            double virtual Perimeter() = 0;
            double virtual Area() = 0;
        protected:
            const string _name;
    };

    class Triangle : public Figure {
        public:
            Triangle(const string& params, const string& name = "TRIANGLE");

            double Perimeter() override;
            double Area() override;
        private:
            int _first_side;
            int _second_side;
            int _third_side;
    };

    class Rect : public Figure {
        public:
            Rect(const string& params, const string& name = "RECT");
        
            double Perimeter() override;
            double Area() override;
        private:
            int _width;
            int _hight;
    };

    class Circle : public Figure {
        public:
            Circle(const string& radius, const string& name = "CIRCLE");

            double Perimeter() override;
            double Area() override;
        private:
            int _radius;
    };

    shared_ptr<Figure> CreateFigure(stringstream& is);

    class Person4 {
        public:
            Person4(const string& name, const string& occupation) : _name(name), _occupation(occupation) {}

            string GetName() const { return _name; }
            string GetOccupation() const { return _occupation; }
            virtual void Walk(const string& destination) const = 0;

        private:
            const string _name;
            const string _occupation;
    };


    class Student : public Person4 {
        public:

            Student(const string& name, const string& favouriteSong) : Person4(name, "Student"), _favouriteSong(favouriteSong) {}

            void Learn() const {
                cout << "Student: " << GetName() << " learns" << endl;
            }

            void Walk(const string& destination) const override {
                cout << "Student: " << GetName() << " walks to: " << destination << endl;
                SingSong();
            }

            void SingSong() const {
                cout << "Student: " << GetName() << " sings a song: " << _favouriteSong << endl;
            }

        private:
            const string _favouriteSong;
    };


    class Teacher : public Person4 {
        public:

            Teacher(const string& name, const string& subject) : Person4(name, "Teacher"), _subject(subject) {}

            void Teach() const {
                cout << "Teacher: " << GetName() << " teaches: " << _subject << endl;
            }

            void Walk(const string& destination) const override {
                cout << "Teacher: " << GetName() << " walks to: " << destination << endl;
            }

        private:
            const string _subject;
    };


    class Policeman : public Person4 {
        public:
            Policeman(const string& name) : Person4(name, "Policeman") {}

            void Check(Person4& person) const {
                cout << "Policeman: " << GetName() << " checks " << person.GetOccupation() << ". "
                    << person.GetOccupation() << "'s name is: " << person.GetName() << endl;
            }

            void Walk(const string& destination) const override {
                cout << "Policeman: " << GetName() << " walks to: " << destination << endl;
            }
    };


    inline void VisitPlaces(Person4& person, vector<string> places) {
        for (const auto& p : places) {
            person.Walk(p);
        }
    }
}