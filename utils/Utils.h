#ifndef TESTPROJECT_UTILS_H
#define TESTPROJECT_UTILS_H

#include <iostream>
#include <chrono>
#include <type_traits>

#include "ConsoleColors.h"
#include "Test.h"

using namespace std;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;

class Utils {

private:
    static int msPrecision;
    static string getStartString();
    static string getEndString();

    template<typename T>
    static auto timed(const string& displayName, T& func);

public:
    template<typename T>
    static void* timedRunner(const string &displayName, T& func);

    template<typename T>
    static auto timedSupplier(const string& displayName, T& func);

};

int Utils::msPrecision = 4;

string Utils::getStartString() {
    return "--- START_EXEC ---";
}

string Utils::getEndString() {
    return "--- END_EXEC ---";
}

// **************************** //

template<typename T>
auto Utils::timed(const string& displayName, T& func) {
    auto start = system_clock::now();
    auto startDuration = duration_cast<milliseconds>(start.time_since_epoch());
    long long startMs = startDuration.count();

    string startString = to_string(startMs);
    string startStringSub = startString.substr(startString.size() - msPrecision);
    string startFormat = getStartString() + " (" + displayName + ") ..." + startStringSub;

    cout << endl << yellow << startFormat << white << endl;
    // --------------------------------------

    auto result = func(); // we run the given function

    // --------------------------------------
    auto end = system_clock::now();
    auto endDuration = duration_cast<milliseconds>(end.time_since_epoch());
    long long endMs = endDuration.count();

    string endString = to_string(endMs);
    string endStringSub = endString.substr(endString.size() - msPrecision);

    long long elapsedMs = endMs - startMs;
    string elapsedString = to_string(elapsedMs);
    string elapsedFormat = getEndString() + " (" + displayName + ") ..." + endStringSub + " (" + elapsedString + "ms)";

    cout << endl << green << elapsedFormat << white << endl;

    return result;
}

// **************************** //

// timedRunner helpers

void (*savedFunc)();

void* savedFuncSupplier(){
    savedFunc();
    return nullptr;
}

// **************************** //

template<typename T>
void* Utils::timedRunner(const string& displayName, T& func) {
    savedFunc = func;
    return timed(displayName, savedFuncSupplier);
}

template<typename T>
auto Utils::timedSupplier(const string& displayName, T& func) {
    return timed(displayName, func);
}

//if (std::is_same<decltype(func()), void>::value) // YUP ce test existe si jamais

#endif //TESTPROJECT_UTILS_H
