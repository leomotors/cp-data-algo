#include <stack>
#include <utility>
#include <vector>

int eval_postfix(std::vector<std::pair<int, int>> v) {
    std::stack<int> s;

    for (const auto& [type, operand] : v) {
        if (type == 1) {
            s.push(operand);
        } else {
            int b = s.top();
            s.pop();
            int a = s.top();
            s.pop();

            switch (operand) {
                case 0:
                    s.push(a + b);
                    break;
                case 1:
                    s.push(a - b);
                    break;
                case 2:
                    s.push(a * b);
                    break;
                case 3:
                    s.push(a / b);
                    break;
            }
        }
    }

    return s.top();
}
