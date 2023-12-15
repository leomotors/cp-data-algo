#ifndef __STUDENT_H_
#define __STUDENT_H_

#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

// you can include anything

using namespace std;

class DigitalWallet {
    // you can declare variables or write new function
  private:
    typedef std::deque<std::pair<size_t, int>> PersonT;

    struct Person {
        PersonT balance;
        int totalBalance;
    };

    std::map<std::string, Person> bank;

    int total_give = 0;
    int total_spent = 0;
    int total_expired = 0;

    void cleanExpired(size_t time, string person_id) {
        auto &[balance, totalBalance] = bank[person_id];

        while (!balance.empty() && balance.front().first < time) {
            totalBalance -= balance.front().second;
            total_expired += balance.front().second;
            balance.pop_front();
        }
    }

    // optimization
    std::deque<std::pair<size_t, std::set<std::string>>> expiredLookup;

  public:
    void add_money(size_t time, string person_id, int amount, size_t duration) {
        auto &[balance, totalBalance] = bank[person_id];
        size_t expireTime = time + duration;

        if (balance.empty() || balance.back().first != expireTime) {
            balance.push_back({expireTime, amount});
        } else {
            balance.back().second += amount;
        }

        totalBalance += amount;
        total_give += amount;

        if (!expiredLookup.empty() &&
            expiredLookup.back().first == expireTime) {
            expiredLookup.back().second.insert(person_id);
        } else {
            expiredLookup.push_back({expireTime, {person_id}});
        }

        cleanExpired(time, person_id);
    }

    bool use_money(size_t time, string person_id, int amount) {
        // your code here
        cleanExpired(time, person_id);

        auto &[balance, totalBalance] = bank[person_id];

        if (totalBalance < amount) {
            return false;
        }

        totalBalance -= amount;
        total_spent += amount;

        while (amount > 0) {
            if (balance.front().second > amount) {
                balance.front().second -= amount;
                return true;
            } else {
                amount -= balance.front().second;
                balance.pop_front();
            }
        }

        return true;
    }

    int current_money(size_t time, string person_id) {
        cleanExpired(time, person_id);
        return bank[person_id].totalBalance;
    }

    void status(size_t time, long long &total_give, long long &total_spent,
                long long &total_expired) {
        // your code here
        while (!expiredLookup.empty() && time > expiredLookup.front().first) {
            for (auto &pid : expiredLookup.front().second)
                cleanExpired(time, pid);

            expiredLookup.pop_front();
        }

        total_give = this->total_give;
        total_spent = this->total_spent;
        total_expired = this->total_expired;
    }
};

#endif
