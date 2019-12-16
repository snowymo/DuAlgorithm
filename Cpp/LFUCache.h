#pragma once
#include "common.h"

// 460. LFU Cache
// Design and implement a data structure for Least Frequently Used (LFU) cache. It should support the following operations: get and put.
/* 
	Example:
	LFUCache cache = new LFUCache( 2 );

	cache.put(1, 1);
	cache.put(2, 2);
	cache.get(1);       // returns 1
	cache.put(3, 3);    // evicts key 2
	cache.get(2);       // returns -1 (not found)
	cache.get(3);       // returns 3.
	cache.put(4, 4);    // evicts key 1.
	cache.get(1);       // returns -1 (not found)
	cache.get(3);       // returns 3
	cache.get(4);       // returns 4
*/
class LFUCache {
private:
	enum Data { KEY, VAL, FREQ };
	int m_capacity;
	int m_size;
	int m_min_freq;
	unordered_map<int, list<tuple<int, int, int>>> m_freq_to_nodes;            // freq to list of {key, val, freq}
	unordered_map<int, list<tuple<int, int, int>>::iterator> m_key_to_nodeit;  // key to list iterator
public:
	LFUCache(int m_capacity) : m_capacity(m_capacity), m_size(0), m_min_freq(0) {
	}

	int get(int key) {
		if (!m_key_to_nodeit.count(key)) {
			return -1;
		}

		auto new_node = *m_key_to_nodeit[key];
		auto& freq = std::get<FREQ>(new_node);
		m_freq_to_nodes[freq].erase(m_key_to_nodeit[key]);
		if (m_freq_to_nodes[freq].empty()) {
			m_freq_to_nodes.erase(freq);
			if (m_min_freq == freq) {
				++m_min_freq;
			}
		}
		++freq;
		m_freq_to_nodes[freq].emplace_back(move(new_node));
		m_key_to_nodeit[key] = prev(m_freq_to_nodes[freq].end());

		return std::get<VAL>(*m_key_to_nodeit[key]);
	}

	void put(int key, int value) {
		if (m_capacity <= 0) {
			return;
		}

		if (get(key) != -1) {
			std::get<VAL>(*m_key_to_nodeit[key]) = value;
			return;
		}

		if (m_size == m_capacity) {
			m_key_to_nodeit.erase(std::get<KEY>(m_freq_to_nodes[m_min_freq].front()));
			m_freq_to_nodes[m_min_freq].pop_front();
			if (m_freq_to_nodes[m_min_freq].empty()) {
				m_freq_to_nodes.erase(m_min_freq);
			}
			--m_size;
		}

		m_min_freq = 1;
		m_freq_to_nodes[m_min_freq].emplace_back(key, value, m_min_freq);
		m_key_to_nodeit[key] = prev(m_freq_to_nodes[m_min_freq].end());
		++m_size;
	}
};

/**
* Your LFUCache object will be instantiated and called as such:
* LFUCache obj = new LFUCache(capacity);
* int param_1 = obj.get(key);
* obj.put(key,value);
*/

// Mine
class LFUCache {
    private:
    int _capacity;
    int smallest;
    struct CacheNode{
        int key;
        int value;
        int frequency;
        CacheNode(int k, int v){
            key = k; 
            value = v; 
            frequency = 1;
        }
        void add(){
            ++frequency;
        }
    };
    
    unordered_map<int, list<CacheNode>::iterator> mymap;
    unordered_map<int, list<CacheNode>> myfreqmap;
public:
    LFUCache(int capacity) {
        _capacity = capacity;
    }
    
    void addToFreq(int f, int key){
        if(myfreqmap.count(f) == 0){
            //std::cout << "L28:" << mymap[key]->key << "," << mymap[key]->value << "\n";
            myfreqmap[f] = {*mymap[key]};
        }else if(myfreqmap[f].empty()){
            //std::cout << "L31:" << mymap[key]->key << "," << mymap[key]->value << "\n";
            myfreqmap[f] = {*mymap[key]};
        }else
            myfreqmap[f].push_front(*mymap[key]);
    }
    
    int get(int key) {
        if(mymap.find(key) != mymap.end()){
            auto iter = mymap[key];
            int curf = iter->frequency;
            // cout << "curf:" << curf << "\n";
            
            mymap[key]->add();
            addToFreq(curf+1, key);
            // cout << "update add freq:";
            // printfreqkey();
            
            myfreqmap[curf].erase(iter);
            // cout << "update erase freq:";
            // printfreqkey();
            
            if(curf == smallest && myfreqmap[curf].empty())
                ++smallest;
            // cout << "smallest:" << smallest << "\n";
            
            mymap[key] = myfreqmap[curf+1].begin();
            // cout << "update map:";
            // printmapkey();
            return mymap[key]->value;
        }else
            return -1;
    }
    
    void printmapkey(){
        cout << "map:\t";
        for (auto const& x : mymap)
        {
            std::cout << x.first  // string (key)
                      << ':' 
                      << x.second->value // string's value 
                      << "\t";
        }
        cout << "end\n";
    }
    
    void printfreqkey(){
        cout << "freq:\t";
        for (auto const& x : myfreqmap)
        {
            std::cout << x.first  // string (key)
                      << ':' 
                      << x.second.size() // string's value 
                      << "\t" ;
        }
        cout << "end\n";
    }
    
    void put(int key, int value) {
        if(mymap.find(key) != mymap.end()){
            auto iter = mymap[key];
            
            int curf = mymap[key]->frequency;
            
            mymap[key]->add();
            mymap[key]->value = value;
            addToFreq(curf+1, key);
            mymap[key] = myfreqmap[curf+1].begin();
            
            myfreqmap[curf].erase(iter);
            if(curf == smallest && myfreqmap[curf].empty())
                ++smallest;
        }else if(mymap.size() < _capacity){
            if(myfreqmap[1].empty()){
                myfreqmap[1] = {CacheNode(key, value)};
            }else
                myfreqmap[1].push_front(CacheNode(key, value));
            mymap[key] = myfreqmap[1].begin();
            smallest = 1;
        }else if(_capacity > 0){
            mymap.erase(myfreqmap[smallest].back().key);
            myfreqmap[smallest].pop_back();
            
            myfreqmap[1].push_front(CacheNode(key, value));
            mymap[key] = myfreqmap[1].begin();
            smallest = 1;
        }
        // printmapkey();
        // printfreqkey();
    }
};
