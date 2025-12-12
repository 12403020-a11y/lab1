#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <memory>
#include <cmath>
#include <random>

// Константи та утиліти
constexpr double PI_VAL = 3.1415926535;

template <typename T>
T square(T x) {
    return x * x;
}

struct User {
    std::string name;
    int age;
    std::string city;

    friend std::ostream& operator<<(std::ostream& os, const User& u) {
        return os << u.name << " - age: " << u.age << " - city: " << u.city;
    }
};

class Base {
public:
    virtual ~Base() = default;
    virtual void run() const {
        std::cout << "[Base] running...\n";
    }
};

class Derived : public Base {
public:
    void run() const override {
        std::cout << "[Derived] running...\n";
    }
};

static std::unique_ptr<Base> createObject(bool makeDerived) {
    if (makeDerived) {
        return std::make_unique<Derived>();
    }
    return std::make_unique<Base>();
}

static int calculateSum(const std::vector<int>& data) {
    return std::accumulate(data.begin(), data.end(), 0);
}

static std::map<std::string, std::string> parseConfig(const std::string& filepath) {
    std::map<std::string, std::string> config;
    std::ifstream file(filepath);

    if (!file.is_open()) {
        std::cerr << "Warning: Could not open config file: " << filepath << "\n";
        return config;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream is_line(line);
        std::string key;
        if (std::getline(is_line, key, '=')) {
            std::string value;
            if (std::getline(is_line, value)) {
                size_t commaPos = value.find(',');
                if (commaPos != std::string::npos) {
                    value = value.substr(0, commaPos);
                }
                config[key] = value;
            }
        }
    }
    return config;
}

static std::vector<int> processData(int x, int y, std::vector<int> data = {}) {
    data.push_back(x);
    data.push_back(y);
    for (auto& val : data) {
        val = square(val);
    }
    return data;
}

int main(int argc, char* argv[]) {
    // Налаштування генератора
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 1);

    std::cout << "Application Start\n";

    try {
        std::vector<int> v1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        int sum1 = calculateSum(v1);
        std::cout << "Sum of elements: " << sum1 << "\n";

        // Сортування
        std::shuffle(v1.begin(), v1.end(), gen);
        std::sort(v1.begin(), v1.end());

        // Конфігурація
        std::string dataFile = "data.txt";
        auto config = parseConfig(dataFile);

        std::string mode = (argc > 1) ? argv[1] : (config.count("mode") ? config["mode"] : "default");
        std::cout << "Current Mode: " << mode << "\n";

        // Поліморфізм
        bool randomChoice = distrib(gen);
        auto obj = createObject(randomChoice);
        obj->run();

        // Арифметика
        int a = 3;
        int r = square(a + 1);
        std::cout << "Square result: " << r << "\n";

        // Структура
        User currentUser{ "John Doe", 30, "Kyiv" };
        std::cout << "User info: " << currentUser << "\n";

    }
    catch (const std::exception& e) {
        std::cerr << "Error occurred: " << e.what() << "\n";
        return 1;
    }

    std::cout << "Application Done\n";
    return 0;
}