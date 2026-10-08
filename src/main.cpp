#include <charconv>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

struct Row {
    int line_no = 0;
    bool ok = false;
    double value = 0.0;
    std::string reason;
};

std::string_view trim(std::string_view text) {
    while (!text.empty() && (text.front() == ' ' || text.front() == '\t' || text.front() == '\r')) {
        text.remove_prefix(1);
    }
    while (!text.empty() && (text.back() == ' ' || text.back() == '\t' || text.back() == '\r')) {
        text.remove_suffix(1);
    }
    return text;
}

// Whole token must be a number. Trailing junk is a reject, not a partial parse.
bool parse_number(std::string_view token, double& out, std::string& reason) {
    if (token.empty()) {
        reason = "empty line";
        return false;
    }
    double value = 0.0;
    const char* first = token.data();
    const char* last = token.data() + token.size();
    const auto parsed = std::from_chars(first, last, value);
    if (parsed.ec != std::errc{}) {
        reason = "not a number";
        return false;
    }
    if (parsed.ptr != last) {
        reason = "trailing junk";
        return false;
    }
    out = value;
    return true;
}

Row check_line(int line_no, std::string_view raw) {
    Row row;
    row.line_no = line_no;
    const std::string_view text = trim(raw);
    if (text.empty()) {
        row.reason = "empty line";
        return row;
    }
    if (text.front() == '#') {
        row.reason = "comment";
        return row;
    }
    double value = 0.0;
    std::string reason;
    if (!parse_number(text, value, reason)) {
        row.reason = reason;
        return row;
    }
    row.ok = true;
    row.value = value;
    return row;
}

bool write_report(const std::string& path, const std::vector<Row>& rows) {
    std::ofstream out(path);
    if (!out) {
        return false;
    }
    int accepted = 0;
    int rejected = 0;
    for (const Row& row : rows) {
        if (row.reason == "comment") {
            continue;
        }
        if (row.ok) {
            ++accepted;
        } else {
            ++rejected;
        }
    }
    out << "accepted: " << accepted << '\n';
    out << "rejected: " << rejected << '\n';
    for (const Row& row : rows) {
        if (row.reason == "comment") {
            continue;
        }
        out << "line " << row.line_no << ": ";
        if (row.ok) {
            out << "ok " << row.value;
        } else {
            out << "reject " << row.reason;
        }
        out << '\n';
    }
    return static_cast<bool>(out);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "usage: cpp-file-check <input.txt> [report.txt]\n";
        return 1;
    }
    const std::string input_path = argv[1];
    const std::string report_path = argc >= 3 ? argv[2] : "report.txt";

    std::ifstream input(input_path);
    if (!input) {
        std::cerr << "cannot open input: " << input_path << '\n';
        return 2;
    }

    std::vector<Row> rows;
    std::string line;
    int line_no = 0;
    while (std::getline(input, line)) {
        ++line_no;
        rows.push_back(check_line(line_no, line));
    }
    if (!write_report(report_path, rows)) {
        std::cerr << "cannot write report: " << report_path << '\n';
        return 3;
    }
    std::cout << "report: " << report_path << '\n';
    return 0;
}
