#include "mydatastore.h"
#include "util.h"
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

mydatastore::mydatastore(){

}

mydatastore::~mydatastore(){
    // clear pList vector
    for (Product* p : pList){
        delete p;
    }
    // clear uList map
    for (std::map<std::string, User*>::iterator it = uList.begin(); it != uList.end(); it++){
        delete it->second;
    }
}

vector<Product*> mydatastore::search(vector<string>& terms, int type){
    set<Product*> result;

    if (terms.empty()){ // if null set
        return {};
    } 

    if (keywordMap.find(terms[0]) != keywordMap.end()){ 
        result = keywordMap[terms[0]];
    }
    for (size_t i = 1; i < terms.size(); i++){
        if (keywordMap.find(terms[i]) == keywordMap.end()){
            continue;
        }
        if (type == 0) {
            result = setIntersection(result, keywordMap[terms[i]]);
        } else {
            result = setUnion(result, keywordMap[terms[i]]);
        }
    }
    return vector<Product*>(result.begin(), result.end());
}

void mydatastore::addProduct(Product* p){
    pList.push_back(p);
    set<string> keywords = p->keywords();
    for (set<string>::iterator it = keywords.begin(); it != keywords.end(); ++it){
        keywordMap[*it].insert(p);
    }
}

void mydatastore::addUser(User* u){
  std::string username = convToLower(u->getName());
  uList[username] = u;
}

void mydatastore::dump(ostream& ofile){
   ofile << "<products>" << endl;
    for (vector<Product*>::const_iterator it = pList.begin(); it != pList.end(); it++){
        (*it)->dump(ofile);
    }
    ofile << "</products>" << endl;

    ofile << "<users>" << endl;
    for (map<string, User*>::const_iterator it = uList.begin(); it != uList.end(); it++){
        it->second->dump(ofile);
    }
    ofile << "</users>" << endl;
}

void mydatastore::addToCart(const string& username, Product* p){
   string name = convToLower(username);
    if (uList.find(name) == uList.end()){
        cout << "Invalid request" << endl;
        return;
    }
    cart[name].push_back(p);
}

void mydatastore::viewCart(const string& username) const{
    string name = convToLower(username);
    if (cart.find(name) == cart.end()){
        cout << "Invalid username" << endl;
        return;
    }

    const vector<Product*>& userCart = cart.at(name);
    if (userCart.empty()) {
        cout << "The cart is currently empty" << endl;
        return;
    }

    for (size_t i = 0; i < userCart.size(); i++) {
        cout << "Item " << i + 1 << ":" << endl;
        cout << userCart[i]->displayString() << endl;
    }
}

void mydatastore::buyCart(const string& username){
  string name = convToLower(username);


    if (uList.find(name) == uList.end()){
        cout << "Invalid username" << endl;
        return;
    }

    if (cart.find(name) == cart.end() || cart[name].empty()){
        return; 
    }

    vector<Product*>& userCart = cart.at(name);
    User* user = uList[name];

    vector<Product*>::iterator it = userCart.begin();
    while (it != userCart.end()){
        Product* product = *it;
        if (product->getQty() > 0 && user->getBalance() >= product->getPrice()){
            product->subtractQty(1);
            user->deductAmount(product->getPrice());
            it = userCart.erase(it);
        } else {
            it++;
        }
    }
}

