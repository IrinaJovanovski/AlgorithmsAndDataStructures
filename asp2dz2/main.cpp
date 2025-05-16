#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <fstream>
using namespace std;

typedef struct node{
    vector<long long> keys;
    vector<vector<string>*> data;
    vector<struct node*> ptrchildren;
    struct node *parent;
    bool leaf;
} BNode;

typedef struct tree{
    BNode *root;
    int m;
    int height;
} BTree;


BTree* createBTree(int m) {
    BTree* bt = new BTree;
    bt->root = new BNode;
    bt->root->leaf = true;
    bt->root->parent = nullptr;
    bt->m = m;
    bt->height = -1; //prazan koren
    return bt;
}

bool min_keys(BNode *b,BTree *bt){
    if(b->keys == bt->root->keys && !b->leaf){
        if (((b->keys).size() + 1) == 2 ){
            return false; // bice premalo nakon brisanja
        }else{
            return true; //dovoljno
        }
    }
    if(b->keys != bt->root->keys && !b->leaf){
        if (((b->keys).size() + 1) == long(ceil(bt->m / 2.)) ){
            return false;
        }else{
            return true;
        }
    }
    if(b->leaf){
        if ((b->keys).size() ==  long(ceil(bt->m / 2.)) - 1){
            return false;
        }
    }
    return true;
}

bool max_keys(BNode *b,BTree *bt){
    if ((b->keys).size() == bt->m ){
        return true; //prekoracenje
    }
    return false;
}


BNode* find_leaf(BTree *bt, long long key){
    BNode *curr = bt->root;
    int j;
    while(!(curr->leaf)){
        j = 0;
        while(key > ((curr->keys)[j]) && j < (curr->keys).size()){
            j++;
        }
        if(key == ((curr->keys)[j])){
            return curr;
        }
        curr = (curr->ptrchildren)[j];
    }
    return curr;
}

