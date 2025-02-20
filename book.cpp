#include "book.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

book::book(const std::string& category, const std::string &name, double price, int qty, const std::string& isbn, const std::string& author) 
    : Product(category, name, price, qty), isbn_(isbn), author_(author) {}

book::~book(){}

std::set<std::string> book::keywords() const{
  std::set<std::string> keys = parseStringToWords(name_);
  std::set<std::string> authorKeys = parseStringToWords(author_);
  keys.insert(authorKeys.begin(), authorKeys.end());
  keys.insert(isbn_);
  return keys;
}

std::string book::displayString() const{
  std::string price = std::to_string(price_);
	size_t pos = price.find('.');
	if (pos != std::string::npos){
    price = price.substr(0, pos + 3);
  }
  return name_ + "\nAuthor: " + author_ + " ISBN: " + isbn_ + "\n" + price + " " + std::to_string(qty_) + " left.";
}

void book::dump(std::ostream& os) const{
  os << "book" << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << "\n";
}


