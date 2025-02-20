#include "movie.h"
#include <string>


movie::movie(const std::string& category, const std::string& name, double price, int qty, const std::string& genre, const std::string& rating): Product(category, name, price, qty), genre_(genre), rating_(rating) {}
movie::~movie(){}

std::set<std::string> movie::keywords() const{
  std::set<std::string> keys = parseStringToWords(name_);
  keys.insert(convToLower(genre_));
  return keys;
}

std::string movie::displayString() const{
  std::string price = std::to_string(price_);
  size_t pos = price.find('.');
  if (pos != std::string::npos){ 
    price = price.substr(0, pos + 3);
  }
  return name_ + "\nGenre: " + genre_ + " Rating: " + rating_ + "\n" + price + " " + std::to_string(qty_) + " left.";
}


void movie::dump(std::ostream& os) const{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << std::endl;
}