BNode* split_node(BNode *curr,BTree *bt){
    int split = ceil(((curr->keys).size()) / 2.) - 1;
    BNode* brother = new BNode;
    //(brother->data).assign(bt->m, nullptr);
    //(brother->ptrchildren).assign(bt->m + 1, nullptr);
    brother->leaf = curr->leaf;
    if(!(curr->parent)){
        bt->height += 1;
        BNode* sibling = new BNode;
        sibling->parent = curr;
        sibling->leaf = brother->leaf;
        //(sibling->data).assign(bt->m, nullptr);
        //(sibling->ptrchildren).assign(bt->m + 1, nullptr);
        for(int k = 0;k < split;k++){
            (sibling->keys).push_back((curr->keys)[k]);
        }
        for(int k = 0;k < split;k++){
            (sibling->data).push_back((curr->data)[k]);
        }
        if(!(curr->ptrchildren).empty()) {
            for (int k = 0; k < split + 1; k++) {
                (sibling->ptrchildren).push_back((curr->ptrchildren)[k]);
                ((curr->ptrchildren)[k])->parent = sibling;
            }
        }
        //copy(  ((curr->data)).begin(), ((curr->data)).begin() + split, ((sibling->data)).begin());
        //(sibling->keys).assign( split, 0);
        //copy(  ((curr->keys)).begin(), ((curr->keys)).begin() + split, ((sibling->keys)).begin());
        //copy(  ((curr->ptrchildren)).begin(), ((curr->ptrchildren)).begin() + split + 1, ((sibling->ptrchildren)).begin());
        brother->parent = curr;
        for(int k = split + 1;k < (curr->keys).size();k++){
            (brother->keys).push_back((curr->keys)[k]);
        }
        for(int k = split + 1;k < (curr->data).size();k++){
            (brother->data).push_back((curr->data)[k]);
        }
        if(!(curr->ptrchildren).empty()){
            for (int k = split + 1; k < (curr->ptrchildren).size(); k++) {
                (brother->ptrchildren).push_back((curr->ptrchildren)[k]);
                ((curr->ptrchildren)[k])->parent = brother;
            }
        }
        //copy(  ((curr->data)).begin()+ split + 1, ((curr->data)).end() , ((brother->data)).begin());
        //(brother->keys).assign((curr->keys).size() - split - 1, 0);
        //copy(  ((curr->keys)).begin()+ split + 1, ((curr->keys)).end(), ((brother->keys)).begin());
        //copy(  ((curr->ptrchildren)).begin()+ split + 1, ((curr->ptrchildren)).end() , ((brother->ptrchildren)).begin());
        curr->leaf = false;
        if(!(curr->keys).empty()){
            (curr->keys).erase(  ((curr->keys)).begin(), ((curr->keys)).begin() + split);
            (curr->keys).erase(  ((curr->keys)).begin() + 1, ((curr->keys)).end());
        }
        if(!(curr->data).empty()){
            (curr->data)[0] = (curr->data)[split];
            (curr->data).erase(  ((curr->data)).begin() + 1, ((curr->data)).end());
        }
        if(!(curr->ptrchildren).empty()){
            (curr->ptrchildren).erase(  ((curr->ptrchildren)).begin(), ((curr->ptrchildren)).end());
        }
        //(curr->ptrchildren).assign(bt->m + 1, nullptr);
        (curr->ptrchildren).push_back(sibling);
        (curr->ptrchildren).push_back(brother);
    }else{
        brother->parent = curr->parent;
        //(brother->keys).assign((curr->keys).size() - split - 1, 0);
        long long key = (curr->keys)[split];
        int j = 0;
        while((curr->parent->keys)[j] < key && j<(curr->parent->keys).size()){
            j++;
        }
        (curr->parent->keys).insert((curr->parent->keys).begin() + j, key);
        (curr->parent->data).insert((curr->parent->data).begin() + j, (curr->data)[split]);
        (curr->parent->ptrchildren).insert((curr->parent->ptrchildren).begin() + j + 1, brother);
        for(int k = split + 1;k < (curr->keys).size();k++){
            (brother->keys).push_back((curr->keys)[k]);
        }
        for(int k = split + 1;k < (curr->data).size();k++){
            (brother->data).push_back((curr->data)[k]);
        }
        //copy(  ((curr->data)).begin() + split + 1, ((curr->data)).end(), ((brother->data)).begin());
        if(!(curr->ptrchildren).empty()){
            for(int k = split + 1;k < (curr->ptrchildren).size();k++){
                (brother->ptrchildren).push_back((curr->ptrchildren)[k]);
                ((curr->ptrchildren)[k])->parent = brother;
            }
        }
        if(!(curr->keys).empty()){
            (curr->keys).erase((curr->keys).begin() + split, (curr->keys).end());
        }
        if(!(curr->data).empty()){
            (curr->data).erase((curr->data).begin() + split, (curr->data).end());
        }
        if(!(curr->ptrchildren).empty()){
            (curr->ptrchildren).erase((curr->ptrchildren).begin() + split + 1, (curr->ptrchildren).end());
        }
    }
    return curr->parent;
}

void insertKey(BTree *bt, string row){
    int m = bt->m;
    vector<string> data;
    char del = '|';
    stringstream ss (row);
    string word;
    while (getline (ss, word, del)) {
        data.push_back (word);
    }
    long long key = stoll(data[0]);
    BNode *curr;

    if(bt->height == -1){ //prazan koren
        curr = bt->root;
        //(curr->ptrchildren).assign(1, nullptr);
        (curr->keys).push_back(key);
        (curr->data).assign(1, nullptr);
        (curr->data)[0] = new vector<string>(6);
        copy(  data.begin(), data.end(), (((curr->data)[0]))->begin());
        bt->height += 1;
        return;
    }
    curr = find_leaf(bt,key);
    if(find((curr->keys).begin(),(curr->keys).end(),key) != (curr->keys).end()){
        cout << "Zadati primarni kljuc vec postoji!" << endl;
        return;
    }
    //dodavanje kljuca tj. cvora

    int j = 0;
    while((curr->keys)[j] < key && j<(curr->keys).size()){
        j++;
    }
    if(j == (curr->keys).size()){
        (curr->data).push_back(nullptr);
        (curr->data)[j] = new vector<string>(6);
        copy(  data.begin(), data.end(), (((curr->data)[j]))->begin());
        (curr->keys).push_back(key);
    }else{
        (curr->keys).insert((curr->keys).begin() + j, key);
        vector<string>* temp;
        (curr->data).insert((curr->data).begin() + j, nullptr);
        (curr->data)[j] = new vector<string>(6);
        copy(  data.begin(), data.end(), (((curr->data)[j]))->begin());
    }
    if(max_keys(curr,bt)){
        // split cvora
        BNode *n = split_node(curr,bt);
        while(n){
            // split predaka
            if(max_keys(n,bt)){
                n = split_node(n,bt);
            }else{
                break;
            }
        }
    }
}


