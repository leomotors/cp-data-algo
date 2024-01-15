#include <iostream>

int main() {
    std::cout <<
        []() {
            return []() {
                return []() {
                    return []() {
                        return []() {
                            return []() {
                                return []() {
                                    return []() {
                                        return []() {
                                            return []() {
                                                return []() {
                                                    return []() {
                                                        return []() {
                                                            return []() {
                                                                return []() {
                                                                    return []() {
                                                                        return []() {
                                                                            return []() {
                                                                                return []() {
                                                                                    return "Hello World!";
                                                                                };
                                                                            };
                                                                        };
                                                                    };
                                                                };
                                                            };
                                                        };
                                                    };
                                                };
                                            };
                                        };
                                    };
                                };
                            };
                        };
                    };
                };
            };
        }()()()()()()()()()()()()()()()()()()()
              << std::endl;
}
