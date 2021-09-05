#include <iostream>
#include <cstring>
#include <mutex>
#include <cstdlib>
#include <pthread.h>

template<typename K, typename V>
class Node{
    K key_;
    V value_;
    std::mutex mutex_;
public:
    Node(){}
    Node(K key,V value, int level);
    ~Node(){}
    K getKey() const;
    V getValue() const;
    void setValue(V value);
    Node<K, V> **forward_;
    int level_;
};

template<typename K, typename V>
Node<K, V>::Node(const K key, const V value, const int level){
    key_ = key;
    value_ = value;
    level_ = level;
    this->forward_ = new Node<K, V>*[level+1];
    memset(forward_, 0, sizeof(Node*) * (level_ + 1) );
}

template<typename K, typename V>
K Node<K, V>::getKey() const { return key_; }

template<typename K, typename V>
V Node<K, V>::getValue() const { return value_; }

template<typename K, typename V>
void Node<K, V>::setValue(V value) {
    std::unique_lock<std::mutex> mlock(mutex_);
    value_ = value;
}

template<typename K, typename V>
class SkipList{
    int MAXLVL_;
    float p_;
    int level_;
    Node<K, V>* header_;


public:
    SkipList(int, float);
    ~SkipList();
    int randomLevel();
    Node<K, V>* createNode(K, V, int);
    bool insertElem(K, V);
    void displayList();
    bool deleteElem(K);
    bool searchElem(K);
    int size();
    int totalelem_;
};

template<typename K, typename V>
SkipList<K, V>::SkipList(int MAXLVL, float p){
    MAXLVL_ = MAXLVL;
    p_ = p;
    level_ = 0;
    totalelem_ = 0;
    K k;
    V v;
    header_ = new Node<K, V>(k, v, MAXLVL_);
}

// 如果你希望1/2， 1/4 。。。的概率产生层数， p = 0.5
template<typename K, typename V>
int SkipList<K, V>::randomLevel(){
    float r = (float)rand() / RAND_MAX;
    int lvl = 0;
    while(lvl < MAXLVL_ && r < p_){
        lvl++;
        r = (float)rand() / RAND_MAX;
    }
    return lvl;
}

template<typename K, typename V>
Node<K, V>* SkipList<K, V>::createNode(K key, V value, int level){
    Node<K, V>* node = new Node<K, V>(key, value, level);
    return node;
}

template<typename K, typename V>
bool SkipList<K, V>::insertElem(K key, V value){
    Node<K, V>* current = header_;
    Node<K, V>* update[MAXLVL_ + 1];
    memset(update, 0, sizeof(Node<K, V>*) * (MAXLVL_ + 1));

    for(int i = level_; i >= 0; --i){
        //找到每一层key的前序节点号，并保存到update中
        while(current->forward_[i] != nullptr && current->forward_[i]->getKey() < key){
            current = current->forward_[i];
        }
        update[i] = current;
    }
    current = current->forward_[0];
    if(current != nullptr && current->getKey() == key){
        current->setValue(value);
        return true;
    } 
    if(current == nullptr && current->getKey() != key){
        int lvl = randomLevel();
        if(lvl > level_){
            for(int i = level_ + 1; i < lvl + 1;++i ){
                update[i] = header_;
            }
            level_ = lvl;
        }

        Node<K, V>* insertnode = createNode(key, value, lvl);
        for(int i = 0; i <= lvl; ++i){
            insertnode->forward_[i] = update[i]->forward_[i];
            update[i]->forward_[i] = insertnode;
        }
        totalelem_++;
        std::cout << "Sucessfully insert key\n";
        return true;
    }
    return false;
}

template<typename K, typename V>
bool SkipList<K, V>::deleteElem(K key){
    Node<K, V>* current = header_;
    Node<K, V>* update[MAXLVL_ + 1];
    memset(update, 0, sizeof(Node<K, V>*) * (MAXLVL_ + 1));

    for(int i = level_; i >= 0; --i){
        //找到每一层key的前序节点号，并保存到update中
        while(current->forward_[i] != nullptr && current->forward_[i]->getKey() < key){
            current = current->forward_[i];
        }
        update[i] = current;
    }

    current = current->forward_[0];
    if(current != nullptr && current->getKey() == key){
        for(int i = 0; i <= level_; ++i){
            if(update[i]->forward_[i] != current){
                break;
            }
            update[i]->forward_[i] = current->forward_[i];
        }
        delete current;
        // 如果删除的是最高一层的节点，那么我们header_指向了NIL，可以降低level_
        while(level_ > 0 && header_->forward_[level_] == nullptr){
            level_--;
        }
        std::cout << "Successfully delete key\n";
        return true;
    }
    std::cout << "Not found key " << key << std::endl;
    return false;
}


template<typename K, typename V>
void SkipList<K, V>::displayList(){
    std::cout << "Display all Key value\n";
    for(int i = 0; i < level_; ++i){
        Node<K, V>* current = header_->forward_[i];
        std::cout << "LEVEL " << i << ":";
        while(current != nullptr){
            std::cout << current->getKey() << ":" << current->getValue() <<";";
            current = current->forward_[i];
        }
        std::cout << std::endl;
    }
}

template<typename K, typename V>
bool SkipList<K, V>::searchElem(K key){
    Node<K, V>* current = header_;
    for(int i = level_; i >= 0; ++i){
        while(current != nullptr && current->forward_[i]->getKey() < key){
            current = current->forward_[i];
        }
    }
    current = current->forward_[0];
    if(current != nullptr && current->getKey() == key){
        std::cout << "Found key: " << key << ", value: " << current->getValue() << std::endl;
        return true;
    }
    std::cout << "Not found key"  << key << std::endl;
    return false;
}


template<typename K, typename V>
SkipList<K, V>::~SkipList(){ }