void create_from_file(BTree *bt,string &file){
    ifstream dat;
    dat.open(file);
    if( ! dat.is_open() ) {
        exit(1);
    }
    string row;

    while(getline(dat, row)){
        if(row.empty()){
            continue;
        }
        insertKey(bt,row);
    }
    dat.close();
}


void print_index(BTree* bt) {
    vector<BNode *> stack;
    BNode *curr = bt->root;
    stack.push_back(curr);
    while(!stack.empty()){
        curr = stack.back();
        stack.pop_back();
        if(curr->ptrchildren.empty()){
            for(int i = 0; i < (curr->data).size(); i++){
                if(i){
                    cout << ", ";
                    cout << endl;
                }
                cout << (*(curr->data[i]))[0] << "|" << (*(curr->data[i]))[1] << "|" << (*(curr->data[i]))[2] << "|" << (*(curr->data[i]))[3] << "|" << (*(curr->data[i]))[4] << "|" << (*(curr->data[i]))[5];
            }
            cout << endl;
            cout << "-------------------------------------------------------------------------";
            cout << endl;
            continue;
        }
        for(int i = (curr->ptrchildren).size() - 1; i >= 0; i--){
            stack.push_back(curr->ptrchildren[i]);
        }
        for(int i = 0; i < (curr->data).size(); i++){
            if(i){
                cout << ", ";
                cout << endl;
            }
            cout << (*(curr->data[i]))[0] << "|" << (*(curr->data[i]))[1] << "|" << (*(curr->data[i]))[2] << "|" << (*(curr->data[i]))[3] << "|" << (*(curr->data[i]))[4] << "|" << (*(curr->data[i]))[5];
        }
        cout << endl;
        cout << "-------------------------------------------------------------------------";
        cout << endl;
    }
}

void search_accounts(BTree* bt, vector<string> client){
    int steps = 0;
    vector<vector<string>> accounts;
    ofstream o("Accounts.txt");
    vector<BNode *> stack;
    BNode* curr;
    stack.push_back(bt->root);
    while(!stack.empty()){
        curr = stack.back();
        stack.pop_back();
        for(int i = 0; i < curr->data.size();i++){
            // kljucevi == client
            if (client[0] == (*(curr->data[i]))[2]){
                steps += 1;
                accounts.push_back(*(curr->data[i]));
            }
            //ptr kljucevi == klijent slucajevi
            if(curr->leaf){
                continue;
            }
            if(i == 0){
                if(stoll(client[0]) <= stoll((*(curr->data[0]))[2])){
                    steps += 1;
                    stack.push_back(curr->ptrchildren[0]);
                }
            }else if(i > 0 && i < curr->data.size()){
                if(stoll(client[0]) >= stoll((*(curr->data[i - 1]))[2]) && stoll(client[0]) <= stoll((*(curr->data[i]))[2])){
                    steps += 1;
                    stack.push_back(curr->ptrchildren[i]);
                }
            }
            if(i == curr->data.size() - 1){
                if(stoll(client[0]) >= stoll((*(curr->data[i]))[2])){
                    steps += 1;
                    stack.push_back(curr->ptrchildren[i + 1]);
                }
            }
        }

    }
    cout << "Pretraga je zavrsena u " << steps << " koraka.";
    cout << endl;
    if(accounts.empty()){
        o << client[0] << "|" << client[1] << "|" << client[2] << "|" << client[3] << "|null|null|null|null";
        o << endl;
        return;
    }
    sort(accounts.begin(),accounts.end());
    for(int i = 0; i < accounts.size(); i++){
        o << client[0] << "|" << client[1] << "|" << client[2] << "|" << client[3] << "|" << (accounts[i])[0] << "|" << (accounts[i])[2] << "|" << (accounts[i])[4] << "|" << (accounts[i])[5];
        o << endl;
    }

}
int join_nodes(BNode* currI, BNode* currII,BTree *bt){
    int index = 0;
    for(int j = 0; j < (currI->parent)->ptrchildren.size(); j++) {
        if ((((currI->parent)->ptrchildren)[j])->keys == currI->keys) {
            index = j;
        }
    }
    // currI je levi cvor, currII je desni
    currI->keys.push_back(((currI->parent)->keys)[index]);
    currI->data.push_back(((currI->parent)->data)[index]);
    int last = 0;
    for(int j = 0; j < (currII)->keys.size(); j++){
        currI->keys.push_back(((currII)->keys)[j]);
        currI->data.push_back(((currII)->data)[j]);
        if(!currI->leaf){
            currI->ptrchildren.push_back(((currII)->ptrchildren)[j]);
            ((currII->ptrchildren)[j])->parent = currI;
            last = j + 1;
        }
    }
    if(!currI->leaf){
        if(last == (currII)->ptrchildren.size() - 1){
            currI->ptrchildren.push_back(((currII)->ptrchildren)[last]);
            ((currII->ptrchildren)[last])->parent = currI;
        }
    }
    (currII->keys).clear();
    (currII->data).clear();
    if(!min_keys(currI->parent,bt)){
        return index;
    }else{
        ((currI->parent)->keys).erase(((currI->parent)->keys).begin() + index);
        ((currI->parent)->data).erase(((currI->parent)->data).begin() + index);
        ((currI->parent)->ptrchildren).erase(((currI->parent)->ptrchildren).begin() + index + 1);
    }
    return -1;
}

