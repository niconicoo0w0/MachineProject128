#include "dna_strand.hpp"
#include <stdexcept>
#include "node.hpp" 
#include <cassert> 
#include <stdexcept>

DNAstrand::~DNAstrand() {
    while(head_ != nullptr) {
        Node* curr = head_;
        head_ = head_->next;
        delete curr;
    }
    tail_ = nullptr;
}

int DNAstrand::Length(const char* pattern) {
    if (pattern[0] == '\0') {
        return 0;
    }
    int len = 0;
    for (int i = 0; pattern[i] != '\0'; i++) {
        len++;
    }
    return len;
}

Node* DNAstrand::FindStart(const char* pattern) {
    Node* start = nullptr;
    Node* curr = head_;
    if (pattern[0] == '\0') {
        return nullptr;
    }
    while (curr != nullptr) {
        if (curr->data == pattern[0]) {
            Node* temp = curr;
            for (int index = 0; temp != nullptr && pattern[index] != '\0' && temp->data == pattern[index]; index++) {
                temp = temp->next;
                if (pattern[index] == '\0') {
                    start = curr;
                }
            }
        }
        curr = curr->next;
    }
    return start;
}

Node* DNAstrand::FindEnd(const char* pattern) {
    Node* curr = head_;
    Node* end = nullptr;
    if (pattern[0] == '\0') {
        return nullptr;
    }
    while (curr != nullptr) {
        if (curr->data == pattern[0]) {
            Node* temp = curr;
            for (int index = 0; temp != nullptr && pattern[index] != '\0' && temp->data == pattern[index]; index++) {
                temp = temp->next;
                if (pattern[index] == '\0') {
                    end = temp;
                }
            }
        }
        curr = curr->next;
    }
    return end;
}

void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
    if (pattern[0] == '\0') {
        if (to_splice_in.tail_ != nullptr) {
            to_splice_in.tail_->next = head_;
            head_ = to_splice_in.head_;
        }
        to_splice_in.head_ = to_splice_in.tail_ = nullptr;
        return;
    }
    Node* start = nullptr;
    Node* end = nullptr;
    start = FindStart(pattern);
    end = FindEnd(pattern);
    if (start == nullptr) {
        throw std::runtime_error("🤠");
    }
    if (start == head_) {            //only one component
        head_ = to_splice_in.head_;
    } else {
        Node* curr = head_;
        while (curr->next != start) {
            curr = curr->next;
        }
        curr->next = to_splice_in.head_;
    }
    while (start != end) {
        Node* tmp = start;
        start = start->next;
        delete tmp;
    }
    to_splice_in.tail_->next = end;
    to_splice_in.head_ = to_splice_in.tail_ = nullptr;
}