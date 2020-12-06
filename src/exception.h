#pragma once

#include <exception>
#include <stdint.h>


class EndException : public std::exception {
private:
    const char *message;
public:
    EndException(const char *msg) {
        message = msg;
    };

    const char *what() {
        return message;
    }
};

class SimpleException : public std::exception {
private:
    const char *message;
public:
    SimpleException(const char *msg) {
        message = msg;
    };

    const char *what() {
        return message;
    }
};

class ComputeException : public std::exception {
private:
    const char *message;
public:
    ComputeException(const char *msg) {
        message = msg;
    };

    const char *what() {
        return message;
    }
};

class RegisterException : public std::exception {
private:
    const char *message;
public:
    RegisterException(const char *msg) {
        message = msg;
    };

    const char *what() {
        return message;
    }
};

class OutOfMemoryException : public std::exception {
private:
    const char *message;
    uint64_t pa;
public:
    OutOfMemoryException(const char *msg, uint64_t pa_) {
        message = msg;
        pa = pa_;
    };

    const char *what() {
        return message;
    }

    uint64_t GetPa() {
        return pa;
    }
};

class UnalignException : public std::exception {
private:
    const char *message;
    uint64_t pa;
public:
    UnalignException(const char *msg, uint64_t pa_) {
        message = msg;
        pa = pa_;
    };

    const char *what() {
        return message;
    }

    uint64_t GetPa() {
        return pa;
    }
};

class PageFaultException : public std::exception {
private:
    const char *message;
    uint32_t pte;

public:
    PageFaultException(const char *msg, uint32_t pte_) {
        message = msg;
        pte = pte_;
    };

    const char *what() {
        return message;
    }

    uint32_t GetPte() {
        return pte;
    }
};
