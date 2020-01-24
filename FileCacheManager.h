//
// Created by yakir on 1/16/20.
//

#ifndef EX4_FILECACHEMANAGER_H
#define EX4_FILECACHEMANAGER_H

#include "CacheManager.h"
#include "string"
#include "functional"
#include "unordered_map"
#include "list"
#include "fstream"
#include <iostream>

using namespace std;

template <class P, class S>
class FileCacheManager : public CacheManager<P, S> {
    //Size of a cache
    unsigned int cacheSize{};
    //List that stores the objects' keys' in order to follow the order of objects in map
    list<P> objects;
    //Unordered map that symbolizes the cache - stores the objects in the cache and returning them within O(1)
    unordered_map<P, pair<S, list<string>::iterator>> cache;
public:

    bool isThereSolution(P problem) {
        hash<P> h;
        P prob = to_string(h(problem));
         if (this->cache.find(problem) != this->cache.end()) {
             return true;
         } else {
             ifstream objToRead(prob, ios::out);
             if (!objToRead) {
                 objToRead.close();
                 return false;
             }
             objToRead.close();
                 return true;
             }
    }
    // S getSolution(P problem) = 0;
    //void saveSolution(S solution) = 0;

    FileCacheManager(int capacity) {
        this->cacheSize = capacity;
    }
    ~FileCacheManager(){
        this->objects.clear();
        this->cache.clear();
    }
    //Insert's an object to the cache and saving it to the disk (as a file)
    ///May need changes on how to save an object (by hash?)
    void saveSolution(P key, S obj) {
        hash<P> h;
        string fileNameSave = to_string(h(key));
        ofstream objToWrite(fileNameSave, ios::out);
        if (!objToWrite) {
            throw ("couldn't open a file to write to.\n");
        }
        objToWrite << obj;
        objToWrite.close();
        //check if key is in cache, if not, insert it
        this->refreshCache(key, obj);
    }
    //Get an object from the cache, if not present there, get it from disk (as a file)
    string getSolution(P key) {
        string obj, toAppend;
        hash<P> h;
        string fileNameLoad = to_string(h(key));
        //If the object is not cache, get it from disk (a file)
        if (cache.find(key) == cache.end()) {
            ifstream objToRead(fileNameLoad , ios::in | ios::binary);
            if (!objToRead) {
                throw ("couldn't find the object to load.\n");
            }
            //objToRead.read((char *) &obj, sizeof(obj));
            while (!objToRead.eof()) {
                objToRead >> toAppend;
                obj.append(toAppend + " ");
            }
            this->refreshKey(key);
            objToRead.close();
            return obj;
            //else - the object is in cache - return it (the check happens at the beginning of the method)
        } else {
            obj = cache[key].first;
        }
        //refresh the location of the object in the map and the list if found and returns the object
        this->refreshKey(key);
        return obj;
    }
    //Activates a function unique to the objects present in the cache
    void foreach(const function<void(S &)> func) {
        pair<S, list<string>::iterator> tempObj;
        for (auto &iter : this->objects) {
            tempObj = this->cache[iter];
            func(tempObj.first);
        }
    }
    //Refreshes the cache (and the list) after inserting a new object
    void refreshCache(P key, S obj) {
        string last;
        if (cache.find(key) == cache.end()) {
            //if cache is full, delete last element and insert the new key
            if (objects.size() == cacheSize) {
                //delete older key
                last = objects.back();
                objects.pop_back();
                cache.erase(last);
                //insert new key
                objects.push_front(key);
                cache[key] = {obj, objects.begin()};
            } else {
                objects.push_front(key);
                cache[key] = {obj, objects.begin()};
            }
        }
        this->refreshKey(key);
    }
    //Refreshes the key in cache (and list) after inserting OR getting the object (from cache or disk)
    void refreshKey(P key) {
        pair<S, list<string>::iterator> obj;
        string elemToRemove;
        //Checks if an object is present in cache
        if (cache.find(key) == cache.end()) {
            //Checks cache size
            if (cache.size() >= cacheSize) {
                elemToRemove = objects.back();
                cache.erase(elemToRemove);
                objects.pop_back();
            }
        }
        if (cache.find(key) != cache.end()) {
            objects.remove(key);
        }
        obj = cache[key];
        objects.push_front(key);
        cache.insert({key,obj});
    }
};

#endif //EX4_FILECACHEMANAGER_H
