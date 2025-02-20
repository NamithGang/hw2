#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <iostream>
#include <string>
#include <map>
#include <queue>
#include "datastore.h"

class mydatastore : public DataStore{
  public:
    mydatastore();
    ~mydatastore();
    void addProduct(Product* p) override;
    void addUser(User* u) override;
    std::vector<Product*> search(std::vector<std::string>& terms, int type) override;
    void dump(std::ostream& ofile) override;
    
    void addToCart(const std::string& username, Product* product);
    void viewCart(const std::string& username) const;
    void buyCart(const std::string& username);

  private:
    std::vector<Product*> pList;
    std::map<std::string, User*> uList;
    std::map<std::string,std::vector<Product*>> cart;
    std::map<std::string, std::set<Product*>> keywordMap;
};

#endif