int delete_leaf(BNode* currI, BTree* bt, int index){
   BNode *curr;
   int x = 0;

   if(currI->keys == bt->root->keys){
       if(!min_keys(currI,bt)){
           bt->root = (currI->ptrchildren)[0];
           currI->parent = nullptr;
           bt->height -= 1;
       }else{
           currI->keys.erase((currI->keys).begin() + index);
           currI->data.erase((currI->data).begin() + index);
           if(!currI->leaf) {
               currI->ptrchildren.erase((currI->ptrchildren).begin() + index + 1);
           }
       }
       return -1;
   }
    if(min_keys(currI,bt)){
        currI->keys.erase((currI->keys).begin() + index);
        currI->data.erase((currI->data).begin() + index);
        /*if(!currI->leaf){
            currI->ptrchildren.erase((currI->ptrchildren).begin() + index + 1);
        }*/
        return -1;
    }else{ //pozajmica od brata
        curr = currI;
        for(int j = 0; j < (curr->parent)->ptrchildren.size(); j++){
            if((((curr->parent)->ptrchildren)[j])->keys == curr->keys){
                x = j;
                break;
            }
        }
        BNode* brother;
        if(x == 0){ //samo desni
            if(min_keys(((curr->parent)->ptrchildren)[x + 1],bt)){
                brother = ((curr->parent)->ptrchildren)[x + 1];
                curr->keys.erase((curr->keys).begin() + index);
                curr->keys.push_back(((curr->parent)->keys)[x]);
                ((curr->parent)->keys)[x] = (brother->keys)[0];
                (brother->keys).erase((brother->keys).begin());
                curr->data.erase((curr->data).begin() + index);
                curr->data.push_back(((curr->parent)->data)[x]);
                ((curr->parent)->data)[x] = (brother->data)[0];
                (brother->data).erase((brother->data).begin());
                if(!curr->leaf){
                    curr->ptrchildren.push_back((brother->ptrchildren)[0]);
                    ((brother->ptrchildren)[0])->parent = curr;
                    (brother->ptrchildren).erase((brother->ptrchildren).begin());
                }
                return -1;
            }else{
                brother = ((curr->parent)->ptrchildren)[x + 1];
                curr->keys.erase((curr->keys).begin() + index);
                curr->data.erase((curr->data).begin() + index);
                if(!curr->leaf){
                    curr->ptrchildren.erase((curr->ptrchildren).begin() + index + 1);
                }
                x = join_nodes(curr,brother,bt);
                return x;
            }
        }else if(x > 0 && x < (curr->parent)->ptrchildren.size() - 1){ //oba brata (prvo desni, pa levi)
            if(min_keys(((curr->parent)->ptrchildren)[x + 1],bt)){
                brother = ((curr->parent)->ptrchildren)[x + 1];
                curr->keys.erase((curr->keys).begin() + index);
                curr->keys.push_back(((curr->parent)->keys)[x]);
                ((curr->parent)->keys)[x] = (brother->keys)[0];
                (brother->keys).erase((brother->keys).begin());
                curr->data.erase((curr->data).begin() + index);
                curr->data.push_back(((curr->parent)->data)[x]);
                ((curr->parent)->data)[x] = (brother->data)[0];
                (brother->data).erase((brother->data).begin());
                if(!curr->leaf){
                    curr->ptrchildren.push_back((brother->ptrchildren)[0]);
                    ((brother->ptrchildren)[0])->parent = curr;
                    (brother->ptrchildren).erase((brother->ptrchildren).begin());
                }
                return -1;
            }
            if(min_keys(((curr->parent)->ptrchildren)[x - 1],bt)){
                brother = ((curr->parent)->ptrchildren)[x - 1];
                curr->keys.erase((curr->keys).begin() + index);
                (curr->keys).insert((curr->keys).begin(),((curr->parent)->keys)[x - 1]);
                ((curr->parent)->keys)[x - 1] = (brother->keys).back();
                (brother->keys).pop_back();
                curr->data.erase((curr->data).begin() + index);
                (curr->data).insert((curr->data).begin(),((curr->parent)->data)[x - 1]);
                ((curr->parent)->data)[x - 1] = (brother->data).back();
                (brother->data).pop_back();
                if(!curr->leaf){
                    curr->ptrchildren.insert((curr->ptrchildren).begin(),(brother->ptrchildren).back());
                    ((brother->ptrchildren)[(brother->ptrchildren).size() - 1])->parent = curr;
                    (brother->ptrchildren).erase((brother->ptrchildren).end() - 1);
                }
                return -1;
            }
            brother = ((curr->parent)->ptrchildren)[x + 1];
            curr->keys.erase((curr->keys).begin() + index);
            curr->data.erase((curr->data).begin() + index);
            if(!curr->leaf){
                curr->ptrchildren.erase((curr->ptrchildren).begin() + index + 1);
            }
            x = join_nodes(curr,brother,bt);
            return x;
        }else if(x == (curr->parent)->ptrchildren.size() - 1){ //samo levi
            if(min_keys(((curr->parent)->ptrchildren)[x - 1],bt)){
                brother = ((curr->parent)->ptrchildren)[x - 1];
                curr->keys.erase((curr->keys).begin() + index);
                (curr->keys).insert((curr->keys).begin(),((curr->parent)->keys)[x - 1]);
                ((curr->parent)->keys)[x - 1] = (brother->keys).back();
                (brother->keys).pop_back();
                curr->data.erase((curr->data).begin() + index);
                (curr->data).insert((curr->data).begin(),((curr->parent)->data)[x - 1]);
                ((curr->parent)->data)[x - 1] = (brother->data).back();
                (brother->data).pop_back();
                if(!curr->leaf){
                    curr->ptrchildren.insert((curr->ptrchildren).begin(),(brother->ptrchildren).back());
                    ((brother->ptrchildren)[(brother->ptrchildren).size() - 1])->parent = curr;
                    (brother->ptrchildren).erase((brother->ptrchildren).end() - 1);
                }
                return -1;
            }else{
                brother = ((curr->parent)->ptrchildren)[x - 1];
                curr->keys.erase((curr->keys).begin() + index);
                curr->data.erase((curr->data).begin() + index);
                if(!curr->leaf){
                    curr->ptrchildren.erase((curr->ptrchildren).begin() + index + 1);
                }
                x = join_nodes(brother,curr,bt);
                return x;
            }
        }
    }
    return -1;
}

