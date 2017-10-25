#ifndef __EVALUATOR_HPP__
#define __EVALUATOR_HPP__

#include <cmath>
#include <string>
#include <map>

class Calc {
public:
    const int SUCCESS = 0;
    const int ERROR_EXPRESSION = 1;
    const int ERROR_DIVZERO = 2;

private:
    const std::pair<int, double> BAD_EXPRESSION = {ERROR_EXPRESSION, 0.0};
    const double EPS = 1e-10;

    std::map<int, std::tuple<int, bool, double, std::string>> calc;

    std::string crearExpression(const std::string &exp) {
        std::string clean;
        for (const char &c: exp) {
            if (c != ' ' && c != '\t')
                clean.push_back(c);
        }
        return clean;
    }

    std::pair<int, double> evaluateExpression(std::string::iterator &it, const std::string::iterator &end) {
        return expression(it, end);
    }

    std::pair<int, double> expression(std::string::iterator &it, const std::string::iterator &end) {
        auto retl = term(it, end);
        if (retl.first != SUCCESS) return retl;
        else if (it == end) return retl;
        else if (*it == '+' || *it == '-') {
            char op = *it;
            auto retr = expression(++it, end);
            if (retr.first != SUCCESS) return retr;
            if (op == '+') return {SUCCESS, retl.second + retr.second};
            return {SUCCESS, retl.second - retr.second};
        }
        return retl;
    }

    std::pair<int, double> term(std::string::iterator &it, const std::string::iterator &end) {
        auto retl = factor(it, end);
        if (retl.first != SUCCESS) return retl;
        else if (it == end) return retl;
        else if (*it == '*' || *it == '/') {
            char op = *it;
            auto retr = term(++it, end);
            if (retr.first != SUCCESS) return retr;
            if (op == '*') return {true, retl.second * retr.second};
            if (std::abs(retr.second) < EPS) return {ERROR_DIVZERO, 0.0};
            return {true, retl.second / retr.second};
        }
        return retl;
    }

    std::pair<int, double> factor(std::string::iterator &it, const std::string::iterator &end) {
        if (*it == '(') {
            auto ret = expression(++it, end);
            if (ret.first != SUCCESS) return ret;
            if (it == end || *it != ')') return BAD_EXPRESSION;
            ++it;
            return ret;
        } else if (isalpha(*it)) {
            return cell(it, end);
        } else {
            return number(it, end);
        }
    }

    std::pair<int, double> cell(std::string::iterator &it, const std::string::iterator &end) {
        std::string ce;
        for (; it != end && isalpha(*it); it++)
            ce.push_back(*it);
        for (; it != end && isdigit(*it); it++)
            ce.push_back(*it);
        if (!isalpha(ce.front())) return BAD_EXPRESSION;
        if (!isdigit(ce.back())) return BAD_EXPRESSION;
    }

    std::pair<int, double> number(std::string::iterator &it, const std::string::iterator &end) {
        std::string nu;
        if (!isdigit(*it) && *it != '-') return BAD_EXPRESSION;
        if (*it == '-') nu.push_back('-'), ++it;
        for (; it != end && isdigit(*it); it++)
            nu.push_back(*it);
        if (it == end || *it != '.') return {SUCCESS, std::stod(nu)};
        if (*it == '.') nu.push_back(*it), ++it;
        for (; it != end && isdigit(*it); it++)
            nu.push_back(*it);
        return {SUCCESS, std::stod(nu)};
    }

public:
    void clearCache() {
        for (auto &e: calc) {
            std::get<1>(e.second) = false;
        }
    }

    void setCell(int id, std::string exp) {
        calc[id] = std::make_tuple(SUCCESS, false, 0.0, exp);
    }

    std::pair<int, double> evaluateSingle(int id) {
        auto &e = calc[id];
        if (!std::get<1>(e)) {
            std::string cleanExpression = crearExpression(std::get<3>(e));
            std::string::iterator it = cleanExpression.begin();
            auto res = evaluateExpression(it, cleanExpression.end());
            std::get<0>(e) = res.first;
            std::get<1>(e) = true;
            std::get<2>(e) = res.second;
            return res;
        }
        return {std::get<0>(e), std::get<2>(e)};
    }
};

#endif