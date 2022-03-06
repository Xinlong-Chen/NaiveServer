#pragma once

#include <iostream>
#include <string>

class Timestamp {
public:
    Timestamp() : microSecondsSinceEpoch_(0) { }
    explicit Timestamp(int64_t microSecondsSinceEpochArg)
            : microSecondsSinceEpoch_(microSecondsSinceEpochArg) { }
    static Timestamp now();
    std::string toString() const;
    
private:
    int64_t microSecondsSinceEpoch_;
};