int delete_parent(BNode* currI,BTree* bt,int index){
    BNode *next;
    next = (currI->ptrchildren)[index + 1];
    while(!(next->ptrchildren).empty()){
        next = (next->ptrchildren)[0];
    }
    (currI->keys)[index] = (next->keys)[0];
    (currI->data)[index] = (next->data)[0];
    return delete_leaf(next,bt,0);
}

int delete_node(BTree* bt, string row){
    vector<string> data;
    char del = '|';
    stringstream ss (row);
    string word;
    while (getline (ss, word, del)) {
        data.push_back (word);
    }
    long long key = stoll(data[0]);
    vector<BNode *> stack;
    BNode* curr;
    BNode* currI = nullptr;
    stack.push_back(bt->root);
    int steps = 0;
    int index = 0;
    while(!stack.empty()){
        curr = stack.back();
        stack.pop_back();
        for(int i = 0; i < curr->data.size();i++){
            if (key == curr->keys[i]){
                steps += 1;
                index = i;
                currI = curr;
                break;
            }
            if(curr->leaf){
                continue;
            }
            if(i == 0){
                if(key <= curr->keys[0]){
                    steps += 1;
                    stack.push_back(curr->ptrchildren[0]);
                }
            }else if(i > 0 && i < curr->keys.size()){
                if(key >= curr->keys[i - 1] && key <= curr->keys[i]){
                    steps += 1;
                    stack.push_back(curr->ptrchildren[i]);
                }
            }
            if(i == curr->data.size() - 1){
                if(key >= curr->keys[i]){
                    steps += 1;
                    stack.push_back(curr->ptrchildren[i + 1]);
                }
            }
        }
    }
    if(!currI){
        cout << "Zadati podaci ne postoje u indeksu!";
        cout << endl;
        return steps;
    }

    if(currI->leaf){
        index = delete_leaf(currI,bt,index);
    }else{
        BNode *next;
        next = (currI->ptrchildren)[index + 1];
        steps += 1;
        while(!(next->ptrchildren).empty()){
            next = (next->ptrchildren)[0];
            steps += 1;
        }
        index = delete_parent(currI,bt,index);
        currI = next;
    }
    BNode *parent = currI->parent;
    while(index != -1){
        index = delete_leaf(parent,bt,index);
        parent = parent->parent;
        if(!parent){
            break;
        }
    }
    return steps;
}

