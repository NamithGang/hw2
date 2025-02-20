#include "clothing.h"
#include <string>


clothing::clothing(const std::string& category, const std::string& name, double price, int qty,
                   const std::string& size, const std::string& brand)
    : Product(category, name, price, qty), size_(size), brand_(brand) {}

clothing::~clothing(){}

std::set<std::string> clothing::keywords() const{
  std::set<std::string> keys = parseStringToWords(name_);
  std::set<std::string> brandKeys = parseStringToWords(brand_);
  keys.insert(brandKeys.begin(), brandKeys.end());
  return keys;
}

std::string clothing::displayString() const{
  std::string price = std::to_string(price_);
  size_t pos = price.find('.');
  if (pos != std::string::npos){
    price = price.substr(0, pos + 3);
  }
  return name_ + "\nSize: " + size_ + " Brand: " + brand_ + "\n" + price + " " + std::to_string(qty_) + " left.";
}

void clothing::dump(std::ostream& os) const{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << std::endl;
}