void delete_accounts(BTree *bt,long long id){
    int steps = 0;
    vector<vector<string>> accounts;
    vector<BNode*> stack;
    BNode* curr;
    stack.push_back(bt->root);
    while(!stack.empty()){
        curr = stack.back();
        stack.pop_back();
        for(int i = 0; i < curr->data.size();i++){
            // kljucevi == client
            if (id == stoll((*(curr->data[i]))[2])){
                steps += 1;
                accounts.push_back(*((curr->data)[i]));
            }
            //ptr kljucevi == klijent slucajevi
            if(curr->leaf){
                continue;
            }
            if(i == 0){
                if(id <= stoll((*(curr->data[0]))[2])){
                    steps += 1;
                    stack.push_back(curr->ptrchildren[0]);
                }
            }else if(i > 0 && i < curr->data.size()){
                if(id >= stoll((*(curr->data[i - 1]))[2]) && id <= stoll((*(curr->data[i]))[2])){
                    steps += 1;
                    stack.push_back(curr->ptrchildren[i]);
                }
            }
            if(i == curr->data.size() - 1){
                if(id >= stoll((*(curr->data[i]))[2])){
                    steps += 1;
                    stack.push_back(curr->ptrchildren[i + 1]);
                }
            }
        }

    }
    if(accounts.empty()){
        cout << "Nijedan zapis nije obrisan!";
        cout << endl;
        cout << "Pretraga je zavrsena u " << steps << " koraka.";
        cout << endl;
        return;
    }
    sort(accounts.begin(),accounts.end());
    int size = accounts.size();
    for(int i = 0; i < size; i++){
        string s = (accounts[i])[0] + "|" + (accounts[i])[1] + "|" + (accounts[i])[2] + "|" + (accounts[i])[3] + "|" + (accounts[i])[4] + "|" + (accounts[i])[5];
        cout << s;
        steps += delete_node(bt,s);
        cout << endl;
    }
    cout << "Pretraga je zavrsena u " << steps << " koraka.";
    cout << endl;
}

int main() {
    int opt,steps;
    string file,account,client,clients,word;
    long long id;
    vector<string> data;
    vector<vector<string>> accounts;
    ifstream table;
    BTree *bt = nullptr;
    while(1){
        cout << "Odaberite opciju:" << endl;
        cout << "1. Stvaranje indeksa za tabelu CUSTOMER_ACCOUNT" << endl;
        cout << "2. Unistavanje indeksa za tabelu CUSTOMER_ACCOUNT" << endl;
        cout << "3. Ispis indeksa za tabelu CUSTOMER_ACCOUNT" << endl;
        cout << "4. Pretraga i ispis racuna iz CUSTOMER_ACCOUNT za klijenta" << endl;
        cout << "5. Dodavanje zapisa u tabelu CUSTOMER_ACCOUNT" << endl;
        cout << "6. Brisanje zapisa iz indeksa" << endl;
        cout << "7. Brisanje svih racuna klijenta" << endl;
        cout << "8. Kraj programa" << endl;
        cin >> opt;
        switch (opt) {
            case 1:
                int m;
                cout << "Unesite red stabla (izmedju 3 i 10):";
                cin >> m;
                bt = createBTree(m);
                cout << "Unesite ime datoteke:";
                cin >> file;
                create_from_file(bt,file);
                break;
            case 2:
                if(bt == nullptr){
                    cout << "Tabela CUSTOMER_ACCOUNT je obrisana/ne postoji!";
                    break;
                }
                delete bt;
                bt = nullptr;
                break;
            case 3:
                if(bt == nullptr){
                    cout << "Tabela CUSTOMER_ACCOUNT je obrisana/ne postoji!";
                    break;
                }
                print_index(bt);
                break;
            case 4:
                table.open("Accounts.txt");
                if(table.is_open()){
                    table.close();
                }
                if(bt == nullptr){
                    cout << "Tabela CUSTOMER_ACCOUNT je obrisana/ne postoji!";
                    break;
                }
                cout << "Unesite C_ID (primarni kljuc klijenta):";
                cin >> client;
                table.open(R"(asp2dz2//Customer)"); //!!! dodaj putanju do tabele CUSTOMER 
                if( ! table.is_open() ) {
                    exit(1);
                }
                while(getline(table, clients)){
                    if(clients.empty()){
                        continue;
                    }
                    char del = '|';
                    stringstream ss (clients);
                    while (getline (ss, word, del)) {
                        data.push_back (word);
                    }
                    if(data[0] == client){
                        search_accounts(bt,data);
                        data.clear();
                        break;
                    }
                    data.clear();
                }
                table.close();
                break;
            case 5:
                if(bt == nullptr){
                    cout << "Tabela CUSTOMER_ACCOUNT je obrisana/ne postoji!";
                    break;
                }
                cout << "Unesite podatke racuna u formatu CA_ID|CA_B_ID|CA_C_ID|CA_NAME|CA_TAX_ST|CA_BAL:" << endl;
                getline(cin, account);
                getline(cin, account);
                insertKey(bt,account);
                break;
            case 6:
                if(bt == nullptr){
                    cout << "Tabela CUSTOMER_ACCOUNT je obrisana/ne postoji!";
                    break;
                }
                cout << "Unesite podatke racuna u formatu CA_ID|CA_B_ID|CA_C_ID|CA_NAME|CA_TAX_ST|CA_BAL:" << endl;
                getline(cin, account);
                getline(cin, account);
                steps = delete_node(bt,account);
                cout << "Pretraga je zavrsena u " << steps << " koraka.";
                cout << endl;
                break;
            case 7:
                if(bt == nullptr){
                    cout << "Tabela CUSTOMER_ACCOUNT je obrisana/ne postoji!";
                    break;
                }
                cout << "Unesite CA_ID klijenta:" << endl;
                cin >> id;
                delete_accounts(bt,id);
                break;
            case 8:
                exit(0);
            default:
                cout << "Uneli ste nekorektnu vrednost!" << endl;
                break;
        }
        cout << endl;
    }
    return 0;
}
